//GraphLegend.cpp - Version 3.0 (Brian Convery, May, 2001)

#include "stdafx.h"
#include "GraphGroupProperty.h"

/////////////////////////////////////////////////////////////////////////////
// CGraphGroupProperty

CGraphGroupProperty::CGraphGroupProperty()
{
}

CGraphGroupProperty::~CGraphGroupProperty()
{
	RemoveAll();
}

void CGraphGroupProperty::Set(	int					iDataGroup,
								CGraphGroupPropertySet *pSet)
{
	Set(iDataGroup,
		pSet->sLegendLabel ,
		pSet->groupColor ,
		pSet->iMarkerSize ,
		pSet->iLineWidth ,
		pSet->eMarkerType);
}

void CGraphGroupProperty::Set(	int					iDataGroup,
								CString				sLabel,
								COLORREF			color,
								int					iMarkerSize,
								int					iLineWidth,
								enumMarkerType		eMarkerType)
{
	CGraphGroupPropertySet *pLegendData =NULL;

	pLegendData=Get(iDataGroup);
	if(pLegendData!=NULL)
	{
		delete pLegendData;
	}

	pLegendData = new CGraphGroupPropertySet();

	strcpy(pLegendData->sLegendLabel,(LPCTSTR)sLabel);
	pLegendData->groupColor=color;
	pLegendData->iMarkerSize=iMarkerSize;
	pLegendData->iLineWidth=iLineWidth;
	pLegendData->eMarkerType=eMarkerType;

	m_arrayProperty.SetAtGrow (iDataGroup,pLegendData);
}

CGraphGroupPropertySet  * CGraphGroupProperty::Get(int iDataGroup)
{
	if(iDataGroup<0||iDataGroup>=GetLegendLength ())
	{
		return NULL;
	}

	CGraphGroupPropertySet* pProperty= (CGraphGroupPropertySet*) m_arrayProperty.GetAt(iDataGroup);

	return pProperty;
}


CString CGraphGroupProperty::GetLegendText(int iDataGroup)
{
	CGraphGroupPropertySet *legendData=(CGraphGroupPropertySet *)m_arrayProperty.GetAt (iDataGroup);
	return legendData->sLegendLabel ;
}

int CGraphGroupProperty::GetLegendLength()
{
	int n=m_arrayProperty.GetCount ();
	return n;
}

void CGraphGroupProperty::RemoveAll()
{
	CGraphGroupPropertySet *legendSet;
	for(int i=0;i<m_arrayProperty.GetCount ();i++)
	{
		legendSet = (CGraphGroupPropertySet*)m_arrayProperty.GetAt(i);
		delete legendSet;
	}
	m_arrayProperty.RemoveAll ();
}
