// CMyGraph.cpp: файл реализации
//

#include "pch.h"
#include "coursework.h"
#include "CMyGraph.h"


// CMyGraph

IMPLEMENT_DYNAMIC(CMyGraph, CStatic)

CMyGraph::CMyGraph()
{

}

CMyGraph::~CMyGraph()
{
}

//todo
std::pair<double, double> CMyGraph::CalculateDot(double x, double y, double width, double heigth)
{
	return std::pair<double, double>();
}




BEGIN_MESSAGE_MAP(CMyGraph, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// Обработчики сообщений CMyGraph




void CMyGraph::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: добавьте свой код обработчика сообщений
					   // Не вызывать CStatic::OnPaint() для сообщений рисования

	LPRECT wind_size;
	GetWindowRect(wind_size);
	for (auto function : functions) {
		double from = max(scale_x.from, function.definition_scope.from);
		double to = min(scale_x.to, function.definition_scope.to);
		for (double x = from; x <= to; x += function.step) {
			CalculateDot(x, function.f(x),wind_size->left-wind_size->right,wind_size->top-wind_size->bottom);
		}
	}
}
