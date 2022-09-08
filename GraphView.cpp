//Graph.cpp - Version 3.0 (Brian Convery, May, 2001)

#include "stdafx.h"
#include "qcdb.h"
#include "afxtempl.h"
#include "GraphSeries.h"
#include "GraphLegend.h"
#include "math.h"
#include "GraphView.h"
#include "GraphPieLabel.h"	//for pie labels
#include "ColorScale.h"
#include "MemDC.h"
#include "PieDrawer.h"
#include "FontGroup.h"
#include "FHCGlobal.h"
#include "DlgChartProperty.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphView

CGraphView::CGraphView()
{
	m_pGraphSeries = new CObList();
	m_iSeriesSize = 0;
	m_iYMinTick = 0;
	m_iYMaxTick = 100;
	m_iYNumTicks = 10;
	m_iYTickSpace = 10;

	m_iXMinTick = 0;
	m_iXMaxTick = 100;
	m_iXNumTicks = 10;
	m_iXTickSpace = 10;

	m_bGraphHasLegend = FALSE;
	m_iLegendWidth = 0;
	m_iLegendMaxText= 0;

	m_iGraphType = 0;

	m_iXAxisAlign = 0;  //horizontal
	m_iXAxisLabelLength = 0;

	m_iXTickFontSize = 12;
	m_iYTickFontSize = 12;
	m_iLegendFontSize = 12;
	m_iPieLabelFontSize= 12;

	m_iYAxisLabelLength=10;
	m_iXAxisLabelLength=10;

	m_iDepth = 0;
	m_lfDepthRatio = 0.05;

	m_iLine3DXBase = 0;
	m_iLine3DYBase = 0;

	SetGridLines(true);

	m_bPieDrawLabels=true;

	m_iGraphQuadType = 1;
	m_bQuadSetManually = FALSE;
	
	SetGridLines(true);
}

IMPLEMENT_DYNCREATE(CGraphView, CView)

BEGIN_MESSAGE_MAP(CGraphView, CView)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_SetChartProperty, OnSetchartproperty)
END_MESSAGE_MAP()

#ifdef _DEBUG
void CGraphView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

#endif //_DEBUG



CGraphView::CGraphView(int type)
{
	m_pGraphSeries = new CObList();
	m_iSeriesSize = 0;
	m_iYMinTick = 0;
	m_iYMaxTick = 100;
	m_iYNumTicks = 10;
	m_iYTickSpace = 10;

	m_bGraphHasLegend = FALSE;
	m_iLegendWidth = 0;
	m_iLegendMaxText= 0;

	m_iGraphType = type;

	m_iXAxisAlign = 0;  //in degrees == horizontal
	m_iXAxisLabelLength = 0;

	m_iXTickFontSize = 12;
	m_iYTickFontSize = 12;
	m_iLegendFontSize = 12;

	m_iDepth = 0;
	m_lfDepthRatio = 0.05;

	m_iLine3DXBase = 0;
	m_iLine3DYBase = 0;

	SetGridLines(FALSE);

	m_iGraphQuadType = 1;
	if(type != BAR_GRAPH)
		m_bQuadSetManually = TRUE;
	else
		m_bQuadSetManually = FALSE;
}

CGraphView::~CGraphView()
{
	RemoveAllData();

	delete m_pGraphSeries;

}

void CGraphView::SetGraphType(int gType)
{
	m_iGraphType = gType;
}

void CGraphView::SetXAxisAlignment(int alignValue)
{
	m_iXAxisAlign = alignValue;
}
 
int CGraphView::GetXAxisAlignment()
{
	return m_iXAxisAlign;
}

COLORREF CGraphView::GetColor(int iDataGroup)
{
	CGraphGroupPropertySet * p= (CGraphGroupPropertySet*) m_graphProperty.Get (iDataGroup);
	if(p)
	{
		return p->groupColor ;
	}
	else
	{
		return 0;
	}
}

int CGraphView::GetMarkerSize(int iDataGroup)
{
	CGraphGroupPropertySet * p= (CGraphGroupPropertySet*) m_graphProperty.Get (iDataGroup);
	if(p)
	{
		return p->iMarkerSize ;
	}
	else
	{
		return 0;
	}
}

int CGraphView::GetLineWidth(int iDataGroup)
{
	CGraphGroupPropertySet * p= (CGraphGroupPropertySet*) m_graphProperty.Get (iDataGroup);
	if(p)
	{
		return p->iLineWidth ;
	}
	else
	{
		return 0;
	}
}

enumMarkerType CGraphView::GetMarkerType(int iDataGroup)
{
	CGraphGroupPropertySet * p= (CGraphGroupPropertySet*) m_graphProperty.Get (iDataGroup);
	if(p)
	{
		return p->eMarkerType ;
	}
	else
	{
		return MT_TRI;
	}
}

