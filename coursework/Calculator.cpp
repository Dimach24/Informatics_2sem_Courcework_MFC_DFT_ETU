//
// Calculator.cpp
//


// including project files
#include "pch.h"
#include "coursework.h"
#include "BeautyLib.h"
#include "Calculator.h"
#include "afxdialogex.h"

#include <initguid.h>	// for guids
#include <cassert>		// for asserts 
#include <cmath>		// for math functions as log, pow, etc

// guids for image codecs
DEFINE_GUID(ImageFormatBMP, 0xb96b3cab, 0x0728, 0x11d3, 0x9d,
	0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);
DEFINE_GUID(ImageFormatJPEG, 0xb96b3cae, 0x0728, 0x11d3, 0x9d,
	0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);
DEFINE_GUID(ImageFormatPNG, 0xb96b3caf, 0x0728, 0x11d3, 0x9d,
	0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);
DEFINE_GUID(ImageFormatGIF, 0xb96b3cb0, 0x0728, 0x11d3, 0x9d,
	0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);

// for runtime data
IMPLEMENT_DYNAMIC(Calculator, CDialogEx)

Calculator::Calculator(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Calculator, pParent),	// base constructor
	signal(),								// SignalFunction default constructor
	dft() {									// DFTFunction default constructor
	dft.set_signal(&signal);				// Set signal function for dft object
}

Calculator::~Calculator() {					// default destructor
}

BOOL Calculator::OnInitDialog() {
	// control elements connection
	graph_signal.SubclassDlgItem(IDC_STATIC_graph, this);
	graph_DFT.SubclassDlgItem(IDC_STATIC_graph2, this);
	bg_cp.SubclassDlgItem(IDC_MFCCOLORBUTTON_BG, this);
	signal_cp.SubclassDlgItem(IDC_MFCCOLORBUTTON_SIGNAL, this);
	dft_cp.SubclassDlgItem(IDC_MFCCOLORBUTTON_DCF, this);
	slider_step.SubclassDlgItem(IDC_SLIDER_STEP, this);
	slider_samples.SubclassDlgItem(IDC_SLIDER_SAMPLES, this);
	text_slider_samples.SubclassDlgItem(IDC_STATIC_SAMPLES, this);
	cb_is_dft_log.SubclassDlgItem(IDC_CHECK_is_log_scale2, this);
	cb_anim.SubclassDlgItem(IDC_CHECK_ANIM, this);
	edit_a.SubclassDlgItem(IDC_EDIT_param_a, this);
	edit_m.SubclassDlgItem(IDC_EDIT_param_m, this);
	edit_f.SubclassDlgItem(IDC_EDIT_param_f, this);
	edit_x_f.SubclassDlgItem(IDC_EDIT_xscale_from, this);
	edit_x_t.SubclassDlgItem(IDC_EDIT_xscale_to, this);
	edit_y_f.SubclassDlgItem(IDC_EDIT_yscale_from, this);
	edit_y_t.SubclassDlgItem(IDC_EDIT_yscale_to, this);
	edit_y_dft_t.SubclassDlgItem(IDC_EDIT_yscale_to2, this);
	edit_y_dft_f.SubclassDlgItem(IDC_EDIT_yscale_from2, this);

	// setting range of the slider
	slider_step.SetRangeMin(1);
	slider_step.SetRangeMax(10);
	slider_samples.SetRangeMin(100);
	slider_samples.SetRangeMax(1000);

	// turn animation on
	cb_anim.SetCheck(1);

	// find element
	CWnd* p = GetDlgItem(IDC_STATIC_signal);
	//set default text
	if (p) { p->SetWindowTextW(_T("x(t) = a\u2219sin(2\u03c0(f + mt)\u2219t")); }

	// set focus to the first input element
	edit_a.SetFocus();

	// set default data for controls
	ResetInputData();
	ResetColorPickers();

	// set default for the MathFunction s
	// and add it to graph drawer
	signal.setDefinitionScope(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
	signal.setLog(0);
	graph_signal.setLog(0);
	graph_signal.functions.push_back(&signal);
	graph_signal.is_hist = false;
	dft.setDefinitionScope(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
	graph_DFT.functions.push_back(&dft);
	graph_DFT.is_hist = true;


	// adding 'save' to the sys menu
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr) {
		CString strSaveMenu = L"Сохранить как";
		if (!strSaveMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDD_Calculator, strSaveMenu);
		}
	}
	return 0;
}

