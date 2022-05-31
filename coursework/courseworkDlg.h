//
// courseworkDlg.h
//

#pragma once

/// <summary>
/// Class that defines exterior and behavior
/// of the main dialog - child of CDialogEx
/// </summary>
class CcourseworkDlg : public CDialogEx
{
public:
	/// <summary>
	/// Standard constructor
	/// </summary>
	/// <param name="pParent">a pointer to the parent window</param>
	CcourseworkDlg(CWnd* pParent = nullptr);

	// dialog id for building
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COURSEWORK_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


protected:
	/// <summary>
	/// App Icon
	/// </summary>
	HICON m_hIcon;

	/// <summary>
	/// Short task info
	/// </summary>
	CString theTask;

	// functions of the message processing
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();

	// message processing loop
	DECLARE_MESSAGE_MAP()
public:
	// functions of the message processing
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedTaskAboutBn();
	afx_msg void OnBnClickedCalculateButton();
};
