// QCDBView.h : CReportView 类的接口
//


#pragma once

#include "ReportCreator.h"
#include "ReportDoc.h"
#include "PopupMenuManager.h"
#include "MyDate.h"

class CReportView : public CScrollView
{
protected: // 仅从序列化创建
	CReportView();
	DECLARE_DYNCREATE(CReportView)

	CReportCreator m_rc;
	CRect m_rectScreen;

	CPopupMenuManager m_menuManager;

	void CreateReport01();
	void CreateReport02();
	void CreateReport03();
	void CreateReport04();
	void CreateReport05();
	void CreateReport06();
	void CreateReport07();
	void CreateReport07_1();
	void CreateReport07_2();
	void CreateReport07_3();
	void CreateReport08();
	void CreateReport09();
	void CreateReport10();
	void CreateReport11();
	void CreateReport12();
	void CreateReport13();
	void CreateReport14();
	void CreateReport15();
	void CreateReport16();
	void CreateReport17();
	void CreateReport18();
	void CreateReport19();
	void CreateReport20();
	void CreateReport21();
	void CreateReport22();
	void CreateReport23();
	void CreateReport24();
	void CreateReport25();
	void CreateReport26();
	void CreateReport27();
	void CreateReport28();
	void CreateReport29();
	void CreateReport30();


	void FormatString(CString &s, int iSmallNumber);

	// For report 13:
	void SetPersonData(	CReportDoc	*pDoc,
						int			iPostOrder,
						CString		sPostName,
						int			&iStartRow);

	void SetRowData(	CString		sName, 
						CString		sPostioned,
						CDataBrowseDoc *pDoc,
						int			iRow);

	// For report 14:
	void SetInstData(	CReportDoc	*pDoc,
						int			iPostOrder,
						CString		sPostName,
						int			&iStartRow);

	// for report 18:
	void CheckWellKindQty(	CDataBrowseDoc *pDoc,
							CWellProperty  *pSingleWell,
							CWellProperty  *pMultiWell,
							int &iSingleWellKindQty,
							int &iMultiWellKindQty);

	CString GetChineseNumber(int i);
	int GetFinishedShotQty(	CDataBrowseDoc *pDoc,
							CString sLineNo,
							CWellProperty *pSSP,
							CWellProperty *pMSP,
							int &iHVLQty,
							CString &sNote,
							CString &sMonitor);

	// For report 19:
	class CClassify
	{
	public:
		int iInitFirst;
		int iInitSecond;
		int iInitBad;
		int iInitBlank;

		int iReFirst;
		int iReSecond;
		int iReBad;
		int iReBlank;

		int iRefTotal;
		int iRefValid;
		int iMicroWellTotal;
		int iMicroWellValid;

		CString sNote;

		CClassify()
		{
			Reset();
		};

		void Reset()
		{
			iInitFirst= iInitSecond=iInitBad=iInitBlank=0;
			iReFirst=iReSecond=iReBad=iReBlank=0;
			iRefTotal=iRefValid=iMicroWellTotal=iMicroWellValid=0;
			sNote="";
		};
	};

	int GetClassify(CDataBrowseDoc *pDoc,
					CString sLineNo,
					CClassify *pClassify,
					CString &sMonitor);
	
	// For report 25: 
	class CMonthStat
	{
	public:
		CMyDate dateMonth;
		CMyDate dateStart;
		CMyDate dateEnd;
		CMyDate dateStartWork;
		CMyDate dateEndWork;

		int iFinishedShot;
		int iNaturalDay;
		int iWorkDay;
		int iCheckDay;
		int iNaturalStandByDay;
		int iOtherStandByDay;

		float fDrillDepth;
		int iRefQty;
		int iMicroWellLogQty;
		int iMaxShot;
		int iMinShot;

		float fDirectCost;
		float fIndirectCost;

		CString sNote;

		CMonthStat()
		{
			iFinishedShot=0;
			iWorkDay=0;
			iNaturalDay=0;
			iCheckDay=0;
			iNaturalStandByDay=0;
			iOtherStandByDay=0;

			fDrillDepth=0.0;
			iRefQty=0;
			iMicroWellLogQty=0;
			iMaxShot=0;
			iMinShot=0;

			fDirectCost=0.0;
			fIndirectCost=0.0;

			sNote="";
		};
	};


	// For report 26:
	class CConsumeStat
	{
	public:
		float fIn;
		float fOut;
		float fConsumeShot;
		float fConsumeRef;
		float fConsumeOther;

		CConsumeStat()
		{
			memset(this,0,sizeof(CConsumeStat));
		};
	};

// 属性
public:
	CReportDoc* GetDocument() const;

	bool SetDrawRect(int iWidth,int iHeight);
	int m_iEdgeWidth;


// 操作
public:

// 重写
	public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CReportView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg void OnZoomin();
	afx_msg void OnZoomout();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnZoomfull();
protected:
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
protected:
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnReportviewSetshowproperty();
	afx_msg void OnReportviewPrint();
};

#ifndef _DEBUG  // QCDBView.cpp 的调试版本
inline CReportDoc* CReportView::GetDocument() const
   { return reinterpret_cast<CReportDoc*>(m_pDocument); }
#endif

