
#include "stdafx.h"
#include "QCDB.h"
#include "MemDC.h"

#include "ReportDoc.h"
#include "ReportView.h"
#include "DlgReportShowProperty.h"
#include "MyDate.h"
#include "fhcglobal.h"

////////////////////////////////////////////////////
// 物 探 工 程 仪 器 专 业 监 督 周 报 表
// 表0303仪器监督日报  表6
////////////////////////////////////////////////////
void CReportView::CreateReport06()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,k;
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

		for(j=4;j<=20;j++)
		{
			sItem[j]=pRecord->GetAt (j+1);
		}

		// 周统计：
		date.Set (pRecord->GetAt (1),pRecord->GetAt (2),pRecord->GetAt (3));
		if(date>=CMyDate(pDoc->m_iStartYear,
							pDoc->m_iStartMonth,
							pDoc->m_iStartDay))
		{
			iWeekRecordQty++;

			for(k=4;k<=20;k++)
			{
				fWeekSum[k]+=stof(sItem[k]);
			}
		}

		// 项目统计：
		for(k=4;k<=20;k++)
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

	m_rc.CombineGrid (0,0,4,5);
	m_rc.CombineGrid (0,0,6,7);
	m_rc.CombineGrid (0,0,8,9);
	m_rc.CombineGrid (0,0,10,11);
	m_rc.CombineGrid (0,1,12,12);
	m_rc.CombineGrid (0,1,13,13);
	m_rc.CombineGrid (0,0,14,15);
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
	s.Format ("物 探 工 程 仪 器 专 业 监 督 周 报 表");
	m_rc.SetTitle (s);

	m_rc.SetGridContent(0,0,"日期");
	m_rc.SetGridContent(0,1,"监理项目");
	m_rc.SetGridContent(0,2,"施工\r单位");
	m_rc.SetGridContent(0,3,"仪器\r型号");
	m_rc.SetGridContent(0,4,"年、月检量");
	m_rc.SetGridContent(1,4,"时间");
	m_rc.SetGridContent(1,5,"数量");

	m_rc.SetGridContent(0,6,"日检");
	m_rc.SetGridContent(1,6,"日期段");
	m_rc.SetGridContent(1,7,"数量");
	m_rc.SetGridContent(0,8,"采集站测试");
	m_rc.SetGridContent(1,8,"时间");
	m_rc.SetGridContent(1,9,"数量");


	m_rc.SetGridContent(0,10,"检波器测试");
	m_rc.SetGridContent(1,10,"月份");
	m_rc.SetGridContent(1,11,"数量");

	m_rc.SetGridContent(0,12,"系统\r极性");

	m_rc.SetGridContent(0,13,"TB\r延迟");
	m_rc.SetGridContent(0,14,"仪器班报");
	m_rc.SetGridContent(1,14,"时间段");
	m_rc.SetGridContent(1,15,"数量");
	m_rc.SetGridContent(0,16,"野  外  检  查");
	m_rc.SetGridContent(1,16,"仪器\r参数");
	m_rc.SetGridContent(1,17,"工作\r道");
	m_rc.SetGridContent(1,18,"环境\r噪音");
	m_rc.SetGridContent(1,19,"检波器\r完好率");
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

		pDoc->GetProjectInfoByNo(pRecord->GetAt (0),&arrayProject);

		m_rc.SetGridContent(2+i,0,date.GetDateString ());
		m_rc.SetGridContent(2+i,1,arrayProject.GetAt (1)); // 项目名称
		m_rc.SetGridContent(2+i,2,arrayProject.GetAt (9)+"队"); // crew number
		

		for(j=3;j<=20;j++)
		{
			sItem[j]=pRecord->GetAt (j+1);
		}

		sNote=pRecord->GetAt (22);
		sNote.Trim ().MakeUpper ();

		for(j=23;j<=26;j++)
		{
			s=pRecord->GetAt (j);
			s.Trim ().MakeUpper ();
			if(s!=""&&s!="NULL")
			{
				sJS+=s;
			}
		}

		for(k=3;k<=20;k++)
		{
			m_rc.SetGridContent(2+i,k,sItem[k]);
		}

		m_rc.SetGridContent(2+i,21,sNote);
	}

	for(k=4;k<=20;k++)
	{
		if(k==4||k==6||k==8||k==14)continue;
		m_rc.SetGridContent(2+iWeekRecordQty,k,vtos(fWeekSum[k]));
		m_rc.SetGridContent(3+iWeekRecordQty,k,vtos(fProjectSum[k]));
	}

	m_rc.SetGridContent(4+iWeekRecordQty,0,"本周情况简述(1、项目测量工作运行情况、2、监督工作、重点是对测量工作的日常检查情况；2、测量工作存在的问题及整改要求；3、下周测量监督工作重点等):\r"+sJS, CW_GRIDWIDTH);
	m_rc.SetGridFormat(4+iWeekRecordQty,0,DT_LEFT);
	
	return;
}

