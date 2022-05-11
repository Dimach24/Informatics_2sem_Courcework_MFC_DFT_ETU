// including project  files 

#include "pch.h"
#include "framework.h"
#include "coursework.h"
#include "courseworkDlg.h"
#include "afxdialogex.h"

#include "Calculator.h"
#include "SomeDefinitions.h"

// definitions for the debug mode
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//=====================CAboutDlg class===========================
/// <summary>
/// Class that defines dlg "about app"
/// </summary>
class CAboutDlg : public CDialogEx
{
public:
	/// <summary>
	/// Constructor
	/// </summary>
	CAboutDlg();

	/// <summary>
	/// Defines on dlg initialization behaviour
	/// </summary>
	BOOL OnInitDialog();

	// dialog id for building
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

protected:
	/// message processing loop
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX) { // call constructor of the base class
}

BOOL CAboutDlg::OnInitDialog() {
	// set the title, commit index - the index of 
	// the last git commit (defined in 'SomeDefinitions.h')
	SetWindowText(_T("О программе. Номер последние изменения: " __COURSE_LAST_COMMIT_INDEX));
	return 0;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX); // use base data exchange
}

// message loop
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

//===============================================================

CcourseworkDlg::CcourseworkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COURSEWORK_DIALOG, pParent) //base constructor
	, theTask(	//task text init
		L"Для сигнала заданного вида вычислить дискретное "
		L"преобразование Фурье(ДПФ), нарисовать график сигнальной "
		L"функции и график модуля  ее ДПФ, предоставить возможность "
		L"изменять масштаб графика по Х и по У, выбор линейного или "
		L"логарифмического масштаба по У для графика ДПФ, интерактивный "
		L"режим изменения параметров сигнала, запись в файл графиков "
		L"сигнала и ДПФ в формате BMP."
	) {
	// set icon
	m_hIcon = AfxGetApp()->LoadIcon(ID_LOGO_ICO);
}

void CcourseworkDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);				// base data exchange
	DDX_Text(pDX, IDC_STATIC_TASK, theTask);	// data exchange between CStatic and CString
}

// message processing loop
BEGIN_MESSAGE_MAP(CcourseworkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CcourseworkDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_Task_About_Bn, &CcourseworkDlg::OnBnClickedTaskAboutBn)
	ON_BN_CLICKED(IDC_CALCULATE_BUTTON, &CcourseworkDlg::OnBnClickedCalculateButton)
END_MESSAGE_MAP()


// Обработчики сообщений CcourseworkDlg

BOOL CcourseworkDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();	// base OnInit
	// set title
	SetWindowText(_T("Курсовая - Чаминов Д. А. гр. 1183 " __COURSE__VERSION));

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	// adding "About" to the system menu
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr) {
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// set icon (32x32 - big icon)
	SetIcon(m_hIcon, TRUE);
	return TRUE;
}

// catching system menu commands
void CcourseworkDlg::OnSysCommand(UINT nID, LPARAM lParam) {
	if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
		// create and show about dlg
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	} else {
		// base action
		CDialogEx::OnSysCommand(nID, lParam);
	}
}


// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CcourseworkDlg::OnQueryDragIcon() {
	return static_cast<HCURSOR>(m_hIcon);
}


// on button 'ok' clicked message
void CcourseworkDlg::OnBnClickedOk() {
	CDialogEx::OnOK();	// base action
}

// on button 'about the task' clicked message
void CcourseworkDlg::OnBnClickedTaskAboutBn() {
	// create and show messagebox with theoretical information
	AfxMessageBox(
		L"Дискретное преобразование Фурье является линейным преобразованием, "
		L"которое переводит 𝖭-мерный комплексный вектор временных отсчётов 𝘅 в 𝖭-мерный "
		L"комплексный вектор спектральных (частотных) отсчётов 𝗫 той же длины. Таким "
		L"образом преобразование может быть реализовано как умножение квадратной матрицы "
		L"на вектор 𝗫=𝖠*𝘅 , где матрица 𝖠 – некая унитарная матрица, которую можно рассматривать "
		L"как матрицу преобразования (поворота) системы координат некоторого 𝖭-мерного пространства.\n"
		L"Формула преобразования для 𝗄-того компонента ДПФ:\n"
		L"𝖷𝗄=Σ𝗑𝗇*𝖾𝗑𝗉(-2π𝗂𝗄𝗇/𝖭)\n"
		L"Эту формулу можно преобразовать с помощью формулы Эйлера.\n "
		L"Квадрат модуля отсчета равен |𝖷𝗄|²=𝖱𝖾²(𝖷𝗄)+𝖨𝗆²(𝖷𝗄)", MB_OK | MB_ICONINFORMATION);
}

// button 'calculate' has been clicked action
void CcourseworkDlg::OnBnClickedCalculateButton() {
	// create and show calculator dlg
	Calculator dlg;
	dlg.DoModal();
}
