
// CeramicCraftSimulationView.h : CCeramicCraftSimulationView 类的接口
//

#pragma once


class CCeramicCraftSimulationView : public CView
{
protected: // 仅从序列化创建
	CCeramicCraftSimulationView();
	DECLARE_DYNCREATE(CCeramicCraftSimulationView)

// 特性
public:
	CCeramicCraftSimulationDoc* GetDocument() const;
	int m_GLPixelIndex;
	HGLRC m_hGLContext;
// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CCeramicCraftSimulationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	bool SetWindowPixelFormate(HDC hDC);
	bool CreateViewGLContext(HDC hDC);
	bool InitGL();
};

#ifndef _DEBUG  // CeramicCraftSimulationView.cpp 中的调试版本
inline CCeramicCraftSimulationDoc* CCeramicCraftSimulationView::GetDocument() const
   { return reinterpret_cast<CCeramicCraftSimulationDoc*>(m_pDocument); }
#endif

