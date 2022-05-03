#pragma once
#include <vector>
#include "MathFunction.h"
#include  <utility> //for std::pair

// CMyGraph

class CMyGraph : public CStatic
{
	
	DECLARE_DYNAMIC(CMyGraph)

protected:
	void drawBg(CDC& dc);
	bool background_calculated=false;
	COLORREF bg_color = RGB(255, 255, 255);
	CBitmap bg_bmp;
	HGDIOBJ old_bmp=NULL;
	CDC bgdc;
protected:
	void drawGraph(CDC& dc);
	bool graph_is_done = false;
	CBitmap graph;
	HGDIOBJ old_g_bmp = NULL;
	CDC graph_dc;

	void draw(CDC& dc);
protected:
	bool animation_in_process=false;
	float current_animation_phase=0;
	float animation_speed=5e-2;
	CPoint recalcDotForAnimation(CPoint point, CRect r);
public:
	struct { int x, y; } serifs={5,3};
	int serifsize = 15;
	bool hist=false;
	int step = 0;
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
	void setStep(int step);
	void setRect(RECT r);
	void setLog(bool b);
	void setNotCalculated();
	void setBgColor(COLORREF col);
	void setAnimState(bool state);
	std::pair<float, float> dotToCoords(int wx, int wy);
	POINT coordsToDot(double x, double y);
	bool timerTick();
};


