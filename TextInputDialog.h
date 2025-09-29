///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __TEXTINPUTDIALOG_H__
#define __TEXTINPUTDIALOG_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class TextInputDialog
///////////////////////////////////////////////////////////////////////////////
class TextInputDialog : public wxDialog
{
private:

protected:
	wxStaticText* m_staticText1;
	wxTextCtrl* m_textCtrl1;
	wxStaticText* m_staticText2;
	wxTextCtrl* m_textCtrl2;
	wxButton* m_button1;
	wxButton* m_button2;

	// Virtual event handlers, overide them in your derived class
	virtual void OnOK(wxCommandEvent& event) { event.Skip(); }
	virtual void OnCancel(wxCommandEvent& event) { event.Skip(); }


public:
	wxString GetText() const { return m_textCtrl1->GetValue(); }
	int GetAngle() const { return wxAtoi(m_textCtrl2->GetValue()); }
	TextInputDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);
	~TextInputDialog();

};

#endif //__TEXTINPUTDIALOG_H__
