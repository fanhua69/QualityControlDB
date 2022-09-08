// LinkingsView.cpp : implementation file
//

#include "stdafx.h"
#include "QCDB.h"
#include "LinkingsView.h"
#include "ProgDlg.h"
#include "DataTransDoc.h"
#include "resource.h"

// CLinkingsView

IMPLEMENT_DYNCREATE(CLinkingsView, CListView)

CLinkingsView::CLinkingsView()
{
	m_bShowAllParents=false;
	m_bShowLinkingParents=false;
	m_bShowAllChildren=false;
	m_bShowLinkingChildren=true;

	m_menu.SetPopupMenu (IDR_Menu_LinkerView);
}

CLinkingsView::~CLinkingsView()
{
}

BEGIN_MESSAGE_MAP(CLinkingsView, CListView)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_Linker_ShowAllParents, OnLinkerShowallparents)
	ON_UPDATE_COMMAND_UI(ID_Linker_ShowAllParents, OnUpdateLinkerShowallparents)
	ON_COMMAND(ID_Linker_ShowLinkingParents, OnLinkerShowLinkingparents)
	ON_UPDATE_COMMAND_UI(ID_Linker_ShowLinkingParents, OnUpdateLinkerShowLinkingparents)
	ON_COMMAND(ID_Linker_ShowAllChildren, OnLinkerShowallChildren)
	ON_UPDATE_COMMAND_UI(ID_Linker_ShowAllChildren, OnUpdateLinkerShowallChildren)
	ON_COMMAND(ID_Linker_ShowLinkingChildren, OnLinkerShowLinkingChildren)
	ON_UPDATE_COMMAND_UI(ID_Linker_ShowLinkingChildren, OnUpdateLinkerShowLinkingChildren)
END_MESSAGE_MAP()


// CLinkingsView drawing

void CLinkingsView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CLinkingsView diagnostics

#ifdef _DEBUG
void CLinkingsView::AssertValid() const
{
	CListView::AssertValid();
}

void CLinkingsView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG


// CLinkingsView message handlers

void CLinkingsView::OnInitialUpdate()
{
	CListCtrlEx &ctlList=(CListCtrlEx &)GetListCtrl();

	ctlList.AddColumn("用户名   ",0);
	ctlList.AddColumn("IP地址   ",1);
	ctlList.AddColumn("端口号   ",2);
	ctlList.AddColumn("开始时间 ",3);
	ctlList.AddColumn("结束时间 ",4);

	CListView::OnInitialUpdate();
}

void CLinkingsView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	
	CProgressDlg dlg;
	dlg.Create();
	dlg.SetStatus("正在加载用户数据...");
	
	// TODO: Add your specialized code here and/or call the base class
	CDataTransDoc *pDoc=(CDataTransDoc *)GetDocument();
	CListCtrlEx &ctrlList=(CListCtrlEx &)GetListCtrl();

	CString sItem;
	ctrlList.DeleteAllItems();

	// Add the survey data body:
	CPtrList *pList=NULL;
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();

	if(pDoc->m_bShowFathers)
	{
		pList=&pApp->m_dt.m_FathersList ;
	}
	else
	{
		pList=&pApp->m_dt.m_ChildrenList ;
	}

	int iLinkQty=pList->GetCount ();
	dlg.SetRange(0,iLinkQty);

	POSITION pos=pList->GetHeadPosition ();
	CConnection *pConn=NULL;
	CString sTime;
	CTime timeLinked;
	int iOrder=0;
	while(pos)
	{
		if(iOrder%100==0)
		{
			dlg.SetPos(iOrder);
		}

		pConn=(CConnection *)pList->GetNext (pos);

		ctrlList.AddItem(iOrder,0,pConn->m_sName );
		ctrlList.AddItem(iOrder,1,pConn->m_sIP);
		ctrlList.AddItem(iOrder,2,pConn->m_iPort );
		sTime=pConn->m_timeStart .Format ("%Y%m%d%H%M%S");
		ctrlList.AddItem(iOrder,3,sTime);
		sTime=pConn->m_timeEnd .Format ("%Y%m%d%H%M%S");
		ctrlList.AddItem(iOrder,4,sTime);

		iOrder++;
	}

	dlg.DestroyWindow();
}

int CLinkingsView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style |= LVS_REPORT;
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;

}

void CLinkingsView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	m_menu.ShowPopupMenu (m_menu.GetPopupMenu(),point,pWnd);
}

void CLinkingsView::OnLinkerShowallparents()
{
	m_bShowAllParents=true;
	m_bShowLinkingParents=false;
	m_bShowAllChildren=false;
	m_bShowLinkingChildren=false;
}

void CLinkingsView::OnUpdateLinkerShowallparents(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck (m_bShowAllParents);
}
void CLinkingsView::OnLinkerShowLinkingparents()
{
	m_bShowAllParents=false;
	m_bShowLinkingParents=true;
	m_bShowAllChildren=false;
	m_bShowLinkingChildren=false;
}

void CLinkingsView::OnUpdateLinkerShowLinkingparents(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck (m_bShowLinkingParents);
}


void CLinkingsView::OnLinkerShowallChildren()
{
	m_bShowAllParents=false;
	m_bShowLinkingParents=false;
	m_bShowAllChildren=true;
	m_bShowLinkingChildren=false;
}

void CLinkingsView::OnUpdateLinkerShowallChildren(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck (m_bShowAllChildren);
}

void CLinkingsView::OnLinkerShowLinkingChildren()
{
	m_bShowAllParents=false;
	m_bShowLinkingParents=false;
	m_bShowAllChildren=false;
	m_bShowLinkingChildren=true;
}

void CLinkingsView::OnUpdateLinkerShowLinkingChildren(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck (m_bShowLinkingChildren);
}
