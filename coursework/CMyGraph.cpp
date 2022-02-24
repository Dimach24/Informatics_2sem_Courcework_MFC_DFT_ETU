﻿// CMyGraph.cpp: файл реализации
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
std::pair<double, double> CMyGraph::CalculateDot(double x, double y, long width, long heigth)
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

	LPRECT wind_size=nullptr;
	GetWindowRect(wind_size);
	for (const MathFunction& function : functions) {
		double from = max(scale_x.from, function.definition_scope.from);
		double to = min(scale_x.to, function.definition_scope.to);
		for (double x = from; x <= to; x += function.step) {
			double y = function.f(x);
			if (y > scale_y.to || y < scale_y.from) { continue; }
			// x checked at the max, min
			CalculateDot(x, y,(wind_size->left)-(wind_size->right),(wind_size->top)-(wind_size->bottom));
		}
	}
}