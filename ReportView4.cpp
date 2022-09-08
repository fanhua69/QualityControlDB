
#include "stdafx.h"
#include "QCDB.h"
#include "MemDC.h"

#include "ReportDoc.h"
#include "ReportView.h"
#include "DlgReportShowProperty.h"
#include "MyDate.h"
#include "fhcglobal.h"
#include "math.h"


////////////////////////////////////////////////
//  ________项目野外采集施工方法监督统计表
//  表0110施工方法监督统计表 表16
////////////////////////////////////////////////
void CReportView::CreateReport16()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j;
	CMyDate date;
	CStringArray *pRecord=NULL;
	int iRecordQty=pDoc->GetRecordQty ();

	/////////////////////////////////////////////////
	// 建立表格：
	/////////////////////////////////////////////////
	m_rc.SetGridQty (iRecordQty+2,20);
	m_rc.CombineGrid (0,1,0,0);
	m_rc.CombineGrid (0,1,1,1);
	m_rc.CombineGrid (0,1,19,19);

	m_rc.CombineGrid (0,0,2,8);
	m_rc.CombineGrid (0,0,9,13);
	m_rc.CombineGrid (0,0,14,18);


	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("%s项目野外采集施工方法监督统计表",pDoc->m_sProjectName );
	m_rc.SetTitle (s);	

	m_rc.SetGridContent (0,0,"序\r号");
	m_rc.SetGridContent (0,1,"线束号");
	m_rc.SetGridContent (1,2,"仪器型号");
	m_rc.SetGridContent (1,3,"道数");
	m_rc.SetGridContent (1,4,"覆盖次数");
	m_rc.SetGridContent (1,5,"道距");
	m_rc.SetGridContent (1,6,"组合井");
	m_rc.SetGridContent (1,7,"单深井");
	m_rc.SetGridContent (1,8,"观测系统");
	m_rc.SetGridContent (1,9,"型号");
	m_rc.SetGridContent (1,10,"个数");
	m_rc.SetGridContent (1,11,"Lx");
	m_rc.SetGridContent (1,12,"Ly");
	m_rc.SetGridContent (1,13,"图形");
	m_rc.SetGridContent (1,14,"前放");
	m_rc.SetGridContent (1,15,"低截");
	m_rc.SetGridContent (1,16,"高截");
	m_rc.SetGridContent (1,17,"采样");
	m_rc.SetGridContent (1,18,"记录长度");
	m_rc.SetGridContent (1,19,"备注");

	m_rc.SetGridContent (0,2,"主    要    工    作    方    法");
	m_rc.SetGridContent (0,9,"检  波  器  组  合");
	m_rc.SetGridContent (0,14,"主  要  仪  器  因  素");
	m_rc.SetGridContent (0,19,"备注");


	//////////////////////////////////
	// Left:
	CStringArray arrayMonitor;
	CMyDate dateStat;
	CString sWell="";
	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;
		
		m_rc.SetGridContent (i+2,0,vtos(i+1));
		m_rc.SetGridContent (i+2,1,pRecord->GetAt (1));
	
		for(j=2;j<=19;j++)
		{
			m_rc.SetGridContent (i+2,j,pRecord->GetAt (j));
		}

		// 单井
		sWell="";
		for(j=0;j<5;j++)
		{
			s=pRecord->GetAt (20+j*2+1);s.Trim ();
			if(stof(s)!=0)
			{
				s+="mX";sWell+=s;
				s=pRecord->GetAt (20+j*2+2);s.Trim ();
				s+="kg\r";sWell+=s;
			}
		}

		m_rc.SetGridContent (i+2,7,sWell);

		// 组合井
		sWell="";
		for(j=0;j<5;j++)
		{
			s=pRecord->GetAt (30+j*2+1);s.Trim ();
			if(stof(s))
			{
				s+="口X";	sWell+=s;	
				s=pRecord->GetAt (30+j*2+2);s.Trim ();
				s+="mX";sWell+=s;
				s=pRecord->GetAt (30+j*2+3);s.Trim ();
				s+="kg\r";sWell+=s;
			}
		}


		m_rc.SetGridContent (i+2,6,sWell);

		AddMonitor(arrayMonitor, pRecord->GetAt (20));
	}

	s.Format("编号：                 统计日期：%d年%d月%d日",
						pDoc->m_iStatYear,
						pDoc->m_iStatMonth,
						pDoc->m_iStatDay);
	m_rc.SetLeftUpString (s);

	s.Format ("施工单位："+pDoc->m_sServer +"  "+pDoc->m_sCrew +"队");

	m_rc.SetRightUpString (s);

	s="驻队监督："+GetMonitorString(arrayMonitor);
	m_rc.SetLeftDownString (s);
	return ;
	

}

