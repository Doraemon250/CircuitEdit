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

	wxBoxSizer* cMainSizer = new wxBoxSizer(wxVERTICAL);//cMain布局
	SetSizer(cMainSizer);

	//主菜单栏
	wxMenuBar* menuBar = new wxMenuBar;
	//文件菜单
	wxMenu* fileMenu = new wxMenu;
	fileMenu->Append(wxID_NEW, "&新建\tCtrl+N");
	fileMenu->Append(wxID_OPEN, "&打开...\tCtrl+M");
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_CLOSE, "&关闭\tCtrl+Shift+W");
	fileMenu->Append(wxID_SAVE, "&保存\tCtrl+S");
	fileMenu->Append(wxID_SAVEAS, "&另存为...\tCtrl+Shift+S");
	fileMenu->Append(wxID_NEW, "&导出项目\tCtrl+Shift+E");
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_EXIT, "&退出\tCtrl+Q");
	menuBar->Append(fileMenu, "&文件");
	//编辑菜单
	wxMenu* editMenu = new wxMenu;

	menuBar->Append(editMenu, "&编辑");
	//项目菜单
	wxMenu* projectMenu = new wxMenu;

	menuBar->Append(projectMenu, "&项目");
	//模拟菜单
	wxMenu* simulateMenu = new wxMenu;

	menuBar->Append(simulateMenu, "&模拟");
	//窗口菜单
	wxMenu* windowMenu = new wxMenu;

	menuBar->Append(windowMenu, "&窗口");
	//帮助菜单
	wxMenu* helpMenu = new wxMenu;

	menuBar->Append(helpMenu, "&帮助");

	SetMenuBar(menuBar);

	//主面板
	wxPanel* m_mainPnl = new wxPanel(this, wxID_ANY);
	wxBoxSizer* m_mainPnlSizer = new wxBoxSizer(wxVERTICAL);//m_mainPnl布局
	m_mainPnl->SetSizer(m_mainPnlSizer);
	cMainSizer->Add(m_mainPnl, 1, wxEXPAND | wxALL, 0);

	//左右分割容器
	wxSplitterWindow* splitter1 = new wxSplitterWindow(m_mainPnl, wxID_ANY, wxDefaultPosition, wxDefaultSize,wxSP_LIVE_UPDATE| wxSP_BORDER);//
	m_mainPnlSizer->Add(splitter1, 1, wxEXPAND | wxALL, 0);
	splitter1->SetDoubleBuffered(true);
	

	//左面板
	
	wxPanel* m_leftPanel = new wxPanel(splitter1,wxID_ANY);
	wxBoxSizer* m_leftPanelSizer = new wxBoxSizer(wxVERTICAL);//m_leftPanel布局
	m_leftPanel ->SetSizer(m_leftPanelSizer);
	//上下分割器
	wxSplitterWindow* splitter2 = new wxSplitterWindow(m_leftPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE| wxSP_BORDER);//
	m_leftPanelSizer->Add(splitter2, 1, wxEXPAND | wxALL, 0);
	splitter2->SetDoubleBuffered(true);

	    //上面的notebook
	wxPanel* m_upPanel = new wxPanel(splitter2, wxID_ANY);
	wxBoxSizer* m_upPanelSizer = new wxBoxSizer(wxVERTICAL);//m_upPanel布局
	m_upPanel->SetSizer(m_upPanelSizer);
	wxNotebook* m_upNotebook = new wxNotebook(m_upPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP);//
	m_upPanelSizer->Add(m_upNotebook, 1, wxEXPAND | wxALL, 0);
	wxPanel* m_panel1 = new wxPanel(m_upNotebook, wxID_ANY);
	wxPanel* m_panel2 = new wxPanel(m_upNotebook, wxID_ANY);
	m_panel1->SetBackgroundColour(wxColour(255, 255, 255));
	wxBoxSizer* m_panel1Sizer = new wxBoxSizer(wxVERTICAL);//m_panel1布局
	m_panel1->SetSizer(m_panel1Sizer);
	m_panel2->SetBackgroundColour(wxColour(255, 255, 255));
	//设计笔记本容器
	m_upNotebook->AddPage(m_panel1, "设计",true);
	        //左侧工具栏
	wxBitmap bitmapAdd;
	bitmapAdd.LoadFile("../resource/image/780.png", wxBITMAP_TYPE_PNG);
	wxImage imageAdd = bitmapAdd.ConvertToImage();
	bitmapAdd = imageAdd.Scale(20, 20, wxIMAGE_QUALITY_HIGH);
	bitmapAdd = wxBitmap(bitmapAdd);
	wxToolBar* left_toolBar = new wxToolBar(m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL);
	left_toolBar->AddTool(201, wxT("添加线路"), bitmapAdd, wxT("添加线路"));
	left_toolBar->Realize();
	m_panel1Sizer->Add(left_toolBar, 0, wxEXPAND | wxALL, 0);
	        //树控件
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
	wxTreeItemId rootId = treeCtrl->AddRoot(wxT("元件库"));
	wxTreeItemId itemId1 = treeCtrl->AppendItem(rootId, wxT("01_基础逻辑门"),0,0);
	wxTreeItemId itemId1_1 = treeCtrl->AppendItem(itemId1, wxT("与门"));
	wxTreeItemId itemId1_2 = treeCtrl->AppendItem(itemId1, wxT("非门"));
	wxTreeItemId itemId1_3 = treeCtrl->AppendItem(itemId1, wxT("或门"));


	wxTreeItemId itemId2 = treeCtrl->AppendItem(rootId, wxT("02_复合逻辑门"),0,0);
	wxTreeItemId itemId2_1 = treeCtrl->AppendItem(itemId2, wxT("与非门"));
	wxTreeItemId itemId2_2 = treeCtrl->AppendItem(itemId2, wxT("或非门"));
	wxTreeItemId itemId2_3 = treeCtrl->AppendItem(itemId2, wxT("同或门"));
	wxTreeItemId itemId2_4 = treeCtrl->AppendItem(itemId2, wxT("异或门"));

	wxTreeItemId itemId3 = treeCtrl->AppendItem(rootId, wxT("03_结点"),0,0);
	wxTreeItemId itemId3_1 = treeCtrl->AppendItem(itemId3, wxT("起始结点"));
	wxTreeItemId itemId3_2 = treeCtrl->AppendItem(itemId3, wxT("终止结点"));

	wxTreeItemId itemId4 = treeCtrl->AppendItem(rootId, wxT("04_扩展元器件"),0,0);




	m_upNotebook->AddPage(m_panel2, "模拟");

	    //下面的notebook
	wxPanel* m_downPanel = new wxPanel(splitter2, wxID_ANY);
	wxBoxSizer* m_downPanelSizer = new wxBoxSizer(wxVERTICAL);//m_downPanel布局
	m_downPanel->SetSizer(m_downPanelSizer);
	wxNotebook* m_downNotebook = new wxNotebook(m_downPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP);//
	m_downPanelSizer->Add(m_downNotebook, 1, wxEXPAND | wxALL, 0);
	wxPanel* m_panel3 = new wxPanel(m_downNotebook, wxID_ANY);
	wxPanel* m_panel4 = new wxPanel(m_downNotebook, wxID_ANY);
	m_panel3->SetBackgroundColour(wxColour(255, 255, 255));
	m_panel4->SetBackgroundColour(wxColour(255, 255, 255));
	m_downNotebook->AddPage(m_panel3, "属性");
	m_downNotebook->AddPage(m_panel4, "状态");
	//属性面板
	wxBoxSizer* m_panel3Sizer = new wxBoxSizer(wxVERTICAL);//m_panel3布局
	
	m_panel3->SetSizer(m_panel3Sizer);


	    //放容器进割上下容器
	splitter2->SplitHorizontally(m_upPanel, m_downPanel, 300);
	//右面板

	wxPanel* m_rightPanel = new wxPanel(splitter1, wxID_ANY);
	wxBoxSizer* m_rightPanelSizer = new wxBoxSizer(wxVERTICAL);//m_rightPanel布局
	m_rightPanel->SetSizer(m_rightPanelSizer);
	//右侧工具栏
	wxBitmap bitmapForDrawLine;
	bitmapForDrawLine.LoadFile("../resource/image/drawLine.png", wxBITMAP_TYPE_PNG);
	wxImage imageForDrawLine = bitmapForDrawLine.ConvertToImage();
	bitmapForDrawLine = imageForDrawLine.Scale(24, 24, wxIMAGE_QUALITY_HIGH);
	bitmapForDrawLine = wxBitmap(bitmapForDrawLine);
	wxToolBar* right_toolBar = new wxToolBar(m_rightPanel, wxID_ANY,wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL);
	right_toolBar->AddTool(101, wxT("画线"), bitmapForDrawLine, wxT("画线工具提示"));

	right_toolBar->Realize();

	drawborad = new DrawBoard(m_rightPanel);
	//放入右侧面板布局管理器
	m_rightPanelSizer->Add(right_toolBar, 0, wxEXPAND | wxALL, 5);
	m_rightPanelSizer->Add(drawborad, 1, wxEXPAND | wxALL, 5);

	//放面板进入左右分割容器
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