// QCDBView.cpp : CReportView 类的实现
//

#include "stdafx.h"
#include "QCDB.h"
#include "MemDC.h"

#include "ReportDoc.h"
#include "ReportView.h"
#include "DlgReportShowProperty.h"
#include "MyDate.h"
#include "fhcglobal.h"

#include "defines.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CReportView

IMPLEMENT_DYNCREATE(CReportView, CScrollView)

BEGIN_MESSAGE_MAP(CReportView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_ZoomIn, OnZoomin)
	ON_COMMAND(ID_ZoomOut, OnZoomout)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_ZoomFull, OnZoomfull)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_REPORTVIEW_SetShowProperty, OnReportviewSetshowproperty)
	ON_COMMAND(ID_REPORTVIEW_Print, OnReportviewPrint)
END_MESSAGE_MAP()

// CReportView 构造/析构

CReportView::CReportView()
{
	m_iEdgeWidth=50;
	m_menuManager.SetPopupMenu (IDR_ReportView);
}

CReportView::~CReportView()
{
}

BOOL CReportView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	return CScrollView::PreCreateWindow(cs);
}

// CReportView 绘制

void CReportView::OnDraw(CDC* pDC)
{
#ifdef DOG
    CFHApp *pApp=(CFHApp*)AfxGetApp();
    if(!pApp->m_dog .m_bCalcChecked )
    {
        return;
    }
    else
    {
        pApp->m_dog.WriteRand (0);
    }

#endif

	m_rc.Draw (pDC);
}


// CReportView 打印

BOOL CReportView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	m_rectScreen=m_rc.GetTargetDrawRect ();
	
	pInfo->SetMinPage (1);
	pInfo->SetMaxPage (1);

	BOOL bSuccess=DoPreparePrinting(pInfo);
	if(!bSuccess)return false;

	return true;

}

void CReportView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	int iEdge=100;
	int iWidth=pDC->GetDeviceCaps(PHYSICALWIDTH);

	int iOffSetX=pDC->GetDeviceCaps(PHYSICALOFFSETX);
	int iOffSetY=pDC->GetDeviceCaps(PHYSICALOFFSETY);

	CRect rect(iOffSetX+iEdge,
				iOffSetY+iEdge,
				iWidth-iOffSetX*3-iEdge,
				100000);

	m_rc.SetDrawRect (pDC,&rect);

	pDC->Rectangle (&rect);

	CScrollView::OnBeginPrinting (pDC,pInfo);

}

void CReportView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	SetDrawRect(m_rectScreen.Width (),m_rectScreen.Height ());
}


// CReportView 诊断

#ifdef _DEBUG
void CReportView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CReportView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CReportDoc* CReportView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CReportDoc)));
	return (CReportDoc*)m_pDocument;
}
#endif //_DEBUG


// CReportView 消息处理程序

void CReportView::OnInitialUpdate()
{
	SetScrollSizes(MM_TEXT,CSize(2000,1000));

	CScrollView::OnInitialUpdate();

	SetDrawRect(2000,1000);

}

void CReportView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();

	m_rc.RemoveAllStrings();

	CStringArray array;
	GetReportNames(array);

	int iTableOrder=-1;
	for(int i=0;i<array.GetCount ();i++)
	{
		if(pDoc->m_sReportName==array.GetAt (i))
		{
			iTableOrder=i;
			break;
		}
	}

	if(iTableOrder==-1)
	{
		ASSERT(false);
		TRACEERROR("没有这个表名字:"+pDoc->m_sReportName);
		return;
	}

	iTableOrder++;

	switch (iTableOrder)
	{
	case 1:
		return CreateReport01();
	case 2:
		return CreateReport02();
	case 3:
		return CreateReport03();
	case 4:
		return CreateReport04();
	case 5:
		return CreateReport05();
	case 6:
		return CreateReport06();
	case 7:
		return CreateReport07();
	case 8:
		return CreateReport08();
	case 9:
		return CreateReport09();
	case 10:
		return CreateReport10();
	case 11:
		return CreateReport11();
	case 12:
		return CreateReport12();
	case 13:
		return CreateReport13();
	case 14:
		return CreateReport14();
	case 15:
		return CreateReport15();
	case 16:
		return CreateReport16();
	case 17:
		return CreateReport17();
	case 18:
		return CreateReport18();
	case 19:
		return CreateReport19();
	case 20:
		return CreateReport20();
	case 21:
		return CreateReport21();
	case 22:
		return CreateReport22();
	case 23:
		return CreateReport23();
	case 24:
		return CreateReport24();
	case 25:
		return CreateReport25();
	case 26:
		return CreateReport26();
	case 27:
		return CreateReport27();
	case 28:
		return CreateReport28();
	case 29:
		return CreateReport29();
	case 30:
		return CreateReport30();
	default:
		ASSERT(false);
		TRACEERROR("没有建立这个表:"+pDoc->m_sReportName);
		return;
	}
}