///////////////////////////////////////////////////////////////////
//  ________项目野外采集施工完成实物工作量监督统计表
//  设计工作量在表0201测线中，实际工作量在表0301监理工作日报  表17
///////////////////////////////////////////////////////////////////
void CReportView::CreateReport17()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,k;
	CMyDate date;
	CStringArray *pRecord=NULL;
	CString sLine;

	/////////////////////////////////////////////////
	// 建立表格：
	/////////////////////////////////////////////////
	int iRecordQty=pDoc->GetRecordQty ();
	m_rc.SetGridQty (iRecordQty+3,20);
	m_rc.CombineGrid (0,2,0,0);
	m_rc.CombineGrid (0,2,1,1);
	m_rc.CombineGrid (0,2,19,19);
	m_rc.CombineGrid (0,2,20,20);

	for(i=2;i<=8;i++)
	{
		m_rc.CombineGrid (1,2,i,i);
	}

	for(i=17;i<=18;i++)
	{
		m_rc.CombineGrid (1,2,i,i);
	}

	m_rc.CombineGrid (0,0,2,4);
	m_rc.CombineGrid (0,0,5,18);
	m_rc.CombineGrid (1,1,9,10);
	m_rc.CombineGrid (1,1,11,12);
	m_rc.CombineGrid (1,1,13,14);
	m_rc.CombineGrid (1,1,15,16);

	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("%s项目野外采集施工完成实物工作量监督统计表",pDoc->m_sProjectName );
	m_rc.SetTitle (s);	


	m_rc.SetGridContent (0,0,"序\r号");
	m_rc.SetGridContent (0,1,"线束号");
	m_rc.SetGridContent (2,2,"满覆盖\r长度");
	m_rc.SetGridContent (2,3,"满覆盖\r面积");
	m_rc.SetGridContent (2,4,"物理\r点数");
	m_rc.SetGridContent (2,5,"满覆盖\r长度");
	m_rc.SetGridContent (2,6,"满覆盖\r面积");
	m_rc.SetGridContent (2,7,"炮数");
	m_rc.SetGridContent (2,8,"加\r密\r炮\r数");
	m_rc.SetGridContent (2,9,"张\r数");
	m_rc.SetGridContent (2,10,"%");
	m_rc.SetGridContent (2,11,"张\r数");
	m_rc.SetGridContent (2,12,"%");
	m_rc.SetGridContent (2,13,"张\r数");
	m_rc.SetGridContent (2,14,"%");
	m_rc.SetGridContent (2,15,"个\r数");
	m_rc.SetGridContent (2,16,"%");
	m_rc.SetGridContent (2,17,"合格\r小折射\r点数");
	m_rc.SetGridContent (2,18,"合格\r微测井\r点数");
	m_rc.SetGridContent (2,19,"施工日期");
	m_rc.SetGridContent (2,20,"备注");

	m_rc.SetGridContent (0,2,"设 计 工 作 量");
	m_rc.SetGridContent (0,5,"实 际 完 成 实 物 工 作 量");
	m_rc.SetGridContent (1,9,"一级品");
	m_rc.SetGridContent (1,11,"二级品");
	m_rc.SetGridContent (1,13,"废品");
	m_rc.SetGridContent (1,15,"空点");


	//////////////////////////////////
	// Left:
	float f3DDesiAreaQty=stof(pDoc->m_s3DDesiWorkAreaQty );
	int i2DDesiShotQty=stof(pDoc->m_s2DDesiShotQty);
	int i3DDesiShotQty=stof(pDoc->m_s3DDesiShotQty);

	CString sMonitor="";
	CMyDate dateStat;
	CString sWell="";
	float f2DShotQty=0.0;
	float f3DShotQty=0.0;
	float fAreaQty=0.0;
	float fKiloQty=0.0;
	float fSum[19];
	float f=0.0;
	int  iTotalShot=0,iValidShot=0;
	int iDailyRecordQty=pDoc->m_docVice .GetRecordQty ();
	CStringArray *pDailyRecord=NULL;
	CMyDate dateStart;
	CMyDate dateEnd;
	dateStart.SetYear (100000);
	dateEnd.SetYear (0);

	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;
		
		m_rc.SetGridContent (i+3,0,vtos(i+1));
		m_rc.SetGridContent (i+3,1,pRecord->GetAt (1));

		// 满覆盖长度
		fKiloQty=stof(pRecord->GetAt (2));
		m_rc.SetGridContent (i+3,2,vtos(fKiloQty));

		// 满覆盖面积
		f2DShotQty=stof(pRecord->GetAt (3));
		f3DShotQty=stof(pRecord->GetAt (4));
		if(i3DDesiShotQty!=0)
		{
			fAreaQty=f3DShotQty/i3DDesiShotQty*f3DDesiAreaQty;
		}
		else
		{
			fAreaQty=0;
		}
		m_rc.SetGridContent (i+3,3,vtos(fAreaQty,2));

		// 物理点数
		if(pDoc->m_bIs3D )
		{
			m_rc.SetGridContent (i+3,4,vtos(f3DShotQty,0));
		}
		else
		{
			m_rc.SetGridContent (i+3,4,vtos(f2DShotQty,0));
		}

		// 对本测线求和：
		for(j=0;j<19;j++)
		{
			fSum[j]=0.0;
		}
		for(j=0;j<iDailyRecordQty;j++)
		{
			pDailyRecord=pDoc->m_docVice.GetRecord (j);
			if(pDailyRecord->GetAt (0)!=pRecord->GetAt (0))continue;
			for(k=13;k<=32;k++)
			{
				fSum[7]+=stof(pDailyRecord->GetAt (k));
			}
			
			fSum[8]+=stof(pDailyRecord->GetAt (2));

			fSum[9]+=stof(pDailyRecord->GetAt (3));
			fSum[11]+=stof(pDailyRecord->GetAt (4));
			fSum[13]+=stof(pDailyRecord->GetAt (5));
			fSum[15]+=stof(pDailyRecord->GetAt (6));

			fSum[17]+=stof(pDailyRecord->GetAt (7));
			fSum[18]+=stof(pDailyRecord->GetAt (8));

			// 起始施工日期:
			date.Set(pDailyRecord->GetAt (9),pDailyRecord->GetAt (10),pDailyRecord->GetAt (11));
			if(date>dateEnd)
			{
				dateEnd=date;
			}
			if(date<dateStart)
			{
				dateStart=date;
			}

			// 驻队监督
			s=pDailyRecord->GetAt (12);
			if(!IsEmpty(s))
			{
				if(sMonitor!="")
				{
					sMonitor+=",";
				}
				sMonitor+=s;
			}
		}

		// 
		iValidShot=fSum[7]-fSum[8];
		if(f2DShotQty!=0)
		{
			fSum[5]=iValidShot/f2DShotQty*fKiloQty;
		}

		if(f3DShotQty!=0)
		{
			fSum[6]=iValidShot/f3DShotQty*fAreaQty;
		}

		iTotalShot=fSum[7]+fSum[8];
		if(iTotalShot!=0)
		{
			fSum[10]=fSum[9]/iTotalShot*100;
			fSum[12]=fSum[11]/iTotalShot*100;
			fSum[14]=fSum[13]/iTotalShot*100;
			fSum[16]=fSum[15]/iTotalShot*100;
		}

		// 设置数据:
		m_rc.SetGridContent (i+3,5,vtos(fSum[5],2));
		m_rc.SetGridContent (i+3,6,vtos(fSum[6],2));
		m_rc.SetGridContent (i+3,7,vtos(fSum[7],0));
		m_rc.SetGridContent (i+3,8,vtos(fSum[8],0));
		m_rc.SetGridContent (i+3,9,vtos(fSum[9],0));
		m_rc.SetGridContent (i+3,10,vtos(fSum[10],2));
		m_rc.SetGridContent (i+3,11,vtos(fSum[11],0));
		m_rc.SetGridContent (i+3,12,vtos(fSum[12],2));
		m_rc.SetGridContent (i+3,13,vtos(fSum[13],0));
		m_rc.SetGridContent (i+3,14,vtos(fSum[14],2));
		m_rc.SetGridContent (i+3,15,vtos(fSum[15],0));
		m_rc.SetGridContent (i+3,16,vtos(fSum[16],2));
		m_rc.SetGridContent (i+3,17,vtos(fSum[17],0));
		m_rc.SetGridContent (i+3,18,vtos(fSum[18],0));

		// 日期
		m_rc.SetGridContent (i+3,19,dateStart.GetDateString ()+"-\r"+dateEnd.GetDateString ());

	}

	s.Format("编号：                 统计日期：%d年%d月%d日",pDoc->m_iStatYear ,pDoc->m_iStatMonth ,pDoc->m_iStatDay );
	m_rc.SetLeftUpString (s);

	s.Format ("施工单位："+pDoc->m_sServer +"  "+pDoc->m_sCrew +"队");

	m_rc.SetRightUpString (s);

	s="驻队监督："+sMonitor;
	m_rc.SetLeftDownString (s);
	return ;


}

