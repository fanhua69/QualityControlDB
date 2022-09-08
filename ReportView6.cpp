#include "stdafx.h"
#include "QCDB.h"
#include "MemDC.h"

#include "ReportDoc.h"
#include "ReportView.h"
#include "DlgReportShowProperty.h"
#include "MyDate.h"
#include "fhcglobal.h"

#include "templates.h"

//  For Table 26:
class CDateRecord
{
public:
	CMyDate date;
	int iRecordOrder;

	bool operator > (CDateRecord &other)
	{
		return date>other.date;
	};

    bool operator < (CDateRecord &other)
    {
        return date<other.date;
    };
};


///////////////////////////////////////////////////////////
//��̽������Ŀըҩ���׹ܣ��գ�ʹ�����ͳ�Ʊ�
//��0301�������ձ�  ��26
///////////////////////////////////////////////////////////
void CReportView::CreateReport26()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,n;
	CMyDate date;
	CStringArray *pRecord=NULL;
	CString sLine;

	float fIn=0.0,fOut=0.0;
	CConsumeStat stProjectLG,stProjectZY;
	CConsumeStat stMonthLG,stMonthZY;

	int iStartRecord=0;

	/////////////////////////////////////////////////
	// �����棺
	/////////////////////////////////////////////////
	int iRecordQty=pDoc->GetRecordQty ();

	CDateRecord *pDateRecord=new CDateRecord[iRecordQty+2];

	CStringArray arrayMonitor;
	CMyDate dateStart;
	
	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
        pDateRecord[i].date.Set(pRecord->GetAt (4),pRecord->GetAt (5),pRecord->GetAt (6));
	    pDateRecord[i].iRecordOrder=i;
	}
	
	Sort(pDateRecord,iRecordQty);


	dateStart.Set(pDoc->m_iStartYear ,pDoc->m_iStartMonth ,pDoc->m_iStartDay );

	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (pDateRecord[i].iRecordOrder);
        if(pDateRecord[i].date>=dateStart)
		{
			iStartRecord=i;
			break;
		}
		stProjectLG.fIn				+=stof(pRecord->GetAt(7));
		stProjectLG.fOut			+=stof(pRecord->GetAt(8));
		stProjectLG.fConsumeShot	+=stof(pRecord->GetAt(9));
		stProjectLG.fConsumeRef		+=stof(pRecord->GetAt(10));
		stProjectLG.fConsumeOther	+=stof(pRecord->GetAt(11));

		stProjectZY.fIn				+=stof(pRecord->GetAt(12));
		stProjectZY.fOut			+=stof(pRecord->GetAt(13));
		stProjectZY.fConsumeShot	+=stof(pRecord->GetAt(14));
		stProjectZY.fConsumeRef		+=stof(pRecord->GetAt(15));
		stProjectZY.fConsumeOther	+=stof(pRecord->GetAt(16));
	}

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	int iValidRecord=iRecordQty-iStartRecord;
	m_rc.SetGridQty (iValidRecord+4,16);

	m_rc.CombineGrid (0,1,0,0);
	m_rc.CombineGrid (0,0,1,7);
	m_rc.CombineGrid (0,0,8,14);
	m_rc.CombineGrid (0,1,15,15);


	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("%s��̽������Ŀըҩ���׹ܣ��գ�ʹ�����ͳ�Ʊ�",pDoc->m_sProjectName  );
	m_rc.SetTitle (s);	

    s="̽����"+pDoc->m_sProspectArea +"         Ͷ�ʷ���"
		      +pDoc->m_sClient +"          ��ҵ����"
			  +pDoc->m_sServer +pDoc->m_sCrew +"��";
    m_rc.SetLeftUpString (s);

	m_rc.SetGridContent (0,0,"����");
	m_rc.SetGridContent (0,1,"�� �� ʹ �� �� ��");
	m_rc.SetGridContent (0,8,"ը ҩ ʹ �� �� ��");
	m_rc.SetGridContent (1,1,"���\r����");
	m_rc.SetGridContent (1,2,"����\r����");
	m_rc.SetGridContent (1,3,"���\r����");
	m_rc.SetGridContent (1,4,"����\r����");
	m_rc.SetGridContent (1,5,"����\r����");
	m_rc.SetGridContent (1,6,"���\r����");
	m_rc.SetGridContent (1,7,"����\r����");
	m_rc.SetGridContent (1,8,"���\r����");
	m_rc.SetGridContent (1,9,"����\r����");
	m_rc.SetGridContent (1,10,"���\r����");
	m_rc.SetGridContent (1,11,"����\r����");
	m_rc.SetGridContent (1,12,"����\r����");
	m_rc.SetGridContent (1,13,"���\r����");
	m_rc.SetGridContent (1,14,"����\r����");
	m_rc.SetGridContent (1,15,"��ע");
	m_rc.SetGridContent (iValidRecord+2,0,"���ºϼ�");
	m_rc.SetGridContent (iValidRecord+3,0,"��Ŀ�ۼ�");

	int iRow=0;
	float fConsumeDP=0.0,fConsumeBC=0.0,fConsumeQT=0.0,fConsume=0.0;
	for(i=iStartRecord;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (pDateRecord[i].iRecordOrder);

		iRow=i-iStartRecord+2;

		// �׹�:
		m_rc.SetGridContent (iRow,0,pDateRecord[i].date.GetDateString ());
		
		stProjectLG.fIn				+=stof(pRecord->GetAt(7));
		stProjectLG.fOut			+=stof(pRecord->GetAt(8));
		stProjectLG.fConsumeShot	+=stof(pRecord->GetAt(9));
		stProjectLG.fConsumeRef		+=stof(pRecord->GetAt(10));
		stProjectLG.fConsumeOther	+=stof(pRecord->GetAt(11));

		stMonthLG.fIn				+=stof(pRecord->GetAt(7));
		stMonthLG.fOut				+=stof(pRecord->GetAt(8));
		stMonthLG.fConsumeShot		+=stof(pRecord->GetAt(9));
		stMonthLG.fConsumeRef		+=stof(pRecord->GetAt(10));
		stMonthLG.fConsumeOther		+=stof(pRecord->GetAt(11));

		m_rc.SetGridContent (iRow,1,pRecord->GetAt(7));
		m_rc.SetGridContent (iRow,2,pRecord->GetAt(8));
		m_rc.SetGridContent (iRow,3,vtos(stProjectLG.fIn -stProjectLG.fOut ));

		fConsumeDP=stof(pRecord->GetAt (9));
		fConsumeBC=stof(pRecord->GetAt (10));
		fConsumeQT=stof(pRecord->GetAt (11));
		fConsume=fConsumeDP+fConsumeBC+fConsumeQT;

		m_rc.SetGridContent (iRow,4,vtos(fConsume,1));
		m_rc.SetGridContent (iRow,5,pRecord->GetAt (9));
		m_rc.SetGridContent (iRow,6,pRecord->GetAt (10));
		m_rc.SetGridContent (iRow,7,pRecord->GetAt (11));


		// ըҩ:
		stProjectZY.fIn				+=stof(pRecord->GetAt(12));
		stProjectZY.fOut			+=stof(pRecord->GetAt(13));
		stProjectZY.fConsumeShot	+=stof(pRecord->GetAt(14));
		stProjectZY.fConsumeRef		+=stof(pRecord->GetAt(15));
		stProjectZY.fConsumeOther	+=stof(pRecord->GetAt(16));
		
		stMonthZY.fIn				+=stof(pRecord->GetAt(12));
		stMonthZY.fOut				+=stof(pRecord->GetAt(13));
		stMonthZY.fConsumeShot		+=stof(pRecord->GetAt(14));
		stMonthZY.fConsumeRef		+=stof(pRecord->GetAt(15));
		stMonthZY.fConsumeOther		+=stof(pRecord->GetAt(16));


		m_rc.SetGridContent (iRow,8,pRecord->GetAt(12));
		m_rc.SetGridContent (iRow,9,pRecord->GetAt(13));
		m_rc.SetGridContent (iRow,10,vtos(stProjectZY.fIn-stProjectZY.fOut,1));

		fConsumeDP=stof(pRecord->GetAt (14));
		fConsumeBC=stof(pRecord->GetAt (15));
		fConsumeQT=stof(pRecord->GetAt (16));
		fConsume=fConsumeDP+fConsumeBC+fConsumeQT;

		m_rc.SetGridContent (iRow,11,vtos(fConsume,1));
		m_rc.SetGridContent (iRow,12,vtos(fConsumeDP,1));
		m_rc.SetGridContent (iRow,13,vtos(fConsumeBC,1));
		m_rc.SetGridContent (iRow,14,vtos(fConsumeQT,1));

		//��ע

		// פ�Ӽල
		AddMonitor(arrayMonitor,pRecord->GetAt (2));
	}

	// �ºϼƣ�
	m_rc.SetGridContent (iValidRecord+2,1,vtos(stMonthLG.fIn,1));
	m_rc.SetGridContent (iValidRecord+2,2,vtos(stMonthLG.fOut ,1));
	m_rc.SetGridContent (iValidRecord+2,3,vtos(stMonthLG.fIn-stMonthLG.fOut,1));
	m_rc.SetGridContent (iValidRecord+2,4,vtos(stMonthLG.fConsumeShot 
												+stMonthLG.fConsumeRef 
												+stMonthLG.fConsumeOther ,1));
	m_rc.SetGridContent (iValidRecord+2,5,vtos(stMonthLG.fConsumeShot,1));
	m_rc.SetGridContent (iValidRecord+2,6,vtos(stMonthLG.fConsumeRef,1));
	m_rc.SetGridContent (iValidRecord+2,7,vtos(stMonthLG.fConsumeOther,1));

	m_rc.SetGridContent (iValidRecord+2,8,vtos(stMonthZY.fIn,1));
	m_rc.SetGridContent (iValidRecord+2,9,vtos(stMonthZY.fOut,1));
	m_rc.SetGridContent (iValidRecord+2,10,vtos(stMonthZY.fIn-stMonthZY.fOut,1));
	m_rc.SetGridContent (iValidRecord+2,11,vtos(stMonthZY.fConsumeShot 
												+stMonthZY.fConsumeRef 
												+stMonthZY.fConsumeOther ,1));
	m_rc.SetGridContent (iValidRecord+2,12,vtos(stMonthZY.fConsumeShot,1));
	m_rc.SetGridContent (iValidRecord+2,13,vtos(stMonthZY.fConsumeRef,1));
	m_rc.SetGridContent (iValidRecord+2,14,vtos(stMonthZY.fConsumeOther,1));


	// ��Ŀ�ϼƣ�
	m_rc.SetGridContent (iValidRecord+3,1,vtos(stProjectLG.fIn,1));
	m_rc.SetGridContent (iValidRecord+3,2,vtos(stProjectLG.fOut ,1));
	m_rc.SetGridContent (iValidRecord+3,3,vtos(stProjectLG.fIn-stProjectLG.fOut,1));
	m_rc.SetGridContent (iValidRecord+3,4,vtos(stProjectLG.fConsumeShot 
												+stProjectLG.fConsumeRef 
												+stProjectLG.fConsumeOther ,1));
	m_rc.SetGridContent (iValidRecord+3,5,vtos(stProjectLG.fConsumeShot,1));
	m_rc.SetGridContent (iValidRecord+3,6,vtos(stProjectLG.fConsumeRef,1));
	m_rc.SetGridContent (iValidRecord+3,7,vtos(stProjectLG.fConsumeOther,1));

	m_rc.SetGridContent (iValidRecord+3,8,vtos(stProjectZY.fIn,1));
	m_rc.SetGridContent (iValidRecord+3,9,vtos(stProjectZY.fOut,1));
	m_rc.SetGridContent (iValidRecord+3,10,vtos(stProjectZY.fIn-stProjectZY.fOut,1));
	m_rc.SetGridContent (iValidRecord+3,11,vtos(stProjectZY.fConsumeShot 
												+stProjectZY.fConsumeRef 
												+stProjectZY.fConsumeOther ,1));
	m_rc.SetGridContent (iValidRecord+3,12,vtos(stProjectZY.fConsumeShot,1));
	m_rc.SetGridContent (iValidRecord+3,13,vtos(stProjectZY.fConsumeRef,1));
	m_rc.SetGridContent (iValidRecord+3,14,vtos(stProjectZY.fConsumeOther,1));

	delete []pDateRecord;

	m_rc.SetLeftDownString ("פ�Ӽල:"+GetMonitorString(arrayMonitor));
	return ;


}

