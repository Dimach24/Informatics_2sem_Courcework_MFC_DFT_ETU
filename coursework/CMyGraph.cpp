// CMyGraph.cpp: файл реализации
//

#include "pch.h"
#include "coursework.h"
#include "CMyGraph.h"


// CMyGraph

IMPLEMENT_DYNAMIC(CMyGraph, CStatic)

void CMyGraph::draw_axis(CDC& dc) {
	CRect r;
	GetClientRect(r);
	if (!background_calculated) {
		if (!bgdc) {
			bgdc.CreateCompatibleDC(&dc);
			bg_bmp.CreateCompatibleBitmap(&dc, r.Width(), r.Height());
		}
		old_bmp = bgdc.SelectObject(bg_bmp);
		bgdc.FillSolidRect(&r, bg_color);

		CPen pen(PS_SOLID,2,RGB(0,0,0));
		HGDIOBJ oldpen = bgdc.SelectObject(pen);

		bgdc.MoveTo(shift.x, 0);
		bgdc.LineTo(shift.x, r.bottom - shift.y);
		bgdc.LineTo(r.Width(), r.bottom - shift.y);
		

		int sstepx = (r.right - shift.x) / serifs.x;
		int sstepy = (r.right - shift.y)/serifs.y;
		for (int sn = 1, scord=shift.x; sn <= serifs.x; sn += 1, scord+=sstepx) {

		}



		bgdc.SelectObject(oldpen);
		background_calculated = true;
	}
	dc.BitBlt(0, 0, r.Width(), r.Height(), &bgdc, 0, 0, SRCCOPY);
}

CMyGraph::CMyGraph()
	:CStatic(),
	scale_x(), scale_y() {
}

CMyGraph::~CMyGraph() {
	bgdc.SelectObject(old_bmp);
}






BEGIN_MESSAGE_MAP(CMyGraph, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// Обработчики сообщений CMyGraph


void CMyGraph::OnPaint() {
	CPaintDC dc(this);
	draw_axis(dc);
	CPen gr(BS_SOLID, 1, RGB(0, 0, 0));
	HGDIOBJ oldpen = dc.SelectObject(gr);
	RECT r;
	GetWindowRect(&r);
	r = { 0,0,r.right - r.left,r.bottom - r.top };
	CRect rforf(r);
	rforf.left += shift.x;
	rforf.bottom -= shift.y;
	dc.IntersectClipRect(&rforf);
	for (MathFunction* f : functions) {
		bool is_first = true;
		CPen gr(BS_SOLID, 1, f->color);
		dc.SelectObject(gr);
		for (POINT dot : f->get_points()) {
			if (hist) {
				dc.MoveTo(dot.x, r.bottom - shift.y);
				dc.LineTo(dot);
			} else {
				if (is_first) { dc.MoveTo(dot); is_first = false; } else {
					dc.LineTo(dot);
				}
			}
		}
	}

	dc.SelectObject(oldpen);
}

void CMyGraph::setScale(double x_from, double x_to, double y_from, double y_to) {
	if (x_from != scale_x.from || x_to != scale_x.to || y_from != scale_y.from || y_to != scale_y.to) {
		background_calculated = false;
	}
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
	r.bottom -= shift.x;
	r.left += shift.x;
	for (MathFunction* f : functions) {
		f->set_rect(r);
	}
}

void CMyGraph::setLog(bool b) {
	if (b != is_log) {
		background_calculated = false;
	}
	this->is_log = b;
	for (MathFunction* f : functions) {
		f->set_log(b);
	}
}

void CMyGraph::setNotCalculated() {
	background_calculated = false;
	for (MathFunction* f : functions) {
		f->set_not_calculated();
	}
}

void CMyGraph::setBgColor(COLORREF col) {
	if (col != bg_color) {
		background_calculated = false;
		bg_color = col;
	}
}