void CGraphView::DrawGraph(CDC* pDC)
{
	CString tickLabel;
	CWnd* graphWnd = pDC->GetWindow();
	CRect graphRect;
	GetClientRect(&graphRect);
	TEXTMETRIC	tm;

	//reset graph to be clear background
	COLORREF backColor;
	backColor = RGB(255,255,255);  //replace with desired background color
	CBrush backBrush (backColor);
	CBrush* pOldBackBrush;
	pOldBackBrush = pDC->SelectObject(&backBrush);
	pDC->Rectangle(0, 0, graphRect.Width(), graphRect.Height());
	pDC->SelectObject(pOldBackBrush);

	m_iMaxHeight = graphRect.Height() - 20;  //for frame window and status bar
	m_iMaxWidth = graphRect.Width() - 5;  //for frame window

	//draw graph title
	CFont titleFont;
	int tFontSize = 24;
	while((m_sGraphTitle.GetLength() * (tFontSize / 2)) > m_iMaxWidth)
	{
		tFontSize -= 2;
	}
	titleFont.CreateFont(tFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
	CFont* pOldFont = (CFont*) pDC->SelectObject(&titleFont);

	pDC->GetTextMetrics(&tm);

	int charWidth = tm.tmAveCharWidth;
	//next line is centered....trust me !!
	pDC->TextOut((graphRect.Width() / 2) - ((m_sGraphTitle.GetLength() / 2) * charWidth),
				10, m_sGraphTitle);
	pDC->SelectObject(pOldFont);

	if((m_iGraphType == PIE_GRAPH) || (m_iGraphType == PIE_GRAPH_3D))
	{

		//since pie does not have axis lines, set to full size minus 5 on each side
		//these are needed for legend to plot itself
		m_xAxisWidth = m_iMaxWidth - 10;
		m_yAxisHeight = m_iMaxHeight - 50;  //10 buffer, 20 for title, and 20 for series label
		m_iXApexPoint = 5;
		m_iYApexPoint = m_iMaxHeight - 5;
	}
	else
	{
		//compute label size for axis alignment
		CFont sideFont, axisFont;
		int tFontSize = 16;
		if(m_iMaxWidth > m_iMaxHeight)
		{
			while((m_sAxisYLabel.GetLength() * (tFontSize / 2)) > m_iMaxHeight)
			{
				tFontSize -= 2;
			}
		}
		else
		{
			while((m_sAxisXLabel.GetLength() * (tFontSize / 2)) > m_iMaxWidth)
			{
				tFontSize -= 2;
			}
		}
		axisFont.CreateFont(tFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
			ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
		sideFont.CreateFont(tFontSize, 0, 900, 0, 700, FALSE, FALSE, 0,
			ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");

		CFont* pOldFont = (CFont*) pDC->SelectObject(&sideFont);
		pDC->GetTextMetrics(&tm);
		int charWidth = tm.tmAveCharWidth;
		int labelHeight = tm.tmHeight + 10;
		if(m_sAxisYLabel.GetLength() == 0)
		{
			labelHeight = 0;
		}
		pDC->SelectObject(pOldFont);

		tickLabel.Format("%d", m_iYMaxTick);

		//determine axis specifications 
		if(m_iGraphType == SCATTER_GRAPH)
		{
			m_iXApexPoint = 5 + tickLabel.GetLength()*m_iYTickFontSize + labelHeight; //labelHeight added for y-axis label height
			m_iYApexPoint = (m_iMaxHeight - 15) - tm.tmHeight;
			m_yAxisHeight = m_iYApexPoint - 40;
			m_xAxisWidth = (m_iMaxWidth - 5) - m_iXApexPoint;
		}
		else
		{
			m_iXApexPoint = 5 + (tickLabel.GetLength() * (m_iYTickFontSize / 2)) + 45; 
			if(!m_iXAxisAlign)  //horizontal
				m_iYApexPoint = (m_iMaxHeight - 5) - 45;		//apex points are the cross section of axis lines
			else
				m_iYApexPoint = (m_iMaxHeight - 5) - (m_iXAxisLabelLength * (m_iXTickFontSize / 2)) - 10;
			m_yAxisHeight = m_iYApexPoint - 40;
			m_xAxisWidth = (m_iMaxWidth - 5) - m_iXApexPoint;
		}
	}

	//draw legend
	if(m_bGraphHasLegend)
	{
		int legendLeft = DrawLegend(pDC);
		m_xAxisWidth = legendLeft - 10 - m_iXApexPoint;
	}

	if((!m_bQuadSetManually) && (m_iGraphType == BAR_GRAPH))
	{
		//computer number of quadrants needed based on data
		POSITION pos,posSer;
		pos = m_pGraphSeries->GetHeadPosition();
		CGraphSeries* tmpSeries;
		int minXValue = 0;
		int minYValue = 0;
		CGraphDataSet *pDataSet=NULL;
		for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
		{
			tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);
			posSer = tmpSeries->GetHeadPosition ();
			while(posSer)
			{
				//to allow scalability (height may be less than tickRange)
				pDataSet =tmpSeries->GetDataValue(posSer);
				if(pDataSet->xPosition  < minXValue)
					minXValue = pDataSet->xPosition;
				if(pDataSet->yValue < minYValue)
					minYValue = pDataSet->yValue ;
			}
		}
		m_iGraphQuadType = 1;
		if((minXValue < 0) && (minYValue < 0))
			m_iGraphQuadType = 4;
		if((minXValue < 0) && (minYValue >= 0))
			m_iGraphQuadType = 2;
		if((minXValue >= 0) && (minYValue < 0))
			m_iGraphQuadType = 3;
	}

	if(m_iGraphType == BAR_GRAPH)
	{
		switch(m_iGraphQuadType)
		{
			case 2 :
				m_iXApexPoint += m_xAxisWidth / 2;
				break;
			case 3 :
				m_iYApexPoint -= m_yAxisHeight / 2;
				break;
			case 4 :
				m_iXApexPoint += m_xAxisWidth / 2;
				m_iYApexPoint -= m_yAxisHeight / 2;
				break;
		}
	}

	if(m_yAxisHeight<0||m_xAxisWidth<0)return;

	SetTickLimits(pDC);

	if((m_iGraphType != 2) && (m_iGraphType != 32))  //pie & 3d pie
	{
		m_bInRedraw = FALSE;
		//draw axis lines
		DrawAxis(pDC);
	}

	//draw series data and labels
	DrawSeries(pDC);

	//lines below are commented for doing redraw.  If you
	//want the axis lines on top of the other graph elements
	//uncomment this functionality...I may add it back later
	//but there were some bugs doing it this way.

	//redraw axis lines in case graph elements overwrote the axis lines
//	if((m_iGraphType != 2) && (m_iGraphType != 32) && (m_iGraphQuadType > 1))  //pie & 3d pie
//	{
//		m_bInRedraw = TRUE;
		//draw axis lines
//		DrawAxis(pDC);
//	}
}

void CGraphView::DrawAxis(CDC* pDC)
{
	TEXTMETRIC	tm;
	pDC->SetTextColor(BLACK);
	CFont sideFont, axisFont, dummyFont;
	int charWidth;
	double tickScale;
	int tickXLocation, tickYLocation;
	int seriesSpace;
	CFont* pOldFont;
	int x, y;
	int barWidth ;
	int iTickLen=6;
	int iMidTickLen=3;

	if(m_pGraphSeries->GetCount()<1)return;


	COLORREF axisLineColor;
	axisLineColor = BLACK;
	CPen axisPen (PS_SOLID, 2, axisLineColor);
	dummyFont.CreateFont(12, 0, 0, 0, 700, FALSE, FALSE, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
	pOldFont = (CFont*)pDC->SelectObject(&dummyFont);
	switch(m_iGraphType)
	{
		case BAR_GRAPH :
		case LINE_GRAPH :
		case SCATTER_GRAPH :
		case BOX_WHISKER_GRAPH :
//		case RADAR_GRAPH :
		case STACKED_BAR_GRAPH :
		case XY_LINE_GRAPH :
				CPen* pOldAxisPen;
				pOldAxisPen = pDC->SelectObject(&axisPen);
				switch(m_iGraphQuadType)
				{
					case 1 :
						//draw y axis
						pDC->MoveTo(m_iXApexPoint, m_iYApexPoint);  
						pDC->LineTo(m_iXApexPoint, m_iYApexPoint - m_yAxisHeight);

						//draw x axis
						pDC->MoveTo(m_iXApexPoint, m_iYApexPoint);  
						pDC->LineTo(m_iXApexPoint + m_xAxisWidth, m_iYApexPoint);
						break;
					case 2 :
						//draw y axis
						pDC->MoveTo(m_iXApexPoint, m_iYApexPoint);  
						pDC->LineTo(m_iXApexPoint, m_iYApexPoint - m_yAxisHeight);

						//draw x axis
						pDC->MoveTo(m_iXApexPoint - (m_xAxisWidth / 2), m_iYApexPoint);  
						pDC->LineTo(m_iXApexPoint + (m_xAxisWidth / 2), m_iYApexPoint);
						break;
					case 3 :
						//draw y axis
						pDC->MoveTo(m_iXApexPoint, m_iYApexPoint + (m_yAxisHeight / 2));  
						pDC->LineTo(m_iXApexPoint, m_iYApexPoint - (m_yAxisHeight / 2));

						//draw x axis
						pDC->MoveTo(m_iXApexPoint, m_iYApexPoint);  
						pDC->LineTo(m_iXApexPoint + m_xAxisWidth, m_iYApexPoint);
						break;
					case 4 :
						//draw y axis
						pDC->MoveTo(m_iXApexPoint, m_iYApexPoint + (m_yAxisHeight / 2));  
						pDC->LineTo(m_iXApexPoint, m_iYApexPoint - (m_yAxisHeight / 2));

						//draw x axis
						pDC->MoveTo(m_iXApexPoint - (m_xAxisWidth / 2), m_iYApexPoint);  
						pDC->LineTo(m_iXApexPoint + (m_xAxisWidth / 2), m_iYApexPoint);
						break;
				}
				pDC->SelectObject(pOldAxisPen);

				int tFontSize;
				//draw labels
				tFontSize = 16;
				if(m_iMaxWidth > m_iMaxHeight)
				{
					while((m_sAxisYLabel.GetLength() * (tFontSize / 2)) > m_iMaxHeight)
					{
						tFontSize -= 2;
					}
				}
				else
				{
					while((m_sAxisXLabel.GetLength() * (tFontSize / 2)) > m_iMaxWidth)
					{
						tFontSize -= 2;
					}
				}
				axisFont.CreateFont(tFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
					ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
				sideFont.CreateFont(tFontSize, 0, 900, 0, 700, FALSE, FALSE, 0,
					ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");

				pDC->SelectObject(&sideFont);
				pDC->GetTextMetrics(&tm);
				charWidth = tm.tmAveCharWidth;

				switch(m_iGraphQuadType)
				{
					case 1 :
					case 2 :
						pDC->TextOut(10, (m_iYApexPoint - (m_yAxisHeight / 2)) + ((m_sAxisYLabel.GetLength() * charWidth) / 2), m_sAxisYLabel);
						break;
					case 3 :
					case 4 :
						pDC->TextOut(10, m_iYApexPoint + ((m_sAxisYLabel.GetLength() * charWidth) / 2), m_sAxisYLabel);
						break;
				}


				pDC->SelectObject(&axisFont);
				pDC->GetTextMetrics(&tm);
				charWidth = tm.tmAveCharWidth;
				switch(m_iGraphQuadType)
				{
					case 1 :
						pDC->TextOut(m_iXApexPoint + (m_xAxisWidth / 2) - ((m_sAxisXLabel.GetLength() / 2) * charWidth), m_iMaxHeight - 5 - 6, m_sAxisXLabel);
						break;
					case 2 :
						pDC->TextOut(m_iXApexPoint - ((m_sAxisXLabel.GetLength() / 2) * charWidth), m_iMaxHeight - 5 - 6, m_sAxisXLabel);
						break;
					case 3 :
						pDC->TextOut(m_iXApexPoint + (m_xAxisWidth / 2) - ((m_sAxisXLabel.GetLength() / 2) * charWidth), m_iMaxHeight - 5 - 6, m_sAxisXLabel);
						break;
					case 4 :
						pDC->TextOut(m_iXApexPoint - ((m_sAxisXLabel.GetLength() / 2) * charWidth), m_iMaxHeight - 5 - 6, m_sAxisXLabel);
						break;
				}

				
				pDC->SelectObject(pOldFont);

				if(m_iYNumTicks!=0)
				{
					tickScale = (m_yAxisHeight - 10) / m_iYNumTicks;
				}
				else
				{
					tickScale=10;
				}

				//draw y axis ticks
				if(!m_bInRedraw)
				{
					switch(m_iGraphQuadType)
					{
						case 1 :
							for(y = 1; y <= m_iYNumTicks; y++) 
							{
								tickYLocation = (int)(m_iYApexPoint - (y * tickScale));

								//draw tick mark
								pDC->MoveTo(m_iXApexPoint - 3, tickYLocation);
								pDC->LineTo(m_iXApexPoint + 3, tickYLocation);

								if(m_bGraphHasGridLines)
								{
									//draw grid lines
									COLORREF gridLineColor;
									gridLineColor = DARK_GREY;
									CPen gridPen (PS_SOLID, 1, gridLineColor);
									CPen* pOldPen;
									pOldPen = pDC->SelectObject(&gridPen);
									pDC->MoveTo(m_iXApexPoint, tickYLocation);
									pDC->LineTo(m_iXApexPoint + m_xAxisWidth, tickYLocation);
									pDC->SelectObject(pOldPen);
								}

								//draw tick label
								CString tickLabel;
								tickLabel.Format("%d", m_iYMinTick + (y * m_iYTickSpace));

								CFont yFont;
								yFont.CreateFont(m_iYTickFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
									ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
									DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
								pDC->SelectObject(&yFont);

								pDC->TextOut(m_iXApexPoint - 10 - (tickLabel.GetLength() * (m_iYTickFontSize / 2)), tickYLocation - 6, tickLabel);
								pDC->SelectObject(pOldFont);
								m_iTopYTick = tickYLocation;
							}
							break;
							pDC->SelectObject(pOldFont);
						case 2 :
							if(m_iGraphType == SCATTER_GRAPH)
							{
								double oldTickScale;
								int oldNumTicks;
								oldNumTicks = m_iYNumTicks;
								oldTickScale = tickScale;

								m_iYNumTicks /= 2;
								tickScale *= 2;
								for(y = 1; y <= m_iYNumTicks; y++)  
								{
									tickYLocation = (int)(m_iYApexPoint - (y * tickScale));

									//draw tick mark
									pDC->MoveTo(m_iXApexPoint - 3, tickYLocation);
									pDC->LineTo(m_iXApexPoint + 3, tickYLocation);

									if(m_bGraphHasGridLines)
									{
										//draw grid lines
										COLORREF gridLineColor;
										gridLineColor = LIGHT_GREY;
										CPen gridPen (PS_SOLID, 1, gridLineColor);
										CPen* pOldPen;
										pOldPen = pDC->SelectObject(&gridPen);
										pDC->MoveTo(m_iXApexPoint - (m_xAxisWidth / 2), tickYLocation);
										pDC->LineTo(m_iXApexPoint + (m_xAxisWidth / 2), tickYLocation);
										pDC->SelectObject(pOldPen);
									}

									//draw tick label
									CString tickLabel;
									tickLabel.Format("%d", m_iYMinTick + (y * m_iYTickSpace));

									CFont yFont;
									yFont.CreateFont(m_iYTickFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
										ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
										DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
									pDC->SelectObject(&yFont);

									pDC->TextOut(m_iXApexPoint - (m_xAxisWidth / 2) - 10 - (tickLabel.GetLength() * (m_iYTickFontSize / 2)), tickYLocation - 6, tickLabel);
									pDC->SelectObject(pOldFont);
									m_iTopYTick = tickYLocation;
								}
								//draw the 0
								pDC->TextOut(m_iXApexPoint - (m_xAxisWidth / 2) - 10 - (m_iYTickFontSize / 2), m_iYApexPoint - 6, "0");

								//reset m_iYNumTicks and tickScale back to normal
								tickScale = oldTickScale;
								m_iYNumTicks = oldNumTicks;
							}
							else
							{
								for(y = 1; y <= m_iYNumTicks; y++)  
								{
									tickYLocation = (int)(m_iYApexPoint - (y * tickScale));

									//draw tick mark
									pDC->MoveTo(m_iXApexPoint - 3, tickYLocation);
									pDC->LineTo(m_iXApexPoint + 3, tickYLocation);

									if(m_bGraphHasGridLines)
									{
										//draw grid lines
										COLORREF gridLineColor;
										gridLineColor = DARK_GREY;
										CPen gridPen (PS_SOLID, 1, gridLineColor);
										CPen* pOldPen;
										pOldPen = pDC->SelectObject(&gridPen);
										pDC->MoveTo(m_iXApexPoint - (m_xAxisWidth / 2), tickYLocation);
										pDC->LineTo(m_iXApexPoint + (m_xAxisWidth / 2), tickYLocation);
										pDC->SelectObject(pOldPen);
									}

									//draw tick label
									CString tickLabel;
									tickLabel.Format("%d", m_iYMinTick + (y * m_iYTickSpace));

									CFont yFont;
									yFont.CreateFont(m_iYTickFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
										ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
										DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
									pDC->SelectObject(&yFont);

									pDC->TextOut(m_iXApexPoint - (m_xAxisWidth / 2) - 10 - (tickLabel.GetLength() * (m_iYTickFontSize / 2)), tickYLocation - 6, tickLabel);
									m_iTopYTick = tickYLocation;

								}
								//draw the 0
								pDC->TextOut(m_iXApexPoint - (m_xAxisWidth / 2) - 10 - (m_iYTickFontSize / 2), m_iYApexPoint - 6, "0");
							}
							pDC->SelectObject(pOldFont);
							break;
						case 3 :
							for(y = 0; y <= m_iYNumTicks / 2; y++) 
							{
								tickYLocation = (int)(m_iYApexPoint + 5 - (m_yAxisHeight / 2) + (y * tickScale));

								//draw tick mark
								pDC->MoveTo(m_iXApexPoint - 3, tickYLocation);
								pDC->LineTo(m_iXApexPoint + 3, tickYLocation);

								if(m_bGraphHasGridLines)
								{
									//draw grid lines
									COLORREF gridLineColor;
									gridLineColor = DARK_GREY;
									CPen gridPen (PS_SOLID, 1, gridLineColor);
									CPen* pOldPen;
									pOldPen = pDC->SelectObject(&gridPen);
									pDC->MoveTo(m_iXApexPoint, tickYLocation);
									pDC->LineTo(m_iXApexPoint, tickYLocation);
									pDC->SelectObject(pOldPen);
								}

								//draw tick label
								CString tickLabel;
								tickLabel.Format("%d", m_iYMaxTick - (y * m_iYTickSpace));

								CFont yFont;
								yFont.CreateFont(m_iYTickFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
									ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
									DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
								pDC->SelectObject(&yFont);

								pDC->TextOut(m_iXApexPoint - 10 - (tickLabel.GetLength() * (m_iYTickFontSize / 2)), tickYLocation - 6, tickLabel);
								m_iTopYTick = tickYLocation;

							}
							//draw the 0
							pDC->TextOut(m_iXApexPoint - (m_xAxisWidth / 2) - 10 - (m_iYTickFontSize / 2), m_iYApexPoint - 6, "0");
							
							for(; y <= m_iYNumTicks; y++) 
							{
								tickYLocation = (int)(m_iYApexPoint + 5 - (m_yAxisHeight / 2) + (y * tickScale));

								//draw tick mark
								pDC->MoveTo(m_iXApexPoint - 3, tickYLocation);
								pDC->LineTo(m_iXApexPoint + 3, tickYLocation);

								if(m_bGraphHasGridLines)
								{
									//draw grid lines
									COLORREF gridLineColor;
									gridLineColor = DARK_GREY;
									CPen gridPen (PS_SOLID, 1, gridLineColor);
									CPen* pOldPen;
									pOldPen = pDC->SelectObject(&gridPen);
									pDC->MoveTo(m_iXApexPoint, tickYLocation);
									pDC->LineTo(m_iXApexPoint, tickYLocation);
									pDC->SelectObject(pOldPen);
								}

								//draw tick label
								CString tickLabel;
								tickLabel.Format("%d", m_iYMinTick + ((m_iYNumTicks - y) * m_iYTickSpace));

								pDC->TextOut(m_iXApexPoint - 10 - (tickLabel.GetLength() * (m_iYTickFontSize / 2)), tickYLocation - 6, tickLabel);
								m_iTopYTick = tickYLocation;

							}
							pDC->SelectObject(pOldFont);
							break;
						pDC->SelectObject(pOldFont);
						case 4 :
							for(y = 1; y <= m_iYNumTicks / 2; y++) 
							{
								tickYLocation = (int)(m_iYApexPoint - (y * tickScale));

								//draw tick mark
								pDC->MoveTo(m_iXApexPoint - 3, tickYLocation);
								pDC->LineTo(m_iXApexPoint + 3, tickYLocation);

								if(m_bGraphHasGridLines)
								{
									//draw grid lines
									COLORREF gridLineColor;
									gridLineColor = DARK_GREY;
									CPen gridPen (PS_SOLID, 1, gridLineColor);
									CPen* pOldPen;
									pOldPen = pDC->SelectObject(&gridPen);
									pDC->MoveTo(m_iXApexPoint - (m_xAxisWidth / 2), tickYLocation);
									pDC->LineTo(m_iXApexPoint + (m_xAxisWidth / 2), tickYLocation);
									pDC->SelectObject(pOldPen);
								}

								//draw tick label
								CString tickLabel;
								tickLabel.Format("%d", m_iYMinTick + (y * m_iYTickSpace));

								CFont yFont;
								yFont.CreateFont(m_iYTickFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
									ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
									DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
								pDC->SelectObject(&yFont);

								pDC->TextOut(m_iXApexPoint - (m_xAxisWidth / 2) - 10 - (tickLabel.GetLength() * (m_iYTickFontSize / 2)), tickYLocation - 6, tickLabel);
								m_iTopYTick = tickYLocation;

							}
							//draw the 0
							pDC->TextOut(m_iXApexPoint - (m_xAxisWidth / 2) - 10 - (m_iYTickFontSize / 2), m_iYApexPoint - 6, "0");
							
							for(; y <= m_iYNumTicks; y++)  
							{
								tickYLocation = (int)(m_iYApexPoint - (m_yAxisHeight / 2) + (y * tickScale));

								//draw tick mark
								pDC->MoveTo(m_iXApexPoint - 3, tickYLocation);
								pDC->LineTo(m_iXApexPoint + 3, tickYLocation);

								if(m_bGraphHasGridLines)
								{
									//draw grid lines
									COLORREF gridLineColor;
									gridLineColor = DARK_GREY;
									CPen gridPen (PS_SOLID, 1, gridLineColor);
									CPen* pOldPen;
									pOldPen = pDC->SelectObject(&gridPen);
									pDC->MoveTo(m_iXApexPoint - (m_xAxisWidth / 2), tickYLocation);
									pDC->LineTo(m_iXApexPoint + (m_xAxisWidth / 2), tickYLocation);
									pDC->SelectObject(pOldPen);
								}

								//draw tick label
								CString tickLabel;
								tickLabel.Format("%d", m_iYMinTick + ((m_iYNumTicks - y) * m_iYTickSpace));

								pDC->TextOut(m_iXApexPoint - (m_xAxisWidth / 2) - 10 - (tickLabel.GetLength() * (m_iYTickFontSize / 2)), tickYLocation - 6, tickLabel);
								m_iTopYTick = tickYLocation;

							}
							pDC->SelectObject(pOldFont);
							break;
					}
				}

				//draw X axis tick marks
				switch(m_iGraphQuadType)
				{
					case 1 :
						if(m_iGraphType != SCATTER_GRAPH)
						{
							POSITION pos;
							pos = m_pGraphSeries->GetHeadPosition();
							CGraphSeries* tmpSeries;
							for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
							{
								tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

								seriesSpace = m_xAxisWidth / m_pGraphSeries->GetCount();
								tickXLocation = m_iXApexPoint + ((x * seriesSpace) - (seriesSpace / 2));

								pDC->MoveTo(tickXLocation,m_iYApexPoint - 3);
								pDC->LineTo(tickXLocation,m_iYApexPoint + 3);

								//draw tick label
								CString tickLabel;
								CFont xFont;
								xFont.CreateFont(m_iXTickFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
									ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
									DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
								pDC->SelectObject(&xFont);
								tickLabel = tmpSeries->GetLabel();
								if(!m_iXAxisAlign)  //horizontal
									pDC->TextOut(tickXLocation - ((tickLabel.GetLength() * 8) / 2), m_iYApexPoint + 8, tickLabel);
								else
								{
									CFont sideFont2;
									sideFont2.CreateFont(m_iXTickFontSize, 0, (m_iXAxisAlign * 10), 0, 700, FALSE, FALSE, 0,
										ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
										DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
									pDC->SelectObject(&sideFont2);
									pDC->GetTextMetrics(&tm);
									charWidth = tm.tmAveCharWidth;
									if(m_iXAxisAlign < 180)
										pDC->TextOut(tickXLocation - 8, m_iYApexPoint + 8 + (m_iXAxisLabelLength * charWidth), tickLabel);
									else
										pDC->TextOut(tickXLocation + 2, m_iYApexPoint + 8, tickLabel);

									pDC->SelectObject(pOldFont);
								}
								m_iRightXTick = tickXLocation;
							}
						}
						else
						{
							//scatter graphs will use the same tick marking on both axis lines
							seriesSpace = (m_xAxisWidth - 20) / m_iXNumTicks;
							for(int x = 1; x <= m_iXNumTicks; x++)  
							{
								tickXLocation = m_iXApexPoint + (x * seriesSpace);

								//draw tick mark
								pDC->MoveTo(tickXLocation, m_iYApexPoint - 3);
								pDC->LineTo(tickXLocation, m_iYApexPoint + 3);

								//draw tick label
								CString tickLabel;
								CFont xFont;
								tickLabel.Format("%d", x * m_iXTickSpace+m_iXMinTick);

								xFont.CreateFont(m_iXTickFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
									ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
									DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
								pDC->SelectObject(&xFont);
								pDC->GetTextMetrics(&tm);
								charWidth = tm.tmAveCharWidth;

								pDC->TextOut(tickXLocation - (tickLabel.GetLength() * charWidth / 2), m_iYApexPoint + 8, tickLabel);

								m_iRightXTick = tickXLocation;
								pDC->SelectObject(pOldFont);
							}

						}
						break;
					case 2 :
						if(m_iGraphType != SCATTER_GRAPH)
						{
							POSITION pos;
							pos = m_pGraphSeries->GetHeadPosition();
							CGraphSeries* tmpSeries;
							seriesSpace = m_xAxisWidth / m_pGraphSeries->GetCount();
							for(x = 1; x <= m_pGraphSeries->GetCount() / 2; x++)
							{
								tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

								tickXLocation = m_iXApexPoint - (m_xAxisWidth / 2) + ((x * seriesSpace) - (seriesSpace / 2));

								pDC->MoveTo(tickXLocation,m_iYApexPoint - 3);
								pDC->LineTo(tickXLocation,m_iYApexPoint + 3);

								if(!m_bInRedraw)
								{
									//draw tick label
									CString tickLabel;
									tickLabel = tmpSeries->GetLabel();
									if(!m_iXAxisAlign)  //horizontal
									{
										CFont xFont;
										xFont.CreateFont(m_iXTickFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
											ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
											DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
										pDC->SelectObject(&xFont);
										pDC->TextOut(tickXLocation - ((tickLabel.GetLength() * 8) / 2), m_iYApexPoint + 8, tickLabel);
										pDC->SelectObject(pOldFont);
									}
									else
									{
										CFont sideFont2;
										sideFont2.CreateFont(m_iXTickFontSize, 0, (m_iXAxisAlign * 10), 0, 700, FALSE, FALSE, 0,
											ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
											DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
										pDC->SelectObject(&sideFont2);
										pDC->GetTextMetrics(&tm);
										charWidth = tm.tmAveCharWidth;
										if(m_iXAxisAlign < 180)
											pDC->TextOut(tickXLocation - 8, m_iYApexPoint + 8 + (m_iXAxisLabelLength * charWidth), tickLabel);
										else
											pDC->TextOut(tickXLocation + 2, m_iYApexPoint + 8, tickLabel);

										pDC->SelectObject(pOldFont);
									}
								}
								m_iRightXTick = tickXLocation;
							}
							if((m_pGraphSeries->GetCount() % 2) > 0)
							{
								tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);
								
								tickXLocation = m_iXApexPoint;

								pDC->MoveTo(tickXLocation,m_iYApexPoint - 3);
								pDC->LineTo(tickXLocation,m_iYApexPoint + 3);

								if(!m_bInRedraw)
								{
									//draw tick label
									CString tickLabel;
									tickLabel = tmpSeries->GetLabel();
									if(!m_iXAxisAlign)  //horizontal
									{
										CFont xFont;
										xFont.CreateFont(m_iXTickFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
											ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
											DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
										pDC->SelectObject(&xFont);
										pDC->TextOut(tickXLocation - ((tickLabel.GetLength() * 8) / 2), m_iYApexPoint + 8, tickLabel);
										pDC->SelectObject(pOldFont);
									}
									else
									{
										CFont sideFont2;
										sideFont2.CreateFont(m_iXTickFontSize, 0, (m_iXAxisAlign * 10), 0, 700, FALSE, FALSE, 0,
											ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
											DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
										pDC->SelectObject(&sideFont2);
										pDC->GetTextMetrics(&tm);
										charWidth = tm.tmAveCharWidth;
										if(m_iXAxisAlign < 180)
											pDC->TextOut(tickXLocation - 8, m_iYApexPoint + 8 + (m_iXAxisLabelLength * charWidth), tickLabel);
										else
											pDC->TextOut(tickXLocation + 2, m_iYApexPoint + 8, tickLabel);

										pDC->SelectObject(pOldFont);
									}
								}
								m_iRightXTick = tickXLocation;
								x++;
							}
							for(; x <= m_pGraphSeries->GetCount(); x++)
							{
								tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

								tickXLocation = m_iXApexPoint - (m_xAxisWidth / 2) + ((x * seriesSpace) - (seriesSpace / 2));

								pDC->MoveTo(tickXLocation,m_iYApexPoint - 3);
								pDC->LineTo(tickXLocation,m_iYApexPoint + 3);

								if(!m_bInRedraw)
								{
									//draw tick label
									CString tickLabel;
									tickLabel = tmpSeries->GetLabel();
									if(!m_iXAxisAlign)  //horizontal
									{
										CFont xFont;
										xFont.CreateFont(m_iXTickFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
											ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
											DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
										pDC->SelectObject(&xFont);
										pDC->TextOut(tickXLocation - ((tickLabel.GetLength() * 8) / 2), m_iYApexPoint + 8, tickLabel);
										pDC->SelectObject(pOldFont);
									}
									else
									{
										CFont sideFont2;
										sideFont2.CreateFont(m_iXTickFontSize, 0, (m_iXAxisAlign * 10), 0, 700, FALSE, FALSE, 0,
											ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
											DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
										pDC->SelectObject(&sideFont2);
										pDC->GetTextMetrics(&tm);
										charWidth = tm.tmAveCharWidth;
										if(m_iXAxisAlign < 180)
											pDC->TextOut(tickXLocation - 8, m_iYApexPoint + 8 + (m_iXAxisLabelLength * charWidth), tickLabel);
										else
											pDC->TextOut(tickXLocation + 2, m_iYApexPoint + 8, tickLabel);

										pDC->SelectObject(pOldFont);
									}
								}
								m_iRightXTick = tickXLocation;
							}
						}
						else
						{
							//scatter graphs will use the same tick marking on both axis lines
							seriesSpace = m_xAxisWidth / m_iXNumTicks;
							for(x = 0; x <= m_iXNumTicks / 2; x++)  
							{
								tickXLocation = m_iXApexPoint + 5 - (m_xAxisWidth / 2) + (x * seriesSpace);

								//draw tick mark
								pDC->MoveTo(tickXLocation, m_iYApexPoint - 3);
								pDC->LineTo(tickXLocation, m_iYApexPoint + 3);

								if(!m_bInRedraw)
								{
									//draw tick label
									CString tickLabel;
									tickLabel.Format("%d", m_iXMinTick + (x * m_iYTickSpace));

									CFont xFont;
									xFont.CreateFont(m_iXTickFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
										ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
										DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
									pDC->SelectObject(&xFont);
									pDC->GetTextMetrics(&tm);
									charWidth = tm.tmAveCharWidth;

									pDC->TextOut(tickXLocation - (tickLabel.GetLength() * charWidth / 2), m_iYApexPoint + 8, tickLabel);
								}
								m_iRightXTick = tickXLocation;
								pDC->SelectObject(pOldFont);
							}
							//draw the 0
							tickXLocation = m_iXApexPoint;
							if(!m_bInRedraw)
							{
								//draw tick label

								CFont xFont;
								xFont.CreateFont(m_iXTickFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
									ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
									DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
								pDC->SelectObject(&xFont);
								pDC->GetTextMetrics(&tm);
								charWidth = tm.tmAveCharWidth;

								pDC->TextOut(tickXLocation - (charWidth / 2), m_iYApexPoint + 8, "0");
							}

							for(; x <= m_iYNumTicks; x++)  
							{
								tickXLocation = m_iXApexPoint - (m_xAxisWidth / 2) + (x * seriesSpace);

								//draw tick mark
								pDC->MoveTo(tickXLocation, m_iYApexPoint - 3);
								pDC->LineTo(tickXLocation, m_iYApexPoint + 3);

								if(!m_bInRedraw)
								{
									//draw tick label
									CString tickLabel;
									tickLabel.Format("%d", (x / 2) * m_iYTickSpace);

									CFont xFont;
									xFont.CreateFont(m_iXTickFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
										ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
										DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
									pDC->SelectObject(&xFont);
									pDC->GetTextMetrics(&tm);
									charWidth = tm.tmAveCharWidth;

									pDC->TextOut(tickXLocation - (tickLabel.GetLength() * charWidth / 2), m_iYApexPoint + 8, tickLabel);
								}
								m_iRightXTick = tickXLocation;
								pDC->SelectObject(pOldFont);
							}
						}
						break;
					case 3 :
						if(m_iGraphType != SCATTER_GRAPH)
						{
							POSITION pos;
							pos = m_pGraphSeries->GetHeadPosition();
							CGraphSeries* tmpSeries;
							for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
							{
								tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

								seriesSpace = m_xAxisWidth / m_pGraphSeries->GetCount();
								tickXLocation = m_iXApexPoint + ((x * seriesSpace) - (seriesSpace / 2));

								pDC->MoveTo(tickXLocation,m_iYApexPoint - 3);
								pDC->LineTo(tickXLocation,m_iYApexPoint + 3);

								if(!m_bInRedraw)
								{
									//draw tick label
									CString tickLabel;
									tickLabel = tmpSeries->GetLabel();
									if(!m_iXAxisAlign)  //horizontal
									{
										CFont xFont;
										xFont.CreateFont(m_iXTickFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
											ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
											DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
										pDC->SelectObject(&xFont);
										pDC->TextOut(tickXLocation - ((tickLabel.GetLength() * 8) / 2), m_iYApexPoint + (m_yAxisHeight / 2) + 8, tickLabel);
										pDC->SelectObject(pOldFont);
									}
									else
									{
										CFont sideFont2;
										sideFont2.CreateFont(m_iXTickFontSize, 0, (m_iXAxisAlign * 10), 0, 700, FALSE, FALSE, 0,
											ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
											DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
										pDC->SelectObject(&sideFont2);
										pDC->GetTextMetrics(&tm);
										charWidth = tm.tmAveCharWidth;
										if(m_iXAxisAlign < 180)
											pDC->TextOut(tickXLocation - 8, m_iYApexPoint + (m_yAxisHeight / 2) + 8 + (m_iXAxisLabelLength * charWidth), tickLabel);
										else
											pDC->TextOut(tickXLocation + 2, m_iYApexPoint + (m_yAxisHeight / 2) + 8, tickLabel);

										pDC->SelectObject(pOldFont);
									}
								}
								m_iRightXTick = tickXLocation;
							}
						}
						else
						{
							//scatter graphs will use the same tick marking on both axis lines
							seriesSpace = (m_xAxisWidth - 20) / m_iXNumTicks;
							for(int x = 1; x <= m_iYNumTicks; x++)  
							{
								tickXLocation = m_iXApexPoint + (x * seriesSpace);

								//draw tick mark
								pDC->MoveTo(tickXLocation, m_iYApexPoint - 3);
								pDC->LineTo(tickXLocation, m_iYApexPoint + 3);

								if(!m_bInRedraw)
								{
									//draw tick label
									CString tickLabel;
									tickLabel.Format("%d", x * m_iXTickSpace+m_iXMinTick);

									CFont xFont;
									xFont.CreateFont(m_iXTickFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
										ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
										DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
									pDC->SelectObject(&xFont);
									pDC->GetTextMetrics(&tm);
									charWidth = tm.tmAveCharWidth;

									pDC->TextOut(tickXLocation - (tickLabel.GetLength() * charWidth / 2), m_iYApexPoint + (m_yAxisHeight / 2) + 8, tickLabel);
								}
								m_iRightXTick = tickXLocation;
								pDC->SelectObject(pOldFont);
							}

						}
						break;
					case 4 :
						if(m_iGraphType != SCATTER_GRAPH)
						{
							POSITION pos;
							pos = m_pGraphSeries->GetHeadPosition();
							CGraphSeries* tmpSeries;
							seriesSpace = m_xAxisWidth / m_pGraphSeries->GetCount();
							for(x = 1; x <= m_pGraphSeries->GetCount() / 2; x++)
							{
								tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

								tickXLocation = m_iXApexPoint - (m_xAxisWidth / 2) + ((x * seriesSpace) - (seriesSpace / 2));

								pDC->MoveTo(tickXLocation,m_iYApexPoint - 3);
								pDC->LineTo(tickXLocation,m_iYApexPoint + 3);

								if(!m_bInRedraw)
								{
									//draw tick label
									CString tickLabel;
									tickLabel = tmpSeries->GetLabel();
									if(!m_iXAxisAlign)  //horizontal
									{
										CFont xFont;
										xFont.CreateFont(m_iXTickFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
											ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
											DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
										pDC->SelectObject(&xFont);
										pDC->TextOut(tickXLocation - ((tickLabel.GetLength() * 8) / 2), m_iYApexPoint + (m_yAxisHeight / 2) + 8, tickLabel);
										pDC->SelectObject(pOldFont);
									}
									else
									{
										CFont sideFont2;
										sideFont2.CreateFont(m_iXTickFontSize, 0, (m_iXAxisAlign * 10), 0, 700, FALSE, FALSE, 0,
											ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
											DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
										pDC->SelectObject(&sideFont2);
										pDC->GetTextMetrics(&tm);
										charWidth = tm.tmAveCharWidth;
										if(m_iXAxisAlign < 180)
											pDC->TextOut(tickXLocation - 8, m_iYApexPoint + (m_yAxisHeight / 2) + 8 + (m_iXAxisLabelLength * charWidth), tickLabel);
										else
											pDC->TextOut(tickXLocation + 2, m_iYApexPoint + (m_yAxisHeight / 2) + 8, tickLabel);

										pDC->SelectObject(pOldFont);
									}
								}
								m_iRightXTick = tickXLocation;
							}
							if((m_pGraphSeries->GetCount() % 2) > 0)
							{
								tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);
								
								tickXLocation = m_iXApexPoint;

								pDC->MoveTo(tickXLocation,m_iYApexPoint - 3);
								pDC->LineTo(tickXLocation,m_iYApexPoint + 3);

								if(!m_bInRedraw)
								{
									//draw tick label
									CString tickLabel;
									tickLabel = tmpSeries->GetLabel();
									if(!m_iXAxisAlign)  //horizontal
									{
										CFont xFont;
										xFont.CreateFont(m_iXTickFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
											ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
											DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
										pDC->SelectObject(&xFont);
										pDC->TextOut(tickXLocation - ((tickLabel.GetLength() * 8) / 2), m_iYApexPoint + (m_yAxisHeight / 2) + 8, tickLabel);
										pDC->SelectObject(pOldFont);
									}
									else
									{
										CFont sideFont2;
										sideFont2.CreateFont(m_iXTickFontSize, 0, (m_iXAxisAlign * 10), 0, 700, FALSE, FALSE, 0,
											ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
											DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
										pDC->SelectObject(&sideFont2);
										pDC->GetTextMetrics(&tm);
										charWidth = tm.tmAveCharWidth;
										if(m_iXAxisAlign < 180)
											pDC->TextOut(tickXLocation - 8, m_iYApexPoint + (m_yAxisHeight / 2) + 8 + (m_iXAxisLabelLength * charWidth), tickLabel);
										else
											pDC->TextOut(tickXLocation + 2, m_iYApexPoint + (m_yAxisHeight / 2) + 8, tickLabel);

										pDC->SelectObject(pOldFont);
									}
								}
								m_iRightXTick = tickXLocation;
								x++;
							}
							for(; x <= m_pGraphSeries->GetCount(); x++)
							{
								tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

								tickXLocation = m_iXApexPoint - (m_xAxisWidth / 2) + ((x * seriesSpace) - (seriesSpace / 2));

								pDC->MoveTo(tickXLocation,m_iYApexPoint - 3);
								pDC->LineTo(tickXLocation,m_iYApexPoint + 3);

								if(!m_bInRedraw)
								{
									//draw tick label
									CString tickLabel;
									tickLabel = tmpSeries->GetLabel();
									if(!m_iXAxisAlign)  //horizontal
									{
										CFont xFont;
										xFont.CreateFont(m_iXTickFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
											ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
											DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
										pDC->SelectObject(&xFont);
										pDC->TextOut(tickXLocation - ((tickLabel.GetLength() * 8) / 2), m_iYApexPoint + (m_yAxisHeight / 2) + 8, tickLabel);
										pDC->SelectObject(pOldFont);
									}
									else
									{
										CFont sideFont2;
										sideFont2.CreateFont(m_iXTickFontSize, 0, (m_iXAxisAlign * 10), 0, 700, FALSE, FALSE, 0,
											ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
											DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
										pDC->SelectObject(&sideFont2);
										pDC->GetTextMetrics(&tm);
										charWidth = tm.tmAveCharWidth;
										if(m_iXAxisAlign < 180)
											pDC->TextOut(tickXLocation - 8, m_iYApexPoint + (m_yAxisHeight / 2) + 8 + (m_iXAxisLabelLength * charWidth), tickLabel);
										else
											pDC->TextOut(tickXLocation + 2, m_iYApexPoint + (m_yAxisHeight / 2) + 8, tickLabel);

										pDC->SelectObject(pOldFont);
									}
								}
								m_iRightXTick = tickXLocation;
							}
						}
						else
						{
							//scatter graphs will use the same tick marking on both axis lines
							seriesSpace = (m_xAxisWidth - 20) / m_iYNumTicks;
							for(x = 1; x <= m_iYNumTicks / 2; x++)  
							{
								tickXLocation = m_iXApexPoint - (m_xAxisWidth / 2) + (x * seriesSpace);

								//draw tick mark
								pDC->MoveTo(tickXLocation, m_iYApexPoint + (m_yAxisHeight / 2) - 3);
								pDC->LineTo(tickXLocation, m_iYApexPoint + (m_yAxisHeight / 2) + 3);

								if(!m_bInRedraw)
								{
									//draw tick label
									CString tickLabel;
									tickLabel.Format("%d", x * m_iYTickSpace);

									CFont xFont;
									xFont.CreateFont(m_iXTickFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
										ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
										DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
									pDC->SelectObject(&xFont);
									pDC->GetTextMetrics(&tm);
									charWidth = tm.tmAveCharWidth;

									pDC->TextOut(tickXLocation - (tickLabel.GetLength() * charWidth / 2), m_iYApexPoint + 8, tickLabel);
								}
								m_iRightXTick = tickXLocation;
								pDC->SelectObject(pOldFont);
							}
							//draw the 0

							for(; x <= m_iYNumTicks; x++)  
							{
								tickXLocation = m_iXApexPoint - (m_xAxisWidth / 2) + (x * seriesSpace);

								//draw tick mark
								pDC->MoveTo(tickXLocation, m_iYApexPoint + (m_yAxisHeight / 2) - 3);
								pDC->LineTo(tickXLocation, m_iYApexPoint + (m_yAxisHeight / 2) + 3);

								if(!m_bInRedraw)
								{
									//draw tick label
									CString tickLabel;
									tickLabel.Format("%d", x * m_iYTickSpace);

									CFont xFont;
									xFont.CreateFont(m_iXTickFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
										ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
										DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
									pDC->SelectObject(&xFont);
									pDC->GetTextMetrics(&tm);
									charWidth = tm.tmAveCharWidth;

									pDC->TextOut(tickXLocation - (tickLabel.GetLength() * charWidth / 2), m_iYApexPoint + 8, tickLabel);
								}
								m_iRightXTick = tickXLocation;
								pDC->SelectObject(pOldFont);
							}
						}
						break;
					}
				break;
		case BAR_GRAPH_3D :
				seriesSpace = m_xAxisWidth  / m_pGraphSeries->GetCount();
				barWidth = (int)((seriesSpace * .8) / m_iSeriesSize);
				m_iDepth= barWidth/2;
				goto Draw3DAxis;

		case LINE_GRAPH_3D :
				m_iDepth = (int)(m_yAxisHeight * m_lfDepthRatio * m_iSeriesSize);
				goto Draw3DAxis;

		case STACKED_BAR_GRAPH_3D :
				m_iDepth = (int)(m_yAxisHeight * m_lfDepthRatio);

Draw3DAxis:
				m_iXApexPoint += m_iDepth;
				m_iYApexPoint -= m_iDepth;
				m_xAxisWidth -= m_iDepth;
				m_yAxisHeight -= m_iDepth;
				//draw y axis
				pDC->MoveTo(m_iXApexPoint, m_iYApexPoint);  
				pDC->LineTo(m_iXApexPoint, m_iYApexPoint - m_yAxisHeight);
				//draw x axis
				pDC->MoveTo(m_iXApexPoint, m_iYApexPoint);  
				pDC->LineTo(m_iXApexPoint + m_xAxisWidth, m_iYApexPoint);

				//adjust graph settings for 3D look
				m_iYApexPoint += m_iDepth;
				m_iXApexPoint -= m_iDepth;
				//foreground axis
				pDC->MoveTo(m_iXApexPoint, m_iYApexPoint +iTickLen);  
				pDC->LineTo(m_iXApexPoint, m_iYApexPoint - m_yAxisHeight);
				pDC->MoveTo(m_iXApexPoint - iTickLen, m_iYApexPoint);  
				pDC->LineTo(m_iXApexPoint + m_xAxisWidth, m_iYApexPoint);
				//connecting line at apex
				pDC->MoveTo(m_iXApexPoint, m_iYApexPoint);  
				pDC->LineTo(m_iXApexPoint + m_iDepth, m_iYApexPoint - m_iDepth);
				//connecting line at height
				pDC->MoveTo(m_iXApexPoint, m_iYApexPoint - m_yAxisHeight);  
				pDC->LineTo(m_iXApexPoint + m_iDepth, m_iYApexPoint - m_yAxisHeight - m_iDepth);
				//connecting line at width
				pDC->MoveTo(m_iXApexPoint + m_xAxisWidth, m_iYApexPoint);  
				pDC->LineTo(m_iXApexPoint + m_xAxisWidth + m_iDepth, m_iYApexPoint - m_iDepth);
				//top and right border lines
				pDC->MoveTo(m_iXApexPoint + m_iDepth, m_iYApexPoint - m_yAxisHeight - m_iDepth);
				pDC->LineTo(m_iXApexPoint + m_xAxisWidth + m_iDepth, m_iYApexPoint - m_yAxisHeight - m_iDepth);
				pDC->LineTo(m_iXApexPoint + m_xAxisWidth + m_iDepth, m_iYApexPoint - m_iDepth);

				//Tick marks ... and labels too
				//draw labels
				tFontSize = 16;
				if(m_iMaxWidth > m_iMaxHeight)
				{
					while((m_sAxisYLabel.GetLength() * (tFontSize / 2)) > m_iMaxHeight)
					{
						tFontSize -= 2;
					}
				}
				else
				{
					while((m_sAxisXLabel.GetLength() * (tFontSize / 2)) > m_iMaxWidth)
					{
						tFontSize -= 2;
					}
				}
				axisFont.CreateFont(tFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
					ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
				sideFont.CreateFont(tFontSize, 0, 900, 0, 700, FALSE, FALSE, 0,
					ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");

				pDC->SelectObject(&sideFont);
				pDC->GetTextMetrics(&tm);
				charWidth = tm.tmAveCharWidth;

				pDC->TextOut(10, (m_iYApexPoint - (m_yAxisHeight / 2)) + ((m_sAxisYLabel.GetLength() * charWidth) / 2), m_sAxisYLabel);

				pDC->SelectObject(&axisFont);
				pDC->GetTextMetrics(&tm);
				charWidth = tm.tmAveCharWidth;
				pDC->TextOut(m_iXApexPoint + (m_xAxisWidth / 2) - ((m_sAxisXLabel.GetLength() / 2) * charWidth), m_iMaxHeight - 5 - 6, m_sAxisXLabel);
				
				pDC->SelectObject(pOldFont);

				tickScale = 0.00;
				tickScale = m_yAxisHeight / m_iYNumTicks;

				//draw y axis ticks
				for(int y = 1; y <= m_iYNumTicks; y++)  
				{

					tickYLocation = m_iYApexPoint - (int)(y * tickScale);

					//draw tick mark
					pDC->MoveTo(m_iXApexPoint - 5, tickYLocation);
					pDC->LineTo(m_iXApexPoint, tickYLocation);

					COLORREF gridLineColor;
					CPen* pOldPen;

					//draw grid lines
					gridLineColor = DARK_GREY;
					CPen gridPen (PS_SOLID, 1, gridLineColor);
					pOldPen = pDC->SelectObject(&gridPen);
					pDC->MoveTo(m_iXApexPoint, tickYLocation);
					pDC->LineTo(m_iXApexPoint + m_iDepth, tickYLocation - m_iDepth);
					if(m_bGraphHasGridLines)
					{
						pDC->LineTo(m_iXApexPoint + m_xAxisWidth + m_iDepth, tickYLocation - m_iDepth);
					}
					pDC->SelectObject(pOldPen);

					//draw tick label
					CString tickLabel;
					tickLabel.Format("%d", m_iYMinTick + (y * m_iYTickSpace));

					CFont yFont;
					yFont.CreateFont(m_iYTickFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
						ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
						DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
					pDC->SelectObject(&yFont);

					pDC->TextOut(m_iXApexPoint - 10 - (tickLabel.GetLength() * (m_iYTickFontSize / 2)), tickYLocation - 6, tickLabel);
					m_iTopYTick = tickYLocation;
					pDC->SelectObject(pOldFont);

					//draw 1/2 tick line (grey)
					int midTickYLocation;
					midTickYLocation = m_iYApexPoint - (int)(y * tickScale * .5) - (int)((y - 1) * tickScale * .5);


					//draw tick mark
					pDC->MoveTo(m_iXApexPoint - 3/*(int)(m_iDepth * .2)*/, midTickYLocation);
					pDC->LineTo(m_iXApexPoint, midTickYLocation);

					//draw grid lines
					gridLineColor = LIGHT_GREY;
					CPen midGridPen (PS_SOLID, 1, gridLineColor);
					pOldPen = pDC->SelectObject(&midGridPen);
					pDC->MoveTo(m_iXApexPoint, midTickYLocation);
					pDC->LineTo(m_iXApexPoint + m_iDepth, midTickYLocation - m_iDepth);
					if(m_bGraphHasGridLines)
					{
						pDC->LineTo(m_iXApexPoint + m_xAxisWidth + m_iDepth, midTickYLocation - m_iDepth);
					}
					pDC->SelectObject(pOldPen);
				}

				//draw X axis tick marks
				POSITION pos;
				pos = m_pGraphSeries->GetHeadPosition();
				CGraphSeries* tmpSeries;
				for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
				{
					tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

					seriesSpace = m_xAxisWidth / m_pGraphSeries->GetCount();
					tickXLocation = m_iXApexPoint + ((x * seriesSpace) - (seriesSpace / 2));

					//unlike normal series, we put ticks here
					//on the outsides of the series
					pDC->MoveTo(m_iXApexPoint + (x * seriesSpace),m_iYApexPoint + 6);
					pDC->LineTo(m_iXApexPoint + (x * seriesSpace),m_iYApexPoint);
					pDC->LineTo(m_iXApexPoint + (x * seriesSpace) + m_iDepth,m_iYApexPoint - m_iDepth);

					//draw tick label
					CString tickLabel;
					tickLabel = tmpSeries->GetLabel();
					CFont sideFont2;
					sideFont2.CreateFont(m_iXTickFontSize, 0, (m_iXAxisAlign * 10), 0, 700, FALSE, FALSE, 0,
						ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
						DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
					pDC->SelectObject(&sideFont2);

					if(!m_iXAxisAlign)  //horizontal
						pDC->TextOut(tickXLocation - ((tickLabel.GetLength() * 8) / 2), m_iYApexPoint + 8, tickLabel);
					else
					{
						pDC->GetTextMetrics(&tm);
						charWidth = tm.tmAveCharWidth;
						if(m_iXAxisAlign < 180)
							pDC->TextOut(tickXLocation - 8, m_iYApexPoint + 8 + (m_iXAxisLabelLength * charWidth), tickLabel);
						else
							pDC->TextOut(tickXLocation + 2, m_iYApexPoint + 8, tickLabel);

						pDC->SelectObject(pOldFont);
					}
					m_iRightXTick = tickXLocation;
				}
				break;
	}

	pDC->SelectObject (pOldFont);
}

void CGraphView::AddSeries(CGraphSeries* dataSet)
{
	int numData = 0;

	numData = dataSet->GetDataCount();
	if(numData==0||numData>10000)return;

	if(numData > m_iSeriesSize)
	{
		m_iSeriesSize = numData;
	}

	m_pGraphSeries->AddTail(dataSet);
}

void CGraphView::SetXAxisLabel(CString label)
{
	m_sAxisXLabel = label;
	m_iXAxisLabelLength = m_sAxisXLabel.GetLength();
}

void CGraphView::SetYAxisLabel(CString label)
{
	m_sAxisYLabel = label;
	m_iYAxisLabelLength = m_sAxisYLabel.GetLength();
}

void CGraphView::DrawSeries(CDC* pDC)
{
	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;

	switch(m_iGraphType)
	{
		case BAR_GRAPH :
				 DrawBarSeries(pDC);
				 break;
		case LINE_GRAPH :
				 DrawLineSeries(pDC);
				 break;
		case PIE_GRAPH :
				 DrawPieSeries(pDC);
				 break;
		case SCATTER_GRAPH :
				 DrawScatterSeries(pDC);
				 break;
		case BOX_WHISKER_GRAPH :
				 DrawBoxWhiskerSeries(pDC);
				 break;
		case STACKED_BAR_GRAPH :
				 DrawStackedBarSeries(pDC);
				 break;
		case XY_LINE_GRAPH :
				 DrawXYLineSeries(pDC);
				 break;
//		case RADAR_GRAPH :
//				 DrawRadarSeries(pDC);
//				 break;
		case BAR_GRAPH_3D :
				 Draw3DBarSeries(pDC);
				 break;
		case LINE_GRAPH_3D :
				 Draw3DLineSeries(pDC);
				 break;
		case STACKED_BAR_GRAPH_3D :
				 Draw3DStackedBarSeries(pDC);
				 break;
		case PIE_GRAPH_3D :
				 Draw3DPieSeries(pDC);
				 break;
		default :
				 AfxMessageBox("No graph type to display");
				 break;
	}

}

void CGraphView::SetGroupProperty(	int					iDataGroup,
									CString				sLabel,
									COLORREF			color,
									int					iMarkerSize,
									int					iLineWidth,
									enumMarkerType		eMarkerType)
{
	if(m_iGraphType != SCATTER_GRAPH)	//scatter graphs don't need legends
	{
		if(sLabel!="")
		{
			m_bGraphHasLegend = TRUE;
			if(m_iLegendMaxText < sLabel.GetLength())
			{
				m_iLegendMaxText = sLabel.GetLength();
			}
		}

		m_graphProperty.Set(iDataGroup,
							sLabel,
							color,
							iMarkerSize,
							iLineWidth,
							eMarkerType);

	}
}

int CGraphView::DrawLegend(CDC* pDC)
{
	//determine size of legend
	//12 chars per m_iSeriesSize + 6 for spacing (3 top and bottom) 
	//+ 1 set for label title(3+12+6) + rectangle (2 chars) + 3 for final bottom buffer
	int legendHeight = 23 + (m_iSeriesSize * 18) + 3;
	int legendL, legendT, legendR, legendB;
	int barL, barT, barR, barB;
	TEXTMETRIC tm;

	legendT = (m_iMaxHeight / 2) - (legendHeight / 2);
	legendB = legendT + legendHeight;
	legendR = m_iMaxWidth - 5;
	legendL = legendR - ((m_iLegendMaxText * (int)(m_iLegendFontSize * .66)) + 25);
		//allows 50 pixels for display of legend bar 45 + 5 space.
	m_iLegendWidth = legendR - legendL;


	pDC->Rectangle(legendL, legendT, legendR, legendB);
	CFont legendTitleFont;
	legendTitleFont.CreateFont(16, 0, 0, 0, 0, FALSE, FALSE, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"ËÎÌå"); //Times New Roman"); //Arial;

	CFont* pOldFont = (CFont*) pDC->SelectObject(&legendTitleFont);
	pDC->GetTextMetrics(&tm);
	int charWidth = tm.tmAveCharWidth;
	pDC->TextOut(legendL + (m_iLegendWidth / 2) - (3 * charWidth), 
					legendT + 3, "Í¼Àý");
	pDC->SelectObject(pOldFont);

	CFont legendFont;

	legendFont.CreateFont(m_iLegendFontSize, 0, 0, 0, 100, FALSE, FALSE, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"ËÎÌå"); //Times New Roman");
	pOldFont = (CFont*) pDC->SelectObject(&legendFont);

	for(int i = 0; i < m_iSeriesSize; i++)
	{
		//top "Legend" text will use 12 + 3 top + 6 bottom (21 total)
		//each legend label will need 3 chars on top, so the 24 in the offset
		//each label than uses 12 + 3 below + 3 above next label, so 18
		// in the i * offset.  


		pDC->TextOut(legendL + 5, legendT + 24 + (i * 18) + 1, m_graphProperty.GetLegendText(i));

		//draw bar
		COLORREF barColor;
		barColor = GetColor(i);
		CBrush brush (barColor);
		CBrush* pOldBrush;
		pOldBrush = pDC->SelectObject(&brush);

		barL = legendL + 5 + (m_iLegendMaxText * (m_iLegendFontSize / 2)) + 5;
		barT = legendT + 24 + (i * 18) + 1, m_graphProperty.GetLegendText(i);
		barR = legendR - 5;
		barB = barT + 12;
		pDC->Rectangle(barL, barT, barR, barB);

		pDC->SelectObject(pOldBrush);
	}

	pDC->SelectObject(pOldFont);


	return legendL;
}

void CGraphView::SetGraphTitle(CString title)
{
	m_sGraphTitle = title;
}

void CGraphView::SetGraphFoot(CString sFoot)
{
	m_sGraphFoot= sFoot;
}

void CGraphView::SetXTickFontSize(int size)
{
	m_iXTickFontSize = size;
}

void CGraphView::SetYTickFontSize(int size)
{
	m_iYTickFontSize = size;
}

void CGraphView::SetLegendFontSize(int size)
{
	m_iLegendFontSize = size;
}


int CGraphView::PrintGraph(CDC* pDC, CPrintInfo* pInfo)
{
	CString		str;
	CFont		graphTitleFont, textFont;
	TEXTMETRIC	tm;
	CString tickLabel;

	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return 0;


	m_iMaxHeight = m_iPGraphT - m_iPGraphB; 
	m_iMaxWidth = m_iPGraphR - m_iPGraphL; 

    //titleFont is 24 point, bold
	graphTitleFont.CreateFont(-480, 0, 0, 0, 700, FALSE, FALSE, 0, ANSI_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH || FF_ROMAN,
			"Times New Roman");

	//textFont is 12 point
	textFont.CreateFont(-240, 0, 0, 0, 400, FALSE, FALSE, 0, ANSI_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH || FF_ROMAN,
			"Times New Roman");

	pDC->SetMapMode(MM_TWIPS);
	CFont* pOldFont = (CFont*) pDC->SelectObject(&graphTitleFont);
	pDC->GetTextMetrics(&tm);

	int charWidth = tm.tmAveCharWidth;
	int charHeight = tm.tmHeight;
	//next line is centered....trust me !!
	pDC->TextOut(m_iPGraphL + (m_iMaxWidth / 2) - ((m_sGraphTitle.GetLength() / 2) * charWidth), m_iPGraphT - 50, m_sGraphTitle);

	pDC->SelectObject(pOldFont);
	
	if((m_iGraphType == PIE_GRAPH) || (m_iGraphType == PIE_GRAPH_3D))
	{
		m_xAxisWidth = m_iPGraphR - m_iPGraphL - 200;
		m_yAxisHeight = m_iMaxHeight - 600 - charHeight;
		m_iXApexPoint = m_iPGraphL + 500;
		m_iYApexPoint = m_iPGraphB + 500;
	}
	else
	{
		//compute label size for axis alignment
		CFont sideFont, axisFont;
		int tFontSize;
		tFontSize = 16;
		if(m_iMaxWidth > m_iMaxHeight)
		{
			while((m_sAxisYLabel.GetLength() * (tFontSize / 2)) > m_iMaxHeight)
			{
				tFontSize -= 2;
			}
		}
		else
		{
			while((m_sAxisXLabel.GetLength() * (tFontSize / 2)) > m_iMaxWidth)
			{
				tFontSize -= 2;
			}
		}
		//set tFontSize for printer
		tFontSize *= -20;
		axisFont.CreateFont(tFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
			ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
		sideFont.CreateFont(tFontSize, 0, 900, 0, 700, FALSE, FALSE, 0,
			ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");

		CFont* pOldFont = (CFont*) pDC->SelectObject(&sideFont);
		pDC->GetTextMetrics(&tm);
		int charWidth = tm.tmAveCharWidth;
		int labelHeight = tm.tmHeight + 50;
		if(m_sAxisXLabel.GetLength() == 0)
			labelHeight = 0;

		pDC->SelectObject(pOldFont);
		
		tickLabel.Format("%d", m_iYMaxTick);


		//determine axis specifications 
		m_iXApexPoint = m_iPGraphL + (tickLabel.GetLength() * charWidth) + labelHeight + 100; 

		if(!m_iXAxisAlign)  //horizontal
		{
			m_iYApexPoint = m_iPGraphB + 50 + (labelHeight * 2);		
		}
		else
		{
			m_iYApexPoint = m_iPGraphB + labelHeight + (m_iXAxisLabelLength * labelHeight);
		}
		m_yAxisHeight = m_iPGraphT - 200 - charHeight/*this is title height*/ - m_iYApexPoint;
		m_xAxisWidth = (m_iMaxWidth - 100) - m_iXApexPoint;
	}

	//draw legend
	if(m_bGraphHasLegend)
	{
		int legendL = PrintLegend(pDC);
		m_xAxisWidth = legendL - 200 - m_iXApexPoint;
	}

	if(m_iGraphType != 2)  //not pie
	{
		//draw axis lines
		PrintAxis(pDC);
	}

	//draw series data and labels
	PrintSeries(pDC);

	
	//update m_iPGraphB value to pad some space below the graph
	m_iPGraphB -= 90;
	return m_iPGraphB;
}


int CGraphView::PrintLegend(CDC *pDC)
{
	CFont		legendLabelFont, legendTitleFont;
	TEXTMETRIC	tm;

	int legendL, legendT, legendR, legendB;
	int barL, barT, barR, barB;

	//legendLabelFont is 12 point
	legendLabelFont.CreateFont(-240, 0, 0, 0, 400, FALSE, FALSE, 0, ANSI_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH || FF_ROMAN,
			"ËÎÌå"); //Times New Roman

	//legendTitleFont is 16 point
	legendTitleFont.CreateFont(-320, 0, 0, 0, 400, FALSE, FALSE, 0, ANSI_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH || FF_ROMAN,
			"ËÎÌå");

	CFont* pOldFont = (CFont*) pDC->SelectObject(&legendTitleFont);
	pDC->GetTextMetrics(&tm);
	int legendCharWidth = tm.tmAveCharWidth;
	legendT = (((m_iPGraphB - m_iPGraphT) / 2) + m_iPGraphT) + (((m_iSeriesSize + 1) / 2) * 240 + 300);
	legendB = (((m_iPGraphB - m_iPGraphT) / 2) + m_iPGraphT) - (((m_iSeriesSize + 1) / 2) * 240 + 300);
	legendR = m_iPGraphR - 100;
	legendL = legendR - ((m_graphProperty.GetLegendLength() * legendCharWidth) + 1000);
	m_iLegendWidth = legendR - legendL;

	pDC->Rectangle(legendL, legendT, legendR, legendB);
	pDC->TextOut(legendL + (m_iLegendWidth / 2) - 360, 
					legendT - 160, "Í¼Àý");
	pDC->SelectObject(pOldFont);
	for(int i = 0; i < m_iSeriesSize; i++)
	{
		pOldFont = (CFont*) pDC->SelectObject(&legendLabelFont);
		pDC->GetTextMetrics(&tm);

		int charWidth = tm.tmMaxCharWidth;
		int charHeight = tm.tmHeight;

		CString valuStr;
		pDC->TextOut(legendL + 100, legendT - 500 - (i * charHeight), m_graphProperty.GetLegendText(i));
		pDC->SelectObject(pOldFont);

		//draw bar
		COLORREF barColor;
		barColor = GetColor(i);
		CBrush brush (barColor);
		CBrush* pOldBrush;
		pOldBrush = pDC->SelectObject(&brush);

		//barT uses a 560 offset below,...why?
		//would be 500, but barB is only using 120 height,
		//when it should be 240 (but 240 puts bars too close
		//together, so I'm setting them to 1/2 size.
		//therefore, I want to adjust my barT by half of that
		//adjustment ( 1/2 of 120 is 60).  This basically centers
		//the bar 1/2 way in text, and makes it 1/2 the height
		//of text
		barL = legendL + 50 + (m_iLegendMaxText * charWidth / 2);
		barT = legendT - 560 - (i * charHeight);
		barR = legendR - 100;
		barB = barT - 120;
		pDC->Rectangle(barL, barT, barR, barB);

		pDC->SelectObject(pOldBrush);
	
	}
	return legendL;
}

void CGraphView::PrintAxis(CDC *pDC)
{
	TEXTMETRIC tm;
	pDC->SetTextColor(BLACK);
	CFont sideFont, axisFont;
	int charWidth;
	int charHeight;
	int tFontSize;
	double tickScale;
	int tickYLocation;
	int seriesSpace;
	int tickXLocation;

	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;

	switch(m_iGraphType)
	{
		case BAR_GRAPH :
		case LINE_GRAPH :
		case SCATTER_GRAPH :
		case BOX_WHISKER_GRAPH :
//		case RADAR_GRAPH :
		case STACKED_BAR_GRAPH :
		case XY_LINE_GRAPH :
				//draw y axis
				pDC->MoveTo(m_iXApexPoint, m_iYApexPoint);  
					//unlike drawAxis, the lineto below uses a + in the y
					//coordinate because printer uses negative locations
					//when going down a page, so use a + to move the line
					//upwards...
				pDC->LineTo(m_iXApexPoint, m_iYApexPoint + m_yAxisHeight);

				//draw x axis
				pDC->MoveTo(m_iXApexPoint, m_iYApexPoint);  
				pDC->LineTo(m_iXApexPoint + m_xAxisWidth, m_iYApexPoint);

				//draw labels
				tFontSize = 16;
				if(m_iMaxWidth > m_iMaxHeight)
				{
					while((m_sAxisYLabel.GetLength() * (tFontSize / 2)) > m_iMaxHeight)
					{
						tFontSize -= 2;
					}
				}
				else
				{
					while((m_sAxisXLabel.GetLength() * (tFontSize / 2)) > m_iMaxWidth)
					{
						tFontSize -= 2;
					}
				}
				tFontSize *= 20;
				axisFont.CreateFont(tFontSize, 0, 0, 0, 700, FALSE, FALSE, 0,
					ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
				sideFont.CreateFont(tFontSize, 0, 2700, 0, 700, FALSE, FALSE, 0,
					ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
				CFont* pOldFont;
				pOldFont = (CFont*) pDC->SelectObject(&sideFont);
				pDC->GetTextMetrics(&tm);
				charWidth = tm.tmAveCharWidth;
				charHeight = tm.tmHeight;

				pDC->TextOut(m_iPGraphL + 10, m_iPGraphT - (m_iMaxHeight / 2) - ((m_sAxisYLabel.GetLength() / 2) * charHeight), m_sAxisYLabel);

				pDC->SelectObject(&axisFont);
				pDC->GetTextMetrics(&tm);
				charWidth = tm.tmAveCharWidth;

				pDC->TextOut(m_iXApexPoint + (m_xAxisWidth / 2) - ((m_sAxisXLabel.GetLength() / 2) * charWidth), m_iPGraphB + 50 + charHeight, m_sAxisXLabel);

				pDC->SelectObject(pOldFont);

				tickScale = 0.00;
				tickScale = (m_yAxisHeight - 100) / m_iYNumTicks;

				//draw y axis ticks
				for(int y = 1; y <= m_iYNumTicks; y++)  
				{
					tickYLocation = m_iYApexPoint + (int)(y * tickScale);

					//draw tick mark
					pDC->MoveTo(m_iXApexPoint - 60, tickYLocation);
					pDC->LineTo(m_iXApexPoint + 60, tickYLocation);

					if(m_bGraphHasGridLines)
					{
						//draw grid lines
						COLORREF gridLineColor;
						gridLineColor = DARK_GREY;
						CBrush gridBrush (gridLineColor);
						CBrush* pOldBrush;
						pOldBrush = pDC->SelectObject(&gridBrush);
						pDC->MoveTo(m_iXApexPoint, tickYLocation);
						pDC->LineTo(m_iXApexPoint + m_xAxisWidth, tickYLocation);
						pDC->SelectObject(pOldBrush);
					}

					//draw tick label
					CString tickLabel;
					tickLabel.Format("%d", m_iYMinTick + (y * m_iYTickSpace));

					CFont yFont;
					yFont.CreateFont(m_iYTickFontSize * 20, 0, 0, 0, 700, FALSE, FALSE, 0,
						ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
						DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
					pOldFont = (CFont*) pDC->SelectObject(&yFont);

					pDC->TextOut(m_iXApexPoint - 200 - (tickLabel.GetLength() * (m_iYTickFontSize / 2) * 20), tickYLocation + 120, tickLabel);

					m_iPTopYTick = tickYLocation;
					pDC->SelectObject(pOldFont);

				}

				//draw X axis tick marks
				if(m_iGraphType != SCATTER_GRAPH)
				{
					POSITION pos;
					pos = m_pGraphSeries->GetHeadPosition();
					CGraphSeries* tmpSeries;
					for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
					{
						tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

						int seriesSpace;
						int tickXLocation;
						seriesSpace = m_xAxisWidth / m_pGraphSeries->GetCount();
						tickXLocation = m_iXApexPoint + ((x * seriesSpace) - (seriesSpace / 2));

						pDC->MoveTo(tickXLocation,m_iYApexPoint - 60);
						pDC->LineTo(tickXLocation,m_iYApexPoint + 60);

						//draw tick label
						CString tickLabel;
						tickLabel = tmpSeries->GetLabel();
						if(!m_iXAxisAlign)  //horizontal
							pDC->TextOut(tickXLocation - ((tickLabel.GetLength() / 2) * (m_iXTickFontSize * 10)), m_iYApexPoint - 160, tickLabel);
						else
						{
							CFont sideFont2;
							sideFont2.CreateFont(m_iXTickFontSize * 20, 0, ((360 - m_iXAxisAlign) * 10), 0, 700, FALSE, FALSE, 0,
								ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
								DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
							pOldFont = (CFont*) pDC->SelectObject(&sideFont2);
							pDC->GetTextMetrics(&tm);
							charWidth = tm.tmAveCharWidth;
							if(m_iXAxisAlign < 180)
								pDC->TextOut(tickXLocation - (m_iXTickFontSize * 10), m_iYApexPoint - (m_iXTickFontSize * 10) - (m_iXAxisLabelLength * charWidth), tickLabel);
							else
								pDC->TextOut(tickXLocation + (m_iXTickFontSize * 10), m_iYApexPoint - 160, tickLabel);

						}
						m_iPRightXTick = tickXLocation;
						pDC->SelectObject(pOldFont);
					}
				}
				else
				{
					//scatter graphs will use the same tick marking on both axis lines
					int seriesSpace;
					seriesSpace = (m_xAxisWidth - 200) / m_iYNumTicks;
					for(int x = 1; x <= m_iYNumTicks; x++)  
					{
						int tickXLocation;
						tickXLocation = m_iXApexPoint + (x * seriesSpace);

						//draw tick mark
						pDC->MoveTo(tickXLocation, m_iYApexPoint - 60);
						pDC->LineTo(tickXLocation, m_iYApexPoint + 60);

						//draw tick label
						CString tickLabel;
						tickLabel.Format("%d", x * m_iYTickSpace);

						CFont xFont;
						xFont.CreateFont(m_iXTickFontSize * 20, 0, 0, 0, 700, FALSE, FALSE, 0,
							ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
							DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
						pOldFont = (CFont*) pDC->SelectObject(&xFont);
						pDC->GetTextMetrics(&tm);
						charWidth = tm.tmAveCharWidth;

						pDC->TextOut(tickXLocation - (tickLabel.GetLength() * charWidth / 2), m_iYApexPoint - 160, tickLabel);

						m_iPRightXTick = tickXLocation;
						pDC->SelectObject(pOldFont);
					}
				}
				break;
		case BAR_GRAPH_3D :
		case LINE_GRAPH_3D :
		case STACKED_BAR_GRAPH_3D :
				m_iDepth = (int)(m_yAxisHeight * .05);
				m_iXApexPoint += m_iDepth;
				m_iYApexPoint += m_iDepth;
				m_xAxisWidth -= m_iDepth;
				m_yAxisHeight -= m_iDepth;
				//draw y axis
				pDC->MoveTo(m_iXApexPoint, m_iYApexPoint);  
				pDC->LineTo(m_iXApexPoint, m_iYApexPoint + m_yAxisHeight);
				//draw x axis
				pDC->MoveTo(m_iXApexPoint, m_iYApexPoint);  
				pDC->LineTo(m_iXApexPoint + m_xAxisWidth, m_iYApexPoint);

				//adjust graph settings for 3D look
				m_iYApexPoint -= m_iDepth;
				m_iXApexPoint -= m_iDepth;
				//foreground axis
				pDC->MoveTo(m_iXApexPoint, m_iYApexPoint - (int)(m_iDepth * .5));  
				pDC->LineTo(m_iXApexPoint, m_iYApexPoint + m_yAxisHeight);
				pDC->MoveTo(m_iXApexPoint - (int)(m_iDepth * .5), m_iYApexPoint);  
				pDC->LineTo(m_iXApexPoint + m_xAxisWidth, m_iYApexPoint);
				//connecting line at apex
				pDC->MoveTo(m_iXApexPoint, m_iYApexPoint);  
				pDC->LineTo(m_iXApexPoint + m_iDepth, m_iYApexPoint + m_iDepth);
				//connecting line at height
				pDC->MoveTo(m_iXApexPoint, m_iYApexPoint + m_yAxisHeight);  
				pDC->LineTo(m_iXApexPoint + m_iDepth, m_iYApexPoint + m_yAxisHeight + m_iDepth);
				//connecting line at width
				pDC->MoveTo(m_iXApexPoint + m_xAxisWidth, m_iYApexPoint);  
				pDC->LineTo(m_iXApexPoint + m_xAxisWidth + m_iDepth, m_iYApexPoint + m_iDepth);
				//top and right border lines
				pDC->MoveTo(m_iXApexPoint + m_iDepth, m_iYApexPoint + m_yAxisHeight + m_iDepth);
				pDC->LineTo(m_iXApexPoint + m_xAxisWidth + m_iDepth, m_iYApexPoint + m_yAxisHeight + m_iDepth);
				pDC->LineTo(m_iXApexPoint + m_xAxisWidth + m_iDepth, m_iYApexPoint + m_iDepth);

				//Tick marks ... and labels too
				//draw labels
				tFontSize = 16;
				if(m_iMaxWidth > m_iMaxHeight)
				{
					while((m_sAxisYLabel.GetLength() * (tFontSize / 2)) > m_iMaxHeight)
					{
						tFontSize -= 2;
					}
				}
				else
				{
					while((m_sAxisXLabel.GetLength() * (tFontSize / 2)) > m_iMaxWidth)
					{
						tFontSize -= 2;
					}
				}
				axisFont.CreateFont(tFontSize * 20, 0, 0, 0, 700, FALSE, FALSE, 0,
					ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
				sideFont.CreateFont(tFontSize * 20, 0, 2700, 0, 700, FALSE, FALSE, 0,
					ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");

				pOldFont = (CFont*) pDC->SelectObject(&sideFont);
				pDC->GetTextMetrics(&tm);
				charWidth = tm.tmAveCharWidth;
				charHeight = tm.tmHeight;

				pDC->TextOut(m_iPGraphL + 10, m_iPGraphT - (m_iMaxHeight / 2) - ((m_sAxisYLabel.GetLength() * charWidth) / 2), m_sAxisYLabel);

				pDC->SelectObject(&axisFont);
				pDC->GetTextMetrics(&tm);
				charWidth = tm.tmAveCharWidth;
				pDC->TextOut(m_iXApexPoint + (m_xAxisWidth / 2) - ((m_sAxisXLabel.GetLength() / 2) * charWidth), m_iPGraphB + 50 + charHeight, m_sAxisXLabel);
				
				pDC->SelectObject(pOldFont);

				//to allow scalability (height may be less than tickRange)
				tickScale = 0.00;
				tickScale = m_yAxisHeight / m_iYNumTicks;

				//draw y axis ticks
				for(int y = 1; y <= m_iYNumTicks; y++)  
				{
					tickYLocation = m_iYApexPoint + (int)(y * tickScale);

					//draw tick mark
					pDC->MoveTo(m_iXApexPoint - (int)(m_iDepth * .5), tickYLocation);
					pDC->LineTo(m_iXApexPoint, tickYLocation);

					COLORREF gridLineColor;
					CPen* pOldPen;
					if(m_bGraphHasGridLines)
					{
						//draw grid lines
						gridLineColor = DARK_GREY;
						CPen gridPen (PS_SOLID, 1, gridLineColor);
						pOldPen = pDC->SelectObject(&gridPen);
						pDC->MoveTo(m_iXApexPoint, tickYLocation);
						pDC->LineTo(m_iXApexPoint + m_iDepth, tickYLocation + m_iDepth);
						pDC->LineTo(m_iXApexPoint + m_xAxisWidth + m_iDepth, tickYLocation + m_iDepth);
						pDC->SelectObject(pOldPen);
					}

					//draw tick label
					CString tickLabel;
					tickLabel.Format("%d", y * m_iYTickSpace);

					CFont yFont;
					yFont.CreateFont(m_iYTickFontSize * 20, 0, 0, 0, 700, FALSE, FALSE, 0,
						ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
						DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
					pOldFont = (CFont*) pDC->SelectObject(&yFont);

					pDC->TextOut(m_iXApexPoint - 200 - (tickLabel.GetLength() * ((m_iYTickFontSize / 2) * 20)), tickYLocation + 120, tickLabel);
					m_iTopYTick = tickYLocation;
					pDC->SelectObject(pOldFont);

					//draw 1/2 tick line (grey)
					int midTickYLocation;
					midTickYLocation = m_iYApexPoint + (int)(y * tickScale * .5) + (int)((y - 1) * tickScale * .5);

					//draw tick mark
					pDC->MoveTo(m_iXApexPoint - (int)(m_iDepth * .5), midTickYLocation);
					pDC->LineTo(m_iXApexPoint, midTickYLocation);

					if(m_bGraphHasGridLines)
					{
						//draw grid lines
						gridLineColor = LIGHT_GREY;
						CPen midGridPen (PS_SOLID, 1, gridLineColor);
						pOldPen = pDC->SelectObject(&midGridPen);
						pDC->MoveTo(m_iXApexPoint, midTickYLocation);
						pDC->LineTo(m_iXApexPoint + m_iDepth, midTickYLocation + m_iDepth);
						pDC->LineTo(m_iXApexPoint + m_xAxisWidth + m_iDepth, midTickYLocation + m_iDepth);
						pDC->SelectObject(pOldPen);
					}
				}

				//draw X axis tick marks
				POSITION pos;
				pos = m_pGraphSeries->GetHeadPosition();
				CGraphSeries* tmpSeries;
				for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
				{
					tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

					seriesSpace = m_xAxisWidth / m_pGraphSeries->GetCount();
					tickXLocation = m_iXApexPoint + ((x * seriesSpace) - (seriesSpace / 2));

					//unlike normal series, we put ticks here
					//on the outsides of the series
					pDC->MoveTo(m_iXApexPoint + (x * seriesSpace),m_iYApexPoint - (int)(m_iDepth * .5));
					pDC->LineTo(m_iXApexPoint + (x * seriesSpace),m_iYApexPoint);
					pDC->LineTo(m_iXApexPoint + (x * seriesSpace) + m_iDepth,m_iYApexPoint + m_iDepth);

					//draw tick label
					CString tickLabel;
					tickLabel = tmpSeries->GetLabel();
					if(!m_iXAxisAlign)  //horizontal
						pDC->TextOut(tickXLocation - ((tickLabel.GetLength() / 2) * (m_iXTickFontSize * 10)), m_iYApexPoint - 160, tickLabel);
					else
					{
						CFont sideFont2;
						sideFont2.CreateFont(m_iXTickFontSize * 20, 0, (m_iXAxisAlign * 10), 0, 700, FALSE, FALSE, 0,
							ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
							DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
						pOldFont = (CFont*) pDC->SelectObject(&sideFont2);
						pDC->GetTextMetrics(&tm);
						charWidth = tm.tmAveCharWidth;
						if(m_iXAxisAlign < 180)
							pDC->TextOut(tickXLocation - (m_iXTickFontSize * 10), m_iYApexPoint - (m_iXTickFontSize * 10) - (m_iXAxisLabelLength * charWidth), tickLabel);
						else
							pDC->TextOut(tickXLocation + (m_iXTickFontSize * 10), m_iYApexPoint - 160, tickLabel);

						pDC->SelectObject(pOldFont);
					}
					m_iPRightXTick = tickXLocation;
				}
			break;
	}
}

void CGraphView::PrintSeries(CDC *pDC)
{
	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;

	switch(m_iGraphType)
	{
		case BAR_GRAPH :
				 PrintBarSeries(pDC);
				 break;
		case LINE_GRAPH :
				 PrintLineSeries(pDC);
				 break;
		case PIE_GRAPH :
				 PrintPieSeries(pDC);
				 break;
		case SCATTER_GRAPH :
				 PrintScatterSeries(pDC);
				 break;
		case BOX_WHISKER_GRAPH :
				 PrintBoxWhiskerSeries(pDC);
				 break;
		case STACKED_BAR_GRAPH :
				 PrintStackedBarSeries(pDC);
				 break;
		case XY_LINE_GRAPH :
				 PrintXYLineSeries(pDC);
				 break;
//		case RADAR_GRAPH :
//				 PrintRadarSeries(pDC);
//				 break;
		case BAR_GRAPH_3D :
				 Print3DBarSeries(pDC);
				 break;
		case LINE_GRAPH_3D :
				 Print3DLineSeries(pDC);
				 break;
		case STACKED_BAR_GRAPH_3D :
				 Print3DStackedBarSeries(pDC);
				 break;
		case PIE_GRAPH_3D :
				 Print3DPieSeries(pDC);
				 break;
		default :
				 AfxMessageBox("No graph type to print");
				 break;
	}
}

void CGraphView::SetMargins(int top, int bottom, int left, int right, int graphTop)
{
	//page margins for portrait or landscape distinction
	m_iTopMargin = top;
	m_iBottomMargin = bottom;
	m_iLeftMargin = left;
	m_iRightMargin = right;

	//set up rectangle area for showing the graph
	m_iPGraphL = m_iLeftMargin;
	m_iPGraphT = graphTop;
	m_iPGraphB = m_iPGraphT - 5760/*7200*/;
	m_iPGraphR = m_iRightMargin;

	if(m_iPGraphB < m_iBottomMargin)
		m_iPGraphB = m_iBottomMargin; 

}

void CGraphView::SetGridLines(BOOL hasGridLines)
{
	m_bGraphHasGridLines = hasGridLines;
}

void CGraphView::SetTickLimits(CDC *pDC)
{
	double dMinX=99999999999.9;
	double dMaxX=-99999999999.9;
	double dMinY=99999999999.9;
	double dMaxY=-99999999999.9;


	POSITION pos,posSer;
	CGraphSeries* tmpSeries;
	CGraphDataSet* pDataSet=NULL;
	double dSumY=0.0;
	pos = m_pGraphSeries->GetHeadPosition();
	while(pos)
	{
		tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

		//////////////////////////////
		// Calc min and max X:
		posSer=tmpSeries->GetHeadPosition ();
		while(posSer)
		{
			pDataSet=tmpSeries->GetDataValue (posSer);
			if(pDataSet->xPosition <dMinX)
			{
				dMinX=pDataSet->xPosition;
			}

			if(pDataSet->xPosition >dMaxX)
			{
				dMaxX=pDataSet->xPosition;
			}
		}

		//////////////////////////////
		// Calc min and max X:
		// Sum the series:
		if(m_iGraphType == STACKED_BAR_GRAPH_3D||m_iGraphType ==STACKED_BAR_GRAPH )
		{
			dSumY=0.0;
			dMinY=0.0;
			posSer=tmpSeries->GetHeadPosition ();
			while(posSer)
			{
				pDataSet=tmpSeries->GetDataValue (posSer);
				dSumY+=pDataSet->yValue;
			}

			if(dSumY >dMaxY)
			{
				dMaxY=dSumY;
			}
		}

		// NO Sum the series:
		else
		{
			posSer=tmpSeries->GetHeadPosition ();
			while(posSer)
			{
				pDataSet=tmpSeries->GetDataValue (posSer);
				if(pDataSet->yValue <dMinY)
				{
					dMinY=pDataSet->yValue;
				}

				if(pDataSet->yValue >dMaxY)
				{
					dMaxY=pDataSet->yValue;
				}
			}
		}
	}
	
	////////////////////////////
	//

	double dFrom,dTo,dStep;

	if(dMinX>dMaxX)
	{
		dMinX=0;
		dMaxX=1000;
	}
	if(dMinY>dMaxY)
	{
		dMinY=0;
		dMaxY=1000;
	}
    int iLimit=1000000;
    if(dMinX<(-iLimit))dMinX=(-iLimit);
    if(dMaxX>iLimit)dMaxX=iLimit;
    if(dMinY<-iLimit)dMinY=-iLimit;
    if(dMaxY>iLimit)dMaxY=iLimit;


	CFontGroup fg;
	double dMidX=(dMinX+dMaxX)/2;
	CString s=vtos(dMidX);
	CSize size=pDC->GetTextExtent (s);
	fg.Set(dMinX,dMaxX,m_xAxisWidth,size.cx );	
	fg.CalcFontGroup (dFrom,dTo,dStep);
	while(dMinX<dFrom)
	{
		dFrom-=dStep;
	}
	while(dMaxX>dTo)
	{
		dTo+=dStep;
	}


	SetXTickLimits(dFrom,dTo,dStep);

	double dMidY=(dMinY+dMaxY)/2;
	s=vtos(dMidY);
	size=pDC->GetTextExtent (s);

	fg.Set(dMinY,dMaxY,m_yAxisHeight,size.cy);	
	fg.CalcFontGroup (dFrom,dTo,dStep);
	while(dMinY<=dFrom)
	{
		dFrom-=dStep;
	}
	while(dMaxY>dTo)
	{
		dTo+=dStep;
	}

	if(m_iGraphType == STACKED_BAR_GRAPH_3D||m_iGraphType ==STACKED_BAR_GRAPH )
	{
		dFrom=0;
	}

    // Set the data limit:
	SetYTickLimits(dFrom,dTo,dStep);
}

void CGraphView::SetYTickLimits(int minTickValue, int maxTickValue, int tickStep)
{
	if(tickStep<1)tickStep=1;
    int iBigValue=99999999;
    if(minTickValue<-iBigValue)minTickValue=iBigValue;
    if(maxTickValue>iBigValue)maxTickValue=iBigValue;

	m_iYMaxTick = maxTickValue;
	m_iYMinTick = minTickValue;
	m_iYTickSpace = tickStep;
	m_iYNumTicks = (m_iYMaxTick - m_iYMinTick) / tickStep;
    if(m_iYNumTicks<1)m_iYNumTicks=1;
	if((m_iYNumTicks * tickStep) < (m_iYMaxTick - m_iYMinTick))
		m_iYNumTicks++;
}

void CGraphView::SetXTickLimits(int minTickValue, int maxTickValue, int tickStep)
{
	if(tickStep<1)tickStep=1;
    int iBigValue=99999999;
    if(minTickValue<-iBigValue)minTickValue=iBigValue;
    if(maxTickValue>iBigValue)maxTickValue=iBigValue;

	m_iXMaxTick = maxTickValue;
	m_iXMinTick = minTickValue;
	m_iXTickSpace = tickStep;
	m_iXNumTicks = (m_iXMaxTick - m_iXMinTick) / tickStep;
    if(m_iXNumTicks<1)m_iXNumTicks=1;
	if((m_iXNumTicks * tickStep) < (m_iXMaxTick - m_iXMinTick))
		m_iXNumTicks++;
}
void CGraphView::DrawBarSeries(CDC* pDC)
{
	int barWidth;
	int dataPlotSize;   //used to plot rects of data
	int barL, barT, barR, barB;
	int tickXLocation;
	int seriesSpace;
	int barHeight;
	POSITION pos;
	CGraphSeries* tmpSeries;
	int x, s;

	if(m_pGraphSeries->GetCount()<1)return;

	//determine width of barchart data blocks
	seriesSpace = m_xAxisWidth / m_pGraphSeries->GetCount();
	barWidth = (int)((seriesSpace * .6) / m_iSeriesSize);
	dataPlotSize = m_iSeriesSize * barWidth;

	pos = m_pGraphSeries->GetHeadPosition();

	switch(m_iGraphQuadType)
	{
		case 1 :
			for(x = 1; x <= m_pGraphSeries->GetCount(); x++)
			{
				tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

				tickXLocation = m_iXApexPoint + ((x * seriesSpace) - (seriesSpace / 2));

				for(s = 0; s < m_iSeriesSize; s++)
				{
					if(tmpSeries->GetData(s) > -1)
					{
						double dataScale = 0.00;
						dataScale = ((m_yAxisHeight - 10) * 1.00) / (m_iYMaxTick - m_iYMinTick);
						barHeight = (int)(((tmpSeries->GetData(s) - m_iYMinTick) * 1.00) * dataScale);
						if(((tmpSeries->GetData(s) - m_iYMinTick) > 0) && (barHeight < 1))
							barHeight = (int)dataScale;

						barL = tickXLocation - (dataPlotSize / 2) + (s * barWidth);
						if(barHeight > m_yAxisHeight)
							barT = m_iYApexPoint - m_yAxisHeight;
						else
							barT = m_iYApexPoint - barHeight;
						barR = barL + barWidth;
						barB = m_iYApexPoint;
						
						COLORREF barColor;
						barColor = GetColor(s);
						CBrush brush (barColor);
						CBrush* pOldBrush;
						pOldBrush = pDC->SelectObject(&brush);
						pDC->Rectangle(barL, barT, barR, barB);
						pDC->SelectObject(pOldBrush);
					}
				}
			}
			break;
		case 2 :
			for(x = 1; x <= m_pGraphSeries->GetCount() / 2; x++)
			{
				tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

				tickXLocation = m_iXApexPoint - (m_xAxisWidth / 2) + ((x * seriesSpace) - (seriesSpace / 2));

				for(s = 0; s < m_iSeriesSize; s++)
				{
					double dataScale = 0.00;
					dataScale = ((m_yAxisHeight - 10) * 1.00) / (m_iYMaxTick - m_iYMinTick);
					barHeight = (int)(((tmpSeries->GetData(s) - m_iYMinTick) * 1.00) * dataScale);
					if(barHeight < 1)
						barHeight = (int)dataScale;

					barL = tickXLocation - (dataPlotSize / 2) + (s * barWidth);
					if(barHeight > (m_yAxisHeight / 2))
						barT = m_iYApexPoint - (m_yAxisHeight / 2);
					else
						barT = m_iYApexPoint - barHeight;
					barR = barL + barWidth;
					barB = m_iYApexPoint;
					
					COLORREF barColor;
					barColor = GetColor(s);
					CBrush brush (barColor);
					CBrush* pOldBrush;
					pOldBrush = pDC->SelectObject(&brush);
					pDC->Rectangle(barL, barT, barR, barB);
					pDC->SelectObject(pOldBrush);
				}
			}
			//draw at the 0 location
			tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);
			tickXLocation = m_iXApexPoint;
			for(s = 0; s < m_iSeriesSize; s++)
			{
				double dataScale = 0.00;
				dataScale = ((m_yAxisHeight - 10) * 1.00) / (m_iYMaxTick - m_iYMinTick);
				barHeight = (int)(((tmpSeries->GetData(s) - m_iYMinTick) * 1.00) * dataScale);
				if(((tmpSeries->GetData(s) - m_iYMinTick) > 0) && (barHeight < 1))
					barHeight = (int)dataScale;

				barL = tickXLocation - (dataPlotSize / 2) + (s * barWidth);
				if(barHeight > m_yAxisHeight)
					barT = m_iYApexPoint - m_yAxisHeight;
				else
					barT = m_iYApexPoint - barHeight;
				barR = barL + barWidth;
				barB = m_iYApexPoint;
				
				COLORREF barColor;
				barColor = GetColor(s);
				CBrush brush (barColor);
				CBrush* pOldBrush;
				pOldBrush = pDC->SelectObject(&brush);
				pDC->Rectangle(barL, barT, barR, barB);
				pDC->SelectObject(pOldBrush);
			}
			x++;

			for(; x <= m_pGraphSeries->GetCount(); x++)
			{
				tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

				tickXLocation = m_iXApexPoint - (m_xAxisWidth / 2) + ((x * seriesSpace) - (seriesSpace / 2));

				for(s = 0; s < m_iSeriesSize; s++)
				{
					double dataScale = 0.00;
					dataScale = ((m_yAxisHeight - 10) * 1.00) / (m_iYMaxTick - m_iYMinTick);
					barHeight = (int)(((tmpSeries->GetData(s) - m_iYMinTick) * 1.00) * dataScale);
					if(((tmpSeries->GetData(s) - m_iYMinTick) > 0) && (barHeight < 1))
						barHeight = (int)dataScale;

					barL = tickXLocation - (dataPlotSize / 2) + (s * barWidth);
					if(barHeight > (m_yAxisHeight / 2))
						barT = m_iYApexPoint - (m_yAxisHeight / 2);
					else
						barT = m_iYApexPoint - barHeight;
					barR = barL + barWidth;
					barB = m_iYApexPoint;
					
					COLORREF barColor;
					barColor = GetColor(s);
					CBrush brush (barColor);
					CBrush* pOldBrush;
					pOldBrush = pDC->SelectObject(&brush);
					pDC->Rectangle(barL, barT, barR, barB);
					pDC->SelectObject(pOldBrush);
				}
			}
			break;
		case 3 :
			for(x = 1; x <= m_pGraphSeries->GetCount(); x++)
			{
				tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

				tickXLocation = m_iXApexPoint + ((x * seriesSpace) - (seriesSpace / 2));

				for(s = 0; s < m_iSeriesSize; s++)
				{
					double dataScale = 0.00;
					dataScale = ((m_yAxisHeight - 10) * 1.00) / (m_iYMaxTick - m_iYMinTick);
					barHeight = (int)(((tmpSeries->GetData(s) - m_iYMinTick) * 1.00) * dataScale);

					barL = tickXLocation - (dataPlotSize / 2) + (s * barWidth);
					if(barHeight < 0)
					{
						if((0 - barHeight) > (m_yAxisHeight / 2))
							barT = m_iYApexPoint - (m_yAxisHeight / 2);
						else
							barT = m_iYApexPoint - barHeight;
					}
					else
					{
						if(barHeight > (m_yAxisHeight / 2))
							barT = m_iYApexPoint - (m_yAxisHeight / 2);
						else
							barT = m_iYApexPoint - barHeight;
					}
					barR = barL + barWidth;
					barB = m_iYApexPoint;
					
					COLORREF barColor;
					barColor = GetColor(s);
					CBrush brush (barColor);
					CBrush* pOldBrush;
					pOldBrush = pDC->SelectObject(&brush);
					pDC->Rectangle(barL, barT, barR, barB);
					pDC->SelectObject(pOldBrush);
				}
			}
			break;
		case 4 :
			for(x = 1; x <= m_pGraphSeries->GetCount() / 2; x++)
			{
				tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

				tickXLocation = m_iXApexPoint - (m_xAxisWidth / 2) + ((x * seriesSpace) - (seriesSpace / 2));

				for(s = 0; s < m_iSeriesSize; s++)
				{
					double dataScale = 0.00;
					dataScale = ((m_yAxisHeight - 10) * 1.00) / (m_iYMaxTick - m_iYMinTick);
					barHeight = (int)(((tmpSeries->GetData(s) - m_iYMinTick) * 1.00) * dataScale);

					barL = tickXLocation - (dataPlotSize / 2) + (s * barWidth);
					if(barHeight < 0)
					{
						if((0 - barHeight) > (m_yAxisHeight / 2))
							barT = m_iYApexPoint - (m_yAxisHeight / 2);
						else
							barT = m_iYApexPoint - barHeight;
					}
					else
					{
						if(barHeight > (m_yAxisHeight / 2))
							barT = m_iYApexPoint - (m_yAxisHeight / 2);
						else
							barT = m_iYApexPoint - barHeight;
					}
					barR = barL + barWidth;
					barB = m_iYApexPoint;
					
					COLORREF barColor;
					barColor = GetColor(s);
					CBrush brush (barColor);
					CBrush* pOldBrush;
					pOldBrush = pDC->SelectObject(&brush);
					pDC->Rectangle(barL, barT, barR, barB);
					pDC->SelectObject(pOldBrush);
				}
			}
			//draw at the 0 location
			tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);
			tickXLocation = m_iXApexPoint;
			for(s = 0; s < m_iSeriesSize; s++)
			{
				double dataScale = 0.00;
				dataScale = ((m_yAxisHeight - 10) * 1.00) / (m_iYMaxTick - m_iYMinTick);
				barHeight = (int)(((tmpSeries->GetData(s) - m_iYMinTick) * 1.00) * dataScale);
				if(((tmpSeries->GetData(s) - m_iYMinTick) > 0) && (barHeight < 1))
					barHeight = (int)dataScale;

				barL = tickXLocation - (dataPlotSize / 2) + (s * barWidth);
				if(barHeight < 0)
				{
					if((0 - barHeight) > (m_yAxisHeight / 2))
						barT = m_iYApexPoint - (m_yAxisHeight / 2);
					else
						barT = m_iYApexPoint - barHeight;
				}
				else
				{
					if(barHeight > (m_yAxisHeight / 2))
						barT = m_iYApexPoint - (m_yAxisHeight / 2);
					else
						barT = m_iYApexPoint - barHeight;
				}
				barR = barL + barWidth;
				barB = m_iYApexPoint;
				
				COLORREF barColor;
				barColor = GetColor(s);
				CBrush brush (barColor);
				CBrush* pOldBrush;
				pOldBrush = pDC->SelectObject(&brush);
				pDC->Rectangle(barL, barT, barR, barB);
				pDC->SelectObject(pOldBrush);
			}
			x++;

			for(; x <= m_pGraphSeries->GetCount(); x++)
			{
				tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

				tickXLocation = m_iXApexPoint - (m_xAxisWidth / 2) + ((x * seriesSpace) - (seriesSpace / 2));

				for(s = 0; s < m_iSeriesSize; s++)
				{
					double dataScale = 0.00;
					dataScale = ((m_yAxisHeight - 10) * 1.00) / (m_iYMaxTick - m_iYMinTick);
					barHeight = (int)(((tmpSeries->GetData(s) - m_iYMinTick) * 1.00) * dataScale);
					if(((tmpSeries->GetData(s) - m_iYMinTick) > 0) && (barHeight < 1))
						barHeight = (int)dataScale;

					barL = tickXLocation - (dataPlotSize / 2) + (s * barWidth);
					if(barHeight < 0)
					{
						if((0 - barHeight) > (m_yAxisHeight / 2))
							barT = m_iYApexPoint - (m_yAxisHeight / 2);
						else
							barT = m_iYApexPoint - barHeight;
					}
					else
					{
						if(barHeight > (m_yAxisHeight / 2))
							barT = m_iYApexPoint - (m_yAxisHeight / 2);
						else
							barT = m_iYApexPoint - barHeight;
					}
					barR = barL + barWidth;
					barB = m_iYApexPoint;
					
					COLORREF barColor;
					barColor = GetColor(s);
					CBrush brush (barColor);
					CBrush* pOldBrush;
					pOldBrush = pDC->SelectObject(&brush);
					pDC->Rectangle(barL, barT, barR, barB);
					pDC->SelectObject(pOldBrush);
				}
			}
			break;
	}
}

void CGraphView::DrawLineSeries(CDC* pDC)
{
	int barWidth;
	int dataPlotSize;   //used to plot rects of data
	int tickXLocation;
	int seriesSpace;
	int barHeight;
	int s=0,x=0;
	double dataScale = 0.00;
	int iMarkerSize=0;
	int iLineWidth=0;
	enumMarkerType eMarkerType;


	POSITION pos;
	CGraphSeries* tmpSeries;
	COLORREF barColor;
	CBrush* pOldBrush=NULL;

	CPen* pOldPen=NULL;

	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;



	int lastXLoc, lastYLoc;
	for(s = 0; s < m_iSeriesSize; s++)
	{
		//determine width of barchart data blocks
		seriesSpace = m_xAxisWidth / m_pGraphSeries->GetCount();
		barWidth = (int)((seriesSpace * .6) / m_iSeriesSize);
		dataPlotSize = m_iSeriesSize * barWidth;


		barColor	= GetColor(s);
		iLineWidth	= GetLineWidth(s);
		iMarkerSize	= GetMarkerSize(s);
		eMarkerType	= GetMarkerType(s);

		CBrush brush (barColor);
		pOldBrush = pDC->SelectObject(&brush);

		CPen linePen (PS_SOLID, iLineWidth, barColor);
		pOldPen = pDC->SelectObject(&linePen);

		pos = m_pGraphSeries->GetHeadPosition();

		for(x = 1; x <= m_pGraphSeries->GetCount(); x++)
		{
			tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

			if(tmpSeries->GetData(s) > -1)
			{
				tickXLocation = m_iXApexPoint + ((x * seriesSpace) - (seriesSpace / 2));
				
				barHeight = 0;
				dataScale = ((m_yAxisHeight - 10) * 1.00) / (m_iYMaxTick - m_iYMinTick);
				barHeight = (int)(((tmpSeries->GetData(s) - m_iYMinTick) * 1.00) * dataScale);
				if(((tmpSeries->GetData(s) - m_iYMinTick) > 0) && (barHeight < 1))
					barHeight = (int)dataScale;

				if(barHeight > m_iYApexPoint)
					barHeight = (int)((m_iYMaxTick - m_iYMinTick) * dataScale) + 5;

				int yDataLocation = m_iYApexPoint - barHeight;
				//now have x and y location of center of ellipse

				//draw line back to last data member
				if(x > 1)
				{
					//pDC->MoveTo(lastXLoc + 2, lastYLoc - 1);
					//pDC->LineTo(tickXLocation - 3, yDataLocation - 1);
					pDC->MoveTo(lastXLoc , lastYLoc );
					pDC->LineTo(tickXLocation , yDataLocation );
				}

				DrawMarker(	pDC,
							eMarkerType,
							tickXLocation,yDataLocation,iMarkerSize);

				lastXLoc = tickXLocation;
				lastYLoc = yDataLocation;
			}
		}

		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);

	}
}

void CGraphView::DrawPieSeries(CDC* pDC)
{
	double dataSum = 0.00;  //for storing cumulative sum
	double labelData = 0.00;
	int lastXLocation, lastYLocation;
	int newXLocation, newYLocation;
	int labelXLocation, labelYLocation;
	double percent = 0.00;
	double labelPercent = 0.00;
	int degrees;
	int labelDegrees;
	double totalSum = 0.00;
	int deltaXY;
	int labelDeltaXY;
	int radius;
	POSITION pos;
	CGraphSeries* tmpSeries;
	int seriesSpace;
	int labelLineXStart, labelLineYStart;
	int labelLineXEnd, labelLineYEnd;
	int maxLabelWidth;
	int maxLabelHeight;
	TEXTMETRIC tm;
		
	lastXLocation = 0;
	lastYLocation = 0;

	pDC->GetTextMetrics(&tm);
	maxLabelWidth = tm.tmMaxCharWidth + 10;
	maxLabelHeight = tm.tmHeight + 6;
	
	//pie labels will be stored in a list and drawn after entire pie
	//is completed.
	CObList *pieLabels;
	CGraphPieLabel *pieLabel;

	/////////////////////////////////
	// Mended By FanHua:
	/////////////////////////////////
	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;


	int iClientArea=m_yAxisHeight*m_xAxisWidth;
	int iUnitArea=iClientArea/iSerQty;
	seriesSpace=sqrt((double)iUnitArea);

	int iHorQty=m_xAxisWidth/seriesSpace;
	int iVerQty=m_yAxisHeight/seriesSpace;

	while(iHorQty*iVerQty<iSerQty)
	{
		seriesSpace--;
		iHorQty=m_xAxisWidth/seriesSpace;
		iVerQty=m_yAxisHeight/seriesSpace;
	}

	radius = seriesSpace / 2 *0.7; 

	CFont labelFont;
	labelFont.CreateFont(m_iPieLabelFontSize , 0, 0, 0, 0, FALSE, FALSE, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
	CFont* pOldFont = (CFont*) pDC->SelectObject(&labelFont);
	/////////////////////////////////
	// Mended by fanhua over
	/////////////////////////////////


	int pieLeft		= 0;
	int pieRight	= 0;
	int centerYPie	= 0; 
	int iHorOrder	= 0;
	int iVerOrder	= 0;
	CSize sizeLabel;
	CString sLabel;

	pDC->SetBkMode (TRANSPARENT);

	pos = m_pGraphSeries->GetHeadPosition();
	for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
	{
		if(iHorOrder>=iHorQty)
		{
			iHorOrder=0;
			iVerOrder++;
		}


		centerYPie	= m_iYApexPoint-iVerOrder*seriesSpace-seriesSpace/2;
		pieLeft		= m_iXApexPoint+iHorOrder*seriesSpace+radius;
		pieRight	= pieLeft + (2 * radius);

		pieLabels = new CObList();

		tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);
		totalSum = 0;
		for(int s = 0; s < m_iSeriesSize; s++)
		{
			totalSum += tmpSeries->GetData(s);
		}

		CRect pieRect (pieLeft, 
				centerYPie - radius,
				pieRight, 
				centerYPie + radius);
		int centerXPie = pieLeft + radius;

		//plot series label
		lastXLocation = pieLeft;
		lastYLocation = centerYPie;

		dataSum = 0;
		for(s = 0; s < m_iSeriesSize; s++)
		{
			if(tmpSeries->GetData(s) > 0)
			{
				int seriesDataValue;
				seriesDataValue = tmpSeries->GetData(s);
				labelData = seriesDataValue / 2;
				dataSum += seriesDataValue;
				percent = (dataSum / totalSum) * 100;
				labelPercent = ((dataSum - labelData) / totalSum) * 100;
				degrees = (int)((360 * percent) / 100);
				labelDegrees = (int)((360 * labelPercent) / 100);

				deltaXY = (degrees * radius) / 90;
				labelDeltaXY = (labelDegrees * radius) / 90;
					//deltaXY is change from start point of pie 0
					//this value is total change.  so if radius is 300
					//and degrees is 270, delta is 300.  The change 
					//would move both x and y 300 pixels.  For x, 100
					//to right is center, another 100 to right edge,
					//100 back to center.  For y, 100 to bottom, 100
					//back to center, 100 to top. thus gives 270 degree
					//rotation.

				//determine destination quadrant...
					//and set newXLocation and newYLocation values...
					//degress / 90 will never exceed 4.
					//this can tell us the quadrant of destination
				int quadrant = degrees / 90;  //truncates decimal
				int labelQuadrant = labelDegrees / 90;

				switch(quadrant)
				{
					//in the computations below, the remarked line is
					//the original computation.  The line above it, for
					//actual use, is the simplified line, and gives the
					//exact same result
					case 0 : newXLocation = pieLeft + deltaXY;
							 newYLocation = centerYPie + deltaXY;
							 break;
					case 1 : newXLocation = pieLeft + deltaXY;
							 newYLocation = centerYPie + (2 * radius) - deltaXY;
							 break;
					case 2 : newXLocation = pieLeft + (4 * radius) - deltaXY;
							 newYLocation = centerYPie + (2 * radius) - deltaXY;
							 break;
					case 3 : newXLocation = pieLeft + (4 * radius) - deltaXY;
							 newYLocation = centerYPie - (4 * radius) + deltaXY;
							 break;
					case 4 : newXLocation = pieLeft;
							 newYLocation = centerYPie - 1;
							 break;
				}
				
				switch(labelQuadrant)
				{
					//after getting X & Y location for label, we take
					//1/2 the delta between x y locations and center pie
					case 0 : labelXLocation = pieLeft + labelDeltaXY;
							 labelYLocation = centerYPie + labelDeltaXY;
							 labelLineXStart = labelXLocation + ((centerXPie - labelXLocation) / 2);
							 labelLineYStart = labelYLocation - ((labelYLocation - centerYPie) / 2);
							 labelLineXEnd = labelXLocation - (radius / 2);
							 labelLineYEnd = labelYLocation + (radius / 2);
							 break;
					case 1 : labelXLocation = pieLeft + labelDeltaXY;
							 labelYLocation = centerYPie + (2 * radius) - labelDeltaXY;
							 labelLineXStart = labelXLocation - ((labelXLocation - centerXPie) / 2);
							 labelLineYStart = labelYLocation - ((labelYLocation - centerYPie) / 2);
							 labelLineXEnd = labelXLocation + (radius / 2);
							 labelLineYEnd = labelYLocation + (radius / 2);
							 break;
					case 2 : labelXLocation = pieLeft + (4 * radius) - labelDeltaXY;
							 labelYLocation = centerYPie + (2 * radius) - labelDeltaXY;
							 labelLineXStart = labelXLocation - ((labelXLocation - centerXPie) / 2);
							 labelLineYStart = labelYLocation + ((centerYPie - labelYLocation) / 2);
							 labelLineXEnd = labelXLocation + (radius / 2);
							 labelLineYEnd = labelYLocation - (radius / 2);
							 break;
					case 3 : labelXLocation = pieLeft + (4 * radius) - labelDeltaXY;
							 labelYLocation = centerYPie - (4 * radius) + labelDeltaXY;
							 labelLineXStart = labelXLocation + ((centerXPie - labelXLocation) / 2);
							 labelLineYStart = labelYLocation + ((centerYPie - labelYLocation) / 2);
							 labelLineXEnd = labelXLocation - (radius / 2);
							 labelLineYEnd = labelYLocation - (radius / 2);
							 break;
//there should never be a half point ending on 4, so leave it out
				}

				pieLabel = new CGraphPieLabel();

				pieLabel->lineXStart = labelLineXStart;
				pieLabel->lineYStart = labelLineYStart;
				pieLabel->lineXEnd = labelLineXEnd;
				pieLabel->lineYEnd = labelLineYEnd;
				switch(labelQuadrant)
				{
					case 0 : //label to left of line
							 pieLabel->topLeftX = labelLineXEnd - maxLabelWidth;
							 pieLabel->topLeftY = labelLineYEnd;
							 break;
					case 1 : //label to right of line
							 pieLabel->topLeftX = labelLineXEnd + 5;
							 pieLabel->topLeftY = labelLineYEnd;
							 break;
					case 2 : //label to right of line
							 pieLabel->topLeftX = labelLineXEnd + 5;
							 pieLabel->topLeftY = labelLineYEnd - maxLabelHeight;
							 break;
					case 3 : //label to left of line
							 pieLabel->topLeftX = labelLineXEnd - maxLabelWidth;
							 pieLabel->topLeftY = labelLineYEnd - maxLabelHeight;
							 break;
				}
				pieLabel->labelQuadrant = labelQuadrant;
				int roundPercent;
				roundPercent = (int)((seriesDataValue * 100) / totalSum);
				pieLabel->pieLabel.Format("%d%%", roundPercent);
				pieLabels->AddTail(pieLabel);

				if(s == 0)
					lastYLocation -= 1;

				CPoint p1 (lastXLocation, lastYLocation);
				CPoint p2 (newXLocation, newYLocation);
				COLORREF barColor;
				barColor = GetColor(s);
				CBrush brush (barColor);
				CBrush* pOldBrush;
				CPen piePen(PS_SOLID, 1, barColor);
				CPen* pOldPen;
				pOldBrush = pDC->SelectObject(&brush);
				pOldPen = pDC->SelectObject(&piePen);
				pDC->Pie(pieRect, p1, p2); 
				pDC->SelectObject(pOldBrush);
				pDC->SelectObject(pOldPen);

				lastXLocation = newXLocation;
				lastYLocation = newYLocation;
			}
		}
		
		//draw lines and labels for pies slices
		if(m_bPieDrawLabels)
		{
			CBrush lineBrush (BLACK);
			CBrush* pOldBrush;
			pOldBrush = pDC->SelectObject(&lineBrush);
			POSITION mainLinePos, checkLinePos;
			mainLinePos = pieLabels->GetHeadPosition();
			int numLinesDrawn = 0;
			CGraphPieLabel* currentLabel;
			CGraphPieLabel* tmpLabel;
			while(mainLinePos != NULL)
			{
				currentLabel = (CGraphPieLabel*)pieLabels->GetNext(mainLinePos);
				int r = 0;
				checkLinePos = pieLabels->GetHeadPosition();
				while(r < numLinesDrawn)
				{
					//check if any overlap in label areas
					tmpLabel = (CGraphPieLabel*)pieLabels->GetAt(checkLinePos);
					if((currentLabel->topLeftX > tmpLabel->topLeftX) &&
						(currentLabel->topLeftX < (tmpLabel->topLeftX + maxLabelWidth)) &&
						(currentLabel->topLeftY > tmpLabel->topLeftY) &&
						(currentLabel->topLeftY < (tmpLabel->topLeftY + maxLabelHeight)))
					{
						//OVERLAP !!!
						//move current label top left position up or down
						//depending on its quadrant
						if(currentLabel->labelQuadrant < 2)
						{
							//move label down to tmplabel topleft + height
							currentLabel->topLeftY = tmpLabel->topLeftY + maxLabelHeight;
							currentLabel->lineYEnd = tmpLabel->lineYEnd + maxLabelHeight;
						}
						else
						{
							//move label up to tmpLabel topleft - height
							currentLabel->topLeftY = tmpLabel->topLeftY - maxLabelHeight;
							currentLabel->lineYEnd = tmpLabel->lineYEnd - maxLabelHeight;
						}
						//reset r value to 0 so it starts over, just in
						//case we moved the label and it overlaps another
						r = 0;
						checkLinePos = pieLabels->GetHeadPosition();
					}
					else
					{
						r++;
						pieLabels->GetNext(checkLinePos);
					}

				}
				//draw the line and label
				pDC->MoveTo(currentLabel->lineXStart, currentLabel->lineYStart);
				pDC->LineTo(currentLabel->lineXEnd, currentLabel->lineYEnd);

				//write the label
				pDC->TextOut(currentLabel->topLeftX, currentLabel->topLeftY,
						currentLabel->pieLabel);

				numLinesDrawn++;
			}

			pDC->SelectObject(pOldBrush);
		}

		// Draw the pie label :
		sLabel=tmpSeries->GetLabel();
		sizeLabel=pDC->GetTextExtent (sLabel);

		pDC->TextOut(centerXPie - (sizeLabel.cx / 2),
			centerYPie + radius + 5, sLabel);
		
		// Below line will write the label in the center of the pie:
		//pDC->TextOut(centerXPie-sizeLabel.cx/2,centerYPie -sizeLabel.cy/2, sLabel);

		//now done, remove everything inside the label list
		POSITION labelPos = pieLabels->GetHeadPosition();
		while(labelPos != NULL)
		{
			pieLabel = (CGraphPieLabel*)pieLabels->GetNext(labelPos);
			delete pieLabel;
		}
		delete pieLabels;
	

		//
		iHorOrder++;
	}

	pDC->SelectObject(pOldFont );

}

void CGraphView::DrawScatterSeries(CDC* pDC)
{
	//m_iRightXTick and m_iTopYTick contain the outer bounds of the axis ticks.
	//So, if m_iYMaxTick is 100 on both axis lines, then 100, 100 would be top
	//right.  We will use the bounds to see spacing from apex points and then
	//scale so any point can be plotted inside

	double yAxisScale, xAxisScale;
	int tickXLocation, tickYLocation;

	//multiply each value by 1.00 to force result into a double value, and therefore
	//make it more accurate in it's plot location.
	yAxisScale = (float) (m_iYApexPoint - m_iTopYTick)   / (m_iYMaxTick-m_iYMinTick);
	xAxisScale = (float)(m_iRightXTick - m_iXApexPoint) / (m_iXMaxTick-m_iXMinTick);

	//points will now plot as ((value * scale) + apex point)
	COLORREF barColor;
	barColor = BLACK;
	CBrush brush (barColor);
	CBrush* pOldBrush;
	pOldBrush = pDC->SelectObject(&brush);

	POSITION pos,posSer;
	CGraphSeries* tmpSeries;
	CGraphDataSet* pDataSet=NULL;
	enumMarkerType markSer;
	COLORREF colorSer=0;
	int iMarkerSize=0;

	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;


	int iOrder=0;
	for(pos = m_pGraphSeries->GetHeadPosition(); pos != NULL; m_pGraphSeries->GetNext(pos))
	{
		tmpSeries = (CGraphSeries*)m_pGraphSeries->GetAt(pos);
		posSer=tmpSeries->GetHeadPosition ();
		iOrder=0;
		while(posSer)
		{
			markSer=GetMarkerType(iOrder);
			colorSer=GetColor(iOrder);
			iMarkerSize=GetMarkerSize(iOrder);
			CBrush brush(colorSer);
			CBrush *pOldBrush=pDC->SelectObject (&brush);

			pDataSet=tmpSeries->GetDataValue (posSer);
			tickXLocation = (pDataSet->xPosition-m_iXMinTick)  * xAxisScale + m_iXApexPoint;
			tickYLocation = m_iYApexPoint - (pDataSet->yValue - m_iYMinTick)* yAxisScale;

			DrawMarker(pDC,markSer,tickXLocation,tickYLocation,iMarkerSize);
			pDC->SelectObject (pOldBrush);

			iOrder++;
		}
	}


	pDC->SelectObject(pOldBrush);


}

void CGraphView::DrawBoxWhiskerSeries(CDC* pDC)
{
	int upperQuartile;
	int lowerQuartile;
	int median;
	int highValue;
	int lowValue;
	
	COLORREF barColor;
	barColor = BLACK;
	CBrush brush (barColor);
	CBrush* pOldBrush;
	pOldBrush = pDC->SelectObject(&brush);

	int barWidth;
	int barL, barT, barR, barB;
	int tickXLocation;
	int seriesSpace;
	int barHeight;
	POSITION pos;
	CGraphSeries* tmpSeries;

	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;


	pos = m_pGraphSeries->GetHeadPosition();
	CUIntArray dataArray;
	CUIntArray sortedArray;

	for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
	{
		dataArray.RemoveAll();
		sortedArray.RemoveAll();

		CObList *sortedData;
		sortedData = new CObList();
		tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);
		m_iSeriesSize = tmpSeries->GetDataCount();

		int dataValue;
		for(int s = 0; s < m_iSeriesSize; s++)
		{
			dataValue = 0;
			if(tmpSeries->GetData(s) > -1)
				dataValue = tmpSeries->GetData(s);
			dataArray.Add(dataValue);
		}

		//sort the array
		dataValue = dataArray.GetAt(0);
		sortedArray.Add(dataValue);
		for(int d = 1; d < dataArray.GetSize(); d++)
		{
			dataValue = dataArray.GetAt(d);
			BOOL placed = FALSE;
			for(int s = 0; s < sortedArray.GetSize(); s++)
			{
				int tmpI = sortedArray.GetAt(s);
				if(dataValue <= tmpI)
				{
					sortedArray.InsertAt(s, dataValue);
					placed = TRUE;
					break;
				}
			}
			if(!placed)	//add at end
				sortedArray.Add(dataValue);
		}
		
		//sortedArray now contains the sorted list of all data in this
		//series.  From here, we derive the other box-whisker data
		
		int medialElement;
		div_t div_result;
		div_result = div(sortedArray.GetSize(), 2);

		if(div_result.rem == 0)	//even number of elements
		{
			//size is not 0 base, so below, I subtract 1 to 0 base it.
			medialElement = (sortedArray.GetSize() / 2) - 1;
			median = sortedArray.GetAt(medialElement) + 
						((sortedArray.GetAt(medialElement + 1) - 
						sortedArray.GetAt(medialElement)) / 2);
			highValue = sortedArray.GetAt(sortedArray.GetSize() - 1);
			lowValue = sortedArray.GetAt(0);
			div_t div2Result;
			div2Result = div(medialElement + 1, 2);
			if(div2Result.rem == 0)	//even again
			{
				upperQuartile = sortedArray.GetAt(medialElement + 1 + (medialElement / 2)) +
									(sortedArray.GetAt(medialElement + (medialElement / 2) + 2) -
									sortedArray.GetAt(medialElement + (medialElement / 2))) / 2;
				lowerQuartile = sortedArray.GetAt(medialElement / 2) +
									((sortedArray.GetAt((medialElement / 2) + 1) -
									sortedArray.GetAt(medialElement / 2)) / 2);
			}
			else	//odd
			{
				upperQuartile = sortedArray.GetAt(medialElement + 1 + (medialElement / 2));
				lowerQuartile = sortedArray.GetAt(medialElement / 2);
			}
		}
		else	//odd number of elements
		{
			//size is not 0 base, so below, I subtract 1 to 0 base it.
			medialElement = sortedArray.GetSize() / 2;
			median = sortedArray.GetAt(medialElement);
			highValue = sortedArray.GetAt(sortedArray.GetSize() - 1);
			lowValue = sortedArray.GetAt(0);
			div_t div2Result;
			div2Result = div(medialElement, 2);
			if(div2Result.rem == 0)	//even 
			{
				upperQuartile = sortedArray.GetAt(medialElement + (medialElement / 2)) +
									(sortedArray.GetAt(medialElement + (medialElement / 2) + 1) -
									sortedArray.GetAt(medialElement + (medialElement / 2))) / 2;
				lowerQuartile = sortedArray.GetAt((medialElement - 1) / 2) +
									((sortedArray.GetAt((medialElement + 1) / 2) -
									sortedArray.GetAt((medialElement - 1) / 2)) / 2);
			}
			else	//odd
			{
				upperQuartile = sortedArray.GetAt(medialElement + 1 + (medialElement / 2));
				lowerQuartile = sortedArray.GetAt(medialElement / 2);
			}
		}

		//data has been computed for median, high, low, and interquartile range
		//now we can draw the series

		seriesSpace = m_xAxisWidth / m_pGraphSeries->GetCount();

		barWidth = (int)(seriesSpace * .8);

		double tickScale = 0.00;
		tickScale = (m_yAxisHeight - 10) / m_iYNumTicks;

		tickXLocation = m_iXApexPoint + ((x * seriesSpace) - (seriesSpace / 2));

		barL = tickXLocation - (barWidth / 2);
		barR = barL + barWidth;
		double dataScale = 0.00;
		dataScale = ((m_yAxisHeight - 10) * 1.00) / (m_iYMaxTick - m_iYMinTick);

		//top cross bar (max value)
		barHeight = (int)((highValue * 1.00) * tickScale);
		barT = m_iYApexPoint - barHeight;
		barB = barT + 3;
		pDC->Rectangle(barL, barT, barR, barB);

		//bottom cross bar (min value)
		barHeight = (int)((lowValue * 1.00) * tickScale);
		barT = m_iYApexPoint - barHeight;
		barB = barT - 3;
		pDC->Rectangle(barL, barT, barR, barB);

		//vertical line (whisker)
		barHeight = (int)((highValue * 1.00) * tickScale);
		barT = m_iYApexPoint - barHeight;
		//barB = ?;	//this will be left over from bottom cross bar
		pDC->Rectangle(tickXLocation - 2, barT, tickXLocation + 2, barB);

		//box (interquartile range, from upper quartile to lower quartile)
		barHeight = (int)(upperQuartile * tickScale);
		barT = m_iYApexPoint - barHeight;
		barHeight = (int)(lowerQuartile * tickScale);
		barB = m_iYApexPoint - barHeight;
		pDC->Rectangle(barL, barT, barR, barB);

		//draw median line (in RED)
		CPen* pOldPen;
		CPen linePen (PS_SOLID, 1, RED);
		pOldPen = pDC->SelectObject(&linePen);
		barHeight = (int)((median * 1.00) * tickScale);
		pDC->MoveTo(barL, m_iYApexPoint - barHeight);
		pDC->LineTo(barR, m_iYApexPoint - barHeight);
		pDC->SelectObject(pOldPen);
	}

	pDC->SelectObject(pOldBrush);
}

void CGraphView::DrawStackedBarSeries(CDC* pDC)
{
	int barWidth;
	int barL, barT, barR, barB;
	int tickXLocation;
	int seriesSpace;
	int barHeight;
	POSITION pos;
	CGraphSeries* tmpSeries;

	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;


	//determine width of barchart data blocks
	seriesSpace = m_xAxisWidth / m_pGraphSeries->GetCount();
	barWidth = (int)(seriesSpace * .6);

	pos = m_pGraphSeries->GetHeadPosition();

	double dataScale = 0.00;
	dataScale = ((m_yAxisHeight - 10) * 1.00) / (m_iYMaxTick - m_iYMinTick);
	for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
	{
		tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

		tickXLocation = m_iXApexPoint + ((x * seriesSpace) - (seriesSpace / 2));
		
		barT = m_iYApexPoint;	//this is a running total;
							//it starts at m_iYApexPoint so barB can
							//start there, then moves up by barHeight
		for(int s = 0; s < m_iSeriesSize; s++)
		{
			if(tmpSeries->GetData(s) > -1)
			{
				barHeight = (int)(((tmpSeries->GetData(s) - m_iYMinTick) * 1.00) * dataScale);
				if(((tmpSeries->GetData(s) - m_iYMinTick) > 0) && (barHeight < 1))
					barHeight = (int)dataScale;

				barB = barT;
				barL = tickXLocation - (barWidth / 2);
				if(barHeight > m_yAxisHeight)
					barT = barB - m_yAxisHeight;
				else
					barT = barB - barHeight;
				barR = barL + barWidth;
				
				COLORREF barColor;
				barColor = GetColor(s);
				CBrush brush (barColor);
				CBrush* pOldBrush;
				pOldBrush = pDC->SelectObject(&brush);
				pDC->Rectangle(barL, barT, barR, barB);
				pDC->SelectObject(pOldBrush);
			}
		}
	}
}

void CGraphView::DrawXYLineSeries(CDC* pDC)
{
	//XY Line graph is same as Line graph, but has no circles at endpoints
	int barWidth;
	int dataPlotSize;   //used to plot rects of data
	int tickXLocation;
	int seriesSpace;
	int barHeight;
	POSITION pos;
	CGraphSeries* tmpSeries;

	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;


	int lastXLoc, lastYLoc;
	for(int s = 0; s < m_iSeriesSize; s++)
	{
		//determine width of barchart data blocks
		seriesSpace = m_xAxisWidth / m_pGraphSeries->GetCount();
		barWidth = (int)((seriesSpace * .6) / m_iSeriesSize);
		dataPlotSize = m_iSeriesSize * barWidth;

		pos = m_pGraphSeries->GetHeadPosition();

		for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
		{
			tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

			if(tmpSeries->GetData(s) > -1)
			{
				tickXLocation = m_iXApexPoint + ((x * seriesSpace) - (seriesSpace / 2));
				
				barHeight = 0;
				double dataScale = 0.00;
				
				if((m_iYMaxTick - m_iYMinTick) != m_yAxisHeight)
					dataScale = (m_yAxisHeight * 1.00) / ((m_iYMaxTick - m_iYMinTick) * 1.00);
				else dataScale = 1;
				barHeight = (int)(((tmpSeries->GetData(s) - m_iYMinTick) * 1.00) * dataScale);
				if(((tmpSeries->GetData(s) - m_iYMinTick) > 0) && (barHeight < 1))
					barHeight = (int)dataScale;

				if(barHeight > m_iYApexPoint)
					barHeight = (int)((m_iYMaxTick - m_iYMinTick) * dataScale) + 5;

				int yDataLocation = m_iYApexPoint - barHeight;
				//now have x and y location of center of ellipse
				COLORREF barColor;
				barColor = GetColor(s);
				//draw line back to last data member
				if(x > 1)
				{
					CPen* pOldPen;
					CPen linePen (PS_SOLID, GetLineWidth(s), barColor);
					pOldPen = pDC->SelectObject(&linePen);
					pDC->MoveTo(lastXLoc, lastYLoc);
					pDC->LineTo(tickXLocation, yDataLocation);
					pDC->SelectObject(pOldPen);
				}
				lastXLoc = tickXLocation;
				lastYLoc = yDataLocation;
			}
		}
	}
}

//I may implement radar graphs in the future, after I really determine
//what the purpose is and what the dynamics of it involves

//void CGraphView::DrawRadarSeries(CDC* pDC)
//{
//}

void CGraphView::Draw3DBarSeries(CDC* pDC)
{
	int barWidth;
	int dataPlotSize;   //used to plot rects of data
	int barL, barT, barR, barB;
	int tickXLocation;
	int seriesSpace;
	int barHeight;
	POSITION pos;
	CGraphSeries* tmpSeries;
	int blue;
	int red;
	int green;
	int x,s;
	int sideRed ;
	int sideGreen;
	int sideBlue ;
	int topRed ;
	int topGreen;
	int topBlue ;
	double dataScale;

	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;

	//determine width of barchart data blocks
	seriesSpace = m_xAxisWidth  / m_pGraphSeries->GetCount();
	barWidth = (int)((seriesSpace * .8) / m_iSeriesSize);
	dataPlotSize = m_iSeriesSize * barWidth;

	pos = m_pGraphSeries->GetHeadPosition();

	for(x = 1; x <= m_pGraphSeries->GetCount(); x++)
	{
		tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

		tickXLocation = m_iXApexPoint + ((x * seriesSpace) - (seriesSpace / 2));

		for(s = 0; s < m_iSeriesSize; s++)
		{
			if(tmpSeries->GetData(s) > -1)
			{
				dataScale = (m_yAxisHeight * 1.00) / (m_iYMaxTick - m_iYMinTick);
				barHeight = (int)(((tmpSeries->GetData(s) - m_iYMinTick) * 1.00) * dataScale);
				if(((tmpSeries->GetData(s) - m_iYMinTick) > 0) && (barHeight < 1))
					barHeight = (int)dataScale;

				barL = tickXLocation - (dataPlotSize / 2) + (s * barWidth);
				if(barHeight > m_yAxisHeight)
					barT = m_iYApexPoint - m_yAxisHeight;
				else
					barT = m_iYApexPoint - barHeight;
				barR = barL + barWidth;
				barB = m_iYApexPoint;
				
				COLORREF barColor;
				barColor = GetColor(s);
				CBrush brush (barColor);
				CPen rectPen (PS_SOLID, 1, barColor);
				CPen* pOldPen;
				pOldPen = pDC->SelectObject(&rectPen);
				CBrush* pOldBrush;
				pOldBrush = pDC->SelectObject(&brush);
				pDC->Rectangle(barL, barT, barR, barB);

				//now, we do the side
				//side is darker than front, so subtract
				//from color to make closer to black
				red = GetRValue(barColor);
				green = GetGValue(barColor);
				blue = GetBValue(barColor);
				sideRed = red - 35;
				sideGreen = green - 35;
				sideBlue = blue - 35;
				if(sideRed < 0) sideRed = 0;
				if(sideGreen < 0) sideGreen = 0;
				if(sideBlue < 0) sideBlue = 0;
				COLORREF sideColor;
				sideColor = RGB(sideRed, sideGreen, sideBlue);
				CBrush sideBrush (sideColor);
				CPen sidePen (PS_SOLID, 1, sideColor);
				pDC->SelectObject(&sideBrush);
				pDC->SelectObject(&sidePen);
				CPoint sidePolyArray[4];
				CPoint sp1(barR, barT);
				CPoint sp2(barR, barB);
				CPoint sp3(barR + m_iDepth, barB - m_iDepth);
				CPoint sp4(barR + m_iDepth, barT - m_iDepth);
				sidePolyArray[0] = sp1;
				sidePolyArray[1] = sp2;
				sidePolyArray[2] = sp3;
				sidePolyArray[3] = sp4;

				pDC->Polygon(sidePolyArray, 4);
				
				//finally, the top
				topRed = red + 35;
				topGreen = green + 35;
				topBlue = blue + 35;
				if(topRed > 255) topRed = 255;
				if(topGreen > 255) topGreen = 255;
				if(topBlue > 255) topBlue = 255;
				COLORREF topColor;
				topColor = RGB(topRed, topGreen, topBlue);
				CBrush topBrush (topColor);
				CPen topPen (PS_SOLID, 1, topColor);
				pDC->SelectObject(&topBrush);
				pDC->SelectObject(&topPen);
				CPoint topPolyArray[4];
				CPoint tp1(barL, barT);
				CPoint tp2(barR, barT);
				CPoint tp3(barR + m_iDepth, barT - m_iDepth);
				CPoint tp4(barL + m_iDepth, barT - m_iDepth);
				topPolyArray[0] = tp1;
				topPolyArray[1] = tp2;
				topPolyArray[2] = tp3;
				topPolyArray[3] = tp4;

				pDC->Polygon(topPolyArray, 4);

				pDC->SelectObject(pOldBrush);
				pDC->SelectObject(pOldPen);
			}
		}
	}
}

void CGraphView::Draw3DLineSeries(CDC* pDC)
{
	int barHeight;
	POSITION pos;
	CGraphSeries* tmpSeries;
	int blue;
	int red;
	int green;
	CBrush* pOldBrush;
	CPen* pOldPen;
	int deltaX, deltaY;

	double yAxisScale, xAxisScale;
	int tickXLocation;

	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;

	//multiply each value by 1.00 to force result into a double value, and therefore
	//make it more accurate in it's plot location.
	switch(m_iGraphQuadType)
	{
		case 1 :
			yAxisScale = ((m_iYApexPoint - m_iTopYTick) / (m_iYMaxTick * 1.00));
			xAxisScale = ((m_iRightXTick - m_iXApexPoint) / (m_iYMaxTick * 1.00));
			break;
		case 2 :
			yAxisScale = ((m_iYApexPoint - m_iTopYTick) / (m_iYMaxTick * 1.00));
			xAxisScale = ((m_iRightXTick - m_iXApexPoint) / (m_iYMaxTick * 1.00));
			break;
		case 3 :
			yAxisScale = ((m_iTopYTick - m_iYApexPoint) / (m_iYMaxTick * 1.00));
			xAxisScale = ((m_iRightXTick - m_iXApexPoint) / (m_iYMaxTick * 1.00));
			break;
		case 4 :
			yAxisScale = ((m_iTopYTick - m_iYApexPoint) / (m_iYMaxTick * 1.00));
			xAxisScale = ((m_iRightXTick - m_iXApexPoint) / (m_iYMaxTick * 1.00));
			break;
	}

	int lastXLoc, lastYLoc;
	//because of how it ends up looking, I'm forcing 3D line graphs
	//to always display as if in vertical mode graph
//	if(m_bVerticalAlign)
//	{
		for(int s = 0; s < m_iSeriesSize; s++)
		{
			lastXLoc = m_iXApexPoint + m_iLine3DXBase;
			lastYLoc = m_iYApexPoint - m_iLine3DYBase;
			//determine width of barchart data blocks

			pos = m_pGraphSeries->GetHeadPosition();
			int yDataLocation;

			for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
			{
				tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

				if(tmpSeries->GetData(s) > -1)
				{
					tickXLocation = m_iXApexPoint + (int)(x * (m_xAxisWidth / m_pGraphSeries->GetCount() + 1));
					
					barHeight = 0;
					double dataScale = 0.00;
					
					if((m_iYMaxTick - m_iYMinTick) != m_yAxisHeight)
						dataScale = (m_yAxisHeight * 1.00) / ((m_iYMaxTick - m_iYMinTick) * 1.00);
					else dataScale = 1;
					barHeight = (int)(((tmpSeries->GetData(s) - m_iYMinTick) * 1.00) * dataScale);
					if(((tmpSeries->GetData(s) - m_iYMinTick) > 0) && (barHeight < 1))
						barHeight = (int)dataScale;

					if(barHeight > m_iYApexPoint)
						barHeight = (int)((m_iYMaxTick - m_iYMinTick) * dataScale) + 5;

					yDataLocation = m_iYApexPoint - barHeight;
					//now have x and y location of center of ellipse
					COLORREF barColor;
					barColor = GetColor(s);
					red = GetRValue(barColor);
					green = GetGValue(barColor);
					blue = GetBValue(barColor);
					CBrush brush (barColor);
					pOldBrush = pDC->SelectObject(&brush);

					//draw line back to last data member
					CPen linePen (PS_SOLID, 2, BLACK);
					pOldPen = pDC->SelectObject(&linePen);
					//front side of line
					/*
					pDC->MoveTo(lastXLoc + ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)), lastYLoc - ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)));
					pDC->LineTo(tickXLocation + ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)), yDataLocation - ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)));
					pDC->MoveTo(lastXLoc + ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)) - (m_iDepth / m_iSeriesSize), lastYLoc - ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)) + (m_iDepth / m_iSeriesSize));
					pDC->LineTo(tickXLocation + ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)) - (m_iDepth / m_iSeriesSize), yDataLocation - ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)) + (m_iDepth / m_iSeriesSize));
					pDC->MoveTo(lastXLoc + ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)) - (m_iDepth / m_iSeriesSize), lastYLoc - ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)) + (m_iDepth / m_iSeriesSize));
					pDC->LineTo(lastXLoc + ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)), lastYLoc - ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)));
					pDC->MoveTo(tickXLocation + ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)) - (m_iDepth / m_iSeriesSize), yDataLocation - ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)) + (m_iDepth / m_iSeriesSize));
					pDC->LineTo(tickXLocation + ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)), yDataLocation - ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)));
*/
					//top part of line, lighter than front
					int topRed = red + 35;
					int topGreen = green + 35;
					int topBlue = blue + 35;
					if(topRed > 255) topRed = 255;
					if(topGreen > 255) topGreen = 255;
					if(topBlue > 255) topBlue = 255;
					COLORREF topColor;
					topColor = RGB(topRed, topGreen, topBlue);
					int bottomRed = red - 55;
					int bottomGreen = green - 55;
					int bottomBlue = blue - 55;
					if(bottomRed < 0) bottomRed = 0;
					if(bottomGreen < 0) bottomGreen = 0;
					if(bottomBlue < 0) bottomBlue = 0;
					COLORREF bottomColor;
					bottomColor = RGB(bottomRed, bottomGreen, bottomBlue);
	
					deltaX = tickXLocation - lastXLoc;
					deltaY = lastYLoc - yDataLocation;

					if(deltaX == deltaY)
					{
						pDC->MoveTo(tickXLocation + ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)), yDataLocation - ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)));
						pDC->LineTo(tickXLocation + ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)) - (m_iDepth / m_iSeriesSize), yDataLocation - ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)) + (m_iDepth / m_iSeriesSize));
					}
					else
					{
						CPoint d3linePolyArray[4];
						if(  
							((deltaX > deltaY) && (deltaX < 0)) ||
							((deltaX < deltaY) && (deltaX > 0))
						  )
						{
							CPen bottomPen(PS_SOLID, 1, BLACK);
							CBrush bottomBrush(bottomColor);
							pDC->SelectObject(&bottomPen);
							pDC->SelectObject(&bottomBrush);
							CPoint bp1(lastXLoc + ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)), lastYLoc - ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)));
							CPoint bp2(lastXLoc + ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)) - (m_iDepth / m_iSeriesSize), lastYLoc - ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)) + (m_iDepth / m_iSeriesSize));
							CPoint bp3(tickXLocation + ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)) - (m_iDepth / m_iSeriesSize), yDataLocation - ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)) + (m_iDepth / m_iSeriesSize));
							CPoint bp4(tickXLocation + ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)), yDataLocation - ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)));
							d3linePolyArray[0] = bp1;
							d3linePolyArray[1] = bp2;
							d3linePolyArray[2] = bp3;
							d3linePolyArray[3] = bp4;
							pDC->Polygon(d3linePolyArray, 4);
						}
						else
						{
							CPen topPen(PS_SOLID, 1, BLACK);
							CBrush topBrush(topColor);
							pDC->SelectObject(&topPen);
							pDC->SelectObject(&topBrush);
							CPoint tp1(lastXLoc + ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)), lastYLoc - ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)));
							CPoint tp2(lastXLoc + ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)) - (m_iDepth / m_iSeriesSize), lastYLoc - ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)) + (m_iDepth / m_iSeriesSize));
							CPoint tp3(tickXLocation + ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)) - (m_iDepth / m_iSeriesSize), yDataLocation - ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)) + (m_iDepth / m_iSeriesSize));
							CPoint tp4(tickXLocation + ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)), yDataLocation - ((m_iSeriesSize - s) * (m_iDepth / m_iSeriesSize)));
							d3linePolyArray[0] = tp1;
							d3linePolyArray[1] = tp2;
							d3linePolyArray[2] = tp3;
							d3linePolyArray[3] = tp4;
							pDC->Polygon(d3linePolyArray, 4);
						}
					}

					pDC->SelectObject(pOldBrush);
					pDC->SelectObject(pOldPen);

					lastXLoc = tickXLocation;
					lastYLoc = yDataLocation;
				}
			}
		}
/*	}
	else
	{
		for(int s = 0; s < m_iSeriesSize; s++)
		{
			//determine width of barchart data blocks
			seriesSpace = m_yAxisHeight / m_pGraphSeries->GetCount();

			pos = m_pGraphSeries->GetHeadPosition();
			int xDataLocation;

			for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
			{
				tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

				if(tmpSeries->GetData(s) > -1)
				{
					tickYLocation = m_iYApexPoint - ((x * seriesSpace) - (seriesSpace / 2));
					
					int barWidth;
					double dataScale = 0.00;

					if((m_iYMaxTick - m_iYMinTick) != m_xAxisWidth)
						dataScale = (m_xAxisWidth * 1.00) / ((m_iYMaxTick - m_iYMinTick) * 1.00);
					else dataScale = 1;
					barWidth = (int)(((tmpSeries->GetData(s) - m_iYMinTick) * 1.00) * dataScale);
					if(((tmpSeries->GetData(s) - m_iYMinTick) > 0) && (barWidth < 1))
						barWidth = (int)dataScale;

					xDataLocation = m_iXApexPoint + barWidth;
					
					//now have x and y location of center of ellipse
					COLORREF barColor;
					barColor = GetColor(s);
					red = GetRValue(barColor);
					green = GetGValue(barColor);
					blue = GetBValue(barColor);
					CBrush brush (barColor);
					pOldBrush = pDC->SelectObject(&brush);
					//draw line back to last data member
					if(x > 1)
					{
						CPen linePen (PS_SOLID, 1, barColor);
						pOldPen = pDC->SelectObject(&linePen);
						//front side of line
						pDC->MoveTo(lastXLoc, lastYLoc);
						pDC->LineTo(xDataLocation, tickYLocation);

						//top part of line, lighter than front
						int topRed = red + 35;
						int topGreen = green + 35;
						int topBlue = blue + 35;
						if(topRed > 255) topRed = 255;
						if(topGreen > 255) topGreen = 255;
						if(topBlue > 255) topBlue = 255;
						COLORREF topColor;
						topColor = RGB(topRed, topGreen, topBlue);
						int bottomRed = red - 55;
						int bottomGreen = green - 55;
						int bottomBlue = blue - 55;
						if(bottomRed < 0) bottomRed = 0;
						if(bottomGreen < 0) bottomGreen = 0;
						if(bottomBlue < 0) bottomBlue = 0;
						COLORREF bottomColor;
						bottomColor = RGB(bottomRed, bottomGreen, bottomBlue);
						
						deltaX = xDataLocation - lastXLoc;
						deltaY = lastYLoc - tickYLocation;

						if(deltaX == deltaY)
						{
							pDC->MoveTo(xDataLocation, tickYLocation);
							pDC->LineTo(xDataLocation + m_iDepth, tickYLocation - m_iDepth);
						}
						else
						{
							CPoint d3linePolyArray[4];
							if(  
								((deltaY > deltaX) && (deltaY < 0)) ||
								((deltaY < deltaX) && (deltaY > 0))
							  )
							{
								CPen bottomPen(PS_SOLID, 1, BLACK);
								CBrush bottomBrush(bottomColor);
								pDC->SelectObject(&bottomPen);
								pDC->SelectObject(&bottomBrush);
								CPoint bp1(lastXLoc, lastYLoc);
								CPoint bp2(lastXLoc + m_iDepth, lastYLoc - m_iDepth);
								CPoint bp3(xDataLocation + m_iDepth, tickYLocation - m_iDepth);
								CPoint bp4(xDataLocation, tickYLocation);
								d3linePolyArray[0] = bp1;
								d3linePolyArray[1] = bp2;
								d3linePolyArray[2] = bp3;
								d3linePolyArray[3] = bp4;
								pDC->Polygon(d3linePolyArray, 4);
							}
							else
							{
								CPen topPen(PS_SOLID, 1, BLACK);
								CBrush topBrush(topColor);
								pDC->SelectObject(&topPen);
								pDC->SelectObject(&topBrush);
								CPoint tp1(lastXLoc, lastYLoc);
								CPoint tp2(lastXLoc + m_iDepth, lastYLoc - m_iDepth);
								CPoint tp3(xDataLocation + m_iDepth, tickYLocation - m_iDepth);
								CPoint tp4(xDataLocation, tickYLocation);
								d3linePolyArray[0] = tp1;
								d3linePolyArray[1] = tp2;
								d3linePolyArray[2] = tp3;
								d3linePolyArray[3] = tp4;
								pDC->Polygon(d3linePolyArray, 4);
							}
						}

						pDC->SelectObject(pOldBrush);
						pDC->SelectObject(pOldPen);
					}
					lastXLoc = xDataLocation;
					lastYLoc = tickYLocation;
				}
			}
		}
	}*/
}

void CGraphView::Draw3DPieSeries(CDC* pDC)
{
	double labelData = 0.00;
	int radius;
	POSITION pos;
	CGraphSeries* tmpSeries;
	int seriesSpace;
	int s;
		
	/////////////////////////////////
	// Mended By FanHua:
	/////////////////////////////////
	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;

	int iClientArea=m_yAxisHeight*m_xAxisWidth;
	int iUnitArea=iClientArea/iSerQty;
	seriesSpace=sqrt((double)iUnitArea);
	if(seriesSpace<1)return;

	int iHorQty=m_xAxisWidth/seriesSpace-1;
	int iVerQty=m_yAxisHeight/seriesSpace;

	while(iHorQty*iVerQty<iSerQty)
	{
		seriesSpace--;
		iHorQty=m_xAxisWidth/seriesSpace-1;
		iVerQty=m_yAxisHeight/seriesSpace;
	}

	radius = seriesSpace / 2 *0.9; 

	CFont labelFont;
	labelFont.CreateFont(m_iPieLabelFontSize , 0, 0, 0, 0, FALSE, FALSE, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
	CFont* pOldFont = (CFont*) pDC->SelectObject(&labelFont);

	int pieLeft		= 0;
	int pieRight	= 0;
	int centerXPie	= 0;
	int centerYPie	= 0; 
	int iHorOrder	= 0;
	int iVerOrder	= 0;

	CSize sizeLabel;
	CString sLabel;

	pDC->SetBkMode (TRANSPARENT);
	/////////////////////////////////
	// Mended by fanhua over
	/////////////////////////////////

	pos = m_pGraphSeries->GetHeadPosition();
	CPieDrawer pie;

	for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
	{
		if(iHorOrder>=iHorQty)
		{
			iHorOrder=0;
			iVerOrder++;
		}
		centerXPie  = m_iXApexPoint+iHorOrder*seriesSpace+seriesSpace;
		centerYPie	= m_iYApexPoint-iVerOrder*seriesSpace-seriesSpace/2;
		pieLeft		= centerXPie-radius;
		pieRight	= centerXPie+radius;

		tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

		CRect pieRect (pieLeft, 
				centerYPie - radius*0.5,
				pieRight, 
				centerYPie + radius*0.5);

		int nPieHeight=radius*0.5;
		pie.SetPar(pieRect,nPieHeight);
		pie.SetPartQty (m_iSeriesSize);

		for(s = 0; s < m_iSeriesSize; s++)
		{
			pie.SetPartWeight(s, tmpSeries->GetData(s));
			pie.SetColor (s,GetColor(s));
		}


		pie.Draw (pDC);

		// Draw the pie label :
		sLabel=tmpSeries->GetLabel();
		sizeLabel=pDC->GetTextExtent (sLabel);

		pDC->TextOut(	centerXPie - (sizeLabel.cx / 2),
						centerYPie + radius + 5, sLabel);

		//
		iHorOrder++;
	}
	pDC->SelectObject(pOldFont);
}

void CGraphView::Draw3DStackedBarSeries(CDC* pDC)
{
	int barWidth;
	int barL, barT, barR, barB;
	int tickXLocation;
	int seriesSpace;
	int barHeight;
	POSITION pos;
	CGraphSeries* tmpSeries;
	int blue;
	int red;
	int green;

	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;


	//determine width of barchart data blocks
	seriesSpace = m_xAxisWidth  / m_pGraphSeries->GetCount();
	barWidth = (int)(seriesSpace * .8);

	pos = m_pGraphSeries->GetHeadPosition();

	double dataScale = 0.00;
	dataScale = (m_yAxisHeight * 1.00) / (m_iYMaxTick - m_iYMinTick);
	double lfData=0.0;
	for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
	{
		tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

		tickXLocation = m_iXApexPoint + ((x * seriesSpace) - (seriesSpace / 2));

		barT = m_iYApexPoint;	//this is a running total;
							//it starts at m_iYApexPoint so barB can
							//start there, then moves up by barHeight
		for(int s = 0; s < m_iSeriesSize; s++)
		{
			if(tmpSeries->GetData(s) > -1)
			{
				lfData=tmpSeries->GetData(s);
				barHeight = (int)(((lfData - m_iYMinTick) * 1.00) * dataScale);
				if(((lfData - m_iYMinTick) > 0) && (barHeight < 1))
					barHeight = (int)dataScale;

				barB = barT;
				barL = tickXLocation - (barWidth / 2);
				if(barHeight > m_yAxisHeight)
					barT = barB - m_yAxisHeight;
				else
					barT = barB - barHeight;
				barR = barL + barWidth;

				COLORREF barColor;
				barColor = GetColor(s);
				CBrush brush (barColor);
				CPen rectPen (PS_SOLID, 1, barColor);
				CPen* pOldPen;
				pOldPen = pDC->SelectObject(&rectPen);
				CBrush* pOldBrush;
				pOldBrush = pDC->SelectObject(&brush);
				pDC->Rectangle(barL, barT, barR, barB);

				//now, we do the side
				//side is darker than front, so subtract
				//from color to make closer to black
				red = GetRValue(barColor);
				green = GetGValue(barColor);
				blue = GetBValue(barColor);
				int sideRed = red - 35;
				int sideGreen = green - 35;
				int sideBlue = blue - 35;
				if(sideRed < 0) sideRed = 0;
				if(sideGreen < 0) sideGreen = 0;
				if(sideBlue < 0) sideBlue = 0;
				COLORREF sideColor;
				sideColor = RGB(sideRed, sideGreen, sideBlue);
				CBrush sideBrush (sideColor);
				CPen sidePen (PS_SOLID, 1, sideColor);
				pDC->SelectObject(&sideBrush);
				pDC->SelectObject(&sidePen);
				CPoint sidePolyArray[4];
				CPoint sp1(barR, barT);
				CPoint sp2(barR, barB);
				CPoint sp3(barR + m_iDepth, barB - m_iDepth);
				CPoint sp4(barR + m_iDepth, barT - m_iDepth);
				sidePolyArray[0] = sp1;
				sidePolyArray[1] = sp2;
				sidePolyArray[2] = sp3;
				sidePolyArray[3] = sp4;

				pDC->Polygon(sidePolyArray, 4);
				
				//finally, the top
				int topRed = red + 35;
				int topGreen = green + 35;
				int topBlue = blue + 35;
				if(topRed > 255) topRed = 255;
				if(topGreen > 255) topGreen = 255;
				if(topBlue > 255) topBlue = 255;
				COLORREF topColor;
				topColor = RGB(topRed, topGreen, topBlue);
				CBrush topBrush (topColor);
				CPen topPen (PS_SOLID, 1, topColor);
				pDC->SelectObject(&topBrush);
				pDC->SelectObject(&topPen);
				CPoint topPolyArray[4];
				CPoint tp1(barL, barT);
				CPoint tp2(barR, barT);
				CPoint tp3(barR + m_iDepth, barT - m_iDepth);
				CPoint tp4(barL + m_iDepth, barT - m_iDepth);
				topPolyArray[0] = tp1;
				topPolyArray[1] = tp2;
				topPolyArray[2] = tp3;
				topPolyArray[3] = tp4;

				pDC->Polygon(topPolyArray, 4);

				pDC->SelectObject(pOldBrush);
				pDC->SelectObject(pOldPen);
			}
		}
	}
}


void CGraphView::PrintBarSeries(CDC* pDC)
{
	int barWidth;
	int dataPlotSize;   //used to plot rects of data
	int barL, barT, barR, barB;
	int tickXLocation;
	int seriesSpace;
	int barHeight;  //for scalability
	POSITION pos;
	CGraphSeries* tmpSeries;

	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;


	//determine width of barchart data blocks
	seriesSpace = m_xAxisWidth / m_pGraphSeries->GetCount();
	barWidth = (int)((seriesSpace * .6) / m_iSeriesSize);
	dataPlotSize = m_iSeriesSize * barWidth;

	pos = m_pGraphSeries->GetHeadPosition();

	for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
	{
		tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

		tickXLocation = m_iXApexPoint + ((x * seriesSpace) - (seriesSpace / 2));

		for(int s = 0; s < m_iSeriesSize; s++)
		{
			if(tmpSeries->GetData(s) > -1)
			{
				double dataScale = 0.00;
				dataScale = ((m_yAxisHeight - 100) * 1.00) / (m_iYMaxTick - m_iYMinTick);
				barHeight = (int)(((tmpSeries->GetData(s) - m_iYMinTick) * 1.00) * dataScale);
				if(((tmpSeries->GetData(s) - m_iYMinTick) > 0) && (barHeight < 1))
					barHeight = (int)dataScale;

				barL = tickXLocation - (dataPlotSize / 2) + (s * barWidth);
				if(barHeight > m_yAxisHeight)
					barT = m_iYApexPoint + m_yAxisHeight;
				else
					barT = m_iYApexPoint + barHeight;
				barR = barL + barWidth;
				barB = m_iYApexPoint;
				
				COLORREF barColor;
				barColor = GetColor(s);
				CBrush brush (barColor);
				CBrush* pOldBrush;
				pOldBrush = pDC->SelectObject(&brush);
				pDC->Rectangle(barL, barT, barR, barB);
				pDC->SelectObject(pOldBrush);
			}
		}
	}
}

void CGraphView::PrintLineSeries(CDC* pDC)
{
	int barWidth;
	int dataPlotSize;   //used to plot rects of data
	int tickXLocation;
	int seriesSpace;
	int barHeight;  //for scalability
	POSITION pos;
	CGraphSeries* tmpSeries;

	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;


	int lastXLoc, lastYLoc;
	for(int s = 0; s < m_iSeriesSize; s++)
	{
		//determine width of barchart data blocks
		seriesSpace = m_xAxisWidth / m_pGraphSeries->GetCount();
		barWidth = (int)((seriesSpace * .6) / m_iSeriesSize);
		dataPlotSize = m_iSeriesSize * barWidth;

		pos = m_pGraphSeries->GetHeadPosition();

		for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
		{
			tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

			if(tmpSeries->GetData(s) > -1)
			{
				tickXLocation = m_iXApexPoint + ((x * seriesSpace) - (seriesSpace / 2));
				
				barHeight = 0;
				double dataScale = 0.00;
				
				if((m_iYMaxTick - m_iYMinTick) != m_yAxisHeight)
					dataScale = ((m_yAxisHeight * 1.00) / ((m_iYMaxTick - m_iYMinTick) * 1.00)) * m_iYTickSpace;	
				else dataScale = m_iYTickSpace * 15.00;

				int axisHeight = (int)(dataScale * m_iYNumTicks);
				double barPercent = 0.00;
				barPercent = ((tmpSeries->GetData(s) - m_iYMinTick) * 1.00) / m_iYMaxTick;
				barHeight = (int)(barPercent * axisHeight);
				if(((tmpSeries->GetData(s) - m_iYMinTick) > 0) && (barHeight < 1))
					barHeight = (int)dataScale;

				int yDataLocation = m_iYApexPoint + barHeight;
				
				//now have x and y location of center of ellipse
				COLORREF barColor;
				barColor = GetColor(s);
				CBrush brush (barColor);
				CBrush* pOldBrush;
				pOldBrush = pDC->SelectObject(&brush);
				//draw line back to last data member
				if(x > 1)
				{
					CPen* pOldPen;
					CPen linePen (PS_SOLID, 20, barColor);
					pOldPen = pDC->SelectObject(&linePen);
					pDC->MoveTo(lastXLoc, lastYLoc);
					pDC->LineTo(tickXLocation, yDataLocation);
					pDC->SelectObject(pOldPen);
				}
				//now draw ellipse...
				pDC->Ellipse(tickXLocation + 60, yDataLocation + 60,
					tickXLocation - 60, yDataLocation - 60);
				lastXLoc = tickXLocation;
				lastYLoc = yDataLocation;
				pDC->SelectObject(pOldBrush);
			}
		}
	}
}

void CGraphView::PrintPieSeries(CDC* pDC)
{
	int seriesSpace;
	POSITION pos;
	CGraphSeries* tmpSeries;

	double dataSum = 0.00;  //for storing cumulative sum
	int lastXLocation, lastYLocation;
	int newXLocation, newYLocation;
	double percent = 0.00;
	int degrees;
	double totalSum = 0.00;
	int deltaXY;
	int radius;

	double labelData = 0.00;
	int labelXLocation, labelYLocation;
	double labelPercent = 0.00;
	int labelDegrees;
	int labelDeltaXY;
	int labelLineXStart, labelLineYStart;
	int labelLineXEnd, labelLineYEnd;
	int maxLabelWidth;
	int maxLabelHeight;
	TEXTMETRIC tm;
	POSITION labelPos;

	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;

		
	lastXLocation = 0;
	lastYLocation = 0;

	pDC->GetTextMetrics(&tm);
	maxLabelWidth = tm.tmMaxCharWidth + 50;
	maxLabelHeight = tm.tmHeight + 30;

	//pie labels are stored in a list and drawn after entire pie
	//is completed.
	CObList *pieLabels;
	CGraphPieLabel *pieLabel;

	//determine width of pie display area
	if(m_xAxisWidth > m_yAxisHeight)
		seriesSpace = m_yAxisHeight / m_pGraphSeries->GetCount();
	else
		seriesSpace = m_xAxisWidth / m_pGraphSeries->GetCount();
	seriesSpace -= (3 * maxLabelWidth);  //allows text like 25%  (3 chars)

	//to plot a pie plus labels inside of series space, use the following :
	//(3 * radius) + (2 * label width) = series space 
	//so, 3*radius = series space - (2 * label width)
	// 1 radius = (series space - (2 * label width)) / 3
	radius = seriesSpace / 3;  //pie needs 2 radius, + 1 extra for line to labels = 3 for my divisor

	int centerYPie = m_iPGraphT - (m_yAxisHeight / 2) - 500;
	
	pos = m_pGraphSeries->GetHeadPosition();
	for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
	{
		pieLabels = new CObList();

		tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);
		totalSum = 0;
		for(int s = 0; s < m_iSeriesSize; s++)
			totalSum += tmpSeries->GetData(s);
		int pieLeft, pieRight;
		if(m_pGraphSeries->GetCount() == 1)
		{
			pieLeft = m_iXApexPoint + (m_xAxisWidth / 2) - radius;
		}
		else
		{
			pieLeft = m_iXApexPoint + 15 + ((x * 2 - 1) * ((m_xAxisWidth / m_pGraphSeries->GetCount()) / 2)) - radius;
		}
		pieRight = pieLeft + (2 * radius);
		CRect pieRect (pieLeft, 
				centerYPie + radius,
				pieRight, 
				centerYPie - radius);
		int centerXPie = pieLeft + radius;

		CFont pieFont;
		pieFont.CreateFont(m_iXTickFontSize * 20, 0, 0, 0, 700, FALSE, FALSE, 0,
			ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
		CFont* pOldFont = (CFont*) pDC->SelectObject(&pieFont);

		//plot series label
		pDC->TextOut(centerXPie - ((tmpSeries->GetLabel().GetLength() / 2) * ((m_iXTickFontSize / 2) * 20)),
					centerYPie - radius - maxLabelHeight - 600, tmpSeries->GetLabel());
		pDC->SelectObject(pOldFont);

		lastXLocation = pieLeft;
		lastYLocation = centerYPie;
		
		dataSum = 0;
		for(s = 0; s < m_iSeriesSize; s++)
		{
			if(tmpSeries->GetData(s) > 0)
			{
				int seriesDataValue;
				seriesDataValue = tmpSeries->GetData(s);
				dataSum += seriesDataValue;
				percent = (dataSum * 100) / totalSum;
				degrees = (int)((360 * percent) / 100);

				labelData = tmpSeries->GetData(s) / 2;
				labelPercent = ((dataSum - labelData) / totalSum) * 100;
				labelDegrees = (int)((360 * labelPercent) / 100);

					//degress / 90 will never exceed 4.
					//this can tell us the quadrant of destination
				deltaXY = (degrees * radius) / 90;
				labelDeltaXY = (labelDegrees * radius) / 90;
					//deltaXY is change from start point of pie 0
					//this value is total change.  so if radius is 300
					//and degrees is 270, delta is 300.  The change 
					//would move both x and y 300 pixels.  For x, 100
					//to right is center, another 100 to right edge,
					//100 back to center.  For y, 100 to bottom, 100
					//back to center, 100 to top. thus gives 270 degree
					//rotation.

				//determine destination quadrant...
					//and set newXLocation and newYLocation values...
				int quadrant = degrees / 90;  //truncates decimal
				int labelQuadrant = labelDegrees / 90;
				switch(quadrant)
				{
					//in the computations below, the remarked line is
					//the original computation.  The line above it, for
					//actual use, is the simplified line, and gives the
					//exact same result
					case 0 : newXLocation = pieLeft + deltaXY;
							 newYLocation = centerYPie - deltaXY;
							 break;
					case 1 : newXLocation = pieLeft + deltaXY;
							 newYLocation = centerYPie - (2 * radius) + deltaXY;
							 break;
					case 2 : newXLocation = pieLeft + (4 * radius) - deltaXY;
							 newYLocation = centerYPie - (2 * radius) + deltaXY;
							 break;
					case 3 : newXLocation = pieLeft + (4 * radius) - deltaXY;
							 newYLocation = centerYPie + (4 * radius) - deltaXY;
							 break;
					case 4 : newXLocation = pieLeft;
							 newYLocation = centerYPie + 1;
							 break;
				}
				
				switch(labelQuadrant)
				{
					//after getting X & Y location for label, we take
					//1/2 the delta between x y locations and center pie
					case 0 : labelXLocation = pieLeft + labelDeltaXY;
							 labelYLocation = centerYPie - labelDeltaXY;
							 labelLineXStart = labelXLocation + ((centerXPie - labelXLocation) / 2);
							 labelLineYStart = labelYLocation - ((labelYLocation - centerYPie) / 2);
							 labelLineXEnd = labelXLocation - (radius / 2);
							 labelLineYEnd = labelYLocation - (radius / 2);
							 break;
					case 1 : labelXLocation = pieLeft + labelDeltaXY;
							 labelYLocation = centerYPie - (2 * radius) + labelDeltaXY;
							 labelLineXStart = labelXLocation - ((labelXLocation - centerXPie) / 2);
							 labelLineYStart = labelYLocation - ((labelYLocation - centerYPie) / 2);
							 labelLineXEnd = labelXLocation + (radius / 2);
							 labelLineYEnd = labelYLocation - (radius / 2);
							 break;
					case 2 : labelXLocation = pieLeft + (4 * radius) - labelDeltaXY;
							 labelYLocation = centerYPie - (2 * radius) + labelDeltaXY;
							 labelLineXStart = labelXLocation - ((labelXLocation - centerXPie) / 2);
							 labelLineYStart = labelYLocation - ((labelYLocation - centerYPie) / 2);
							 labelLineXEnd = labelXLocation + (radius / 2);
							 labelLineYEnd = labelYLocation + (radius / 2);
							 break;
					case 3 : labelXLocation = pieLeft + (4 * radius) - labelDeltaXY;
							 labelYLocation = centerYPie + (4 * radius) - labelDeltaXY;
							 labelLineXStart = labelXLocation + ((centerXPie - labelXLocation) / 2);
							 labelLineYStart = labelYLocation - ((labelYLocation - centerYPie) / 2);
							 labelLineXEnd = labelXLocation - (radius / 2);
							 labelLineYEnd = labelYLocation + (radius / 2);
							 break;
//there should never be a half point ending on 4, so leave it out
				}

				pieLabel = new CGraphPieLabel();

				pieLabel->lineXStart = labelLineXStart;
				pieLabel->lineYStart = labelLineYStart;
				pieLabel->lineXEnd = labelLineXEnd;
				pieLabel->lineYEnd = labelLineYEnd;
				switch(labelQuadrant)
				{
					case 0 : //label to left of line
							 pieLabel->topLeftX = labelLineXEnd - maxLabelWidth;
							 pieLabel->topLeftY = labelLineYEnd;
							 break;
					case 1 : //label to right of line
							 pieLabel->topLeftX = labelLineXEnd + 50;
							 pieLabel->topLeftY = labelLineYEnd;
							 break;
					case 2 : //label to right of line
							 pieLabel->topLeftX = labelLineXEnd + 50;
							 pieLabel->topLeftY = labelLineYEnd + maxLabelHeight;
							 break;
					case 3 : //label to left of line
							 pieLabel->topLeftX = labelLineXEnd - maxLabelWidth;
							 pieLabel->topLeftY = labelLineYEnd + maxLabelHeight;
							 break;
				}
				pieLabel->labelQuadrant = labelQuadrant;
				int roundPercent;
				roundPercent = (int)((seriesDataValue * 100) / totalSum);
				pieLabel->pieLabel.Format("%d%%", roundPercent);
				pieLabels->AddTail(pieLabel);

				if(s == 0)
					lastYLocation -= 1;

				CPoint p1 (lastXLocation, lastYLocation);
				CPoint p2 (newXLocation, newYLocation);
				COLORREF barColor;
				barColor = GetColor(s);
				CBrush brush (barColor);
				CBrush* pOldBrush;
				CPen piePen(PS_SOLID, 1, barColor);
				CPen* pOldPen;
				pOldBrush = pDC->SelectObject(&brush);
				pOldPen = pDC->SelectObject(&piePen);
				pDC->Pie(pieRect, p1, p2); 
				pDC->SelectObject(pOldBrush);
				pDC->SelectObject(pOldPen);

				lastXLocation = newXLocation;
				lastYLocation = newYLocation;
			}
		}

		//draw lines and labels for pies slices
		CBrush lineBrush (BLACK);
		CBrush* pOldBrush;
		pOldBrush = pDC->SelectObject(&lineBrush);
		POSITION mainLinePos, checkLinePos;
		mainLinePos = pieLabels->GetHeadPosition();
		int numLinesDrawn = 0;
		CGraphPieLabel* currentLabel;
		CGraphPieLabel* tmpLabel;
		while(mainLinePos != NULL)
		{
			currentLabel = (CGraphPieLabel*)pieLabels->GetNext(mainLinePos);
			int r = 0;
			checkLinePos = pieLabels->GetHeadPosition();
			while(r < numLinesDrawn)
			{
				//check if any overlap in label areas
				tmpLabel = (CGraphPieLabel*)pieLabels->GetAt(checkLinePos);
				if((currentLabel->topLeftX > tmpLabel->topLeftX) &&
					(currentLabel->topLeftX < (tmpLabel->topLeftX + maxLabelWidth)) &&
					(currentLabel->topLeftY < tmpLabel->topLeftY) &&
					(currentLabel->topLeftY > (tmpLabel->topLeftY - maxLabelHeight)))
				{
					//OVERLAP !!!
					//move current label top left position up or down
					//depending on its quadrant
					if(currentLabel->labelQuadrant < 2)
					{
						//move label down to tmplabel topleft + height
						currentLabel->topLeftY = tmpLabel->topLeftY - maxLabelHeight;
						currentLabel->lineYEnd = tmpLabel->lineYEnd - maxLabelHeight;
					}
					else
					{
						//move label up to tmpLabel topleft - height
						currentLabel->topLeftY = tmpLabel->topLeftY + maxLabelHeight;
						currentLabel->lineYEnd = tmpLabel->lineYEnd + maxLabelHeight;
					}
					//reset r value to 0 so it starts over, just in
					//case we moved the label and it overlaps another
					r = 0;
					checkLinePos = pieLabels->GetHeadPosition();
				}
				else
				{
					r++;
					pieLabels->GetNext(checkLinePos);
				}

			}
			//draw the line and label
			pDC->MoveTo(currentLabel->lineXStart, currentLabel->lineYStart);
			pDC->LineTo(currentLabel->lineXEnd, currentLabel->lineYEnd);

			//write the label
			pDC->TextOut(currentLabel->topLeftX, currentLabel->topLeftY,
					currentLabel->pieLabel);
			numLinesDrawn++;
		}

		pDC->SelectObject(pOldBrush);

		//now done, remove everything inside the label list
		labelPos = pieLabels->GetHeadPosition();
		while(labelPos != NULL)
		{
			pieLabel = (CGraphPieLabel*)pieLabels->GetNext(labelPos);
			delete pieLabel;
		}
		delete pieLabels;
	}
}


void CGraphView::PrintScatterSeries(CDC* pDC)
{
	//m_iRightXTick and m_iTopYTick contain the outer bounds of the axis ticks.
	//So, if m_iYMaxTick is 100 on both axis lines, then 100, 100 would be top
	//right.  We will use the bounds to see spacing from apex points and then
	//scale so any point can be plotted inside

	double yAxisScale, xAxisScale;
	int tickXLocation, tickYLocation;

	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;


	//multiply each value by 1.00 to force result into a double value, and therefore
	//make it more accurate in it's plot location.
	yAxisScale = ((m_iPTopYTick - m_iYApexPoint) / (m_iYMaxTick * 1.00));
	xAxisScale = ((m_iPRightXTick - m_iXApexPoint) / (m_iYMaxTick * 1.00));

	//points will now plot as ((value * scale) + apex point)
	COLORREF barColor;
	barColor = BLACK;
	CBrush brush (barColor);
	CBrush* pOldBrush;
	pOldBrush = pDC->SelectObject(&brush);

	POSITION pos,posSer;
	CGraphSeries* tmpSeries;
	CGraphDataSet* pDataSet=NULL;
	for(pos = m_pGraphSeries->GetHeadPosition(); pos != NULL; m_pGraphSeries->GetNext(pos))
	{
		tmpSeries = (CGraphSeries*)m_pGraphSeries->GetAt(pos);

		posSer=tmpSeries->GetHeadPosition ();
		while(posSer)
		{
			pDataSet=tmpSeries->GetDataValue (posSer);
			tickXLocation = pDataSet->xPosition  * xAxisScale + m_iXApexPoint;
			tickYLocation = m_iYApexPoint + pDataSet->yValue * yAxisScale;
			
			//draw ellipse...
			pDC->Ellipse(tickXLocation - 60, tickYLocation - 60,
				tickXLocation + 60, tickYLocation + 60);
		}
	}
	pDC->SelectObject(pOldBrush);

}

void CGraphView::PrintBoxWhiskerSeries(CDC* pDC)
{
	int upperQuartile;
	int lowerQuartile;
	int median;
	int highValue;
	int lowValue;
	
	COLORREF barColor;
	barColor = BLACK;
	CBrush brush (barColor);
	CBrush* pOldBrush;
	pOldBrush = pDC->SelectObject(&brush);

	int barWidth;
	int barL, barT, barR, barB;
	int tickXLocation;
	int seriesSpace;
	int barHeight;
	POSITION pos;
	CGraphSeries* tmpSeries;

	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;


	pos = m_pGraphSeries->GetHeadPosition();
	CUIntArray dataArray;
	CUIntArray sortedArray;

	for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
	{
		dataArray.RemoveAll();
		sortedArray.RemoveAll();

		CObList *sortedData;
		sortedData = new CObList();
		tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);
		m_iSeriesSize = tmpSeries->GetDataCount();

		int dataValue;
		for(int s = 0; s < m_iSeriesSize; s++)
		{
			dataValue = 0;
			if(tmpSeries->GetData(s) > -1)
				dataValue = tmpSeries->GetData(s);
			dataArray.Add(dataValue);
		}

		//sort the array
		dataValue = dataArray.GetAt(0);
		sortedArray.Add(dataValue);
		for(int d = 1; d < dataArray.GetSize(); d++)
		{
			dataValue = dataArray.GetAt(d);
			BOOL placed = FALSE;
			for(int s = 0; s < sortedArray.GetSize(); s++)
			{
				int tmpI = sortedArray.GetAt(s);
				if(dataValue <= tmpI)
				{
					sortedArray.InsertAt(s, dataValue);
					placed = TRUE;
					break;
				}
			}
			if(!placed)	//add at end
				sortedArray.Add(dataValue);
		}
		
		//sortedArray now contains the sorted list of all data in this
		//series.  From here, we derive the other box-whisker data
		
		int medialElement;
		div_t div_result;
		div_result = div(sortedArray.GetSize(), 2);

		if(div_result.rem == 0)	//even number of elements
		{
			//size is not 0 base, so below, I subtract 1 to 0 base it.
			medialElement = (sortedArray.GetSize() / 2) - 1;
			median = sortedArray.GetAt(medialElement) + 
						((sortedArray.GetAt(medialElement + 1) - 
						sortedArray.GetAt(medialElement)) / 2);
			highValue = sortedArray.GetAt(sortedArray.GetSize() - 1);
			lowValue = sortedArray.GetAt(0);
			div_t div2Result;
			div2Result = div(medialElement + 1, 2);
			if(div2Result.rem == 0)	//even again
			{
				upperQuartile = sortedArray.GetAt(medialElement + 1 + (medialElement / 2)) +
									(sortedArray.GetAt(medialElement + (medialElement / 2) + 2) -
									sortedArray.GetAt(medialElement + (medialElement / 2))) / 2;
				lowerQuartile = sortedArray.GetAt(medialElement / 2) +
									((sortedArray.GetAt((medialElement / 2) + 1) -
									sortedArray.GetAt(medialElement / 2)) / 2);
			}
			else	//odd
			{
				upperQuartile = sortedArray.GetAt(medialElement + 1 + (medialElement / 2));
				lowerQuartile = sortedArray.GetAt(medialElement / 2);
			}
		}
		else	//odd number of elements
		{
			//size is not 0 base, so below, I subtract 1 to 0 base it.
			medialElement = sortedArray.GetSize() / 2;
			median = sortedArray.GetAt(medialElement);
			highValue = sortedArray.GetAt(sortedArray.GetSize() - 1);
			lowValue = sortedArray.GetAt(0);
			div_t div2Result;
			div2Result = div(medialElement, 2);
			if(div2Result.rem == 0)	//even 
			{
				upperQuartile = sortedArray.GetAt(medialElement + (medialElement / 2)) +
									(sortedArray.GetAt(medialElement + (medialElement / 2) + 1) -
									sortedArray.GetAt(medialElement + (medialElement / 2))) / 2;
				lowerQuartile = sortedArray.GetAt((medialElement - 1) / 2) +
									((sortedArray.GetAt((medialElement + 1) / 2) -
									sortedArray.GetAt((medialElement - 1) / 2)) / 2);
			}
			else	//odd
			{
				upperQuartile = sortedArray.GetAt(medialElement + 1 + (medialElement / 2));
				lowerQuartile = sortedArray.GetAt(medialElement / 2);
			}
		}

		//data has been computed for median, high, low, and interquartile range
		//now we can draw the series
		seriesSpace = m_xAxisWidth / m_pGraphSeries->GetCount();

		barWidth = (int)(seriesSpace * .8);

		double tickScale = 0.00;
		tickScale = (m_yAxisHeight - 100) / m_iYNumTicks;	//this must be consistent with PrintAxis()

		tickXLocation = m_iXApexPoint + ((x * seriesSpace) - (seriesSpace / 2));

		barL = tickXLocation - (barWidth / 2);
		barR = barL + barWidth;
		double dataScale = 0.00;
		dataScale = ((m_yAxisHeight - 60) * 1.00) / (m_iYMaxTick - m_iYMinTick);

		//top cross bar (max value)
		barHeight = (int)((highValue * 1.00) * tickScale);
		barT = m_iYApexPoint + barHeight;
		barB = barT - 60;
		pDC->Rectangle(barL, barT, barR, barB);

		//bottom cross bar (min value)
		barHeight = (int)((lowValue * 1.00) * tickScale);
		barT = m_iYApexPoint + barHeight;
		barB = barT + 60;
		pDC->Rectangle(barL, barT, barR, barB);

		//vertical line (whisker)
		barHeight = (int)((highValue * 1.00) * tickScale);
		barT = m_iYApexPoint + barHeight;
		pDC->Rectangle(tickXLocation - 40, barT, tickXLocation + 40, barB);

		//box (interquartile range, from upper quartile to lower quartile)
		barHeight = (int)(upperQuartile * tickScale);
		barT = m_iYApexPoint + barHeight;
		barHeight = (int)(lowerQuartile * tickScale);
		barB = m_iYApexPoint + barHeight;
		pDC->Rectangle(barL, barT, barR, barB);

		//draw median line (in RED)
		CPen* pOldPen;
		CPen linePen (PS_SOLID, 1, RED);
		pOldPen = pDC->SelectObject(&linePen);
		barHeight = (int)((median * 1.00) * tickScale);
		pDC->MoveTo(barL, m_iYApexPoint + barHeight);
		pDC->LineTo(barR, m_iYApexPoint + barHeight);
		pDC->SelectObject(pOldPen);
	}

	pDC->SelectObject(pOldBrush);
}

void CGraphView::PrintStackedBarSeries(CDC* pDC)
{
	int barWidth;
	int barL, barT, barR, barB;
	int tickXLocation;
	int seriesSpace;
	int barHeight;  //for scalability
	POSITION pos;
	CGraphSeries* tmpSeries;

	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;


	//determine width of barchart data blocks
	seriesSpace = m_xAxisWidth / m_pGraphSeries->GetCount();
	barWidth = (int)(seriesSpace * .6);

	pos = m_pGraphSeries->GetHeadPosition();

	double dataScale = 0.00;
	dataScale = ((m_yAxisHeight - 100) * 1.00) / (m_iYMaxTick - m_iYMinTick);
	for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
	{
		tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

		tickXLocation = m_iXApexPoint + ((x * seriesSpace) - (seriesSpace / 2));
		
		barT = m_iYApexPoint;	//this is a running total;
							//it starts at m_iYApexPoint so barB can
							//start there, then moves up by barHeight
		for(int s = 0; s < m_iSeriesSize; s++)
		{
			if(tmpSeries->GetData(s) > -1)
			{
				barHeight = (int)(((tmpSeries->GetData(s) - m_iYMinTick) * 1.00) * dataScale);
				if(((tmpSeries->GetData(s) - m_iYMinTick) > 0) && (barHeight < 1))
					barHeight = (int)dataScale;

				barB = barT;
				barL = tickXLocation - (barWidth / 2);
				if(barHeight > m_yAxisHeight)
					barT = barB + m_yAxisHeight;
				else
					barT = barB + barHeight;
				barR = barL + barWidth;

				COLORREF barColor;
				barColor = GetColor(s);
				CBrush brush (barColor);
				CBrush* pOldBrush;
				pOldBrush = pDC->SelectObject(&brush);
				pDC->Rectangle(barL, barT, barR, barB);
				pDC->SelectObject(pOldBrush);
			}
		}
	}
}

void CGraphView::PrintXYLineSeries(CDC* pDC)
{
	//same as Line graph, but without dots at the values
	int barWidth;
	int dataPlotSize;   //used to plot rects of data
	int tickXLocation;
	int seriesSpace;
	int barHeight;  //for scalability
	POSITION pos;
	CGraphSeries* tmpSeries;

	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;


	int lastXLoc, lastYLoc;
	for(int s = 0; s < m_iSeriesSize; s++)
	{
		//determine width of barchart data blocks
		seriesSpace = m_xAxisWidth / m_pGraphSeries->GetCount();
		barWidth = (int)((seriesSpace * .6) / m_iSeriesSize);
		dataPlotSize = m_iSeriesSize * barWidth;

		pos = m_pGraphSeries->GetHeadPosition();

		for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
		{
			tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

			if(tmpSeries->GetData(s) > -1)
			{
				tickXLocation = m_iXApexPoint + ((x * seriesSpace) - (seriesSpace / 2));
				
				barHeight = 0;
				double dataScale = 0.00;
				
				if((m_iYMaxTick - m_iYMinTick) != m_yAxisHeight)
					dataScale = ((m_yAxisHeight * 1.00) / ((m_iYMaxTick - m_iYMinTick) * 1.00)) * m_iYTickSpace;	
				else dataScale = m_iYTickSpace * 15.00;

				int axisHeight = (int)(dataScale * m_iYNumTicks);
				double barPercent = 0.00;
				barPercent = ((tmpSeries->GetData(s) - m_iYMinTick) * 1.00) / m_iYMaxTick;
				barHeight = (int)(barPercent * axisHeight);
				if(((tmpSeries->GetData(s) - m_iYMinTick) > 0) && (barHeight < 1))
					barHeight = (int)dataScale;

				int yDataLocation = m_iYApexPoint + barHeight;
				
				//now have x and y location of center of ellipse
				COLORREF barColor;
				barColor = GetColor(s);
				CBrush brush (barColor);
				CBrush* pOldBrush;
				pOldBrush = pDC->SelectObject(&brush);
				//draw line back to last data member
				if(x > 1)
				{
					CPen* pOldPen;
					CPen linePen (PS_SOLID, 40, barColor);
					pOldPen = pDC->SelectObject(&linePen);
					pDC->MoveTo(lastXLoc, lastYLoc);
					pDC->LineTo(tickXLocation, yDataLocation);
					pDC->SelectObject(pOldPen);
				}
				lastXLoc = tickXLocation;
				lastYLoc = yDataLocation;
				pDC->SelectObject(pOldBrush);
			}
		}
	}
}

//void CGraphView::PrintRadarSeries(CDC* pDC)
//{
//}

void CGraphView::Print3DBarSeries(CDC* pDC)
{
	int barWidth;
	int dataPlotSize;   //used to plot rects of data
	int barL, barT, barR, barB;
	int tickXLocation;
	int seriesSpace;
	int barHeight;
	POSITION pos;
	CGraphSeries* tmpSeries;
	int blue;
	int red;
	int green;

	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;

	//determine width of barchart data blocks
	seriesSpace = (m_xAxisWidth - 100) / m_pGraphSeries->GetCount();
	barWidth = (int)((seriesSpace * .8) / m_iSeriesSize);
	dataPlotSize = m_iSeriesSize * barWidth;

	pos = m_pGraphSeries->GetHeadPosition();

	for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
	{
		tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

		tickXLocation = m_iXApexPoint + ((x * seriesSpace) - (seriesSpace / 2));

		for(int s = 0; s < m_iSeriesSize; s++)
		{
			if(tmpSeries->GetData(s) > -1)
			{
				double dataScale = 0.00;
				dataScale = (m_yAxisHeight * 1.00) / (m_iYMaxTick - m_iYMinTick);
				int dScale;
				dScale = (int)dataScale;
				barHeight = (int)(((tmpSeries->GetData(s) - m_iYMinTick) * 1.00) * dScale);
				if(((tmpSeries->GetData(s) - m_iYMinTick) > 0) && (barHeight < 1))
					barHeight = 1 * dScale;

				barL = tickXLocation - (dataPlotSize / 2) + (s * barWidth);
				if(barHeight > m_yAxisHeight)
					barT = m_iYApexPoint + m_yAxisHeight;
				else
					barT = m_iYApexPoint + barHeight;
				barR = barL + barWidth;
				barB = m_iYApexPoint;
				
				COLORREF barColor;
				barColor = GetColor(s);
				CBrush brush (barColor);
				CPen rectPen (PS_SOLID, 1, barColor);
				CPen* pOldPen;
				pOldPen = pDC->SelectObject(&rectPen);
				CBrush* pOldBrush;
				pOldBrush = pDC->SelectObject(&brush);
				pDC->Rectangle(barL, barT, barR, barB);

				//now, we do the side
				//side is darker than front, so subtract
				//from color to make closer to black
				red = GetRValue(barColor);
				green = GetGValue(barColor);
				blue = GetBValue(barColor);
				int sideRed = red - 35;
				int sideGreen = green - 35;
				int sideBlue = blue - 35;
				if(sideRed < 0) sideRed = 0;
				if(sideGreen < 0) sideGreen = 0;
				if(sideBlue < 0) sideBlue = 0;
				COLORREF sideColor;
				sideColor = RGB(sideRed, sideGreen, sideBlue);
				CBrush sideBrush (sideColor);
				CPen sidePen (PS_SOLID, 1, sideColor);
				pDC->SelectObject(&sideBrush);
				pDC->SelectObject(&sidePen);
				CPoint sidePolyArray[4];
				CPoint sp1(barR, barT);
				CPoint sp2(barR, barB);
				CPoint sp3(barR + m_iDepth, barB + m_iDepth);
				CPoint sp4(barR + m_iDepth, barT + m_iDepth);
				sidePolyArray[0] = sp1;
				sidePolyArray[1] = sp2;
				sidePolyArray[2] = sp3;
				sidePolyArray[3] = sp4;

				pDC->Polygon(sidePolyArray, 4);
				
				//finally, the top
				int topRed = red + 35;
				int topGreen = green + 35;
				int topBlue = blue + 35;
				if(topRed > 255) topRed = 255;
				if(topGreen > 255) topGreen = 255;
				if(topBlue > 255) topBlue = 255;
				COLORREF topColor;
				topColor = RGB(topRed, topGreen, topBlue);
				CBrush topBrush (topColor);
				CPen topPen (PS_SOLID, 1, topColor);
				pDC->SelectObject(&topBrush);
				pDC->SelectObject(&topPen);
				CPoint topPolyArray[4];
				CPoint tp1(barL, barT);
				CPoint tp2(barR, barT);
				CPoint tp3(barR + m_iDepth, barT + m_iDepth);
				CPoint tp4(barL + m_iDepth, barT + m_iDepth);
				topPolyArray[0] = tp1;
				topPolyArray[1] = tp2;
				topPolyArray[2] = tp3;
				topPolyArray[3] = tp4;

				pDC->Polygon(topPolyArray, 4);

				pDC->SelectObject(pOldBrush);
				pDC->SelectObject(pOldPen);
			}
		}
	}
}

void CGraphView::Print3DLineSeries(CDC* pDC)
{
	int tickXLocation;
	int seriesSpace;
	int barHeight;
	POSITION pos;
	CGraphSeries* tmpSeries;
	int thick;
	int blue;
	int red;
	int green;
	CBrush* pOldBrush;
	CPen* pOldPen;

	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;


	thick = m_iDepth / 5;

	int lastXLoc, lastYLoc;
	for(int s = 0; s < m_iSeriesSize; s++)
	{
		//determine width of barchart data blocks
		seriesSpace = (m_xAxisWidth - 100) / m_pGraphSeries->GetCount();

		pos = m_pGraphSeries->GetHeadPosition();
		int yDataLocation;

		for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
		{
			tickXLocation = m_iXApexPoint + ((x * seriesSpace) - (seriesSpace / 2));
			tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

			if(tmpSeries->GetData(s) > -1)
			{
				double dataScale = 0.00;
				dataScale = (m_yAxisHeight * 1.00) / (m_iYMaxTick - m_iYMinTick);
				int dScale;
				dScale = (int)dataScale;
				barHeight = (int)(((tmpSeries->GetData(s) - m_iYMinTick) * 1.00) * dScale);
				if(((tmpSeries->GetData(s) - m_iYMinTick) > 0) && (barHeight < 1))
					barHeight = 1 * dScale;

				yDataLocation = m_iYApexPoint + barHeight;
				//now have x and y location of center of ellipse
				COLORREF barColor;
				barColor = GetColor(s);
				red = GetRValue(barColor);
				green = GetGValue(barColor);
				blue = GetBValue(barColor);
				CBrush brush (barColor);
				pOldBrush = pDC->SelectObject(&brush);
				//draw line back to last data member
				if(x > 1)
				{
					CPen linePen (PS_SOLID, 1, barColor);
					pOldPen = pDC->SelectObject(&linePen);
					//front side of line
					CPoint sidePolyArray[4];
					CPoint sp1(lastXLoc, lastYLoc);
					CPoint sp2(lastXLoc, lastYLoc - thick);
					CPoint sp3(tickXLocation, yDataLocation - thick);
					CPoint sp4(tickXLocation, yDataLocation);
					sidePolyArray[0] = sp1;
					sidePolyArray[1] = sp2;
					sidePolyArray[2] = sp3;
					sidePolyArray[3] = sp4;
					pDC->Polygon(sidePolyArray, 4);

					//top part of line, lighter than front
					int topRed = red + 35;
					int topGreen = green + 35;
					int topBlue = blue + 35;
					if(topRed > 255) topRed = 255;
					if(topGreen > 255) topGreen = 255;
					if(topBlue > 255) topBlue = 255;
					COLORREF topColor;
					topColor = RGB(topRed, topGreen, topBlue);
					
					CPen topPen(PS_SOLID, 1, topColor);
					CBrush topBrush(topColor);
					pDC->SelectObject(&topPen);
					pDC->SelectObject(&topBrush);
					CPoint topPolyArray[4];
					CPoint tp1(lastXLoc, lastYLoc);
					CPoint tp2(lastXLoc + m_iDepth, lastYLoc + m_iDepth);
					CPoint tp3(tickXLocation + m_iDepth, yDataLocation + m_iDepth);
					CPoint tp4(tickXLocation, yDataLocation);
					topPolyArray[0] = tp1;
					topPolyArray[1] = tp2;
					topPolyArray[2] = tp3;
					topPolyArray[3] = tp4;
					pDC->Polygon(topPolyArray, 4);

					pDC->SelectObject(pOldBrush);
					pDC->SelectObject(pOldPen);
				}
				lastXLoc = tickXLocation;
				lastYLoc = yDataLocation;
			}
		}
		if(x > 1)
		{
			//end point of line
			int endRed = red - 35;
			int endGreen = green - 35;
			int endBlue = blue - 35;
			if(endRed < 0) endRed = 0;
			if(endGreen < 0) endGreen = 0;
			if(endBlue < 0) endBlue = 0;
			COLORREF endColor;
			endColor = RGB(endRed, endGreen, endBlue);
			
			CPen endPen(PS_SOLID, 1, endColor);
			CBrush endBrush(endColor);
			pDC->SelectObject(&endPen);
			pDC->SelectObject(&endBrush);
			CPoint endPolyArray[4];
			CPoint ep1(tickXLocation, yDataLocation);
			CPoint ep2(tickXLocation + m_iDepth, yDataLocation + m_iDepth);
			CPoint ep3(tickXLocation + m_iDepth, yDataLocation + m_iDepth - thick);
			CPoint ep4(tickXLocation, yDataLocation + thick);
			endPolyArray[0] = ep1;
			endPolyArray[1] = ep2;
			endPolyArray[2] = ep3;
			endPolyArray[3] = ep4;
			pDC->Polygon(endPolyArray, 4);

			pDC->SelectObject(pOldBrush);
			pDC->SelectObject(pOldPen);
		}
	}
}

void CGraphView::Print3DPieSeries(CDC* pDC)
{
	double dataSum = 0.00;  //for storing cumulative sum
	double labelData = 0.00;
	int lastXLocation, lastYLocation;
	int newXLocation, newYLocation;
	int labelXLocation, labelYLocation;
	double percent = 0.00;
	double labelPercent = 0.00;
	int degrees;
	int labelDegrees;
	double totalSum = 0.00;
	int radius;
	POSITION pos;
	CGraphSeries* tmpSeries;
	int seriesSpace;
	int labelLineXStart, labelLineYStart;
	int labelLineXEnd, labelLineYEnd;
	int maxLabelWidth;
	int maxLabelHeight;
	TEXTMETRIC tm;
	CPen* pOldPen;
	CBrush* pOldBrush;

	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;

		
	CPen tmpPen(PS_SOLID, 1, BLACK);
	CBrush tmpBrush(WHITE);
	pOldPen = pDC->SelectObject(&tmpPen);
	pOldBrush = pDC->SelectObject(&tmpBrush);



	//deltaX and deltaY will be based on distance from x and y
	//axis for the new endpoint of the pie.  These values can 
	//then be used to find the true distance between starting 
	//line and ending line of pie boundary.
	double deltaX, deltaY;
	double degreeRadians, degreeRadians2;
	double labelDeltaX, labelDeltaY;
	double labelDegreeRadians, labelDegreeRadians2;

	lastXLocation = 0;
	lastYLocation = 0;

	pDC->GetTextMetrics(&tm);
	maxLabelWidth = tm.tmMaxCharWidth + 10;
	maxLabelHeight = tm.tmHeight + 6;
	
	//pie labels will be stored in a list and drawn after entire pie
	//is completed.
	CObList *pieLabels;
	CGraphPieLabel *pieLabel;

	//determine width of pie display area
	if(m_xAxisWidth > m_yAxisHeight)
		seriesSpace = m_yAxisHeight / m_pGraphSeries->GetCount();
	else
		seriesSpace = m_xAxisWidth / m_pGraphSeries->GetCount();
	seriesSpace -= (3 * maxLabelWidth);  //allows text like 25%  (3 chars)

	//to plot a pie plus labels inside of series space, use the following :
	//(3 * radius) + (2 * label width) = series space 
	//so, 3*radius = series space - (2 * label width)
	// 1 radius = (series space - (2 * label width)) / 3
	radius = seriesSpace / 3;  //pie needs 2 radius, + 1 extra for line to labels = 3 for my divisor
	int m_iDepth = (int)(radius * m_lfDepthRatio);	//for shadow pie

	int centerYPie = m_iPGraphT - (m_yAxisHeight / 2) - 500 - m_iDepth;

	pos = m_pGraphSeries->GetHeadPosition();
	for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
	{
		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);
		pieLabels = new CObList();

		tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);
		totalSum = 0;
		for(int s = 0; s < m_iSeriesSize; s++)
			totalSum += tmpSeries->GetData(s);
		int pieLeft, pieRight;
		if(m_pGraphSeries->GetCount() == 1)
		{
			pieLeft = m_iXApexPoint + (m_xAxisWidth / 2) - radius;
		}
		else
		{
			pieLeft = m_iXApexPoint + 15 + ((x * 2 - 1) * ((m_xAxisWidth / m_pGraphSeries->GetCount()) / 2)) - radius;
		}
		pieRight = pieLeft + (2 * radius);
		CRect pieRect (pieLeft, 
				centerYPie + radius,
				pieRight, 
				centerYPie - radius);
		CRect shadowRect (pieLeft + m_iDepth,
				centerYPie + radius - m_iDepth,
				pieRight + m_iDepth,
				centerYPie - radius - m_iDepth);
		int centerXPie = pieLeft + radius;

		//plot series label
		pDC->TextOut(centerXPie - ((tmpSeries->GetLabel().GetLength() / 2) * ((m_iXTickFontSize / 2) * 20)),
					centerYPie - radius - maxLabelHeight - 600 - m_iDepth, tmpSeries->GetLabel());

		int centerShadowXPie;
		int centerShadowYPie;

		//draw shadow pie first
		centerShadowYPie = centerYPie - m_iDepth;
		centerShadowXPie = centerXPie + m_iDepth;
		lastXLocation = centerShadowXPie - radius;
		lastYLocation = centerShadowYPie;

		int lastTopX = centerXPie - radius;
		int lastTopY = centerYPie;
		int newTopX, newTopY;
		dataSum = 0;
		int lastQuad = 0;
		CPoint lastSidePolyArray[4];
		COLORREF lastColor;
		CPoint spa1;
		CPoint spa2;
		CPoint spa3;
		CPoint spa4;
		for(s = 0; s < m_iSeriesSize; s++)
		{
			if(tmpSeries->GetData(s) > 0)
			{
				int seriesDataValue;
				seriesDataValue = tmpSeries->GetData(s);
				dataSum += seriesDataValue;
				percent = (dataSum / totalSum) * 100;
				degrees = (int)((360 * percent) / 100);

				//determine destination quadrant...
					//and set newXLocation and newYLocation values...
					//degrees / 90 will never exceed 4.
					//this can tell us the quadrant of destination
				int quadrant = degrees / 90;  //truncates decimal

				//using the law of sines to determine the deltas :
				//deltaX = radius * sin(90 - degrees)
				//deltaY = radius * sin(degrees)
				//we convert degrees into radians so sin() function works right
				//note :  in quad 1 and 3, we reverse the angle used to compute
				//			the deltas, since the triangle plots reversed.
				switch(quadrant)
				{
					case 0 : //this is the base quadrant, so no manipulation needed
							 degreeRadians = degrees * (3.14159 / 180);
							 degreeRadians2 = (90 - degrees) * (3.14159 / 180);
							 deltaX = radius * sin(degreeRadians2);
							 deltaY = radius * sin(degreeRadians);
							 newXLocation = (int)(centerShadowXPie - deltaX);
							 newYLocation = (int)(centerShadowYPie - deltaY);
							 newTopX = (int)(centerXPie - deltaX);
							 newTopY = (int)(centerYPie - deltaY);
							 break;
					case 1 : //bottom right quadrant, subtract 90 from angle
							 degreeRadians = (degrees - 90) * (3.14159 / 180);
							 degreeRadians2 = (90 - (degrees - 90)) * (3.14159 / 180);
							 deltaX = radius * sin(degreeRadians);
							 deltaY = radius * sin(degreeRadians2);
							 newXLocation = (int)(centerShadowXPie + deltaX);
							 newYLocation = (int)(centerShadowYPie - deltaY);
							 newTopX = (int)(centerXPie + deltaX);
							 newTopY = (int)(centerYPie - deltaY);
							 break;
					case 2 : //top right quadrant, subtract 180 from angle
							 degreeRadians = (degrees - 180) * (3.14159 / 180);
							 degreeRadians2 = (90 - (degrees - 180)) * (3.14159 / 180);
							 deltaX = radius * sin(degreeRadians2);
							 deltaY = radius * sin(degreeRadians);
							 newXLocation = (int)(centerShadowXPie + deltaX);
							 newYLocation = (int)(centerShadowYPie + deltaY);
							 newTopX = (int)(centerXPie + deltaX);
							 newTopY = (int)(centerYPie + deltaY);
							 break;
					case 3 : //upper left quadrant, subtract 270 from angle
							 degreeRadians = (degrees - 270) * (3.14159 / 180);
							 degreeRadians2 = (90 - (degrees - 270)) * (3.14159 / 180);
							 deltaX = radius * sin(degreeRadians);
							 deltaY = radius * sin(degreeRadians2);
							 newXLocation = (int)(centerShadowXPie - deltaX);
							 newYLocation = (int)(centerShadowYPie + deltaY);
							 newTopX = (int)(centerXPie - deltaX);
							 newTopY = (int)(centerYPie + deltaY);
							 break;
					case 4 : //straight line to left of center
							 deltaX = radius;
							 deltaY = 1;
							 newXLocation = (int)(centerShadowXPie - deltaX);
							 newYLocation = (int)(centerShadowYPie + deltaY);
							 newTopX = (int)(centerXPie - deltaX);
							 newTopY = (int)(centerYPie + deltaY);
							 break;
				}
				
				if(s == 0)
				{
					lastYLocation += 1;
					lastTopY += 1;
				}

				COLORREF barColor;
				barColor = GetColor(s);
				int red, green, blue;
				red = GetRValue(barColor) - 35;
				green = GetGValue(barColor) - 35;
				blue = GetBValue(barColor) - 35;
				if(red < 0) red = 0;
				if(green < 0) green = 0;
				if(blue < 0) blue = 0;
				CPoint sp1 (lastXLocation, lastYLocation);
				CPoint sp2 (newXLocation, newYLocation);
				COLORREF shadowColor(RGB(red, green, blue));
				CPen shadowPen (PS_SOLID, 1, shadowColor);
				CBrush shadowBrush(shadowColor);
				pDC->SelectObject(&shadowPen);
				pDC->SelectObject(&shadowBrush);
				if((quadrant < 2) || (lastQuad < 2))
				{
					CPoint sidePolyArray[4];
					spa1.x = lastXLocation;
					spa1.y = lastYLocation;
					spa2.x = newXLocation;
					spa2.y = newYLocation;
					spa3.x = newTopX;
					spa3.y = newTopY;
					spa4.x = lastTopX;
					spa4.y = lastTopY;
					sidePolyArray[0] = spa1;
					sidePolyArray[1] = spa2;
					sidePolyArray[2] = spa3;
					sidePolyArray[3] = spa4;
					pDC->Polygon(sidePolyArray, 4);
					pDC->Pie(shadowRect, sp1, sp2);
				}
				else
				{
					CPoint sidePolyArray[3];
					spa1.x = newXLocation;
					spa1.y = newYLocation;
					spa2.x = newTopX;
					spa2.y = newTopY;
					spa3.x = lastTopX;
					spa3.y = lastTopY;
					sidePolyArray[0] = spa1;
					sidePolyArray[1] = spa2;
					sidePolyArray[2] = spa3;
					CPen oldShadowPen (PS_SOLID, 1, lastColor);
					pDC->SelectObject(&oldShadowPen);
					CBrush oldShadowBrush(lastColor);
					pDC->SelectObject(&oldShadowBrush);
					pDC->Pie(shadowRect, sp1, sp2);
					pDC->Polygon(sidePolyArray, 3);
					pDC->SelectObject(&shadowPen);
					pDC->SelectObject(&shadowBrush);
				}

				lastXLocation = newXLocation;
				lastYLocation = newYLocation;
				lastTopX = newTopX;
				lastTopY = newTopY;
				if((quadrant > 1) && (lastQuad < 2))
				{
					lastSidePolyArray[0] = spa1;
					lastSidePolyArray[1] = spa2;
					lastSidePolyArray[2] = spa3;
					lastSidePolyArray[3] = spa4;
					lastColor = shadowColor;
				}
				lastQuad = quadrant;
				pDC->SelectObject(pOldBrush);
				pDC->SelectObject(pOldPen);
			}
		}

		//draw normal pie
		lastXLocation = pieLeft;
		lastYLocation = centerYPie;

		dataSum = 0;
		for(s = 0; s < m_iSeriesSize; s++)
		{
			if(tmpSeries->GetData(s) > 0)
			{
				int seriesDataValue;
				seriesDataValue = tmpSeries->GetData(s);
				labelData = seriesDataValue / 2;
				dataSum += seriesDataValue;
				percent = (dataSum / totalSum) * 100;
				labelPercent = ((dataSum - labelData) / totalSum) * 100;
				degrees = (int)((360 * percent) / 100);
				labelDegrees = (int)((360 * labelPercent) / 100);

				//determine destination quadrant...
					//and set newXLocation and newYLocation values...
					//degress / 90 will never exceed 4.
					//this can tell us the quadrant of destination
				int quadrant = degrees / 90;  //truncates decimal
				int labelQuadrant = labelDegrees / 90;

				//using the law of sines to determine the deltas :
				//deltaX = radius * sin(90 - degrees)
				//deltaY = radius * sin(degrees)
				//we convert degrees into radians so sin() function works right
				//note :  in quad 1 and 3, we reverse the angle used to compute
				//			the deltas, since the triangle plots reversed.
				switch(quadrant)
				{
					case 0 : //this is the base quadrant, so no manipulation needed
							 degreeRadians = degrees * (3.14159 / 180);
							 degreeRadians2 = (90 - degrees) * (3.14159 / 180);
							 deltaX = radius * sin(degreeRadians2);
							 deltaY = radius * sin(degreeRadians);
							 newXLocation = (int)(centerXPie - deltaX);
							 newYLocation = (int)(centerYPie - deltaY);
							 break;
					case 1 : //bottom right quadrant, subtract 90 from angle
							 degreeRadians = (degrees - 90) * (3.14159 / 180);
							 degreeRadians2 = (90 - (degrees - 90)) * (3.14159 / 180);
							 deltaX = radius * sin(degreeRadians);
							 deltaY = radius * sin(degreeRadians2);
							 newXLocation = (int)(centerXPie + deltaX);
							 newYLocation = (int)(centerYPie - deltaY);
							 break;
					case 2 : //top right quadrant, subtract 180 from angle
							 degreeRadians = (degrees - 180) * (3.14159 / 180);
							 degreeRadians2 = (90 - (degrees - 180)) * (3.14159 / 180);
							 deltaX = radius * sin(degreeRadians2);
							 deltaY = radius * sin(degreeRadians);
							 newXLocation = (int)(centerXPie + deltaX);
							 newYLocation = (int)(centerYPie + deltaY);
							 break;
					case 3 : //upper left quadrant, subtract 270 from angle
							 degreeRadians = (degrees - 270) * (3.14159 / 180);
							 degreeRadians2 = (90 - (degrees - 270)) * (3.14159 / 180);
							 deltaX = radius * sin(degreeRadians);
							 deltaY = radius * sin(degreeRadians2);
							 newXLocation = (int)(centerXPie - deltaX);
							 newYLocation = (int)(centerYPie + deltaY);
							 break;
					case 4 : //straight line to left of center
							 deltaX = radius;
							 deltaY = 1;
							 newXLocation = (int)(centerXPie - deltaX);
							 newYLocation = (int)(centerYPie + deltaY);
							 break;
				}
				
				switch(labelQuadrant)
				{
					//after getting X & Y location for label, we take
					//1/2 the delta between x y locations and center pie
					case 0 : 
							 labelDegreeRadians = labelDegrees * (3.14159 / 180);
							 labelDegreeRadians2 = (90 - labelDegrees) * (3.14159 / 180);
							 labelDeltaX = radius * sin(labelDegreeRadians2);
							 labelDeltaY = radius * sin(labelDegreeRadians);
							 labelXLocation = (int)(centerXPie - labelDeltaX);
							 labelYLocation = (int)(centerYPie - labelDeltaY);
							 labelLineXStart = labelXLocation + ((centerXPie - labelXLocation) / 2);
							 labelLineYStart = labelYLocation - ((labelYLocation - centerYPie) / 2);
							 labelLineXEnd = labelXLocation - (radius / 2);
							 labelLineYEnd = labelYLocation - (radius / 2);
							 break;
					case 1 : 
							 labelDegreeRadians = (labelDegrees - 90) * (3.14159 / 180);
							 labelDegreeRadians2 = (90 - (labelDegrees - 90)) * (3.14159 / 180);
							 labelDeltaX = radius * sin(labelDegreeRadians);
							 labelDeltaY = radius * sin(labelDegreeRadians2);
							 labelXLocation = (int)(centerXPie + labelDeltaX);
							 labelYLocation = (int)(centerYPie - labelDeltaY);
							 labelLineXStart = labelXLocation - ((labelXLocation - centerXPie) / 2);
							 labelLineYStart = labelYLocation - ((labelYLocation - centerYPie) / 2);
							 labelLineXEnd = labelXLocation + (radius / 2);
							 labelLineYEnd = labelYLocation - (radius / 2);
							 break;
					case 2 : 
							 labelDegreeRadians = (labelDegrees - 180) * (3.14159 / 180);
							 labelDegreeRadians2 = (90 - (labelDegrees - 180)) * (3.14159 / 180);
							 labelDeltaX = radius * sin(labelDegreeRadians2);
							 labelDeltaY = radius * sin(labelDegreeRadians);
							 labelXLocation = (int)(centerXPie + labelDeltaX);
							 labelYLocation = (int)(centerYPie + labelDeltaY);
							 labelLineXStart = labelXLocation - ((labelXLocation - centerXPie) / 2);
							 labelLineYStart = labelYLocation - ((labelYLocation - centerYPie) / 2);
							 labelLineXEnd = labelXLocation + (radius / 2);
							 labelLineYEnd = labelYLocation + (radius / 2);
							 break;
					case 3 : 
							 labelDegreeRadians = (labelDegrees - 270) * (3.14159 / 180);
							 labelDegreeRadians2 = (90 - (labelDegrees - 270)) * (3.14159 / 180);
							 labelDeltaX = radius * sin(labelDegreeRadians);
							 labelDeltaY = radius * sin(labelDegreeRadians2);
							 labelXLocation = (int)(centerXPie - labelDeltaX);
							 labelYLocation = (int)(centerYPie + labelDeltaY);
							 labelLineXStart = labelXLocation + ((centerXPie - labelXLocation) / 2);
							 labelLineYStart = labelYLocation - ((labelYLocation - centerYPie) / 2);
							 labelLineXEnd = labelXLocation - (radius / 2);
							 labelLineYEnd = labelYLocation + (radius / 2);
							 break;
//there should never be a half point ending on 4, so leave it out
				}

				pieLabel = new CGraphPieLabel();

				pieLabel->lineXStart = labelLineXStart;
				pieLabel->lineYStart = labelLineYStart;
				pieLabel->lineXEnd = labelLineXEnd;
				pieLabel->lineYEnd = labelLineYEnd;
				switch(labelQuadrant)
				{
					case 0 : //label to left of line
							 pieLabel->topLeftX = labelLineXEnd - maxLabelWidth;
							 pieLabel->topLeftY = labelLineYEnd;
							 break;
					case 1 : //label to right of line
							 pieLabel->topLeftX = labelLineXEnd + 50;
							 pieLabel->topLeftY = labelLineYEnd;
							 break;
					case 2 : //label to right of line
							 pieLabel->topLeftX = labelLineXEnd + 50;
							 pieLabel->topLeftY = labelLineYEnd + maxLabelHeight;
							 break;
					case 3 : //label to left of line
							 pieLabel->topLeftX = labelLineXEnd - maxLabelWidth;
							 pieLabel->topLeftY = labelLineYEnd + maxLabelHeight;
							 break;
				}
				pieLabel->labelQuadrant = labelQuadrant;
				int roundPercent;
				roundPercent = (int)((seriesDataValue * 100) / totalSum);
				pieLabel->pieLabel.Format("%d%%", roundPercent);
				pieLabels->AddTail(pieLabel);

				if(s == 0)
					lastYLocation += 1;

				COLORREF barColor;
				barColor = GetColor(s);
				CPoint p1 (lastXLocation, lastYLocation);
				CPoint p2 (newXLocation, newYLocation);
				CBrush brush (barColor);
				CPen piePen (PS_SOLID, 1, barColor);
				pDC->SelectObject(&piePen);
				pDC->SelectObject(&brush);
				pDC->Pie(pieRect, p1, p2); 

				lastXLocation = newXLocation;
				lastYLocation = newYLocation;
			}
			pDC->SelectObject(pOldBrush);
			pDC->SelectObject(pOldPen);
		}

		//draw lines and labels for pies slices
		POSITION labelPos;

		CBrush lineBrush (BLACK);
		CPen linePen (PS_SOLID, 1, BLACK);
		pDC->SelectObject(&lineBrush);
		pDC->SelectObject(&linePen);
		POSITION mainLinePos, checkLinePos;
		mainLinePos = pieLabels->GetHeadPosition();
		int numLinesDrawn = 0;
		CGraphPieLabel* currentLabel;
		CGraphPieLabel* tmpLabel;
		while(mainLinePos != NULL)
		{
			currentLabel = (CGraphPieLabel*)pieLabels->GetNext(mainLinePos);
			int r = 0;
			checkLinePos = pieLabels->GetHeadPosition();
			while(r < numLinesDrawn)
			{
				//check if any overlap in label areas
				tmpLabel = (CGraphPieLabel*)pieLabels->GetAt(checkLinePos);
				if((currentLabel->topLeftX > tmpLabel->topLeftX) &&
					(currentLabel->topLeftX < (tmpLabel->topLeftX - maxLabelWidth)) &&
					(currentLabel->topLeftY > tmpLabel->topLeftY) &&
					(currentLabel->topLeftY < (tmpLabel->topLeftY - maxLabelHeight)))
				{
					//OVERLAP !!!
					//move current label top left position up or down
					//depending on its quadrant
					if(currentLabel->labelQuadrant < 2)
					{
						//move label down to tmplabel topleft + height
						currentLabel->topLeftY = tmpLabel->topLeftY - maxLabelHeight;
						currentLabel->lineYEnd = tmpLabel->lineYEnd - maxLabelHeight;
					}
					else
					{
						//move label up to tmpLabel topleft - height
						currentLabel->topLeftY = tmpLabel->topLeftY + maxLabelHeight;
						currentLabel->lineYEnd = tmpLabel->lineYEnd + maxLabelHeight;
					}
					//reset r value to 0 so it starts over, just in
					//case we moved the label and it overlaps another
					r = 0;
					checkLinePos = pieLabels->GetHeadPosition();
				}
				else
				{
					r++;
					pieLabels->GetNext(checkLinePos);
				}

			}
			//draw the line and label
			pDC->MoveTo(currentLabel->lineXStart, currentLabel->lineYStart);
			pDC->LineTo(currentLabel->lineXEnd, currentLabel->lineYEnd);

			//write the label
			pDC->TextOut(currentLabel->topLeftX, currentLabel->topLeftY,
					currentLabel->pieLabel);
			numLinesDrawn++;
		}

		//now done, remove everything inside the label list
		labelPos = pieLabels->GetHeadPosition();
		while(labelPos != NULL)
		{
			pieLabel = (CGraphPieLabel*)pieLabels->GetNext(labelPos);
			delete pieLabel;
		}
		delete pieLabels;
	}
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

void CGraphView::Print3DStackedBarSeries(CDC* pDC)
{
	int barWidth;
	int barL, barT, barR, barB;
	int tickXLocation;
	int seriesSpace;
	int barHeight;
	POSITION pos;
	CGraphSeries* tmpSeries;
	int blue;
	int red;
	int green;
	int iSerQty=m_pGraphSeries->GetCount();
	if(iSerQty<1)return;

	//determine width of barchart data blocks
	seriesSpace = m_xAxisWidth  / m_pGraphSeries->GetCount();
	barWidth = (int)(seriesSpace * .8);

	pos = m_pGraphSeries->GetHeadPosition();

	double dataScale = 0.00;
	dataScale = (m_yAxisHeight * 1.00) / (m_iYMaxTick - m_iYMinTick);
	for(int x = 1; x <= m_pGraphSeries->GetCount(); x++)
	{
		tmpSeries = (CGraphSeries*)m_pGraphSeries->GetNext(pos);

		tickXLocation = m_iXApexPoint + ((x * seriesSpace) - (seriesSpace / 2));

		barT = m_iYApexPoint;	//this is a running total;
							//it starts at m_iYApexPoint so barB can
							//start there, then moves up by barHeight
		for(int s = 0; s < m_iSeriesSize; s++)
		{
			if(tmpSeries->GetData(s) > -1)
			{
				barHeight = (int)(((tmpSeries->GetData(s) - m_iYMinTick) * 1.00) * dataScale);
				if(((tmpSeries->GetData(s) - m_iYMinTick) > 0) && (barHeight < 1))
					barHeight = (int)dataScale;

				barB = barT;
				barL = tickXLocation - (barWidth / 2);
				if(barHeight > m_yAxisHeight)
					barT = barB + m_yAxisHeight;
				else
					barT = barB + barHeight;
				barR = barL + barWidth;

				COLORREF barColor;
				barColor = GetColor(s);
				CBrush brush (barColor);
				CPen rectPen (PS_SOLID, 1, barColor);
				CPen* pOldPen;
				pOldPen = pDC->SelectObject(&rectPen);
				CBrush* pOldBrush;
				pOldBrush = pDC->SelectObject(&brush);
				pDC->Rectangle(barL, barT, barR, barB);

				//now, we do the side
				//side is darker than front, so subtract
				//from color to make closer to black
				red = GetRValue(barColor);
				green = GetGValue(barColor);
				blue = GetBValue(barColor);
				int sideRed = red - 35;
				int sideGreen = green - 35;
				int sideBlue = blue - 35;
				if(sideRed < 0) sideRed = 0;
				if(sideGreen < 0) sideGreen = 0;
				if(sideBlue < 0) sideBlue = 0;
				COLORREF sideColor;
				sideColor = RGB(sideRed, sideGreen, sideBlue);
				CBrush sideBrush (sideColor);
				CPen sidePen (PS_SOLID, 1, sideColor);
				pDC->SelectObject(&sideBrush);
				pDC->SelectObject(&sidePen);
				CPoint sidePolyArray[4];
				CPoint sp1(barR, barT);
				CPoint sp2(barR, barB);
				CPoint sp3(barR + m_iDepth, barB + m_iDepth);
				CPoint sp4(barR + m_iDepth, barT + m_iDepth);
				sidePolyArray[0] = sp1;
				sidePolyArray[1] = sp2;
				sidePolyArray[2] = sp3;
				sidePolyArray[3] = sp4;

				pDC->Polygon(sidePolyArray, 4);
				
				//finally, the top
				int topRed = red + 35;
				int topGreen = green + 35;
				int topBlue = blue + 35;
				if(topRed > 255) topRed = 255;
				if(topGreen > 255) topGreen = 255;
				if(topBlue > 255) topBlue = 255;
				COLORREF topColor;
				topColor = RGB(topRed, topGreen, topBlue);
				CBrush topBrush (topColor);
				CPen topPen (PS_SOLID, 1, topColor);
				pDC->SelectObject(&topBrush);
				pDC->SelectObject(&topPen);
				CPoint topPolyArray[4];
				CPoint tp1(barL, barT);
				CPoint tp2(barR, barT);
				CPoint tp3(barR + m_iDepth, barT + m_iDepth);
				CPoint tp4(barL + m_iDepth, barT + m_iDepth);
				topPolyArray[0] = tp1;
				topPolyArray[1] = tp2;
				topPolyArray[2] = tp3;
				topPolyArray[3] = tp4;

				pDC->Polygon(topPolyArray, 4);

				pDC->SelectObject(pOldBrush);
				pDC->SelectObject(pOldPen);
			}
		}
	}
}

void CGraphView::RemoveSeries(CString label)
{
	POSITION pos;
	CGraphSeries* pSeries;
	pos = m_pGraphSeries->GetHeadPosition();
	while(pos != NULL)
	{
		pSeries = (CGraphSeries*)m_pGraphSeries->GetAt(pos);
		if(pSeries->GetLabel().Compare(label) == 0)
		{
			m_pGraphSeries->RemoveAt(pos);
			delete pSeries;
			break;
		}
		m_pGraphSeries->GetNext(pos);
	}
}

void CGraphView::RemoveAllSeries()
{
	POSITION pos,posLast;
	CGraphSeries* pSeries;
	pos = m_pGraphSeries->GetHeadPosition();
	while(pos != NULL)
	{
		posLast=pos;
		pSeries = (CGraphSeries*) m_pGraphSeries->GetNext( pos );
		m_pGraphSeries->RemoveAt(posLast);
		delete pSeries;
	}

	m_pGraphSeries->RemoveAll();
	m_iSeriesSize=0;
}

void CGraphView::RemoveAllData()
{
	RemoveAllSeries();
}

void CGraphView::Set3DDepthRatio(double ratio)
{
	m_lfDepthRatio = ratio;
}

void CGraphView::SetGraphQuadType(int quads)
{
	if(m_iGraphType == BAR_GRAPH)
	{
		if((quads < 1) || (quads > 4))
			m_iGraphQuadType = 1;
		else
		{
			m_iGraphQuadType = quads;
			m_bQuadSetManually = TRUE;
		}
	}
}

void CGraphView::Set3DLineBase(int x, int y)
{
	m_iLine3DXBase = x;
	m_iLine3DYBase = y;
}



void CGraphView::DrawMarker(CDC *pDC,
						enumMarkerType eMarkerType,
						int iHorPos, 
						int iVerPos, 
						int iSize)
{
	if(eMarkerType==MT_NONE)
	{
		return;
	}

	static int n1,n2,n3;
	if(eMarkerType==MT_TRI)
	{
		n1=iSize/1.732;
		n2=iSize/2;
		n3=iSize/2/1.732;
		m_point[ 0 ].x = iHorPos;
		m_point[ 0 ].y = iVerPos-n1;
		m_point[ 1 ].x = iHorPos-n2;
		m_point[ 1 ].y = iVerPos+n3;
		m_point[ 2 ].x = iHorPos+n2;
		m_point[ 2 ].y = iVerPos+n3;
		pDC->Polygon( m_point, 3 );
	}

	else if(eMarkerType==MT_BOX)
	{
		n1=iSize/2;
		m_point[ 0 ].x = iHorPos-n1;
		m_point[ 0 ].y = iVerPos-n1;
		m_point[ 1 ].x = iHorPos+n1;
		m_point[ 1 ].y = iVerPos-n1;
		m_point[ 2 ].x = iHorPos+n1;
		m_point[ 2 ].y = iVerPos+n1;
		m_point[ 3 ].x = iHorPos-n1;
		m_point[ 3 ].y = iVerPos+n1;
		pDC->Polygon( m_point, 4 );
	}

	else if(eMarkerType==MT_SPH)
	{
		n1=iSize/2;
		pDC->Ellipse (iHorPos-n1,iVerPos-n1,iHorPos+n1,iVerPos+n1);
	}

	else if(eMarkerType==MT_DIA)
	{
		n1=iSize/2*1.414;
		m_point[ 0 ].x = iHorPos;
		m_point[ 0 ].y = iVerPos-n1;
		m_point[ 1 ].x = iHorPos+n1;
		m_point[ 1 ].y = iVerPos;
		m_point[ 2 ].x = iHorPos;
		m_point[ 2 ].y = iVerPos+n1;
		m_point[ 3 ].x = iHorPos-n1;
		m_point[ 3 ].y = iVerPos;
		pDC->Polygon( m_point, 4 );
	}
}


// CGraphView message handlers

void CGraphView::OnContextMenu(CWnd* pWnd, CPoint point)
{
}


void CGraphView::OnDraw(CDC* pDC)
{
	DrawGraph (pDC);
}

void CGraphView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	OnPrepareDC(&dc);
	CMemDC memDC(&dc,this);	
	OnDraw(&memDC);
}

BOOL CGraphView::OnEraseBkgnd(CDC* pDC)
{
	//return CView::OnEraseBkgnd (pDC);
	return true;
}

void CGraphView::SetChartProperty()
{
	CColorDlg dlg;
	dlg.SetColorSerial (2);
	dlg.SetRange (-0.4,m_iSeriesSize-1);
	
	enumMarkerType eMarkerType;
	int iType=0;
    m_graphProperty.RemoveAll();

	for(int i=0;i<m_iSeriesSize;i++)
	{
		iType=i%4;
		if(iType==0)
		{
			eMarkerType=MT_TRI;
		}
		else if(iType==1)
		{
			eMarkerType=MT_BOX;
		}
		else if(iType==2)
		{
			eMarkerType=MT_SPH;
		}
		else if(iType==3)
		{
			eMarkerType=MT_DIA;
		}

		m_graphProperty.Set(i,
							"×é"+vtos(i),
							dlg.GetColor (i),
							3,
							2,
							eMarkerType);
	}
}

void CGraphView::SetChart()
{
	return ;
}

void CGraphView::SetLegend()
{
	return;
}

void CGraphView::SetLegend(int iGroup,CString sLabel)
{
	// Check if the label is sum or total:
	int n=sLabel.Find ("=");
	if(n!=-1)
	{
		sLabel=sLabel.Left (n);
	}

	// Set the label:
	CGraphGroupPropertySet *p=(CGraphGroupPropertySet *)m_graphProperty.Get (iGroup);
	if(!p)return;
	strcpy(p->sLegendLabel,(LPCTSTR) sLabel);

	if(m_iGraphType != SCATTER_GRAPH)	//scatter graphs don't need legends
	{
		if(sLabel!="")
		{
			m_bGraphHasLegend = TRUE;
			if(m_iLegendMaxText < sLabel.GetLength())
			{
				m_iLegendMaxText = sLabel.GetLength();
			}
		}
	}
}

void CGraphView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	SetChart();
	SetChartProperty();	
	SetLegend();
}

void CGraphView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CView::OnRButtonDown(nFlags, point);

	CRect rect;
	GetWindowRect (&rect);
	point+=rect.TopLeft ();
	CMenu *pMenu=m_menuManager.GetPopupMenu();
	if(!pMenu)return;

	m_menuManager.ShowPopupMenu(pMenu,point,this);

}

void CGraphView::OnSetchartproperty()
{
	CDlgChartProperty dlg;
    CGraphGroupPropertySet *p=NULL;

	for(int i=0;i<m_graphProperty.GetLegendLength ();i++)
	{
		p=m_graphProperty.Get(i);
		dlg.AddGroupProperty (p);
	}
	dlg.SetChartStyle (m_iGraphType);
	dlg.SetPieDrawLabel(m_bPieDrawLabels);

	if(dlg.DoModal() ==IDCANCEL)return;

	for(int i=0;i<m_graphProperty.GetLegendLength ();i++)
	{
		p=(CGraphGroupPropertySet *)dlg.m_arraySerProperty .GetAt (i);
		m_graphProperty.Set (i,p);
	}

	m_iGraphType=dlg.GetChartStyle ();
	m_bPieDrawLabels=dlg.GetPieDrawLabel();

    SetChart();
    Invalidate();

}
