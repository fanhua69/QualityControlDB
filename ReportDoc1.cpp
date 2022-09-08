
#include "stdafx.h"
#include "QCDB.h"
#include "ReportDoc.h"
#include "DlgReportProperty.h"
#include "MyDate.h"

BOOL CReportDoc::GetDataForReport01(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	CString sTable="表0201测线";
	sSQL.Format ("select * from %s where 项目编号='%s'",(LPCTSTR)sTable,(LPCTSTR)m_sProjectNo);

	arrayFields.Add ("测线名称");			//0

	arrayFields.Add ("设计炮点起始桩号");	//1
	arrayFields.Add ("设计炮点终止桩号");
	arrayFields.Add ("设计满覆盖长度");
	arrayFields.Add ("设计二维激发点数");

	arrayFields.Add ("设计炮线开始线号");	//5
	arrayFields.Add ("设计炮线终止线号");
	arrayFields.Add ("设计炮线间隔");

	arrayFields.Add ("设计炮点开始点号");
	arrayFields.Add ("设计炮点终止点号");
	arrayFields.Add ("设计炮点间隔");		//10
	
	arrayFields.Add ("设计接收线开始线号");
	arrayFields.Add ("设计接收线终止线号");
	arrayFields.Add ("设计接收线间隔");

	arrayFields.Add ("设计接收点开始点号");
	arrayFields.Add ("设计接收点终止点号");	//15
	arrayFields.Add ("设计接收点间隔");
	arrayFields.Add ("设计接收线长度");

	arrayFields.Add ("设计三维激发点数");
	arrayFields.Add ("设计小折射点数");
	arrayFields.Add ("设计微测井点数");		//20

	arrayFields.Add ("驻队监督");		//21


	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};
	return TRUE;
}



// 中油勘探监理公司     年度      探区        勘探监理项目
//（表0103）设计质量指标、目的层指标（表0104）、主要干扰波指标统计表（表0105）

BOOL CReportDoc::GetDataForReport02(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	CString sTable="表0103项目设计质量统计表";
	sSQL.Format ("select * from %s where 项目编号='%s'",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo);
	arrayFields.Add ("全区一级品率指标");	//0
	arrayFields.Add ("全区一级品率要求");
	arrayFields.Add ("全区合格率指标");
	arrayFields.Add ("全区合格率要求");
	arrayFields.Add ("全区废品率指标");	//4

	arrayFields.Add ("全区废品率要求");
	arrayFields.Add ("全区空炮率指标");
	arrayFields.Add ("全区空炮率要求");
	arrayFields.Add ("单束线空炮率指标");
	arrayFields.Add ("单束线空炮率要求");		//9
	
	arrayFields.Add ("单束线废品率指标");
	arrayFields.Add ("单束线废品率要求");
	arrayFields.Add ("全区测量资料合格率指标");
	arrayFields.Add ("全区测量资料合格率要求");
	arrayFields.Add ("全区表层调查资料合格率指标");	//14

	arrayFields.Add ("全区表层调查资料合格率要求");
	arrayFields.Add ("全区现场处理率指标");
	arrayFields.Add ("全区现场处理率要求");


	CTableDate dateFrom;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateFrom,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	if(GetRecordQty ()==0)
	{
		TRACEERROR("没有符合条件的项目:"+sSQL);
		return false;
	}

	if(GetRecordQty ()>1)
	{
		TRACEERROR("符合条件的项目多于一个:"+sSQL);
		return false;
	}

	CStringArray *pRecord=GetRecord (0);
	if(!pRecord)
	{
		TRACEERROR("无法获得记录:"+sSQL);
		return false;
	}

	m_arrayProject1.Copy (*pRecord);

	///////////////////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////////////////
	sTable="表0104目的层指标统计表";
	sSQL.Format ("select * from %s where 项目编号='%s'",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo);
	arrayFields.RemoveAll ();

	arrayFields.Add ("目的层");			//0

	arrayFields.Add ("代码");	//1
	arrayFields.Add ("T0时间");
	arrayFields.Add ("主频起始");
	arrayFields.Add ("主频终止");
	arrayFields.Add ("分辨率起始");	//5

	arrayFields.Add ("分辨率终止");
	arrayFields.Add ("信噪比起始");
	arrayFields.Add ("信噪比终止");
	arrayFields.Add ("能量起始");
	arrayFields.Add ("能量终止");		//10
	
	arrayFields.Add ("要求");
	arrayFields.Add ("备注");

	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateFrom,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	////////////////////////////////////////
	//
	////////////////////////////////////////
	sTable="表0105干扰波指标";
	sSQL.Format ("select * from %s where 项目编号='%s'",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo);
	arrayFields.RemoveAll ();

	arrayFields.Add ("干扰波");			//0

	arrayFields.Add ("代码");	//1
	arrayFields.Add ("视频率起始");
	arrayFields.Add ("视频率终止");
	arrayFields.Add ("视速度起始");	//4

	arrayFields.Add ("视速度终止"); //5
	arrayFields.Add ("视波长起始");
	arrayFields.Add ("视波长终止");
	arrayFields.Add ("强度起始");
	arrayFields.Add ("强度终止");		//9
	
	arrayFields.Add ("要求");    // 10
	arrayFields.Add ("备注");

	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateFrom,&arrayFields,&m_docVice,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};
	return TRUE;
}


