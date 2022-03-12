#pragma once
#include <vector>
#include "PureFunction.h"
class MathFunction {
protected:
	PureFunction* funct;
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
	void set_function(PureFunction* funct);
	void set_step(double s);
	void set_rect(CRect r);
	void set_log(bool b);
	void set_color(COLORREF rgb);
	void set_not_calculated();
	const std::vector<POINT>& get_points();
protected:
	void calculate();
	POINT to_the_new_coords_system(double x, double y) const;
};

