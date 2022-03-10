// CMyGraph.cpp: файл реализации
//

#include "pch.h"
#include "coursework.h"
#include "CMyGraph.h"


// CMyGraph

IMPLEMENT_DYNAMIC(CMyGraph, CStatic)

CMyGraph::CMyGraph() :CStatic()
{
}

CMyGraph::~CMyGraph()
{
}






BEGIN_MESSAGE_MAP(CMyGraph, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// Обработчики сообщений CMyGraph





void CMyGraph::OnPaint()
{
	CPaintDC dc(this);
	//dc.LineTo({ 255,255 });
	RECT r;
	GetWindowRect(&r);
	r = {0,0,r.right-r.left,r.bottom-r.top};
	dc.FillSolidRect(&r, RGB(250,250,250));

	for (MathFunction& f : functions) {
		//dc.LineTo({ 0,128 });
		bool is_first = true;
		RECT r;;
		for (POINT dot : f.points) {
			if (is_first) { dc.LineTo(dot); is_first = false; }
			else { dc.LineTo(dot); }

		}
	}
	//dc.LineTo({ 128, 0 });
}

void CMyGraph::setScale(double x_from, double x_to, double y_from, double y_to)
{
	for (MathFunction& f : functions) {
		f.set_scale(x_from, x_to, y_from, y_to);
	}
}

void CMyGraph::setStep(double step)
{
	for (MathFunction& f : functions) {
		f.set_step(step);
	}
}

void CMyGraph::setRect(RECT r)
{
	for (MathFunction& f : functions) {
		f.set_rect(r);
	}
}

void CMyGraph::setLog(bool b)
{
	for (MathFunction& f : functions) {
		f.set_log(b);
	}
}

void CMyGraph::setNotCalculated()
{
	for (MathFunction& f : functions) {
		f.set_not_calculated();
	}
}
