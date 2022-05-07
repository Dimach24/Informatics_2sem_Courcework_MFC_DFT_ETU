// including project files
#include "pch.h"
#include "coursework.h"
#include "CMyGraph.h"


// for run0time data
IMPLEMENT_DYNAMIC(CMyGraph, CStatic)

std::pair<float, float> CMyGraph::dotToCoords(int wx, int wy, CRect r) {
	// shift left and botom borders to get calculating area
	r.left += shift.x;
	r.bottom -= shift.y;
	
	// place for result
	double x, y;

	// moving axis like the math ↑→ (but still in pixels)
	wy = r.bottom - wy;
	wx -= shift.x;

	// multiplying to scale coef: * (... - ...) / (...), shiting: + (...)
	y = wy * (scale_y.to - scale_y.from) / r.Height() + scale_y.from;
	x = wx * (scale_x.to - scale_x.from) / r.Width() + scale_x.from;
	// make pair and return it
	return std::make_pair(x, y);
}

POINT CMyGraph::coordsToDot(double x, double y, CRect rect) {
	// shifting bounds to get calculating area
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

	// create point from x and y and return it
	return POINT({ (long)round(x), (long)round(y) });
}

bool CMyGraph::timerTick() {
	// increase current phase
	current_animation_phase += animation_speed;

	// limit the phase
	if (current_animation_phase > 1) { current_animation_phase = 1; }
	
	// draw the frame with increased phase
	RedrawWindow();
	
	// return if the animation is stopped
	return current_animation_phase == 1;
}

