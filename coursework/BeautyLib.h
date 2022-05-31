//
// BeautyLib.h
//

#pragma once
#include <atlstr.h> // for CString
#include <utility>	// for std::pair

/// <summary>
/// Returns formatted string (if it needed) like '123.1234*10^3'
/// </summary>
/// <param name="number">the number</param>
/// <param name="exponent">sets the hight bound of 
/// the regular number mode. When the exponent of the number
/// will be greater than it (or less then the negative exp)
/// there will be used exponential notation</param>
/// <param name="after_dot">amount of digits after the dot</param>
/// <returns>formatted string</returns>
CString beautifulRepresentation(double number, int exponent = 3, int after_dot = 4);

/// <summary>
/// Returns the significant and 
/// the exponent (decimal) of the number
/// </summary>
/// <param name="number">the number</param>
/// <returns>pair of significant and exponent</returns>
std::pair<double, int> getME(double number);
