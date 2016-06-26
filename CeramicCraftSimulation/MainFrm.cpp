
// MainFrm.cpp : CMainFrame ���ʵ��
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
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO:  �ڴ���ӳ�Ա��ʼ������
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
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	//��ӻ���
	///////////////////////////////
	int index = 14;// ռλ������
	int width = 150;// ռλ�����
	int height = 24;

	m_wndToolBar.SetButtonInfo(index, IDC_SLIDER, TBBS_SEPARATOR | TBS_HORZ, width);

	CRect rect;
	m_wndToolBar.GetItemRect(index, &rect);
	rect.bottom = rect.top + height;
	m_slider.Create(WS_CHILD | WS_VISIBLE  ,rect, this, IDC_SLIDER);

	m_slider.SetRange(1, 100);
	m_slider.SetPos(20);


	///////////////////////////////
	//��ӵ�ɫ��
	///////////////////////////////
	index = 15;// ռλ������
	width = 150;// ռλ�����
	m_wndToolBar.SetButtonInfo(index, IDC_PALETTE, TBBS_SEPARATOR , width);

	CRect rect1;
	m_wndToolBar.GetItemRect(index, &rect);
	height = 100;// ComboBox������߶�,�������ɡ�
	rect1.bottom = rect1.top + height;
	CreatePalette();

	//m_slider.Create(WS_CHILD | WS_VISIBLE, rect1, this, IDC_SLIDER);


	///////////////////////////////
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO:  �������Ҫ��ͣ������������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������



void CMainFrame::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	UINT nSize = sizeof(LOGPALETTE)+(sizeof(PALETTEENTRY)*(nColors - 1)); //�����߼���ɫ������ռ�
	pLP = (LOGPALETTE*) new BYTE[nSize];
	//��ʼ���߼���ɫ�壬����R,G,B ������ǵ�ɫ�����ɫ�죬�̣�����������������
	pLP->palVersion = 0x300; //�̶�ֵ
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
