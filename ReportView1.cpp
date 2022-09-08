
#include "stdafx.h"
#include "QCDB.h"
#include "MemDC.h"

#include "ReportDoc.h"
#include "ReportView.h"
#include "DlgReportShowProperty.h"
#include "MyDate.h"
#include "fhcglobal.h"


//  勘探监理项目设计工作量统计表
void CReportView::CreateReport01()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();

	int iRecordQty=pDoc->GetRecordQty ();
	m_rc.SetGridQty (iRecordQty+3,18);
	m_rc.CombineGrid (0,1,0,0);
	m_rc.CombineGrid (0,1,1,1);
	m_rc.CombineGrid (0,0,2,5);
	m_rc.CombineGrid (0,0,6,15);
	m_rc.CombineGrid (0,1,16,16);
	m_rc.CombineGrid (0,1,17,17);

	m_rc.CombineGrid (iRecordQty+2,iRecordQty+2,6,13);

	CString s;
	s.Format ("中油勘探监理公司%s年度%s探区%s勘探监理项目设计工作量统计表",
					(LPCTSTR)pDoc->m_sYear ,
					(LPCTSTR)pDoc->m_sProspectArea ,
					(LPCTSTR)pDoc->m_sArea );
	m_rc.SetTitle (s);

	CMyDate date(pDoc->m_iStatYear, 
				pDoc->m_iStatMonth, 
				pDoc->m_iStatDay); 


	s.Format ("统计日期：%s",date.GetDateString ());

	m_rc.SetLeftUpString (s);

	s.Format("施工单位： %s 公司 %s 队",pDoc->m_sServer ,pDoc->m_sCrew );
	m_rc.SetRightUpString (s);


	m_rc.SetGridContent (0,0,"序号");
	m_rc.SetGridContent (0,1,"测线号\r(线束号)");
	m_rc.SetGridContent (0,2,"二维项目");
	m_rc.SetGridContent (1,2,"炮点起\r始桩号");
	m_rc.SetGridContent (1,3,"炮点终\r止桩号");
	m_rc.SetGridContent (1,4,"满覆盖\r长度Km");
	m_rc.SetGridContent (1,5,"激发物\r理点数");
	m_rc.SetGridContent (0,11,"三维项目");
	m_rc.SetGridContent (1,6,"炮线起\r止线号");
	m_rc.SetGridContent (1,7,"炮线\r间隔");
	m_rc.SetGridContent (1,8,"炮点起\r止线号");
	m_rc.SetGridContent (1,9,"炮点\r间隔");
	m_rc.SetGridContent (1,10,"接收线\r起止线号");
	m_rc.SetGridContent (1,11,"接收线\r间隔");
	m_rc.SetGridContent (1,12,"接收点\r起止点号");
	m_rc.SetGridContent (1,13,"接收点\r间隔");
	m_rc.SetGridContent (1,14,"接收线\r长度Km");
	m_rc.SetGridContent (1,15,"激发物\r理点数");
	m_rc.SetGridContent (0,16,"小折\r射点\r数");
	m_rc.SetGridContent (0,17,"微测\r井点\r数");

	CStringArray *pRecord=NULL;
	float fFullCoverArea=0.0;
	for(int i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)
		{
			ASSERT(false);
			break;
		}
		m_rc.SetGridContent (i+2,0,vtos(i));
		m_rc.SetGridContent (i+2,1,pRecord->GetAt (0));
		m_rc.SetGridContent (i+2,2,pRecord->GetAt (1));
		m_rc.SetGridContent (i+2,3,pRecord->GetAt (2));
		m_rc.SetGridContent (i+2,4,pRecord->GetAt (3));
		m_rc.SetGridContent (i+2,5,pRecord->GetAt (4));

		m_rc.SetGridContent (i+2,6,pRecord->GetAt (5)+"-\r-"+pRecord->GetAt (6));
		m_rc.SetGridContent (i+2,7,pRecord->GetAt (7));
		m_rc.SetGridContent (i+2,8,pRecord->GetAt (8)+"-\r-"+pRecord->GetAt (9));
		m_rc.SetGridContent (i+2,9,pRecord->GetAt (10));

		m_rc.SetGridContent (i+2,10,pRecord->GetAt (11)+"-\r-"+pRecord->GetAt (12));
		m_rc.SetGridContent (i+2,11,pRecord->GetAt (13));
		m_rc.SetGridContent (i+2,12,pRecord->GetAt (14)+"-\r-"+pRecord->GetAt (15));
		m_rc.SetGridContent (i+2,13,pRecord->GetAt (16));

		m_rc.SetGridContent (i+2,14,pRecord->GetAt (17));
		m_rc.SetGridContent (i+2,15,pRecord->GetAt (18));

		m_rc.SetGridContent (i+2,16,pRecord->GetAt (19));
		m_rc.SetGridContent (i+2,17,pRecord->GetAt (20));

	}

	m_rc.SetGridContent (iRecordQty+2,0,"合\r计");
	m_rc.SetGridContent (iRecordQty+2,1,vtos(iRecordQty)+"条束");
	
	CString sContent;
	sContent.Format ("满覆盖面积:%sKm\0012  一次覆盖面积:%sKm\0012   施工面积:%sKm\0012",
			pDoc->m_s3DDesiFullCover ,pDoc->m_s3DDesignSingleCover ,pDoc->m_s3DDesiWorkAreaQty );
	m_rc.SetGridContent (iRecordQty+2,6,sContent);

	if(pRecord)
	{
		s.Format ("驻队监督：%s",pRecord->GetAt (21));
	}
	m_rc.SetLeftDownString (s);
}