BOOL CReportDoc::GetDataForReport03(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	CString sEndDay=MakeDateCmpString(	"年",
						"月",
						"日",
						"<=",
						dlg.m_iEndYear ,
						dlg.m_iEndMonth ,
						dlg.m_iEndDay );

	CString sTable="表0301监理工作日报";
	sSQL.Format ("select * from %s where 项目编号='%s' and %s",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo,
					(LPCTSTR)sEndDay);

	arrayFields.Add ("测线编号");		//0

	arrayFields.Add ("年");			//1
	arrayFields.Add ("月");			//2
	arrayFields.Add ("日");			//3
	arrayFields.Add ("项目编号");	//4
	arrayFields.Add ("核实公里数");	//5
	arrayFields.Add ("核实小折射点数");	
	arrayFields.Add ("核实微测井点数");	
	arrayFields.Add ("复评一级");
	arrayFields.Add ("复评二级");
	arrayFields.Add ("复评空点");		//10
	arrayFields.Add ("复评废品");
	arrayFields.Add ("检查激发点数");		
	arrayFields.Add ("合格激发点数");
	arrayFields.Add ("检查接收点数");
	arrayFields.Add ("合格接收点数");	//15
	arrayFields.Add ("测线合格通知书份数");
	arrayFields.Add ("月检");			//
	arrayFields.Add ("日检");			//
	arrayFields.Add ("检查测量点数");	//
	arrayFields.Add ("合格测量点数");	//20
	arrayFields.Add ("现场检查");		//
	arrayFields.Add ("备忘录");			//
	arrayFields.Add ("附件编号");		//
	arrayFields.Add ("监理项目运行情况");	//
	arrayFields.Add ("监督工作情况");		//25
	arrayFields.Add ("下步监督工作重点");	//
	arrayFields.Add ("驻队监督");			//27


	arrayFields.Add ("单井激发1点数");		//28
	arrayFields.Add ("单井激发2点数");		//29
	arrayFields.Add ("单井激发3点数");		//30
	arrayFields.Add ("单井激发4点数");		//31
	arrayFields.Add ("单井激发5点数");		//32
	arrayFields.Add ("单井激发6点数");		//33
	arrayFields.Add ("单井激发7点数");		//34
	arrayFields.Add ("单井激发8点数");		//35
	arrayFields.Add ("单井激发9点数");		//36
	arrayFields.Add ("单井激发10点数");		//37


	arrayFields.Add ("组合激发1点数");		//38
	arrayFields.Add ("组合激发2点数");		//39
	arrayFields.Add ("组合激发3点数");		//40
	arrayFields.Add ("组合激发4点数");		//41
	arrayFields.Add ("组合激发5点数");		//42
	arrayFields.Add ("组合激发6点数");		//43
	arrayFields.Add ("组合激发7点数");		//44
	arrayFields.Add ("组合激发8点数");		//45
	arrayFields.Add ("组合激发9点数");		//46
	arrayFields.Add ("组合激发10点数");		//47


	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};
	return TRUE;
}

