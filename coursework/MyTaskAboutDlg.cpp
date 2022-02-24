// MyTaskAboutDlg.cpp: файл реализации
//

#include "pch.h"
#include "coursework.h"
#include "MyTaskAboutDlg.h"
#include "afxdialogex.h"


// Диалоговое окно MyTaskAboutDlg

IMPLEMENT_DYNAMIC(MyTaskAboutDlg, CDialogEx)

MyTaskAboutDlg::MyTaskAboutDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MyTaskAboutDlg, pParent)
{

}


MyTaskAboutDlg::~MyTaskAboutDlg()
{
}


void MyTaskAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MyTaskAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Обработчики сообщений MyTaskAboutDlg