/////////////////////////////////////
// 物探工程开工验收监督检查表
// 表0106开工验收检查表  表7
/////////////////////////////////////
void CReportView::CreateReport07()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j;
	CStringArray *pRecord=NULL;

	int iPrintPage=pDoc->m_iPrintPage ;

	if(iPrintPage==1)
	{
		CreateReport07_1();
	}
	else if(iPrintPage==2)
	{
		CreateReport07_2();
	}
	else if(iPrintPage==3)
	{
		CreateReport07_3();
	}
	else
	{
		CreateReport07_1();
	}
}
void CReportView::CreateReport07_2()
{
	int i,j;
	CStringArray *pRecord=NULL;
	CReportDoc *pDoc=GetDocument();

	/////////////////////////////////////////////////
	// 建立表格：
	/////////////////////////////////////////////////
	m_rc.SetGridQty (20,5);
	m_rc.CombineGrid (0,0,3,4);
	m_rc.CombineGrid (1,1,3,4);

	m_rc.CombineGrid (3,10,0,0);
	m_rc.CombineGrid (11,19,0,0);

	
	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("物探工程开工验收监督检查表");
	m_rc.SetTitle (s);

	m_rc.SetGridContent(0,0,"施工工区");
	m_rc.SetGridContent(1,0,"监理项目");
	m_rc.SetGridContent(0,2,"施工单位");
	m_rc.SetGridContent(1,2,"检查时间");
	m_rc.SetGridContent(2,0,"检查项目");
	m_rc.SetGridContent(2,1,"检   查   内   容");
	m_rc.SetGridContent(2,2,"施工方自检情况");

	m_rc.SetGridContent(2,3,"监 督 检 查 结 果");
	m_rc.SetGridContent(2,4,"检查日期");
	m_rc.SetGridContent(3,0,"测\r量\r基\r础\r资\r料");
	m_rc.SetGridContent(11,0,"解\r释\r、\r地\r质\r资\r料");

	
	m_rc.SetGridContent(3,1,"测量技术设计");
	m_rc.SetGridContent(4 ,1,"测量仪器型号、数量及使用年限");
	m_rc.SetGridContent(5 ,1,"测量仪器检验合格证书");
	m_rc.SetGridContent(6 ,1,"测量应用软件运行状况");
	m_rc.SetGridContent(7 ,1,"勘探部署图和地形图");
	m_rc.SetGridContent(8 ,1,"工区踏勘报告");
	m_rc.SetGridContent(9 ,1,"设计坐标校核和展图核对");
	m_rc.SetGridContent(10,1,"GPS等方法加密控制点成果");
	m_rc.SetGridContent(11,1,"采集项目设计及甲方批复意见");
	m_rc.SetGridContent(12,1,"物探采集技术标准及规范");
	m_rc.SetGridContent(13,1,"采集方法试验方案");
	m_rc.SetGridContent(14,1,"工区以往典型剖面收集");
	m_rc.SetGridContent(15,1,"工区部署图");
	m_rc.SetGridContent(16,1,"目的层构造图");
	m_rc.SetGridContent(17,1,"工区地形图");
	m_rc.SetGridContent(18,1,"地层系统柱状图、地质图幅说明书");
	m_rc.SetGridContent(19,1,"技术人员对地质目标的认识");

	m_rc.SetGridContent(0,1,pDoc->m_sBasin +"盆地 "+pDoc->m_sArea +"工区");
	m_rc.SetGridContent(0,3,pDoc->m_sServer +pDoc->m_sCrew +"队");
	m_rc.SetGridContent(1,1,pDoc->m_sProjectName );

	CMyDate dateCheck;
	//
	int iRow=0;
	int iYear=0,iMonth=0,iDay=0;

	CStringArray arrayMonitor;
	for(i=0;i<pDoc->GetRecordQty ();i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;

		iRow=-1;
		for(j=30;j<=46;j++)
		{
			if(IsTrue(pRecord->GetAt(j)))
			{
				iRow=j-27;
				break;
			}
		}
		if(iRow==-1)
		{
			TRACEERROR("错误：该记录没有指定检查内容。检查日期:"+pRecord->GetAt(68)+"年"+pRecord->GetAt(69)+"月"+pRecord->GetAt(70)+"日");
			continue;
		}

		//
		m_rc.SetGridContent(iRow,2,pRecord->GetAt(66));
		m_rc.SetGridContent(iRow,3,pRecord->GetAt(67));
		m_rc.SetGridContent(iRow,4,pRecord->GetAt(68)+"年"+pRecord->GetAt(69)+"月"+pRecord->GetAt(70)+"日");

		iYear=stof(pRecord->GetAt(1));
		iMonth=stof(pRecord->GetAt(2));
		iDay=stof(pRecord->GetAt(3));

		if(iYear!=0&&iMonth!=0&&iDay!=0)
		{
			dateCheck.Set(iYear,iMonth,iDay);
		}
		AddMonitor(arrayMonitor,pRecord->GetAt(4));
	}

	m_rc.SetGridContent (1,3,dateCheck.GetDateString ());
	m_rc.SetLeftDownString ("物探监督:"+GetMonitorString(arrayMonitor));
	
	return;
}
void CReportView::CreateReport07_3()
{
	int i,j;
	CStringArray *pRecord=NULL;
	CReportDoc *pDoc=GetDocument();

	/////////////////////////////////////////////////
	// 建立表格：
	/////////////////////////////////////////////////
	m_rc.SetGridQty (22,5);
	m_rc.CombineGrid (0,0,3,4);
	m_rc.CombineGrid (1,1,3,4);

	m_rc.CombineGrid (3,6,0,0);
	m_rc.CombineGrid (7,21,0,0);


	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("物探工程开工验收监督检查表");
	m_rc.SetTitle (s);

	m_rc.SetGridContent(0,0,"施工工区");
	m_rc.SetGridContent(1,0,"监理项目");
	m_rc.SetGridContent(0,2,"施工单位");
	m_rc.SetGridContent(1,2,"检查时间");
	m_rc.SetGridContent(2,0,"检查项目");
	m_rc.SetGridContent(2,1,"检   查   内   容");
	m_rc.SetGridContent(2,2,"施工方自检情况");

	m_rc.SetGridContent(2,3,"监 督 检 查 结 果");
	m_rc.SetGridContent(2,4,"检查日期");
	m_rc.SetGridContent(3,0,"队\r伍\r资\r质");
	m_rc.SetGridContent(7,0,"Q\rH\rS\rE\r管\r理");

	m_rc.SetGridContent(3 ,1,"主要队领导及技术骨干到位情况");
	m_rc.SetGridContent(4 ,1,"钻机、可控震源等特种设备到位情况");
	m_rc.SetGridContent(5 ,1,"承诺车辆及其它设备到位情况");
	m_rc.SetGridContent(6 ,1,"现场处理机软、硬件配置");
	m_rc.SetGridContent(7 ,1,"质量教育、标准宣贯、学习设计和记录");
	m_rc.SetGridContent(8 ,1,"岗位技术培训、岗位练兵情况");
	m_rc.SetGridContent(9 ,1,"质量管理组织及管理措施");
	m_rc.SetGridContent(10,1,"质量活动计划和目标");
	m_rc.SetGridContent(11,1,"HSE管理组织及管理措施");
	m_rc.SetGridContent(12,1,"HSE培训和审核");
	m_rc.SetGridContent(13,1,"85#、85#物品存放、管理、使用措施");
	m_rc.SetGridContent(14,1,"工区重点隐患登记及对策");
	m_rc.SetGridContent(15,1,"特种岗位操作证");
	m_rc.SetGridContent(16,1,"炊事人员体检证明");
	m_rc.SetGridContent(17,1,"饮用水检测证明");
	m_rc.SetGridContent(18,1,"营地垃圾处理措施");
	m_rc.SetGridContent(19,1,"厕所设置");
	m_rc.SetGridContent(20,1,"紧急集合点设置及标志");
	m_rc.SetGridContent(21,1,"营地、宿舍消防、用电设施及安全标识");


	m_rc.SetGridContent(0,1,pDoc->m_sBasin +"盆地 "+pDoc->m_sArea +"工区");
	m_rc.SetGridContent(0,3,pDoc->m_sServer +pDoc->m_sCrew +"队");
	m_rc.SetGridContent(1,1,pDoc->m_sProjectName );

	CMyDate dateCheck;
	//
	int iRow=0;
	int iYear=0,iMonth=0,iDay=0;

	CStringArray arrayMonitor;
	for(i=0;i<pDoc->GetRecordQty ();i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;

		iRow=-1;
		for(j=47;j<=65;j++)
		{
			if(IsTrue(pRecord->GetAt(j)))
			{
				iRow=j-44;
				break;
			}
		}
		if(iRow==-1)
		{
			TRACEERROR("错误：该记录没有指定检查内容。检查日期:"+pRecord->GetAt(68)+"年"+pRecord->GetAt(69)+"月"+pRecord->GetAt(70)+"日");
			continue;
		}

		//
		m_rc.SetGridContent(iRow,2,pRecord->GetAt(66));
		m_rc.SetGridContent(iRow,3,pRecord->GetAt(67));
		m_rc.SetGridContent(iRow,4,pRecord->GetAt(68)+"年"+pRecord->GetAt(69)+"月"+pRecord->GetAt(70)+"日");

		iYear=stof(pRecord->GetAt(1));
		iMonth=stof(pRecord->GetAt(2));
		iDay=stof(pRecord->GetAt(3));

		if(iYear!=0&&iMonth!=0&&iDay!=0)
		{
			dateCheck.Set(iYear,iMonth,iDay);
		}
		AddMonitor(arrayMonitor,pRecord->GetAt(4));
	}

	m_rc.SetGridContent (1,3,dateCheck.GetDateString ());
	m_rc.SetLeftDownString ("物探监督:"+GetMonitorString(arrayMonitor));
	
	return;

}

