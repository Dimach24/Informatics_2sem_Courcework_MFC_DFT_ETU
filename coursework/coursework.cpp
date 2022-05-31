//
// coursework.cpp
//

// including project files
#include "pch.h"
#include "framework.h"
#include "coursework.h"
#include "courseworkDlg.h"

// definitions for the debug mode
#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// start message processing loop for the app
BEGIN_MESSAGE_MAP(CcourseworkApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()
// end message processing loop


CcourseworkApp::CcourseworkApp() {
	// restart manager supporting
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}



// the single instance of the application class
// it represents the app
CcourseworkApp theApp;


BOOL CcourseworkApp::InitInstance() {
	// data for dynamic lib of control elements connection
	INITCOMMONCONTROLSEX InitCtrls;
	// initialization of this data
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	// ensure that the lib is connected
	InitCommonControlsEx(&InitCtrls);

	// calling InitInstance of the base class
	CWinApp::InitInstance();


	// creating shell manager
	CShellManager* pShellManager = new CShellManager;

	// Активация визуального диспетчера "Классический Windows" для включения элементов управления MFC
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// setting the win registry key for application data
	SetRegistryKey(_T("SPbETU Chaminov Dmeatry 1183"));

	// creating main dlg
	CcourseworkDlg dlg;
	// setting dlg as main dlg
	m_pMainWnd = &dlg;

	// waiting till the dlg is closed
	INT_PTR nResponse = dlg.DoModal();
	// response checking
	if (nResponse == -1) {
		TRACE(traceAppMsg, 0, "Предупреждение. Не удалось создать диалоговое окно, поэтому работа приложения неожиданно завершена.\n");
		TRACE(traceAppMsg, 0, "Предупреждение. При использовании элементов управления MFC для диалогового окна невозможно #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// safe deleting of the shell manager
	if (pShellManager != nullptr) {
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// close the app (as main dlg is closed)
	return FALSE;
}

