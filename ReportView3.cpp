
#include "stdafx.h"
#include "QCDB.h"
#include "MemDC.h"

#include "ReportDoc.h"
#include "ReportView.h"
#include "DlgReportShowProperty.h"
#include "MyDate.h"
#include "fhcglobal.h"

///////////////////////////////////////
// 物探工程监督整改工作汇总表
///////////////////////////////////////
void CReportView::CreateReport11()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i;
	CMyDate date;
	CStringArray *pRecord=NULL;
	int iRecordQty=pDoc->GetRecordQty ();

	/////////////////////////////////////////////////
	// 建立表格：
	/////////////////////////////////////////////////
	m_rc.SetGridQty (iRecordQty+1,6);


	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("物探工程监督整改工作汇总表");
	m_rc.SetTitle (s);

	m_rc.SetGridContent (0,0,"序号");
	m_rc.SetGridContent (0,1,"检查日期");
	m_rc.SetGridContent (0,2,"发现问题");
	m_rc.SetGridContent (0,3,"整改内容");
	m_rc.SetGridContent (0,4,"整改日期");
	m_rc.SetGridContent (0,5,"整改效果");

	//////////////////////////////////
	// Left:
	CString sMonitor="";
	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;
		date.Set(pRecord->GetAt (1),pRecord->GetAt (2),pRecord->GetAt (3));
		m_rc.SetGridContent (i+1,0,vtos(i+1));
		m_rc.SetGridContent (i+1,1,date.GetDateString ());
		m_rc.SetGridContent (i+1,2,pRecord->GetAt (4)+pRecord->GetAt (5));
		m_rc.SetGridContent (i+1,3,pRecord->GetAt (6));

		date.Set(pRecord->GetAt (7),pRecord->GetAt (8),pRecord->GetAt (9));
		m_rc.SetGridContent (i+1,4,date.GetDateString ());
		m_rc.SetGridContent (i+1,5,pRecord->GetAt (10));
		s=pRecord->GetAt (11);
		if(!IsEmpty(s))
		{
			sMonitor=s;
		}
	}

	s="施工工区："+pDoc->m_sArea +"     施工单位："+pDoc->m_sServer +pDoc->m_sCrew + "队"
		+"       施工项目："+pDoc->m_sProjectName ;
	m_rc.SetLeftUpString (s);

	s="驻队监督："+sMonitor+"                   制表："+pDoc->m_sReportCreator ;
	m_rc.SetLeftDownString (s);
	return ;
	
}