//设计质量指标、目的层指标、主要干扰波指标统计表
void CReportView::CreateReport02()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();

	int iRowQty=11;

	int iRecordQty1=pDoc->GetRecordQty ();
	int iRecordQty2=pDoc->m_docVice.GetRecordQty ();
	int n=iRecordQty1+iRecordQty2+4;
	if(n>iRowQty)
	{
		iRowQty=n;
	}

	m_rc.SetGridQty (iRowQty,15);
	m_rc.CombineGrid (0,1,0,0);
	m_rc.CombineGrid (0,0,1,4);
	m_rc.CombineGrid (0,1,5,5);
	m_rc.CombineGrid (0,0,6,13);
	m_rc.CombineGrid (0,1,14,14);


	m_rc.CombineGrid (iRecordQty1+2,iRecordQty1+3,5,5);
	m_rc.CombineGrid (iRecordQty1+2,iRecordQty1+2,6,13);
	m_rc.CombineGrid (iRecordQty1+2,iRecordQty1+3,14,14);

	for(int i=iRecordQty1+3;i<iRowQty;i++)
	{
		m_rc.CombineGrid (i,i,12,13);
	}

	CString s;
	s.Format ("中油勘探监理公司%s年度%s探区%s勘探监理项目",
					(LPCTSTR)pDoc->m_sYear ,
					(LPCTSTR)pDoc->m_sProspectArea ,
					(LPCTSTR)pDoc->m_sArea );
	m_rc.SetTitle (s);
	m_rc.SetViceTitle("设计质量指标、目的层指标、主要干扰波指标统计表");

	CMyDate date(	pDoc->m_iStatYear ,
					pDoc->m_iStatMonth ,
					pDoc->m_iStartDay );

	s.Format ("统计日期：%s",date.GetDateString ());

	m_rc.SetLeftUpString (s);

	s.Format("施工单位： %s 公司 %s 队",pDoc->m_sServer ,pDoc->m_sCrew );
	m_rc.SetRightUpString (s);


	m_rc.SetGridContent (0,0,"序\r号");
	m_rc.SetGridContent (0,1,"质   量   指   标   及   要   求");
	m_rc.SetGridContent (1,1,"项      目");
	m_rc.SetGridContent (1,2,"符号");
	m_rc.SetGridContent (1,3,"指标");
	m_rc.SetGridContent (1,4,"要求");

	m_rc.SetGridContent (2,0,"1");
	m_rc.SetGridContent (2,1,"全区一级品率");
	m_rc.SetGridContent (2,2,"≥");
	m_rc.SetGridContent (2,3,pDoc->m_arrayProject1 .GetAt (0));
	m_rc.SetGridContent (2,4,pDoc->m_arrayProject1 .GetAt (1));

	m_rc.SetGridContent (3,0,"2");
	m_rc.SetGridContent (3,1,"全区合格率");
	m_rc.SetGridContent (3,2,"≥");
	m_rc.SetGridContent (3,3,pDoc->m_arrayProject1 .GetAt (2));
	m_rc.SetGridContent (3,4,pDoc->m_arrayProject1 .GetAt (3));

	m_rc.SetGridContent (4,0,"3");
	m_rc.SetGridContent (4,1,"全区废品率");
	m_rc.SetGridContent (4,2,"≤");
	m_rc.SetGridContent (4,3,pDoc->m_arrayProject1 .GetAt (4));
	m_rc.SetGridContent (4,4,pDoc->m_arrayProject1 .GetAt (5));

	m_rc.SetGridContent (5,0,"4");
	m_rc.SetGridContent (5,1,"全区空炮率");
	m_rc.SetGridContent (5,2,"≤");
	m_rc.SetGridContent (5,3,pDoc->m_arrayProject1 .GetAt (6));
	m_rc.SetGridContent (5,4,pDoc->m_arrayProject1 .GetAt (7));

	m_rc.SetGridContent (6,0,"5");
	m_rc.SetGridContent (6,1,"单束线空炮率");
	m_rc.SetGridContent (6,2,"≤");
	m_rc.SetGridContent (6,3,pDoc->m_arrayProject1 .GetAt (8));
	m_rc.SetGridContent (6,4,pDoc->m_arrayProject1 .GetAt (9));

	m_rc.SetGridContent (7,0,"6");
	m_rc.SetGridContent (7,1,"单束线废品率");
	m_rc.SetGridContent (7,2,"≤");
	m_rc.SetGridContent (7,3,pDoc->m_arrayProject1 .GetAt (10));
	m_rc.SetGridContent (7,4,pDoc->m_arrayProject1 .GetAt (11));


	m_rc.SetGridContent (8,0,"7");
	m_rc.SetGridContent (8,1,"全区测量资料合格率");
	m_rc.SetGridContent (8,2,"＝");
	m_rc.SetGridContent (8,3,pDoc->m_arrayProject1 .GetAt (12));
	m_rc.SetGridContent (8,4,pDoc->m_arrayProject1 .GetAt (13));

	m_rc.SetGridContent (9,0,"8");
	m_rc.SetGridContent (9,1,"全区表层调查资料合格率");
	m_rc.SetGridContent (9,2,"＝");
	m_rc.SetGridContent (9,3,pDoc->m_arrayProject1 .GetAt (14));
	m_rc.SetGridContent (9,4,pDoc->m_arrayProject1 .GetAt (15));

	m_rc.SetGridContent (10,0,"9");
	m_rc.SetGridContent (10,1,"全区现场处理率");
	m_rc.SetGridContent (10,2,"＝");
	m_rc.SetGridContent (10,3,pDoc->m_arrayProject1 .GetAt (16));
	m_rc.SetGridContent (10,4,pDoc->m_arrayProject1 .GetAt (17));
	
	//////////////////////////////////////
	//目的层指标
	///////////////////////////////////////
	m_rc.SetGridContent (0,5,"序\r号");
	m_rc.SetGridContent (0,6,"主  要  目  的  层  指  标  及  要  求");
	m_rc.SetGridContent (1,6,"目的层");
	m_rc.SetGridContent (1,7,"代码");
	m_rc.SetGridContent (1,8,"T0时间");
	m_rc.SetGridContent (1,9,"主频");
	m_rc.SetGridContent (1,10,"分辨率");
	m_rc.SetGridContent (1,11,"信噪比");
	m_rc.SetGridContent (1,12,"能量");
	m_rc.SetGridContent (1,13,"要求");
	m_rc.SetGridContent (1,14,"备注");

	CStringArray *pRecord=NULL;
	for(int i=0;i<iRecordQty1;i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)
		{
			ASSERT(false);
			break;
		}
		m_rc.SetGridContent (i+2,5,vtos(i+1));
		m_rc.SetGridContent (i+2,6,pRecord->GetAt (0));
		m_rc.SetGridContent (i+2,7,pRecord->GetAt (1));
		m_rc.SetGridContent (i+2,8,pRecord->GetAt (2));
		m_rc.SetGridContent (i+2,9,pRecord->GetAt (3)+"\r-"+pRecord->GetAt (4));
		m_rc.SetGridContent (i+2,10,pRecord->GetAt (5)+"\r-"+pRecord->GetAt (6));
		m_rc.SetGridContent (i+2,11,pRecord->GetAt (7)+"\r-"+pRecord->GetAt (8));
		m_rc.SetGridContent (i+2,12,pRecord->GetAt (9)+"\r-"+pRecord->GetAt (10));
		m_rc.SetGridContent (i+2,13,pRecord->GetAt (11));
		m_rc.SetGridContent (i+2,14,pRecord->GetAt (12));

	}

	//////////////////////////////////////
	//   主要干扰波指标统计表
	///////////////////////////////////////
	m_rc.SetGridContent (iRecordQty1+2,5,"序\r号");
	m_rc.SetGridContent (iRecordQty1+2,6,"主  要  干  扰  波  指  标  及  要  求");
	m_rc.SetGridContent (iRecordQty1+3,6,"干扰波");
	m_rc.SetGridContent (iRecordQty1+3,7,"代码");
	m_rc.SetGridContent (iRecordQty1+3,8,"视频率");
	m_rc.SetGridContent (iRecordQty1+3,9,"视速度");
	m_rc.SetGridContent (iRecordQty1+3,10,"视波长");
	m_rc.SetGridContent (iRecordQty1+3,11,"强度");
	m_rc.SetGridContent (iRecordQty1+3,12,"要求");
	m_rc.SetGridContent (iRecordQty1+3,14,"备注");

	CDataBrowseDoc *pDBDoc=&pDoc->m_docVice ;
	for(i=0;i<iRecordQty2;i++)
	{
		pRecord=pDBDoc->GetRecord (i);
		if(!pRecord)
		{
			ASSERT(false);
			break;
		}
		m_rc.SetGridContent (iRecordQty1+4+i,5,vtos(i+1));
		m_rc.SetGridContent (iRecordQty1+4+i,6,pRecord->GetAt (0));
		m_rc.SetGridContent (iRecordQty1+4+i,7,pRecord->GetAt (1));
		m_rc.SetGridContent (iRecordQty1+4+i,8,pRecord->GetAt (2)+"\r"+pRecord->GetAt (3));
		m_rc.SetGridContent (iRecordQty1+4+i,9,pRecord->GetAt (4)+"\r"+pRecord->GetAt (5));
		m_rc.SetGridContent (iRecordQty1+4+i,10,pRecord->GetAt (6)+"\r"+pRecord->GetAt (7));
		m_rc.SetGridContent (iRecordQty1+4+i,11,pRecord->GetAt (8)+"\r"+pRecord->GetAt (9));
		m_rc.SetGridContent (iRecordQty1+4+i,12,pRecord->GetAt (10));
		m_rc.SetGridContent (iRecordQty1+4+i,14,pRecord->GetAt (11)+"12345我们1234我123456789012345678901234567890我们",CW_COMMONWIDTH);
	}
}


