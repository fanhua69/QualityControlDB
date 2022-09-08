// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "QCDB.h"

#include "MainFrm.h"
#include "TreeViewDB.h"
#include ".\mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFHMainFrm)

BEGIN_MESSAGE_MAP(CMainFrame, CFHMainFrm)
	ON_WM_CREATE()
	// ȫ�ְ�������
	ON_COMMAND(ID_HELP_FINDER, CFHMainFrm::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFHMainFrm::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFHMainFrm::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFHMainFrm::OnHelpFinder)
	ON_COMMAND(ID_ShowDataFlowHistory, OnShowdataflowhistory)
	ON_UPDATE_COMMAND_UI(ID_ShowDataFlowHistory, OnUpdateShowdataflowhistory)

	ON_COMMAND(ID_ShowLinker, OnShowLinker)
	ON_UPDATE_COMMAND_UI(ID_ShowLinker, OnUpdateShowLinker)

	ON_COMMAND(ID_OutputBar, OnOutputBar)
	ON_UPDATE_COMMAND_UI(ID_OutputBar, OnUpdateOutputBar)


END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	SetMainToolBar(IDR_MAINFRAME);
	
	m_wndOutput.SetDockSide(CBRS_BOTTOM);

	CStringArray array;
	array.Add ("���");
	array.Add ("ʱ��");
	array.Add ("��Դ��ַ");
	array.Add ("��Դ�û�");
	array.Add ("Ŀ���ַ");
	array.Add ("����");
	array.Add ("����");

	m_wndDataFlow.SetColProperty (array);

	array.RemoveAll ();
	array.Add ("״̬");
	array.Add ("��ַ");
	array.Add ("��������");
	array.Add ("��ʼʱ��");
	array.Add ("����ʱ��");
	array.Add ("��������");
	array.Add ("��������");

	m_wndDataLinker.SetColProperty (array);


	m_iShowOneWindow=0;

	GetPar("QCDB_SHOW_ONLY_ONE_INFOWINDOW",m_iShowOneWindow);

	m_bOutBarShowing=true;
	m_bDataFlowShowing=true;
	m_bDataLinkerShowing=true;

	if(m_iShowOneWindow!=0)
	{
		m_bDataFlowShowing=false;
		m_bDataLinkerShowing=false;
	}
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFHMainFrm::OnCreate(lpCreateStruct) == -1)
		return -1;

	
	// The output bar:
	if (!m_wndDataFlow.Create(this, ID_VIEW_DATAFLOW,
		_T("��������Ϣ"), CSize(200,100), CBRS_BOTTOM))   //CBRS_BOTTOM
	{
		TRACE0("Failed to create dialog bar m_wndOutput\n");
		return -1;		// fail to create
	}
	//m_wndDataFlow.SetMenuID(IDR_POPUP);
	m_wndDataFlow.EnableDockingOnSizeBar(CBRS_ALIGN_ANY);
	DockSizeBar(&m_wndDataFlow);
	if(!m_bDataFlowShowing)
	{
		m_wndDataFlow.ModifyStyle(WS_VISIBLE,0);
	}

	//FloatControlBar(&m_wndDataFlow, CPoint(200,200));

	// The output bar:
	if (!m_wndDataLinker.Create(this, ID_VIEW_DATALINKER,
		_T("�����������Ϣ"), CSize(200,100), CBRS_BOTTOM))
	{
		TRACE0("Failed to create dialog bar m_wndDataLinker\n");
		return -1;		// fail to create
	}
	//m_wndOutput.SetMenuID(IDR_POPUP);
	m_wndDataLinker.EnableDockingOnSizeBar(CBRS_ALIGN_ANY);
	
	DockSizeBar(&m_wndDataLinker);	
	//FloatControlBar(&m_wndDataLinker, CPoint(300,300));
	if(!m_bDataLinkerShowing)
	{
		m_wndDataLinker.ModifyStyle(WS_VISIBLE,0);
	}

	m_wndWorkspace.RemoveAllViews();
	m_wndWorkspace.AddView(_T("���ݿ����"),RUNTIME_CLASS(CTreeViewDB),0);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFHMainFrm::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ

	return TRUE;
}


// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFHMainFrm::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFHMainFrm::Dump(dc);
}

#endif //_DEBUG