void CReportView::CreateReport12()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	CMyDate date;
	int iRecordQty=pDoc->GetRecordQty ();
	if(iRecordQty!=1)
	{
		TRACEERROR("记录数不为1:"+vtos(iRecordQty));
		return ;
	}
	CStringArray *pRecord=pDoc->GetRecord (0);

	/////////////////////////////////////////////////
	// 建立表格：
	/////////////////////////////////////////////////
	m_rc.SetGridQty (16,4);

	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s=pDoc->m_sArea +"工区地震采集施工参数一览表";
	m_rc.SetTitle (s);
	m_rc.SetLeftUpString ("编号：");
	m_rc.SetGridContent (0,0,"项 目");
	m_rc.SetGridContent (0,1,"参 数");
	m_rc.SetGridContent (0,2,"项 目");
	m_rc.SetGridContent (0,3,"参 数");

	m_rc.SetGridContent (1,0,"面元尺寸");		m_rc.SetGridContent (1,1,pRecord->GetAt (1));
	m_rc.SetGridContent (2,0,"覆盖次数");		m_rc.SetGridContent (2,1,pRecord->GetAt (2));
	m_rc.SetGridContent (3,0,"观测系统");		m_rc.SetGridContent (3,1,pRecord->GetAt (3));
	m_rc.SetGridContent (4,0,"接收道数");		m_rc.SetGridContent (4,1,pRecord->GetAt (4));
	m_rc.SetGridContent (5,0,"激发方式");		m_rc.SetGridContent (5,1,pRecord->GetAt (5));
	m_rc.SetGridContent (6,0,"采样间隔");		m_rc.SetGridContent (6,1,pRecord->GetAt (6));
	m_rc.SetGridContent (7,0,"记录长度");		m_rc.SetGridContent (7,1,pRecord->GetAt (7));
	m_rc.SetGridContent (8,0,"道    距");		m_rc.SetGridContent (8,1,pRecord->GetAt (8));
	m_rc.SetGridContent (9,0,"炮 点 距");		m_rc.SetGridContent (9,1,pRecord->GetAt (9));
	m_rc.SetGridContent (11,0,"检波器型号");	m_rc.SetGridContent (11,1,pRecord->GetAt (20));
	m_rc.SetGridContent (12,0,"检波器下井深度");m_rc.SetGridContent (12,1,pRecord->GetAt (21));
	m_rc.SetGridContent (13,0,"组合方式");		m_rc.SetGridContent (13,1,pRecord->GetAt (22));
	m_rc.SetGridContent (14,0,"井组合方式");	m_rc.SetGridContent (14,1,pRecord->GetAt (23));
	m_rc.SetGridContent (15,0,"前放增益");		m_rc.SetGridContent (15,1,pRecord->GetAt (24));


	m_rc.SetGridContent (1,2,"线    束");		m_rc.SetGridContent (1,3,pRecord->GetAt (10));
	m_rc.SetGridContent (2,2,"接收线距");		m_rc.SetGridContent (2,3,pRecord->GetAt (11));
	m_rc.SetGridContent (3,2,"炮 线 距");		m_rc.SetGridContent (3,3,pRecord->GetAt (12));
	m_rc.SetGridContent (4,2,"接收线条数");		m_rc.SetGridContent (4,3,pRecord->GetAt (13));
	m_rc.SetGridContent (5,2,"激发位置");		m_rc.SetGridContent (5,3,pRecord->GetAt (14));
	m_rc.SetGridContent (6,2,"纵向最小炮检距");	m_rc.SetGridContent (6,3,pRecord->GetAt (15));
	m_rc.SetGridContent (7,2,"纵向最大炮检距");	m_rc.SetGridContent (7,3,pRecord->GetAt (16));
	m_rc.SetGridContent (8,2,"最大炮检距");		m_rc.SetGridContent (8,3,pRecord->GetAt (17));
	m_rc.SetGridContent (9,2,"最大非纵距");		m_rc.SetGridContent (9,3,pRecord->GetAt (18));
	m_rc.SetGridContent (10,2,"最小炮检距");	m_rc.SetGridContent (10,3,pRecord->GetAt (19));
	m_rc.SetGridContent (11,2,"检波器个数");	m_rc.SetGridContent (11,3,pRecord->GetAt (25));
	m_rc.SetGridContent (12,2,"仪器型号");		m_rc.SetGridContent (12,3,pRecord->GetAt (26));
	m_rc.SetGridContent (13,2,"组合参数");		m_rc.SetGridContent (13,3,pRecord->GetAt (27));
	m_rc.SetGridContent (14,2,"井组合基距");	m_rc.SetGridContent (14,3,pRecord->GetAt (28));
	m_rc.SetGridContent (15,2,"记录密度");		m_rc.SetGridContent (15,3,pRecord->GetAt (29));

	
	return ;
	
}


//////////////////////////////////////////////////////////
// 工区主要技术人员到位情况检查表
// 表0107工区主要技术人员到位情况检查表  表13
//////////////////////////////////////////////////////////
void CReportView::CreateReport13()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	CMyDate date;
	int iRecordQty=pDoc->GetRecordQty ();

	/////////////////////////////////////////////////
	// 建立表格：
	/////////////////////////////////////////////////
	m_rc.SetGridQty (iRecordQty+1,7);

	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s=pDoc->m_sArea +"工区主要技术人员到位情况检查表";
	m_rc.SetTitle (s);
	m_rc.SetLeftUpString ("编号：");
	m_rc.SetGridContent (0,0,"岗位名称");
	m_rc.SetGridContent (0,1,"姓  名");
	m_rc.SetGridContent (0,2,"职  称");
	m_rc.SetGridContent (0,3,"年  龄");
	m_rc.SetGridContent (0,4,"文化程度");
	m_rc.SetGridContent (0,5,"工作时间");
	m_rc.SetGridContent (0,6,"到位情况");
	
	//项目负责
	int iStartRow=1;
	SetPersonData(	pDoc,
					2,
					"项目负责",
					iStartRow);

	SetPersonData(	pDoc,
					3,
					"队    长",
					iStartRow);

	SetPersonData(	pDoc,
					4,
					"书    记",
					iStartRow);

	SetPersonData(	pDoc,
					5,
					"副 队 长",
					iStartRow);

	SetPersonData(	pDoc,
					6,
					"HSE 监 督",
					iStartRow);

	SetPersonData(	pDoc,
					7,
					"施工组长",
					iStartRow);

	SetPersonData(	pDoc,
					8,
					"施工员",
					iStartRow);

	SetPersonData(	pDoc,
					9,
					"仪器组长",
					iStartRow);

	SetPersonData(	pDoc,
					10,
					"操作员",
					iStartRow);

	SetPersonData(	pDoc,
					11,
					"现场处理组长",
					iStartRow);

	SetPersonData(	pDoc,
					12,
					"现场处理员",
					iStartRow);

	SetPersonData(	pDoc,
					13,
					"测量组长",
					iStartRow);

	SetPersonData(	pDoc,
					14,
					"测量员",
					iStartRow);

	return ;
}

