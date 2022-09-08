// PicShowView.cpp : implementation file
//

#include "stdafx.h"
#include "QCDB.h"
#include "PicShowView.h"
#include "FHImage.h"
#include ".\picshowview.h"
#include "MemDC.h"

// CPicShowView

IMPLEMENT_DYNCREATE(CPicShowView, CScrollView)

CPicShowView::CPicShowView()
{

}

CPicShowView::~CPicShowView()
{
}


BEGIN_MESSAGE_MAP(CPicShowView, CScrollView)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CPicShowView drawing

void CPicShowView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CPicShowView::OnDraw(CDC* pDC)
{
	if(!ShowPic(pDC))
    {
	    CFont font;
	    font.CreateFont(32, 0, 0, 0, 0, FALSE, FALSE, 0,
		    ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		    DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"ËÎÌå"); //Times New Roman"); //Arial;

	    CFont *pOldFont=pDC->SelectObject (&font);

	    CString s="Í¼Æ¬ÏÔÊ¾Çø";
	    CRect rect;
	    GetClientRect(&rect);
        pDC->DrawText(s,rect,DT_SINGLELINE|DT_VCENTER|DT_CENTER|DT_NOCLIP);

	    pDC->SelectObject (pOldFont);
    }
}


// CPicShowView diagnostics

#ifdef _DEBUG
void CPicShowView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CPicShowView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG


// CPicShowView message handlers


bool CPicShowView::ShowPic(CDC *pDC)
{
	CDataBrowseDoc* pDoc = (CDataBrowseDoc*)GetDocument();

	if(pDoc->m_sBigPicName =="")return false;

	if(!pDoc->m_bDrawBigPic)return false;

	SetScrollSizes(MM_TEXT,CSize(	pDoc->m_iBigPicWidth +2*pDoc->m_iBigPicOffsetX,
									pDoc->m_iBigPicHeight+2*pDoc->m_iBigPicOffsetY));

	CFHImage bimage;
	HRESULT hr=bimage.Load (pDoc->m_sBigPicName);
	if(hr!=E_FAIL)
	{
		CRect rectPic(	CPoint(	pDoc->m_iBigPicOffsetX ,
								pDoc->m_iBigPicOffsetY ),	
						CSize(	pDoc->m_iBigPicWidth ,
								pDoc->m_iBigPicHeight ));

		
		bimage.Show(pDC ,
					rectPic,
					pDoc->m_bBigPicKeepRatio );

		rectPic.top = rectPic.bottom +40;

        CFont font;
        font.CreateFont(32, 0, 0, 0, 0, FALSE, FALSE, 0,
            ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"ËÎÌå"); //Times New Roman"); //Arial;

        CFont *pOldFont=pDC->SelectObject (&font);

		pDC->DrawText("Í¼Æ¬ÏÔÊ¾Çø",rectPic,DT_SINGLELINE|DT_VCENTER|DT_CENTER|DT_NOCLIP);
        pDC->SelectObject (pOldFont);


		return true;
	}
	else
	{
		return false;
	}

}


BOOL CPicShowView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return false;
}

void CPicShowView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	

	OnPrepareDC(&dc);
	CMemDC memDC(&dc,this);	

	OnDraw(&memDC);


}