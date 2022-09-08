//Graph.h - Version 3.0 (Brian Convery, May, 2001)

#if !defined(AFX_GRAPH_H__9DB68B4D_3C7C_47E2_9F72_EEDA5D2CDBB0__INCLUDED_)
#define AFX_GRAPH_H__9DB68B4D_3C7C_47E2_9F72_EEDA5D2CDBB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Graph.h : header file
//

#include "GraphGroupProperty.h"
#include "PopupMenuManager.h"

//color definitions
#define RED				RGB(255,0,0)
#define GREEN			RGB(0,255,0) 
#define BLUE			RGB(0,0,255)
#define YELLOW			RGB(255,255,0)
#define ORANGE			RGB(255,153,51)
#define HOT_PINK		RGB(255,51,153)
#define PURPLE			RGB(153,0,204)
#define CYAN			RGB(0,255,255)
#define BLACK			RGB(0,0,0)
#define WHITE			RGB(255,255,255)
#define LAVENDER		RGB(199,177,255)
#define PEACH			RGB(255,226,177)
#define SKY_BLUE		RGB(142,255,255)
#define FOREST_GREEN	RGB(0,192,0)
#define BROWN			RGB(80,50,0)
#define TURQUOISE		RGB(0,192,192)
#define ROYAL_BLUE		RGB(0,0,192)
#define GREY			RGB(192,192,192)
#define DARK_GREY		RGB(128,128,128)
#define TAN				RGB(255,198,107)
#define DARK_BLUE		RGB(0,0,128)
#define MAROON			RGB(128,0,0)
#define DUSK			RGB(255,143,107)
#define LIGHT_GREY		RGB(225,225,225)	//only for 3D graph lines

//for graph type definitions :
	//single number = 2D type graph
	//number in 20s = 2D type graph related to graph of single number
	//number in 30s = 3D type graph related to graph of single number
//graph type definitions
#define BAR_GRAPH				0
#define LINE_GRAPH				1	//lines between plotted points
#define PIE_GRAPH				2
#define SCATTER_GRAPH			3
#define BOX_WHISKER_GRAPH		4
//#define RADAR_GRAPH				5
//specialty graphs
#define STACKED_BAR_GRAPH		20
#define XY_LINE_GRAPH			21	//straight line, no circles at data points
#define BAR_GRAPH_3D			30
#define LINE_GRAPH_3D			31	//looks like a "tape" graph
#define PIE_GRAPH_3D			32
#define STACKED_BAR_GRAPH_3D	320

/////////////////////////////////////////////////////////////////////////////
// CGraphView window

#include "GraphSeries.h"
#include "GraphLegend.h"

class CGraphView: public CView
{
// Construction
public:
	CGraphView();
	CGraphView(int type);

	DECLARE_DYNCREATE(CGraphView)

// Attributes
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	virtual void OnDraw(CDC* pDC);      // overridden to draw this view


protected:
	int m_iYTickSpace;	//number of pixels between "y" axis ticks
	int m_iXTickSpace;	//number of pixels between "y" axis ticks

	CObList* m_pGraphSeries;
	int m_iGraphType;	//0 - bar graph, 1 - line graph, 2 - pie
	int m_iMaxHeight;
	int m_iMaxWidth;
	CString m_sAxisYLabel;
	CString m_sAxisXLabel;
	int m_iYApexPoint;	//yApex is the number of pixels from top to draw the x axis(bottom of y axis line)
	int m_iXApexPoint;	//xApex is number of pixels from left to draw y axis (leftmost point of x axis line)
	int m_yAxisHeight;
	int m_xAxisWidth;
	int m_iYTickFontSize;
	int m_iXTickFontSize;
	int m_iLegendFontSize;
	int m_iYNumTicks;
	int m_iYMinTick, m_iYMaxTick;

	int m_iXNumTicks;
	int m_iXMinTick, m_iXMaxTick;

	int m_iSeriesSize;	//number of data elements to map per series
	CGraphGroupProperty m_graphProperty;
	BOOL m_bGraphHasLegend;
	int m_iLegendWidth;
	int m_iXAxisAlign;	//# - degree rotation (0 = horizontal, 90 = vertical, etc)
	int m_iXAxisLabelLength;
	int m_iYAxisLabelLength;	//in case I ever need it
	CString m_sGraphTitle;
	CString m_sGraphFoot;
	BOOL m_bGraphHasGridLines;
	int m_iLegendMaxText;
	int m_iTopYTick;
	int m_iRightXTick;
	int m_iDepth;	//for 3D graphs
	double m_lfDepthRatio;
	int m_iGraphQuadType;
	BOOL m_bQuadSetManually;
	BOOL m_bInRedraw;
	int m_iLine3DXBase;	//for 3d line
	int m_iLine3DYBase;	//for 3d line