void Calculator::UpdateCalculatorParams() {
	// getting data from input as strings
	// and converting string to doubles

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

	// if lower bound is more then high one
	if (x_from >= x_to || y_from > y_to || y_from2 > y_to2) {
		// send message to the user
		AfxMessageBox(_T("Невозможный масштаб"), MB_OK | MB_ICONERROR);
		// end (do not update info)
		return;
	}

	// if there is no empty fields
	if (a_s != "" && m_s != "" && f_s != "" && x_from_s != "" && x_to_s != "" && y_from_s != "" && y_to_s != "") {

		// coefs
		f *= 1e7;
		m *= 1e7;
		x_from *= 1e-4;
		x_to *= 1e-4;

		// set signal params
		signal.set_a(a);	signal.set_f(f);	signal.set_m(m);
		dft.set_a(a);		dft.set_f(f);		dft.set_m(m);


		double
			x_from_dft = 0,
			x_to_dft = 1e7;
		// if log 
		if (cb_is_dft_log.GetCheck() == 1) {
			if (y_from2 < 0) {	// negative log scale
				// send message to the user
				AfxMessageBox(_T("Отрицательные границы логарифмического масштаба"), MB_OK | MB_ICONERROR);
				return;
			}
			// set log scale
			graph_DFT.setScale(x_from_dft, x_to_dft, log10(y_from2), log10(y_to2));
		} else {
			// set scale
			graph_DFT.setScale(x_from_dft, x_to_dft, y_from2, y_to2);
		}
		graph_signal.setScale(x_from, x_to, y_from, y_to);
		// declare rectangular
		CRect r;
		// write client region to it
		graph_signal.GetClientRect(r);

		// get graph step (amount of pixels between two nearest
		// graph points along the abscissa axis)
		int step = slider_step.GetPos();

		// setting the step and region
		graph_signal.setStep(step);
		graph_DFT.setStep(step);
		graph_signal.setRect(r);
		graph_DFT.GetClientRect(r);
		graph_DFT.setRect(r);

		// setting samples amount
		int N = slider_samples.GetPos();
		dft.set_samples_amount(N);
		signal.set_samples_amount(N);
		graph_DFT.setColumnsCount(N);

		// set log scale
		graph_DFT.setLog(cb_is_dft_log.GetCheck() == 1);

		// set colors
		graph_signal.setBgColor(bg_cp.GetColor());
		graph_DFT.setBgColor(bg_cp.GetColor());
		graph_signal.functions[0]->setColor(signal_cp.GetColor());
		graph_DFT.functions[0]->setColor(dft_cp.GetColor());

		// find the static element and put formatted string to it
		CWnd* p;
		p = GetDlgItem(IDC_STATIC_signal);
		if (p) {
			CString signal;
			signal.Format(L"x(t) = %s\u2219sin(2π(%s + %s\u2219t)\u2219t)",
				beautifulRepresentation(a, 2, 2),
				beautifulRepresentation(f, 2, 2),
				beautifulRepresentation(m, 2, 2)
			);
			p->SetWindowTextW(signal);
		}

	} else { // empty elements were found
		// find the static element and put formetted string to it
		CWnd* p = GetDlgItem(IDC_STATIC_signal);
		if (p) { p->SetWindowTextW(_T("x(t) = a\u2219sin(2\u03c0(f + mt)\u2219t")); }
		// send message to the user
		AfxMessageBox(_T("Недостаточно параметров"), MB_OK | MB_ICONERROR);
	}
}

void Calculator::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);								// base data exchange
																// controls data exchange
	DDX_Control(pDX, IDC_STATIC_graph, graph_signal);
	DDX_Control(pDX, IDC_SLIDER_STEP, slider_step);
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
	DDX_Control(pDX, IDC_CHECK_ANIM, cb_anim);
	DDX_Control(pDX, IDC_SLIDER_SAMPLES, slider_samples);
	DDX_Control(pDX, IDC_STATIC_SAMPLES, text_slider_samples);
}


// messages processing loop
BEGIN_MESSAGE_MAP(Calculator, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_graph, &Calculator::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_reset, &Calculator::OnBnClickedButtonreset)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_GR, &Calculator::OnBnClickedButtonSaveGr)
	ON_BN_CLICKED(IDC_CHECK_is_log_scale2, &Calculator::OnBnClickedCheckislogscale2)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_SYSCOMMAND()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


void Calculator::OnBnClickedButtonUpdate() {
	UpdateCalculatorParams();			// update data
	if (cb_anim.GetCheck() == 1) {		// if do animate
		graph_signal.setAnimState(true);// set anim state
		graph_DFT.setAnimState(true);	// same
		// set timer
		SetTimer(timer_id, timer_delay, nullptr);
	}
	// draw graphs
	graph_signal.RedrawWindow();
	graph_DFT.RedrawWindow();
}

