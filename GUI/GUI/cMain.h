#pragma once
#include <wx/wx.h>
#include"DrawBoard.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	wxButton* m_btn1 = nullptr;
	wxTextCtrl* m_txt1 = nullptr;
	wxListBox* m_list1 = nullptr;
	DrawBoard* drawborad;

	void OnSave(wxCommandEvent& event);
	//void OnOpen(wxCommandEvent& event);
	//void OnClear(wxCommandEvent& event);
	
	void OnDrawLineButtonClick(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

