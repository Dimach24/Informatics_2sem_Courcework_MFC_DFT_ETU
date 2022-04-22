// Calculator.cpp: файл реализации
//
#include <cmath>
#include "pch.h"
#include "coursework.h"
#include "Calculator.h"
#include "afxdialogex.h"
#include "DataErrorDlg.h"
#include <initguid.h>
#include <cassert>

DEFINE_GUID(ImageFormatBMP, 0xb96b3cab, 0x0728, 0x11d3, 0x9d,
	0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);
DEFINE_GUID(ImageFormatJPEG, 0xb96b3cae, 0x0728, 0x11d3, 0x9d,
	0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);
DEFINE_GUID(ImageFormatPNG, 0xb96b3caf, 0x0728, 0x11d3, 0x9d,
	0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);
DEFINE_GUID(ImageFormatGIF, 0xb96b3cb0, 0x0728, 0x11d3, 0x9d,
	0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);

// Диалоговое окно Calculator

IMPLEMENT_DYNAMIC(Calculator, CDialogEx)

Calculator::Calculator(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Calculator, pParent),
	signal(),
	dft(nullptr) {
	dft.set_signal(&signal);
}

Calculator::~Calculator() {
}

BOOL Calculator::OnInitDialog() {
	graph_signal.SubclassDlgItem(IDC_STATIC_graph, this);
	graph_DFT.SubclassDlgItem(IDC_STATIC_graph2, this);
	bg_cp.SubclassDlgItem(IDC_MFCCOLORBUTTON_BG, this);
	signal_cp.SubclassDlgItem(IDC_MFCCOLORBUTTON_SIGNAL, this);
	dft_cp.SubclassDlgItem(IDC_MFCCOLORBUTTON_DCF, this);
	slider_step.SubclassDlgItem(IDC_SLIDER_STEP, this);
	cb_is_log.SubclassDlgItem(IDC_CHECK_is_log_scale, this);
	cb_is_dft_log.SubclassDlgItem(IDC_CHECK_is_log_scale2, this);
	edit_a.SubclassDlgItem(IDC_EDIT_param_a, this);
	edit_m.SubclassDlgItem(IDC_EDIT_param_m, this);
	edit_f.SubclassDlgItem(IDC_EDIT_param_f, this);
	edit_x_f.SubclassDlgItem(IDC_EDIT_xscale_from, this);
	edit_x_t.SubclassDlgItem(IDC_EDIT_xscale_to, this);
	edit_y_f.SubclassDlgItem(IDC_EDIT_yscale_from, this);
	edit_y_t.SubclassDlgItem(IDC_EDIT_yscale_to, this);
	edit_y_dft_t.SubclassDlgItem(IDC_EDIT_yscale_to2, this);
	edit_y_dft_f.SubclassDlgItem(IDC_EDIT_yscale_from2, this);
	slider_step.SetRangeMin(1);
	slider_step.SetRangeMax(10);
	slider_step.SetPos(3);

	CWnd* p = GetDlgItem(IDC_STATIC_signal);
	if (p) { p->SetWindowTextW(_T("x(t) = a*sin(2\u03c0(f + mt)*t")); }
	p = nullptr;
	edit_a.SetFocus();

	ResetInputData();
	ResetColorPickers();

	signal.set_definition_scope(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
	graph_signal.functions.push_back(&signal);
	graph_signal.hist = false;
	dft.set_definition_scope(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
	graph_DFT.functions.push_back(&dft);
	graph_DFT.hist = true;

	return 0;
}


void Calculator::UpdateCalculatorParams() {
	CString a_s;
	edit_a.GetWindowTextW(a_s);
	double a = _wtof(a_s);

	CString m_s;
	edit_m.GetWindowTextW(m_s);
	double m = _wtof(m_s);

	CString f_s;
	edit_f.GetWindowTextW(f_s);
	double f = _wtof(f_s);

	CString x_from_s;
	edit_x_f.GetWindowTextW(x_from_s);
	double x_from = _wtof(x_from_s);

	CString x_to_s;
	edit_x_t.GetWindowTextW(x_to_s);
	double x_to = _wtof(x_to_s);

	CString y_from_s;
	edit_y_f.GetWindowTextW(y_from_s);
	double y_from = _wtof(y_from_s);

	CString y_to_s;
	edit_y_t.GetWindowTextW(y_to_s);
	double y_to = _wtof(y_to_s);

	CString y_from2_s;
	edit_y_dft_f.GetWindowTextW(y_from2_s);
	double y_from2 = _wtof(y_from2_s);

	CString y_to2_s;
	edit_y_dft_t.GetWindowTextW(y_to2_s);
	double y_to2 = _wtof(y_to2_s);

	if (x_from >= x_to || y_from > y_to) {
		AfxMessageBox(_T("Невозможный масштаб"), MB_OK | MB_ICONERROR);
		return;
	}
	if (a_s != "" && m_s != "" && f_s != "" && x_from_s != "" && x_to_s != "" && y_from_s != "" && y_to_s != "") {
		signal.set_a(a);
		signal.set_f(f);
		signal.set_m(m);
		dft.set_a(a);
		dft.set_f(f);
		dft.set_m(m);
		if (cb_is_log.GetCheck() == 1) {
			if (y_from <= 0) {
				AfxMessageBox(_T("Неприемлимые границы логарифмического масштаба"), MB_OK | MB_ICONERROR);
				return;
			}
			graph_signal.setScale(x_from, x_to, log10(y_from), log10(y_to));
		} else {
			graph_signal.setScale(x_from, x_to, y_from, y_to);
		}
		if (cb_is_dft_log.GetCheck() == 1) {
			if (y_from2 < 0) {
				AfxMessageBox(_T("Отрицательные границы логарифмического масштаба"), MB_OK | MB_ICONERROR);
				return;
			}
			graph_DFT.setScale(x_from, x_to, log10(y_from2), log10(y_to2));
		} else {
			graph_DFT.setScale(x_from, x_to, y_from2, y_to2);
		}
		RECT r;
		graph_signal.GetWindowRect(&r);
		r.right = r.right - r.left;
		r.bottom = r.bottom - r.top;
		r.left = r.top = 0;
		double step = slider_step.GetPos() * (x_to - x_from) / (r.right - r.left);
		graph_signal.setStep(step);
		graph_DFT.setStep(step);
		graph_signal.setRect(r);
		graph_DFT.setRect(r);
		graph_signal.setLog(cb_is_log.GetCheck() == 1);
		graph_DFT.setLog(cb_is_dft_log.GetCheck() == 1);
		graph_signal.setBgColor(bg_cp.GetColor());
		graph_DFT.setBgColor(bg_cp.GetColor());
		graph_signal.functions[0]->color = signal_cp.GetColor();
		graph_DFT.functions[0]->color = dft_cp.GetColor();

		CWnd* p;
		p = GetDlgItem(IDC_STATIC_signal);
		if (p) {
			CString signal;
			signal.Format(L"x(t) = %.2F*sin(2π(%.2F + %.2Ft)*t)", a, f, m);
			p->SetWindowTextW(signal);
		}

	} else {
		CWnd* p = GetDlgItem(IDC_STATIC_signal);
		if (p) { p->SetWindowTextW(_T("x(t) = a*sin(2\u03c0(f + mt)*t")); }
		AfxMessageBox(_T("Недостаточно параметров"), MB_OK | MB_ICONERROR);
	}
}

void Calculator::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_graph, graph_signal);
	DDX_Control(pDX, IDC_SLIDER_STEP, slider_step);
	DDX_Control(pDX, IDC_CHECK_is_log_scale, cb_is_log);
	DDX_Control(pDX, IDC_EDIT_param_a, edit_a);
	DDX_Control(pDX, IDC_EDIT_param_m, edit_m);
	DDX_Control(pDX, IDC_EDIT_param_f, edit_f);
	DDX_Control(pDX, IDC_EDIT_xscale_from, edit_x_f);
	DDX_Control(pDX, IDC_EDIT_xscale_to, edit_x_t);
	DDX_Control(pDX, IDC_EDIT_yscale_from, edit_y_f);
	DDX_Control(pDX, IDC_EDIT_yscale_to, edit_y_t);
	DDX_Control(pDX, IDC_STATIC_graph2, graph_DFT);
	DDX_Control(pDX, IDC_CHECK_is_log_scale2, cb_is_dft_log);
	DDX_Control(pDX, IDC_EDIT_yscale_from2, edit_y_dft_f);
	DDX_Control(pDX, IDC_EDIT_yscale_to2, edit_y_dft_t);
}


