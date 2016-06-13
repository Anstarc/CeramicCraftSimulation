
// CeramicCraftSimulationView.cpp : CCeramicCraftSimulationView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CeramicCraftSimulation.h"
#endif

#include "CeramicCraftSimulationDoc.h"
#include "CeramicCraftSimulationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCeramicCraftSimulationView

IMPLEMENT_DYNCREATE(CCeramicCraftSimulationView, CView)

BEGIN_MESSAGE_MAP(CCeramicCraftSimulationView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CCeramicCraftSimulationView 构造/析构

CCeramicCraftSimulationView::CCeramicCraftSimulationView()
{
	// TODO:  在此处添加构造代码
	m_hGLContext = NULL;
	m_GLPixelIndex = 0;
}

CCeramicCraftSimulationView::~CCeramicCraftSimulationView()
{
}

BOOL CCeramicCraftSimulationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.style |= (WS_CLIPCHILDREN | WS_CLIPCHILDREN);

	return CView::PreCreateWindow(cs);
}

// CCeramicCraftSimulationView 绘制

void CCeramicCraftSimulationView::OnDraw(CDC* /*pDC*/)
{
	CCeramicCraftSimulationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CCeramicCraftSimulationView 打印

BOOL CCeramicCraftSimulationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCeramicCraftSimulationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CCeramicCraftSimulationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CCeramicCraftSimulationView 诊断

#ifdef _DEBUG
void CCeramicCraftSimulationView::AssertValid() const
{
	CView::AssertValid();
}

void CCeramicCraftSimulationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCeramicCraftSimulationDoc* CCeramicCraftSimulationView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCeramicCraftSimulationDoc)));
	return (CCeramicCraftSimulationDoc*)m_pDocument;
}
#endif //_DEBUG


// CCeramicCraftSimulationView 消息处理程序


int CCeramicCraftSimulationView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	HWND hWnd = this->GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);

	if (this->SetWindowPixelFormate(hDC) == FALSE)
	{//设置像素格式
		return 0;
	}
	if (this->CreateViewGLContext(hDC) == FALSE)
	{//创建RC并选为所用
		return 0;
	}
	if (!this->InitGL())
	{//初始化openGL
		return 0;
	}
	return 0;

}


void CCeramicCraftSimulationView::OnDestroy()
{
	CView::OnDestroy();
	if (wglGetCurrentContext() != NULL)
		wglMakeCurrent(NULL, NULL);

	if (m_hGLContext != NULL)
	{
		wglDeleteContext(m_hGLContext);
		m_hGLContext = NULL;
	}
}


void CCeramicCraftSimulationView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	GLsizei width, height;
	width = cx;
	height = cy;
	if (height == 0)                                        // Prevent A Divide By Zero By
	{
		height = 1;                                        // Making Height Equal One
	}

	glViewport(0, 0, width, height);                        // Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
	glLoadIdentity();                                    // Reset The Projection Matrix
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);//透视投影
	glMatrixMode(GL_MODELVIEW);                            // Select The Modelview Matrix
	glLoadIdentity();                                    // Reset The Modelview Matrix
}


void CCeramicCraftSimulationView::OnPaint()
{
	CCeramicCraftSimulationDoc *pDoc = (CCeramicCraftSimulationDoc *)GetDocument();
	if (pDoc->m_pmesh == NULL)
		return;

	GLfloat rtri = 0;
	CPaintDC dc(this); // device context for painting
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glTranslatef(0.0f, -7.0f, -26.0f);						// Move Left 1.5 Units And Into The Screen 6.0
	glRotatef(rtri, 0.0f, 1.0f, 0.0f);						// Rotate The Triangle On The Y axis ( NEW )

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	pDoc->m_pmesh->gl_draw(true);									// Done Drawing The Pyramid


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor4f(0.75f, 0.65f, 0.15f, 1.0f);
	pDoc->m_pmesh->gl_draw(true);	                              // 正方形绘制结束
	glFlush();
	SwapBuffers(dc.m_hDC);
}


bool CCeramicCraftSimulationView::SetWindowPixelFormate(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;

	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;

	pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER | PFD_STEREO_DONTCARE;

	pixelDesc.iPixelType = PFD_TYPE_RGBA;
	pixelDesc.cColorBits = 32;
	pixelDesc.cRedBits = 8;
	pixelDesc.cRedShift = 16;
	pixelDesc.cGreenBits = 8;
	pixelDesc.cGreenShift = 8;
	pixelDesc.cBlueBits = 8;
	pixelDesc.cBlueShift = 0;
	pixelDesc.cAlphaBits = 0;
	pixelDesc.cAlphaShift = 0;
	pixelDesc.cAccumBits = 64;
	pixelDesc.cAccumRedBits = 16;
	pixelDesc.cAccumGreenBits = 16;
	pixelDesc.cAccumBlueBits = 16;
	pixelDesc.cAccumAlphaBits = 0;
	pixelDesc.cDepthBits = 32;
	pixelDesc.cStencilBits = 8;
	pixelDesc.cAuxBuffers = 0;
	pixelDesc.iLayerType = PFD_MAIN_PLANE;
	pixelDesc.bReserved = 0;
	pixelDesc.dwLayerMask = 0;
	pixelDesc.dwVisibleMask = 0;
	pixelDesc.dwDamageMask = 0;

	m_GLPixelIndex = ChoosePixelFormat(hDC, &pixelDesc);
	if (m_GLPixelIndex == 0) // Choose default
	{
		m_GLPixelIndex = 1;
		if (DescribePixelFormat(hDC, m_GLPixelIndex,
			sizeof(PIXELFORMATDESCRIPTOR), &pixelDesc) == 0)
			return FALSE;
	}

	if (!SetPixelFormat(hDC, m_GLPixelIndex, &pixelDesc))
		return FALSE;

	return TRUE;
}


bool CCeramicCraftSimulationView::CreateViewGLContext(HDC hDC)
{
	m_hGLContext = wglCreateContext(hDC);

	if (m_hGLContext == NULL)
		return FALSE;

	if (wglMakeCurrent(hDC, m_hGLContext) == FALSE)
		return FALSE;

	//g_FontListID = CreateOpenGLFont(_T("Arial"), FONT_HEIGHT);

	return TRUE;
}


bool CCeramicCraftSimulationView::InitGL()
{
	glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
	glClearColor(0.0, 0.0, 0.0, 0.0);// Black Background
	glClearDepth(1.0f);                                    // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);                                // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);    // Really Nice Perspective Calculations
	return TRUE;                                        // Initialization Went OK
}

