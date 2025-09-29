#pragma once
#include <wx/wx.h>
#include <wx/graphics.h>

class Shape 
{
protected:
    wxPoint startPos;
    wxPoint endPos;
    int Thickness;
    wxColour Color;
    wxColour brushColor;
    wxString ShapeType;
public:
    Shape() : Thickness(2), Color(*wxBLACK) {}
    virtual ~Shape() {}

    wxPoint GetStart() const { return startPos; }
    wxPoint GetEnd() const { return endPos; }
    int GetThickness() const { return Thickness; }
    wxColour GetColor() const { return Color; }
    wxColour GetBrushColor() const { return brushColor; }
    wxString GetType() const { return ShapeType; }

    virtual void drawSelf(wxGraphicsContext* gc) const = 0;
};

class Line : public Shape 
{

public:
    Line(const wxPoint& start, const wxPoint& end) : Shape()
    {
        this->startPos = start; this->endPos = end;
    }
    virtual void drawSelf(wxGraphicsContext* gc) const override;
};

class ComponentNot :public Shape
{
public:
    ComponentNot(const wxPoint& mouse) :Shape()
    {
        this->startPos = mouse;
    }
    virtual void drawSelf(wxGraphicsContext* gc) const override;
};

class ComponentAnd :public Shape
{
public:
    ComponentAnd(const wxPoint& mouse) :Shape()
    {
        this->startPos = mouse;
    }
    virtual void drawSelf(wxGraphicsContext* gc) const override;
};