void CReportView::FormatString(CString &s, int iSmallNumber)
{
    double lf;
	sscanf((LPCTSTR)s,"%lf",&lf);
	s.Format ("%0.3lf",lf);
}

void CReportView::OnZoomin()
{
	CSize size;
	size.cx=m_totalLog .cx*1.1;
	size.cy=m_totalLog .cy*1.1;

	while(!SetDrawRect(size.cx,size.cy))
	{
		size.cx*=1.1;
		size.cy*=1.1;
	}

	SetScrollSizes(MM_TEXT,size);
	Invalidate();
}

void CReportView::OnZoomout()
{
	CSize size;
	size.cx=m_totalLog .cx/1.1;
	size.cy=m_totalLog .cy/1.1;

	int iLimit=m_iEdgeWidth*2+100;
	if(size.cx<iLimit)
	{
		size.cx=iLimit;
	}
	if(size.cy<iLimit)
	{
		size.cy=iLimit;
	}

	if(SetDrawRect(size.cx,size.cy))
	{
		SetScrollSizes(MM_TEXT,size);
		Invalidate();
	}	
}

void CReportView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	OnPrepareDC(&dc);
	CMemDC memDC(&dc,this);	

	OnDraw(&memDC);

}

BOOL CReportView::OnEraseBkgnd(CDC* pDC)
{
	return false;
}

void CReportView::OnZoomfull()
{
	CRect rect;
	GetClientRect(&rect);

	CSize size(rect.Width (),rect.Height ());
	if(SetDrawRect(size.cx,size.cy))
	{
		SetScrollSizes(MM_TEXT,size);
		Invalidate();
	}
}

bool CReportView::SetDrawRect(int iWidth,int iHeight)
{

	CClientDC dc(this);

	CRect rect(m_iEdgeWidth,
				m_iEdgeWidth,
				iWidth-m_iEdgeWidth,
				iHeight-m_iEdgeWidth);

	return m_rc.SetDrawRect (&dc,&rect);
}
void CReportView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class

	CScrollView::OnPrint(pDC, pInfo);
}

void CReportView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	CScrollView::OnPrepareDC(pDC, pInfo);

	// See is Got:
	/*
	pDC->SetMapMode (MM_ANISOTROPIC);
	CSize size(100,10);
	pDC->SetWindowExt (size);

	int x=pDC->GetDeviceCaps (LOGPIXELSX);
	int y=pDC->GetDeviceCaps (LOGPIXELSY);

	long xExt=(long)size.cx*x/96;
	long yExt=(long)size.cy*y/96;

	pDC->SetViewportExt (xExt,yExt);
	*/

}

void CReportView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView)
{
	// TODO: Add your specialized code here and/or call the base class

	CScrollView::OnEndPrintPreview(pDC, pInfo, point, pView);
}

void CReportView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu *pMenu=m_menuManager.GetPopupMenu();
	if(!pMenu)return;

	m_menuManager.ShowPopupMenu(pMenu,point,this);

}

void CReportView::OnReportviewSetshowproperty()
{
	CDlgReportShowProperty dlg;
	if(dlg.DoModal ()==IDCANCEL)return;

	LOGFONT lf;
	dlg.GetTitleLogFont (lf);
	m_rc.SetTitleLogFont (lf);

	dlg.GetViceTitleLogFont (lf);
	m_rc.SetViceTitleLogFont (lf);

	dlg.GetFootLogFont (lf);
	m_rc.SetFootLogFont (lf);

	dlg.GetContentLogFont (lf);
	m_rc.SetGridFont (lf);

	CClientDC dc(this);

	m_rc.SetLineWidth(dlg.GetLineWidth ());
	m_rc.SetEdgeLineWidth(dlg.GetEdgeLineWidth ());
	m_rc.SetCharLineLimit(&dc,dlg.m_iNoteCharLineLimit );
	m_rc.SetMarkPicWidth(dlg.m_iMarkPicWidth );
	m_rc.SetMarkPic (dlg.GetMarkPicName ());

	m_rc.SetDrawRect (&dc,NULL);

	Invalidate();

}

void CReportView::OnReportviewPrint()
{
	// TODO: Add your command handler code here
}


