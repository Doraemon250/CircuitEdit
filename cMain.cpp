#include "cMain.h"
#include <wx/splitter.h>
#include <wx/panel.h>
#include<wx/notebook.h>
#include<wx/sizer.h>
#include <wx/treectrl.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include"DrawBoard.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_TOOL(101, cMain::OnDrawLineButtonClick)
EVT_MENU(wxID_SAVE,cMain::OnSave)
//EVT_MENU(wxID_OPEN,cMain::OnOpen)

//EVT_MENU(wxID_CLEAR,cMain::OnClear)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr,wxID_ANY,"Hello wxWidgets!",wxPoint(30,30),wxSize(800,600))
{

	wxInitAllImageHandlers();

	wxBoxSizer* cMainSizer = new wxBoxSizer(wxVERTICAL);//cMain����
	SetSizer(cMainSizer);

	//���˵���
	wxMenuBar* menuBar = new wxMenuBar;
	//�ļ��˵�
	wxMenu* fileMenu = new wxMenu;
	fileMenu->Append(wxID_NEW, "&�½�\tCtrl+N");
	fileMenu->Append(wxID_OPEN, "&��...\tCtrl+M");
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_CLOSE, "&�ر�\tCtrl+Shift+W");
	fileMenu->Append(wxID_SAVE, "&����\tCtrl+S");
	fileMenu->Append(wxID_SAVEAS, "&���Ϊ...\tCtrl+Shift+S");
	fileMenu->Append(wxID_NEW, "&������Ŀ\tCtrl+Shift+E");
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_EXIT, "&�˳�\tCtrl+Q");
	menuBar->Append(fileMenu, "&�ļ�");
	//�༭�˵�
	wxMenu* editMenu = new wxMenu;

	menuBar->Append(editMenu, "&�༭");
	//��Ŀ�˵�
	wxMenu* projectMenu = new wxMenu;

	menuBar->Append(projectMenu, "&��Ŀ");
	//ģ��˵�
	wxMenu* simulateMenu = new wxMenu;

	menuBar->Append(simulateMenu, "&ģ��");
	//���ڲ˵�
	wxMenu* windowMenu = new wxMenu;

	menuBar->Append(windowMenu, "&����");
	//�����˵�
	wxMenu* helpMenu = new wxMenu;

	menuBar->Append(helpMenu, "&����");

	SetMenuBar(menuBar);

	//�����
	wxPanel* m_mainPnl = new wxPanel(this, wxID_ANY);
	wxBoxSizer* m_mainPnlSizer = new wxBoxSizer(wxVERTICAL);//m_mainPnl����
	m_mainPnl->SetSizer(m_mainPnlSizer);
	cMainSizer->Add(m_mainPnl, 1, wxEXPAND | wxALL, 0);

	//���ҷָ�����
	wxSplitterWindow* splitter1 = new wxSplitterWindow(m_mainPnl, wxID_ANY, wxDefaultPosition, wxDefaultSize,wxSP_LIVE_UPDATE| wxSP_BORDER);//
	m_mainPnlSizer->Add(splitter1, 1, wxEXPAND | wxALL, 0);
	splitter1->SetDoubleBuffered(true);
	

	//�����
	
	wxPanel* m_leftPanel = new wxPanel(splitter1,wxID_ANY);
	wxBoxSizer* m_leftPanelSizer = new wxBoxSizer(wxVERTICAL);//m_leftPanel����
	m_leftPanel ->SetSizer(m_leftPanelSizer);
	//���·ָ���
	wxSplitterWindow* splitter2 = new wxSplitterWindow(m_leftPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE| wxSP_BORDER);//
	m_leftPanelSizer->Add(splitter2, 1, wxEXPAND | wxALL, 0);
	splitter2->SetDoubleBuffered(true);

	    //�����notebook
	wxPanel* m_upPanel = new wxPanel(splitter2, wxID_ANY);
	wxBoxSizer* m_upPanelSizer = new wxBoxSizer(wxVERTICAL);//m_upPanel����
	m_upPanel->SetSizer(m_upPanelSizer);
	wxNotebook* m_upNotebook = new wxNotebook(m_upPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP);//
	m_upPanelSizer->Add(m_upNotebook, 1, wxEXPAND | wxALL, 0);
	wxPanel* m_panel1 = new wxPanel(m_upNotebook, wxID_ANY);
	wxPanel* m_panel2 = new wxPanel(m_upNotebook, wxID_ANY);
	m_panel1->SetBackgroundColour(wxColour(255, 255, 255));
	wxBoxSizer* m_panel1Sizer = new wxBoxSizer(wxVERTICAL);//m_panel1����
	m_panel1->SetSizer(m_panel1Sizer);
	m_panel2->SetBackgroundColour(wxColour(255, 255, 255));
	//��ƱʼǱ�����
	m_upNotebook->AddPage(m_panel1, "���",true);
	        //��๤����
	wxBitmap bitmapAdd;
	bitmapAdd.LoadFile("../resource/image/780.png", wxBITMAP_TYPE_PNG);
	wxImage imageAdd = bitmapAdd.ConvertToImage();
	bitmapAdd = imageAdd.Scale(20, 20, wxIMAGE_QUALITY_HIGH);
	bitmapAdd = wxBitmap(bitmapAdd);
	wxToolBar* left_toolBar = new wxToolBar(m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL);
	left_toolBar->AddTool(201, wxT("�����·"), bitmapAdd, wxT("�����·"));
	left_toolBar->Realize();
	m_panel1Sizer->Add(left_toolBar, 0, wxEXPAND | wxALL, 0);
	        //���ؼ�
	wxTreeCtrl* treeCtrl = new wxTreeCtrl(m_panel1,wxID_ANY,wxDefaultPosition, wxDefaultSize,wxTR_DEFAULT_STYLE| wxTR_HIDE_ROOT
		| wxTR_NO_LINES);
	m_panel1Sizer->Add(treeCtrl, 1, wxEXPAND | wxALL, 0);
	wxImageList* imageList = new wxImageList(16, 16);
	wxBitmap bitmapFile;
	bitmapFile.LoadFile("E:/code_monkey/C++/GUI/resource/image/OIP-C.png", wxBITMAP_TYPE_PNG);
	wxImage imageForDrawText = bitmapFile.ConvertToImage();
	bitmapFile = imageForDrawText.Scale(24, 24, wxIMAGE_QUALITY_HIGH);
	bitmapFile = wxBitmap(bitmapFile);
	imageList->Add(bitmapFile);


	treeCtrl->AssignImageList(imageList);
	wxTreeItemId rootId = treeCtrl->AddRoot(wxT("Ԫ����"));
	wxTreeItemId itemId1 = treeCtrl->AppendItem(rootId, wxT("01_�����߼���"),0,0);
	wxTreeItemId itemId1_1 = treeCtrl->AppendItem(itemId1, wxT("����"));
	wxTreeItemId itemId1_2 = treeCtrl->AppendItem(itemId1, wxT("����"));
	wxTreeItemId itemId1_3 = treeCtrl->AppendItem(itemId1, wxT("����"));


	wxTreeItemId itemId2 = treeCtrl->AppendItem(rootId, wxT("02_�����߼���"),0,0);
	wxTreeItemId itemId2_1 = treeCtrl->AppendItem(itemId2, wxT("�����"));
	wxTreeItemId itemId2_2 = treeCtrl->AppendItem(itemId2, wxT("�����"));
	wxTreeItemId itemId2_3 = treeCtrl->AppendItem(itemId2, wxT("ͬ����"));
	wxTreeItemId itemId2_4 = treeCtrl->AppendItem(itemId2, wxT("�����"));

	wxTreeItemId itemId3 = treeCtrl->AppendItem(rootId, wxT("03_���"),0,0);
	wxTreeItemId itemId3_1 = treeCtrl->AppendItem(itemId3, wxT("��ʼ���"));
	wxTreeItemId itemId3_2 = treeCtrl->AppendItem(itemId3, wxT("��ֹ���"));

	wxTreeItemId itemId4 = treeCtrl->AppendItem(rootId, wxT("04_��չԪ����"),0,0);




	m_upNotebook->AddPage(m_panel2, "ģ��");

	    //�����notebook
	wxPanel* m_downPanel = new wxPanel(splitter2, wxID_ANY);
	wxBoxSizer* m_downPanelSizer = new wxBoxSizer(wxVERTICAL);//m_downPanel����
	m_downPanel->SetSizer(m_downPanelSizer);
	wxNotebook* m_downNotebook = new wxNotebook(m_downPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP);//
	m_downPanelSizer->Add(m_downNotebook, 1, wxEXPAND | wxALL, 0);
	wxPanel* m_panel3 = new wxPanel(m_downNotebook, wxID_ANY);
	wxPanel* m_panel4 = new wxPanel(m_downNotebook, wxID_ANY);
	m_panel3->SetBackgroundColour(wxColour(255, 255, 255));
	m_panel4->SetBackgroundColour(wxColour(255, 255, 255));
	m_downNotebook->AddPage(m_panel3, "����");
	m_downNotebook->AddPage(m_panel4, "״̬");
	//�������
	wxBoxSizer* m_panel3Sizer = new wxBoxSizer(wxVERTICAL);//m_panel3����
	
	m_panel3->SetSizer(m_panel3Sizer);


	    //������������������
	splitter2->SplitHorizontally(m_upPanel, m_downPanel, 300);
	//�����

	wxPanel* m_rightPanel = new wxPanel(splitter1, wxID_ANY);
	wxBoxSizer* m_rightPanelSizer = new wxBoxSizer(wxVERTICAL);//m_rightPanel����
	m_rightPanel->SetSizer(m_rightPanelSizer);
	//�Ҳ๤����
	wxBitmap bitmapForDrawLine;
	bitmapForDrawLine.LoadFile("../resource/image/drawLine.png", wxBITMAP_TYPE_PNG);
	wxImage imageForDrawLine = bitmapForDrawLine.ConvertToImage();
	bitmapForDrawLine = imageForDrawLine.Scale(24, 24, wxIMAGE_QUALITY_HIGH);
	bitmapForDrawLine = wxBitmap(bitmapForDrawLine);
	wxToolBar* right_toolBar = new wxToolBar(m_rightPanel, wxID_ANY,wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL);
	right_toolBar->AddTool(101, wxT("����"), bitmapForDrawLine, wxT("���߹�����ʾ"));

	right_toolBar->Realize();

	drawborad = new DrawBoard(m_rightPanel);
	//�����Ҳ���岼�ֹ�����
	m_rightPanelSizer->Add(right_toolBar, 0, wxEXPAND | wxALL, 5);
	m_rightPanelSizer->Add(drawborad, 1, wxEXPAND | wxALL, 5);

	//�����������ҷָ�����
	splitter1->SplitVertically(m_leftPanel, m_rightPanel, 600);

	
	
}

cMain::~cMain() {
	
}

void cMain::OnDrawLineButtonClick(wxCommandEvent& event) {
	drawborad->isDrawingLine = true;
	//panel->Refresh();
}

void cMain::OnSave(wxCommandEvent& event) {
	wxString filename = wxFileSelector("Save File", wxEmptyString, wxEmptyString, "json", "JSON files (*.json)|*.json", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
}
/*
void OnOpen(wxCommandEvent& event) {

}
void OnClear(wxCommandEvent& event) {

}*/