void CReportView::CreateReport27()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,n;
	CMyDate date;
	CStringArray *pRecord=NULL;
	CString sLine;


	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	m_rc.SetGridQty (8,10);

	m_rc.CombineGrid (0,0,0,9);
	m_rc.CombineGrid (1,1,0,4);
	m_rc.CombineGrid (1,1,5,9);
	m_rc.CombineGrid (4,4,0,9);
	m_rc.CombineGrid (5,5,0,4);
	m_rc.CombineGrid (5,5,5,9);


	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("%s��̽������ĿͶ�ʷ���ʩ������ͬ�����",pDoc->m_sProjectName  );
	m_rc.SetTitle (s);	

    s="̽����"+pDoc->m_sProspectArea +"         Ͷ�ʷ���"
		      +pDoc->m_sClient +"          ʩ������"
			  +pDoc->m_sServer +pDoc->m_sCrew +"��";
    m_rc.SetLeftUpString (s);

	m_rc.SetGridContent (0,0,"Ͷ�ʷ�Ͷ�����");
	m_rc.SetGridFormat (0,0,DT_LEFT);
	m_rc.SetGridContent (1,0,"��                       ά");
	m_rc.SetGridContent (1,5,"��                       ά");
	m_rc.SetGridContent (2,0,"������");
	m_rc.SetGridContent (2,1,"���ڹ�����");
	m_rc.SetGridContent (2,2,"���ڳɱ�");
	m_rc.SetGridContent (2,3,"�ڹ���ɱ�");
	m_rc.SetGridContent (2,4,"��ͬ�ܶ�");
	m_rc.SetGridContent (2,5,"������");
	m_rc.SetGridContent (2,6,"���������");
	m_rc.SetGridContent (2,7,"���ڳɱ�");
	m_rc.SetGridContent (2,8,"�ڹ���ɱ�");
	m_rc.SetGridContent (2,9,"��ͬ�ܶ�");

	m_rc.SetGridContent (4,0,"ʩ�����������");
	m_rc.SetGridFormat  (4,0,DT_LEFT);
	m_rc.SetGridContent (5,0,"��                       ά");
	m_rc.SetGridContent (5,5,"��                       ά");
	m_rc.SetGridContent (6,0,"������");
	m_rc.SetGridContent (6,1,"���ڹ�����");
	m_rc.SetGridContent (6,2,"���ڳɱ�");
	m_rc.SetGridContent (6,3,"�ڹ���ɱ�");
	m_rc.SetGridContent (6,4,"��ͬ�ܶ�");
	m_rc.SetGridContent (6,5,"������");
	m_rc.SetGridContent (6,6,"���������");
	m_rc.SetGridContent (6,7,"���ڳɱ�");
	m_rc.SetGridContent (6,8,"�ڹ���ɱ�");
	m_rc.SetGridContent (6,9,"��ͬ�ܶ�");


	m_rc.SetGridContent (3,0,vtos(pDoc->m_Client2D.iShotQty));
	m_rc.SetGridContent (3,1,vtos(pDoc->m_Client2D.fShotKilometer));
	m_rc.SetGridContent (3,2,vtos(pDoc->m_Client2D.fMoney/pDoc->m_Client2D.iShotQty));
	m_rc.SetGridContent (3,3,vtos(pDoc->m_Client2D.fMoney/pDoc->m_Client2D.fShotKilometer));
	m_rc.SetGridContent (3,4,vtos(pDoc->m_Client2D.fMoney ));

	m_rc.SetGridContent (3,5,vtos(pDoc->m_Client3D.iShotQty));
	m_rc.SetGridContent (3,6,vtos(pDoc->m_Client3D.fShotKilometer));
	m_rc.SetGridContent (3,7,vtos(pDoc->m_Client3D.fMoney/pDoc->m_Client2D.iShotQty));
	m_rc.SetGridContent (3,8,vtos(pDoc->m_Client3D.fMoney/pDoc->m_Client2D.fShotKilometer));
	m_rc.SetGridContent (3,9,vtos(pDoc->m_Client3D.fMoney ));

	m_rc.SetGridContent (7,0,vtos(pDoc->m_Server2D.iShotQty));
	m_rc.SetGridContent (7,1,vtos(pDoc->m_Server2D.fShotKilometer));
	m_rc.SetGridContent (7,2,vtos(pDoc->m_Server2D.fMoney/pDoc->m_Server2D.iShotQty));
	m_rc.SetGridContent (7,3,vtos(pDoc->m_Server2D.fMoney/pDoc->m_Server2D.fShotKilometer));
	m_rc.SetGridContent (7,4,vtos(pDoc->m_Server2D.fMoney ));

	m_rc.SetGridContent (7,5,vtos(pDoc->m_Server3D.iShotQty));
	m_rc.SetGridContent (7,6,vtos(pDoc->m_Server3D.fShotKilometer));
	m_rc.SetGridContent (7,7,vtos(pDoc->m_Server3D.fMoney/pDoc->m_Server2D.iShotQty));
	m_rc.SetGridContent (7,8,vtos(pDoc->m_Server3D.fMoney/pDoc->m_Server2D.fShotKilometer));
	m_rc.SetGridContent (7,9,vtos(pDoc->m_Server3D.fMoney ));


	m_rc.SetLeftDownString ("פ�Ӽල:"+pDoc->m_sMonitor);
	return ;
}

