
// CeramicCraftSimulationView.h : CCeramicCraftSimulationView ��Ľӿ�
//

#pragma once


class CCeramicCraftSimulationView : public CView
{
protected: // �������л�����
	CCeramicCraftSimulationView();
	DECLARE_DYNCREATE(CCeramicCraftSimulationView)

// ����
public:
	CCeramicCraftSimulationDoc* GetDocument() const;
	int m_GLPixelIndex;
	HGLRC m_hGLContext;
	GLfloat rtri;
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];

	double winX, winY, object_x, object_y, object_z;
	float winZ;
	float moveLength;
	bool reshape;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CCeramicCraftSimulationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	bool SetWindowPixelFormate(HDC hDC);
	bool CreateViewGLContext(HDC hDC);
	bool InitGL();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void OnReshape();
};

#ifndef _DEBUG  // CeramicCraftSimulationView.cpp �еĵ��԰汾
inline CCeramicCraftSimulationDoc* CCeramicCraftSimulationView::GetDocument() const
   { return reinterpret_cast<CCeramicCraftSimulationDoc*>(m_pDocument); }
#endif