void Calculator::OnBnClickedButtonreset() {
	ResetInputData();	// reset input data
	ResetColorPickers();// reset color pickers
}

void Calculator::ResetColorPickers() {
	// sets default colors
	bg_cp.SetColor(RGB(0xff, 0xfb, 0xf0));
	signal_cp.SetColor(RGB(0x80, 0, 0));
	dft_cp.SetColor(RGB(0, 0, 0x80));
}

void Calculator::ResetInputData() {
	// sets default input data
	edit_a.SetWindowTextW(_T("1"));
	edit_m.SetWindowTextW(_T("1"));
	edit_f.SetWindowTextW(_T("0.2"));
	edit_x_f.SetWindowTextW(_T("0"));
	edit_x_t.SetWindowTextW(_T("1"));
	edit_y_f.SetWindowTextW(_T("-1.5"));
	edit_y_t.SetWindowTextW(_T("1.5"));
	edit_y_dft_f.SetWindowTextW(_T("0.01"));
	edit_y_dft_t.SetWindowTextW(_T("10000"));
	text_slider_samples.SetWindowTextW(L"Число отсчётов: 500");
	cb_is_dft_log.SetCheck(1);
	slider_step.SetPos(1);
	slider_samples.SetPos(500);
}

void Calculator::OnBnClickedButtonSaveGr() {
	// Areas of the 1st pic, 2nd pic and result pic
	CRect r1, r2, rr;

	// offset between pics
	const int offset = 20;

	// getting areas
	graph_signal.GetClientRect(r1);
	graph_DFT.GetClientRect(r2);

	//calculating the area
	rr = { 0,0,r1.Width(),r1.Height() + r2.Height() + offset };

	CBitmap bmp;		// bitmap for the picture
	CDC bmdc;			// dc for drawing

	// existing dc to create own bmdc
	CWindowDC wdc(&graph_signal);

	// creating dc and bitmap
	bmdc.CreateCompatibleDC(&wdc);
	bmp.CreateCompatibleBitmap(&wdc, rr.Width(), rr.Height());

	// selecting bitmap
	HGDIOBJ olddc = bmdc.SelectObject(&bmp);

	// copying pic from CWindowDC(&graph_signal)
	bmdc.BitBlt(0, 0, r1.Width(), r1.Height(), &wdc, 0, 0, SRCCOPY);

	// filling space between pics
	bmdc.FillSolidRect(
		CRect({ 0,r1.Height(),r1.Width(),r1.Height() + offset }),
		graph_signal.getBgColor()
	);

	// copying pic from CWindowDC(&graph_DFT)
	bmdc.BitBlt(0, r1.Height() + offset, r2.Width(), r2.Height(), &CWindowDC(&graph_DFT), 0, 0, SRCCOPY);

	// dc restoring
	bmdc.SelectObject(olddc);


	// creating file dialog
	CFileDialog dlg(FALSE, _T(".bmp"), L"График ДПФ.bmp", OFN_OVERWRITEPROMPT,
		L"BMP Files (*.bmp)|*.bmp|PNG Files (*.png)|*.png| GIF Files(*.gif)"
		L"|*.gif| JPG Files (*.jpg)|*.jpg|All Files (*.*)|*.*||");
	dlg.DoModal();	// show the dlg

	// getting file path
	CString path = dlg.GetOFN().lpstrFile;

	// find the last dot in the path
	short i = path.ReverseFind(L'.');

	// file extension
	CString extension;
	if (i == -1) {
		// there is no dot
		path += ".bmp";			// default
		extension = _T(".bmp");	// default
	} else {
		// calculating length of the 
		// path after last dot
		i = path.GetLength() - i;

		// slicing the path string to get extension
		extension = path.Right(i);

		// lowering the extension (from ".BMP" to ".bmp", etc)
		extension.MakeLower();
	}
	// Creating CImage according to the bitmap 'bmp'
	CImage img;
	img.Attach(HBITMAP(bmp));

	HRESULT saving;	// place for the error code

	// switch-case like block (choosing the file format)
	if (extension == _T(".jpg")) {
		saving = img.Save(path, ImageFormatJPEG);
	} else if (extension == _T(".png")) {
		saving = img.Save(path, ImageFormatPNG);
	} else if (extension == _T(".gif")) {
		saving = img.Save(path, ImageFormatGIF);
	} else if (extension == _T(".bmp")) {
		saving = img.Save(path, ImageFormatBMP);
	} else {	// default
		// if not found correct img formats
		// add ".bmp" to the end of path
		//		file.myexten -> file.myexten.bmp
		// to avoid mistakes with replacing extension
		path += ".bmp";
		saving = img.Save(path, ImageFormatBMP);
	}
	if (FAILED(saving)) {	// errors detected
		// tell to user
		AfxMessageBox(_T("При сохранении файла что-то пошло не так"), MB_OK | MB_ICONERROR);
	}
}


