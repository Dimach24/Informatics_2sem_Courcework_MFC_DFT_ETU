#pragma once
class PureFunction
{
public:
	virtual double calc(double x) = 0;
};

class SignalFunction :public PureFunction {
public:
	SignalFunction(double a, double m, double f);
	double a, m, f;
	double calc(double x);
};