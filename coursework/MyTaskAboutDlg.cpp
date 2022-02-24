// MyTaskAboutDlg.cpp: файл реализации
//

#include "pch.h"
#include "coursework.h"
#include "MyTaskAboutDlg.h"
#include "afxdialogex.h"


// Диалоговое окно MyTaskAboutDlg

IMPLEMENT_DYNAMIC(MyTaskAboutDlg, CDialogEx)

MyTaskAboutDlg::MyTaskAboutDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MyTaskAboutDlg, pParent),
	about_string(_T(R"({\b Hello} World!)"))
{
	//TaskAboutCtrl.SetTextMode(TM_RICHTEXT | TM_MULTICODEPAGE);
	//SendDlgItemMessage(IDC_TaskAbout, EM_SETTEXTMODE, TM_RICHTEXT | TM_MULTICODEPAGE, 0);
}


MyTaskAboutDlg::~MyTaskAboutDlg()
{
}


void MyTaskAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TaskAbout, about_string);
	DDX_Control(pDX, IDC_TaskAbout, TaskAboutCtrl);
}


BEGIN_MESSAGE_MAP(MyTaskAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Обработчики сообщений MyTaskAboutDlg
