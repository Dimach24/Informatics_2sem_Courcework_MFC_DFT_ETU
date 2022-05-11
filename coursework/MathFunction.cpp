#include "pch.h"
#include "MathFunction.h"
#include <cmath>

void MathFunction::setNotCalculated() {
	is_calculated = false;
}

bool MathFunction::setScale(double x_from, double x_to, double y_from, double y_to) {
	if (x_from == scale.x_from && y_from == scale.y_from && x_to == scale.x_to && y_to == scale.y_to) { return false; }
	setNotCalculated();
	scale = { x_from, x_to, y_from, y_to };
	return true;
}

bool MathFunction::setDefinitionScope(double from, double to) {
	if (from == this->from && to == this->to) { return false; }
	setNotCalculated();
	this->from = from;
	this->to = to;
	return true;
}

bool MathFunction::setStep(double s) {
	if (step == s) { return false; }
	setNotCalculated();
	step = s;
	return true;
}

bool MathFunction::setRect(CRect r) {
	if (r.left == rect.left && r.right == rect.right && r.top == rect.top && r.bottom == rect.bottom) { return false; }
	setNotCalculated();
	rect = r;
	return true;
}

bool MathFunction::setLog(bool b) {
	if (b == is_log) { return false; }
	setNotCalculated();
	is_log = b;
	return true;
}

void MathFunction::setBgColor(COLORREF rgb) {
	color = rgb;
}

bool MathFunction::getCalculated() {
	return is_calculated;
}

const std::vector<POINT>& MathFunction::get_points() {
	if (!is_calculated) {
		calculate();
	}
	return points;
}

POINT MathFunction::coordsToDot(double x, double y) const {
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
		points[i] = coordsToDot(x, y);
	}
	is_calculated = true;
}

double SignalFunction::f(double t) {
	return a * sin(2 * PI * (f_ + m * t) * t);
}

bool SignalFunction::set_a(double a) {
	if (a == this->a) { return false; }
	setNotCalculated();
	this->a = a;
	return true;
}

bool SignalFunction::set_m(double m) {
	if (m == this->m) { return false; }
	setNotCalculated();
	this->m = m;
	return true;
}

bool SignalFunction::set_f(double f) {
	if (f == this->f_) { return false; }
	setNotCalculated();
	this->f_ = f;
	return true;
}

const std::vector<double>& SignalFunction::getData() {
	if (!is_calculated) {
		calculate();
	}
	return data;
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
		points[i] = coordsToDot(x, y);
	}
	is_calculated = true;
}

DFTFunction::DFTFunction(SignalFunction* s) {
	signal = s;
}

double DFTFunction::f(double x) {
	assert(signal);
	size_t m = x;
	std::vector<double> data = signal->getData();
	size_t N = data.size();
	double re = 0, im = 0;
	for (size_t n = 0; n < N; n++) {
		re += data[n] * cos(2 * PI * m * n / N);
		im += data[n] * sin(-2 * PI * m * n / N);
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
		points[i] = coordsToDot(x, y);
	}
	is_calculated = true;
}

void DFTFunction::set_signal(SignalFunction* s) {
	signal = s;
	setNotCalculated();
}

