#include "StdAfx.h"
#include "ReportView.h"
#include "afxwin.h"
#include "StringExtractor.h"
#include "math.h"
#include "fhcglobal.h"
#include "DlgReportShowProperty.h"
#include "math.h"
#include "ReportCreator.h"
#include "fhmainfrm.h"


CReportGrid::CReportGrid()
{
    siWidth=10;
    siHeight=10;
    psContent=NULL;
    psFont=NULL;
	memset(&lfOriFont,0,sizeof(LOGFONT));
	lfOriFont.lfHeight =16.0;

	eContentWidth=CW_NOLIMIT;
	siContentWidth=-1;

	if(psFont)
	{
		delete psFont;
		psFont=NULL;
	}
	psFont=new CFont;
	psFont->CreateFontIndirect (&lfOriFont);

	nFormatContent=DT_SINGLELINE|DT_VCENTER|DT_CENTER;
};

CReportGrid::~CReportGrid()
{
    if(psContent)
    {
        delete []psContent;
        psContent=NULL;
    }

    if(psFont!=NULL)
    {
        delete psFont;
		psFont=NULL;
    }
};

// CReportCreator message handlers

void CReportGrid::SetContent(CString sContent, enumContentWidth eCW, short siCW)
{
    if(psContent)
    {
        delete []psContent;
        psContent=NULL;
    }

    psContent=new char [sContent.GetLength ()+8];

    strcpy(psContent,(LPCTSTR)sContent);
	eContentWidth=eCW;
	if(eContentWidth==CW_FIXEDBYCONTENT)
	{
	}
	else if(eContentWidth==CW_NOLIMIT)
	{
	}
	else if(eContentWidth==CW_COMMONWIDTH)
	{
	}
	else if(eContentWidth==CW_GRIDWIDTH)
	{
	}
	else if(eContentWidth==CW_SETBYUSER)
	{
		siContentWidth=siCW;
	}
	else
	{
		ASSERT(false);
	}
};

void CReportGrid::SetOriFont(LOGFONT *pLogFont)
{
	memcpy(&lfOriFont,pLogFont,sizeof(LOGFONT));

	if(psFont)
	{
		delete psFont;
	}
	psFont=new CFont;
	psFont->CreateFontIndirect (&lfOriFont);
};

bool CReportGrid::GetLogFont(LOGFONT *pLogFont)
{
	if(psFont==NULL)
	{
		return false;
	}
	else
	{
		psFont->GetLogFont (pLogFont);
		return true;
	}
}

void CReportGrid::SetLineStyle(enumLinePos LP,int iWidth,int iStyle)
{
    switch (LP)
    {
    case LP_TOP: 
        lineUp.Set (iWidth,iStyle);
        break;
    case LP_BOTTOM:
        lineDown.Set (iWidth,iStyle);
        break;
    case LP_LEFT: 
        lineLeft.Set (iWidth,iStyle);
        break;
    case LP_RIGHT:
        lineRight.Set (iWidth,iStyle);
        break;
    default:
        lineUp.Set (iWidth,iStyle);
        lineDown.Set (iWidth,iStyle);;
        lineLeft.Set (iWidth,iStyle);
        lineRight.Set (iWidth,iStyle);
    }
};

void CReportGrid::SetLine(enumLinePos LP,CReportLine &line)
{
	switch (LP)
    {
    case LP_TOP: 
        lineUp.Set (line);
        break;
    case LP_BOTTOM:
        lineDown.Set  (line);
        break;
    case LP_LEFT: 
        lineLeft.Set  (line);
        break;
    case LP_RIGHT:
        lineRight.Set (line);
        break;
    default:
        lineUp.Set (line);
        lineDown.Set  (line);
        lineLeft.Set  (line);
        lineRight.Set  (line);
    }
}

CReportCreator::CReportCreator()
{
    m_iRowQty=0;
    m_iColQty=0;
	m_iColor=0;
    m_pGrids=NULL;
	m_fDrawRatio=1.0;

	CDlgReportShowProperty dlg;

    m_iDefaultLineWidth=dlg.GetLineWidth ();	
	m_iEdgeWidth=dlg.GetEdgeLineWidth ();
	m_iNoteRowLength=dlg.GetLineCharLimit ();
	m_iMarkPicWidth=dlg.GetMarkPicWidth ();
	m_sMarkPic = dlg.GetMarkPicName();


	dlg.GetContentLogFont (m_lfContent);
	dlg.GetTitleLogFont (m_lfTitle);
	dlg.GetViceTitleLogFont (m_lfViceTitle);
	dlg.GetFootLogFont (m_lfFoot);

	this->SetMarkPic (m_sMarkPic);
	
	m_bKeepRatio=true;   // 根据网格中数据的多少决定网格的高度。

}

CReportCreator::~CReportCreator()
{
    if(m_pGrids)
    {
        delete []m_pGrids;
        m_pGrids=NULL;
    }

	RemoveAllStrings();
}

bool CReportCreator::SetColor(COLORREF iColor)
{
	m_iColor=iColor;

	return true;
}
    
bool CReportCreator::SetGridQty(int iRowQty,int iColQty)
{
    if(iRowQty<1||iRowQty>10000||iColQty<1||iColQty>10000)
    {
        return false;
    }

    int iGridQty=iRowQty*iColQty;
    if(m_pGrids)
    {
        delete []m_pGrids;
        m_pGrids=NULL;
    }
    m_pGrids=new CReportGrid[iGridQty+5];


    m_iRowQty=iRowQty;
    m_iColQty=iColQty;

	SetGridFont(m_lfContent);

    return true;
}

bool CReportCreator::SetGridContent(int iRow,
									int iCol, 
									CString sContent,
									enumContentWidth eCW,
									int iWidth)
{
    CReportGrid *pGrid=GetGrid(iRow,iCol);
    if(!pGrid)
    {
        return false;
    }

    pGrid->SetContent(sContent,eCW,iWidth);

	return true;
}



bool CReportCreator::ReCutNoteContent()
{
    CReportGrid *pGrid=NULL;

	int i=0,j=0;
	CString sContent,sCutContent;
	for(i=0;i<m_iRowQty;i++)
	{
		for(j=0;j<m_iColQty;j++)
		{
			CReportGrid *pGrid=GetGrid(i,j);
			if(pGrid->eContentWidth ==CW_COMMONWIDTH
				||pGrid->eContentWidth ==CW_SETBYUSER)
			{
				if(pGrid->eContentWidth ==CW_COMMONWIDTH)
				{
					pGrid->siContentWidth = m_iNoteRowLength;
				}
				sCutContent=ReSplitString(pGrid->GetContent (),pGrid->siContentWidth);
				pGrid->SetContent (sCutContent);
			}
		}
	}

	return true;
}

