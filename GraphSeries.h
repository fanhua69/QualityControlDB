//GraphSeries.h - Version 3.0 (Brian Convery, May, 2001)

#if !defined(AFX_GRAPHSERIES_H__A059628E_F6C8_4DA0_9E2F_820131D257E7__INCLUDED_)
#define AFX_GRAPHSERIES_H__A059628E_F6C8_4DA0_9E2F_820131D257E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphSeries.h : header file
//

class CGraphDataSet:public CObject
{
public:
	double  xPosition;
	double  yValue;

	CGraphDataSet()
	{
		xPosition=0.0;
		yValue=0.0;
	};
};

/////////////////////////////////////////////////////////////////////////////
// CGraphSeries window

class CGraphSeries : public CObject
{
// Construction
public:
	CGraphSeries();

// Attributes
public:


private:
	CString seriesLabel;
	CObList *dataValues;	//list of CGraphDataSet objects

// Operations
public:

	void SetLabel(CString label);
	void SetData(double xValue, double yValue);
	CString GetLabel();
	double GetData(double xValue);
	int GetDataCount();
	CGraphDataSet * GetDataValue(POSITION &pos);	//for scatter graphs only
	POSITION GetHeadPosition();


// Implementation
public:
	virtual ~CGraphSeries();

	// Generated message map functions
protected:

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHSERIES_H__A059628E_F6C8_4DA0_9E2F_820131D257E7__INCLUDED_)
