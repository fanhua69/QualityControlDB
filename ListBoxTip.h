////////////////////////////////////////////////////////////////
// VCKBASE -- June 2001 
// Visual C++ 6.0 环境编译, Windows 98 和 NT 环境运行.
//
#pragma once

#include "subclass.h"
#include "puptext.h"

//////////////////
// Generic tip-handler to display tip for wide text in a list box.
// To use:
// - instantiate one of these for each list box
// - call Init
//
class CListBoxTipHandler : public CSubclassWnd {
protected:
	UINT	m_idMyControl;						 // id of list box control
	UINT	m_nCurItem;							 // index of current item
	BOOL	m_bCapture;							 // whether mouse is captured
	static CPopupText g_wndTip;			 // THE tip window

	// subclass window proc
	virtual LRESULT WindowProc(UINT msg, WPARAM wp, LPARAM lp);

	// virtual fns you can override
	virtual void OnMouseMove(CPoint p);
	virtual BOOL IsRectCompletelyVisible(const CRect& rc);
	virtual UINT OnGetItemInfo(CPoint p, CRect& rc, CString& s);

public:
	CListBoxTipHandler();
	~CListBoxTipHandler();
	static UINT g_nTipTimeMsec;			 // global: msec wait before showing tip
	void Init(CWnd* pListBox);				 // initialize
};
