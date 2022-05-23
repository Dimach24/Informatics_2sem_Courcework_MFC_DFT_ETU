
#include "pch.h"
#include "BeautyLib.h"

#include <cmath>

CString beautifulRepresentation(double number, int exponent /* = 3 */, int after_dot /* = 4 */) {
	CString res;
	auto me = getME(number);
	CString format;
	auto mme = getME(me.first);
	format.Format(L"%s%d%c", L"%.", after_dot, L'f');
	if (abs(me.second) > exponent) {
		if (me.second < 0) {
			format += L"*10^(%d)";
			res.Format(format, me.first, me.second);
		} else {
			format += L"*10^%d";
			res.Format(format, me.first, me.second);
		}
	} else {
		res.Format(format, number);
	}

	return res;
}

std::pair<double, int> getME(double number) {
	if (number == 0) {
		return std::make_pair(0., 0);
	}
	double m;
	int e;

	e = floor(log10(abs(number)));
	m = number / pow(10, e);

	return std::make_pair(m, e);
}