CString CReportCreator::ReSplitString(CString sContent,int iWidth)
{
	iWidth=abs(iWidth);
	if(iWidth<1)
	{
		iWidth=1;
	}

	sContent.Remove ('\2');
	CString sCutContent="";
	while(sContent.GetLength ()>iWidth)
	{
		sCutContent+=CutString(sContent, iWidth);
		sCutContent+="\2";
	}
	sCutContent+=sContent;

	return sCutContent;
}

bool CReportCreator::AdjustRowColWidth(CDC *pDC)
{
	//
	CFont *pFont=NULL;
	int iWidth=0,iHeight=0;
	int iMaxWidth=0,iMaxHeight=0;
	CSize sizeContent;
	CReportGrid *pGrid=GetGrid(0,0);
	if(!pGrid)return false ;

	int i=0,j=0,k=0,n=0;
	char * pSubString=NULL;
	int iCX=0,iCY=0;

	
	CFont *pOldFont=pDC->SelectObject (pGrid->psFont );

	///////////////////////////////////
	// Make every Col the max width:
	///////////////////////////////////
	for(i=0;i<m_iColQty;i++)
	{
		iMaxWidth=0;

		for(j=0;j<m_iRowQty;j++)
		{
			pGrid=GetGrid(j,i);
			if(!pGrid)continue;

			// A combined grid:
			if(IsHorCombined(pGrid))
			{
				iCX=10;
			}

			// a single grid:
			else
			{
				if(pGrid->eContentWidth !=CW_GRIDWIDTH) // deal with it after all grids width 
				{
					sizeContent=GetContentSize(pDC,pGrid);
					iCX=sizeContent.cx;
				}
				else
				{
					iCX=10;
				}
			}

			if(iCX > iMaxWidth)
			{
				iMaxWidth=iCX;
			}
		}

		iMaxWidth+=8;

		//
		for(j=0;j<m_iRowQty;j++)
		{
			pGrid=GetGrid(j,i);
			pGrid->siWidth = iMaxWidth;
		}
	}



	//////////////////////////////////////////////////////////////
	// Increase the width according to the combined grid content:
	//////////////////////////////////////////////////////////////
	int iAdd=0;
	CRect rectRange;
	CRect rectSize;
	for(i=0;i<m_iColQty;i++)
	{

		for(j=0;j<m_iRowQty;j++)
		{
			pGrid=GetGrid(j,i);
			if(!pGrid||!pGrid->psContent )continue;

			// A combined grid:
			if(IsHorCombined(pGrid)&&pGrid->eContentWidth !=CW_GRIDWIDTH)
			{
				rectRange=GetGridCombineRange(j,i);

				sizeContent=GetContentSize(pDC,pGrid);
				sizeContent.cx +=8;

				rectSize=GetGridRect(rectRange);
				if(sizeContent.cx>rectSize.Width ())
				{
					iAdd=sizeContent.cx-rectSize.Width ();
					EnlargeGridWidth(rectRange,iAdd);
				}
			}
		}
	}


	/////////////////////////////////////////////////////////////////
	// Deal with those grids whose width changes with grid width:
	/////////////////////////////////////////////////////////////////
	CRect rect1,rect;
	CString sNewContent;
	CSize size;
	for(i=0;i<m_iColQty;i++)
	{
		pGrid=GetGrid(0,i);
		iMaxWidth=pGrid->siWidth ;

		for(j=0;j<m_iRowQty;j++)
		{
			pGrid=GetGrid(j,i);
			if(!pGrid||pGrid->eContentWidth!=CW_GRIDWIDTH||pGrid->psContent ==NULL) 
			{
				continue;
			}

			// A combined grid:
			if(IsHorCombined(pGrid))
			{
				rect1=GetGridCombineRange (j,i);
				rect=GetGridRect(rect1);
				iWidth=rect.Width ();
			}
			else
			{
				iWidth=iMaxWidth;
			}

			// a single grid:
			CFont fontTmp;
			fontTmp.CreateFontIndirect (&pGrid->lfOriFont);
			pDC->SelectObject (&fontTmp);

			sNewContent=ReSplitStringByWidth(	pDC,
												pGrid->GetContent (),
												iWidth);
			
			pGrid->SetContent (sNewContent,CW_GRIDWIDTH);

		}
	}

	///////////////////////////////////
	// Make every row the max height:
	///////////////////////////////////
	for(i=0;i<m_iRowQty;i++)
	{
		iMaxHeight=0;

		for(j=0;j<m_iColQty;j++)
		{
			pGrid=GetGrid(i,j);
			if(!pGrid)continue;

			if(IsVerCombined(pGrid))
			{
				iCY=10;
			}
			else
			{				
				sizeContent=GetContentSize(pDC,pGrid);
				iCY=sizeContent.cy;
			}

			if(iCY> iMaxHeight)
			{
				iMaxHeight=iCY;
			}
		}

		iMaxHeight+=8;
		if(iMaxHeight<=10)
		{
			iMaxHeight=10;
		}

		//
		for(j=0;j<m_iColQty;j++)
		{
			pGrid=GetGrid(i,j);
			pGrid->siHeight = iMaxHeight;
		}
	}

	//////////////////////////////////////////////////////////////
	// Increase the heights according to the combined grid content:
	//////////////////////////////////////////////////////////////
	for(i=0;i<m_iColQty;i++)
	{
		for(j=0;j<m_iRowQty;j++)
		{
			pGrid=GetGrid(j,i);
			if(!pGrid||!pGrid->psContent )continue;

			// A combined grid:
			if(IsVerCombined(pGrid))
			{
				rectRange=GetGridCombineRange(j,i);

				sizeContent=GetContentSize(pDC,pGrid);
				sizeContent.cy +=8;

				rectSize=GetGridRect(rectRange);

				if(sizeContent.cy>rectSize.Height ())
				{
					iAdd=sizeContent.cy-rectSize.Height ();
					EnlargeGridHeight(rectRange,iAdd);
				}
			}
		}
	}


	pDC->SelectObject (pOldFont);
		

    return true;
}

