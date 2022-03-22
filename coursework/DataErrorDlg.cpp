// DataErrorDlg.cpp: файл реализации
//

#include "pch.h"
#include "coursework.h"
#include "DataErrorDlg.h"
#include "afxdialogex.h"


// Диалоговое окно DataErrorDlg

IMPLEMENT_DYNAMIC(DataErrorDlg, CDialogEx)

DataErrorDlg::DataErrorDlg(CWnd* pParent /*=nullptr*/)
{

}

DataErrorDlg::~DataErrorDlg()
{
}

BOOL DataErrorDlg::OnInitDialog()
{
	GetDlgItem(IDCANCEL)->SetWindowTextW(_T("Вернуться"));
	return 0;
}

void DataErrorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DataErrorDlg, CDialogEx)
END_MESSAGE_MAP()


// Обработчики сообщений DataErrorDlg
