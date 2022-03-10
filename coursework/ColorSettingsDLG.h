#pragma once


// Диалоговое окно ColorSettingsDLG

class ColorSettingsDLG : public CDialogEx
{
	DECLARE_DYNAMIC(ColorSettingsDLG)

public:
	ColorSettingsDLG(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~ColorSettingsDLG();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ColorSettingsDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
};
