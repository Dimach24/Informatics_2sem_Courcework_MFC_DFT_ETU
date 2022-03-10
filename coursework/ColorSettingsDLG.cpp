// ColorSettingsDLG.cpp: файл реализации
//

#include "pch.h"
#include "coursework.h"
#include "ColorSettingsDLG.h"
#include "afxdialogex.h"


// Диалоговое окно ColorSettingsDLG

IMPLEMENT_DYNAMIC(ColorSettingsDLG, CDialogEx)

ColorSettingsDLG::ColorSettingsDLG(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ColorSettingsDLG, pParent)
{

}

ColorSettingsDLG::~ColorSettingsDLG()
{
}

void ColorSettingsDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ColorSettingsDLG, CDialogEx)
END_MESSAGE_MAP()


// Обработчики сообщений ColorSettingsDLG
