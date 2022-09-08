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
//勘探监理项目炸药、雷管（日）使用情况统计表
//表0301监理工作日报  表26
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
	// 计算库存：
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
	// 建立表格：
	/////////////////////////////////////////////////
	int iValidRecord=iRecordQty-iStartRecord;
	m_rc.SetGridQty (iValidRecord+4,16);

	m_rc.CombineGrid (0,1,0,0);
	m_rc.CombineGrid (0,0,1,7);
	m_rc.CombineGrid (0,0,8,14);
	m_rc.CombineGrid (0,1,15,15);


	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("%s勘探监理项目炸药、雷管（日）使用情况统计表",pDoc->m_sProjectName  );
	m_rc.SetTitle (s);	

    s="探区："+pDoc->m_sProspectArea +"         投资方："
		      +pDoc->m_sClient +"          作业方："
			  +pDoc->m_sServer +pDoc->m_sCrew +"队";
    m_rc.SetLeftUpString (s);

	m_rc.SetGridContent (0,0,"日期");
	m_rc.SetGridContent (0,1,"雷 管 使 用 情 况");
	m_rc.SetGridContent (0,8,"炸 药 使 用 情 况");
	m_rc.SetGridContent (1,1,"入库\r数量");
	m_rc.SetGridContent (1,2,"出库\r数量");
	m_rc.SetGridContent (1,3,"库存\r数量");
	m_rc.SetGridContent (1,4,"消耗\r数量");
	m_rc.SetGridContent (1,5,"大炮\r消耗");
	m_rc.SetGridContent (1,6,"表层\r消耗");
	m_rc.SetGridContent (1,7,"其它\r消耗");
	m_rc.SetGridContent (1,8,"入库\r数量");
	m_rc.SetGridContent (1,9,"出库\r数量");
	m_rc.SetGridContent (1,10,"库存\r数量");
	m_rc.SetGridContent (1,11,"消耗\r数量");
	m_rc.SetGridContent (1,12,"大炮\r消耗");
	m_rc.SetGridContent (1,13,"表层\r消耗");
	m_rc.SetGridContent (1,14,"其它\r消耗");
	m_rc.SetGridContent (1,15,"备注");
	m_rc.SetGridContent (iValidRecord+2,0,"本月合计");
	m_rc.SetGridContent (iValidRecord+3,0,"项目累计");

	int iRow=0;
	float fConsumeDP=0.0,fConsumeBC=0.0,fConsumeQT=0.0,fConsume=0.0;
	for(i=iStartRecord;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (pDateRecord[i].iRecordOrder);

		iRow=i-iStartRecord+2;

		// 雷管:
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


		// 炸药:
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

		//备注

		// 驻队监督
		AddMonitor(arrayMonitor,pRecord->GetAt (2));
	}

	// 月合计：
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


	// 项目合计：
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

	m_rc.SetLeftDownString ("驻队监督:"+GetMonitorString(arrayMonitor));
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
	// 建立表格：
	/////////////////////////////////////////////////
	m_rc.SetGridQty (8,10);

	m_rc.CombineGrid (0,0,0,9);
	m_rc.CombineGrid (1,1,0,4);
	m_rc.CombineGrid (1,1,5,9);
	m_rc.CombineGrid (4,4,0,9);
	m_rc.CombineGrid (5,5,0,4);
	m_rc.CombineGrid (5,5,5,9);


	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("%s勘探监理项目投资方及施工方合同情况表",pDoc->m_sProjectName  );
	m_rc.SetTitle (s);	

    s="探区："+pDoc->m_sProspectArea +"         投资方："
		      +pDoc->m_sClient +"          施工方："
			  +pDoc->m_sServer +pDoc->m_sCrew +"队";
    m_rc.SetLeftUpString (s);

	m_rc.SetGridContent (0,0,"投资方投资情况");
	m_rc.SetGridFormat (0,0,DT_LEFT);
	m_rc.SetGridContent (1,0,"二                       维");
	m_rc.SetGridContent (1,5,"三                       维");
	m_rc.SetGridContent (2,0,"总炮数");
	m_rc.SetGridContent (2,1,"总炮公里数");
	m_rc.SetGridContent (2,2,"单炮成本");
	m_rc.SetGridContent (2,3,"炮公里成本");
	m_rc.SetGridContent (2,4,"合同总额");
	m_rc.SetGridContent (2,5,"总炮数");
	m_rc.SetGridContent (2,6,"满覆盖面积");
	m_rc.SetGridContent (2,7,"单炮成本");
	m_rc.SetGridContent (2,8,"炮公里成本");
	m_rc.SetGridContent (2,9,"合同总额");

	m_rc.SetGridContent (4,0,"施工方控制情况");
	m_rc.SetGridFormat  (4,0,DT_LEFT);
	m_rc.SetGridContent (5,0,"二                       维");
	m_rc.SetGridContent (5,5,"三                       维");
	m_rc.SetGridContent (6,0,"总炮数");
	m_rc.SetGridContent (6,1,"总炮公里数");
	m_rc.SetGridContent (6,2,"单炮成本");
	m_rc.SetGridContent (6,3,"炮公里成本");
	m_rc.SetGridContent (6,4,"合同总额");
	m_rc.SetGridContent (6,5,"总炮数");
	m_rc.SetGridContent (6,6,"满覆盖面积");
	m_rc.SetGridContent (6,7,"单炮成本");
	m_rc.SetGridContent (6,8,"炮公里成本");
	m_rc.SetGridContent (6,9,"合同总额");


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


	m_rc.SetLeftDownString ("驻队监督:"+pDoc->m_sMonitor);
	return ;
}