//勘探监理项目监理工作周报表
void CReportView::CreateReport03()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,k;
	CStringArray *pRecord=NULL;

	CString sData;
	CMyDate date;
	float fWeekSum[22],fProjectSum[22];
	CString sItem[22];
	for(i=0;i<22;i++)
	{
		fWeekSum[i]=0.0;
		fProjectSum[i]=0.0;
	}

	int iWeekRecordQty=0;
	int iShotNum=0;
	for(i=0;i<pDoc->GetRecordQty ();i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;
		date.Set(pRecord->GetAt (1),pRecord->GetAt (2),pRecord->GetAt (3));

		iShotNum=0;
		for(j=28;j<=47;j++)
		{
			iShotNum+=stof(pRecord->GetAt (j));
		}

		sItem[2]=vtos(iShotNum);
		sItem[3]=pRecord->GetAt (5);
		sItem[4]=pRecord->GetAt (6);
		sItem[5]=pRecord->GetAt (7);
		sItem[6]=pRecord->GetAt (8);
		sItem[7]=pRecord->GetAt (9);
		sItem[8]=pRecord->GetAt (10);
		sItem[9]=pRecord->GetAt (11);
		sItem[10]=pRecord->GetAt (12);
		sItem[11]=pRecord->GetAt (13);
		sItem[12]=pRecord->GetAt (14);
		sItem[13]=pRecord->GetAt (15);
		sItem[14]=pRecord->GetAt (16);
		sItem[15]=pRecord->GetAt (17);
		sItem[16]=pRecord->GetAt (18);
		sItem[17]=pRecord->GetAt (19);
		sItem[18]=pRecord->GetAt (20);
		sItem[19]=pRecord->GetAt (21);
		sItem[20]=pRecord->GetAt (22);
		sItem[21]=pRecord->GetAt (23);

		date.Set (pRecord->GetAt (1),pRecord->GetAt (2),pRecord->GetAt (3));
		if(date>=CMyDate(pDoc->m_iStartYear,
							pDoc->m_iStartMonth,
							pDoc->m_iStartDay))
		{
			iWeekRecordQty++;

			for(k=2;k<=21;k++)
			{
				fWeekSum[k]+=stof(sItem[k]);
			}
		}

		for(k=2;k<=21;k++)
		{
			fProjectSum[k]+=stof(sItem[k]);
		}
	}

	/////////////////////////////////////////////////
	//
	/////////////////////////////////////////////////
	int iRowQty=iWeekRecordQty+6;

	m_rc.SetGridQty (iRowQty,22);
	m_rc.CombineGrid (0,1,0,0);
	m_rc.CombineGrid (0,1,1,1);
	m_rc.CombineGrid (0,0,2,5);
	m_rc.CombineGrid (0,0,6,9);
	
	m_rc.CombineGrid (iWeekRecordQty+3,iWeekRecordQty+3,0,1);
	m_rc.CombineGrid (iWeekRecordQty+2,iWeekRecordQty+2,0,1);
	m_rc.CombineGrid (iWeekRecordQty+4,iWeekRecordQty+5,0,21);

	for(i=10;i<=21;i++)
	{
		m_rc.CombineGrid (0,1,i,i);
	}

	CString s;
	s.Format ("中油勘探监理公司%s年度%s探区%s勘探监理项目监理工作周报表",
					(LPCTSTR)pDoc->m_sYear ,
					(LPCTSTR)pDoc->m_sProspectArea ,
					(LPCTSTR)pDoc->m_sArea );
	m_rc.SetTitle (s);
	
	CString sMonitor="";
	pRecord=pDoc->GetRecord (0);
	if(pRecord)
	{
		sMonitor=pRecord->GetAt (27);
	}

	s.Format ("驻队监督:%s          探区:%s           施工单位:%s",
		sMonitor,
		pDoc->m_sProspectArea ,
		pDoc->m_sCrew );

	if(pDoc->m_bIs3D )
	{
		s+="        3D";
	}
	else
	{
		s+="        2D";
	}

	CString s2;
	CString sKilometer=pDoc->m_s3DDesiFullCover ;
	CString sShotQty=pDoc->m_s3DDesiShotQty ;
	if(!pDoc->m_bIs3D )
	{
		sKilometer=pDoc->m_s2DDesiFullCover;
		sShotQty=pDoc->m_s2DDesiShotQty ;
	}
	s2.Format ("设计测线: %s 条(束)    炮数: %s  公里:%s",
			pDoc->m_sDesiLineQty     ,
			sShotQty,
			sKilometer);

	s+=s2;

	m_rc.SetLeftUpString (s);

	m_rc.SetGridContent(0,0,"日期");
	m_rc.SetGridContent(0,1,"测线");
	m_rc.SetGridContent(0,2,"监  督  核  实  工  作  量");
	m_rc.SetGridContent(1,2,"炮数");
	m_rc.SetGridContent(1,3,"公里");
	m_rc.SetGridContent(1,4,"小折射");
	m_rc.SetGridContent(1,5,"微测井");

	m_rc.SetGridContent(0,6,"监 督 复 评 统 计");
	m_rc.SetGridContent(1,6,"一级");
	m_rc.SetGridContent(1,7,"二级");
	m_rc.SetGridContent(1,8,"空点");
	m_rc.SetGridContent(1,9,"废品");

	m_rc.SetGridContent(0,10,"检查\r激发");
	m_rc.SetGridContent(0,11,"激发\r合格");
	m_rc.SetGridContent(0,12,"检查\r接收");
	m_rc.SetGridContent(0,13,"接收\r合格");
	m_rc.SetGridContent(0,14,"测线\r合格");
	m_rc.SetGridContent(0,15,"月检");
	m_rc.SetGridContent(0,16,"日检");
	m_rc.SetGridContent(0,17,"检查\r测量\r标志");
	m_rc.SetGridContent(0,18,"合格\r测量\r标志");
	m_rc.SetGridContent(0,19,"现场\r检查");
	m_rc.SetGridContent(0,20,"备忘录");
	m_rc.SetGridContent(0,21,"图象等\r附件\r编号");

	m_rc.SetGridContent(iWeekRecordQty+2,0,"合计");
	m_rc.SetGridContent(iWeekRecordQty+3,0,"累计");


	CString sNote="";

	


	for(i=0;i<pDoc->GetRecordQty ();i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;
		date.Set(pRecord->GetAt (1),pRecord->GetAt (2),pRecord->GetAt (3));
		
		if(date<CMyDate(pDoc->m_iStartYear,
							pDoc->m_iStartMonth,
							pDoc->m_iStartDay))
		{
			continue;
		}


		m_rc.SetGridContent(2+i,0,date.GetDateString ());
		m_rc.SetGridContent(2+i,1,pDoc->GetLineName (pRecord->GetAt (0)));
		
		iShotNum=0;
		for(j=28;j<=37;j++)
		{
			iShotNum+=stof(pRecord->GetAt (j));
		}

		sItem[2]=vtos(iShotNum);
		sItem[3]=pRecord->GetAt (5);
		sItem[4]=pRecord->GetAt (6);
		sItem[5]=pRecord->GetAt (7);
		sItem[6]=pRecord->GetAt (8);
		sItem[7]=pRecord->GetAt (9);
		sItem[8]=pRecord->GetAt (10);
		sItem[9]=pRecord->GetAt (11);
		sItem[10]=pRecord->GetAt (12);
		sItem[11]=pRecord->GetAt (13);
		sItem[12]=pRecord->GetAt (14);
		sItem[13]=pRecord->GetAt (15);
		sItem[14]=pRecord->GetAt (16);
		sItem[15]=pRecord->GetAt (17);
		sItem[16]=pRecord->GetAt (18);
		sItem[17]=pRecord->GetAt (19);
		sItem[18]=pRecord->GetAt (20);
		sItem[19]=pRecord->GetAt (21);
		sItem[20]=pRecord->GetAt (22);
		sItem[21]=pRecord->GetAt (23);

		sNote+=pRecord->GetAt (24);
		sNote+=pRecord->GetAt (25);
		sNote+=pRecord->GetAt (26);

		for(k=2;k<=21;k++)
		{
			m_rc.SetGridContent(2+i,k,sItem[k]);
		}
	}

	for(k=2;k<=19;k++)
	{
		m_rc.SetGridContent(2+iWeekRecordQty,k,vtos(fWeekSum[k]));
		m_rc.SetGridContent(3+iWeekRecordQty,k,vtos(fProjectSum[k]));
	}

	m_rc.SetGridContent(4+iWeekRecordQty,0,"监理情况简述(1、监理项目运行情况；2、监督工作情况；3、下步监督工作重点等):\r"+sNote, CW_GRIDWIDTH);
	m_rc.SetGridFormat(4+iWeekRecordQty,0,DT_LEFT);
	
	return;
}