//////////////////////////////////////////
// 物探工程开工验收监督检查表, 第一部分
// 表0106开工验收检查表  表7
//////////////////////////////////////////
void CReportView::CreateReport07_1()
{
	int i,j;
	CStringArray *pRecord=NULL;
	CReportDoc *pDoc=GetDocument();

	/////////////////////////////////////////////////
	// 建立表格：
	/////////////////////////////////////////////////
	m_rc.SetGridQty (28,5);
	m_rc.CombineGrid (0,0,3,4);
	m_rc.CombineGrid (1,1,3,4);

	m_rc.CombineGrid (3,27,0,0);
	/*m_rc.CombineGrid (28,35,0,0);

	m_rc.CombineGrid (36,44,0,0);
	m_rc.CombineGrid (45,48,0,0);
	m_rc.CombineGrid (49,63,0,0);
	*/

	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("物探工程开工验收监督检查表");
	m_rc.SetTitle (s);

	m_rc.SetGridContent(0,0,"施工工区");
	m_rc.SetGridContent(1,0,"监理项目");
	m_rc.SetGridContent(0,2,"施工单位");
	m_rc.SetGridContent(1,2,"检查时间");
	m_rc.SetGridContent(2,0,"检查项目");
	m_rc.SetGridContent(2,1,"检   查   内   容");
	m_rc.SetGridContent(2,2,"施工方自检情况");

	m_rc.SetGridContent(2,3,"监 督 检 查 结 果");
	m_rc.SetGridContent(2,4,"检查日期");
	m_rc.SetGridContent(3,0,"地\r震\r、\r表\r层\r调\r查\r仪\r器\r及\r外\r设\r基\r础\r资\r料");
	/*m_rc.SetGridContent(28,0,"测\r量\r基\r础\r资\r料");
	m_rc.SetGridContent(36,0,"解\r释\r、\r地\r质\r资\r料");
	m_rc.SetGridContent(45,0,"队\r伍\r资\r质");
	m_rc.SetGridContent(49,0,"Q\rH\rS\rE\r管\r理");*/


	m_rc.SetGridContent(3,1,"地震仪器型号、数量及使用年限");
	m_rc.SetGridContent(4,1,"采集仪器执行标准");
	m_rc.SetGridContent(5,1,"采集仪器年、月检及检验记录");
	m_rc.SetGridContent(6,1,"采集站型号、数量及使用年限");
	m_rc.SetGridContent(7,1,"电源站型号、数量及使用年限");
	m_rc.SetGridContent(8,1,"交叉站型号、数量及使用年限");
	m_rc.SetGridContent(9,1,"采集站年检及检验记录");
	m_rc.SetGridContent(10,1,"可控震源型号及数量");
	m_rc.SetGridContent(11,1,"可控震源年检及检验记录");
	m_rc.SetGridContent(12,1,"表层调查仪器型号及使用年限");
	m_rc.SetGridContent(13,1,"表层调查仪器年检及检验记录");
	m_rc.SetGridContent(14,1,"表层调查排列长度和道距校准记录");
	m_rc.SetGridContent(15,1,"爆炸机型号、数量及更改说明");
	m_rc.SetGridContent(16,1,"爆炸机TB延迟测试记录");
	m_rc.SetGridContent(17,1,"检波器型号、数量及使用年限");
	m_rc.SetGridContent(18,1,"大线型号、数量及使用年限");
	m_rc.SetGridContent(19,1,"交叉线型号、数量及使用年限");
	m_rc.SetGridContent(20,1,"外设检测标准");
	m_rc.SetGridContent(21,1,"系统极性测试资料、方法及数量");
	m_rc.SetGridContent(22,1,"系统延迟测试记录和班报");
	m_rc.SetGridContent(23,1,"检波器测试仪型号、数量及使用年限");
	m_rc.SetGridContent(24,1,"检波器测试仪年度鉴定证书");
	m_rc.SetGridContent(25,1,"检波器测试记录及检查情况");
	m_rc.SetGridContent(26,1,"表层调查检波器检查及测试情况");
	m_rc.SetGridContent(27,1,"井口检波器检查及测试情况");

	/*
	m_rc.SetGridContent(28,1,"测量技术设计");
	m_rc.SetGridContent(29,1,"测量仪器型号、数量及使用年限");
	m_rc.SetGridContent(30,1,"测量仪器检验合格证书");
	m_rc.SetGridContent(31,1,"测量应用软件运行状况");
	m_rc.SetGridContent(32,1,"勘探部署图和地形图");
	m_rc.SetGridContent(33,1,"工区踏勘报告");
	m_rc.SetGridContent(34,1,"设计坐标校核和展图核对");
	m_rc.SetGridContent(35,1,"GPS等方法加密控制点成果");
	m_rc.SetGridContent(36,1,"采集项目设计及甲方批复意见");
	m_rc.SetGridContent(37,1,"物探采集技术标准及规范");
	m_rc.SetGridContent(38,1,"采集方法试验方案");
	m_rc.SetGridContent(39,1,"工区以往典型剖面收集");
	m_rc.SetGridContent(40,1,"工区部署图");
	m_rc.SetGridContent(41,1,"目的层构造图");
	m_rc.SetGridContent(42,1,"工区地形图");
	m_rc.SetGridContent(43,1,"地层系统柱状图、地质图幅说明书");
	m_rc.SetGridContent(44,1,"技术人员对地质目标的认识");
	m_rc.SetGridContent(45,1,"主要队领导及技术骨干到位情况");
	m_rc.SetGridContent(46,1,"钻机、可控震源等特种设备到位情况");
	m_rc.SetGridContent(47,1,"承诺车辆及其它设备到位情况");
	m_rc.SetGridContent(48,1,"现场处理机软、硬件配置");
	m_rc.SetGridContent(49,1,"质量教育、标准宣贯、学习设计和记录");
	m_rc.SetGridContent(50,1,"岗位技术培训、岗位练兵情况");
	m_rc.SetGridContent(51,1,"质量管理组织及管理措施");
	m_rc.SetGridContent(52,1,"质量活动计划和目标");
	m_rc.SetGridContent(53,1,"HSE管理组织及管理措施");
	m_rc.SetGridContent(54,1,"HSE培训和审核");
	m_rc.SetGridContent(55,1,"85#、85#物品存放、管理、使用措施");
	m_rc.SetGridContent(56,1,"工区重点隐患登记及对策");
	m_rc.SetGridContent(57,1,"特种岗位操作证");
	m_rc.SetGridContent(58,1,"炊事人员体检证明");
	m_rc.SetGridContent(59,1,"饮用水检测证明");
	m_rc.SetGridContent(60,1,"营地垃圾处理措施");
	m_rc.SetGridContent(61,1,"厕所设置");
	m_rc.SetGridContent(62,1,"紧急集合点设置及标志");
	m_rc.SetGridContent(63,1,"营地、宿舍消防、用电设施及安全标识");

*/

	m_rc.SetGridContent(0,1,pDoc->m_sBasin +"盆地 "+pDoc->m_sArea +"工区");
	m_rc.SetGridContent(0,3,pDoc->m_sServer +pDoc->m_sCrew +"队");
	m_rc.SetGridContent(1,1,pDoc->m_sProjectName );

	CMyDate dateCheck;
	//
	int iRow=0;
	int iYear=0,iMonth=0,iDay=0;

	CStringArray arrayMonitor;
	for(i=0;i<pDoc->GetRecordQty ();i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;

		iRow=-1;
		for(j=5;j<=29;j++)
		{
			if(IsTrue(pRecord->GetAt(j)))
			{
				iRow=j-2;
				break;
			}
		}
		if(iRow==-1)
		{
			TRACEERROR("错误：该记录没有指定检查内容。检查日期:"+pRecord->GetAt(68)+"年"+pRecord->GetAt(69)+"月"+pRecord->GetAt(70)+"日");
			continue;
		}

		//
		m_rc.SetGridContent(iRow,2,pRecord->GetAt(66));
		m_rc.SetGridContent(iRow,3,pRecord->GetAt(67));
		m_rc.SetGridContent(iRow,4,pRecord->GetAt(68)+"年"+pRecord->GetAt(69)+"月"+pRecord->GetAt(70)+"日");

		iYear=stof(pRecord->GetAt(1));
		iMonth=stof(pRecord->GetAt(2));
		iDay=stof(pRecord->GetAt(3));

		if(iYear!=0&&iMonth!=0&&iDay!=0)
		{
			dateCheck.Set(iYear,iMonth,iDay);
		}
		AddMonitor(arrayMonitor,pRecord->GetAt(4));
	}

	m_rc.SetGridContent (1,3,dateCheck.GetDateString ());
	m_rc.SetLeftDownString ("物探监督:"+GetMonitorString(arrayMonitor));
	
	return;
}


