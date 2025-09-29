#include "DrawBoard.h"


DrawBoard::DrawBoard(wxWindow* parent) : wxPanel(parent) {

    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &DrawBoard::OnPaint, this);
    Bind(wxEVT_MOTION, &DrawBoard::OnButtonMove, this);
    Bind(wxEVT_LEFT_DOWN, &DrawBoard::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &DrawBoard::OnLeftUp, this);

    isDrawingLine = false;
}

DrawBoard::~DrawBoard() {
}


void DrawBoard::OnPaint(wxPaintEvent& event) {
    wxAutoBufferedPaintDC dc(this);
    dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();

    wxBitmap bufferBitmap(GetClientSize());
    wxMemoryDC memDC;
    memDC.SelectObject(bufferBitmap);
    memDC.SetBackground(*wxWHITE_BRUSH);
    memDC.Clear();
    wxGraphicsContext* gc = wxGraphicsContext::Create(memDC);
    if (gc) {
        //gc->SetAntialiasMode(wxANTIALIAS_DEFAULT);
        //gc->SetInterpolationQuality(wxINTERPOLATION_DEFAULT);
        drawGrid(gc);

        
        //画十字定位线
        
        gc->SetBrush(wxBrush(wxColour(0, 0, 0)));
        gc->SetPen(wxPen(wxColour(0, 0, 0), 1));
        gc->StrokeLine(mousePos.x, 0, mousePos.x, GetSize().y);
        gc->StrokeLine(0, mousePos.y, GetSize().x, mousePos.y);
        
        //显示所有已画图像
        for (const std::unique_ptr<Shape>& shapePtr : shapes) {
            const Shape& shape = *shapePtr;
            Pen.SetColour(shape.GetColor());
            Pen.SetWidth(shape.GetThickness());
            gc->SetPen(Pen);
            gc->SetBrush(shape.GetBrushColor());
            shape.drawSelf(gc);
        }
        //实现显示正在画的图像
        gc->StrokeLine(currentStart.x, currentStart.y, currentEnd.x, currentEnd.y);
        delete gc;
    }

    dc.Blit(0, 0, GetClientSize().GetWidth(), GetClientSize().GetHeight(), &memDC, 0, 0);

}


void DrawBoard::drawGrid(wxGraphicsContext* gc) {

    wxSize size = GetSize();
    int gridSize = 20;

    gc->SetPen(wxPen(wxColour(180, 180, 180), 1, wxPENSTYLE_DOT_DASH));
    for (int x = 0; x < size.x; x += gridSize) {
        gc->StrokeLine(x, 0, x, size.y);
    }

    for (int y = 0; y < size.y; y += gridSize) {
        gc->StrokeLine(0, y, size.x, y);
    }
}

void DrawBoard::OnButtonMove(wxMouseEvent& event) {
    mousePos = event.GetPosition();
    if (isDrawingLine and isDrawing) {
        currentEnd = mousePos;
    }
    Refresh();
}

void DrawBoard::OnLeftDown(wxMouseEvent& event) {

    if (isDrawingLine) {
        isDrawing = true;
        currentStart = event.GetPosition();
    }
    std::unique_ptr<Shape> componentNotPtr = std::make_unique<ComponentNot>(mousePos);
    shapes.push_back(std::move(componentNotPtr));

}

void DrawBoard::OnLeftUp(wxMouseEvent& event) {
    if (isDrawingLine) {
        isDrawing = false;
        std::unique_ptr<Shape> linePtr = std::make_unique<Line>(currentStart, currentEnd);
        shapes.push_back(std::move(linePtr));
        currentStart = currentEnd;
        Refresh();
    }
}