//勘探监理项目监理工作月报表
BOOL CReportDoc::GetDataForReport04(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	int i=0,j=0;


	CString sEndDay=MakeDateCmpString(	"年",
						"月",
						"日",
						"<=",
						dlg.m_iEndYear ,
						dlg.m_iEndMonth ,
						dlg.m_iEndDay );

	CString sTable="表0301监理工作日报";
	sSQL.Format ("select * from %s where 项目编号='%s' and %s",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo,
					(LPCTSTR)sEndDay);

	arrayFields.Add ("测线编号");		//0

	arrayFields.Add ("年");			//1
	arrayFields.Add ("月");			//2
	arrayFields.Add ("日");			//3
	arrayFields.Add ("项目编号");	//4
	arrayFields.Add ("核实公里数");	//5
	arrayFields.Add ("核实小折射点数");	
	arrayFields.Add ("核实微测井点数");	
	arrayFields.Add ("复评一级");
	arrayFields.Add ("复评二级");
	arrayFields.Add ("复评空点");		//10
	arrayFields.Add ("复评废品");
	arrayFields.Add ("检查激发点数");		
	arrayFields.Add ("合格激发点数");
	arrayFields.Add ("检查接收点数");
	arrayFields.Add ("合格接收点数");	//15
	arrayFields.Add ("测线合格通知书份数");
	arrayFields.Add ("月检");			//
	arrayFields.Add ("日检");			//
	arrayFields.Add ("检查测量点数");	//
	arrayFields.Add ("合格测量点数");	//20
	arrayFields.Add ("现场检查");		//
	arrayFields.Add ("备忘录");			//
	arrayFields.Add ("附件编号");		//
	arrayFields.Add ("监理项目运行情况");	//
	arrayFields.Add ("监督工作情况");		//25
	arrayFields.Add ("下步监督工作重点");	//
	arrayFields.Add ("监理项目概况");		//
	arrayFields.Add ("驻队监督");
	arrayFields.Add ("本日测线开工");
	arrayFields.Add ("本日测线完工");		// 30

	arrayFields.Add ("单井激发1点数");		//31
	arrayFields.Add ("单井激发2点数");		//32
	arrayFields.Add ("单井激发3点数");		//33
	arrayFields.Add ("单井激发4点数");		//34
	arrayFields.Add ("单井激发5点数");		//35
	arrayFields.Add ("单井激发6点数");		//36
	arrayFields.Add ("单井激发7点数");		//37
	arrayFields.Add ("单井激发8点数");		//38
	arrayFields.Add ("单井激发9点数");		//39
	arrayFields.Add ("单井激发10点数");		//40


	arrayFields.Add ("组合激发1点数");		//41
	arrayFields.Add ("组合激发2点数");		//42
	arrayFields.Add ("组合激发3点数");		//43
	arrayFields.Add ("组合激发4点数");		//44
	arrayFields.Add ("组合激发5点数");		//45
	arrayFields.Add ("组合激发6点数");		//46
	arrayFields.Add ("组合激发7点数");		//47
	arrayFields.Add ("组合激发8点数");		//48
	arrayFields.Add ("组合激发9点数");		//49
	arrayFields.Add ("组合激发10点数");		//50


	CDataBrowseDoc docBrowse;
	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,&docBrowse,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	///////////////////////////////////////
	// 计算共有多少条测线，并记录他们的名字：
	///////////////////////////////////////
	CStringArray arrayLineNames;
	CStringArray *pRecord=NULL;
	CString sLine;
	bool bExist=false;
	for(i=0;i<docBrowse.GetRecordQty ();i++)
	{
		pRecord=docBrowse.GetRecord (i);
		
		sLine=pRecord->GetAt (0);
		for(j=0;j<arrayLineNames.GetCount ();j++)
		{
			bExist=false;
			if(sLine==arrayLineNames.GetAt (j))
			{
				bExist=true;
				break;
			}
		}
		if(!bExist)
		{
			arrayLineNames.Add (sLine);
		}
	}

	CDailyReportRecord *pMRR=new CDailyReportRecord[arrayLineNames.GetCount ()+2];
	CDailyReportRecord reportTotal;
	CDailyReportRecord reportMonth;


	for(i=0;i<arrayLineNames.GetCount ();i++)
	{
		pMRR[i].sLineName=arrayLineNames.GetAt (i);
	}

	////////////////////////////////////////
	//  计算这些测线的相关数据：
	////////////////////////////////////////
	int iPos=0;
	CMyDate dateToday;

	for(i=0;i<docBrowse.GetRecordQty ();i++)
	{
		pRecord=docBrowse.GetRecord (i);
		
		sLine=pRecord->GetAt (0);
		iPos=-1;
		for(j=0;j<arrayLineNames.GetCount ();j++)
		{
			if(sLine==arrayLineNames.GetAt (j))
			{
				iPos=j;	
				break;
			}
		}
		if(iPos==-1)
		{
			ASSERT(false);
			return false;
		}

		dateToday.Set (pRecord->GetAt (1),pRecord->GetAt (2),pRecord->GetAt (3));
		
		// 日期：
		if(IsTrue(pRecord->GetAt (29)))
		{
			pMRR[iPos].iStartYear = dateToday.GetYear();
			pMRR[iPos].iStartMonth =  dateToday.GetMonth ();
			pMRR[iPos].iStartDay =  dateToday.GetDay ();
		}

		if(IsTrue(pRecord->GetAt (30)))
		{
			pMRR[iPos].iEndYear =  dateToday.GetYear();
			pMRR[iPos].iEndMonth =  dateToday.GetMonth();
			pMRR[iPos].iEndDay =  dateToday.GetDay();
		}

		// 累计：
		for(j=31;j<=50;j++)
		{
			reportTotal.iShotQty +=stof(pRecord->GetAt(j));
		}


		reportTotal.fKilometer +=stof(pRecord->GetAt(5));
		reportTotal.iRefraction +=stof(pRecord->GetAt(6));
		reportTotal.iMicroSurveyWell +=stof(pRecord->GetAt(7));
		reportTotal.iFirstClass +=stof(pRecord->GetAt(8));
		reportTotal.iSecondClass +=stof(pRecord->GetAt(9));
		reportTotal.iEmptyPoint +=stof(pRecord->GetAt(10));
		reportTotal.iBadPoint +=stof(pRecord->GetAt(11));
		reportTotal.iInspectedShot +=stof(pRecord->GetAt(12));

		reportTotal.iShotValid +=stof(pRecord->GetAt(13));
		reportTotal.iInspectedRcv +=stof(pRecord->GetAt(14));
		reportTotal.iRcvValid +=stof(pRecord->GetAt(15));
		reportTotal.iLineValid +=stof(pRecord->GetAt(16));
		reportTotal.iMonthlyCheck +=stof(pRecord->GetAt(17));
		reportTotal.iDailyCheck +=stof(pRecord->GetAt(18));
		reportTotal.iSurveyMark +=stof(pRecord->GetAt(19));
		reportTotal.iValidSurveyMark +=stof(pRecord->GetAt(20));
		reportTotal.iOnPostInspect +=stof(pRecord->GetAt(21));
		reportTotal.iMemo +=stof(pRecord->GetAt(22));

		// 本月累计：
		if(dateToday>=CMyDate (m_iStartYear,m_iStartMonth,m_iStartDay))
		{
			for(j=31;j<=50;j++)
			{
				pMRR[iPos].iShotQty +=stof(pRecord->GetAt(j));
			}


			pMRR[iPos].fKilometer +=stof(pRecord->GetAt(5));
			pMRR[iPos].iRefraction +=stof(pRecord->GetAt(6));
			pMRR[iPos].iMicroSurveyWell +=stof(pRecord->GetAt(7));
			pMRR[iPos].iFirstClass +=stof(pRecord->GetAt(8));
			pMRR[iPos].iSecondClass +=stof(pRecord->GetAt(9));
			pMRR[iPos].iEmptyPoint +=stof(pRecord->GetAt(10));
			pMRR[iPos].iBadPoint +=stof(pRecord->GetAt(11));
			pMRR[iPos].iInspectedShot +=stof(pRecord->GetAt(12));

			pMRR[iPos].iShotValid +=stof(pRecord->GetAt(13));
			pMRR[iPos].iInspectedRcv +=stof(pRecord->GetAt(14));
			pMRR[iPos].iRcvValid +=stof(pRecord->GetAt(15));
			pMRR[iPos].iLineValid +=stof(pRecord->GetAt(16));
			pMRR[iPos].iMonthlyCheck +=stof(pRecord->GetAt(17));
			pMRR[iPos].iDailyCheck +=stof(pRecord->GetAt(18));
			pMRR[iPos].iSurveyMark +=stof(pRecord->GetAt(19));
			pMRR[iPos].iValidSurveyMark +=stof(pRecord->GetAt(20));
			pMRR[iPos].iOnPostInspect +=stof(pRecord->GetAt(21));
			pMRR[iPos].iMemo +=stof(pRecord->GetAt(22));
			pMRR[iPos].sTags +=pRecord->GetAt(23);

			pMRR[iPos].sProjectRun +=pRecord->GetAt(24);
			pMRR[iPos].sProjectWork +=pRecord->GetAt(25);
			pMRR[iPos].sNextStep +=pRecord->GetAt(26);
			pMRR[iPos].sProjectSummary +=pRecord->GetAt(27);
			
			pMRR[iPos].sMonitor =pRecord->GetAt(28);

			for(j=31;j<=50;j++)
			{
				reportMonth.iShotQty +=stof(pRecord->GetAt(j));
			}

			reportMonth.fKilometer +=stof(pRecord->GetAt(5));
			reportMonth.iRefraction +=stof(pRecord->GetAt(6));
			reportMonth.iMicroSurveyWell +=stof(pRecord->GetAt(7));
			reportMonth.iFirstClass +=stof(pRecord->GetAt(8));
			reportMonth.iSecondClass +=stof(pRecord->GetAt(9));
			reportMonth.iEmptyPoint +=stof(pRecord->GetAt(10));
			reportMonth.iBadPoint +=stof(pRecord->GetAt(11));
			reportMonth.iInspectedShot +=stof(pRecord->GetAt(12));

			reportMonth.iShotValid +=stof(pRecord->GetAt(13));
			reportMonth.iInspectedRcv +=stof(pRecord->GetAt(14));
			reportMonth.iRcvValid +=stof(pRecord->GetAt(15));
			reportMonth.iLineValid +=stof(pRecord->GetAt(16));
			reportMonth.iMonthlyCheck +=stof(pRecord->GetAt(17));
			reportMonth.iDailyCheck +=stof(pRecord->GetAt(18));
			reportMonth.iSurveyMark +=stof(pRecord->GetAt(19));
			reportMonth.iValidSurveyMark +=stof(pRecord->GetAt(20));
			reportMonth.iOnPostInspect +=stof(pRecord->GetAt(21));
			reportMonth.iMemo +=stof(pRecord->GetAt(22));

			reportMonth.sProjectRun+=pRecord->GetAt(24);
			reportMonth.sProjectWork+=pRecord->GetAt(25);
			reportMonth.sNextStep+=pRecord->GetAt(26);
			reportMonth.sProjectSummary+=pRecord->GetAt(27);
			reportMonth.sProblem="";			//32
		}
	}

	////////////////////////////////////
	// 发现及整改的问题 在表表0402监督检查备忘录 中
	////////////////////////////////////
	sTable="表0402监督检查备忘录";
	arrayFields.RemoveAll ();
	arrayFields.Add ("检查线束编号");		//0
	arrayFields.Add ("检查年");		//1
	arrayFields.Add ("检查月");		//2
	arrayFields.Add ("检查日");		//3
	arrayFields.Add ("检查项目与位置");		//4
	arrayFields.Add ("检查情况描述");		//5

	CTableDate dateFrom;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateFrom,&arrayFields,&docBrowse,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	for(i=0;i<docBrowse.GetRecordQty ();i++)
	{
		pRecord=docBrowse.GetRecord (i);
		dateToday.Set (pRecord->GetAt (1),pRecord->GetAt (2),pRecord->GetAt (3));
		if(dateToday>= CMyDate(m_iStartYear,m_iStartMonth,m_iStartDay))
		{
			reportMonth.sProblem+=pRecord->GetAt (4);
			reportMonth.sProblem+=pRecord->GetAt (5);
		}
	}

	////////////////////////////////////
	// 把数据放到本文档中：
	////////////////////////////////////
	CStringArray arrayNames,arrayTypes;

	pMRR[0].GetItemNames(arrayNames, arrayTypes);


	CreateDBFile ();
	SetField(arrayNames, arrayTypes);

	CStringArray arrayRecord;
	for(i=0;i<arrayLineNames.GetCount ();i++)
	{
		pMRR[i].sLineName=GetLineName(pMRR[i].sLineName);
		pMRR[i].WriteIntoArray(arrayRecord);
		AppendRecord(&arrayRecord);
	}

	// 放入月累计数据:
	reportMonth.WriteIntoArray(arrayRecord);
	AppendRecord(&arrayRecord);

	// 放入总累计数据:
	reportTotal.WriteIntoArray(arrayRecord);
	AppendRecord(&arrayRecord);

	delete []pMRR;


	return TRUE;
}