BEGIN_MESSAGE_MAP(Calculator, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_graph, &Calculator::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_reset, &Calculator::OnBnClickedButtonreset)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_GR, &Calculator::OnBnClickedButtonSaveGr)
	ON_BN_CLICKED(IDC_CHECK_is_log_scale, &Calculator::OnBnClickedCheckislogscale)
	ON_BN_CLICKED(IDC_CHECK_is_log_scale2, &Calculator::OnBnClickedCheckislogscale2)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// Обработчики сообщений Calculator


void Calculator::OnBnClickedButtonUpdate() {
	UpdateCalculatorParams();
	graph_signal.RedrawWindow();
	graph_DFT.RedrawWindow();
}


void Calculator::OnBnClickedButtonreset() {
	ResetInputData();

	ResetColorPickers();
}

void Calculator::ResetColorPickers() {
	bg_cp.SetColor(RGB(0xff, 0xfb, 0xf0));
	signal_cp.SetColor(RGB(0x80, 0, 0));
	dft_cp.SetColor(RGB(0, 0, 0x80));
}

void Calculator::ResetInputData() {
	edit_a.SetWindowTextW(_T("1"));
	edit_m.SetWindowTextW(_T("0"));
	edit_f.SetWindowTextW(_T("0.1592"));
	edit_x_f.SetWindowTextW(_T("-6.2832"));
	edit_x_t.SetWindowTextW(_T("6.2832"));
	edit_y_f.SetWindowTextW(_T("-1.5"));
	edit_y_t.SetWindowTextW(_T("1.5"));
	edit_y_dft_f.SetWindowTextW(_T("0"));
	edit_y_dft_t.SetWindowTextW(_T("1.5"));
	cb_is_dft_log.SetCheck(0);
	cb_is_log.SetCheck(0);
}


