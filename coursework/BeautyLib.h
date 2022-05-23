#pragma once
#include <atlstr.h> // for CString
#include <utility>	// for std::pair


CString beautifulRepresentation(double number, int exponent = 3, int after_dot = 4);

std::pair<double, int> getME(double number);