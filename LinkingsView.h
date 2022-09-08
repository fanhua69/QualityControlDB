#pragma once


// CLinkingsView view
#include "ctrlext.h"
#include "afxcview.h"
#include "PopupMenuManager.h"

class CLinkingsView : public CListView
{
	DECLARE_DYNCREATE(CLinkingsView)

protected:
	CLinkingsView();           // protected constructor used by dynamic creation
	virtual ~CLinkingsView();

	CPopupMenuManager m_menu;

	bool m_bShowAllParents;
	bool m_bShowLinkingParents;
	bool m_bShowAllChildren;
	bool m_bShowLinkingChildren;
	
public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);

	afx_msg void OnLinkerShowallparents();
	afx_msg void OnUpdateLinkerShowallparents(CCmdUI *pCmdUI);
	afx_msg void OnLinkerShowLinkingparents();
	afx_msg void OnUpdateLinkerShowLinkingparents(CCmdUI *pCmdUI);
	afx_msg void OnLinkerShowallChildren();
	afx_msg void OnUpdateLinkerShowallChildren(CCmdUI *pCmdUI);
	afx_msg void OnLinkerShowLinkingChildren();
	afx_msg void OnUpdateLinkerShowLinkingChildren(CCmdUI *pCmdUI);
};


