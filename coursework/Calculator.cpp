// Calculator.cpp: файл реализации
//
#include <cmath>
#include "pch.h"
#include "coursework.h"
#include "Calculator.h"
#include "afxdialogex.h"
#include "DataErrorDlg.h"

// Диалоговое окно Calculator

IMPLEMENT_DYNAMIC(Calculator, CDialogEx)

Calculator::Calculator(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Calculator, pParent),
	signal(),
	dft(nullptr)
{
	dft.set_signal(&signal);
}

Calculator::~Calculator()
{
}

BOOL Calculator::OnInitDialog()
{
	Cgraph.SubclassDlgItem(IDC_STATIC_graph, this);
	axes_cp.SubclassDlgItem(IDC_MFCCOLORBUTTON_AXES, this);
	bg_cp.SubclassDlgItem(IDC_MFCCOLORBUTTON_BG, this);
	signal_cp.SubclassDlgItem(IDC_MFCCOLORBUTTON_SIGNAL, this);
	dft_cp.SubclassDlgItem(IDC_MFCCOLORBUTTON_DCF, this);
	slider_step.SubclassDlgItem(IDC_SLIDER_STEP, this);
	cb_is_log.SubclassDlgItem(IDC_CHECK_is_log_scale, this);

	slider_step.SetRangeMin(1);
	slider_step.SetRangeMax(10);
	slider_step.SetPos(3);

	CWnd* p = GetDlgItem(IDC_STATIC_signal);
	if (p) { p->SetWindowTextW(_T("x(t) = a*sin(2\u03c0(f + mt)*t")); }
	p = nullptr;
	p = GetDlgItem(IDC_EDIT_param_a);
	if (p) { p->SetFocus(); }

	ResetInputData();
	ResetColorPickers();

	signal.set_definition_scope(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
	Cgraph.functions.push_back(&signal);
	
	dft.set_definition_scope(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
	Cgraph.functions.push_back(&dft);


	return 0;
}
#define MY_PARAM_HELPER(P,ID,NAME)\
	P=GetDlgItem(ID);\
	assert(P);\
	CStringW NAME##_s;\
	P->GetWindowTextW(NAME##_s);\
	double NAME = _wtof(NAME##_s)

void Calculator::UpdateCalculatorParams()
{
	CWnd* p = nullptr;
	MY_PARAM_HELPER(p, IDC_EDIT_param_a, a);
	MY_PARAM_HELPER(p, IDC_EDIT_param_m, m);
	MY_PARAM_HELPER(p, IDC_EDIT_param_f, f);
	MY_PARAM_HELPER(p, IDC_EDIT_xscale_from, x_from);
	MY_PARAM_HELPER(p, IDC_EDIT_xscale_to, x_to);
	MY_PARAM_HELPER(p, IDC_EDIT_yscale_from, y_from);
	MY_PARAM_HELPER(p, IDC_EDIT_yscale_to, y_to);
	if (a_s != "" && m_s != "" && f_s != "" && x_from_s != "" && x_to_s != "" && y_from_s != "" && y_to_s != "") {
		signal.set_a(a);
		signal.set_f(f);
		signal.set_m(m);
		Cgraph.setScale(x_from, x_to, y_from, y_to);
		RECT r;
		Cgraph.GetWindowRect(&r);
		r.right = r.right - r.left;
		r.bottom = r.bottom - r.top;
		r.left = r.top = 0;
		double step = slider_step.GetPos() * (x_to - x_from) / (r.right - r.left);
		Cgraph.setStep(step);
		Cgraph.setRect(r);
		Cgraph.setLog(cb_is_log.GetCheck() == 1);
		Cgraph.axes_color = axes_cp.GetColor();
		Cgraph.bg_color = bg_cp.GetColor();
		Cgraph.functions[0]->color = signal_cp.GetColor();
		Cgraph.functions[1]->color = dft_cp.GetColor();
		p = GetDlgItem(IDC_STATIC_signal);
		if (p) {
			CString signal;
			signal.Format(L"x(t) = %.2F*sin(2π(%.2F + %.2Ft)*t)", a, f, m);
			p->SetWindowTextW(signal);
		}

	}
	else {
		p = GetDlgItem(IDC_STATIC_signal);
		if (p) { p->SetWindowTextW(_T("x(t) = a*sin(2\u03c0(f + mt)*t")); }
		DataErrorDlg dlg;
		dlg.DoModal();
	}
}
#undef MY_PARAM_HELPER


void Calculator::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_graph, Cgraph);
	DDX_Control(pDX, IDC_SLIDER_STEP, slider_step);
	DDX_Control(pDX, IDC_CHECK_is_log_scale, cb_is_log);
}


BEGIN_MESSAGE_MAP(Calculator, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_graph, &Calculator::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_reset, &Calculator::OnBnClickedButtonreset)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_GR, &Calculator::OnBnClickedButtonSaveGr)
END_MESSAGE_MAP()


// Обработчики сообщений Calculator


void Calculator::OnBnClickedButtonUpdate()
{
	UpdateCalculatorParams();
	Cgraph.RedrawWindow();
}


void Calculator::OnBnClickedButtonreset()
{
	ResetInputData();

	ResetColorPickers();
}

void Calculator::ResetColorPickers()
{
	bg_cp.SetColor(RGB(0xff, 0xfb, 0xf0));
	signal_cp.SetColor(RGB(0x80, 0, 0));
	axes_cp.SetColor(RGB(0, 0, 0));
	dft_cp.SetColor(RGB(0, 0, 0x80));
}

void Calculator::ResetInputData()
{
	CWnd* p;
	p = nullptr;
	p = GetDlgItem(IDC_EDIT_param_a);
	if (p) { p->SetWindowTextW(L"1"); }
	p = nullptr;
	p = GetDlgItem(IDC_EDIT_param_m);
	if (p) { p->SetWindowTextW(L"0"); }
	p = nullptr;
	p = GetDlgItem(IDC_EDIT_param_f);
	if (p) { p->SetWindowTextW(L"0.1592"); }
	p = nullptr;
	p = GetDlgItem(IDC_EDIT_xscale_from);
	if (p) { p->SetWindowTextW(L"-6.2832"); }
	p = nullptr;
	p = GetDlgItem(IDC_EDIT_xscale_to);
	if (p) { p->SetWindowTextW(L"6.2832"); }
	p = nullptr;
	p = GetDlgItem(IDC_EDIT_yscale_from);
	if (p) { p->SetWindowTextW(L"-1.5"); }
	p = nullptr;
	p = GetDlgItem(IDC_EDIT_yscale_to);
	if (p) { p->SetWindowTextW(L"1.5"); }
}


void Calculator::OnBnClickedButtonSaveGr()
{
	CWnd* p = GetDlgItem(IDC_STATIC_graph);
	if (p) {
		CRect rect;
		p->GetClientRect(rect);
		CWindowDC wdc(p);
		CDC bmdc;
		bmdc.CreateCompatibleDC(&wdc);
		CBitmap bmp;
		bmp.CreateCompatibleBitmap(&bmdc, rect.Width(), rect.Height());
		HGDIOBJ olddc = bmdc.SelectObject(&bmp);
		bmdc.BitBlt(0, 0, rect.Width(), rect.Height(), &wdc, 0, 0, SRCCOPY);
		bmdc.SelectObject(olddc);
	}
}
