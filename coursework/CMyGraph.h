#pragma once
#include <vector>

// CMyGraph

class CMyGraph : public CStatic
{
	DECLARE_DYNAMIC(CMyGraph)

public:
	struct MathFunction {
		double(* f)(double x);
		struct {
			double from, to;
		}definition_scope;
		double step;
		struct { uint8_t r, g, b; } rgb;
	};
	struct {
		double from, to;
	}scale_x, scale_y;
	bool is_log;
	std::vector<MathFunction> functions;
	CMyGraph();
	virtual ~CMyGraph();

protected:
	std::pair<double,double> CalculateDot(double x, double y, long width, long heigth);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


