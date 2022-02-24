#pragma once


// Диалоговое окно MyTaskAboutDlg

class MyTaskAboutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MyTaskAboutDlg)

public:
	MyTaskAboutDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	BOOL OnInitDialog();
	virtual ~MyTaskAboutDlg();
// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MyTaskAboutDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
};
