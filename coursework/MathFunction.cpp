#include "pch.h"
#include "MathFunction.h"
#include <cmath>

void MathFunction::set_not_calculated() {
	is_calculated = false;
}

void MathFunction::set_scale(double x_from, double x_to, double y_from, double y_to) {
	if (x_from == scale.x_from && y_from == scale.y_from && x_to == scale.x_to && y_to == scale.y_to) { return; }
	set_not_calculated();
	scale = { x_from, x_to, y_from, y_to };
}

void MathFunction::set_definition_scope(double from, double to) {
	if (from == this->from && to == this->to) { return; }
	set_not_calculated();
	this->from = from;
	this->to = to;
}

void MathFunction::set_step(double s) {
	if (step == s) { return; }
	set_not_calculated();
	step = s;
}

void MathFunction::set_rect(CRect r) {
	if (r.left == rect.left && r.right == rect.right && r.top == rect.top && r.bottom == rect.bottom) { return; }
	set_not_calculated();
	rect = r;
}

void MathFunction::set_log(bool b) {
	if (b == is_log) { return; }
	set_not_calculated();
	is_log = b;
}

void MathFunction::set_color(COLORREF rgb) {
	color = rgb;
}

const std::vector<POINT>& MathFunction::get_points() {
	if (!is_calculated) {
		calculate();
	}
	return points;
}

POINT MathFunction::to_the_new_coords_system(double x, double y) const {
	double shifted_x = x - scale.x_from;
	double shifted_y = y - scale.y_from;
	x = rect.left + shifted_x * rect.Width() / (scale.x_to - scale.x_from);
	y = rect.bottom - shifted_y * rect.Height() / (scale.y_to - scale.y_from);
	return POINT({ (long)round(x), (long)round(y) });
}

void MathFunction::calculate() {
	double start = max(scale.x_from, from);
	double stop = min(scale.x_to, to);
	points.resize(ceil((stop - start) / step));
	for (size_t i = 0; i < points.size(); i++) {
		double x = start + step * i;	// calculating x of the point
		double y = f(x);				// calculating y of the point
		if (is_log) {
			y = log10(abs(y));
		}
		points[i] = to_the_new_coords_system(x, y);
	}
	is_calculated = true;
}

double SignalFunction::f(double x) {
	return a * sin(2 * PI * (f_ + m * x) * x);
}

void SignalFunction::set_a(double a) {
	if (a == this->a) { return; }
	set_not_calculated();
	this->a = a;
}

void SignalFunction::set_m(double m) {
	if (m == this->m) { return; }
	set_not_calculated();
	this->m = m;
}

void SignalFunction::set_f(double f) {
	if (f == this->f_) { return; }
	set_not_calculated();
	this->f_ = f;
}

void SignalFunction::calculate() {
	double start = max(scale.x_from, from);
	double stop = min(scale.x_to, to);
	points.resize(ceil((stop - start) / step));
	data.resize(points.size());
	for (size_t i = 0; i < points.size(); i++) {
		double x = start + step * i;	// calculating x of the point
		double y = f(x);				// calculating y of the point
		data[i] = y;
		if (is_log) {
			y = log10(abs(y));
		}
		points[i] = to_the_new_coords_system(x, y);
	}
	is_calculated = true;
}

DFTFunction::DFTFunction(SignalFunction* s) {
	signal = s;
}

double DFTFunction::f(double x) {
	size_t m = x;
	size_t N = signal->data.size();
	double re = 0, im = 0;
	for (size_t n = 0; n < N; n++) {
		re += signal->data[n] * cos(2 * PI * m * n / N);
		im += signal->data[n] * sin(-2 * PI * m * n / N);
	}
	return sqrt(re * re + im * im);
}

void DFTFunction::calculate() {
	double start = max(scale.x_from, from);
	double stop = min(scale.x_to, to);
	points.resize(ceil((stop - start) / step));
	for (size_t i = 0; i < points.size(); i++) {
		double x = start + step * i;	// calculating x of the point
		double y = f(i);				// calculating y of the point
		if (is_log) {
			y = log10(abs(y));
		}
		points[i] = to_the_new_coords_system(x, y);
	}
	is_calculated = true;
}

void DFTFunction::set_signal(SignalFunction* s) {
	signal = s;
}