void CReportView::CheckWellKindQty(	CDataBrowseDoc *pDoc,
									CWellProperty  *pSingleWell,
									CWellProperty  *pMultiWell,
									int &iSingleWellKindQty,
									int &iMultiWellKindQty)
{
	int iRecordQty=pDoc->GetRecordQty ();
	int i=0,j=0;
	CStringArray *pRecord=NULL;

	iSingleWellKindQty=0;
	iMultiWellKindQty=0;

	int n=0;
	CString s;
	float f;

	int bSingleValid[10],bMultiValid[10];
	memset(bSingleValid,0,sizeof(int)*10);
	memset(bMultiValid,0,sizeof(int)*10);

	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord(i);
		
		for(j=1;j<=10;j++)
		{
			s=pRecord->GetAt (j);
			f=stof(s);
			if(fabs(f)>0.00001)
			{
				bSingleValid[j-1]=1;
			}
		}

		for(j=11;j<=20;j++)
		{
			s=pRecord->GetAt (j);
			f=stof(s);
			if(fabs(f)>0.00001)
			{
				bMultiValid[j-11]=1;
			}
		}
	}

	int iOrder=0;
	for(i=0;i<10;i++)
	{
		pSingleWell[i].iValidOrder=-1;
		if(bSingleValid[i]!=0)
		{
			pSingleWell[i].iValidOrder = iOrder;
			iOrder++;
		}
	}
	iSingleWellKindQty=iOrder;

	iOrder=0;
	for(i=0;i<10;i++)
	{
		pMultiWell[i].iValidOrder=-1;
		if(bMultiValid[i]!=0)
		{
			pMultiWell[i].iValidOrder = iOrder;
			iOrder++;
		}
	}
	iMultiWellKindQty=iOrder;




	return;
}

