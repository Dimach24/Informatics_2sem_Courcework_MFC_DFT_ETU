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
		double from, to;//scale
	}scale;
	std::vector<MathFunction> functions;
	CMyGraph();
	virtual ~CMyGraph();

protected:
	/// <summary>
	/// Draws the function from this->functions[local_function_id]
	/// </summary>
	/// <param name="local_fuction_id"> - index in this graph functions vector</param>
	void drawTheFunction(size_t local_fuction_id);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