//勘探监理项目监理工作月报表
void CReportView::CreateReport04()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j;
	CStringArray *pRecord=NULL;

	CString sData;
	CMyDate date;
	
	/////////////////////////////////////////////////
	//
	/////////////////////////////////////////////////
	int iRecordQty=pDoc->GetRecordQty ()-2;  // The 2 records left is month total and project total;
	if(iRecordQty<0)
	{
		iRecordQty=0;
	}
	int iRowQty=iRecordQty+5;

	m_rc.SetGridQty (iRowQty,22);
	m_rc.CombineGrid (0,1,0,0);
	m_rc.CombineGrid (0,1,1,1);
	m_rc.CombineGrid (0,0,2,5);
	m_rc.CombineGrid (0,0,6,9);
	
	m_rc.CombineGrid (iRecordQty+3,iRecordQty+3,0,1);
	m_rc.CombineGrid (iRecordQty+2,iRecordQty+2,0,1);
	m_rc.CombineGrid (iRecordQty+4,iRecordQty+5,0,21);

	for(i=10;i<=21;i++)
	{
		m_rc.CombineGrid (0,1,i,i);
	}

	CString s;
	s.Format ("中油勘探监理公司%s年度%s探区%s勘探监理项目监理工作月报表",
					(LPCTSTR)pDoc->m_sYear ,
					(LPCTSTR)pDoc->m_sProspectArea ,
					(LPCTSTR)pDoc->m_sArea );
	m_rc.SetTitle (s);
	
	CString sMonitor="";
	pRecord=pDoc->GetRecord (0);
	if(pRecord)
	{
		sMonitor=pRecord->GetAt (32);
	}

	s.Format ("驻队监督:%s          探区:%s           施工单位:%s",
		sMonitor,
		pDoc->m_sProspectArea ,
		pDoc->m_sCrew );

	if(pDoc->m_bIs3D )
	{
		s+="        3D";
	}
	else
	{
		s+="        2D";
	}

	CString s2;
	CString sKilometer=pDoc->m_s3DDesiFullCover ;
	CString sShotQty=pDoc->m_s3DDesiShotQty ;
	if(!pDoc->m_bIs3D )
	{
		sKilometer=pDoc->m_s2DDesiFullCover;
		sShotQty=pDoc->m_s2DDesiShotQty ;
	}
	s2.Format ("设计测线: %s 条(束)    炮数: %s  公里:%s",
			pDoc->m_sDesiLineQty,
			sShotQty,
			sKilometer);
	s+=s2;

	m_rc.SetLeftUpString (s);

	m_rc.SetGridContent(0,0,"测线或\r线束号");
	m_rc.SetGridContent(0,1,"起止日期");
	m_rc.SetGridContent(0,2,"监  督  核  实  工  作  量");
	m_rc.SetGridContent(1,2,"炮数");
	m_rc.SetGridContent(1,3,"公里");
	m_rc.SetGridContent(1,4,"小折射");
	m_rc.SetGridContent(1,5,"微测井");

	m_rc.SetGridContent(0,6,"监 督 复 评 统 计");
	m_rc.SetGridContent(1,6,"一级");
	m_rc.SetGridContent(1,7,"二级");
	m_rc.SetGridContent(1,8,"空点");
	m_rc.SetGridContent(1,9,"废品");

	m_rc.SetGridContent(0,10,"检查\r激发");
	m_rc.SetGridContent(0,11,"激发\r合格");
	m_rc.SetGridContent(0,12,"检查\r接收");
	m_rc.SetGridContent(0,13,"接收\r合格");
	m_rc.SetGridContent(0,14,"测线\r合格");
	m_rc.SetGridContent(0,15,"月检");
	m_rc.SetGridContent(0,16,"日检");
	m_rc.SetGridContent(0,17,"检查\r测量\r标志");
	m_rc.SetGridContent(0,18,"合格\r测量\r标志");
	m_rc.SetGridContent(0,19,"现场\r检查");
	m_rc.SetGridContent(0,20,"备忘录");
	m_rc.SetGridContent(0,21,"图象等\r附件\r编号");

	m_rc.SetGridContent(iRecordQty+2,0,"合计");
	m_rc.SetGridContent(iRecordQty+3,0,"累计");


	CString sNote[5];

	for(i=0;i<pDoc->GetRecordQty ();i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;

		if(i<iRecordQty)
		{
			// 测线名
			m_rc.SetGridContent(2+i,0,pRecord->GetAt (0));

			// 起止日期：
			date.Set(pRecord->GetAt(1),pRecord->GetAt(2),pRecord->GetAt(3));
			s="";
			//if(date.GetYear() !=0)
			{
				s=date.GetDateString ();
			}

			date.Set(pRecord->GetAt(4),pRecord->GetAt(5),pRecord->GetAt(6));
			//if(date.GetYear() !=0)
			{
				s+="--"+date.GetDateString ();
			}		
			
			m_rc.SetGridContent(2+i,1,s);
		}

		for(j=2;j<=21;j++)
		{
			s=pRecord->GetAt (j+5);
			s.Trim ();
			m_rc.SetGridContent(2+i,j,s);
		}
	
		for(j=0;j<5;j++)
		{
			s=pRecord->GetAt (27+j);
			s.Trim ().MakeUpper ();
			if(s!="NULL")
			{
				sNote[j]+=s;
			}
		}
	}

	m_rc.SetGridContent(4+iRecordQty,0,"本月情况简述(1、项目运行及完成情况；2、监督工作及监督数据统计情况；3、发现及整改的问题；4、下步监督工作重点；5、第一个月要另附监理项目概况):\r"
					+sNote[0]+sNote[1]+sNote[2]+sNote[3]+sNote[4], CW_GRIDWIDTH);
	m_rc.SetGridFormat(4+iRecordQty,0,DT_LEFT);
	
	return;
}

