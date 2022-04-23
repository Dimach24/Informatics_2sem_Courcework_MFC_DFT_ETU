// CMyGraph.cpp: файл реализации
//

#include "pch.h"
#include "coursework.h"
#include "CMyGraph.h"


// CMyGraph

IMPLEMENT_DYNAMIC(CMyGraph, CStatic)

std::pair<float, float> CMyGraph::dotToCoords(int wx, int wy) {
	CRect r;
	GetClientRect(r);
	r.left += shift.x;
	r.bottom -= shift.y;
	double x, y;
	wy = r.bottom - wy;
	wx -= shift.x;
	y = wy * (scale_y.to - scale_y.from) / r.Height() + scale_y.from;
	x = wx * (scale_x.to - scale_x.from) / r.Width() + scale_x.from;



	return std::make_pair(x, y);
}

POINT CMyGraph::coordsToDot(double x, double y) {

	CRect rect;
	GetClientRect(&rect);

	//
	rect.left += shift.x;
	rect.bottom -= shift.y;

	// shifting in the math coords
	x = x - scale_x.from;
	y = y - scale_y.from;

	// scaling
	x = x * rect.Width() / (scale_x.to - scale_x.from);
	y = -(y * rect.Height() / (scale_y.to - scale_y.from));

	// shifting in win coords
	x += rect.left;
	y += rect.bottom;

	return POINT({ (long)round(x), (long)round(y) });
}

void CMyGraph::drawBg(CDC& dc) {
	CRect r;
	GetClientRect(r);
	
	dc.FillSolidRect(&r, bg_color);

	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
	HGDIOBJ oldpen = dc.SelectObject(pen);

	dc.MoveTo(shift.x, 0);
	dc.LineTo(shift.x, r.bottom - shift.y);
	dc.LineTo(r.Width(), r.bottom - shift.y);


	CFont font;
	font.CreateFontW(18, 0, 0, 0, FW_NORMAL, 0, 0, 0,
		DEFAULT_CHARSET, OUT_RASTER_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH || FF_ROMAN, _T("Times"));
	CFont pfont;
	pfont.CreateFontW(14, 0, 0, 0, FW_NORMAL, 0, 0, 0,
		DEFAULT_CHARSET, OUT_RASTER_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH || FF_ROMAN, _T("Times"));

	HGDIOBJ oldfont = dc.SelectObject(font);



	double step = (scale_x.to - scale_x.from) / (serifs.x);
	for (int i = 0; i <= serifs.x; i++) {
		double the_x = i * step + scale_x.from;
		CPoint sp = coordsToDot(the_x, scale_y.from);
		sp.Offset(0, -serifsize / 2);
		dc.MoveTo(sp);
		sp.Offset(0, serifsize);
		dc.LineTo(sp);
		sp.Offset(0, 4);
		CString st = L"Что-то пошло не так!";
		st.Format(L"%.4g", the_x);
		dc.SetTextAlign(TA_CENTER);
		dc.TextOutW(sp.x, sp.y, st);
	}

	if (!is_log) {
		step = (scale_y.to - scale_y.from) / (serifs.y);
		for (int i = 0; i <= serifs.y; i++) {
			double the_y = i * step + scale_y.from;
			CPoint sp = coordsToDot(scale_x.from, the_y);
			sp.Offset(serifsize / 2, 0);
			dc.MoveTo(sp);
			sp.Offset(-serifsize, 0);
			dc.LineTo(sp);
			sp.Offset(-40, -1);
			CString st = L"Что-то пошло не так!";
			st.Format(L"%.4g", the_y);
			dc.SetTextAlign(TA_TOP);
			dc.TextOutW(sp.x, sp.y, st);
		}
	} else {	// log scale
		int start_power = ceil(scale_y.from),
			stop_power = ceil(scale_y.to),
			step_power = ceil(((double)stop_power - start_power) / (serifs.y));
		for (int i = 0; i <= serifs.y; i++) {
			int current_power = i * step_power + start_power;
			double the_y = pow(10, (double)current_power);
			CPoint sp = coordsToDot(scale_x.from, log10(the_y));
			sp.Offset(serifsize / 2, 0);
			dc.MoveTo(sp);
			sp.Offset(-serifsize, 0);
			dc.LineTo(sp);
			sp.Offset(-40, -5);
			CString st = L"10";
			/*st.Format(L"%.4g", the_y);*/
			dc.SetTextAlign(TA_TOP);
			dc.TextOutW(sp.x, sp.y, st);
			sp.Offset(16, -5);
			dc.SelectObject(pfont);
			st.Format(L"%d", current_power);
			dc.SetTextAlign(TA_LEFT);
			dc.TextOutW(sp.x, sp.y, st);
			dc.SelectObject(font);
		}
	}

	dc.SelectObject(oldfont);
	dc.SelectObject(oldpen);
	background_calculated = true;
}

