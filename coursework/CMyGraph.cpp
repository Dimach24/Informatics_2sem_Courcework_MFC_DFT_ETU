// CMyGraph.cpp: файл реализации
//

#include "pch.h"
#include "coursework.h"
#include "CMyGraph.h"


// CMyGraph

IMPLEMENT_DYNAMIC(CMyGraph, CStatic)

CMyGraph::CMyGraph()
	:CStatic(),
	scale_x(), scale_y() {
}

CMyGraph::~CMyGraph() {
}






BEGIN_MESSAGE_MAP(CMyGraph, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// Обработчики сообщений CMyGraph


void CMyGraph::OnPaint() {
	CPaintDC dc(this);
	CPen gr(BS_SOLID, 1, RGB(0, 0, 0));
	HGDIOBJ oldpen = dc.SelectObject(gr);

	RECT r;
	GetWindowRect(&r);
	r = { 0,0,r.right - r.left,r.bottom - r.top };
	dc.IntersectClipRect(&r);
	dc.FillSolidRect(&r, bg_color);


	for (MathFunction* f : functions) {
		bool is_first = true;
		CPen gr(BS_SOLID, 1, f->color);
		dc.SelectObject(gr);
		dc.MoveTo({ r.right / 2, r.bottom / 2 });
		for (POINT dot : f->get_points()) {
			if (hist) {
				dc.MoveTo(dot.x, r.bottom);
				dc.LineTo(dot);
			}
			else {
				if (is_first) { dc.MoveTo(dot); is_first = false; } else {
					dc.LineTo(dot);
				}
			}
		}
	}

	CPen axespen(BS_SOLID, 2, RGB(0, 0, 0));
	dc.SelectObject(axespen);

	dc.MoveTo(1, 0);
	dc.LineTo(1, r.bottom - 1);
	dc.LineTo(r.right, r.bottom - 1);
	int axis_serifs;
	axis_serifs = 5;
	double step;
	step = (scale_x.to - scale_x.from) / (axis_serifs + 1);
	for (int i = 1; i * step < scale_x.to - scale_x.from; i++) {
		long x = round(i * step / (scale_x.to - scale_x.from) * r.right);
		dc.MoveTo(x, r.bottom);
		dc.LineTo(x, r.bottom - 10);
		double l = i * step + scale_x.from;
		CString str;
		str.Format(L"%5.2f", l);
		dc.TextOutW(x - 20, r.bottom - 30, str);
	}
	axis_serifs = 4;
	step = (scale_y.to - scale_y.from) / (axis_serifs + 1);
	for (int i = 1; i * step < scale_y.to - scale_y.from; i++) {
		long y = round(r.bottom - i * step / (scale_y.to - scale_y.from) * r.bottom);
		dc.MoveTo(0, y);
		dc.LineTo(10, y);
		double l = i * step + scale_y.from;
		if (is_log) { l = pow(10, l); }
		CString str;
		str.Format(L"%5.2f", l);
		dc.TextOutW(15, y - 10, str);
	}

	dc.SelectObject(oldpen);
}

void CMyGraph::setScale(double x_from, double x_to, double y_from, double y_to) {
	this->scale_x = { x_from,x_to };
	this->scale_y = { y_from,y_to };
	for (MathFunction* f : functions) {
		f->set_scale(x_from, x_to, y_from, y_to);
	}
}

void CMyGraph::setStep(double step) {
	for (MathFunction* f : functions) {
		f->set_step(step);
	}
}

void CMyGraph::setRect(RECT r) {
	for (MathFunction* f : functions) {
		f->set_rect(r);
	}
}

void CMyGraph::setLog(bool b) {
	this->is_log = b;
	for (MathFunction* f : functions) {
		f->set_log(b);
	}
}

void CMyGraph::setNotCalculated() {
	for (MathFunction* f : functions) {
		f->set_not_calculated();
	}
}
