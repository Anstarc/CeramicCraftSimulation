
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "CeramicCraftSimulation.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO:  在此添加成员初始化代码
	pLP = NULL;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	//添加滑块
	///////////////////////////////
	int index = 14;// 占位符索引
	int width = 150;// 占位符宽度
	int height = 24;

	m_wndToolBar.SetButtonInfo(index, IDC_SLIDER, TBBS_SEPARATOR | TBS_HORZ, width);

	CRect rect;
	m_wndToolBar.GetItemRect(index, &rect);
	rect.bottom = rect.top + height;
	m_slider.Create(WS_CHILD | WS_VISIBLE  ,rect, this, IDC_SLIDER);

	m_slider.SetRange(1, 100);
	m_slider.SetPos(20);


	///////////////////////////////
	//添加调色板
	///////////////////////////////
	index = 15;// 占位符索引
	width = 150;// 占位符宽度
	m_wndToolBar.SetButtonInfo(index, IDC_PALETTE, TBBS_SEPARATOR , width);

	CRect rect1;
	m_wndToolBar.GetItemRect(index, &rect);
	height = 100;// ComboBox下拉后高度,尽量长吧。
	rect1.bottom = rect1.top + height;
	CreatePalette();

	//m_slider.Create(WS_CHILD | WS_VISIBLE, rect1, this, IDC_SLIDER);


	///////////////////////////////
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO:  如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



void CMainFrame::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (pScrollBar == GetDlgItem(IDC_SLIDER))
	{
		step = nPos / 10.0 * 12;
	}
	//GetActiveView()->SendMessage(WM_HSCROLL);
	CMDIFrameWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}


bool CMainFrame::CreatePalette()
{
	const int nColors = 24; 
	BYTE R[nColors], G[nColors], B[nColors];
	UINT nSize = sizeof(LOGPALETTE)+(sizeof(PALETTEENTRY)*(nColors - 1)); //计算逻辑调色板所需空间
	pLP = (LOGPALETTE*) new BYTE[nSize];
	//初始化逻辑调色板，假设R,G,B 保存的是调色板各颜色红，绿，蓝三个分量的数组
	pLP->palVersion = 0x300; //固定值
	pLP->palNumEntries = nColors;
	for (int i = 0; i < nColors; i++)
	{
		pLP->palPalEntry[i].peRed = R[i];
		pLP->palPalEntry[i].peGreen = G[i];
		pLP->palPalEntry[i].peBlue = B[i];
		pLP->palPalEntry[i].peFlags = 0;
	}
	m_palette.CreatePalette(pLP);
	return true;
}