///////////////////////////////////////////////
// ��̽������Ŀ�ɱ������£�ͳ�Ʊ�
// ��0501�ɱ�������ͳ�Ʊ�  ��28
///////////////////////////////////////////////
void CReportView::CreateReport28()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,n;
	CStringArray *pRecord=NULL;
	int iRecordQty=pDoc->GetRecordQty ();

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	m_rc.SetGridQty (iRecordQty+3,16);

	m_rc.CombineGrid (0,1,0,0);
	m_rc.CombineGrid (0,0,1,7);
	m_rc.CombineGrid (0,1,8,8);
	m_rc.CombineGrid (0,0,9,12);
	m_rc.CombineGrid (0,1,13,13);
	m_rc.CombineGrid (0,1,14,14);
	m_rc.CombineGrid (0,1,15,15);

	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("%s��̽������Ŀ�ɱ������£�ͳ�Ʊ�",pDoc->m_sProjectName  );
	m_rc.SetTitle (s);	

    s="̽����"+pDoc->m_sProspectArea +"         Ͷ�ʷ���"
		      +pDoc->m_sClient +"          ʩ������"
			  +pDoc->m_sServer +pDoc->m_sCrew +"��";
    m_rc.SetLeftUpString (s);

	m_rc.SetGridContent (0,1,"ֱ    ��    ��    ��");
	m_rc.SetGridContent (0,9,"�� �� �� ��");
	
	m_rc.SetGridContent (1,0,"����");
	m_rc.SetGridContent (1,1,"�׹�");
	m_rc.SetGridContent (1,2,"ըҩ");
	m_rc.SetGridContent (1,3,"����");
	m_rc.SetGridContent (1,4,"ȼ��");
	m_rc.SetGridContent (1,5,"����");
	m_rc.SetGridContent (1,6,"���ʡ���\r��������");
	m_rc.SetGridContent (1,7,"����ֱ\r�ӳɱ�");
	m_rc.SetGridContent (1,8,"ֱ�ӳ�\r���ܼ�");
	m_rc.SetGridContent (1,9,"�豸\r����");
	m_rc.SetGridContent (1,10,"�豸\r�۾�");
	m_rc.SetGridContent (1,11,"����\r����");
	m_rc.SetGridContent (1,12,"������\r�ӳɱ�");
	m_rc.SetGridContent (1,13,"��ӳ�\r���ܼ�");
	m_rc.SetGridContent (1,14,"����\r�ɱ�");
	m_rc.SetGridContent (1,15,"��ע");


	//////////////////////////////////////
	//
	float fSum1=0.0,fSum2=0.0;
	CStringArray arrayMonitor;
	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;
		s=pRecord->GetAt (4);
		s+="��";
		s+=pRecord->GetAt (5);
		s+="��";

		m_rc.SetGridContent (i+2,0,s);
		m_rc.SetGridContent (i+2,1,pRecord->GetAt (6));
		m_rc.SetGridContent (i+2,2,pRecord->GetAt (7));
		m_rc.SetGridContent (i+2,3,pRecord->GetAt (8));
		m_rc.SetGridContent (i+2,4,pRecord->GetAt (9));
		m_rc.SetGridContent (i+2,5,pRecord->GetAt (10));
		m_rc.SetGridContent (i+2,6,pRecord->GetAt (11));
		m_rc.SetGridContent (i+2,7,pRecord->GetAt (12));

		fSum1=0.0;
		for(j=6;j<=12;j++)
		{
			fSum1+=stof(pRecord->GetAt (j));
		}
		m_rc.SetGridContent (i+2,8,vtos(fSum1));

		m_rc.SetGridContent (i+2,9,pRecord->GetAt (13));
		m_rc.SetGridContent (i+2,10,pRecord->GetAt (14));
		m_rc.SetGridContent (i+2,11,pRecord->GetAt (15));
		m_rc.SetGridContent (i+2,12,pRecord->GetAt (16));

		fSum2=0.0;
		for(j=13;j<=16;j++)
		{
			fSum2+=stof(pRecord->GetAt (j));
		}
		m_rc.SetGridContent (i+2,13,vtos(fSum2));


		m_rc.SetGridContent (i+2,14,vtos(fSum1+fSum2));
		m_rc.SetGridContent (i+2,15,pRecord->GetAt (3));

		AddMonitor(arrayMonitor,pRecord->GetAt (2));
	}

	m_rc.SetLeftDownString ("פ�Ӽල:"+GetMonitorString(arrayMonitor));
	return ;
}
///////////////////////////////////////////////////////////
// ��̽������Ŀ�ɱ������£�������
//��0501�ɱ�������ͳ�Ʊ���ͬ���ڳɱ���ӱ�0101��Ŀ���ó�  ��29
//����ʩ��������������������ȴӱ�0301�ձ��еó�
///////////////////////////////////////////////////////////
void CReportView::CreateReport29()
{
	int iProjectDesignShot=0;

	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,n;
	CMyDate date;
	CStringArray *pRecord=NULL;
	CString sLine;

	CMyDate dateStart,dateEnd;
	dateStart.Set(pDoc->m_iStartYear ,pDoc->m_iStartMonth,pDoc->m_iStartDay );
	dateEnd.Set(pDoc->m_iEndYear ,pDoc->m_iEndMonth,pDoc->m_iEndDay );

	dateStart.SetType(pDoc->m_eMonthType);
	if(pDoc->m_eMonthType == MT_STATISTICS)
	{
		dateStart.IncreaseMonth ();
	}

	int iMonthQty=dateEnd.MonthFrom (dateStart)+1;
	CMonthStat *pMonthStat=new CMonthStat[iMonthQty];
	CMyDate month=dateStart;
	month.DecreaseMonth ();
	for(i=0;i<iMonthQty;i++)
	{
		month.IncreaseMonth ();
		pMonthStat[i].dateMonth =month;
		pMonthStat[i].dateMonth.GetMonthDate (	pMonthStat[i].dateStart ,
												pMonthStat[i].dateEnd);

		pMonthStat[i].iNaturalDay = pMonthStat[i].dateEnd .DayFrom (pMonthStat[i].dateStart)+1;

		pMonthStat[i].fDirectCost=0.0;
		pMonthStat[i].fIndirectCost=0.0;

	}

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	m_rc.SetGridQty (iMonthQty+2,14);

	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("%s��̽������Ŀ�ɱ������£�������",pDoc->m_sProjectName);
	m_rc.SetTitle (s);	

    s="̽����"+pDoc->m_sProspectArea +"         Ͷ�ʷ���"
		      +pDoc->m_sClient +"          ʩ������"
			  +pDoc->m_sServer +pDoc->m_sCrew +"��";
    m_rc.SetLeftUpString (s);

	m_rc.SetGridContent (0,0,"����");
	m_rc.SetGridContent (0,1,"����ʩ\r������");
	m_rc.SetGridContent (0,2,"������\r������");
	m_rc.SetGridContent (0,3,"��ֱ��\r�ɱ���");
	m_rc.SetGridContent (0,4,"����ƽ��\rֱ�ӳɱ�");
	m_rc.SetGridContent (0,5,"�¼��\r�ɱ���");
	m_rc.SetGridContent (0,6,"����ƽ��\r��ӳɱ�");
	m_rc.SetGridContent (0,7,"����\r�ɱ���");
	m_rc.SetGridContent (0,8,"ռ��Ͷ��\r��");
	m_rc.SetGridContent (0,9,"ʵ������\rƽ���ɱ�");
	m_rc.SetGridContent (0,10,"��ͬ����\r�ɱ���");
	m_rc.SetGridContent (0,11,"�ڳɱ�\r���+/-");
	m_rc.SetGridContent (0,12,"�ڳɱ�\r����ʣ�");
	m_rc.SetGridContent (0,13,"��ע");
	m_rc.SetGridContent (iMonthQty+1,0,"�ۼ�");
	
    // ����ÿ��������
	int iShotSum=0,iShot=0;
	CStringArray arrayMonitor;
	
	int iRecordQty=pDoc->m_docVice .GetRecordQty ();
	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->m_docVice .GetRecord (i);
        date.Set(pRecord->GetAt (0),pRecord->GetAt (1),pRecord->GetAt (2));

		// ����Ŀ
		iShotSum=0;
		for(j=3;j<=12;j++)
		{
			iShot=stof(pRecord->GetAt (j));
			iShotSum+=iShot;
		}
		for(j=14;j<=23;j++)
		{
			iShot=stof(pRecord->GetAt (j));
			iShotSum+=iShot;
		}

		for(j=0;j<iMonthQty;j++)
		{
			if(date<pMonthStat[j].dateStart||date>pMonthStat[j].dateEnd)continue;

			// ����Ŀ:
			pMonthStat[j].iFinishedShot += iShotSum;

			// ������:
			if(IsTrue(pRecord->GetAt (13)))
			{
				pMonthStat[j].iWorkDay++;
			}
		}
	}

	// ��Ŀ���������������Ͷ�ʣ�
	int iProjectMonth=pDoc->m_iProjectMonth ;
	float fMoneyTotal=pDoc->m_Server2D .fMoney ;
	int iProjectShotQty=stof(pDoc->m_s2DDesiShotQty );
	if(pDoc->m_bIs3D )
	{
		iProjectShotQty=stof(pDoc->m_s3DDesiShotQty );	
		fMoneyTotal=pDoc->m_Server3D .fMoney ;
	}

	// ÿ�³ɱ���
	float fSum1=0.0,fSum2=0.0;
	iRecordQty=pDoc->GetRecordQty ();
	int iYear=0,iMonth=0;
	CString sNote;
	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;

		iYear=stof(pRecord->GetAt (4));
		iMonth=stof(pRecord->GetAt (5));

		// ֱ�ӳɱ���
		fSum1=0.0;
		for(j=6;j<=12;j++)
		{
			fSum1+=stof(pRecord->GetAt (j));
		}
		m_rc.SetGridContent (i+2,8,vtos(fSum1));

		// ��ӳɱ���
		fSum2=0.0;
		for(j=13;j<=16;j++)
		{
			fSum2+=stof(pRecord->GetAt (j));
		}

		// ������Ե���:
		for(j=0;j<iMonthQty;j++)
		{
			if(iYear==pMonthStat[j].dateEnd .GetYear ()
				&&iMonth==pMonthStat[j].dateEnd .GetMonth ())
			{
				pMonthStat[j].fDirectCost		= fSum1;
				pMonthStat[j].fIndirectCost		= fSum2;
				break;
			}
		}

		// ��ע��
		sNote=pRecord->GetAt (3);
		sNote.Trim ();
		if(sNote!="NULL"&&sNote!="")
		{
			pMonthStat[j].sNote +=sNote;
		}
		// פ�Ӽල��
		AddMonitor(arrayMonitor,pRecord->GetAt (2));
	}

	// ��Ŀ�ϼƣ�
	CMonthStat projectSum;
	projectSum.iMaxShot =-1000;
	projectSum.iMinShot =999999;
	for(i=0;i<iMonthQty;i++)
	{
		projectSum.iFinishedShot	+=pMonthStat[i].iFinishedShot ;
		projectSum.iWorkDay			+=pMonthStat[i].iWorkDay ;
		projectSum.fDirectCost		+=pMonthStat[i].fDirectCost ;
		projectSum.fIndirectCost	+=pMonthStat[i].fIndirectCost ;
	}

	// д��ÿ�����ݣ�
	int iRow=0;
	float fSum=0.0;
	float fDiff=0.0;
	for(i=0;i<iMonthQty;i++)
	{
		iRow=i+1;
		s.Format("%d��%d��",pMonthStat[i].dateMonth .GetYear (),
							pMonthStat[i].dateMonth .GetMonth ());

		fSum=pMonthStat[i].fIndirectCost+pMonthStat[i].fDirectCost;

		m_rc.SetGridContent (iRow,0,s);
		m_rc.SetGridContent (iRow,1,vtos(pMonthStat[i].iWorkDay));
		m_rc.SetGridContent (iRow,2,vtos(pMonthStat[i].iFinishedShot ));
		m_rc.SetGridContent (iRow,3,vtos(pMonthStat[i].fDirectCost ));
		m_rc.SetGridContent (iRow,4,vtos(pMonthStat[i].fDirectCost/pMonthStat[i].iFinishedShot ));
		m_rc.SetGridContent (iRow,5,vtos(pMonthStat[i].fIndirectCost ));
		m_rc.SetGridContent (iRow,6,vtos(pMonthStat[i].fIndirectCost/pMonthStat[i].iFinishedShot ));
		m_rc.SetGridContent (iRow,7,vtos(fSum));
		m_rc.SetGridContent (iRow,8,vtos(fSum/fMoneyTotal*100));
		m_rc.SetGridContent (iRow,9,vtos(fSum/pMonthStat[i].iFinishedShot ));
		m_rc.SetGridContent (iRow,10,vtos(fMoneyTotal/iProjectShotQty));

		fDiff=fSum/pMonthStat[i].iFinishedShot-fMoneyTotal/iProjectShotQty;
		m_rc.SetGridContent (iRow,11,vtos(fDiff));
		m_rc.SetGridContent (iRow,12,vtos(fDiff/(fMoneyTotal/iProjectShotQty)*100));
		m_rc.SetGridContent (iRow,13,pMonthStat[i].sNote);
	}

	// д����Ŀ�ܼƣ�
	iRow=iMonthQty+1;
	fSum=projectSum.fIndirectCost+projectSum.fDirectCost;

	m_rc.SetGridContent (iRow,1,vtos(projectSum.iWorkDay));
	m_rc.SetGridContent (iRow,2,vtos(projectSum.iFinishedShot ));
	m_rc.SetGridContent (iRow,3,vtos(projectSum.fDirectCost ));
	m_rc.SetGridContent (iRow,4,vtos(projectSum.fDirectCost/projectSum.iFinishedShot ));
	m_rc.SetGridContent (iRow,5,vtos(projectSum.fIndirectCost ));
	m_rc.SetGridContent (iRow,6,vtos(projectSum.fIndirectCost/projectSum.iFinishedShot ));
	m_rc.SetGridContent (iRow,7,vtos(fSum));
	m_rc.SetGridContent (iRow,8,vtos(fSum/fMoneyTotal*100));
	m_rc.SetGridContent (iRow,9,vtos(fSum/projectSum.iFinishedShot ));
	m_rc.SetGridContent (iRow,10,vtos(fMoneyTotal/iProjectShotQty));

	fDiff=fSum/projectSum.iFinishedShot-fMoneyTotal/iProjectShotQty;
	m_rc.SetGridContent (iRow,11,vtos(fDiff));
	m_rc.SetGridContent (iRow,12,vtos(fDiff/(fMoneyTotal/iProjectShotQty)*100));


	m_rc.SetLeftDownString ("פ�Ӽල:"+GetMonitorString(arrayMonitor));

	delete []pMonthStat;

	return ;

}

