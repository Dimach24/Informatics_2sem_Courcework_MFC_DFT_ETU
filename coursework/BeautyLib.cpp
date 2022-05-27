//
// BeautyLib.cpp
//

#include "pch.h"
#include "BeautyLib.h"

#include <cmath>

CString beautifulRepresentation(double number, int exponent /* = 3 */, int after_dot /* = 4 */) {
	// place for result
	CString res;

	// getting the significant and exponent of a number
	auto me = getME(number);

	// string for a number format
	CString format;
	// setting the format
	format.Format(L"%s%d%c", L"%.", after_dot, L'f');
	// if hight bound reached
	if (abs(me.second) > exponent) {
		// setting brackets for negative
		if (me.second < 0) {
			format += L"\u221910^(%d)";
		} else {
			format += L"\u221910^%d";
		}
		// formatting result in exp mode
		res.Format(format, me.first, me.second);
	} else {
		// formatting result in regular mode
		res.Format(format, number);
	}

	return res;
}

std::pair<double, int> getME(double number) {
	
	/*       n = m * 10^(e)                */
	
	// if zero return zero
	if (number == 0) {
		return std::make_pair(0., 0);
	}
	// place for result
	double m;
	int e;

	// lg(n) = lg(m) + e, lg(m) < 1
	e = floor(log10(abs(number)));
	// m = n / 10^(e)
	m = number / pow(10, e);

	// return the result
	return std::make_pair(m, e);
}