///////////////////////////////////////////////
// 勘探监理项目成本管理（月）统计表
// 表0501成本管理月统计表  表28
///////////////////////////////////////////////
void CReportView::CreateReport28()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,n;
	CStringArray *pRecord=NULL;
	int iRecordQty=pDoc->GetRecordQty ();

	/////////////////////////////////////////////////
	// 建立表格：
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
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("%s勘探监理项目成本管理（月）统计表",pDoc->m_sProjectName  );
	m_rc.SetTitle (s);	

    s="探区："+pDoc->m_sProspectArea +"         投资方："
		      +pDoc->m_sClient +"          施工方："
			  +pDoc->m_sServer +pDoc->m_sCrew +"队";
    m_rc.SetLeftUpString (s);

	m_rc.SetGridContent (0,1,"直    接    成    本");
	m_rc.SetGridContent (0,9,"间 接 成 本");
	
	m_rc.SetGridContent (1,0,"日期");
	m_rc.SetGridContent (1,1,"雷管");
	m_rc.SetGridContent (1,2,"炸药");
	m_rc.SetGridContent (1,3,"炮线");
	m_rc.SetGridContent (1,4,"燃油");
	m_rc.SetGridContent (1,5,"材料");
	m_rc.SetGridContent (1,6,"工资、补\r贴、奖金");
	m_rc.SetGridContent (1,7,"其它直\r接成本");
	m_rc.SetGridContent (1,8,"直接成\r本总计");
	m_rc.SetGridContent (1,9,"设备\r租赁");
	m_rc.SetGridContent (1,10,"设备\r折旧");
	m_rc.SetGridContent (1,11,"土地\r补偿");
	m_rc.SetGridContent (1,12,"其它间\r接成本");
	m_rc.SetGridContent (1,13,"间接成\r本总计");
	m_rc.SetGridContent (1,14,"月总\r成本");
	m_rc.SetGridContent (1,15,"备注");


	//////////////////////////////////////
	//
	float fSum1=0.0,fSum2=0.0;
	CStringArray arrayMonitor;
	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;
		s=pRecord->GetAt (4);
		s+="年";
		s+=pRecord->GetAt (5);
		s+="月";

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

	m_rc.SetLeftDownString ("驻队监督:"+GetMonitorString(arrayMonitor));
	return ;
}
///////////////////////////////////////////////////////////
// 勘探监理项目成本管理（月）分析表
//表0501成本管理月统计表，合同月炮成本额从表0101项目中拿出  表29
//本月施工天数、本月完成炮数等从表0301日报中得出
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
	// 建立表格：
	/////////////////////////////////////////////////
	m_rc.SetGridQty (iMonthQty+2,14);

	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("%s勘探监理项目成本管理（月）分析表",pDoc->m_sProjectName);
	m_rc.SetTitle (s);	

    s="探区："+pDoc->m_sProspectArea +"         投资方："
		      +pDoc->m_sClient +"          施工方："
			  +pDoc->m_sServer +pDoc->m_sCrew +"队";
    m_rc.SetLeftUpString (s);

	m_rc.SetGridContent (0,0,"日期");
	m_rc.SetGridContent (0,1,"本月施\r工天数");
	m_rc.SetGridContent (0,2,"本月完\r成炮数");
	m_rc.SetGridContent (0,3,"月直接\r成本额");
	m_rc.SetGridContent (0,4,"月炮平均\r直接成本");
	m_rc.SetGridContent (0,5,"月间接\r成本额");
	m_rc.SetGridContent (0,6,"月炮平均\r间接成本");
	m_rc.SetGridContent (0,7,"月总\r成本额");
	m_rc.SetGridContent (0,8,"占总投资\r％");
	m_rc.SetGridContent (0,9,"实际月炮\r平均成本");
	m_rc.SetGridContent (0,10,"合同月炮\r成本额");
	m_rc.SetGridContent (0,11,"炮成本\r差额+/-");
	m_rc.SetGridContent (0,12,"炮成本\r误差率％");
	m_rc.SetGridContent (0,13,"备注");
	m_rc.SetGridContent (iMonthQty+1,0,"累计");
	
    // 计算每月数量：
	int iShotSum=0,iShot=0;
	CStringArray arrayMonitor;
	
	int iRecordQty=pDoc->m_docVice .GetRecordQty ();
	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->m_docVice .GetRecord (i);
        date.Set(pRecord->GetAt (0),pRecord->GetAt (1),pRecord->GetAt (2));

		// 炮数目
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

			// 炮数目:
			pMonthStat[j].iFinishedShot += iShotSum;

			// 工作日:
			if(IsTrue(pRecord->GetAt (13)))
			{
				pMonthStat[j].iWorkDay++;
			}
		}
	}

	// 项目设计炮数、月数、投资：
	int iProjectMonth=pDoc->m_iProjectMonth ;
	float fMoneyTotal=pDoc->m_Server2D .fMoney ;
	int iProjectShotQty=stof(pDoc->m_s2DDesiShotQty );
	if(pDoc->m_bIs3D )
	{
		iProjectShotQty=stof(pDoc->m_s3DDesiShotQty );	
		fMoneyTotal=pDoc->m_Server3D .fMoney ;
	}

	// 每月成本：
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

		// 直接成本：
		fSum1=0.0;
		for(j=6;j<=12;j++)
		{
			fSum1+=stof(pRecord->GetAt (j));
		}
		m_rc.SetGridContent (i+2,8,vtos(fSum1));

		// 间接成本：
		fSum2=0.0;
		for(j=13;j<=16;j++)
		{
			fSum2+=stof(pRecord->GetAt (j));
		}

		// 查找相对的月:
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

		// 备注：
		sNote=pRecord->GetAt (3);
		sNote.Trim ();
		if(sNote!="NULL"&&sNote!="")
		{
			pMonthStat[j].sNote +=sNote;
		}
		// 驻队监督：
		AddMonitor(arrayMonitor,pRecord->GetAt (2));
	}

	// 项目合计：
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

	// 写入每月数据：
	int iRow=0;
	float fSum=0.0;
	float fDiff=0.0;
	for(i=0;i<iMonthQty;i++)
	{
		iRow=i+1;
		s.Format("%d年%d月",pMonthStat[i].dateMonth .GetYear (),
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

	// 写入项目总计：
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


	m_rc.SetLeftDownString ("驻队监督:"+GetMonitorString(arrayMonitor));

	delete []pMonthStat;

	return ;

}

///////////////////////////////////////////////////
//   物探工程质量监控系统QC报告入库清单
//   表0304QC报告入库清单  表30
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
	// 建立表格：
	/////////////////////////////////////////////////
	m_rc.SetGridQty (iRecordQty+1,11);

	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("物探工程质量监控系统QC报告入库清单");
	m_rc.SetTitle (s);	

    s=   "探区："+pDoc->m_sProspectArea 
		+"       监理项目:"+pDoc->m_sProjectName 
		+"       投资方：" +pDoc->m_sClient 
		+"       施工方：" +pDoc->m_sServer +pDoc->m_sCrew +"队";

    m_rc.SetLeftUpString (s);

	m_rc.SetGridContent (0,0,"日期");
	m_rc.SetGridContent (0,1,"参考物理点");
	m_rc.SetGridContent (0,2,"SPS");
	m_rc.SetGridContent (0,3,"检波器测试");
	m_rc.SetGridContent (0,4,"激发因素设计");
	m_rc.SetGridContent (0,5,"静校正");
	m_rc.SetGridContent (0,6,"年月日检");
	m_rc.SetGridContent (0,7,"环境噪音");
	m_rc.SetGridContent (0,8,"可控震源");
	m_rc.SetGridContent (0,9,"测量成果");
	m_rc.SetGridContent (0,10,"备注");

	CStringArray arrayMonitor;
	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
		s=pRecord->GetAt (3)+"年"+pRecord->GetAt (4)+"月"+pRecord->GetAt (5)+"日";

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

	m_rc.SetLeftDownString ("驻队监督:"+GetMonitorString(arrayMonitor));
	return ;
}
