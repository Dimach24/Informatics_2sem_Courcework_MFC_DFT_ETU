#include "pch.h"
#include "MathFunction.h"

void MathFunction::set_scale(double x_from, double x_to, double y_from, double y_to)
{
	if (x_from == scale.x_from && y_from == scale.y_from && x_to == scale.x_to && y_to == scale.y_to) { return; }
	is_calculated = false;
	scale = { x_from, x_to, y_from, y_to };
}

void MathFunction::set_definition_scope(double from, double to)
{
	if (from == this->from && to == this->to) { return; }
	is_calculated = false;
	this->from = from;
	this->to = to;
}

void MathFunction::set_function(PureFunction* funct)
{
	is_calculated = false;
	this->funct = funct;
}

void MathFunction::set_step(double s)
{
	if (step == s) { return; }
	is_calculated = false;
	step = s;
}

void MathFunction::set_rect(CRect r)
{
	if (r.left == rect.left && r.right == rect.right && r.top == rect.top && r.bottom == rect.bottom) { return; }
	is_calculated = false;
	rect = r;
}

void MathFunction::set_log(bool b)
{
	if (b == is_log) { return; }
	is_calculated = false;
	is_log = b;
}

void MathFunction::set_color(COLORREF rgb)
{
	color = rgb;
}

void MathFunction::set_not_calculated()
{
	is_calculated = false;
}

const std::vector<POINT>& MathFunction::get_points()
{
	if (!is_calculated) {
		calculate();
	}
	return points;
}


void MathFunction::calculate() {
	double start = max(scale.x_from, from);
	double stop = min(scale.x_to, to);
	points.resize(floor((stop - start) / step));
	for (size_t i = 0; i < points.size(); i++) {
		double x = start + step * i;	// calculating x of the point
		double y = funct->calc(x);				// calculating y of the point
		if (is_log) { y = log(y); }
		points[i] = to_the_new_coords_system(x, y);
	}
	is_calculated = true;
}

POINT MathFunction::to_the_new_coords_system(double x, double y) const
{
	double shifted_x = x - scale.x_from;
	double shifted_y = y - scale.y_from;
	x = rect.left + shifted_x * rect.Width() / (scale.x_to - scale.x_from);
	y = rect.bottom - shifted_y * rect.Height() / (scale.y_to - scale.y_from);
	return POINT({ (long)round(x), (long)round(y) });
}
