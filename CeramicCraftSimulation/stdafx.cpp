
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// CeramicCraftSimulation.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"


int step = 1;



/*
BOOL CMainFrame::OnQueryNewPalette()
{
	// TODO: Add your message handler code here and/or call default

	GetActiveView()->SendMessage(WM_DOREALIZE);
	return TRUE; //����TRUE����ʵ�����߼���ɫ��
}

void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd)
{
	CFrameWnd::OnPaletteChanged(pFocusWnd);
	// TODO: Add your message handler code here

	if (GetActiveView() != pFocusWnd)
		GetActiveView()->SendMessage(WM_DOREALIZE);
}

�嵥11.2 CTestPalView��Ĳ��ִ���
// TestPalView.h : interface of the CTestPalView class
class CTestPalView : public CView
{
	. . .
protected:

	CPalette m_Palette;
	. . .
		afx_msg LRESULT OnDoRealize(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

// TestPalView.cpp : implementation of the CTestPalView class

BEGIN_MESSAGE_MAP(CTestPalView, CView)

	. . .
	ON_MESSAGE(WM_DOREALIZE, OnDoRealize)
END_MESSAGE_MAP()

CTestPalView::CTestPalView()
{
	// TODO: add construction code here

	LPLOGPALETTE pLogPal;
	pLogPal = (LPLOGPALETTE)malloc(sizeof(LOGPALETTE)+
		sizeof(PALETTEENTRY)* 256);
	pLogPal->palVersion = 0x300;
	pLogPal->palNumEntries = 256;
	for (int i = 0; i < 256; i++)
	{
		pLogPal->palPalEntry[i].peRed = i; //��ʼ��Ϊ��ɫ
		pLogPal->palPalEntry[i].peGreen = 0;
		pLogPal->palPalEntry[i].peBlue = 0;
		pLogPal->palPalEntry[i].peFlags = 0;
	}
	if (!m_Palette.CreatePalette(pLogPal))
		AfxMessageBox("Can't create palette!");
}

void CTestPalView::OnDraw(CDC* pDC)
{
	CTestPalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here

	CBrush brush, *pOldBrush;
	int x, y, i;

	pDC->SelectPalette(&m_Palette, FALSE);
	pDC->RealizePalette();
	pDC->SelectStockObject(BLACK_PEN);
	for (i = 0; i < 256; i++)
	{
		x = (i % 16) * 16;
		y = (i / 16) * 16;
		brush.CreateSolidBrush(PALETTEINDEX(i)); //��ɫ����������
		pOldBrush = pDC->SelectObject(&brush);
		pDC->Rectangle(x, y, x + 16, y + 16);
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
	}
	for (i = 0; i < 256; i++)
	{
		x = (i % 16) * 16 + 300;
		y = (i / 16) * 16;
		brush.CreateSolidBrush(RGB(i, 0, 0)); //RGB����
		pOldBrush = pDC->SelectObject(&brush);
		pDC->Rectangle(x, y, x + 16, y + 16);
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
	}
}


LRESULT CTestPalView::OnDoRealize(WPARAM wParam, LPARAM)
{
	CClientDC dc(this);
	dc.SelectPalette(&m_Palette, FALSE);
	if (dc.RealizePalette()) //����ɫ��ӳ�䱻�ı���ˢ����ͼ
		GetDocument()->UpdateAllViews(NULL);
	return 0L;
}
*/