void CReportView::SetPersonData(CReportDoc		*pDoc,
								int				iPostOrder,
								CString			sPostName,
								int				&iStartRow)
{
	CStringArray *pRecord=NULL;
	CString sName;
	CString sPositioned;
	int i;

	CDataBrowseDoc	*pViceDoc=&(pDoc->m_docVice );

	int iStart=iStartRow;
	for(i=0;i<pDoc->GetRecordQty ();i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(IsTrue(pRecord->GetAt(iPostOrder)))
		{
			sName=pRecord->GetAt(1);
			sPositioned=pRecord->GetAt (15);
			SetRowData(sName,sPositioned,pViceDoc,iStartRow);
			iStartRow++;
		}
	}

	m_rc.CombineGrid (iStart,iStartRow-1,0,0);
	m_rc.SetGridContent(iStart,0,sPostName);
}

void CReportView::SetRowData(CString	sName, 
							 CString	sPostioned,
							 CDataBrowseDoc *pDoc,
							 int		iRow)
{
	m_rc.SetGridContent (iRow,1,sName);
	if(IsTrue(sPostioned))
	{
		m_rc.SetGridContent (iRow,6,"到位");
	}
	else
	{
		m_rc.SetGridContent (iRow,6,"未到位");
	}

	CStringArray *pRecord=NULL;
	sName.Trim ();
	CString sNameTag;
	int iRecord=-1;
	for(int i=0;i<pDoc->GetRecordQty();i++)
	{
		pRecord=pDoc->GetRecord(i);
		sNameTag=pRecord->GetAt (0);
		sNameTag.Trim ();
		if(sNameTag==sName)
		{
			iRecord=i;
			break;
		}
	}

	if(iRecord==-1)return;

	//职称
	m_rc.SetGridContent (iRow,2,pRecord->GetAt(1));


	// 年龄
	CReportDoc *pDocReport=(CReportDoc *)GetDocument();
	int iAge=pDocReport->m_iCurrYear-stof(pRecord->GetAt (2));
	m_rc.SetGridContent (iRow,3,vtos(iAge));

	// 学历:
	CString sEdu=pRecord->GetAt (3);
	CString s=pRecord->GetAt (4);
	if(!IsEmpty(s))
	{
		sEdu=s;
	}
	s=pRecord->GetAt (5);
	if(!IsEmpty(s))
	{
		sEdu=s;
	}
	m_rc.SetGridContent (iRow,4,sEdu);

	// 工作时间:
	int iWorkYear=pDocReport->m_iCurrYear-stof(pRecord->GetAt (6));
	m_rc.SetGridContent (iRow,5,vtos(iWorkYear));

	return;
}

//////////////////////////////////////////
//      工区主要设备到位情况检查表
// 表0108工区主要设备到位情况检查表  表14
//////////////////////////////////////////
void CReportView::CreateReport14()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	CMyDate date;
	int iRecordQty=pDoc->GetRecordQty ();

	/////////////////////////////////////////////////
	// 建立表格：
	/////////////////////////////////////////////////
	m_rc.SetGridQty (iRecordQty+1,5);

	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s=pDoc->m_sArea +"工区主要设备到位情况检查表";
	m_rc.SetTitle (s);
	m_rc.SetLeftUpString ("编号：");
	m_rc.SetGridContent (0,0," 用途 ");
	m_rc.SetGridContent (0,1,"  设备名称  ");
	m_rc.SetGridContent (0,2,"  设备型号  ");
	m_rc.SetGridContent (0,3,"    数量    ");
	m_rc.SetGridContent (0,4,"  到位情况  ");
	
	//项目负责
	int iStartRow=1;

	int iStart=iStartRow;
	SetInstData(pDoc,1,"仪器",iStartRow);
	SetInstData(pDoc,2,"检波器",iStartRow);
	SetInstData(pDoc,3,"采集站",iStartRow);
	SetInstData(pDoc,4,"大线",iStartRow);
	SetInstData(pDoc,5,"微机",iStartRow);
	SetInstData(pDoc,6,"GPS",iStartRow);
	SetInstData(pDoc,7,"计算机",iStartRow);
	SetInstData(pDoc,8,"打印机",iStartRow);
	SetInstData(pDoc,9,"现场处理机",iStartRow);

	m_rc.CombineGrid (iStart,iStartRow-1,0,0);
	m_rc.SetGridContent (iStart,0,"仪\r器\r及\r外\r设");

	iStart=iStartRow;
	SetInstData(pDoc,10,"钻机",iStartRow);
	SetInstData(pDoc,11,"电动冲击钻",iStartRow);
	SetInstData(pDoc,12,"炸药车",iStartRow);
	SetInstData(pDoc,13,"雷管车",iStartRow);
	SetInstData(pDoc,14,"钻井水罐车",iStartRow);
	
	m_rc.CombineGrid (iStart,iStartRow-1,0,0);
	m_rc.SetGridContent (iStart,0,"钻\r井\r生\r产");
	
	iStart=iStartRow;
	SetInstData(pDoc,15,"干钻",iStartRow);
	SetInstData(pDoc,16,"大客车",iStartRow);
	SetInstData(pDoc,17,"倒线车",iStartRow);
	SetInstData(pDoc,18,"查线车",iStartRow);
	SetInstData(pDoc,19,"放炮车",iStartRow);
	SetInstData(pDoc,20,"放线水罐车",iStartRow);
	m_rc.CombineGrid (iStart,iStartRow-1,0,0);
	m_rc.SetGridContent (iStart,0,"放\r线");


	iStart=iStartRow;
	SetInstData(pDoc,21,"车载电台",iStartRow);
	SetInstData(pDoc,22,"手持式电台",iStartRow);
	m_rc.CombineGrid (iStart,iStartRow-1,0,0);
	m_rc.SetGridContent (iStart,0,"");

	return ;

}