void Calculator::OnBnClickedButtonSaveGr() {
	CWnd* p = GetDlgItem(IDC_STATIC_graph2);
	if (p) {
		CRect rect;
		p->GetClientRect(rect);
		CWindowDC wdc(p);
		CDC bmdc;
		bmdc.CreateCompatibleDC(&wdc);
		CBitmap bmp;
		bmp.CreateCompatibleBitmap(&wdc, rect.Width(), rect.Height());
		HGDIOBJ olddc = bmdc.SelectObject(&bmp);
		bmdc.BitBlt(0, 0, rect.Width(), rect.Height(), &wdc, 0, 0, SRCCOPY);
		bmdc.SelectObject(olddc);
		CFileDialog dlg(FALSE, _T(".bmp"), L"График ДПФ.bmp", OFN_OVERWRITEPROMPT,
			_T("BMP Files (*.bmp)|*.bmp|PNG Files (*.png)|*.png| GIF Files(*.gif)\
|*.gif| JPG Files (*.jpg)|*.jpg|All Files (*.*)|*.*||"));
		dlg.DoModal();
		CString path = dlg.GetOFN().lpstrFile;
		short i = path.ReverseFind(L'.');
		CString extension;
		if (i == -1) {
			path += ".bmp";
			extension = _T(".bmp");
		} else {
			i = path.GetLength() - i;
			extension = path.Right(i);
			extension.MakeLower();
		}
		CImage img;
		img.Attach(HBITMAP(bmp));
		HRESULT saving;
		if (extension == _T(".jpg")) {
			saving = img.Save(path, ImageFormatJPEG);
		} else if (extension == _T(".png")) {
			saving = img.Save(path, ImageFormatPNG);
		} else if (extension == _T(".gif")) {
			saving = img.Save(path, ImageFormatGIF);
		} else if (extension == _T(".bmp")) {
			saving = img.Save(path, ImageFormatBMP);
		} else {
			path += ".bmp";
			saving = img.Save(path, ImageFormatBMP);
		}
		if (FAILED(saving)) {
			AfxMessageBox(_T("При сохранении файла что-то пошло не так"));
		}
	}
}


