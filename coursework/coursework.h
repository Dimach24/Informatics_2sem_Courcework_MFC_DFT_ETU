//
// coursework.h
//

#pragma once

#ifndef __AFXWIN_H__
#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// including interface markup


/// <summary>
/// Class that defines the application - child of CWinApp
/// </summary>
class CcourseworkApp : public CWinApp
{
public:
	/// <summary>
	/// Constructor
	/// </summary>
	CcourseworkApp();
public:
	/// <summary>
	/// Initialization
	/// </summary>
	virtual BOOL InitInstance();


	/// <summary>
	/// message processing loop
	/// </summary>
	DECLARE_MESSAGE_MAP()
};
/// <summary>
/// the single instance of the class,
/// it represents the app
/// </summary>
extern CcourseworkApp theApp;
