#pragma once
#include <atlstr.h> // for CString
#include <utility>	// for std::pair


CString beautifulRepresentation(double number, int digits=2);

std::pair<double, int> getME(double number);