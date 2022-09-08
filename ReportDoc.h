#pragma once


// CReportDoc document
#include "DlgReportProperty.h"
#include "DataBrowseDoc.h"
class CReportDoc;
#include "fhcglobal.h"

class CDailyReportRecord
{
public:
	CString sLineName;
	int iStartYear;
	int iStartMonth;
	int iStartDay;
	int iEndYear;
	int iEndMonth;   //5
	int iEndDay;
	
	int iShotQty;
	float fKilometer;
	int iRefraction;
	int iMicroSurveyWell;
	int iFirstClass;
	int iSecondClass;
	int iEmptyPoint;
	int iBadPoint;

	int iInspectedShot;
	int iShotValid;
	int iInspectedRcv;
	int iRcvValid;

	int iLineValid;
	int iMonthlyCheck;
	int iDailyCheck;

	int iSurveyMark;
	int iValidSurveyMark;
	int iOnPostInspect;
	int iMemo;

	CString sTags;

	CString sProjectRun;
	CString sProjectWork;
	CString sNextStep;
	CString sProjectSummary;
	CString sMonitor;

	CString sProblem;

	CDailyReportRecord()
	{
		sLineName="";  // 0
		iStartYear=0;
		iStartMonth=0;
		iStartDay=0;
		iEndYear=0;
		iEndMonth=0;   //5
		iEndDay=0;
	
		iShotQty=0;
		fKilometer=0.0;
		iRefraction=0;
		iMicroSurveyWell=0;   // 10
		iFirstClass=0;
		iSecondClass=0;
		iEmptyPoint=0;
		iBadPoint=0;

		iInspectedShot=0;		//15
		iShotValid=0;
		iInspectedRcv=0;
		iRcvValid=0;

		iLineValid=0;
		iMonthlyCheck=0;		//20
		iDailyCheck=0;

		iSurveyMark=0;
		iValidSurveyMark=0;
		iOnPostInspect=0;
		iMemo=0;				//25

		sTags="";
		
		sProjectRun="";
		sProjectWork="";
		sNextStep="";
		sProjectSummary="";		//30

		sMonitor="";			//31

		sProblem="";			//32
	};

	void WriteIntoArray(CStringArray &array)
	{
		array.SetSize (33);
		array.SetAt (0,sLineName );
		array.SetAt (1,vtos(iStartYear ));
		array.SetAt (2,vtos(iStartMonth ));
		array.SetAt (3,vtos(iStartDay ));
		array.SetAt (4,vtos(iEndYear ));
		array.SetAt (5,vtos(iEndMonth ));
		array.SetAt (6,vtos(iEndDay ));
		array.SetAt (7,vtos(iShotQty ));
		array.SetAt (8,vtos(fKilometer ));
		array.SetAt (9,vtos(iRefraction ));
		array.SetAt (10,vtos(iMicroSurveyWell ));
		array.SetAt (11,vtos(iFirstClass ));
		array.SetAt (12,vtos(iSecondClass ));
		array.SetAt (13,vtos(iEmptyPoint ));
		array.SetAt (14,vtos(iBadPoint ));
		array.SetAt (15,vtos(iInspectedShot ));
		array.SetAt (16,vtos(iShotValid ));
		array.SetAt (17,vtos(iInspectedRcv ));
		array.SetAt (18,vtos(iRcvValid ));
		array.SetAt (19,vtos(iLineValid ));
		array.SetAt (20,vtos(iMonthlyCheck ));
		array.SetAt (21,vtos(iDailyCheck ));
		array.SetAt (22,vtos(iSurveyMark ));
		array.SetAt (23,vtos(iValidSurveyMark ));
		array.SetAt (24,vtos(iOnPostInspect ));
		array.SetAt (25,vtos(iMemo ));
		array.SetAt (26,sTags);
		array.SetAt (27,sProjectRun);
		array.SetAt (28,sProjectWork);
		array.SetAt (29,sNextStep);
		array.SetAt (30,sProjectSummary);
		array.SetAt (31,sProblem);
		array.SetAt (32,sMonitor);
	};

	void GetItemNames(CStringArray &arrayNames, CStringArray &arrayTypes)
	{
		arrayNames.SetSize (33);
		arrayTypes.SetSize (33);
		
		for(int i=0;i<33;i++)
		{
			arrayNames.SetAt (i,"TEST");
		}
		arrayTypes.SetAt (0,"CHAR(10)");
		arrayTypes.SetAt (1,"INTEGER");
		arrayTypes.SetAt (2,"INTEGER");
		arrayTypes.SetAt (3,"INTEGER");
		arrayTypes.SetAt (4,"INTEGER");
		arrayTypes.SetAt (5,"INTEGER");
		arrayTypes.SetAt (6,"INTEGER");
		arrayTypes.SetAt (7,"INTEGER");
		arrayTypes.SetAt (8,"FLOAT");
		arrayTypes.SetAt (9,"INTEGER");
		arrayTypes.SetAt (10,"INTEGER");
		arrayTypes.SetAt (11,"INTEGER");
		arrayTypes.SetAt (12,"INTEGER");
		arrayTypes.SetAt (13,"INTEGER");
		arrayTypes.SetAt (14,"INTEGER");
		arrayTypes.SetAt (15,"INTEGER");
		arrayTypes.SetAt (16,"INTEGER");
		arrayTypes.SetAt (17,"INTEGER");
		arrayTypes.SetAt (18,"INTEGER");
		arrayTypes.SetAt (19,"INTEGER");
		arrayTypes.SetAt (20,"INTEGER");
		arrayTypes.SetAt (21,"INTEGER");
		arrayTypes.SetAt (22,"INTEGER");
		arrayTypes.SetAt (23,"INTEGER");
		arrayTypes.SetAt (24,"INTEGER");
		arrayTypes.SetAt (25,"INTEGER");
		arrayTypes.SetAt (26,"NOTE");
		arrayTypes.SetAt (27,"NOTE");
		arrayTypes.SetAt (28,"NOTE");
		arrayTypes.SetAt (29,"NOTE");
		arrayTypes.SetAt (30,"NOTE");
		arrayTypes.SetAt (31,"CHAR(10)");
		arrayTypes.SetAt (32,"NOTE");
	}
};

