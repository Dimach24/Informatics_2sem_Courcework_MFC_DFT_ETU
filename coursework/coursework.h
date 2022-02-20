
// coursework.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CcourseworkApp:
// Сведения о реализации этого класса: coursework.cpp
//

class CcourseworkApp : public CWinApp
{
public:
	CcourseworkApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CcourseworkApp theApp;
