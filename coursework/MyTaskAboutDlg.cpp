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

BOOL MyTaskAboutDlg::OnInitDialog()
{
	SetWindowText(_T("О задании"));
	CWnd* p=GetDlgItem(IDC_TaskAbout);
	if (p) {
		p->SetWindowText(
			L"Дискретное преобразование Фурье является линейным преобразованием, \
которое переводит 𝖭-мерный комплексный вектор временных отсчётов 𝘅 в 𝖭-мерный \
комплексный вектор спектральных (частотных) отсчётов 𝗫 той же длины. Таким \
образом преобразование может быть реализовано как умножение квадратной матрицы \
на вектор 𝗫=𝖠*𝘅 , где матрица 𝖠 – некая унитарная матрица, которую можно рассматривать \
как матрицу преобразования (поворота) системы координат некоторого 𝖭-мерного пространства.\n\
Формула преобразования для 𝗄-того компонента ДПФ:\n\
𝖷𝗄=Σ𝗑𝗇*𝖾𝗑𝗉(-2π𝗂𝗄𝗇/𝖭)\n\
Эту формулу можно преобразовать с помощью формулы Эйлера.\n \
Квадрат модуля отсчета равен |𝖷𝗄|²=𝖱𝖾²(𝖷𝗄)+𝖨𝗆²(𝖷𝗄)"); ;
	}
	return 0;
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