void CMyGraph::drawBg(CDC& dc) {
	// getting client rect
	CRect r;
	GetClientRect(r);

	// filling with bg color
	dc.FillSolidRect(&r, bg_color);

	// set the pen and remember old object
	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
	HGDIOBJ oldpen = dc.SelectObject(pen);

	// draw axes
	dc.MoveTo(shift.x, 0);
	dc.LineTo(shift.x, r.bottom - shift.y);
	dc.LineTo(r.Width(), r.bottom - shift.y);

	// find font for the numbers and powers of 10
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

	// select font and remember old obj
	HGDIOBJ oldfont = dc.SelectObject(font);


	// calculate step in real (math) coords
	// (because back conv can give uncomfortable numbers)
	double step = (scale_x.to - scale_x.from) / (serifs.x);

	// for the serif
	for (int i = 0; i <= serifs.x; i++) {
		// calculate position (in math coords)
		// (arithmetic progression)
		double the_x = i * step + scale_x.from;

		// calculate position (in element coords)
		CPoint sp = coordsToDot(the_x, scale_y.from, r);
		
		// some moves to draw the serif with length=serifsize
		sp.Offset(0, -serifsize / 2);
		dc.MoveTo(sp);
		sp.Offset(0, serifsize);
		dc.LineTo(sp);
		sp.Offset(0, 4);

		// default text
		CString st = L"Что-то пошло не так!";
		
		// make the string consist of x coord rounded to 4 
		// significant digits
		st.Format(L"%.4g", the_x);
		
		// set text align
		dc.SetTextAlign(TA_CENTER);
		
		//show the text
		dc.TextOutW(sp.x, sp.y, st);
	}

	if (!is_log) { // same as with x axis
		step = (scale_y.to - scale_y.from) / (serifs.y);
		for (int i = 0; i <= serifs.y; i++) {
			double the_y = i * step + scale_y.from;
			CPoint sp = coordsToDot(scale_x.from, the_y, r);
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
		// progresiion with powers of 10
		int start_power = floor(scale_y.from),
			stop_power = ceil(scale_y.to),
			step_power = ceil(((double)stop_power - start_power) / (serifs.y));
		for (int i = 0; i <= serifs.y; i++) { // for power of 10
			// calculate the power
			int current_power = i * step_power + start_power;
			
			// calculate the y of the serif (in math coords)
			double the_y = pow(10, (double)current_power);
			
			// calculate in element coords
			CPoint sp = coordsToDot(scale_x.from, log10(the_y), r);

			// moves to draw serif
			sp.Offset(serifsize / 2, 0);
			dc.MoveTo(sp);
			sp.Offset(-serifsize, 0);
			dc.LineTo(sp);
			sp.Offset(-40, -5);
			
			// write '10'
			CString st = L"10";
			dc.SetTextAlign(TA_TOP);
			dc.TextOutW(sp.x, sp.y, st);
			
			// offset, change the font
			sp.Offset(16, -5);
			dc.SelectObject(pfont);

			// write the power
			st.Format(L"%d", current_power);
			dc.SetTextAlign(TA_LEFT);
			dc.TextOutW(sp.x, sp.y, st);

			// select normal font
			dc.SelectObject(font);
		}
	}

	// select old objects (get to the start state)
	dc.SelectObject(oldfont);
	dc.SelectObject(oldpen);

	// remember background as painted
	background_calculated = true;
}

void CMyGraph::drawGraph(CDC& dc) {

	// create pen, select it and remember old obj
	CPen gr(BS_SOLID, 1, RGB(0, 0, 0));
	HGDIOBJ oldpen = dc.SelectObject(gr);
	
	// get the client area borders
	CRect r;
	GetWindowRect(&r);
	r = { 0,0,r.right - r.left,r.bottom - r.top };

	// copy bg from the bitmap
	dc.BitBlt(0, 0, r.Width(), r.Height(), &bgdc, 0, 0, SRCCOPY);

	// calculating area
	CRect rforf(r);
	rforf.left += shift.x;
	rforf.bottom -= shift.y;

	// rgn for the clipping graph
	CRgn rgnf;
	rgnf.CreateRectRgn(rforf.left, rforf.top, rforf.right, rforf.bottom);
	dc.SelectClipRgn(&rgnf);

	// for each MathFunction like object in this graph
	for (MathFunction* f : functions) {

		// set that it's the first point
		bool is_first = true;
		
		// create pen for this function, and choose it
		CPen gr(BS_SOLID, 1, f->color);
		dc.SelectObject(gr);

		// get dots vector
		auto dots = f->get_points();

		//amount of dots
		size_t dots_count = dots.size();
		
		for (size_t i = 0; i < dots_count; i++) {
			
			// current dot from the dots
			CPoint dot(dots[i]);

			if (hist) {
				if (animation_in_process) {
					// recalc coords according to phase
					dot=recalcDotForAnimation(dot,rforf);
				}
				
				// hist column calculating and drawing
				RECT rect = {dot.x,dot.y,dot.x+step,rforf.bottom};
				dc.FillSolidRect(&rect, f->color);
			} else {// not hist
				if (is_first) {
					dc.MoveTo(dot);		//just move here not draw the line
					is_first = false;	// set not first
				} else {
					dc.LineTo(dot);		// draw the line
				}
				// if current phase means to stop drawing
				if (animation_in_process && i > dots_count*pow(dots_count,current_animation_phase-1)) {
					break; // stop drawing
				}
			}
		}
	}
	// restore dc state
	dc.SelectObject(oldpen);
	CRgn rgn;
	rgn.CreateRectRgn(r.left, r.top, r.right, r.bottom);
	dc.SelectClipRgn(&rgn);
}


void CMyGraph::draw(CDC& dc) {
	// getting client area
	CRect r;
	GetClientRect(r);

	// if graph isn't done
	if (!graph_is_done) {
		// if bgdc doesn't exist
		if (!bgdc) {
			// create dc and prepare it to drawing in bitmap
			bgdc.CreateCompatibleDC(&dc);
			bg_bmp.CreateCompatibleBitmap(&dc, r.Width(), r.Height());
			old_bmp = bgdc.SelectObject(bg_bmp);
		}

		// if bg isn't done
		if (!background_calculated) {
			// draw bg
			drawBg(bgdc);
		}
		// if graph_dc doesn't exist
		if (!graph_dc) {
			// create dc and prepare it to drawing in bitmap
			graph_dc.CreateCompatibleDC(&dc);
			graph.CreateCompatibleBitmap(&dc, r.Width(), r.Height());
			old_g_bmp = graph_dc.SelectObject(graph);
		}
		//draw the graph
		drawGraph(graph_dc);
	}
	// copy to passed as param dc
	dc.BitBlt(0, 0, r.Width(), r.Height(), &graph_dc, 0, 0, SRCCOPY);
}

CPoint CMyGraph::recalcDotForAnimation(CPoint p, const CRect& r) {
	// shift and reverse
	double y = r.bottom - p.y;

	// protection from small numbers
	if (y < 1) { p.y = r.bottom - y*current_animation_phase; return p; }
	
	//recalcing
	p.y = r.bottom-y*pow(y,current_animation_phase-1);
	
	return p;
}

CMyGraph::CMyGraph()	// default constructors call
	:CStatic(),
	scale_x(), scale_y() {
}

CMyGraph::~CMyGraph() {
	// dc's state restoring
	bgdc.SelectObject(old_bmp);
	graph_dc.SelectObject(old_g_bmp);
}





// message processing loop
BEGIN_MESSAGE_MAP(CMyGraph, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()




void CMyGraph::OnPaint() {
	// just draw it
	CPaintDC dc(this);
	draw(dc);
}



// setters,
// they set states (graph_is done, background calculated)
// according to changes

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

void CMyGraph::setStep(int step_) {
	if (this->step != step) {
		graph_is_done = false;
	}
	RECT r;
	GetClientRect(&r);
	double step = step_ * (scale_x.to - scale_x.from) / (r.right - r.left);
	this -> step = step_;
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

void CMyGraph::setAnimState(bool state) {
	current_animation_phase = 0;
	animation_in_process = state;
}

