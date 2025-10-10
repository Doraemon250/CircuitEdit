#pragma once
#include <wx/wx.h>
#include <wx/dcgraph.h>
#include <wx/dcbuffer.h>
#include"Shape.h"

class DrawBoard : public wxPanel
{
public:
	wxPoint mousePos;
	wxPoint currentStart;
	wxPoint currentEnd;
	wxPen Pen;
	
	std::vector<std::unique_ptr<Shape>> shapes;

	bool isDrawingLine;
	bool isDrawing;


	void OnPaint(wxPaintEvent& event);
	void OnButtonMove(wxMouseEvent& event);
	void OnLeftDown(wxMouseEvent& event);
	void OnLeftUp(wxMouseEvent& event);
	void drawGrid(wxGraphicsContext* gc);
	
public:
	DrawBoard(wxWindow* parent);
	~DrawBoard();

public:

};
