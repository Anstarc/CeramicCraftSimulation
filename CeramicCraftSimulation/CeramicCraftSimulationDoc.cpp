
// CeramicCraftSimulationDoc.cpp : CCeramicCraftSimulationDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CeramicCraftSimulation.h"
#endif

#include "CeramicCraftSimulationDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCeramicCraftSimulationDoc

IMPLEMENT_DYNCREATE(CCeramicCraftSimulationDoc, CDocument)

BEGIN_MESSAGE_MAP(CCeramicCraftSimulationDoc, CDocument)
	ON_COMMAND(ID_IMPORT, OnImport)
END_MESSAGE_MAP()


// CCeramicCraftSimulationDoc 构造/析构

CCeramicCraftSimulationDoc::CCeramicCraftSimulationDoc()
{
	// TODO:  在此添加一次性构造代码
	m_pmesh = new Mesh3D;
}

CCeramicCraftSimulationDoc::~CCeramicCraftSimulationDoc()
{
	if (m_pmesh) {
		delete m_pmesh;
		m_pmesh = NULL;
	}
}

BOOL CCeramicCraftSimulationDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	InitMesh();

	return TRUE;
	
}




// CCeramicCraftSimulationDoc 序列化

void CCeramicCraftSimulationDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
	}
	else
	{
		// TODO:  在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CCeramicCraftSimulationDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CCeramicCraftSimulationDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CCeramicCraftSimulationDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCeramicCraftSimulationDoc 诊断

#ifdef _DEBUG
void CCeramicCraftSimulationDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCeramicCraftSimulationDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCeramicCraftSimulationDoc 命令
void CCeramicCraftSimulationDoc::OnImport()
{
	// TODO:  在此添加命令处理程序代码
	CString lpszFilter = _T("Obj files (*.obj)|*.obj|Off files (*.off)|*.off||");
	CFileDialog dlg(true, NULL, NULL, OFN_READONLY, lpszFilter);
	dlg.m_ofn.lpstrTitle = _T("Import 3D model");		////
	dlg.m_ofn.lpstrDefExt = _T("obj");

	if (dlg.DoModal() == IDOK)
	{
		CString		strFile = dlg.GetPathName();

		//	delete  m_pmesh, m_pmesh = NULL;
		if (m_pmesh == NULL) {
			m_pmesh = new Mesh3D;
		}

		CString extension = strFile;
		extension = extension.Right(extension.GetLength() - extension.ReverseFind('.'));
		extension.MakeLower();

		if (extension == ".off")
		{
			CStringA   ss(strFile);
			m_pmesh->load_off((LPCSTR)(ss));
		}
		else if (extension == ".obj")
		{
			//const char * ss = CString2constchar(strFile);
			CStringA  ss(strFile);
			m_pmesh->load_obj((LPCSTR)(ss));
		}

		m_pmesh->update_mesh();

	}

	UpdateAllViews(NULL);

}

void CCeramicCraftSimulationDoc::InitMesh()
{
	if (m_pmesh == NULL) {
		m_pmesh = new Mesh3D;
	}

	GetCurrentDirectory(sizeof(buf), (LPWSTR)buf);
	CStringA  ss((LPWSTR)buf);
	ss += "\\Cylinder.obj";
	//if (!m_pmesh->load_obj((LPCSTR)(ss)))
	m_pmesh->load_obj((LPCSTR)(ss));

}