int CReportView::GetFinishedShotQty(CDataBrowseDoc *pDoc,
									CString sLineNo,
									CWellProperty *pSSP,
									CWellProperty *pMSP,
									int &iHVLQty,
									CString &sNote,
									CString &sMonitor)
{
	sLineNo.Trim();
	sLineNo.MakeUpper();

	CString sNoLine;
	CStringArray *pRecord=NULL;
	CStringArray arrayMonitor;
	int i,j;
	int iShotQty=0;
	CString s;

	for(j=0;j<10;j++)
	{
		pSSP[j].iQty =0;
		pMSP[j].iQty =0;
	}
	iHVLQty=0;

	for(i=0;i<pDoc->GetRecordQty();i++)
	{
		pRecord=pDoc->GetRecord(i);
		sNoLine=pRecord->GetAt(0);
		sNoLine.Trim();
		sNoLine.MakeUpper();
		if(sNoLine==sLineNo)
		{
			for(j=1;j<=10;j++)
			{
				pSSP[j-1].iQty +=stof(pRecord->GetAt (j));
				iShotQty+=pSSP[j-1].iQty;
			}
			for(j=11;j<=20;j++)
			{
				pMSP[j-11].iQty +=stof(pRecord->GetAt (j));
				iShotQty+=pMSP[j-11].iQty;
			}

			iHVLQty+=stof(pRecord->GetAt (11));

			// The note string:
			s=pRecord->GetAt (12);
			s.Trim ().MakeUpper ();
			if(s!=""&&s!="NULL")
			{
				sNote+=s;
			}

			AddMonitor(arrayMonitor,pRecord->GetAt (13));
		}
	}

	sMonitor=GetMonitorString(arrayMonitor);

	return iShotQty;
}


CString CReportView::GetChineseNumber(int i)
{
	switch (i)
	{
	case 0:
		return "零";
	case 1 :
		return "一";
	case 2 :
		return "二";
	case 3 :
		return "三";
	case 4 :
		return "四";
	case 5 :
		return "五";
	case 6 :
		return "六";
	case 7 :
		return "七";
	case 8 :
		return "八";
	case 9 :
		return "九";
	case 10:
		return "十";
	default:
		ASSERT(false);
		return "超限";
	}		
}

