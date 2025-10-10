///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "TextInputDialog.h"

///////////////////////////////////////////////////////////////////////////

TextInputDialog::TextInputDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog(parent, id, title, pos, size, style)
{
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    wxBoxSizer* bSizer1;
    bSizer1 = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* bSizer2;
    bSizer2 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText1 = new wxStaticText(this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText1->Wrap(-1);
    bSizer2->Add(m_staticText1, 0, wxALL, 5);

    m_textCtrl1 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    bSizer2->Add(m_textCtrl1, 0, wxALL, 5);


    bSizer1->Add(bSizer2, 1, wxEXPAND, 5);

    wxBoxSizer* bSizer4;
    bSizer4 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText2 = new wxStaticText(this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText2->Wrap(-1);
    bSizer4->Add(m_staticText2, 0, wxALL, 5);

    m_textCtrl2 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    bSizer4->Add(m_textCtrl2, 0, wxALL, 5);


    bSizer1->Add(bSizer4, 1, wxEXPAND, 5);

    wxBoxSizer* bSizer5;
    bSizer5 = new wxBoxSizer(wxHORIZONTAL);

    m_button1 = new wxButton(this, wxID_OK, wxT("MyButton"), wxDefaultPosition, wxDefaultSize, 0);
    bSizer5->Add(m_button1, 0, wxALL, 5);
    
    m_button2 = new wxButton(this, wxID_CANCEL, wxT("MyButton"), wxDefaultPosition, wxDefaultSize, 0);
    bSizer5->Add(m_button2, 0, wxALL, 5);


    bSizer1->Add(bSizer5, 1, wxEXPAND, 5);


    this->SetSizer(bSizer1);
    this->Layout();
    bSizer1->Fit(this);

    this->Centre(wxBOTH);

    // Connect Events
    m_button1->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TextInputDialog::OnOK), NULL, this);
    m_button2->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TextInputDialog::OnCancel), NULL, this);
}

TextInputDialog::~TextInputDialog()
{
    // Disconnect Events
    m_button1->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TextInputDialog::OnOK), NULL, this);
    m_button2->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TextInputDialog::OnCancel), NULL, this);

}