class CWellProperty
{
public:
	int   iComboQty;
	float fDepth;
	float fDynamite;
	int   iValidOrder;
	int   iQty;

	CWellProperty()
	{
		iComboQty=0;
		fDepth=0.0;
		fDynamite=0.0;
		iValidOrder=0;
		iQty=0;
	};
};

#include "mydate.h"

class CReportDoc : public CDataBrowseDoc
{
	DECLARE_DYNCREATE(CReportDoc)

public:
	CReportDoc();
	virtual ~CReportDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	CString m_sReportName;
	CString m_sProjectNo;
	CString m_sProjectName;
	CString m_sLineName;
	CString m_sLineNo;

	CString m_sBasin;
	CString m_sProspectArea;
	CString m_sProspectAreaShort;
	CString m_sArea;
	CString m_sAreaShort;

	CString m_sReportNumber;

	CString m_sYear;
	CString m_sServer;
	CString m_sCrew;
	CString m_sClient;
	int m_iPrintPage;


	bool m_bIs3D;
	CString m_sDesiLineQty;
	
	CString m_s2DDesiShotQty;
	CString m_s2DDesiFullCover;  // for 2D

	CString m_s3DDesiShotQty;
	CString m_s3DDesignSingleCover;
	CString m_s3DDesiWorkAreaQty;
	CString m_s3DDesiFullCover;  // for 3D

	class CWorkQty
	{
	public:
		int iShotQty;
		float fShotKilometer;
		float fMoney;
		CWorkQty()
		{
			iShotQty=0;
			fShotKilometer=0.0;
			fMoney=0.0;
		};
	};
	CWorkQty m_Client2D;
	CWorkQty m_Client3D;
	CWorkQty m_Server2D;
	CWorkQty m_Server3D;

	CString m_sReportCreator;
	CString m_sReportAuditor;

	CString m_sMonitor;

	int m_iCurrYear;
	int m_iCurrMonth;
	int m_iCurrDay;

	int m_iStartYear;
	int m_iStartMonth;
	int m_iStartDay;

	int m_iEndYear;
	int m_iEndMonth;
	int m_iEndDay;
	
	int m_iStatYear;
	int m_iStatMonth;
	int m_iStatDay;

	int m_iProjectMonth;

	CWellProperty m_CSingleWell[10];
	CWellProperty m_CMultiWell[10];

	enumMonthType m_eMonthType;

	CStringArray m_arrayProject;
	
	CStringArray m_arrayProject1;
	CStringArray m_arrayProject2;
	CStringArray m_arrayProject3;

	CDataBrowseDoc m_docVice;
	CString GetLineName(CString sNo);
	BOOL	GetProjectInfoByNo(CString sProjectNo, CStringArray *pArrayProject=NULL);
	BOOL	GetProjectInfo(CString sProject, CStringArray *pArrayProject=NULL);

protected:

	BOOL GetDataForReport01(CDlgReportProperty &dlg);
	BOOL GetDataForReport02(CDlgReportProperty &dlg);
	BOOL GetDataForReport03(CDlgReportProperty &dlg);
	BOOL GetDataForReport04(CDlgReportProperty &dlg);
	BOOL GetDataForReport05(CDlgReportProperty &dlg);
	BOOL GetDataForReport06(CDlgReportProperty &dlg);
	BOOL GetDataForReport07(CDlgReportProperty &dlg);
	BOOL GetDataForReport08(CDlgReportProperty &dlg);
	BOOL GetDataForReport09(CDlgReportProperty &dlg);
	BOOL GetDataForReport10(CDlgReportProperty &dlg);
	BOOL GetDataForReport11(CDlgReportProperty &dlg);
	BOOL GetDataForReport12(CDlgReportProperty &dlg);
	BOOL GetDataForReport13(CDlgReportProperty &dlg);
	BOOL GetDataForReport14(CDlgReportProperty &dlg);
	BOOL GetDataForReport15(CDlgReportProperty &dlg);
	BOOL GetDataForReport16(CDlgReportProperty &dlg);
	BOOL GetDataForReport17(CDlgReportProperty &dlg);
	BOOL GetDataForReport18(CDlgReportProperty &dlg);
	BOOL GetDataForReport19(CDlgReportProperty &dlg);
	BOOL GetDataForReport20(CDlgReportProperty &dlg);
	BOOL GetDataForReport21(CDlgReportProperty &dlg);
	BOOL GetDataForReport22(CDlgReportProperty &dlg);
	BOOL GetDataForReport23(CDlgReportProperty &dlg);
	BOOL GetDataForReport24(CDlgReportProperty &dlg);
	BOOL GetDataForReport25(CDlgReportProperty &dlg);
	BOOL GetDataForReport26(CDlgReportProperty &dlg);
	BOOL GetDataForReport27(CDlgReportProperty &dlg);
	BOOL GetDataForReport28(CDlgReportProperty &dlg);
	BOOL GetDataForReport29(CDlgReportProperty &dlg);
	BOOL GetDataForReport30(CDlgReportProperty &dlg);

	CString Get2DProjectFullCover(CString sProjectName);
	
protected:
	virtual BOOL OnNewDocument();

	DECLARE_MESSAGE_MAP()
};
