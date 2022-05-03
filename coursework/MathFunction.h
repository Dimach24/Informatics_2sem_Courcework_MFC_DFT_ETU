#pragma once
#include <vector>
#define PI 3.141592653589793238463
class MathFunction
{
protected:
	virtual  double f(double x) = 0;
	double from, to;
	double step=1;

	bool is_log;
	struct
	{
		double x_from, x_to;
		double y_from, y_to;
	}scale;
	bool is_calculated = false;
	CRect rect;
	std::vector<POINT> points;
public:
	COLORREF color;
public:
	bool setScale(double x_from, double x_to, double y_from, double y_to);
	bool setDefinitionScope(double from, double to);
	bool setStep(double s);
	bool setRect(CRect r);
	bool setLog(bool b);
	void setBgColor(COLORREF rgb);
	bool getCalculated();
	void setNotCalculated();
	virtual const std::vector<POINT>& get_points();
protected:
	virtual void calculate();
	POINT coordsToDot(double x, double y) const;
};

class SignalFunction : public MathFunction
{
protected:
	double a, m, f_;
public:
	std::vector<double> data;
protected:
	virtual double f(double x);
public:
	bool set_a(double a);
	bool set_m(double m);
	bool set_f(double f);
	const std::vector<double>& getData();
	virtual void calculate();
};
class DFTFunction : public SignalFunction
{
public:
	DFTFunction(SignalFunction* s);
protected:
	double f(double x);
	SignalFunction* signal;
public:
	void calculate();
	void set_signal(SignalFunction* s);

};