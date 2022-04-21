#pragma once
#include <vector>
#include "MathFunction.h"
#include  <utility> //for std::pair

// CMyGraph

class CMyGraph : public CStatic
{
	DECLARE_DYNAMIC(CMyGraph)

protected:
	std::pair<float,float> dotCoords(int wx, int wy);
	POINT realToScreenCoords(double x, double y);
	void draw_axis(CDC& dc);
	bool background_calculated=false;
	COLORREF bg_color = RGB(255, 255, 255);
	CBitmap bg_bmp;
	HGDIOBJ old_bmp=NULL;
	CDC bgdc;
public:
	struct { int x, y; } serifs={5,3};
	int serifsize = 15;
	bool hist=false;
	struct
	{
		double from, to;
	}scale_x, scale_y;
	bool is_log = false;
	std::vector<MathFunction*> functions;
	CMyGraph();
	virtual ~CMyGraph();
	POINT shift = {60,30};
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	void setScale(double x_from, double x_to, double y_from, double y_to);
	void setStep(double step);
	void setRect(RECT r);
	void setLog(bool b);
	void setNotCalculated();
	void setBgColor(COLORREF col);
};