// 物 探 工 程 仪 器 专 业 监 督 周 报 表
void CReportView::CreateReport05()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,k;
	CStringArray *pRecord=NULL;

	///////////////////////////////////////////
	// 计算每周总计和项目总计
	///////////////////////////////////////////
	CString sData;
	CMyDate date;
	float fWeekSum[22],fProjectSum[22];
	CString sItem[22];
	for(i=0;i<22;i++)
	{
		fWeekSum[i]=0.0;
		fProjectSum[i]=0.0;
	}

	int iWeekRecordQty=0;
	float f=0;
	for(i=0;i<pDoc->GetRecordQty ();i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;
		
		sItem[4]=pRecord->GetAt (5);
		sItem[5]=pRecord->GetAt (6);
		sItem[6]=pRecord->GetAt (7);
		
		f=stof(sItem[6]);
		if(f!=0)
		{
			sItem[7]=vtos(stof(pRecord->GetAt (8))/f);
		}
		else
		{
			sItem[7]="";
		}

		sItem[8]=pRecord->GetAt (9);
		sItem[9]=pRecord->GetAt (10);
		sItem[10]=pRecord->GetAt (11);
		sItem[11]=pRecord->GetAt (12);
		sItem[12]=pRecord->GetAt (13);
		sItem[13]=pRecord->GetAt (14);
		sItem[14]=pRecord->GetAt (15);
		sItem[15]=pRecord->GetAt (16);
		sItem[16]=pRecord->GetAt (17);
		sItem[17]=pRecord->GetAt (18);
		sItem[18]=pRecord->GetAt (19);
		sItem[19]=pRecord->GetAt (20);

		date.Set (pRecord->GetAt (1),pRecord->GetAt (2),pRecord->GetAt (3));
		if(date>=CMyDate(pDoc->m_iStartYear,
							pDoc->m_iStartMonth,
							pDoc->m_iStartDay))
		{
			iWeekRecordQty++;

			for(k=4;k<=19;k++)
			{
				fWeekSum[k]+=stof(sItem[k]);
			}
		}

		for(k=4;k<=19;k++)
		{
			fProjectSum[k]+=stof(sItem[k]);
		}
	}

	/////////////////////////////////////////////////
	// 建立表格：
	/////////////////////////////////////////////////
	int iRowQty=iWeekRecordQty+5;

	m_rc.SetGridQty (iRowQty,22);
	m_rc.CombineGrid (0,1,0,0);
	m_rc.CombineGrid (0,1,1,1);
	m_rc.CombineGrid (0,1,2,2);
	m_rc.CombineGrid (0,1,3,3);

	m_rc.CombineGrid (0,0,4,7);
	m_rc.CombineGrid (0,0,8,9);
	m_rc.CombineGrid (0,0,10,12);
	m_rc.CombineGrid (0,0,13,15);
	m_rc.CombineGrid (0,0,16,19);

	m_rc.CombineGrid (0,1,20,20);
	m_rc.CombineGrid (0,1,21,21);
	
	m_rc.CombineGrid (iWeekRecordQty+2,iWeekRecordQty+2,0,3);
	m_rc.CombineGrid (iWeekRecordQty+3,iWeekRecordQty+3,0,3);
	m_rc.CombineGrid (iWeekRecordQty+4,iWeekRecordQty+4,0,21);


	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("物 探 工 程 测 量 专 业 监 督 周 报 表");
	m_rc.SetTitle (s);

	m_rc.SetGridContent(0,0,"日期");
	m_rc.SetGridContent(0,1,"监理项目");
	m_rc.SetGridContent(0,2,"施工\r单位");
	m_rc.SetGridContent(0,3,"检查\r线束号");
	m_rc.SetGridContent(0,4,"监督核实工作量");
	m_rc.SetGridContent(1,4,"长度");
	m_rc.SetGridContent(1,5,"放样\r点数");

	m_rc.SetGridContent(1,6,"复测\r点数");
	m_rc.SetGridContent(1,7,"复测率");
	m_rc.SetGridContent(0,8,"放样误差(最大)");
	m_rc.SetGridContent(1,8,"Δx");
	m_rc.SetGridContent(1,9,"Δy");

	m_rc.SetGridContent(0,10,"复测较差(最大)");
	m_rc.SetGridContent(1,10,"Δx");
	m_rc.SetGridContent(1,11,"Δy");
	m_rc.SetGridContent(1,12,"Δh");
	m_rc.SetGridContent(0,13,"复测精度(中误差最大)");
	m_rc.SetGridContent(1,13,"Mx(+/-)");
	m_rc.SetGridContent(1,14,"My(+/-)");
	m_rc.SetGridContent(1,15,"Mh(+/-)");
	m_rc.SetGridContent(0,16,"野  外  检  查");
	m_rc.SetGridContent(1,16,"测量\r标志");
	m_rc.SetGridContent(1,17,"特殊\r点位");
	m_rc.SetGridContent(1,18,"复检\r点数");
	m_rc.SetGridContent(1,19,"施工\r参数");
	m_rc.SetGridContent(0,20,"备\r忘\r录");
	m_rc.SetGridContent(0,21,"备注");

	m_rc.SetGridContent(iWeekRecordQty+2,0,"合   计");
	m_rc.SetGridContent(iWeekRecordQty+3,0,"累   计");


	CString sNote="";
	CString sJS="";
	CString sProjectName;

	CStringArray arrayProject;
	for(i=0;i<pDoc->GetRecordQty ();i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;
		date.Set(pRecord->GetAt (1),pRecord->GetAt (2),pRecord->GetAt (3));
		
		if(date<CMyDate(pDoc->m_iStartYear,
							pDoc->m_iStartMonth,
							pDoc->m_iStartDay))
		{
			continue;
		}

		pDoc->GetProjectInfoByNo(pRecord->GetAt (29),&arrayProject);

		m_rc.SetGridContent(2+i,0,date.GetDateString ());
		m_rc.SetGridContent(2+i,1,arrayProject.GetAt (1));
		m_rc.SetGridContent(2+i,2,arrayProject.GetAt (8));
		m_rc.SetGridContent(2+i,3,pDoc->GetLineName (pRecord->GetAt (0)));
		
		sItem[4]=pRecord->GetAt (5);
		sItem[5]=pRecord->GetAt (6);
		sItem[6]=pRecord->GetAt (7);
		sItem[7]=pRecord->GetAt (8);
		sItem[8]=pRecord->GetAt (9);
		sItem[9]=pRecord->GetAt (10);
		sItem[10]=pRecord->GetAt (11);
		sItem[11]=pRecord->GetAt (12);
		sItem[12]=pRecord->GetAt (13);
		sItem[13]=pRecord->GetAt (14);
		sItem[14]=pRecord->GetAt (15);
		sItem[15]=pRecord->GetAt (16);
		sItem[16]=pRecord->GetAt (17);
		sItem[17]=pRecord->GetAt (18);
		sItem[18]=pRecord->GetAt (19);
		sItem[19]=pRecord->GetAt (20);

		sNote=pRecord->GetAt (22);

		sJS+=pRecord->GetAt (23);
		sJS+=pRecord->GetAt (24);
		sJS+=pRecord->GetAt (25);
		sJS+=pRecord->GetAt (26);
		sJS+=pRecord->GetAt (27);

		for(k=4;k<=19;k++)
		{
			m_rc.SetGridContent(2+i,k,sItem[k]);
		}

		m_rc.SetGridContent(2+i,20,sNote);
	}

	for(k=4;k<=19;k++)
	{
		m_rc.SetGridContent(2+iWeekRecordQty,k,vtos(fWeekSum[k]));
		m_rc.SetGridContent(3+iWeekRecordQty,k,vtos(fProjectSum[k]));
	}

	// fanhua test:
	m_rc.SetGridContent(4+iWeekRecordQty,0,"本周情况简述(1、项目测量工作运行情况、2、监督工作、重点是对测量工作的日常检查情况；2、测量工作存在的问题及整改要求；3、下周测量监督工作重点等):\r"+sJS, CW_GRIDWIDTH);
	m_rc.SetGridFormat(4+iWeekRecordQty,0,DT_LEFT);
	
	return;
}


