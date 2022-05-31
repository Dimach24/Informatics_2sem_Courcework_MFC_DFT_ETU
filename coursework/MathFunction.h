//
// MathFunction.h
//

#pragma once		// include this file once

#include <vector>	// vector of dots/points


/// <summary>
/// class defines type of object that will be
/// drawed in CMyGraph element
/// </summary>
class MathFunction
{
protected:
	/// <summary>
	/// deafult dot calculation function
	/// is used in default points calculation function
	/// </summary>
	/// <param name="x">argument</param>
	/// <returns>function value in the x</returns>
	virtual  double f(double x) = 0;
	// pure virtual function (must be defined in subclasses)

	// definition scope
	double from, to;

	// calculating step (in math coords)
	double step = 1;


	// indicates if axis is log
	bool is_log;

	// calculating scope
	struct
	{
		double x_from, x_to;
		double y_from, y_to;
	}scale;

	// indicates if vector is ready
	bool is_calculated = false;

	// drawing area
	CRect rect;

	// vector of the points
	std::vector<POINT> points;
public:
	// color on the graph
	COLORREF color;
public:
	// setters
	bool setScale(double x_from, double x_to, double y_from, double y_to);
	bool setDefinitionScope(double from, double to);
	bool setStep(double s);
	bool setRect(CRect r);
	bool setLog(bool b);
	void setColor(COLORREF rgb);
	void setNotCalculated();
	// getters
	bool getCalculated();
	virtual const std::vector<POINT>& get_points();
protected:
	/// <summary>
	/// calculates vector of the points
	/// </summary>
	virtual void calculate();

	/// <summary>
	/// math coords to the element coords conversion
	/// </summary>
	/// <param name="x">x coord</param>
	/// <param name="y">y coord</param>
	/// <returns>POINT in element coords</returns>
	POINT coordsToDot(double x, double y) const;
};

/// <summary>
/// Subclass that defines signal function like x(t)=a*sin(x*(m*x+f))
/// </summary>
class SignalFunction : public MathFunction
{
protected:
	// parameters of the signal function
	double a, m, f_;
	// samples amount
	size_t samples_amount = 100;
	static const double samples_step;	
	// vector of the dots for DFT
	std::vector<double> samples;
protected:
	/// <summary>
	/// Calculates x(t)=a*sin(x*(m*x+f))
	/// </summary>
	/// <param name="t"></param>
	/// <returns>x(t)</returns>
	virtual double f(double t) override;
public:
	// setters
	bool set_a(double a);
	bool set_m(double m);
	bool set_f(double f);
	bool set_samples_amount(size_t N);
	// dots vector getter
	const std::vector<double>& getData();

	// overriding of the parent calculation function
	virtual void calculate() override;
};

/// <summary>
/// Subclass that defines DFT for signal function
/// </summary>
class DFTFunction : public SignalFunction
{
public:
	/// <summary>
	/// Constructs the class
	/// </summary>
	/// <param name="s">a pinter to the SignalFunction - signal function</param>
	DFTFunction(SignalFunction* s = nullptr);
protected:
	/// <summary>
	/// calculates one sample
	/// </summary>
	/// <param name="x">number of the sample (is double cos of overriding)</param>
	/// <returns>|Xk|</returns>
	double f(int m);

	// a pointer to a signal function
	SignalFunction* signal;
public:
	// calculation overriding
	void calculate() override;
	// signal function setter
	void set_signal(SignalFunction* s);

};