void CMyGraph::drawGraph(CDC& dc) {//FIXME//TODO
	CPen gr(BS_SOLID, 1, RGB(0, 0, 0));
	HGDIOBJ oldpen = dc.SelectObject(gr);
	CRect r;
	GetWindowRect(&r);
	r = { 0,0,r.right - r.left,r.bottom - r.top };
	dc.BitBlt(0, 0, r.Width(), r.Height(), &bgdc, 0, 0, SRCCOPY);

	CRect rforf(r);
	rforf.left += shift.x;
	rforf.bottom -= shift.y;

	CRgn rgnf;
	rgnf.CreateRectRgn(rforf.left, rforf.top, rforf.right, rforf.bottom);
	dc.SelectClipRgn(&rgnf);
	
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
	CRgn rgn;
	rgn.CreateRectRgn(r.left, r.top, r.right, r.bottom);
	dc.SelectClipRgn(&rgn);
}

CMyGraph::CMyGraph()
	:CStatic(),
	scale_x(), scale_y() {
}

CMyGraph::~CMyGraph() {
	bgdc.SelectObject(old_bmp);
	graph_dc.SelectObject(old_g_bmp);
}






BEGIN_MESSAGE_MAP(CMyGraph, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()




void CMyGraph::OnPaint() {
	CPaintDC dc(this);
	CRect r;
	GetClientRect(r);
	if (!graph_is_done) {

		if (!bgdc) {
			bgdc.CreateCompatibleDC(&dc);
			bg_bmp.CreateCompatibleBitmap(&dc, r.Width(), r.Height());
			old_bmp = bgdc.SelectObject(bg_bmp);
		}

		if (!background_calculated) {
			drawBg(bgdc);
		}
		if (!graph_dc) {
			graph_dc.CreateCompatibleDC(&dc);
			graph.CreateCompatibleBitmap(&dc, r.Width(), r.Height());
			old_g_bmp = graph_dc.SelectObject(graph);
		}
		drawGraph(graph_dc);
	}
	dc.BitBlt(0, 0, r.Width(), r.Height(), &graph_dc, 0, 0, SRCCOPY);
}


// setters


void CMyGraph::setScale(double x_from, double x_to, double y_from, double y_to) {
	if (x_from != scale_x.from || x_to != scale_x.to || y_from != scale_y.from || y_to != scale_y.to) {
		background_calculated = false;
		graph_is_done = false;
	}
	this->scale_x = { x_from,x_to };
	this->scale_y = { y_from,y_to };
	for (MathFunction* f : functions) {
		f->setScale(x_from, x_to, y_from, y_to);
	}
}

void CMyGraph::setStep(double step) {
	graph_is_done = false;
	for (MathFunction* f : functions) {
		f->setStep(step);
	}
}

void CMyGraph::setRect(RECT r) {
	r.bottom -= shift.x;
	r.left += shift.x;
	for (MathFunction* f : functions) {
		f->setRect(r);
	}
}

void CMyGraph::setLog(bool b) {
	if (b != is_log) {
		graph_is_done = false;
		background_calculated = false;
	}
	this->is_log = b;
	for (MathFunction* f : functions) {
		f->setLog(b);
	}
}

void CMyGraph::setNotCalculated() {
	graph_is_done = false;
	background_calculated = false;
	for (MathFunction* f : functions) {
		f->setNotCalculated();
	}
}

void CMyGraph::setBgColor(COLORREF col) {
	if (col != bg_color) {
		graph_is_done = false;
		background_calculated = false;
		bg_color = col;
	}
}

