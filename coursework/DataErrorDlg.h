#pragma once


// Диалоговое окно DataErrorDlg

class DataErrorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DataErrorDlg)

public:
	DataErrorDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~DataErrorDlg();
	BOOL OnInitDialog();
// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DataErrorDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
};
