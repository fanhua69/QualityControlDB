#pragma once



// CPicShowView view

class CPicShowView : public CScrollView
{
	DECLARE_DYNCREATE(CPicShowView)

protected:
	CPicShowView();           // protected constructor used by dynamic creation
	virtual ~CPicShowView();

public:
	bool ShowPic(CDC *pDC);

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
};


