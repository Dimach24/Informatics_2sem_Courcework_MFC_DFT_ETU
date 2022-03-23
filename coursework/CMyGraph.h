#pragma once
#include <vector>
#include "MathFunction.h"
// CMyGraph

class CMyGraph : public CStatic
{
	DECLARE_DYNAMIC(CMyGraph)

protected:
public:
	
	struct {
		double from, to;
	}scale_x, scale_y;
	
	std::vector<MathFunction*> functions;
	CMyGraph();
	virtual ~CMyGraph();

protected:
	DECLARE_MESSAGE_MAP()
public:
	COLORREF bg_color=RGB(255,255,255);
	afx_msg void OnPaint();
	void setScale(double x_from, double x_to, double y_from, double y_to);
	void setStep(double step);
	void setRect(RECT r);
	void setLog(bool b);
	void setNotCalculated();
};


