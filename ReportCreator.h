
#pragma once

#include <list>
#include "fhimage.h"

class CReportLine
{
public:
    short siWidth;
    unsigned int iStyle;

public:
    CReportLine()
    {
        siWidth=1;
        iStyle=1;
    };

    void Set(short siWidthTag,unsigned int iStyleTag)
    {
        siWidth=siWidthTag;
        iStyle=iStyleTag;
    };

    void Set(CReportLine &line)
    {
		memcpy(this,&line,sizeof(CReportLine));
    };


};

enum enumLinePos
{
    LP_TOP,
    LP_BOTTOM,
    LP_LEFT,
    LP_RIGHT,
    LP_ALL
};

enum enumContentWidth
{
	CW_FIXEDBYCONTENT,
	CW_NOLIMIT,
    CW_COMMONWIDTH,
	CW_GRIDWIDTH,
	CW_SETBYUSER
};


class CReportGrid
{

public:
	char  * psContent;
    CFont * psFont;
	LOGFONT lfOriFont;
	UINT nFormatContent;
	enumContentWidth eContentWidth;
	short siContentWidth;

    short siWidth;
    short siHeight;

    CReportLine lineUp;
    CReportLine lineDown;
    CReportLine lineLeft;
    CReportLine lineRight;

    CReportGrid(void);
    ~CReportGrid(void);

    void SetOriFont(LOGFONT *pLogFont);
    void SetContent(CString sContent, enumContentWidth eCW=CW_NOLIMIT, short siCW=0);
    void SetLineStyle(enum enumLinePos,int iWidth,int iStyle=1);
	void SetLine(enumLinePos LP,CReportLine &line);
	bool GetLogFont(LOGFONT *pLogFont);
	char *GetContent(){ return psContent;};
	bool SetDimension(int iWidth,int iHeight);

};

enum enumStringPos 
{
	SP_TITLE,
	SP_SECONDTITLE,
	SP_LEFTUP,
	SP_LEFTDOWN,
	SP_RIGHTUP,
	SP_RIGHTDOWN,
	SP_COMMON
};

class CReportString
{
public:
	CRect rectPos;
	char *psString;
	LOGFONT lfOriFont;
	CFont *pFont;
	UINT nFormat;
	enumStringPos pos;

	CReportString()
	{
		psString=NULL;
		pFont=NULL;
		memset(&lfOriFont,0,sizeof(LOGFONT));
		lfOriFont.lfHeight =16;
		lfOriFont.lfCharSet = GB2312_CHARSET;
		strcpy(lfOriFont.lfFaceName ,(LPCTSTR)"ËÎÌו");
		pFont=new CFont;
		pFont->CreateFontIndirect (&lfOriFont);

		nFormat=DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_NOCLIP;
	};

	~CReportString()
	{
		if(psString)
		{
			delete []psString;
			psString=NULL;
		}

		if(pFont)
		{
			delete pFont;
			pFont=NULL;
		}
	};

	void SetOriFont(LOGFONT *pLogfont)
	{
		memcpy(&lfOriFont,pLogfont,sizeof(LOGFONT));
	};
	
};

class CReportCreator
{

protected:
    int m_iRowQty;
    int m_iColQty;
	COLORREF m_iColor;
    
    // Default Line:
    int m_iDefaultLineWidth;
    unsigned int m_iDefaultLineStyle;

    CReportGrid *m_pGrids;
	
	LOGFONT m_lfTitle;
	LOGFONT m_lfViceTitle;
	LOGFONT m_lfFoot;
	LOGFONT m_lfContent;

	std::list<CReportString * >	m_listStrings;

	CRect m_rectTable;
	CRect m_rectReport;
	int   m_iEdgeWidth;

	bool m_bKeepRatio;

	CRect	m_rectTargetDraw;

	int m_iNoteRowLength;
	int m_iMarkPicWidth;

	CString m_sMarkPic;
	CFHImage m_Image;

