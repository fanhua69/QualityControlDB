////////////////////////////////////////////////////////////////
// VCKBASE -- June 2001 
// Visual C++ 6.0 环境编译, Windows 98 和 NT 环境运行.
//
#include "stdafx.h"
#include "PupText.h"
#include "ListBoxTip.h"

#define GET_X_LPARAM(lp)   ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)   ((int)(short)HIWORD(lp))

// THE popup tip window
CPopupText CListBoxTipHandler::g_wndTip;

// Timeout before showing long listbox tip -- you can change
UINT CListBoxTipHandler::g_nTipTimeMsec = 100; // .1 sec

CListBoxTipHandler::CListBoxTipHandler()
{
	m_nCurItem=-1;
	m_bCapture = FALSE;
}

CListBoxTipHandler::~CListBoxTipHandler()
{
}

//////////////////
// Install hook. Initialize control ID from list box and create
// (invisible) tip window.
//
void CListBoxTipHandler::Init(CWnd* pListBox)
{
	CSubclassWnd::HookWindow(pListBox);
	m_idMyControl = pListBox->GetDlgCtrlID();
	if (!g_wndTip) {
		// create scroll tip window
		g_wndTip.Create(CPoint(0,0), pListBox, PTS_TRANSPARENT);
	}
}

//////////////////
// "Hook" function traps messages sent to listbox/control. 
//
LRESULT CListBoxTipHandler::WindowProc(UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg) {
	case WM_MOUSEMOVE:
		OnMouseMove(CPoint(GET_X_LPARAM(lp),GET_Y_LPARAM(lp)));
		break;
	case WM_LBUTTONDOWN:
		g_wndTip.Cancel(); // cancel popup text if any
		break;
	}
	return CSubclassWnd::WindowProc(msg, wp, lp);
}

/////////////////
// User moved the mouse.
// Get info for listbox item under mouse:
// If text is too wide to fit in list box, prepare tip window and start
// timer to display it.
//
void CListBoxTipHandler::OnMouseMove(CPoint pt)
{
	CListBox* pListBox = (CListBox*)CWnd::FromHandle(m_hWnd);
	if (!m_bCapture) {
		::SetCapture(m_hWnd);
		m_bCapture = TRUE;
	}

	// Get text and text rectangle for item under mouse
	CString sText;	// item text
	CRect rcText;	// item text rect
	UINT nItem = OnGetItemInfo(pt, rcText, sText);

	if (nItem==-1 || nItem!=m_nCurItem) {
		g_wndTip.Cancel(); // new item, or no item: cancel popup text

		if (nItem>=0 && !IsRectCompletelyVisible(rcText)) {
			// new item, and not wholly visible: prepare popup tip
			CRect rc = rcText;
			pListBox->ClientToScreen(&rc);	// text rect in screen coords
			g_wndTip.SetWindowText(sText);	// set tip text to that of item

			// move tip window over list text
			g_wndTip.SetWindowPos(NULL, rc.left-3, rc.top, rc.Width()+6,
				rc.Height(), SWP_NOZORDER|SWP_NOACTIVATE);

			g_wndTip.ShowDelayed(g_nTipTimeMsec); // show popup text delayed
		}
	}
	m_nCurItem = nItem;

	if (nItem==-1) {
		::ReleaseCapture();
		m_bCapture=FALSE;
	}
}

//////////////////
// Determine if given rectangle is completely visible withing list box
//
BOOL CListBoxTipHandler::IsRectCompletelyVisible(const CRect& rc)
{
	CListBox* pListBox = (CListBox*)CWnd::FromHandle(m_hWnd);
	CRect rcClient;
	pListBox->GetClientRect(&rcClient);
	return rcClient.Width() > rc.Width();
}

//////////////////
// Get info (rectangle and text) for item under point
//
UINT CListBoxTipHandler::OnGetItemInfo(CPoint p, CRect& rc, CString& s)
{
	CListBox* pListBox = (CListBox*)CWnd::FromHandle(m_hWnd);
	ASSERT_VALID(pListBox);
	BOOL bOutside;
	UINT nItem = pListBox->ItemFromPoint(p,bOutside);
	s.Empty();
	if (!bOutside) {
		pListBox->GetText(nItem, s);
		pListBox->GetItemRect(nItem, &rc);
		CFont *pFont = pListBox->GetFont();
		CClientDC dc(pListBox);
		CFont* pOldFont = dc.SelectObject(pFont);
		dc.DrawText(s,&rc,DT_CALCRECT);
		dc.SelectObject(pOldFont);
		return nItem;
	}
	return -1;
}