///////////////////////////////////////////////////
//  年度           地震勘探激发因素统计表
//           （表0201测线）  表18
///////////////////////////////////////////////////
void CReportView::CreateReport18()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,n;
	CMyDate date;
	CStringArray *pRecord=NULL;
	CString sLine;
	int iStart=0;

	CWellProperty CSingleWell[10];
	CWellProperty CMultiWell[10];
	for(i=0;i<10;i++)
	{
		memcpy(&CSingleWell[i],&pDoc->m_CSingleWell[i],sizeof(CWellProperty));
		memcpy(&CMultiWell[i],&pDoc->m_CMultiWell[i]  ,sizeof(CWellProperty));
	}

	int iSingleWellQty=0,iMultiWellQty=0;
	CheckWellKindQty(pDoc,
					CSingleWell,
					CMultiWell,
					iSingleWellQty,
					iMultiWellQty);

	/////////////////////////////////////////////////
	// 建立表格：
	/////////////////////////////////////////////////
	int iRecordQty=pDoc->m_docVice .GetRecordQty ();
	m_rc.SetGridQty (iRecordQty+3,iSingleWellQty*3+ iMultiWellQty*4+9 );
	for(i=0;i<=3;i++)
	{
		m_rc.CombineGrid (0,1,i,i);
	}
	for(i=0;i<iSingleWellQty;i++)
	{
		m_rc.CombineGrid (0,0,4+i*3,4+i*3+2);
	}

	for(i=0;i<iMultiWellQty;i++)
	{
		iStart=4+iSingleWellQty*3;
		m_rc.CombineGrid (0,0,iStart+i*4,iStart+i*4+3);
	}

	iStart=4+iSingleWellQty*3+iMultiWellQty*4;
	m_rc.CombineGrid (0,0,iStart,iStart+4);
	m_rc.CombineGrid (iRecordQty+2,iRecordQty+2,0,1);


	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("%s年度%s地震勘探激发因素统计表",pDoc->m_sYear , pDoc->m_sProjectName );
	m_rc.SetTitle (s);	


	m_rc.SetGridContent (0,0,"序\r号");
	m_rc.SetGridContent (0,1,"测线号");
	m_rc.SetGridContent (0,2,"设计\r炮数");
	m_rc.SetGridContent (0,3,"完成\r炮数");

	for(i=0;i<iSingleWellQty;i++)
	{
		iStart=4+i*3;
		m_rc.SetGridContent (0,iStart,"单井激发("+GetChineseNumber(i+1)+")");
		m_rc.SetGridContent (1,iStart,"井深\r(m)");
		m_rc.SetGridContent (1,iStart+1,"药量\r(Kg)");
		m_rc.SetGridContent (1,iStart+2,"激发\r点数");
	}

	for(i=0;i<iMultiWellQty;i++)
	{
		iStart=4+iSingleWellQty*3+i*4;
		m_rc.SetGridContent (0,iStart,"组合激发("+GetChineseNumber(i+1)+")");
		m_rc.SetGridContent (1,iStart,"口数");
		m_rc.SetGridContent (1,iStart+1,"井深\r(m)");
		m_rc.SetGridContent (1,iStart+2,"药量\r(Kg)");
		m_rc.SetGridContent (1,iStart+3,"激发\r点数");
	}
	
	iStart=4+iSingleWellQty*3+iMultiWellQty*4;
	
	m_rc.SetGridContent (0,iStart,"激发位置");
	m_rc.SetGridContent (1,iStart,"高速\r层激\r发数");
	m_rc.SetGridContent (1,iStart+1,"占总数\r的(%)");
	m_rc.SetGridContent (1,iStart+2,"降速\r层激\r发数");
	m_rc.SetGridContent (1,iStart+3,"占总数\r的(%)");
	m_rc.SetGridContent (1,iStart+4,"备  注");

	m_rc.SetGridContent (iRecordQty+2,0,"合  计");

	//////////////////////////////////
	// Left:
	float f3DDesiAreaQty=stof(pDoc->m_s3DDesiWorkAreaQty );
	int i2DDesiShotQty=stof(pDoc->m_s2DDesiShotQty);
	int i3DDesiShotQty=stof(pDoc->m_s3DDesiShotQty);

	CString sMonitor="";
	float f=0.0;

	iRecordQty=pDoc->m_docVice .GetRecordQty(); 

	CString sNo;
	CStringArray *pRecordLine=NULL;
	int iFinishedShotQty=0;

	int iWellOrder=0;
	int iHVLQty=0;
	CString sNote;

	float *pfSum=new float[9+iSingleWellQty*3+iMultiWellQty*4+10];
	memset(pfSum,0,sizeof(float)*(9+iSingleWellQty*3+iMultiWellQty*4+10));

	for(i=0;i<iRecordQty;i++)
	{
		pRecordLine=pDoc->m_docVice .GetRecord (i);
		if(!pRecordLine)break;
		
		m_rc.SetGridContent (i+2,0,vtos(i+1));
		
		sNo=pRecordLine->GetAt (0);
		m_rc.SetGridContent (i+2,1,pRecordLine->GetAt (1));
		if(pDoc->m_bIs3D )
		{
			m_rc.SetGridContent (i+2,2,pRecordLine->GetAt (3));
			pfSum[2]+=stof(pRecordLine->GetAt (3));
		}
		else
		{
			m_rc.SetGridContent (i+2,2,pRecordLine->GetAt (2));
			pfSum[2]+=stof(pRecordLine->GetAt (2));
		}

		sNote="";
		iFinishedShotQty=GetFinishedShotQty(pDoc,
											sNo,
											CSingleWell,
											CMultiWell,
											iHVLQty,
											sNote,
											sMonitor);

		m_rc.SetGridContent (i+2,3,vtos(iFinishedShotQty));
		pfSum[3]+=iFinishedShotQty;

		// 单井属性
		for(j=0;j<10;j++)
		{
			if(CSingleWell[j].iQty !=0)
			{
				n=4+CSingleWell[j].iValidOrder *3;
				m_rc.SetGridContent (i+2,n,vtos(CSingleWell[j].fDepth ));
				m_rc.SetGridContent (i+2,n+1,vtos(CSingleWell[j].fDynamite ) );
				m_rc.SetGridContent (i+2,n+2,vtos(CSingleWell[j].iQty ));

				pfSum[n]+=CSingleWell[j].fDepth ;
				pfSum[n+1]+=CSingleWell[j].fDynamite ;
				pfSum[n+2]+=CSingleWell[j].iQty ;
			}
		}

		// 多井属性
		iStart=4+iSingleWellQty*3;
		for(j=0;j<10;j++)
		{
			if(CMultiWell[j].iQty !=0)
			{
				n=iStart+CMultiWell[j].iValidOrder*4;
				m_rc.SetGridContent (i+2,n,vtos(CMultiWell[j].iComboQty ) );
				m_rc.SetGridContent (i+2,n+1,vtos(CMultiWell[j].fDepth ));
				m_rc.SetGridContent (i+2,n+2,vtos(CMultiWell[j].fDynamite ) );
				m_rc.SetGridContent (i+2,n+3,vtos(CMultiWell[j].iQty ));
			
				pfSum[n]+=CMultiWell[j].iComboQty ;
				pfSum[n+1]+=CMultiWell[j].fDepth ;
				pfSum[n+2]+=CMultiWell[j].fDynamite ;
				pfSum[n+3]+=CMultiWell[j].iQty ;
			}
		}

		// 激发位置:
		iStart=4+iSingleWellQty*3+iMultiWellQty*4;
		m_rc.SetGridContent (i+2,iStart,vtos(iHVLQty));
		pfSum[iStart]+=iHVLQty ;

		f=iHVLQty/(float)iFinishedShotQty*100;
		m_rc.SetGridContent (i+2,iStart+1,vtos(f,2));
		pfSum[iStart+1]+=f/iRecordQty ;

		m_rc.SetGridContent (i+2,iStart+2,vtos(iFinishedShotQty-iHVLQty));
		pfSum[iStart+2]+=iFinishedShotQty-iHVLQty ;

		m_rc.SetGridContent (i+2,iStart+3,vtos(100-f,2));
		pfSum[iStart+3]+=(100-f)/iRecordQty ;
		
		//备   注
		m_rc.SetGridContent (i+2,iStart+4,sNote);
	}

	for(i=2;i<=iStart+3;i++)
	{
		m_rc.SetGridContent (iRecordQty+2,i,vtos((int)(pfSum[i])));
	}
	m_rc.SetGridContent (iRecordQty+2,iStart+1,vtos(pfSum[iStart+1],2));
	m_rc.SetGridContent (iRecordQty+2,iStart+3,vtos(pfSum[iStart+3],2));


	s.Format ("编号:         项目名称：%s    投资方：%s    作业方：%s",
		pDoc->m_sProjectName ,
		pDoc->m_sClient ,
		pDoc->m_sServer +pDoc->m_sCrew +"队");
	m_rc.SetLeftUpString (s);

	s="现场监督："+sMonitor;
	m_rc.SetRightUpString (s);

	s="制表： "+pDoc->m_sReportCreator ;
	m_rc.SetLeftDownString (s);

	s="审核： "+pDoc->m_sReportAuditor;
	m_rc.SetRightDownString (s);

	delete []pfSum;

	return ;
}