	float m_fDrawRatio;


public:
    CReportCreator();
    ~CReportCreator();

	CRect GetTargetDrawRect(){return m_rectTargetDraw;};

    bool SetGridQty(int iRowQty,int iColQty);
	bool SetGridContent(int iRow,
						int iCol, 
						CString sContent,
						enumContentWidth eCW=CW_NOLIMIT,
						int iWidth=0);
	
	bool SetGridFormat(int iRow,int iCol,UINT iFormat );
	
	bool CombineGrid(int iStartRow, int iEndRow, int iStartCol,int iEndCol);
	bool SetColor(COLORREF iColor);

    void SetGridFont(int iRow,int iCol, LOGFONT *pLogFont);

    void SetDefaultLine(int iWidth, unsigned int iStyle);
	void SetEdgeLine(CReportLine & line);

	void SetEdgeLineWidth(int iWidth);
	void SetLineWidth(int iWidth);
	void SetCharLineLimit(CDC *pDC,int iLimit);
	void SetMarkPicWidth(int iPicWidth);
	bool SetMarkPic(CString sPicName);

	CString CutString(CString &sOri, int iCutLen);
	CString ReSplitString(CString sContent,int iWidth);
	CString ReSplitStringByWidth(CDC *pDC,CString sContent,int iWidth);

	////////////////////////////////
	//
	////////////////////////////////
	bool GetGridFont(int iRow,int iCol,LOGFONT *pLogFont);
	CSize GetContentSize(CDC *pDC, CReportGrid *pGrid);
	CRect GetGridCombineRange(int iRow,int iCol);
	CRect GetGridRect(CRect rectRange);
	void EnlargeGridWidth(CRect rectRange,int iAdd);
	void EnlargeGridHeight(CRect rectRange,int iAdd);
	bool IsHorCombined(CReportGrid *pGrid);
	bool IsVerCombined(CReportGrid *pGrid);

	void RemoveAllStrings();

	CRect GetStringsRange();

	void SetTitleLogFont(LOGFONT &lf);
	void SetViceTitleLogFont(LOGFONT &lf);
	void SetFootLogFont(LOGFONT &lf);
	void SetGridFont(LOGFONT &lf);

    //////////////////////////////
    //
    //////////////////////////////
	bool SetDrawRect(CDC *pDC,CRect *pRect);
    void Draw(CDC *pDC);


	/////////////////////////////
	//
	void AddString(CString sString,
					CRect rect,
					enumStringPos sp=SP_COMMON,
					UINT iFormat=0,
					LOGFONT * pLogFont=NULL);

	void ModifyStringFont(LOGFONT &lf, enumStringPos pos);


	void SetTitle(CString sTitle,LOGFONT * pLogFont=NULL);
	void SetViceTitle(CString sTitle,LOGFONT * pLogFont=NULL);
	void SetLeftUpString(CString sString,LOGFONT * pLogFont=NULL);
	void SetRightUpString(CString sString,LOGFONT * pLogFont=NULL);
	void SetLeftDownString(CString sString,LOGFONT * pLogFont=NULL);
	void SetRightDownString(CString sString,LOGFONT * pLogFont=NULL);

protected:
	void DrawPic(CDC *pDC, int iX,int iY);
	void DrawGrids(CDC *pDC,double dOriX,double dOriY);
	void DrawContents(CDC *pDC,double dOriX,double dOriY);
	void DrawStrings(CDC *pDC,double dOriX,double dOriY);

	void DrawText(			CDC		*pDC,
							CString	s, 
							CRect	rect,
							UINT	iFormat);

   
	CReportGrid  * GetGrid(int iRow,int iCol);
	bool AdjustRowColWidth(CDC *pDC);
	bool AdjustReportSize(CRect rectTarget);

	CRect CalcTableRect();
	CRect CalcReportRect(); //CDC *pDC, int nXOrg,int nyOrg);
	bool ReCutNoteContent();


};