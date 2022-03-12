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
	CMFCColorButton axes_cp;
	CMFCColorButton bg_cp;
	CMFCColorButton signal_cp;
	CMFCColorButton dft_cp;
	afx_msg void OnBnClickedButtonreset();
protected:
	void ResetColorPickers();
	void ResetInputData();
};