int CReportView::GetClassify(CDataBrowseDoc *pDoc,
							CString sLineNo,
							CClassify *pClassify,
							CString &sMonitor)
{
	sLineNo.Trim();
	sLineNo.MakeUpper();

	CString sNoLine;
	CStringArray *pRecord=NULL;
	int i,j;
	int iShotQty=0;
	pClassify->Reset ();
	CStringArray arrayMonitor;

	for(i=0;i<pDoc->GetRecordQty();i++)
	{
		pRecord=pDoc->GetRecord(i);
		sNoLine=pRecord->GetAt(0);
		sNoLine.Trim();
		sNoLine.MakeUpper();
		if(sNoLine==sLineNo)
		{
			pClassify->iInitFirst	= stof(pRecord->GetAt (11));
			pClassify->iInitSecond	= stof(pRecord->GetAt (12));
			pClassify->iInitBad		= stof(pRecord->GetAt (13));
			pClassify->iInitBlank	= stof(pRecord->GetAt (14));

			iShotQty+=pClassify->iInitFirst;
			iShotQty+=pClassify->iInitSecond;
			iShotQty+=pClassify->iInitBad;

			pClassify->iReFirst		= stof(pRecord->GetAt (15));
			pClassify->iReSecond	= stof(pRecord->GetAt (16));
			pClassify->iReBad		= stof(pRecord->GetAt (17));
			pClassify->iReBlank		= stof(pRecord->GetAt (18));


			pClassify->iRefTotal 	= stof(pRecord->GetAt (19));
			pClassify->iRefValid	= stof(pRecord->GetAt (20));
			pClassify->iMicroWellTotal = stof(pRecord->GetAt (21));
			pClassify->iMicroWellValid = stof(pRecord->GetAt (22));
			
			if(!IsEmpty(pRecord->GetAt (23)))
			{
				pClassify->sNote +=pRecord->GetAt (23);
			}

			AddMonitor(arrayMonitor,pRecord->GetAt (24));
		}
	}

	sMonitor=GetMonitorString(arrayMonitor);

	return iShotQty;
}

