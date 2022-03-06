#include "pch.h"
#include "PureFunction.h"
#define PI 3.141592653589793238463
SignalFunction::SignalFunction(double a, double m, double f)
{
	this->a = a;
	this->m = m;
	this->f = f;
}

double SignalFunction::calc(double x)
{
	return a*sin(2*PI*(f+m*x)*x);
}