// CMainFrame ��Ϣ�������
void CMainFrame::OnShowdataflowhistory()
{
    GetPar("QCDB_SHOW_ONLY_ONE_INFOWINDOW",m_iShowOneWindow);

	if(!m_iShowOneWindow)
	{
		OnBarCheck(ID_VIEW_DATAFLOW);
	}
	else
	{
		m_bOutBarShowing=false;
		m_bDataFlowShowing=true;
		m_bDataLinkerShowing=false;

		ShowBar(ID_VIEW_DATAFLOW,m_bDataFlowShowing);
		ShowBar(ID_VIEW_DATALINKER,m_bDataLinkerShowing);
		ShowBar(ID_VIEW_OUTPUTBAR,m_bOutBarShowing);
	}
}

void CMainFrame::OnUpdateShowdataflowhistory(CCmdUI *pCmdUI)
{
    GetPar("QCDB_SHOW_ONLY_ONE_INFOWINDOW",m_iShowOneWindow);

	if(!m_iShowOneWindow)
	{
		pCmdUI->m_nID = ID_VIEW_DATAFLOW;
		pCmdUI->Enable();
		OnUpdateControlBarMenu(pCmdUI);	
	}
	else
	{
		pCmdUI->SetCheck (m_bDataFlowShowing);
	}
}

void CMainFrame::OnShowLinker()
{
    GetPar("QCDB_SHOW_ONLY_ONE_INFOWINDOW",m_iShowOneWindow);

	if(!m_iShowOneWindow)
	{
		OnBarCheck(ID_VIEW_DATALINKER);
	}
	else
	{
		m_bOutBarShowing=false;
		m_bDataFlowShowing=false;
		m_bDataLinkerShowing=true;

		ShowBar(ID_VIEW_DATAFLOW,m_bDataFlowShowing);
		ShowBar(ID_VIEW_DATALINKER,m_bDataLinkerShowing);
		ShowBar(ID_VIEW_OUTPUTBAR,m_bOutBarShowing);
	}

}

void CMainFrame::OnUpdateShowLinker(CCmdUI *pCmdUI)
{
    GetPar("QCDB_SHOW_ONLY_ONE_INFOWINDOW",m_iShowOneWindow);

	if(!m_iShowOneWindow)
	{
		pCmdUI->m_nID = ID_VIEW_DATALINKER;
		pCmdUI->Enable();
		OnUpdateControlBarMenu(pCmdUI);	
	}
	else
	{
		pCmdUI->SetCheck (m_bDataLinkerShowing);
	}
}


void CMainFrame::OnOutputBar() 
{
    GetPar("QCDB_SHOW_ONLY_ONE_INFOWINDOW",m_iShowOneWindow);

	if(!m_iShowOneWindow)
	{
		OnBarCheck(ID_VIEW_OUTPUTBAR);
	}
	else
	{
		m_bOutBarShowing=true;
		m_bDataFlowShowing=false;
		m_bDataLinkerShowing=false;

		ShowBar(ID_VIEW_DATAFLOW,m_bDataFlowShowing);
		ShowBar(ID_VIEW_DATALINKER,m_bDataLinkerShowing);
		ShowBar(ID_VIEW_OUTPUTBAR,m_bOutBarShowing);
	}
}

void CMainFrame::OnUpdateOutputBar(CCmdUI* pCmdUI) 
{
    GetPar("QCDB_SHOW_ONLY_ONE_INFOWINDOW",m_iShowOneWindow);

	if(!m_iShowOneWindow)
	{
		pCmdUI->m_nID = ID_VIEW_OUTPUTBAR;
		pCmdUI->Enable();
		OnUpdateControlBarMenu(pCmdUI);	
	}
	else
	{
		pCmdUI->SetCheck (m_bOutBarShowing);
	}
}
void CMainFrame::ReShowInfoWnd()
{
	GetPar("QCDB_SHOW_ONLY_ONE_INFOWINDOW",m_iShowOneWindow);
	if(m_iShowOneWindow==0)
	{
		m_bOutBarShowing=true;
		m_bDataFlowShowing=true;
		m_bDataLinkerShowing=true;

		m_wndDataFlow.ShowWindow(SW_SHOW);
		m_wndDataLinker.ShowWindow (SW_SHOW);
		m_wndOutput.ShowWindow (SW_SHOW);

		RecalcLayout();
	}
	else
	{
		m_bOutBarShowing=true;
		m_bDataFlowShowing=false;
		m_bDataLinkerShowing=false;
		m_wndDataFlow.ShowWindow(SW_SHOW);
		m_wndDataLinker.ShowWindow (SW_HIDE  );
		m_wndOutput.ShowWindow (SW_HIDE );
		RecalcLayout();

	}


}
void CMainFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	CFHMainFrm::OnUpdateFrameTitle(bAddToTitle);
	if(IsServer())
	{
		SetWindowText ("QCDB-Server");
	}
	else
	{
		SetWindowText ("QCDB-Client");
	}
}