////////////////////////////////////////////////////
//物 探 工 程 测 量 专 业 监 督 周 报 表
////////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport05(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	CString sEndDay=MakeDateCmpString(	"年",
						"月",
						"日",
						"<=",
						dlg.m_iEndYear ,
						dlg.m_iEndMonth ,
						dlg.m_iEndDay );

	CString sTable="表0302测量监督日报";
	sSQL.Format ("select * from %s where %s",
					(LPCTSTR)sTable,
					(LPCTSTR)sEndDay);


	arrayFields.Add ("检查线束编号");		//0

	arrayFields.Add ("年");			//1
	arrayFields.Add ("月");			//2
	arrayFields.Add ("日");			//3
	arrayFields.Add ("检查线束编号");	//4
	arrayFields.Add ("监督核实长度");	//5
	arrayFields.Add ("监督核实放样点数");	
	arrayFields.Add ("监督核实复测点数");	
	arrayFields.Add ("监督核实复测点数");    // 复测率的位置
	arrayFields.Add ("最大放样误差X");
	arrayFields.Add ("最大放样误差Y");		//10
	arrayFields.Add ("最大复测较差X");
	arrayFields.Add ("最大复测较差Y");	
	arrayFields.Add ("最大复测较差H");	
	arrayFields.Add ("复测精度X");
	arrayFields.Add ("复测精度Y");	//15
	arrayFields.Add ("复测精度H");	//16
	arrayFields.Add ("野外检查测量标志");
	arrayFields.Add ("野外检查特殊点位");			//
	arrayFields.Add ("野外检查复检点数");			//
	arrayFields.Add ("野外检查施工参数");	//20
	arrayFields.Add ("备忘录");	//21
	arrayFields.Add ("备注");		//
	arrayFields.Add ("测量工作运行情况");			//
	arrayFields.Add ("监督工作情况");		//
	arrayFields.Add ("存在问题及整改情况");	//25
	arrayFields.Add ("下周测量监督工作重点");		//26
	arrayFields.Add ("其它");	//
	arrayFields.Add ("测量监督");		// 28
	arrayFields.Add ("项目编号");		// 29


	CTableDate dateFrom;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateFrom,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};
	return TRUE;
}
