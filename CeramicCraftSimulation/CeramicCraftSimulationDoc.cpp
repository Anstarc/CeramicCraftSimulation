
// CeramicCraftSimulationDoc.cpp : CCeramicCraftSimulationDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CCeramicCraftSimulationDoc ����/����

CCeramicCraftSimulationDoc::CCeramicCraftSimulationDoc()
{
	// TODO:  �ڴ����һ���Թ������
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

	// TODO:  �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	InitMesh();

	return TRUE;
	
}




// CCeramicCraftSimulationDoc ���л�

void CCeramicCraftSimulationDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  �ڴ���Ӵ洢����
	}
	else
	{
		// TODO:  �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CCeramicCraftSimulationDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CCeramicCraftSimulationDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CCeramicCraftSimulationDoc ���

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


// CCeramicCraftSimulationDoc ����
void CCeramicCraftSimulationDoc::OnImport()
{
	// TODO:  �ڴ���������������
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
