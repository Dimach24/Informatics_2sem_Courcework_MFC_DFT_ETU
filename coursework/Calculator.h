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
	SignalFunction signal;
};
