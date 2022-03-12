#pragma once
#include <vector>
#define PI 3.141592653589793238463
class MathFunction {
protected:
	virtual  double f(double x) = 0;
	double from, to;
	double step;

	bool is_log;
	struct {
		double x_from, x_to;
		double y_from, y_to;
	}scale;
	bool is_calculated = false;
	CRect rect;
public:
	std::vector<POINT> points;
	COLORREF color;
public:
	void set_scale(double x_from, double x_to, double y_from, double y_to);
	void set_definition_scope(double from, double to);
	void set_step(double s);
	void set_rect(CRect r);
	void set_log(bool b);
	void set_color(COLORREF rgb);
	void set_not_calculated();
	const std::vector<POINT>& get_points();
protected:
	virtual void calculate();
	POINT to_the_new_coords_system(double x, double y) const;
};

class SignalFunction :MathFunction {
protected:
	double a, m, f;
public:
	std::vector<double> data;
protected:
	double f(double x);
public:
	void set_a(double a);
	void set_m(double m);
	void set_f(double f);
	void calculate();
};
class DFTFunction :MathFunction {
protected:
	double f(double x);
	SignalFunction* signal;
};