///////////////////////////////////////////////////
//   ��̽�����������ϵͳQC��������嵥
//   ��0304QC��������嵥  ��30
///////////////////////////////////////////////////
void CReportView::CreateReport30()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,n;
	CMyDate date;
	CStringArray *pRecord=NULL;
	CString sLine;

	int iRecordQty=pDoc->GetRecordQty ();

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	m_rc.SetGridQty (iRecordQty+1,11);

	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("��̽�����������ϵͳQC��������嵥");
	m_rc.SetTitle (s);	

    s=   "̽����"+pDoc->m_sProspectArea 
		+"       ������Ŀ:"+pDoc->m_sProjectName 
		+"       Ͷ�ʷ���" +pDoc->m_sClient 
		+"       ʩ������" +pDoc->m_sServer +pDoc->m_sCrew +"��";

    m_rc.SetLeftUpString (s);

	m_rc.SetGridContent (0,0,"����");
	m_rc.SetGridContent (0,1,"�ο������");
	m_rc.SetGridContent (0,2,"SPS");
	m_rc.SetGridContent (0,3,"�첨������");
	m_rc.SetGridContent (0,4,"�����������");
	m_rc.SetGridContent (0,5,"��У��");
	m_rc.SetGridContent (0,6,"�����ռ�");
	m_rc.SetGridContent (0,7,"��������");
	m_rc.SetGridContent (0,8,"�ɿ���Դ");
	m_rc.SetGridContent (0,9,"�����ɹ�");
	m_rc.SetGridContent (0,10,"��ע");

	CStringArray arrayMonitor;
	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
		s=pRecord->GetAt (3)+"��"+pRecord->GetAt (4)+"��"+pRecord->GetAt (5)+"��";

		m_rc.SetGridContent (i+1,0,s);

		for(j=1;j<=10;j++)
		{
			s=pRecord->GetAt (5+j);
			if(IsTrue(s))
			{
				m_rc.SetGridContent (i+1,j,"Y");
			}
			else
			{
				m_rc.SetGridContent (i+1,j,"N");
			}
		}

		AddMonitor(arrayMonitor,pRecord->GetAt (15));
	}

	m_rc.SetLeftDownString ("פ�Ӽල:"+GetMonitorString(arrayMonitor));
	return ;
}
