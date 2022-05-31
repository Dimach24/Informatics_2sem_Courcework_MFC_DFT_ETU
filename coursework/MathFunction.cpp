//
// MathFunction.cpp
//


#include <math.h> // for math like sin, log, etc
#include <cassert>// for asserts

// including project files
#include "pch.h"
#include "MathFunction.h"

void MathFunction::setNotCalculated() {
	// turn is calculated indicator to false
	is_calculated = false;
}

bool MathFunction::setScale(double x_from, double x_to, double y_from, double y_to) {
	// if scale is not changed return false
	if (x_from == scale.x_from && y_from == scale.y_from &&
		x_to == scale.x_to && y_to == scale.y_to) {
		return false;
	}
	// else
	setNotCalculated();
	// construct and assign scale
	scale = { x_from, x_to, y_from, y_to };
	return true;
}

bool MathFunction::setDefinitionScope(double from, double to) {
	// if scale is not changed return false
	if (from == this->from && to == this->to) { return false; }
	// else
	setNotCalculated();
	// assign the scope
	this->from = from;
	this->to = to;
	return true;
}

bool MathFunction::setStep(double s) {
	// if step is not changed return false
	if (step == s) { return false; }
	// else
	setNotCalculated();
	// assign step
	step = s;
	return true;
}

bool MathFunction::setRect(CRect r) {
	// if drawing area isn't changed return false
	if (r.left == rect.left && r.right == rect.right &&
		r.top == rect.top && r.bottom == rect.bottom) {
		return false;
	}
	//else
	setNotCalculated();
	// assign drawing rect
	rect = r;
	return true;
}

bool MathFunction::setLog(bool b) {
	// if log indicator is not changed return false
	if (b == is_log) { return false; }
	// else
	setNotCalculated();
	// assign indicator
	is_log = b;
	return true;
}

void MathFunction::setColor(COLORREF rgb) {
	// set the color
	color = rgb;
}

bool MathFunction::getCalculated() {
	return is_calculated;
}

const std::vector<POINT>& MathFunction::get_points() {
	// if vector is not ready
	if (!is_calculated) {
		calculate();	// calculate
	}
	return points;		// return the vector
}

POINT MathFunction::coordsToDot(double x, double y) const {
	// coord shifting to the coords with zero in (x_from,y_from)
	double shifted_x = x - scale.x_from;
	double shifted_y = y - scale.y_from;
	// multiplication with scale coefs +-.../(... - ...)
	// makes the distance between 2 points correct 
	// and shifting makes (x_from, y_from) be in the left bottom corner
	x = rect.left + shifted_x * rect.Width() / (scale.x_to - scale.x_from);
	y = rect.bottom - shifted_y * rect.Height() / (scale.y_to - scale.y_from);

	// create point and return it
	return POINT({ (long)round(x), (long)round(y) });
}

void MathFunction::calculate() {
	// calculating range calculating
	double start = max(scale.x_from, from);
	double stop = min(scale.x_to, to);

	// reserving memory for the points
	points.resize(ceil((stop - start) / step));

	// for points with the step
	for (size_t i = 0; i < points.size(); i++) {
		double x = start + step * i;	// calculating x of the point (progression)
		double y = f(x);				// calculating y of the point
		if (is_log) {					// if log scale
			y = log10(abs(y));			// calculate log of y
		}
		points[i] = coordsToDot(x, y);	// coord conversion
	}
	is_calculated = true;				// set calculated
}

const double SignalFunction::samples_step = 1e-7;	// const initialization

double SignalFunction::f(double t) {
	// signal function ↓
	return a * sin(2 * M_PI * (f_ + m * t) * t);
}

bool SignalFunction::set_a(double a) {
	// if 'a' is not changed return false
	if (a == this->a) { return false; }
	// else
	setNotCalculated();
	// change the 'a'
	this->a = a;
	return true;
}

bool SignalFunction::set_m(double m) {
	// like with 'a' param
	if (m == this->m) { return false; }
	setNotCalculated();
	this->m = m;
	return true;
}

bool SignalFunction::set_f(double f) {
	// like with 'a' param
	if (f == this->f_) { return false; }
	setNotCalculated();
	this->f_ = f;
	return true;
}

bool SignalFunction::set_samples_amount(size_t N) {
	// check if not changed
	if (samples_amount == N) { return false; }
	// mark as irrelevant
	setNotCalculated();
	// set
	samples_amount = N;
	// return that there was difference
	return true;
}

const std::vector<double>& SignalFunction::getData() {
	// if data is not relevant
	if (!is_calculated) {
		calculate();	// update data
	}
	return samples;		// return it
}

void SignalFunction::calculate() {
	// calculating scope of the calculating
	double start = max(scale.x_from, from);
	double stop = min(scale.x_to, to);


	// memory reserving for the samples data 
	samples.resize(samples_amount);

	// repeat for each i = 0, 1, ..., samples_amount-1
	for (int i = 0; i < samples_amount; i++) {
		// calculate x (like an arithmetic progression)
		// calculate f(x)
		// write f(x) to the samples vector
		samples[i] = f(i * samples_step + start);
	}

	// amount of dots on the graph calculation
	int N = ceil((stop - start) / step);

	// memory reserving for the points vector
	points.resize(N);

	// repeat for each i = 0, 1, ..., N
	for (int i = 0; i < N; i++) {

		// calculate x (like an arithmetic progression)
		double x = i * step + start;
		// calculate f(x)
		double y = f(x);

		// use logarithm if needed
		if (is_log) { y = log10(y); }

		// converse coords and write 
		// the point to the vector
		points[i] = coordsToDot(x, y);
	}


	// mark as calculated
	is_calculated = true;

}

DFTFunction::DFTFunction(SignalFunction* s) {
	// assign the pointer to signal function 
	signal = s;
}

double DFTFunction::f(int m) {
#ifdef __DEBUG
	assert(signal);	// must exist
#endif
	// getting signal function samples 
	std::vector<double> samples = signal->getData();

	// amount of samples
	size_t N = samples.size();

	// real and imaginary parts
	double re = 0, im = 0;

	// for each sample
	for (size_t n = 0; n < N; n++) {
		// summing
		re += samples[n] * cos(2 * M_PI * m * n / N);
		im += samples[n] * sin(-2 * M_PI * m * n / N);
	}
	// return the abs(X)
	return sqrt(re * re + im * im);
}

void DFTFunction::calculate() {
	// calculating scope calculating
	double start = max(scale.x_from, from);
	double stop = min(scale.x_to, to);
	// memory reserving for points
	points.resize(samples_amount);

	// for each point with the step
	for (size_t i = 0; i < samples_amount; i++) {
		// calculating f=Fд*k/N 
		double x = 1. / samples_step * i / samples_amount;
		double y = f(i);				// calculating y of the point abs(DFT)
		if (is_log) {					// if log scale enabled
			y = log10(abs(y));			// calculate log
		}
		points[i] = coordsToDot(x, y);	// coord conversion
	}
	is_calculated = true;				// mark points as relevant
}

void DFTFunction::set_signal(SignalFunction* s) {
	signal = s;			// set signal
	setNotCalculated();	// set not relevant
}

