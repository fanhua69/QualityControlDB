//GraphSeries.cpp - Version 3.0 (Brian Convery, May, 2001)

#include "stdafx.h"
#include "GraphSeries.h"
#include "math.h"

/////////////////////////////////////////////////////////////////////////////
// CGraphSeries

CGraphSeries::CGraphSeries()
{
	dataValues = new CObList();
}

CGraphSeries::~CGraphSeries()
{
	POSITION pos,posLast;
	CGraphDataSet *dataSet;
	pos = dataValues->GetHeadPosition();
	while(pos != NULL)
	{
		posLast=pos;
		dataSet = (CGraphDataSet*)dataValues->GetNext (pos);
		dataValues->RemoveAt(posLast);
		delete dataSet;
	}
	delete dataValues;
}

/////////////////////////////////////////////////////////////////////////////
// CGraphSeries message handlers

void CGraphSeries::SetLabel(CString label)
{
	seriesLabel = label;
}

void CGraphSeries::SetData(double xValue, double yValue)
{
	CGraphDataSet *dataSet = new CGraphDataSet();
	dataSet->xPosition = xValue;
	dataSet->yValue = yValue;
	dataValues->AddTail(dataSet);
}

CString CGraphSeries::GetLabel()
{
	return seriesLabel;
}

double CGraphSeries::GetData(double xValue)
{
	POSITION pos;
	pos = dataValues->GetHeadPosition();
	int retVal = 0;
	while(pos != NULL)
	{
		CGraphDataSet *dataSet;
		dataSet = (CGraphDataSet*)dataValues->GetAt(pos);
		if(fabs(dataSet->xPosition - xValue)<0.0000001)
		{
			retVal = dataSet->yValue ;
			return retVal;
		}
		dataValues->GetNext(pos);
	}
	return 0;
}

int CGraphSeries::GetDataCount()
{
	return dataValues->GetCount();
}

POSITION CGraphSeries::GetHeadPosition()
{
	return dataValues->GetHeadPosition();
}

CGraphDataSet *  CGraphSeries::GetDataValue(POSITION &pos)
{
	CGraphDataSet *retVal= (CGraphDataSet*)dataValues->GetNext(pos);
	return retVal;
}