///////////////////////////////////////////////
//  地震采集监视记录初、复评对照表
//     （表6监理日报）  表19
///////////////////////////////////////////////
void CReportView::CreateReport19()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,n;
	CMyDate date;
	CStringArray *pRecord=NULL;
	CString sLine;

	int iSingleWellQty=0,iMultiWellQty=0;

	/////////////////////////////////////////////////
	// 建立表格：
	/////////////////////////////////////////////////
	int iRecordQty=pDoc->m_docVice .GetRecordQty ();
	m_rc.SetGridQty (iRecordQty+4,26 );
	m_rc.CombineGrid (0,2,0,0);
	m_rc.CombineGrid (0,2,1,1);
	m_rc.CombineGrid (0,2,2,2);
	m_rc.CombineGrid (0,2,3,3);

	m_rc.CombineGrid (0,0,4,11);
	m_rc.CombineGrid (1,1,4,5);
	m_rc.CombineGrid (1,1,6,7);
	m_rc.CombineGrid (1,1,8,9);
	m_rc.CombineGrid (1,1,10,11);

	m_rc.CombineGrid (0,0,12,19);
	m_rc.CombineGrid (1,1,12,13);
	m_rc.CombineGrid (1,1,14,15);
	m_rc.CombineGrid (1,1,16,17);
	m_rc.CombineGrid (1,1,18,19);

	m_rc.CombineGrid (0,2,20,20);

	m_rc.CombineGrid (0,0,21,22);
	m_rc.CombineGrid (1,2,21,21);
	m_rc.CombineGrid (1,2,22,22);
	m_rc.CombineGrid (0,0,23,24);
	m_rc.CombineGrid (1,2,23,23);
	m_rc.CombineGrid (1,2,24,24);

	m_rc.CombineGrid (0,2,25,25);

	m_rc.CombineGrid (iRecordQty+3,iRecordQty+3,0,1);

	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("地震采集监视记录初、复评对照表");
	m_rc.SetTitle (s);	


	m_rc.SetGridContent (0,0,"序\r号");
	m_rc.SetGridContent (0,1,"测线号");
	m_rc.SetGridContent (0,2,"设计\r炮数");
	m_rc.SetGridContent (0,3,"完成\r炮数");

	m_rc.SetGridContent (0,4,"初    评");
	m_rc.SetGridContent (1,4,"一级");
	m_rc.SetGridContent (1,6,"二级");
	m_rc.SetGridContent (1,8,"废炮");
	m_rc.SetGridContent (1,10,"空点");

	m_rc.SetGridContent (1,12,"一级");
	m_rc.SetGridContent (1,14,"二级");
	m_rc.SetGridContent (1,16,"废炮");
	m_rc.SetGridContent (1,18,"空点");

	for(i=4;i<=18;i+=2)
	{
		m_rc.SetGridContent (2,i,"张数");
		m_rc.SetGridContent (2,i+1,"%");
	}

	m_rc.SetGridContent (0,20,"初复\r评一\r级差");
	m_rc.SetGridContent (0,21,"小折射");
	m_rc.SetGridContent (0,23,"微测井");

	m_rc.SetGridContent (1,21,"点数");
	m_rc.SetGridContent (1,22,"合格");
	m_rc.SetGridContent (1,23,"点数");
	m_rc.SetGridContent (1,24,"合格");
	m_rc.SetGridContent (0,25,"备   注");


	m_rc.SetGridContent (iRecordQty+3,0,"合  计");

	//////////////////////////////////
	// Left:
	float f3DDesiAreaQty=stof(pDoc->m_s3DDesiWorkAreaQty );
	int i2DDesiShotQty=stof(pDoc->m_s2DDesiShotQty);
	int i3DDesiShotQty=stof(pDoc->m_s3DDesiShotQty);

	CString sMonitor="";
	float f=0.0;

	iRecordQty=pDoc->m_docVice .GetRecordQty(); 

	CString sNo;
	CStringArray *pRecordLine=NULL;
	int iFinishedShotQty=0;

	int iWellOrder=0;
	int iHVLQty=0;
	CString sNote;

	float *pfSum=new float[25];
	memset(pfSum,0,sizeof(float)*25);

	CClassify classify;
	int iDesiShotQty=0;
	float fRate=0.0;

	for(i=0;i<iRecordQty;i++)
	{
		pRecordLine=pDoc->m_docVice .GetRecord (i);
		if(!pRecordLine)break;
		
		m_rc.SetGridContent (i+3,0,vtos(i+1));
		
		sNo=pRecordLine->GetAt (0);
		m_rc.SetGridContent (i+3,1,pRecordLine->GetAt (1));
		if(pDoc->m_bIs3D )
		{
			m_rc.SetGridContent (i+3,2,pRecordLine->GetAt (3));
			iDesiShotQty=stof(pRecordLine->GetAt (3));
		}
		else
		{
			m_rc.SetGridContent (i+3,2,pRecordLine->GetAt (2));
			iDesiShotQty=stof(pRecordLine->GetAt (2));
		}
		pfSum[2]+=iDesiShotQty;

		iFinishedShotQty=GetClassify(pDoc,sNo,&classify,sMonitor);

		m_rc.SetGridContent (i+3,3,vtos(iFinishedShotQty));
		pfSum[3]+=iFinishedShotQty;

		// 初评
		m_rc.SetGridContent (i+3,4,vtos(classify.iInitFirst ));
		pfSum[4]+=classify.iInitFirst;

		fRate=classify.iInitFirst/(float)iDesiShotQty*100.0;
		m_rc.SetGridContent (i+3,5,vtos(fRate,2));
		pfSum[5]+=fRate/iRecordQty;

		m_rc.SetGridContent (i+3,6,vtos(classify.iInitSecond ));
		pfSum[6]+=classify.iInitSecond;

		fRate=classify.iInitSecond/(float)iDesiShotQty*100.0;
		m_rc.SetGridContent (i+3,7,vtos(fRate,2));
		pfSum[7]+=fRate/iRecordQty;

		m_rc.SetGridContent (i+3,8,vtos(classify.iInitBad ));
		pfSum[8]+=classify.iInitBad;

		fRate=classify.iInitBad/(float)iDesiShotQty*100.0;
		m_rc.SetGridContent (i+3,9,vtos(fRate,2));
		pfSum[9]+=fRate/iRecordQty;

		m_rc.SetGridContent (i+3,10,vtos(classify.iInitBlank ));
		pfSum[10]+=classify.iInitBlank;

		fRate=classify.iInitBlank/(float)iDesiShotQty*100.0;
		m_rc.SetGridContent (i+3,11,vtos(fRate,2));
		pfSum[11]+=fRate/iRecordQty;


		// 复评
		m_rc.SetGridContent (i+3,12,vtos(classify.iReFirst));
		pfSum[12]+=classify.iReFirst;

		fRate=classify.iReFirst/(float)iDesiShotQty*100.0;
		m_rc.SetGridContent (i+3,13,vtos(fRate,2));
		pfSum[13]+=fRate/iRecordQty;

		m_rc.SetGridContent (i+3,14,vtos(classify.iReSecond ));
		pfSum[14]+=classify.iReSecond;

		fRate=classify.iReSecond/(float)iDesiShotQty*100.0;
		m_rc.SetGridContent (i+3,15,vtos(fRate,2));
		pfSum[15]+=fRate/iRecordQty;

		m_rc.SetGridContent (i+3,16,vtos(classify.iReBad ));
		pfSum[16]+=classify.iReBad;

		fRate=classify.iReBad/(float)iDesiShotQty*100.0;
		m_rc.SetGridContent (i+3,17,vtos(fRate,2));
		pfSum[17]+=fRate/iRecordQty;

		m_rc.SetGridContent (i+3,18,vtos(classify.iReBlank ));
		pfSum[18]+=classify.iReBlank;

		fRate=classify.iReBlank/(float)iDesiShotQty*100.0;
		m_rc.SetGridContent (i+3,19,vtos(fRate,2));
		pfSum[19]+=fRate/iRecordQty;
		
		// 
		m_rc.SetGridContent (i+3,20,vtos(classify.iInitFirst -classify.iReFirst ));
		pfSum[20]+=classify.iInitFirst -classify.iReFirst;
		
		// 小折射:
		m_rc.SetGridContent (i+3,21,vtos(classify.iRefTotal ));
		pfSum[21]+=classify.iRefTotal;

		m_rc.SetGridContent (i+3,22,vtos(classify.iRefValid ));
		pfSum[22]+=classify.iRefValid;

		// 微测井:
		m_rc.SetGridContent (i+3,23,vtos(classify.iMicroWellTotal ));
		pfSum[23]+=classify.iMicroWellTotal;

		m_rc.SetGridContent (i+3,24,vtos(classify.iMicroWellValid ));
		pfSum[24]+=classify.iMicroWellValid;

		//备   注
		m_rc.SetGridContent (i+3,25,classify.sNote);
	}

	for(i=2;i<=24;i++)
	{
		m_rc.SetGridContent (iRecordQty+3,i,vtos((int)(pfSum[i])));
	}

	for(i=5;i<=19;i+=2)
	{
		m_rc.SetGridContent (iRecordQty+3,i,vtos(pfSum[i],2));
	}


	s.Format ("编号:         项目名称：%s    投资方：%s    作业方：%s",
		pDoc->m_sProjectName ,
		pDoc->m_sClient ,
		pDoc->m_sServer +pDoc->m_sCrew +"队");
	m_rc.SetLeftUpString (s);

	s="现场监督："+sMonitor;
	m_rc.SetRightUpString (s);

	s="制表： "+pDoc->m_sReportCreator ;
	m_rc.SetLeftDownString (s);

	s="审核： "+pDoc->m_sReportAuditor;
	m_rc.SetRightDownString (s);

	delete []pfSum;

	return ;
}