void Calculator::OnBnClickedCheckislogscale() {
	CString fromStr, toStr;
	edit_y_f.GetWindowTextW(fromStr);
	edit_y_t.GetWindowTextW(toStr);
	double
		from = _wtof(fromStr),
		to = _wtof(toStr);
	if (cb_is_log.GetCheck() == 1) { //turned to log
		// exponentiating
		fromStr.Format(L"%f", pow(10, from));
		edit_y_f.SetWindowTextW(fromStr);
		toStr.Format(L"%f", pow(10, to));
		edit_y_t.SetWindowTextW(toStr);
	} else {						//turned to the normal
		if (from <= 0 || to <= 0) { return; }
		fromStr.Format(L"%f", log10(from));
		edit_y_f.SetWindowTextW(fromStr);
		toStr.Format(L"%f", log10(to));
		edit_y_t.SetWindowTextW(toStr);
	}
}


void Calculator::OnBnClickedCheckislogscale2() {
	CString fromStr, toStr;
	edit_y_dft_f.GetWindowTextW(fromStr);
	edit_y_dft_t.GetWindowTextW(toStr);
	double
		from = _wtof(fromStr),
		to = _wtof(toStr);
	if (cb_is_dft_log.GetCheck() == 1) { //turned to log
		// exponentiating
		fromStr.Format(L"%f", pow(10, from));
		edit_y_dft_f.SetWindowTextW(fromStr);
		toStr.Format(L"%f", pow(10, to));
		edit_y_dft_t.SetWindowTextW(toStr);
	} else {						//turned to the normal
		if (from <= 0 || to <= 0) { return; }
		fromStr.Format(L"%f", log10(from));
		edit_y_dft_f.SetWindowTextW(fromStr);
		toStr.Format(L"%f", log10(to));
		edit_y_dft_t.SetWindowTextW(toStr);
	}
}


void Calculator::OnMouseMove(UINT nFlags, CPoint point) {
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CPoint p(point);
	ClientToScreen(&p);
	CWnd* pWnd = nullptr;
	pWnd = GetDlgItem(IDC_STATIC_CPOS);
	CString s = L"Наведите курсор на график";
	assert(pWnd);

	CRect rs;
	graph_signal.GetWindowRect(rs);
	CRect rd;
	graph_DFT.GetWindowRect(rd);
	if (rs.PtInRect(p)) {
		p.Offset(-rs.left, -rs.top);
		auto dot = graph_signal.dotCoords(p.x, p.y);
		s.Format(L"%.4f; %.4f", dot.first, dot.second);
	} else	if (rd.PtInRect(p)) {
		p.Offset(-rd.left, -rd.top);
		auto dot = graph_DFT.dotCoords(p.x, p.y);
		s.Format(L"%.4f; %.4f", dot.first, dot.second);
	}
	pWnd->SetWindowTextW(s);
	CDialogEx::OnMouseMove(nFlags, point);
}