////////////////////////////////////////////////
//  物探工程施工工序监督检查表
////////////////////////////////////////////////
void CReportView::CreateReport08()
{
//	 □□■

	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j;
	CStringArray *pRecord=pDoc->GetRecord (0);
	CString sItem="";

	/////////////////////////////////////////////////
	// 建立表格：
	/////////////////////////////////////////////////
	m_rc.SetGridQty (7,2);
	for(i=0;i<6;i++)
	{
		m_rc.CombineGrid (i,i,0,1);
	}

	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("物探工程施工工序监督检查表");
	m_rc.SetTitle (s);

	s="施工工区:"+pDoc->m_sArea ;

	if(pDoc->m_bIs3D)
	{
		s+="□2D_■3D";
	}
	else
	{
		s+="■2D_□3D";
	}

	s+="   施工单位:"+pDoc->m_sServer +pDoc->m_sCrew+"队";
	s+="   检查日期:";
	if(pRecord)
	{
		s+=pRecord->GetAt (1)+"年"+pRecord->GetAt (2)+"月"+pRecord->GetAt (3)+"日";
	}
	m_rc.SetGridContent (0,0,s);

	s="";
	if(pRecord)
	{
		if(IsTrue(pRecord->GetAt (4)))
		{
			s="■试验   □测量   □激发   □接收   □仪器   □表层调查   □现场处理   □原始资料";
		}
		else if(IsTrue(pRecord->GetAt (5)))
		{
			s="□试验   ■测量   □激发   □接收   □仪器   □表层调查   □现场处理   □原始资料";
		}
		else if(IsTrue(pRecord->GetAt (6)))
		{
			s="□试验   □测量   ■激发   □接收   □仪器   □表层调查   □现场处理   □原始资料";
		}
		else if(IsTrue(pRecord->GetAt (7)))
		{
			s="□试验   □测量   □激发   ■接收   □仪器   □表层调查   □现场处理   □原始资料";
		}
		else if(IsTrue(pRecord->GetAt (8)))
		{
			s="□试验   □测量   □激发   □接收   ■仪器   □表层调查   □现场处理   □原始资料";
		}
		else if(IsTrue(pRecord->GetAt (9)))
		{
			s="□试验   □测量   □激发   □接收   □仪器   ■表层调查   □现场处理   □原始资料";
		}
		else if(IsTrue(pRecord->GetAt (10)))
		{
			s="□试验   □测量   □激发   □接收   □仪器   □表层调查   ■现场处理   □原始资料";
		}
		else if(IsTrue(pRecord->GetAt (11)))
		{
			s="□试验   □测量   □激发   □接收   □仪器   □表层调查   □现场处理   ■原始资料";
		}
		else
		{
			s="□试验   □测量   □激发   □接收   □仪器   □表层调查   □现场处理   □原始资料";
		}

	}
	else
	{
		s="□试验   □测量   □激发   □接收   □仪器   □表层调查   □现场处理   □原始资料";
	}

	m_rc.SetGridContent(1,0,s);

	s="检查情况描述：（位置、数量、情况）\r";
	if(pRecord)
	{
		s+=pRecord->GetAt (12)+"\r";
		s+=pRecord->GetAt (13)+"\r";
		s+=pRecord->GetAt (14);
	}

	m_rc.SetGridContent(2,0,s);

	s="附件：";
	sItem="";
	{
		sItem=pRecord->GetAt (15);
		sItem.Trim ();
	}
	if(sItem!="")
	{
		s+="■图像资料(编号："+sItem+")";
	}
	else
	{
		s+="□图像资料(编号：  )";
	}

	sItem="";
	if(pRecord)
	{
		sItem=pRecord->GetAt (16);
		sItem.Trim ();
	}
	if(sItem!="")
	{
		s+="    ■基础资料(编号："+sItem+")";
	}
	else
	{
		s+="    □基础资料(编号：  )";
	}

	sItem="";
	if(pRecord)
	{
		sItem=pRecord->GetAt (17);
		sItem.Trim ();
	}
	if(sItem!="")
	{
		s+="    ■其它(编号："+sItem+")";
	}
	else
	{
		s+="    □其它(编号：    )";
	}

	m_rc.SetGridContent (3,0,s);

	s="检查结果及整改意见：\r";
	sItem="";
	if(pRecord)
	{
		sItem=pRecord->GetAt (18);
		sItem.Trim ();
	}
	s+=sItem+"\r";
	sItem=pRecord->GetAt (19);
	sItem.Trim ();
	s+=sItem+"\r";

	m_rc.SetGridContent (4,0,s);

	s="整改效果：\r";
	sItem="";
	if(pRecord)
	{
		sItem=pRecord->GetAt (20);
		sItem.Trim ();
	}
	s+=sItem+"\r";
	
	CMyDate d;
	if(pRecord)
	{
		d.Set (pRecord->GetAt (21),pRecord->GetAt (22),pRecord->GetAt (23));
	}
	s+="整改日期："+d.GetDateString ();
	m_rc.SetGridContent (5,0,s);

	
	s="陪同检查人:";
	sItem="";
	if(pRecord)
	{
		sItem=pRecord->GetAt (24);
		sItem.Trim ();
	}
	s+=sItem;
	m_rc.SetGridContent (6,0,s);

	s="驻队监督:";
	sItem="";
	if(pRecord)
	{
		sItem=pRecord->GetAt (25);
		sItem.Trim ();
	}
	s+=sItem;
	m_rc.SetGridContent (6,1,s);


	//////////////////////////////////
	// Left:
	for(i=0;i<7;i++)
	{
		m_rc.SetGridFormat (i,0,DT_LEFT);
	}
	m_rc.SetGridFormat (6,1,DT_LEFT);


	return ;
	

}
void CReportView::CreateReport09()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j;
	CMyDate date;
	CStringArray *pRecord=pDoc->GetRecord (0);
	if(!pRecord)return;


	CString sItem="";

	/////////////////////////////////////////////////
	// 建立表格：
	/////////////////////////////////////////////////
	m_rc.SetGridQty (8,7);
	m_rc.CombineGrid (0,0,0,1);
	m_rc.CombineGrid (1,1,0,1);
	m_rc.CombineGrid (2,2,0,6);


	for(i=3;i<=6;i++)
	{
		m_rc.CombineGrid (i,i,1,6);
	}
	m_rc.CombineGrid (7,7,0,1);
	m_rc.CombineGrid (7,7,2,3);
	m_rc.CombineGrid (7,7,5,6);


	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("物探工程监督检查备忘录");
	m_rc.SetTitle (s);

	m_rc.SetGridContent (0,0,"施工工区");
	m_rc.SetGridContent (0,2,pDoc->m_sArea);
	m_rc.SetGridContent (0,3,"施工单位");
	m_rc.SetGridContent (0,4,pDoc->m_sServer+ pDoc->m_sCrew+"队");
	m_rc.SetGridContent (0,5,"备忘录编号");
	m_rc.SetGridContent (0,6,pRecord->GetAt (4));

	m_rc.SetGridContent (1,0,"检查线束");
	m_rc.SetGridContent (1,2,pDoc->GetLineName (pRecord->GetAt ( 5)));
	m_rc.SetGridContent (1,3,"检查人");
	m_rc.SetGridContent (1,4,pRecord->GetAt( 6));
	m_rc.SetGridContent (1,5,"检查日期");

	date.Set(pRecord->GetAt (1),pRecord->GetAt (2),pRecord->GetAt (3));
	m_rc.SetGridContent (1,6,date.GetDateString ());
	
	s="关于:"+pRecord->GetAt (7);
	m_rc.SetGridContent (2,0,s);

	m_rc.SetGridContent (3,0,"检\r查\r项\r目\r与\r位\r置");
	m_rc.SetGridContent (3,1,pRecord->GetAt ( 8));

	m_rc.SetGridContent (4,0,"检\r查\r情\r况\r描\r述");
	m_rc.SetGridContent (4,1,pRecord->GetAt ( 9));

	m_rc.SetGridContent (5,0,"处\r理\r及\r整\r改\r意\r见");
	m_rc.SetGridContent (5,1,pRecord->GetAt ( 10));

	m_rc.SetGridContent (6,0,"整\r改\r效\r果");
	date.Set(pRecord->GetAt (15),pRecord->GetAt (16),pRecord->GetAt (17));
	s=pRecord->GetAt (11)+"\r                         验证日期："+date.GetDateString ();
	m_rc.SetGridContent (6,1,s);

	m_rc.SetGridContent (7,0,"施工单位\r领导签字");
	date.Set(pRecord->GetAt (19),pRecord->GetAt (20),pRecord->GetAt (21));
	m_rc.SetGridContent (7,2,"  \r  \r  "+date.GetDateString ());

	date.Set(pRecord->GetAt (23),pRecord->GetAt (24),pRecord->GetAt (25));
	m_rc.SetGridContent (7,4,"驻队监督\r签   字");
	m_rc.SetGridContent (7,5,"  \r  \r  "+date.GetDateString ());

	//////////////////////////////////
	// Left:
	for(i=3;i<=6;i++)
	{
		m_rc.SetGridFormat (i,1,DT_LEFT);
	}
	m_rc.SetGridFormat (2,0,DT_LEFT);

	return ;
}


