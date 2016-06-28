
// CeramicCraftSimulationView.cpp : CCeramicCraftSimulationView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CeramicCraftSimulation.h"
#endif

#include "CeramicCraftSimulationDoc.h"
#include "CeramicCraftSimulationView.h"
#include "MainFrm.h"

#include "./Optimize/Optimize.h"
#include "./Optimize/OptimizationParameter.h"

#include <cstring>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCeramicCraftSimulationView

static UINT WM_CHANGESTEP = RegisterWindowMessage((LPCWSTR)"ChangeStep");


IMPLEMENT_DYNCREATE(CCeramicCraftSimulationView, CView)

BEGIN_MESSAGE_MAP(CCeramicCraftSimulationView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_COMMAND(ID_START, OnStart)
	ON_COMMAND(ID_STOP, OnStop)
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_REGISTERED_MESSAGE(WM_CHANGESTEP, OnChangeStep)
	ON_COMMAND(ID_DEMO1, &CCeramicCraftSimulationView::OnDemo1)
	ON_UPDATE_COMMAND_UI(ID_START, &CCeramicCraftSimulationView::OnUpdateStart)
	ON_UPDATE_COMMAND_UI(ID_STOP, &CCeramicCraftSimulationView::OnUpdateStop)
	ON_UPDATE_COMMAND_UI(ID_DEMO1, &CCeramicCraftSimulationView::OnUpdateDemo1)
	//ON_COMMAND(ID_LINE, &CCeramicCraftSimulationView::OnLine)
	//ON_UPDATE_COMMAND_UI(ID_LINE, &CCeramicCraftSimulationView::OnUpdateLine)
END_MESSAGE_MAP()

// CCeramicCraftSimulationView ����/����

CCeramicCraftSimulationView::CCeramicCraftSimulationView()
{
	// TODO:  �ڴ˴���ӹ������
	m_hGLContext = NULL;
	m_GLPixelIndex = 0;
	rtri = 0;
	line = false;
	//step = 1;
	reshape = false;
	start = false;

	x = (int *)malloc(7 * sizeof(int));
	y = (int *)malloc(7 * sizeof(int));
	x[0] = 0; x[1] = 0; x[2] = 4; x[3] = 7; x[4] = 12; x[5] = 8; x[6] = 14;
	y[0] = 18; y[1] = 2; y[2] = 4; y[3] = 0; y[4] = 0; y[5] = 6; y[6] = 7;
	demo = false;
	//const int x[7] = { 0, 0, 4, 8, 9, 8, 18 };
	//const int y[7] = { 18, 2, 14, 0, 0, 6, 7 };
}

CCeramicCraftSimulationView::~CCeramicCraftSimulationView()
{
}

BOOL CCeramicCraftSimulationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style |= (WS_CLIPCHILDREN | WS_CLIPCHILDREN);

	return CView::PreCreateWindow(cs);
}

// CCeramicCraftSimulationView ����

void CCeramicCraftSimulationView::OnDraw(CDC* /*pDC*/)
{
	CCeramicCraftSimulationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CCeramicCraftSimulationView ��ӡ

BOOL CCeramicCraftSimulationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CCeramicCraftSimulationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CCeramicCraftSimulationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CCeramicCraftSimulationView ���

#ifdef _DEBUG
void CCeramicCraftSimulationView::AssertValid() const
{
	CView::AssertValid();
}

void CCeramicCraftSimulationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCeramicCraftSimulationDoc* CCeramicCraftSimulationView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCeramicCraftSimulationDoc)));
	return (CCeramicCraftSimulationDoc*)m_pDocument;
}
#endif //_DEBUG


// CCeramicCraftSimulationView ��Ϣ�������


int CCeramicCraftSimulationView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetTimer(1, 100, NULL);

	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	HWND hWnd = this->GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);

	if (this->SetWindowPixelFormate(hDC) == FALSE)
	{//�������ظ�ʽ
		return 0;
	}
	if (this->CreateViewGLContext(hDC) == FALSE)
	{//����RC��ѡΪ����
		return 0;
	}
	if (!this->InitGL())
	{//��ʼ��openGL
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
	// TODO: �ڴ˴������Ϣ����������
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
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);//͸��ͶӰ
	glMatrixMode(GL_MODELVIEW);                            // Select The Modelview Matrix
	glLoadIdentity();                                    // Reset The Modelview Matrix
}


void CCeramicCraftSimulationView::OnPaint()
{
	CCeramicCraftSimulationDoc *pDoc = (CCeramicCraftSimulationDoc *)GetDocument();
	if (pDoc->m_pmesh == NULL)
		return;


	glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
	glLoadIdentity();                                    // Reset The Projection Matrix
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);//͸��ͶӰ
	glMatrixMode(GL_MODELVIEW);                            // Select The Modelview Matrix
	glLoadIdentity();


	CPaintDC dc(this); // device context for painting
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();
	glPushMatrix();

	glTranslatef(0.0f, -7.0f, -26.0f);
	glRotatef(rtri, 0.0f, 1.0f, 0.0f);

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	//if (line)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		pDoc->m_pmesh->gl_draw(true);
	}


	glEnable(GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor4f(0.725f, 0.627f, 0.510f, 1.0f);
	pDoc->m_pmesh->gl_draw(true);
	glDisable(GL_LIGHTING);

	glPopMatrix();
	if (demo)
		DrawCursor();

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

	return TRUE;
}


bool CCeramicCraftSimulationView::InitGL()
{
	glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
	glClearColor(0.0, 0.0, 0.0, 0.0);// Black Background
	glClearDepth(1.0f);                                    // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
	glDepthFunc(GL_LESS);                                // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);    // Really Nice Perspective Calculations

	GLfloat sun_light_position[] = { 1.0f, 1.0f, 1.0f };
	GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat sun_light_diffuse[] = { 0.725f, 0.627f, 0.510f, 0.6f };
	GLfloat sun_light_specular[] = { 0.725f, 0.627f, 0.510f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position); //ָ����0�Ź�Դ��λ��   
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient); //GL_AMBIENT��ʾ���ֹ������䵽�ò����ϣ�  
	//�����ܶ�η�������������ڻ����еĹ���ǿ�ȣ���ɫ��  
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse); //�������~~  
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);//���淴���~~~  

	glEnable(GL_LIGHT0); //ʹ�õ�0�Ź���  
	//glEnable(GL_LIGHTING); //�ں������Ⱦ��ʹ�ù���  


	return TRUE;                                        // Initialization Went OK
}

void CCeramicCraftSimulationView::OnStart()
{
	start = true;
}
void CCeramicCraftSimulationView::OnStop()
{
	start = false;
	rtri = 0;
}


void CCeramicCraftSimulationView::OnTimer(UINT_PTR nIDEvent)
{
	CPoint point;
	GetCursorPos(&point);
	CMainFrame* cmf = (CMainFrame*)AfxGetMainWnd();
	if (!cmf)
		TRACE("!cmf\n");
	CString cs = CString("x=");
	char cs2[10];
	itoa(point.x, cs2, 10);
	cs += CString(cs2);
	cs += CString(" y=");
	itoa(point.y, cs2, 10);
	cs += CString(cs2);

	LPCTSTR lpctstr = cs.GetString();
	cmf->UpdateMessageText(lpctstr);


	if (start&&nIDEvent==1)
	{
		step = cmf->m_slider.GetPos() / 10.0 * 12;
		rtri += step;
		if (reshape)
			OnReshape();
		OnPaint();
	}
	CView::OnTimer(nIDEvent);
}



LRESULT CCeramicCraftSimulationView::OnChangeStep(WPARAM wParam, LPARAM lParam)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	step = lParam / 10.0 * 12;
	//TRACE("�յ���Ϣ");

	return 0;
}