void Calculator::OnBnClickedCheckislogscale2() {
	// same but with another controls
	CString fromStr, toStr;
	edit_y_dft_f.GetWindowTextW(fromStr);
	edit_y_dft_t.GetWindowTextW(toStr);
	double
		from = _wtof(fromStr),
		to = _wtof(toStr);
	if (cb_is_dft_log.GetCheck() == 1) { // turned to log
		// exponentiating
		fromStr.Format(L"%f", pow(10, from));
		edit_y_dft_f.SetWindowTextW(fromStr);
		toStr.Format(L"%f", pow(10, to));
		edit_y_dft_t.SetWindowTextW(toStr);
	} else {						// turned to the normal
		if (from <= 0 || to <= 0) { return; }
		fromStr.Format(L"%f", log10(from));
		edit_y_dft_f.SetWindowTextW(fromStr);
		toStr.Format(L"%f", log10(to));
		edit_y_dft_t.SetWindowTextW(toStr);
	}
}

void Calculator::OnMouseMove(UINT nFlags, CPoint point) {
	CPoint p(point);	// copy coords
	ClientToScreen(&p);	// coord conversion
	// find the static text object
	CWnd* pWnd = nullptr;
	pWnd = GetDlgItem(IDC_STATIC_CPOS);

	// default text
	CString s = L"Для трассировки наведите курсор на график";
	assert(pWnd);

	// get client rects of the graphs
	CRect rs;
	graph_signal.GetWindowRect(rs);
	CRect rd;
	graph_DFT.GetWindowRect(rd);

	// if point in the 1st graph
	if (rs.PtInRect(p)) {
		// move the point
		p.Offset(-rs.left, -rs.top);
		// rect shifting
		rs = { 0,0,rs.Width(),rs.Height() };
		// coord back conversion
		auto dot = graph_signal.dotToCoords(p.x, p.y, rs);
		// format string according to scale type
		if (!graph_signal.is_log) {
			s.Format(L"t:%s; x:%s",
				beautifulRepresentation(dot.first, 2, 4),
				beautifulRepresentation(dot.second, 2, 4));
		} else {
			s.Format(L"t:%s; x:%s",
				beautifulRepresentation(dot.first, 2, 4),
				beautifulRepresentation(pow(10, dot.second), 2, 4));
		}
	} else	if (rd.PtInRect(p)) {	//same but with 2nd graph
		p.Offset(-rd.left, -rd.top);
		rd = { 0,0,rd.Width(),rd.Height() };
		auto dot = graph_DFT.dotToCoords(p.x, p.y, rd);
		if (!graph_DFT.is_log) {
			s.Format(L"\u03c9:%s; X:%s",
				beautifulRepresentation(dot.first, 2, 4),
				beautifulRepresentation(dot.second, 2, 4));
		} else {
			s.Format(L"\u03c9:%s; X:%s",
				beautifulRepresentation(dot.first, 2, 4),
				beautifulRepresentation(pow(10, dot.second), 2, 4));
		}
	}//else{;}

	// set formatted text
	pWnd->SetWindowTextW(s);

	// base message processing
	CDialogEx::OnMouseMove(nFlags, point);
}

void Calculator::OnTimer(UINT_PTR nIDEvent) {
	if (nIDEvent == timer_id) { // if it is animation timer
		// tick and check is it the last tick 
		// in the animation for both graphs
		bool end = graph_signal.timerTick();
		end = graph_DFT.timerTick() && end;
		// P.S. move operands if you want to draw one by one

		if (end) { // if it is the last tick in both graphs
			// stop the timer
			KillTimer(timer_id);

			// set animation stopped
			graph_DFT.setAnimState(false);
			graph_signal.setAnimState(false);
		}
	}
	CDialogEx::OnTimer(nIDEvent);	// base timer processing
}

// on system menu called
void Calculator::OnSysCommand(UINT nID, LPARAM lParam) {
	// if action is 'save'
	if (nID == IDD_Calculator) {
		OnBnClickedButtonSaveGr();
	} else {// base case
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// updates CStatic with number of samples
void Calculator::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	// check if it's slider for number of samples
	if (pScrollBar == reinterpret_cast<CScrollBar*>(&slider_samples)) {
		// create string
		CString str;
		// format the string
		str.Format(L"Число отсчётов: %d", slider_samples.GetPos());
		// update CStatic text
		text_slider_samples.SetWindowTextW(str);
	}
	// base action
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