/////////////////////////////////////////////
//   物探工程监督工作数据统计分析表
/////////////////////////////////////////////
void CReportView::CreateReport10()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j;
	CMyDate date;
	CStringArray *pRecord=NULL;
	int iRecordQty=pDoc->GetRecordQty ();

	/////////////////////////////////////////////////
	// 建立表格：
	/////////////////////////////////////////////////
	m_rc.SetGridQty (iRecordQty+2,21);


	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("物探工程监督工作数据统计分析表");
	m_rc.SetTitle (s);

	m_rc.SetGridContent (0,0,"日\r期");
	m_rc.SetGridContent (0,1,"检查\r激发\r点数");
	m_rc.SetGridContent (0,2,"合格\r激发\r点数");
	m_rc.SetGridContent (0,3,"激发\r合格\r率");
	m_rc.SetGridContent (0,4,"检查\r接收\r点数");
	m_rc.SetGridContent (0,5,"合格\r接收\r点数");
	m_rc.SetGridContent (0,6,"接收\r合格\r率");
	m_rc.SetGridContent (0,7,"检查\r记录\r张数");
	m_rc.SetGridContent (0,8,"一级\r品数");
	m_rc.SetGridContent (0,9,"一级\r品率");
	m_rc.SetGridContent (0,10,"二级\r品数");
	m_rc.SetGridContent (0,11,"二级\r品率");
	m_rc.SetGridContent (0,12,"废品\r数");
	m_rc.SetGridContent (0,13,"废品\r率");
	m_rc.SetGridContent (0,14,"检查\r小折\r射数");
	m_rc.SetGridContent (0,15,"合格\r小折\r射数");
	m_rc.SetGridContent (0,16,"检查\r微测\r井数");
	m_rc.SetGridContent (0,17,"合格\r微测\r井数");
	m_rc.SetGridContent (0,18,"检查\r测量\r点数");
	m_rc.SetGridContent (0,19,"合格\r测量\r点数");
	m_rc.SetGridContent (0,20,"备注");
	m_rc.SetGridContent (iRecordQty+1,0,"月");


	//////////////////////////////////
	// Left:
	CString sItem[21];

	int iMonthSum[21];
	for(i=0;i<21;i++)
	{
		iMonthSum[i]=0;
	}

	CString sMonitor="";
	float fValue=0.0;
	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;
		date.Set(pRecord->GetAt (1),pRecord->GetAt (2),pRecord->GetAt (3));

		sItem[0]=pRecord->GetAt (2)+"月"+pRecord->GetAt (3)+"日";
		sItem[1]=pRecord->GetAt (4);
		sItem[2]=pRecord->GetAt (5);
		
		sItem[3]=GetRatioString(sItem[2],sItem[1]);

		sItem[4]=pRecord->GetAt (6);
		sItem[5]=pRecord->GetAt (7);
		sItem[6]=GetRatioString(sItem[5],sItem[4]);
		sItem[7]=pRecord->GetAt (8);
		sItem[8]=pRecord->GetAt (9);
		sItem[9]=GetRatioString(sItem[8],sItem[7]);
		sItem[10]=pRecord->GetAt (10);
		sItem[11]=GetRatioString(sItem[10],sItem[7]);
		sItem[12]=pRecord->GetAt (11);
		sItem[13]=GetRatioString(sItem[12],sItem[7]);
		sItem[14]=pRecord->GetAt (12);
		sItem[15]=pRecord->GetAt (13);
		sItem[16]=pRecord->GetAt (14);
		sItem[17]=pRecord->GetAt (15);
		sItem[18]=pRecord->GetAt (16);
		sItem[19]=pRecord->GetAt (17);
		sItem[20]=pRecord->GetAt (18);

		for(j=0;j<21;j++)
		{
            m_rc.SetGridContent (i+1,j,sItem[j]);
			iMonthSum[j]+=stof(sItem[j]);
		}

		s=pRecord->GetAt (19);
		if(!IsEmpty(s))
		{
			sMonitor=s;
		}
	}

	for(j=1;j<=19;j++)
	{
        m_rc.SetGridContent (iRecordQty+1,j,vtos(iMonthSum[j]));
	}

	m_rc.SetGridContent (iRecordQty+1,3,GetRatioString(iMonthSum[2],iMonthSum[1]));
	m_rc.SetGridContent (iRecordQty+1,6,GetRatioString(iMonthSum[5],iMonthSum[4]));
	m_rc.SetGridContent (iRecordQty+1,9,GetRatioString(iMonthSum[8],iMonthSum[7]));
	m_rc.SetGridContent (iRecordQty+1,11,GetRatioString(iMonthSum[10],iMonthSum[7]));
	m_rc.SetGridContent (iRecordQty+1,13,GetRatioString(iMonthSum[12],iMonthSum[7]));


	s="物探现场监督："+sMonitor+ "      监理项目："+pDoc->m_sProjectName +"   时间："+date.GetDateString ();
	m_rc.SetLeftUpString (s);
	return ;
	


}