	//print settings
	int m_iTopMargin;
	int m_iBottomMargin;
	int m_iLeftMargin;
	int m_iRightMargin;
	int m_iPGraphL, m_iPGraphT, m_iPGraphB, m_iPGraphR;
	int m_iPTopYTick;
	int m_iPRightXTick;

	bool m_bPieDrawLabels;
	int  m_iPieLabelFontSize;
	CPoint m_point[10];


// Operations
public:
	void SetXTickFontSize(int size);
	void SetYTickFontSize(int size);
	void SetLegendFontSize(int size);
	void DrawGraph(CDC* pDC);
	void AddSeries(CGraphSeries* dataSet);
	void SetXAxisLabel(CString label);
	void SetYAxisLabel(CString label);
	void SetGroupProperty(	int					iDataGroup,
							CString				sLabel,
							COLORREF			color,
							int					iMarkerSize,
							int					iLineWidth,
							enumMarkerType		eMarkerType);

	void SetXAxisAlignment(int alignValue);
	void SetGraphType(int gType);

	void SetGraphTitle(CString title);
	void SetGraphFoot(CString sFoot);

	int PrintGraph(CDC *pDC, CPrintInfo* pInfo);
	void SetMargins(int top, int bottom, int left, int right, int graphTop);
	void SetGridLines(BOOL hasGridLines);
	void SetGraphAlignment(int alignment);  //0 - vertical, 1 horizontal
	void SetXTickLimits(int iMinTick, int iMaxTick, int tickStep);
	void SetYTickLimits(int iMinTick, int iMaxTick, int tickStep);
	void SetTickLimits(CDC *pDC);
	void RemoveSeries(CString label);
	void RemoveAllSeries();
	void RemoveAllData();	//removes all series, legends and colors
	void Set3DDepthRatio(double ratio);
	void SetGraphQuadType(int quads);
	void Set3DLineBase(int x, int y);

	virtual void SetChartProperty();
	virtual void SetChart();
	virtual void SetLegend();
	void SetLegend(int iGroup,CString sLabel);



private:
	void DrawAxis(CDC* pDC);
	void DrawSeries(CDC* pDC);
	int DrawLegend(CDC* pDC);
	COLORREF GetColor(int iDataGroup);
	int	GetMarkerSize(int iDataGroup);
	int GetLineWidth(int iDataGroup);
	enumMarkerType GetMarkerType(int iDataGroup);



	int GetXAxisAlignment();
	int PrintLegend(CDC *pDC);
	void PrintAxis(CDC *pDC);
	void PrintSeries(CDC *pDC);

	void DrawBarSeries(CDC* pDC);
	void DrawLineSeries(CDC* pDC);
	void DrawPieSeries(CDC* pDC);
	void DrawScatterSeries(CDC* pDC);
	void DrawBoxWhiskerSeries(CDC* pDC);
	void DrawStackedBarSeries(CDC* pDC);
	void DrawXYLineSeries(CDC* pDC);
//	void DrawRadarSeries(CDC* pDC);
	void Draw3DBarSeries(CDC* pDC);
	void Draw3DLineSeries(CDC* pDC);
	void Draw3DPieSeries(CDC* pDC);
	void Draw3DStackedBarSeries(CDC* pDC);

	void PrintBarSeries(CDC* pDC);
	void PrintLineSeries(CDC* pDC);
	void PrintPieSeries(CDC* pDC);
	void PrintScatterSeries(CDC* pDC);
	void PrintBoxWhiskerSeries(CDC* pDC);
	void PrintStackedBarSeries(CDC* pDC);
	void PrintXYLineSeries(CDC* pDC);
//	void PrintRadarSeries(CDC* pDC);
	void Print3DBarSeries(CDC* pDC);
	void Print3DLineSeries(CDC* pDC);
	void Print3DPieSeries(CDC* pDC);
	void Print3DStackedBarSeries(CDC* pDC);

	void DrawMarker(	CDC *pDC,
						enumMarkerType eMarkerType,
						int iHorPos, 
						int iVerPos, 
						int iSize);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphView)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphView();

	// Generated message map functions
protected:
	CPopupMenuManager m_menuManager;

	//{{AFX_MSG(CGraphView)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:

	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetchartproperty();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPH_H__9DB68B4D_3C7C_47E2_9F72_EEDA5D2CDBB0__INCLUDED_)