bool CReportCreator::IsHorCombined(CReportGrid *pGrid)
{
	if(	pGrid->lineLeft	.siWidth	==0||
		pGrid->lineRight.siWidth	==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CReportCreator::IsVerCombined(CReportGrid *pGrid)
{
	if(	pGrid->lineDown	.siWidth	==0||
		pGrid->lineUp.siWidth	==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CReportCreator::EnlargeGridWidth(CRect rectRange,int iAdd)
{
	CReportGrid *pGrid=NULL;
	int i,j;

	int iAdjustableCol=0;
	int *piAdjusttable=new int [rectRange.right-rectRange.left +1+10];
	memset(piAdjusttable,0,sizeof(int)*(rectRange.right-rectRange.left +1+10));

	int iOrder=0;
	for(i=rectRange.left ;i<=rectRange.right ;i++)
	{
		piAdjusttable[iOrder]=1;
		for(j=0;j<m_iRowQty;j++)
		{
			pGrid=GetGrid(j,i);
			if(!pGrid)
			{
				ASSERT(false);
				continue;
			}

			if(pGrid->eContentWidth == CW_FIXEDBYCONTENT||
			   pGrid->eContentWidth == CW_SETBYUSER)
			{
				piAdjusttable[iOrder]=0;
				break;
			}
		}

		if(piAdjusttable[iOrder])
		{
			iAdjustableCol++;
		}

		iOrder++;
	}

	if(iAdjustableCol==0)
	{
		iAdjustableCol=rectRange.right-rectRange.left +1;
	}
	int iColAdd=iAdd/iAdjustableCol;

	iOrder=0;
	for(i=rectRange.left ;i<=rectRange.right ;i++)
	{
		if(piAdjusttable[iOrder]==0)continue;

		for(j=0;j<m_iRowQty;j++)
		{
			pGrid=GetGrid(j,i);
			pGrid->siWidth +=iColAdd;
		}

		iOrder++;
	}

	delete []piAdjusttable;

	return;
}


void CReportCreator::EnlargeGridHeight(CRect rectRange,int iAdd)
{
	CReportGrid *pGrid=NULL;
	int i,j;
	int iColAdd=iAdd/(rectRange.bottom - rectRange.top+1);
	for(i=rectRange.top ;i<=rectRange.bottom ;i++)
	{
		for(j=0;j<m_iColQty;j++)
		{
			pGrid=GetGrid(i,j);
			if(!pGrid)
			{
				ASSERT(false);
				continue;
			}
			pGrid->siHeight +=iColAdd;
		}
	}

	return;
}


CRect CReportCreator::GetGridRect(CRect rectRange)
{
	int i=0;
	int iCX=0,iCY=0;
	CReportGrid *pGrid=NULL;
	CRect rect;

	iCX=0;
	for(i=0;i<m_iColQty;i++)
	{
		pGrid=GetGrid(rectRange.top,i);
		if(i==rectRange.left )
		{
			rect.left = iCX+pGrid->lineLeft .siWidth +2;
		}
		
		iCX+=pGrid->siWidth ;

		if(i==rectRange.right)
		{
			rect.right = iCX-pGrid->lineLeft .siWidth -2;
		}
	}

	iCY=0;
	for(i=0;i<m_iRowQty;i++)
	{
		pGrid=GetGrid(i,rectRange.left);
		if(i==rectRange.top )
		{
			rect.top= iCY+pGrid->lineUp .siWidth +2;;
		}
		
		iCY+=pGrid->siHeight ;

		if(i==rectRange.bottom)
		{
			rect.bottom = iCY-pGrid->lineDown .siWidth -2;;
		}
	}

	return rect;
}

CRect CReportCreator::GetGridCombineRange(int iRow,int iCol)
{
	int i,j;
	CReportGrid *pGrid=NULL;
	int iUp,iDown,iLeft=iCol,iRight=iCol;

	// Up:
	iUp=0;
	for(i=iRow;i>=0;i--)
	{
		pGrid=GetGrid(i,iCol);
		if(pGrid->lineUp .siWidth !=0)
		{
			iUp=i;
			break;
		}
	}

	// Down:
	iDown=m_iRowQty-1;
	for(i=iRow;i<m_iRowQty;i++)
	{
		pGrid=GetGrid(i,iCol);
		if(pGrid->lineDown.siWidth !=0)
		{
			iDown=i;
			break;
		}
	}

	// Left and right:
	int iLeftMin=0,iRightMin=m_iColQty-1;
	for(i=iUp;i<=iDown;i++)
	{
		for(j=iCol;j>=0;j--)
		{
			pGrid=GetGrid(i,j);

			if(pGrid->lineLeft .siWidth !=0)
			{
				iLeft=j;
				break;
			}
		}

		for(j=iCol;j<m_iColQty;j++)
		{
			pGrid=GetGrid(i,j);

			if(pGrid->lineRight .siWidth !=0)
			{
				iRight=j;
				break;
			}
		}

		if(iLeft>iLeftMin)
		{
			iLeftMin=iLeft;
		}

		if(iRight<iRightMin)
		{
			iRightMin=iRight;
		}
	}

	return CRect(iLeftMin,iUp,iRightMin,iDown);
}

CSize CReportCreator::GetContentSize(CDC *pDC,
									 CReportGrid *pGrid)
{
	static int k=0;
	static CFont *pOldFont=NULL;
	static char *pSubString=NULL;
	static CStringExtractor se;
	static CSize sizeContent;
	static int n=0;
	static int iCX=0,iCY=0;
	CString sContent=pGrid->psContent ;


	se.SetSepChar ("\r\2");
	if(sContent=="")return CSize(10,10);

	pOldFont=pDC->SelectObject (pGrid->psFont);

	se.SetString (sContent.GetBuffer ());
	sContent.ReleaseBuffer ();
	n=se.GetSubStringQty ();
	iCX=0;
	iCY=0;

	int iCharHor=0;
	int iCharVer=0;

	for(k=0;k<n;k++)
	{
		pSubString=se.GetSubString(k);
		if(strlen(pSubString)>iCharHor)
		{
			iCharHor=strlen(pSubString);
		}
		sizeContent=pDC->GetTextExtent (pSubString);
		if(sizeContent.cx > iCX)
		{
			iCX=sizeContent.cx;
		}
		iCY+=sizeContent.cy;
		iCharVer++;
	}

	//////////////////////////////
	//

	int iOriCX=abs(pGrid->lfOriFont .lfHeight )/ (iCY/(float)iCharVer) * iCX;
	int iOriCY=abs(pGrid->lfOriFont .lfHeight )* iCharVer;


	return CSize(iOriCX,iOriCY);
}

void CReportCreator::SetDefaultLine(int iWidth, unsigned int iStyle)
{
    m_iDefaultLineWidth=iWidth;
    m_iDefaultLineStyle=iStyle;
}

void CReportCreator::RemoveAllStrings()
{
	std::list <CReportString *>::iterator p;
	CReportString * par;

	for ( p = m_listStrings.begin(); p!= m_listStrings.end(); ++p )
	{
		par=*p;
		delete par;
	}

	m_listStrings.clear ();

}

bool CReportCreator::CombineGrid(int iStartRow, int iEndRow, int iStartCol,int iEndCol)
{
    int i,j;
    CReportGrid *pGrid=NULL;

    /////////////////////////////
    // Set All Grids to NULL Edge:
    /////////////////////////////
    for(i=iStartRow;i<=iEndRow;i++)
    {
        for(j=iStartCol;j<=iEndCol;j++)
        {
            pGrid=GetGrid(i,j);
            if(!pGrid)continue;
            pGrid->SetLineStyle (LP_LEFT,0,0);
            pGrid->SetLineStyle (LP_TOP,0,0);
            pGrid->SetLineStyle (LP_RIGHT,0,0);
            pGrid->SetLineStyle (LP_BOTTOM,0,0);
        }
    }

    /////////////////////////////
    // Grids Edges:
    /////////////////////////////
    int iWidth=m_iDefaultLineWidth;
    int iStyle=m_iDefaultLineStyle;
    for(i=iStartRow;i<=iEndRow;i++)
    {
        pGrid=GetGrid(i,iEndCol);
        if(!pGrid)continue;
        pGrid->SetLineStyle (LP_RIGHT,iWidth, iStyle);
    }

    for(i=iStartRow;i<=iEndRow;i++)
    {
        pGrid=GetGrid(i,iStartCol);
        if(!pGrid)continue;
        pGrid->SetLineStyle (LP_LEFT,iWidth, iStyle);
    }

    for(i=iStartCol;i<=iEndCol;i++)
    {
        pGrid=GetGrid(iStartRow,i);
        if(!pGrid)continue;
        pGrid->SetLineStyle (LP_TOP,iWidth, iStyle);
    }

    for(i=iStartCol;i<=iEndCol;i++)
    {
        pGrid=GetGrid(iEndRow,i);
        if(!pGrid)continue;
        pGrid->SetLineStyle (LP_BOTTOM,iWidth, iStyle);
    }

    return true;
}


void CReportCreator::SetGridFont(int iRow,int iCol, LOGFONT *pLogFont)
{
    CReportGrid *pGrid=GetGrid(iRow,iCol);
    pGrid->SetOriFont(pLogFont);
}


CReportGrid  *  CReportCreator::GetGrid(int iRow,int iCol)
{
    if(iRow<0||iRow>=m_iRowQty||iCol<0||iCol>=m_iColQty||!m_pGrids)
    {
        return NULL;
    }

    int iOrder=iRow*m_iColQty+iCol;

    return &m_pGrids[iOrder];
};

bool  CReportCreator::SetDrawRect(CDC *pDC, CRect *pRect)
{
	CRect rect;
	if(!pRect)
	{
		rect.CopyRect (&m_rectTargetDraw);
	}
	else
	{
		rect.CopyRect (pRect);
	}

	if(rect.Width ()<100)
	{
		rect.right =rect.left +100;
	}

	if(rect.Height ()<100)
	{
		rect.bottom =rect.top +100;
	}

	ReCutNoteContent();

	if(!AdjustRowColWidth(pDC))return false;
	
	if(AdjustReportSize(rect))
	{
		m_rectTargetDraw=rect;
		CalcTableRect();
		CalcReportRect();
		return true;
	}
	else
	{
		return false;
	}
}

void CReportCreator::Draw(CDC *pDC)
{
	CRect rect=GetStringsRange();

	CPoint point(-rect.left+m_rectTargetDraw.left  ,-rect.top+m_rectTargetDraw.top );
	DrawPic(pDC,m_rectReport.left+point.x ,m_rectReport.top+point.y );
	DrawContents(pDC,point.x,point.y);
	DrawStrings(pDC,point.x,point.y);
	DrawGrids(pDC,point.x,point.y);
}

bool CReportCreator::SetMarkPic(CString sPicName)
{
	m_sMarkPic=sPicName;
	m_Image.Destroy ();
	HRESULT hr=m_Image.Load (m_sMarkPic);
	if(FAILED(hr))
	{
		TRACEERROR("无法载入图片:"+m_sMarkPic);
		return false;
	}
	return true;
}

void CReportCreator::SetMarkPicWidth(int iPoint)
{
	m_iMarkPicWidth=iPoint;
}

void CReportCreator::DrawPic(CDC *pDC, int iX,int iY)
{	
	int iCurrWidth=m_iMarkPicWidth*m_fDrawRatio;
	
	CRect rect(iX,iY,iX+iCurrWidth,10000);
	m_Image.Show(pDC ,rect,true);
}

CRect CReportCreator::GetStringsRange()
{
	std::list <CReportString *>::iterator p;
	CReportString * par;

	CRect rect=m_rectTargetDraw;

	for ( p = m_listStrings.begin(); p!= m_listStrings.end(); ++p )
	{
		par=*p;
		
		if(par->psString !=NULL)
		{
			if(par->rectPos.left<rect.left )
			{
				rect.left =par->rectPos.left ;
			}

			if(par->rectPos.right >rect.right )
			{
				rect.right  =par->rectPos.right  ;
			}

			if(par->rectPos.top < rect.top  )
			{
				rect.top   =par->rectPos.top   ;
			}

			if(par->rectPos.bottom > rect.bottom  )
			{
				rect.bottom   =par->rectPos.bottom   ;
			}
		}
	}

	return rect;
}

void CReportCreator::DrawStrings(CDC *pDC,double dOriX,double dOriY)
{
	std::list <CReportString *>::iterator p;
	CReportString * par;
	CRect rect;

	CReportGrid *pGrid0=GetGrid(0,0);
	CReportGrid *pGrid1=GetGrid(m_iRowQty-1,0);
	if(!pGrid0||!pGrid1)return;

	CFont *pOldFont=pDC->SelectObject (pGrid0->psFont );


	for ( p = m_listStrings.begin(); p!= m_listStrings.end(); ++p )
	{
		par=*p;
		
		if(par->psString !=NULL)
		{
			if(par->pFont !=NULL)
			{
				pDC->SelectObject (par->pFont );
			}
			else
			{
				continue;
			}


			rect.left  =par->rectPos.left  + dOriX;
			rect.right =par->rectPos.right + dOriX;
			rect.top   =par->rectPos.top   + dOriY;
			rect.bottom=par->rectPos.bottom+ dOriY;

			if(   par->pos == SP_TITLE
				||par->pos == SP_SECONDTITLE
				||par->pos == SP_LEFTUP
				||par->pos == SP_RIGHTUP)
			{
				rect.OffsetRect (0,-m_iEdgeWidth);
			}


			if(par->pos == SP_LEFTDOWN || par->pos ==SP_RIGHTDOWN)
			{
				rect.OffsetRect (0,m_iEdgeWidth);
			}

			//pDC->Rectangle (rect);
			pDC->DrawText (	par->psString ,
							rect ,
							par->nFormat );			
			
		}
	}

	pDC->SelectObject (pOldFont);

}

void CReportCreator::DrawGrids(CDC *pDC,double dOriX,double dOriY)
{
    int i,j;

    CReportGrid *pGrid=NULL;
	CBrush brush;
	brush.CreateSolidBrush (m_iColor);
	CBrush *pOldBrush = pDC->SelectObject (&brush);

	double xRight=0;
	double yDown=0;
    double x=dOriX;
    double y=dOriY;

	int iLineWidth=0;

    for(i=0;i<m_iRowQty;i++)
    {
        for(j=0;j<m_iColQty;j++)
        {            
            pGrid=GetGrid(i,j);

			if(!pGrid)continue;


            if(pGrid->lineRight .siWidth !=0)            
            {
				iLineWidth=pGrid->lineRight .siWidth;
				if(j==m_iColQty-1)
				{
					iLineWidth=m_iEdgeWidth;
				}
                pDC->Rectangle (x+pGrid->siWidth ,
								y,
								x+pGrid->siWidth +iLineWidth ,
								y+pGrid->siHeight );
            }

            if(pGrid->lineDown .siWidth !=0)
            {
				iLineWidth=pGrid->lineDown .siWidth;
				if(i==m_iRowQty-1)
				{
					iLineWidth=m_iEdgeWidth;
				}

				pDC->Rectangle (x,
								y+pGrid->siHeight, 
								x+pGrid->siWidth,
								y+pGrid->siHeight+iLineWidth );
			}
			
			x+=pGrid->siWidth ;
        }
		xRight=x;
        x=dOriX;
        y+=pGrid->siHeight ;
    };
	yDown=y;

	/////////////////////////////////////////
	// Draw The Report Edges:
	/////////////////////////////////////////
	
	// Draw the left :
	pDC->Rectangle (dOriX-m_iEdgeWidth,dOriY-m_iEdgeWidth,dOriX,yDown+m_iEdgeWidth);
	
	// Draw the right :
	pDC->Rectangle (xRight,dOriY-m_iEdgeWidth,xRight+m_iEdgeWidth,yDown+m_iEdgeWidth);

	// Draw the top :
	pDC->Rectangle (dOriX,dOriY,xRight+m_iEdgeWidth,dOriY-m_iEdgeWidth);

	// Draw the down :
	pDC->Rectangle (dOriX,yDown,xRight,yDown+m_iEdgeWidth);

	pDC->SelectObject (pOldBrush );	
}

void CReportCreator::DrawContents(CDC *pDC,double dOriX,double dOriY)
{
    int i,j,k,n;

    double x=dOriX;
    double y=dOriY;
    CReportGrid *pGrid=GetGrid(0,0);
	if(!pGrid)return;

	CFont *pOldFont=pDC->SelectObject (pGrid->psFont );

	CFont *pFont=NULL;

	double xRight=0;
	double yDown=0;
	CRect rect;
	CStringExtractor se;
	se.SetSepChar ("\r\2");
	int iCX=0,iCY=0;
	char *pSubString=NULL;
	CSize sizeContent;
	CRect rect1;
	CRect rect2;


    for(i=0;i<m_iRowQty;i++)
    {
        for(j=0;j<m_iColQty;j++)
        {            
            pGrid=GetGrid(i,j);
            if(!pGrid)continue;		

			if(pGrid->psContent !=NULL)
			{
				pDC->SelectObject (pGrid->psFont );

				LOGFONT lf;
				pGrid->psFont->GetLogFont (&lf);

				//
				if(IsHorCombined(pGrid)||IsVerCombined(pGrid))
				{
					rect1=GetGridCombineRange (i,j);
					rect=GetGridRect(rect1);
					rect.OffsetRect (dOriX,dOriY);
				}
				else if(i==0&&j==0)
				{
					rect.SetRect (  x,
									y,
									x+pGrid->siWidth,
									y+pGrid->siHeight);

				}
				else if(i==0)
				{
					rect.SetRect (	x,
									y+pGrid->lineUp.siWidth,
									x+pGrid->siWidth,
									y+pGrid->siHeight);
				}
				else if(j==0)
				{
					rect.SetRect (	x, //+pGrid->lineLeft.siWidth,
									y+pGrid->lineUp.siWidth,
									x+pGrid->siWidth,
									y+pGrid->siHeight);

				}
				else
				{
					rect.SetRect (	x+pGrid->lineLeft.siWidth,
									y+pGrid->lineUp.siWidth,
									x+pGrid->siWidth,
									y+pGrid->siHeight);
				}
				se.SetString (pGrid->psContent);
				n=se.GetSubStringQty ();

				// Draw the texts, if VCENTER, locate the start vertical pos:
				iCX=0;
				iCY=0;
				if(pGrid->nFormatContent|DT_VCENTER)
				{
					for(k=0;k<n;k++)// Calc the total height:
					{
						pSubString=se.GetSubString(k);
						sizeContent=pDC->GetTextExtent (pSubString);
						iCY+=sizeContent.cy ;
					}
					iCY=(rect.Height ()-iCY)/2;
				}


				for(k=0;k<n;k++)
				{
					pSubString=se.GetSubString(k);
					
					sizeContent=pDC->GetTextExtent (pSubString);
					DrawText (	pDC,
								pSubString,
								CRect(rect.left,rect.top +iCY, rect.right ,rect.top+iCY+sizeContent.cy),
								pGrid->nFormatContent);

					iCY+=sizeContent.cy;
				}
			}             
			
			x+=pGrid->siWidth ;
        }
		xRight=x;
        x=dOriX;
        y+=pGrid->siHeight ;
    };

	pDC->SelectObject (pOldFont);
}

void CReportCreator::SetEdgeLine(CReportLine &line)
{
    /////////////////////////////
    // Grids Edges:
    /////////////////////////////
	int i;
    int iWidth=m_iDefaultLineWidth;
    int iStyle=m_iDefaultLineStyle;
	CReportGrid *pGrid=NULL;
    for(i=0;i<=m_iRowQty;i++)
    {
        pGrid=GetGrid(i,0);
        if(!pGrid)continue;
        pGrid->SetLine(LP_LEFT,line);
    }

    for(i=0;i<=m_iRowQty;i++)
    {
        pGrid=GetGrid(i,m_iColQty-1);
        if(!pGrid)continue;
        pGrid->SetLine(LP_RIGHT,line);
    }

    for(i=0;i<=m_iColQty;i++)
    {
        pGrid=GetGrid(0,i);
        if(!pGrid)continue;
        pGrid->SetLine(LP_TOP,line);
    }

    for(i=0;i<=m_iColQty;i++)
    {
        pGrid=GetGrid(m_iRowQty-1,i);
        if(!pGrid)continue;
        pGrid->SetLine (LP_BOTTOM,line);
    }	
}

/////////////////////////////////////
//
/////////////////////////////////////
void CReportCreator::AddString(CString sString,
						CRect rect,
						enumStringPos sp,
						UINT iFormat,
						LOGFONT * pLogFont)
{
	CReportString *s=new CReportString;
	
	//
	s->psString = new char [sString.GetLength()+8];
	strcpy(s->psString ,(LPCTSTR)sString);
	
	//
	s->rectPos = rect;

	//
	s->pos = sp;

	//
	if(iFormat!=0)
	{
		s->nFormat = iFormat;
	}

	//
	if(pLogFont!=NULL)
	{
		memcpy(&s->lfOriFont ,pLogFont,sizeof(LOGFONT));
		if(s->pFont )
		{
			delete s->pFont ;
		}
		s->pFont = new CFont ;
		s->pFont ->CreateFontIndirect (pLogFont);
	}

	//
	m_listStrings.push_back(s);
}

void  CReportCreator::SetTitle(CString sTitle,LOGFONT * pLogFont)
{
	if(pLogFont==NULL)
	{
		pLogFont=&m_lfTitle;
	}
	AddString(sTitle,CRect(0,0,10,10),SP_TITLE,0,pLogFont);
}
void  CReportCreator::SetViceTitle(CString sTitle,LOGFONT * pLogFont)
{
	if(pLogFont==NULL)
	{
		pLogFont=&m_lfFoot;
	}

	AddString(sTitle,CRect(0,0,10,10),SP_SECONDTITLE,0,pLogFont);
}
void  CReportCreator::SetLeftUpString(CString sString,LOGFONT * pLogFont)
{
	if(pLogFont==NULL)
	{
		pLogFont=&m_lfFoot;
	}

	AddString(sString,CRect(0,0,10,10),SP_LEFTUP,0,pLogFont);
}
void  CReportCreator::SetRightUpString(CString sString,LOGFONT * pLogFont)
{
	if(pLogFont==NULL)
	{
		pLogFont=&m_lfFoot;
	}

	AddString(sString,CRect(0,0,10,10),SP_RIGHTUP,0,pLogFont);
}
void  CReportCreator::SetLeftDownString(CString sString,LOGFONT * pLogFont)
{
	if(pLogFont==NULL)
	{
		pLogFont=&m_lfFoot;
	}
	AddString(sString,CRect(0,0,10,10),SP_LEFTDOWN,0,pLogFont);
}
void  CReportCreator::SetRightDownString(CString sString,LOGFONT * pLogFont)
{
	if(pLogFont==NULL)
	{
		pLogFont=&m_lfFoot;
	}

	AddString(sString,CRect(0,0,10,10),SP_RIGHTDOWN,0,pLogFont);
}

CRect  CReportCreator::CalcTableRect()
{
	CReportGrid *pGrid=NULL;
	long i;
	
	double xRight=0;	
    for(i=0;i<m_iColQty;i++)
    {            
        pGrid=GetGrid(0,i);
        if(!pGrid)continue;

		xRight+=pGrid->siWidth ;
    }

	double yDown=0;
    for(i=0;i<m_iRowQty;i++)
    {
	    pGrid=GetGrid(i,0);
        if(!pGrid)continue;
		yDown+=pGrid->siHeight ;
    };

	m_rectTable.left =0;
	m_rectTable.right =xRight;
	m_rectTable.top  =0;
	m_rectTable.bottom =yDown;

	return m_rectTable;
}

bool CReportCreator::AdjustReportSize(CRect rectTarget)
{

	CRect rectTable=CalcTableRect();
	int iXOri=rectTable.left ;
	int iYOri=rectTable.top ;

	rectTable.bottom	+=abs(m_lfFoot .lfHeight );
	rectTable.top		-=abs(m_lfFoot .lfHeight );
	rectTable.top		-=abs(m_lfViceTitle.lfHeight );
	rectTable.top		-=abs(m_lfTitle .lfHeight );


	float fWidthRatio=(float)rectTarget.Width ()/rectTable.Width ();
	float fHeightRatio=(float)rectTarget.Height ()/rectTable.Height ();



	int iWidth=0;
	int iHeight=0;

	/////////////////////////////////////////////
	// Adjust the Strings:
	/////////////////////////////////////////////
	std::list <CReportString *>::iterator p;
	CReportString * par;
	
	CRect rectString;
	LOGFONT logFont;
	float fXDis=0.0;
	float fYDis=0.0;
	float fWidth=0.0;
	float fHeight=0.0;

	// Font Ratio:
	m_fDrawRatio=fWidthRatio;
	if(fHeightRatio<m_fDrawRatio)
	{
		m_fDrawRatio=fHeightRatio;
	}

	/////////////////////////////////////////////
	// Adjust the Grids:
	/////////////////////////////////////////////
    CReportGrid *pGrid=NULL;
	int i=0,j=0;

    for(i=0;i<m_iRowQty;i++)
    {
        for(j=0;j<m_iColQty;j++)
        {            
            pGrid=GetGrid(i,j);
            if(!pGrid)continue;


			pGrid->siWidth  *= m_fDrawRatio;
			pGrid->siHeight *= m_fDrawRatio;

			// The Font In the grid:
			memcpy(&logFont,&pGrid->lfOriFont,sizeof(LOGFONT));
			logFont.lfHeight*= m_fDrawRatio;

			if(abs(logFont.lfHeight)<1)
			{
				logFont.lfHeight=1;
			}


			if(pGrid->psFont !=NULL)
			{
				delete pGrid->psFont ;
				pGrid->psFont=NULL;
			}
			pGrid->psFont  = new CFont;
			pGrid->psFont ->CreateFontIndirect (&logFont);
		}
	}

	// Self Fonts:
	LOGFONT lfString;
	memset(&lfString,0,sizeof(LOGFONT));

	for ( p = m_listStrings.begin(); p!= m_listStrings.end(); ++p )
	{
		par=*p;
		
		if(par->psString ==NULL)continue;

		fXDis=par->rectPos.left -iXOri;
		fYDis=par->rectPos.top  -iYOri;
		fWidth=par->rectPos.Width ();
		fHeight=par->rectPos.Height ();

		if(par->pFont !=NULL)
		{
			par->pFont ->DeleteObject ();
			par->pFont=NULL;
		}
		memcpy(&lfString,&par->lfOriFont,sizeof(LOGFONT));
		lfString.lfHeight*=m_fDrawRatio ;
		if(abs(lfString.lfHeight)<1)
		{
			lfString.lfHeight=1;
		}

		par->pFont=new CFont;
		par->pFont ->CreateFontIndirect (&lfString);
	
		fXDis*=m_fDrawRatio;
		fYDis*=m_fDrawRatio;
		fWidth*=m_fDrawRatio;
		fHeight*=m_fDrawRatio;
		par->rectPos.left   = fXDis+iXOri;
		par->rectPos.top    = fYDis+iYOri;
		par->rectPos.right  = par->rectPos.left + fWidth;
		par->rectPos.bottom = par->rectPos.top  + fHeight;
	}

	////////////////////////////
	//
	////////////////////////////
	return true;
}

CRect CReportCreator:: CalcReportRect()
{
	std::list <CReportString *>::iterator p;
	CReportString * par;
		
	m_rectReport=m_rectTable;
	CRect rectString;
	int iDis=2;


	//////////////////////////////////////
	// Check the characters at the 4 corners:
	//////////////////////////////////////
	int iTopUpper=0;
	int iBottomLower=0;
	int iFontHeight=0;

	CRect rect(m_rectReport);

	for ( p = m_listStrings.begin(); p!= m_listStrings.end(); ++p )
	{
		par=*p;
		
		if(par->psString ==NULL)continue;

		iFontHeight=abs(par->lfOriFont.lfHeight)*m_fDrawRatio;
		if(par->pos == SP_LEFTUP)
		{
			par->rectPos.left = rect.left;
			par->rectPos.right = rect.right ;
			par->rectPos.bottom = rect.top;
			par->rectPos.top= rect.top-iFontHeight-iDis ;
			par->nFormat =DT_SINGLELINE|DT_VCENTER|DT_NOCLIP|DT_LEFT;

			if((iFontHeight+iDis)>iTopUpper)
			{
				iTopUpper=iFontHeight+iDis;
			}
		}
		else if(par->pos == SP_RIGHTUP)
		{
			par->rectPos.left = rect.left;
			par->rectPos.right = rect.right ;
			par->rectPos.bottom = rect.top;
			par->rectPos.top= rect.top-iFontHeight-iDis ;
			par->nFormat =DT_SINGLELINE|DT_VCENTER|DT_NOCLIP|DT_RIGHT;
			if((iFontHeight+iDis)>iTopUpper)
			{
				iTopUpper=iFontHeight+iDis;
			}
		}
		else if(par->pos == SP_LEFTDOWN)
		{
			par->rectPos.left = rect.left;
			par->rectPos.right = rect.right ;
			par->rectPos.top = rect.bottom ;
			par->rectPos.bottom = rect.bottom + iFontHeight+iDis ;
			par->nFormat =DT_SINGLELINE|DT_LEFT|DT_NOCLIP|DT_VCENTER;
			if((iFontHeight+iDis)>iBottomLower)
			{
				iBottomLower=iFontHeight+iDis;
			}
		}
		else if(par->pos == SP_RIGHTDOWN)
		{
			par->rectPos.left = rect.left;
			par->rectPos.right = rect.right ;
			par->rectPos.top = rect.bottom ;
			par->rectPos.bottom = rect.bottom + iFontHeight+iDis ;
			par->nFormat =DT_SINGLELINE|DT_RIGHT|DT_NOCLIP|DT_VCENTER;
			if((iFontHeight+iDis)>iBottomLower)
			{
				iBottomLower=iFontHeight+iDis;
			}
		}
	}

	if(iTopUpper==0)
	{
		iTopUpper=abs(this->m_lfFoot .lfHeight* m_fDrawRatio);
	}
	m_rectReport.top -= iTopUpper;
	m_rectReport.bottom += iBottomLower;

	//////////////////////////////////////
	// Let the title far from the foot title:
	//////////////////////////////////////
	m_rectReport.top-=iTopUpper;

	//////////////////////////////////////
	// Check the Lower Title:
	//////////////////////////////////////
	for ( p = m_listStrings.begin(); p!= m_listStrings.end(); ++p )
	{
		par=*p;
		
		if(par->psString ==NULL)continue;

		
		if(par->pos == SP_SECONDTITLE)
		{
			iFontHeight= abs( par->lfOriFont.lfHeight )*m_fDrawRatio;

			par->rectPos.left = rect.left;
			par->rectPos.right = rect.right ;
			par->rectPos.top =m_rectReport.top- iFontHeight- iDis;
			par->rectPos.bottom = m_rectReport.top ;
			par->nFormat =par->nFormat|DT_RIGHT;

			if(par->rectPos.top<m_rectReport.top)
			{
				m_rectReport.top =par->rectPos.top;
			}

			break;
		}
	}

	//////////////////////////////////////
	// Check the Title:
	//////////////////////////////////////
	for ( p = m_listStrings.begin(); p!= m_listStrings.end(); ++p )
	{
		par=*p;
		
		if(par->psString ==NULL)continue;
		if(par->pos == SP_TITLE)
		{
			iFontHeight= abs( par->lfOriFont.lfHeight )*m_fDrawRatio;

			par->rectPos.left = rect.left;
			par->rectPos.right = rect.right ;
			par->rectPos.top =m_rectReport.top- iFontHeight -iDis;
			par->rectPos.bottom = m_rectReport.top;
			par->nFormat =par->nFormat|DT_RIGHT;

			if(par->rectPos.top<m_rectReport.top)
			{
				m_rectReport.top =par->rectPos.top;
			}

			break;
		}
	}


	//////////////////////////////////////
	// return:
	//////////////////////////////////////
	return m_rectReport;
}

void CReportCreator:: SetTitleLogFont(LOGFONT &lf)
{
	memcpy(&m_lfTitle ,&lf,sizeof(LOGFONT));
	ModifyStringFont(lf,SP_TITLE);
}

void CReportCreator:: SetViceTitleLogFont(LOGFONT &lf)
{
	memcpy(&m_lfViceTitle ,&lf,sizeof(LOGFONT));
	ModifyStringFont(lf,SP_SECONDTITLE);
}

void CReportCreator::SetFootLogFont(LOGFONT &lf)
{
	memcpy(&m_lfFoot ,&lf,sizeof(LOGFONT));
	ModifyStringFont(lf,SP_LEFTUP);
	ModifyStringFont(lf,SP_LEFTDOWN);
	ModifyStringFont(lf,SP_RIGHTUP);
	ModifyStringFont(lf,SP_RIGHTDOWN);
}

void CReportCreator::SetGridFont(LOGFONT &lf)
{
	int i=0,j=0;
	for(i=0;i<m_iRowQty;i++)
	{
		for(j=0;j<m_iColQty;j++)
		{
			CReportGrid *pGrid=GetGrid(i,j);
			pGrid->SetOriFont (&lf);
		}
	}
}

void CReportCreator::SetEdgeLineWidth(int iWidth)
{
	this->m_iEdgeWidth=iWidth;
}

void CReportCreator::SetLineWidth(int iWidth)
{
	int i=0,j=0;
	CReportGrid *pGrid=NULL;
	for(i=0;i<m_iRowQty;i++)
    {
        for(j=0;j<m_iColQty;j++)
        {            
            pGrid=GetGrid(i,j);
            if(!pGrid)continue;

            if(pGrid->lineUp .siWidth !=0)
            {
				pGrid->lineUp .siWidth=iWidth;
            }

            if(pGrid->lineRight .siWidth !=0)            
            {
				pGrid->lineRight .siWidth=iWidth;
            }

            if(pGrid->lineDown .siWidth !=0)
            {
				pGrid->lineDown .siWidth=iWidth;
			}
			
			if(pGrid->lineLeft .siWidth !=0)
			{
				pGrid->lineLeft .siWidth=iWidth;
			}
        }
    };

}

void CReportCreator::ModifyStringFont(LOGFONT &lf, enumStringPos pos)
{
	CReportString * par=NULL;
	std::list <CReportString *>::iterator p;
	LOGFONT lfDraw;

	for ( p = m_listStrings.begin(); p!= m_listStrings.end(); ++p )
	{
		par=*p;
		
		if(par->psString ==NULL||par->pos != pos)
		{
			continue;
		}
			
		memcpy(&par->lfOriFont ,&lf,sizeof(LOGFONT));
		memcpy(&lfDraw ,&lf,sizeof(LOGFONT));
		lfDraw.lfHeight *= m_fDrawRatio;

		if(par->pFont )
		{
			delete par->pFont;
			par->pFont=NULL;
		}
		par->pFont=new CFont;
		par->pFont->CreateFontIndirect (&lfDraw);
	}
}

void CReportCreator::DrawText(CDC		*pDC,
							 CString	s, 
							 CRect		rect,
							 UINT		iFormat)
{
	int i=0;
	int *piMarkPos=new int [s.GetLength()+10];
	char *pcMark=new char[s.GetLength()+10];

	// Mark the top font char:
	int iMarkQty=0;
	bool bFound=false;
	char c,c2;
	do
	{
		bFound=false;
		for(i=0;i<s.GetLength ();i++)
		{
			c=s.GetAt(i);
			if(c=='\1')
			{
				s.Delete(i); 
				piMarkPos[iMarkQty]=i;
				c2=s.GetAt(i);
				pcMark[iMarkQty]=c2;
				s.Delete (i);
				s.Insert(i," ");
				iMarkQty++;
				bFound=true;
				break;
			}            
		}
	}while(bFound);

	//////////////////////////////
	//
	//////////////////////////////
	UINT iFormat2=iFormat|DT_CALCRECT ;
	CRect rectBack=rect;
	pDC->DrawText(s,&rectBack,iFormat2); // Do NOT Draw in fact.
	if(iFormat&DT_CENTER)
	{
		int iMove=(rect.Width()-rectBack.Width())/2;
		rectBack.left +=iMove;
		rectBack.right +=iMove;
	}	
	else if(iFormat&DT_RIGHT)
	{
		int iMove=(rect.Width()-rectBack.Width());
		rectBack.left +=iMove;
		rectBack.right +=iMove;
	}	

	pDC->DrawText(s,&rect,iFormat);


	LOGFONT lf;
	CFont font;
	font.CreateFont( 12, 0, 0, 0, FW_NORMAL,
					 FALSE, FALSE, FALSE, ANSI_CHARSET,
					 OUT_TT_PRECIS, CLIP_TT_ALWAYS, PROOF_QUALITY,
					 DEFAULT_PITCH, "Arial");
	CFont *pOldFont = pDC->SelectObject (&font);

	pOldFont->GetLogFont (&lf);
	CFont fontSmall;

	lf.lfHeight =abs(lf.lfHeight )*0.7;
	fontSmall.CreateFontIndirect (&lf);
	pDC->SelectObject (pOldFont);
	CSize size;
	for(i=0;i<iMarkQty;i++)
	{
		size=pDC->GetTextExtent (s.Left (piMarkPos[i]));
		pOldFont=pDC->SelectObject (&fontSmall);
		pDC->TextOut (rectBack.left +size.cx ,rectBack.top ,CString(pcMark[i]));
		pDC->SelectObject (pOldFont);
	}


	delete []piMarkPos;
	delete []pcMark;
}

CString CReportCreator::CutString(CString &sOri, int iCutLen)
{

	int iLen=sOri.GetLength ();

	char c;
	if (iCutLen<2)iCutLen=2;

	CString sReturn;
	int iCutChinese=0;
	for(int i=0;i<iLen;i++)
	{
		if(i>=iCutLen&&iCutChinese%2==0)
		{
			break;
		}

		c=sOri.GetAt (i);
		if(c=='\r')
		{
			sReturn+=c;
			break;
		}
		if(c>0xa0||c<0)
		{
			iCutChinese++;
		}
		sReturn+=c;
	}

	sOri=sOri.Mid(sReturn.GetLength ());

	return sReturn;
}

void CReportCreator::SetCharLineLimit(CDC *pDC,int iLimit)
{
	m_iNoteRowLength=iLimit;
	ReCutNoteContent();

	if(!AdjustRowColWidth(pDC))return;
	
	AdjustReportSize(m_rectTargetDraw);

	CalcTableRect();
	CalcReportRect();
}

bool CReportCreator::SetGridFormat(int iRow,int iCol,UINT iFormat )
{
	CReportGrid *pGrid=GetGrid(iRow,iCol);
	if(iFormat==DT_LEFT)
	{
		pGrid->nFormatContent=DT_SINGLELINE|DT_VCENTER|DT_NOCLIP|DT_LEFT;
	}
	else if (iFormat==DT_CENTER)
	{
		pGrid->nFormatContent=DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_NOCLIP;
	}
	else if (iFormat==DT_RIGHT)
	{
		pGrid->nFormatContent=DT_SINGLELINE|DT_RIGHT|DT_VCENTER|DT_NOCLIP;
	}
	else
	{
		pGrid->nFormatContent=iFormat;
	}

	return true;
}


CString CReportCreator::ReSplitStringByWidth(CDC *pDC,
										  CString sContent,
										  int iWidthOri)
{
	int i=0;
	CString sExt;
	char c=0;
	CString sContentReturn="";
	sContent.Remove ('\2');
	int iSrcLen=0;
	int iChineseChar=0;

	int iWidth=iWidthOri*0.9;
	do
	{
		iSrcLen=sContent.GetLength ();
		sExt="";
		iChineseChar=0;
		i=0;
		do 
		{
			i++;
			sExt=sContent.Left(i);
			c=sContent.GetAt (i-1);
			if(c=='\r')break;
			if(c<0||c>0xa0)
			{
				iChineseChar++;
			}
		}while((pDC->GetTextExtent (sExt).cx <iWidth||iChineseChar%2==1)&&i<iSrcLen);

		sContentReturn+=sExt;
		if(sExt.GetLength ()<sContent.GetLength ()&&c!='\r')
		{
			sContentReturn+="\2";
		}

		if(sExt.GetLength ()<=sContent.GetLength ())
		{
			sContent=sContent.Mid (i);
		}

	}while(sContent.GetLength ()>0);
	
	return sContentReturn;
}