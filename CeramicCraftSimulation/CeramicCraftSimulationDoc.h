
// CeramicCraftSimulationDoc.h : CCeramicCraftSimulationDoc ��Ľӿ�
//


#pragma once
#include "Mesh3D.h"


class CCeramicCraftSimulationDoc : public CDocument
{
protected: // �������л�����
	CCeramicCraftSimulationDoc();
	DECLARE_DYNCREATE(CCeramicCraftSimulationDoc)

// ����
public:
	Mesh3D* m_pmesh;
	char buf[100];
// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CCeramicCraftSimulationDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnImport();

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	void InitMesh();
};