void CReportView::SetInstData(	CReportDoc		*pDoc,
								int				iPostOrder,
								CString			sPostName,
								int				&iStartRow)
{
	CStringArray *pRecord=NULL;
	CString sType,sQty,sPositioned;
	int i;

	int iStart=iStartRow;
	for(i=0;i<pDoc->GetRecordQty ();i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(IsTrue(pRecord->GetAt(iPostOrder)))
		{
			sType=pRecord->GetAt(23);
			sQty=pRecord->GetAt(24);
			sPositioned=pRecord->GetAt(25);
			if(IsTrue(sPositioned))
			{
				sPositioned="到位";
			}
			else
			{
				sPositioned="未到位";
			}
			m_rc.SetGridContent(iStartRow,2,sType);
			m_rc.SetGridContent(iStartRow,3,sQty);
			m_rc.SetGridContent(iStartRow,4,sPositioned);

			iStartRow++;
		}
	}

	m_rc.CombineGrid (iStart,iStartRow-1,1,1);
	m_rc.SetGridContent(iStart,1,sPostName);
}

void CReportView::CreateReport15()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j;
	CMyDate date;
	CStringArray *pRecord=NULL;
	int iRecordQty=pDoc->GetRecordQty ();

	/////////////////////////////////////////////////
	// 建立表格：
	/////////////////////////////////////////////////
	m_rc.SetGridQty (iRecordQty+2,13);
	for(i=0;i<=6;i++)
	{
		m_rc.CombineGrid (0,1,i,i);
	}
	m_rc.CombineGrid (0,0,7,8);
	m_rc.CombineGrid (0,0,9,11);
	m_rc.CombineGrid (0,1,12,12);


	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("%s项目野外采集试验工作监督统计表",pDoc->m_sProjectName );
	m_rc.SetTitle (s);	

	m_rc.SetGridContent (0,0,"序\r号");
	m_rc.SetGridContent (0,1,"试验点位置");
	m_rc.SetGridContent (0,2,"试验项目");
	m_rc.SetGridContent (0,3,"试验因素");
	m_rc.SetGridContent (0,4,"炸药\r类型");
	m_rc.SetGridContent (0,5,"固定\r因素");
	m_rc.SetGridContent (0,6,"试验\r效果");
	m_rc.SetGridContent (0,7,"试验点");
	m_rc.SetGridContent (1,7,"点数");
	m_rc.SetGridContent (1,8,"试验记录");
	m_rc.SetGridContent (0,9,"试验段");
	m_rc.SetGridContent (1,9,"段数");
	m_rc.SetGridContent (1,10,"试验记录");
	m_rc.SetGridContent (1,11,"长度");
	m_rc.SetGridContent (1,12,"试验日期");

	//////////////////////////////////
	// Left:
	CString sMonitor="";
	CMyDate dateStat;
	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;
		
		m_rc.SetGridContent (i+2,0,vtos(i+1));
		
		for(j=1;j<=11;j++)
		{
			m_rc.SetGridContent (i+2,j,pRecord->GetAt (j));
		}

		date.Set(pRecord->GetAt (12),pRecord->GetAt (13),pRecord->GetAt (14));
		m_rc.SetGridContent (i+2,12,date.GetDateString ());

		s=pRecord->GetAt (15);
		if(!IsEmpty(s))
		{
			sMonitor=s;
		}
	}

	s.Format("编号：                 统计日期：%d年%d月%d日",
							pDoc->m_iStatYear ,
							pDoc->m_iStatMonth ,
							pDoc->m_iStatDay);

	m_rc.SetLeftUpString (s);

	s.Format ("施工单位："+pDoc->m_sServer +"  "+pDoc->m_sCrew +"队");

	m_rc.SetRightUpString (s);

	s="驻队监督："+sMonitor;
	m_rc.SetLeftDownString (s);
	return ;
	
}
