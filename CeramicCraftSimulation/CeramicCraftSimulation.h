
// CeramicCraftSimulation.h : CeramicCraftSimulation Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CCeramicCraftSimulationApp:
// �йش����ʵ�֣������ CeramicCraftSimulation.cpp
//

class CCeramicCraftSimulationApp : public CWinApp
{
public:
	CCeramicCraftSimulationApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCeramicCraftSimulationApp theApp;
