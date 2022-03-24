#pragma once

#include "CMyGraph.h"
// Диалоговое окно Calculator

class Calculator : public CDialogEx
{
	DECLARE_DYNAMIC(Calculator)

public:
	Calculator(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~Calculator();
	BOOL OnInitDialog();
	void UpdateCalculatorParams();
protected:
	SignalFunction signal;
	DFTFunction dft;
	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Calculator };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	DECLARE_MESSAGE_MAP()
public:
	CMyGraph Cgraph;
	afx_msg void OnBnClickedButtonUpdate();
	CSliderCtrl slider_step;
	CButton cb_is_log;
	CMFCColorButton bg_cp;
	CMFCColorButton signal_cp;
	CMFCColorButton dft_cp;
	afx_msg void OnBnClickedButtonreset();
protected:
	void ResetColorPickers();
	void ResetInputData();
public:
	afx_msg void OnBnClickedButtonSaveGr();
	afx_msg void OnBnClickedCheckislogscale();
	CEdit edit_a;
	CEdit edit_m;
	CEdit edit_f;
	CEdit edit_x_f;
	CEdit edit_x_t;
	CEdit edit_y_f;
	CEdit edit_y_t;
	CMyGraph DFTgraph;
	CButton cb_is_dft_log;
	CEdit edit_y_dft_f;
	CEdit edit_y_dft_t;
};