void CCeramicCraftSimulationView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	reshape = true;

	glLoadIdentity();
	glTranslatef(0.0f, -7.0f, -26.0f);
	glRotatef(rtri, 0.0f, 1.0f, 0.0f);


	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);
	TRACE("view:%d\n", (int)viewport[3]);

	if (!demo)
	{
		winX = point.x;
		winY = viewport[3] - point.y;
	}
	else
	{
		winX = cursorPoint.x;
		winY = viewport[3] - cursorPoint.y;
	}
	TRACE("%d %d\n", (int)winX, (int)winY);
	glReadBuffer(GL_BACK);
	glReadPixels((int)winX, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, (double)winZ, modelview, projection, viewport, &object_x, &object_y, &object_z);
	
	TRACE("%lf ,%lf %lf\n", object_x, object_y, object_z);

	firstVertA = rtri;
	currentVertA = 0;
	CCeramicCraftSimulationDoc *pDoc = (CCeramicCraftSimulationDoc *)GetDocument();
	if (!pDoc)
		return;
	currentVert = pDoc->m_pmesh->NearestVert(object_x, object_y, object_z);
	TRACE("%f %f %f\n", currentVert->x, currentVert->y, currentVert->z);

	//firstVert = currentVert;
	//firstMoveLength = 0;

	CView::OnLButtonDown(nFlags, point);
}


void CCeramicCraftSimulationView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	reshape = false;
	CView::OnLButtonUp(nFlags, point);
}


void CCeramicCraftSimulationView::OnReshape()
{
	if (!demo)
	{
		CPoint point;
		GetCursorPos(&point);
		moveLength = point.x - winX;

	}
	else
		moveLength = cursorPoint.x - winX;


	if (moveLength < -490)
		moveLength = -490;


	CCeramicCraftSimulationDoc *pDoc = (CCeramicCraftSimulationDoc *)GetDocument();
	if (!pDoc)
		return;

	if (rtri - firstVertA >= 12)
	{
		firstVertA += 12;
		currentVertA += 12;
		currentVert = pDoc->m_pmesh->LeftVert(currentVert);
	}
	//TRACE("%f %f\n", firstVertA, currentVertA);
	if (!currentVert)
		TRACE("!currentVert\n");

	if (currentVertA >= 360)
	{
		reshape = false;
		return;
	}

	//TRACE("%f %f %f\n", currentVert->x, currentVert->y, currentVert->z);
	TRACE("��ά����:%f %f %f\n",currentVert->x, currentVert->y, currentVert->z);
	pDoc->m_pmesh->Reshape(currentVert, moveLength / 100);

	//OnOptimize(pDoc->m_pmesh);
}


void CCeramicCraftSimulationView::OnOptimize(Mesh3D* m_pmesh)
{
	OptimizeParameter *opp = new OptimizeParameter(m_pmesh);
	MeshOptimization::opp = opp;
	MeshOptimization::Init();
	delete opp;

}


void CCeramicCraftSimulationView::OnDemo1()
{
	// TODO:  �ڴ���������������
	CWinThread* pThread = NULL;
	demo = true;
	CreateThread(&pThread);
	StartThread(pThread);
}