/////////////////////////////////////////////////
//  物探工程原始记录监督复评降级文件登记表
//表0403原始记录监督复评降级文件登记表  表20 
/////////////////////////////////////////////////
void CReportView::CreateReport20()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,n;
	CMyDate date;
	CStringArray *pRecord=NULL;
	CString sLine;

	int iSingleWellQty=0,iMultiWellQty=0;

	/////////////////////////////////////////////////
	// 建立表格：
	/////////////////////////////////////////////////
	int iRecordQty=pDoc->GetRecordQty ();
	m_rc.SetGridQty (iRecordQty+3,11);
	m_rc.CombineGrid (0,1,0,0);
	m_rc.CombineGrid (0,1,1,1);
	m_rc.CombineGrid (0,1,2,2);
	m_rc.CombineGrid (0,1,3,3);

	m_rc.CombineGrid (0,0,4,10);

	m_rc.CombineGrid (iRecordQty+2,iRecordQty+2,0,1);

	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("物探工程原始记录监督复评降级文件登记表");
	m_rc.SetTitle (s);	


	m_rc.SetGridContent (0,0,"序\r号");
	m_rc.SetGridContent (0,1,"文件号");
	m_rc.SetGridContent (0,2,"合格");
	m_rc.SetGridContent (0,3,"废品");

	m_rc.SetGridContent (0,4,"降       级       原       因");
	m_rc.SetGridContent (1,4,"目的层");
	m_rc.SetGridContent (1,5,"工作道");
	m_rc.SetGridContent (1,6,"初至时间");
	m_rc.SetGridContent (1,7,"能量");

	m_rc.SetGridContent (1,8,"干扰");
	m_rc.SetGridContent (1,9,"τ值");
	m_rc.SetGridContent (1,10,"其它");



	m_rc.SetGridContent (iRecordQty+2,0,"合  计");

	//////////////////////////////////
	// Left:
	CString sMonitor="";
	float f=0.0;

	iRecordQty=pDoc->GetRecordQty(); 

	CStringArray *pRecordLine=NULL;
	int iFinishedShotQty=0;

	float *pfSum=new float[11];
	memset(pfSum,0,sizeof(float)*11);

	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;
		
		m_rc.SetGridContent (i+2,0,vtos(i+1));
		m_rc.SetGridContent (i+2,1,pRecord->GetAt (0));

		for(j=1;j<=9;j++)
		{
			s=pRecord->GetAt (j);
			if(IsTrue(s))
			{
				m_rc.SetGridContent (i+2,j+1,"是");
				pfSum[j+1]+=stof(s);
			}
		}
	}

	//总和：
	for(i=2;i<=10;i++)
	{
		m_rc.SetGridContent (iRecordQty+2,i,vtos((int)(pfSum[i])));
	}


	s.Format ("工区：%s      测线或线束号：%s",
		pDoc->m_sArea ,
		pDoc->m_sLineName );
	m_rc.SetLeftUpString (s);

	// 现场监督:
	sMonitor="";
	for(i=0;i<pDoc->m_docVice.GetRecordQty();i++)
	{
		pRecord=pDoc->m_docVice.GetRecord (i);

		// 驻队监督
		s=pRecord->GetAt (0);
		if(!IsEmpty(s))
		{
			if(sMonitor!="")
			{
				sMonitor+=",";
			}
			sMonitor+=s;
		}
	}
	s="现场监督："+sMonitor;
	m_rc.SetRightUpString (s);

	s="制表： "+pDoc->m_sReportCreator ;
	m_rc.SetLeftDownString (s);


	delete []pfSum;

	return ;
}

