#pragma once

#include <wx/wx.h>
#include <wx/graphics.h>

class Text {
protected:
	wxPoint origin;
	wxString content;
	wxFont font;
	wxColour colour;
	double angle = 0;

public:
	Text(wxPoint origin, wxString content);
	Text(wxPoint origin, wxString content, const wxColour& colour, const wxFont font);

	wxPoint getOrigin() { return origin; }
	wxString& getContent() { return content; }
	wxFont& getFont() { return font; }
	double getAngle() { return angle; }
	wxColour getColour() { return colour; }



	void setContent(wxString& newContent) { content = newContent; }
	void setAngle(double newAngle) { angle = newAngle; }
	void setColour(wxColour newColor) { colour = newColor; }
	void setOrigin(wxPoint newOrigin) { origin = newOrigin; }
	void setFont(wxFont newFont) { font = newFont; }

	void drawText(wxGraphicsContext* gc, wxPoint position);
	void drawText(wxGraphicsContext* gc);
};

#pragma once
