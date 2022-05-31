//
// CMyGraph.h
//

#pragma once
#include <vector>			// for the vector
#include  <utility>			// for std::pair
#include "MathFunction.h"	// functions to draw

/// <summary>
/// Class represents CStatic element,
/// that will draw graphics of
/// MathFunction like objects
/// </summary>
class CMyGraph : public CStatic
{
	// enables access to run-time class information
	DECLARE_DYNAMIC(CMyGraph)

protected:

	/// <summary>
	/// Draws background with axes, axes serifs and numbers on them
	/// </summary>
	/// <param name="dc">dc to use</param>
	void drawBg(CDC& dc);

	/// <summary>
	/// indicates if background is done
	/// </summary>
	bool background_calculated = false;

	/// <summary>
	/// background color
	/// </summary>
	COLORREF bg_color = RGB(255, 255, 255);

	/// <summary>
	/// Bitmap for the background
	/// </summary>
	CBitmap bg_bmp;

	/// <summary>
	/// Old object for bgdc
	/// </summary>
	HGDIOBJ old_bmp = NULL;

	/// <summary>
	/// dc for drawing background
	/// </summary>
	CDC bgdc;

protected:

	/// <summary>
	/// Draws graph ON THE PAINTED BACKGROUND
	/// </summary>
	/// <param name="dc">dc to draw</param>
	void drawGraph(CDC& dc);

	/// <summary>
	/// indicates if graph is done
	/// </summary>
	bool graph_is_done = false;

	/// <summary>
	/// Graph bitmap
	/// </summary>
	CBitmap graph;

	/// <summary>
	/// old object for the graph_dc
	/// </summary>
	HGDIOBJ old_g_bmp = NULL;

	/// <summary>
	/// dc gor drawing graph
	/// </summary>
	CDC graph_dc;


	/// <summary>
	/// 'smart' function that checkes is graph and bg drawed and paint it
	/// recommended to use against of drawGraph and drawBg
	/// </summary>
	/// <param name="dc">dc to paint</param>
	void draw(CDC& dc);
protected:
	/// <summary>
	/// indicates if animation in progress
	/// </summary>
	bool animation_in_process = false;

	/// <summary>
	/// animation phase divided by 2pi
	/// </summary>
	float current_animation_phase = 0;

	/// <summary>
	/// animation cyclic frequency divided by 2pi
	/// </summary>
	float animation_speed = 5e-2;

	/// <summary>
	/// Recalculates column according to the phase
	/// </summary>
	/// <param name="column_h">true height</param>
	/// <returns>new column height</returns>
	int recalcDotForAnimation(int h);
public:
	/// <summary>
	/// shifting of the graph from the left bottom corner of the element
	/// </summary>
	POINT shift = { 80,30 };

	/// <summary>
	/// represents amount of serifs on axes
	/// </summary>
	struct { int x, y; } serifs = { 5,3 };

	/// <summary>
	/// length of serifs in the pixels
	/// </summary>
	int serifsize = 15;

	/// <summary>
	/// indicates if it is histogram
	/// </summary>
	bool is_hist = false;

	/// <summary>
	/// widths of hist columns
	/// </summary>
	int hist_width = 1;

	/// <summary>
	///  calculating step in pixels
	/// </summary>
	int step = 0;

	/// <summary>
	/// bounds of the calculating area (in math coords)
	/// </summary>
	struct
	{
		double from, to;
	}scale_x, scale_y;

	/// <summary>
	/// idicates if there is logarithmic scale on the ordinate axis
	/// </summary>
	bool is_log = false;

	/// <summary>
	/// Vector of the MathFunction like objects to draw
	/// </summary>
	std::vector<MathFunction*> functions;

	/// <summary>
	/// default constructor
	/// </summary>
	CMyGraph();

	/// <summary>
	/// destructor
	/// </summary>
	virtual ~CMyGraph();
protected:
	// for the message processing loop
	DECLARE_MESSAGE_MAP()
public:
	/// <summary>
	/// defines on message WM_PAINT behavior
	/// </summary>
	afx_msg void OnPaint();

	// setters
	void setScale(double x_from, double x_to, double y_from, double y_to);
	void setStep(int step);
	void setRect(RECT r);
	void setLog(bool b);
	void setNotCalculated();
	void setBgColor(COLORREF col);
	void setAnimState(bool state);
	void setColumnsCount(int N);

	// getter
	COLORREF getBgColor();

	/// <summary>
	/// Back conversion elemnts to real coords
	/// </summary>
	/// <param name="wx">x coord in the elements coords</param>
	/// <param name="wy">y coord in the elements coords</param>
	/// <param name="rect">rectangular border of the drawing region (of this element)</param>
	/// <returns>pair of double - real (math) coords</returns>
	std::pair<double, double> dotToCoords(int wx, int wy, CRect rect);

	/// <summary>
	/// Direct conversion real (math) to element (in pixels) coords
	/// </summary>
	/// <param name="x">x math coord</param>
	/// <param name="y">y math coord</param>
	/// <returns>element coords as POINT</returns>
	POINT coordsToDot(double x, double y, CRect rect);

	/// <summary>
	/// Defines behavior on timer tick (it is not connected to the timer)
	/// you should call it if you think that it's time to draw next frame
	/// </summary>
	/// <returns>returns if animation ended</returns>
	bool timerTick();
};


