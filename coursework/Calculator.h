//
// Calculator.h
//

#pragma once

#include "CMyGraph.h" // for graphs

/// <summary>
/// Defines dlg with calculating
/// </summary>
class Calculator : public CDialogEx
{
	// timer settings for animation
	const static uint64_t timer_id = 12345654;
	const static uint64_t timer_delay = 40;

	// enables access to run-time class information
	DECLARE_DYNAMIC(Calculator)

public:
	/// <summary>
	/// Standard constructor
	/// </summary>
	/// <param name="pParent">a pointer to the parent window</param>
	Calculator(CWnd* pParent = nullptr);

	/// <summary>
	/// std destructor
	/// </summary>
	virtual ~Calculator();

	/// <summary>
	/// defines init behavior
	/// </summary>
	BOOL OnInitDialog();

	/// <summary>
	/// Updates params in the functions and graphs
	/// with info from controls
	/// </summary>
	void UpdateCalculatorParams();
protected:

	// MathFunction objects for graphs:

	/// <summary>
	/// the object represents signal function
	/// </summary>
	SignalFunction signal;

	/// <summary>
	/// the object represents DFT
	/// </summary>
	DFTFunction dft;

	// Graphs:

	/// <summary>
	/// signal graph painter
	/// </summary>
	CMyGraph graph_signal;

	/// <summary>
	/// DFT hist painter
	/// </summary>
	CMyGraph graph_DFT;

	// Controls:

	CSliderCtrl slider_samples;
	CSliderCtrl slider_step;

	CEdit edit_a;
	CEdit edit_m;
	CEdit edit_f;
	CEdit edit_x_f;
	CEdit edit_x_t;
	CEdit edit_y_f;
	CEdit edit_y_t;
	CEdit edit_y_dft_f;
	CEdit edit_y_dft_t;

	CButton cb_is_dft_log;
	CButton cb_anim;

	CMFCColorButton bg_cp;
	CMFCColorButton signal_cp;
	CMFCColorButton dft_cp;

	// static text with samples amount
	CStatic text_slider_samples;

	// dialog id for building
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Calculator };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	// message processing loop
	DECLARE_MESSAGE_MAP()

protected:
	/// <summary>
	/// resets color pickers
	/// </summary>
	void ResetColorPickers();

	/// <summary>
	/// resets all data
	/// </summary>
	void ResetInputData();
public:
	// messages processing functions
	afx_msg void OnBnClickedButtonUpdate();
	afx_msg void OnBnClickedButtonreset();
	afx_msg void OnBnClickedButtonSaveGr();
	afx_msg void OnBnClickedCheckislogscale();
	afx_msg void OnBnClickedCheckislogscale2();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
