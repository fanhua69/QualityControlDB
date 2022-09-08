

#pragma once

enum enumMarkerType
{
	MT_NONE,
	MT_TRI,
	MT_BOX,
	MT_SPH,
	MT_DIA
};

class CGraphGroupPropertySet
{
// Construction
public:
	CGraphGroupPropertySet()
	{
		strcpy(sLegendLabel,"未知");
		groupColor=RGB(255,0,0);
		iMarkerSize=4;
		iLineWidth=2;
		eMarkerType=MT_TRI;
	};

	void Copy( CGraphGroupPropertySet *pOther)
	{
		memcpy(this,pOther,sizeof(CGraphGroupPropertySet));
	};

	char			sLegendLabel[100];
	COLORREF		groupColor;
	int				iMarkerSize;
	int				iLineWidth;
	enumMarkerType	eMarkerType;
};

/////////////////////////////////////////////////////////////////////////////
// CGraphGroupProperty window

class CGraphGroupProperty
{
// Construction
public:
	CGraphGroupProperty();
	~CGraphGroupProperty();

private:
	CPtrArray m_arrayProperty;

// Operations
public:
	void Set(	int					iDataGroup,
				CString				sLabel,
				COLORREF			color,
				int					iMarkerSize,
				int					iLineWidth,
				enumMarkerType		eMarkerType);

	void Set(	int					iDataGroup,
				CGraphGroupPropertySet *pSet);
	
	CGraphGroupPropertySet  * Get(int iDataGroup);


	void SetLegendText(int iDatagroup, CString label);
	CString GetLegendText(int iDatagroup);
	int GetLegendLength();
	void RemoveAll();

};