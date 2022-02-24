#pragma once


// Диалоговое окно MyTaskAboutDlg

class MyTaskAboutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MyTaskAboutDlg)

public:
	MyTaskAboutDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~MyTaskAboutDlg();
// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MyTaskAboutDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CString about_string;
	// элемент управления richedit taskabout
	CRichEditCtrl TaskAboutCtrl;
};