void CCeramicCraftSimulationView::CreateThread(CWinThread** pThread)
{
	*pThread = ::AfxBeginThread(ThreadFun, (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
}

void CCeramicCraftSimulationView::StartThread(CWinThread* pThread)
{
	pThread->ResumeThread();
}



void CCeramicCraftSimulationView::OnUpdateStart(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	pCmdUI->Enable(!start);
}

void CCeramicCraftSimulationView::OnUpdateStop(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	pCmdUI->Enable(start);
}

void CCeramicCraftSimulationView::OnUpdateDemo1(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	pCmdUI->Enable(!demo);
}



UINT CCeramicCraftSimulationView::ThreadFun(LPVOID pParam){ //�߳�Ҫ���õĺ���

	CCeramicCraftSimulationView* cccv = (CCeramicCraftSimulationView*)pParam;

	cccv->start = true;

	GetCursorPos(&cccv->cursorPoint);
	cccv->cursorPoint.x = (int)(1080.0 / 1912.0 * cccv->width);
	cccv->cursorPoint.y = (int)(650.0 / 950.0 * cccv->height);
	Sleep(500);

	cccv->OnLButtonDown(0, cccv->cursorPoint);
	cccv->reshape = true;
	cccv->cursorPoint.x = (int)(1250.0 / 1912.0 * cccv->width);
	cccv->cursorPoint.y = (int)(650.0 / 950.0 * cccv->height);

	//cccv->SuspendThread()
	Sleep(3200);
	cccv->OnLButtonUp(0, cccv->cursorPoint);

	cccv->demo = false;
	return 0;
}



void CCeramicCraftSimulationView::DrawCursor()
{
	glLoadIdentity();
	glTranslatef(0.0f, -7.0f, -26.0f);
	//glRotatef(rtri, 0.0f, 1.0f, 0.0f);


	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);
	TRACE("view:%d\n", (int)viewport[3]);

	double winX, winY, winZ, object_x, object_y, object_z;
	winX = cursorPoint.x;
	winY = viewport[3] - cursorPoint.y;
	
	TRACE("%d %d\n", (int)winX, (int)winY);
	glReadBuffer(GL_BACK);
	glReadPixels((int)winX, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, (double)winZ, modelview, projection, viewport, &object_x, &object_y, &object_z);
	TRACE("����ָ�룺%lf ,%lf %lf\n", object_x, object_y, object_z);

	//glOrtho(-1.0f*width / 2, 1.0f*width / 2, -1.0f*height / 2, 1.0f*height / 2, -1.0f, 100.0f);
	//glTranslatef(-cursorPoint.x/2.0f, -(viewport[3]-cursorPoint.y) / 2.0f, 0.0f);
	glTranslatef(0.1f, 0.2f, -2.0f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x[2] / 200.0f + object_x, y[2] / 200.0f + object_y, object_z - 1);
	//TRACE("%d %d\n",x[2], width); 
	//TRACE("%f %f\n", 2.0f * x[2] / width, 2 * (float)y[2] / height);
	glVertex3f(x[3] / 200.0f + object_x, y[3] / 200.0f + object_y, object_z - 1);
	glVertex3f(x[4] / 200.0f + object_x, y[4] / 200.0f + object_y, object_z - 1);
	glVertex3f(x[5] / 200.0f + object_x, y[5] / 200.0f + object_y, object_z - 1);
	glVertex3f(x[0] / 200.0f + object_x, y[0] / 200.0f + object_y, object_z - 1);
	glVertex3f(x[1] / 200.0f + object_x, y[1] / 200.0f + object_y, object_z - 1);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(x[0] / 200.0f + object_x, y[0] / 200.0f + object_y, object_z - 1);
	glVertex3f(x[5] / 200.0f + object_x, y[5] / 200.0f + object_y, object_z - 1);
	glVertex3f(x[6] / 200.0f + object_x, y[6] / 200.0f + object_y, object_z - 1);
	glEnd();

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 7; i++)
	{
		glVertex3f(x[i] / 200.0f + object_x, y[i] / 200.0f + object_y, object_z - 1);
	}
	glEnd();

	//TRACE("������꣺%d %d\n", cursorPoint.x, cursorPoint.y);

}



//void CCeramicCraftSimulationView::OnLine()
//{
//	// TODO:  �ڴ���������������
//	line = !line;
//}


//void CCeramicCraftSimulationView::OnUpdateLine(CCmdUI *pCmdUI)
//{
//	// TODO:  �ڴ������������û����洦��������
//	pCmdUI->Enable(!line);
//}
