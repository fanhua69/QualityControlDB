#include "stdafx.h"
#include "QCDB.h"
#include "MemDC.h"

#include "ReportDoc.h"
#include "ReportView.h"
#include "DlgReportShowProperty.h"
#include "MyDate.h"
#include "MyTime.h"
#include "fhcglobal.h"

///////////////////////////////////////////////
//       探区执行经理巡回检查记录
//  表0404执行经理巡回检查记录  表21
///////////////////////////////////////////////
void CReportView::CreateReport21()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,n;
	CMyDate date;
	CStringArray *pRecord=NULL;
	CString sLine;
	
	pRecord=pDoc->GetRecord (0);
	if(!pRecord)
	{
		return;
	}

	/////////////////////////////////////////////////
	// 建立表格：
	/////////////////////////////////////////////////
	int iRecordQty=pDoc->GetRecordQty ();
	m_rc.SetGridQty (47,8);
	m_rc.CombineGrid (0,0,0,1);
	m_rc.CombineGrid (1,1,0,1);
	m_rc.CombineGrid (0,0,3,7);
	m_rc.CombineGrid (1,1,3,7);

	m_rc.CombineGrid (2,3,0,0);
	m_rc.CombineGrid (2,3,1,2);
	m_rc.CombineGrid (2,2,4,7);


	m_rc.CombineGrid (4,24,0,0);
	m_rc.CombineGrid (25,30,0,0);
	m_rc.CombineGrid (31,42,0,0);

	for(i=4;i<=42;i++)
	{
		m_rc.CombineGrid (i,i,1,2);
	}

	m_rc.CombineGrid (43,43,0,7);
	m_rc.CombineGrid (44,44,0,7);
	m_rc.CombineGrid (45,45,0,7);

	m_rc.CombineGrid (46,46,0,1);
	m_rc.CombineGrid (46,46,2,7);

	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("探区执行经理巡回检查记录" );
	m_rc.SetTitle (s);	


	m_rc.SetGridContent (0,0,"探区:"+pDoc->m_sProspectArea);
	m_rc.SetGridContent (0,2,"项目:"+pDoc->m_sProjectName );
	m_rc.SetGridContent (0,4,"编号:"+pDoc->m_sReportNumber );

	m_rc.SetGridContent (1,0,"现场监督:"+pRecord->GetAt (1));

	m_rc.SetGridContent (1,2,"陪同人:"+pRecord->GetAt (3));
	m_rc.SetGridContent (1,4,"日期:"+pRecord->GetAt (4)+"年"
									+pRecord->GetAt (5)+"月"
									+pRecord->GetAt (6)+"日");

	m_rc.SetGridFormat (0,0,DT_LEFT);
	m_rc.SetGridFormat (0,2,DT_LEFT);
	m_rc.SetGridFormat (0,4,DT_LEFT);
	m_rc.SetGridFormat (1,0,DT_LEFT);
	m_rc.SetGridFormat (1,2,DT_LEFT);
	m_rc.SetGridFormat (1,4,DT_LEFT);


	m_rc.SetGridContent (2,0,"项\r目");
	m_rc.SetGridContent (2,1,"检     查    内     容");
	m_rc.SetGridContent (2,3,"评  价  意  见");
	m_rc.SetGridContent (3,3,"好");
	m_rc.SetGridContent (3,4,"较\r好");
	m_rc.SetGridContent (3,5,"一\r般");
	m_rc.SetGridContent (3,6,"较\r差");
	m_rc.SetGridContent (3,7,"差");


	m_rc.SetGridContent (4,0,"监\r督\r基\r础\r工\r作\r和\r资\r料");
	m_rc.SetGridContent (25,0,"监\r督\r纪\r律");
	m_rc.SetGridContent (31,0,"施\r工\r现\r场\r监\r督\r工\作");

	m_rc.SetGridContent (4,1,"监督计划是否按要求、按时编写");
	m_rc.SetGridContent (5,1,"监督工作流程是否按要求展示并执行");
	m_rc.SetGridContent (6,1,"监督工作日志是否按要求记录、是否详尽");
	m_rc.SetGridContent (7,1,"如采用工序检查表，是否按要求记录、是否详尽");
	m_rc.SetGridContent (8,1,"监督工作附件是否按要求收集、整理");
	m_rc.SetGridContent (9,1,"基础资料检查时是否留下工作痕迹");
	m_rc.SetGridContent (10,1,"监督数据统计是否准确、一致");
	m_rc.SetGridContent (11,1,"周报是否按要求、按时统计并上报");
	m_rc.SetGridContent (12,1,"月报是否按要求、按时统计并上报");
	m_rc.SetGridContent (13,1,"日志、周报、月报、备忘录等与监督工作统计表是否一一对应");
	m_rc.SetGridContent (14,1,"备忘录或整改通知书是否按要求使用");
	m_rc.SetGridContent (15,1,"监督工作数据统计分析表是否按要求填写，与工作日志是否能对应");
	m_rc.SetGridContent (16,1,"监理资料展示是否按要求执行");
	m_rc.SetGridContent (17,1,"监督检查工作是否量化、量化数据是否能达到投资方要求");
	m_rc.SetGridContent (18,1,"野外检查点的时空分布是否科学，是否能有效反映施工全貌");
	m_rc.SetGridContent (19,1,"检查测量时各项指标是否符合要求，特殊点是否按要求执行");
	m_rc.SetGridContent (20,1,"检查仪器及附属设备基础资料时是否彻底、统计是否齐全");
	m_rc.SetGridContent (21,1,"检查激发、接收工序时是否确定量化质量标准");
	m_rc.SetGridContent (22,1,"是否有经投资方认可的原始记录评价标准");
	m_rc.SetGridContent (23,1,"施工方法、因素等改变或重要问题时是否有投资方的批复意见");
	m_rc.SetGridContent (24,1,"是否与投资方、执行经理和项目经理部随时进行信息沟通");
	m_rc.SetGridContent (25,1,"是否存在吃、拿、卡、要、报问题");
	m_rc.SetGridContent (26,1,"是否存在与施工方一起欺瞒投资方问题");
	m_rc.SetGridContent (27,1,"是否存在无故离开探区的情况");
	m_rc.SetGridContent (28,1,"是否存在私带民工、私带家属、介绍包工头问题");
	m_rc.SetGridContent (29,1,"是否存在对承包方领导无理现象");
	m_rc.SetGridContent (30,1,"是否存在生活待遇搞特殊化的问题");
	m_rc.SetGridContent (31,1,"抽查经监督检查过的野外激发点，是否仍存在不合格问题");
	m_rc.SetGridContent (32,1,"抽查经监督检查过的野外接收点，是否仍存在不合格问题");
	m_rc.SetGridContent (33,1,"抽查测量标志、特殊点处理等，是否存在问题");
	m_rc.SetGridContent (34,1,"野外现场抽查50－100张原始记录，是否能到达设计要求");
	m_rc.SetGridContent (35,1,"抽查现场施工基础资料，是否填写准确、齐全");
	m_rc.SetGridContent (36,1,"抽查表层调查工作，是否按要求施工，资料是否经监督认可");
	m_rc.SetGridContent (37,1,"抽查野外特殊部位、特殊点是否按设计、合同、要求执行");
	m_rc.SetGridContent (38,1,"现场测量10道线的检波器串，阻值是否合格");
	m_rc.SetGridContent (39,1,"要求闷井地区抽查爆炸后闷井情况，是否按要求执行");
	m_rc.SetGridContent (40,1,"下井检波器施工时抽查检波器井质量，是否符合要求");
	m_rc.SetGridContent (41,1,"激发深度是否按设计因素施工，岩性是否准确");
	m_rc.SetGridContent (42,1,"与施工方人员交流，观察质量意识、标准等落实情况");

	for(i=4;i<=42;i++)
	{
		m_rc.SetGridFormat (i,1,DT_LEFT);
	}


	int iSum[5];
	for(i=0;i<5;i++)
	{
		iSum[i]=0;
	}
	for(i=7;i<=45;i++)
	{
		s=pRecord->GetAt (i);
		s.Trim ().MakeUpper();
		s=s.Left (1);

		if(s=="A"||s=="1")
		{
			m_rc.SetGridContent (i-3,3,"是");
			iSum[0]++;
		}
		else if(s=="B"||s=="2")
		{
			m_rc.SetGridContent (i-3,4,"是");
			iSum[1]++;
		}
		else if(s=="C"||s=="3")
		{
			m_rc.SetGridContent (i-3,5,"是");
			iSum[2]++;
		}
		else if(s=="D"||s=="4")
		{
			m_rc.SetGridContent (i-3,6,"是");
			iSum[3]++;
		}
		else
		{
			m_rc.SetGridContent (i-3,7,"是");
			iSum[4]++;
		}
	}

	s=pRecord->GetAt (46);

	CString ss;
	ss.Format ("本次检查情况简评：（好%d个，较好%d个，一般%d个，较差%d个，差%d个）",
		iSum[0],iSum[1],iSum[2],iSum[3],iSum[4]);
	ss+="\r"+s;
	m_rc.SetGridContent (43,0,ss);
	m_rc.SetGridFormat (43,0,DT_LEFT);


	s=pRecord->GetAt (47);
	s.Trim().MakeUpper ();
	if(s=="A"||s=="1")
	{
		s="该项目驻队监督是否能继续胜任监督工作：  ■能     □经重新培训后能    □不能";
	}
	else if(s=="B"||s=="2")
	{
		s="该项目驻队监督是否能继续胜任监督工作：  □能     ■经重新培训后能    □不能";
	}
	else
	{
		s="该项目驻队监督是否能继续胜任监督工作：  □能     □经重新培训后能    ■不能";
	}
	m_rc.SetGridContent (44,0,s);
	m_rc.SetGridFormat (44,0,DT_LEFT);


	s=pRecord->GetAt (48);
	m_rc.SetGridContent (45,0,"对该项目下步监督工作要求：\r"+s);
	m_rc.SetGridFormat (45,0,DT_LEFT);

	s=pRecord->GetAt (1);
	m_rc.SetGridContent (46,0,"现场监督签字：\r      "+s+"\r          年   月   日");
	m_rc.SetGridFormat (46,0,DT_LEFT);
	
	s=pRecord->GetAt (2);
	m_rc.SetGridContent (46,2,"探区执行经理：\r      "+s+"\r          年   月   日");
	m_rc.SetGridFormat (46,2,DT_LEFT);


	s.Format (" 编  号：");
	m_rc.SetLeftUpString (s);

	return ;

}

/////////////////////////////////////////////////////////
//       项目经理部对执行经理巡回检查记录
//   表0405项目经理部对执行经理巡回检查记录  表22
/////////////////////////////////////////////////////////
void CReportView::CreateReport22()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,n;
	CMyDate date;
	CStringArray *pRecord=NULL;
	CString sLine;
	
	pRecord=pDoc->GetRecord (0);
	if(!pRecord)
	{
		return;
	}

	/////////////////////////////////////////////////
	// 建立表格：
	/////////////////////////////////////////////////
	int iRecordQty=pDoc->GetRecordQty ();
	m_rc.SetGridQty (29,9);
	m_rc.CombineGrid (0,0,0,1);
	m_rc.CombineGrid (0,0,3,5);
	m_rc.CombineGrid (0,0,6,8);

	m_rc.CombineGrid (1,2,0,0);
	m_rc.CombineGrid (1,2,1,3);
	m_rc.CombineGrid (1,1,4,5);
	m_rc.CombineGrid (1,1,6,8);

	m_rc.CombineGrid (3,22,0,0);
	m_rc.CombineGrid (23,27,0,0);
	m_rc.CombineGrid (28,28,0,2);
	m_rc.CombineGrid (28,28,3,8);

	for(i=3;i<=27;i++)
	{
		m_rc.CombineGrid (i,i,1,3);
	}

	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("项目经理部对执行经理巡回检查记录" );
	m_rc.SetTitle (s);	


	m_rc.SetGridContent (0,0,"探区:"+pDoc->m_sProspectArea);
	m_rc.SetGridContent (0,2,"执行经理:"+pRecord->GetAt (3));
	m_rc.SetGridContent (0,3,"日期:"+pRecord->GetAt (4)+"年"
									+pRecord->GetAt (5)+"月"
									+pRecord->GetAt (6)+"日");

	m_rc.SetGridContent (0,6,"编号:"+pDoc->m_sReportNumber );

	m_rc.SetGridContent (1,0,"项\r目");
	m_rc.SetGridContent (1,1,"检     查    内     容");
	m_rc.SetGridContent (1,4,"检查结果");
	m_rc.SetGridContent (1,6,"评价意见");
	m_rc.SetGridContent (2,4,"是");
	m_rc.SetGridContent (2,5,"否");
	m_rc.SetGridContent (2,6,"好");
	m_rc.SetGridContent (2,7,"一般");
	m_rc.SetGridContent (2,8,"差");

	m_rc.SetGridContent (3,0,"监\r督\r管\r理\r工\r作\r和\r资\r料");
	m_rc.SetGridContent (23,0,"行\r为\r纪\r律");
	m_rc.SetGridContent (28,0,"探区执行经理签字：\r       "
						+pRecord->GetAt (3)
						+"\r        年    月    日");

	m_rc.SetGridContent (28,3,"项目经理部：\r       "
						+pRecord->GetAt (2)
						+"\r        年    月    日");

	
	s.Format ("编  号：");
	m_rc.SetLeftUpString (s);

	m_rc.SetGridFormat (0,0,DT_LEFT);
	m_rc.SetGridFormat (0,2,DT_LEFT);
	m_rc.SetGridFormat (0,3,DT_LEFT);
	m_rc.SetGridFormat (0,6,DT_LEFT);
	m_rc.SetGridFormat (28,0,DT_LEFT);
	m_rc.SetGridFormat (28,3,DT_LEFT);

	m_rc.SetGridContent (3,1,"是否按要求审查探区所有项目监督工作计划，格式是否统一");
	m_rc.SetGridContent (4,1,"探区内是否统一监督工作流程");
	m_rc.SetGridContent (5,1,"探区内是否统一监督周报、月报的格式及内容");
	m_rc.SetGridContent (6,1,"探区内是否统一监督记录格式");
	m_rc.SetGridContent (7,1,"探区内是否统一监督展示资料格式");
	m_rc.SetGridContent (8,1,"探区内是否规范了监督工作统计表格");
	m_rc.SetGridContent (9,1,"探区内是否统一规范了监督报告内容、格式及附表格式");
	m_rc.SetGridContent (10,1,"在有条件的项目，是否要求采用E-mail形式汇报");
	m_rc.SetGridContent (11,1,"与投资方有关领导是否交流、沟通了监督工作认识");
	m_rc.SetGridContent (12,1,"是否向投资方介绍了公司及的监督工作管理思路");
	m_rc.SetGridContent (13,1,"是否了解投资方对监督工作的要求和特点");
	m_rc.SetGridContent (14,1,"是否把投资方的特殊要求传达到各项目监督人员");
	m_rc.SetGridContent (15,1,"是否了解各项目及监督工作动态情况");
	m_rc.SetGridContent (16,1,"是否按要求巡回检查了各项目监督工作");
	m_rc.SetGridContent (17,1,"巡回检查资料是否齐全、规范");
	m_rc.SetGridContent (18,1,"是否按要求对技术支持工作进行了安排和实施");
	m_rc.SetGridContent (19,1,"技术支持是否达到了应有的效果");
	m_rc.SetGridContent (20,1,"工作记录是否齐全、准确");
	m_rc.SetGridContent (21,1,"是否及时与投资方有关领导进行信息沟通");
	m_rc.SetGridContent (22,1,"是否及时与项目经理部进行信息沟通");
	m_rc.SetGridContent (23,1,"大额资金使用是否经过请示");
	m_rc.SetGridContent (24,1,"是否注重成本控制问题");
	m_rc.SetGridContent (25,1,"工作态度是否认真、积极、不懈怠");
	m_rc.SetGridContent (26,1,"是否能创造性开展监督管理工作");
	m_rc.SetGridContent (27,1,"生活待遇方面是否不搞特殊化");

	for(i=3;i<=27;i++)
	{
		m_rc.SetGridFormat (i,1,DT_LEFT);
	}

	int iRow=0;
	for(i=7;i<=55;i+=2)
	{
		s=pRecord->GetAt (i);
		s.Trim ().MakeUpper();
		s=s.Left (1);


		iRow=(i-7)/2+3;
		if(IsTrue(s))
		{
			m_rc.SetGridContent (iRow,4,"是");
		}
		else
		{
			m_rc.SetGridContent (iRow,5,"否");
		}

		s=pRecord->GetAt (i+1);
		s.Trim ().MakeUpper();
		s=s.Left (1);

		if (s=="A"||s=="1")
		{
			m_rc.SetGridContent (iRow,6,"好");
		}
		else if(s=="B"||s=="2")
		{
			m_rc.SetGridContent (iRow,7,"一般");
		}
		else
		{
			m_rc.SetGridContent (iRow,8,"差");
		}
	}

	return ;
}

/////////////////////////////////////////////////////////////
//    项目经理部对现场监督巡回检查记录
//   表0406项目经理部对现场监督巡回检查记录  表23
/////////////////////////////////////////////////////////////
void CReportView::CreateReport23()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,n;
	CMyDate date;
	CStringArray *pRecord=NULL;
	CString sLine;
	
	pRecord=pDoc->GetRecord (0);
	if(!pRecord)
	{
		return;
	}

	/////////////////////////////////////////////////
	// 建立表格：
	/////////////////////////////////////////////////
	int iRecordQty=pDoc->GetRecordQty ();
	m_rc.SetGridQty (32,9);
	m_rc.CombineGrid (0,0,0,1);
	m_rc.CombineGrid (0,0,2,3);
	m_rc.CombineGrid (0,0,4,8);

	m_rc.CombineGrid (1,1,0,1);
	m_rc.CombineGrid (1,1,2,3);
	m_rc.CombineGrid (1,1,4,8);
	
	m_rc.CombineGrid (2,3,0,0);
	m_rc.CombineGrid (2,3,1,3);
	m_rc.CombineGrid (2,2,4,5);
	m_rc.CombineGrid (2,2,6,8);
	
	
	m_rc.CombineGrid (4,24,0,0);
	m_rc.CombineGrid (25,30,0,0);
	m_rc.CombineGrid (31,31,0,2);
	m_rc.CombineGrid (31,31,3,8);

	for(i=4;i<=30;i++)
	{
		m_rc.CombineGrid (i,i,1,3);
	}

	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("项目经理部对现场监督巡回检查记录" );
	m_rc.SetTitle (s);	


	m_rc.SetGridContent (0,0,"探区:"+pDoc->m_sProspectArea);
	m_rc.SetGridContent (0,2,"项目:"+pDoc->m_sProjectName );
	m_rc.SetGridContent (0,4,"编号:"+pDoc->m_sReportNumber );

	m_rc.SetGridContent (1,0,"现场监督:"+pRecord->GetAt (2));

	m_rc.SetGridContent (1,2,"陪同人:"+pRecord->GetAt (3));
	m_rc.SetGridContent (1,4,"日期:"+pRecord->GetAt (4)+"年"+pRecord->GetAt (5)+"月"+pRecord->GetAt (6)+"日");


	m_rc.SetGridContent (2,0,"项\r目",CW_FIXEDBYCONTENT);
	m_rc.SetGridContent (2,1,"检     查    内     容");
	m_rc.SetGridContent (2,4,"检查结果");
	m_rc.SetGridContent (2,6,"评价意见");

	m_rc.SetGridContent (3,4,"是");
	m_rc.SetGridContent (3,5,"否");
	m_rc.SetGridContent (3,6,"好");
	m_rc.SetGridContent (3,7,"一般");
	m_rc.SetGridContent (3,8,"差");

	m_rc.SetGridContent (4,0,"监\r督\r工\r作\r、\r资\r料\r、\r纪\r律",CW_FIXEDBYCONTENT);

	m_rc.SetGridContent (25,0,"施\r工\r现\r场",CW_FIXEDBYCONTENT);
	m_rc.SetGridContent (31,0,"现场监督签字：\r        "
						+pRecord->GetAt (2)
						+CString("\r        年    月    日"));

	m_rc.SetGridContent (31,3,"项目经理部：\r       "
						+pRecord->GetAt (1)
						+"\r        年    月    日");

	
	s.Format ("编  号：");
	m_rc.SetLeftUpString (s);

	m_rc.SetGridFormat (0,0,DT_LEFT);
	m_rc.SetGridFormat (0,2,DT_LEFT);
	m_rc.SetGridFormat (0,4,DT_LEFT);
	m_rc.SetGridFormat (1,0,DT_LEFT);
	m_rc.SetGridFormat (1,2,DT_LEFT);
	m_rc.SetGridFormat (1,4,DT_LEFT);
	m_rc.SetGridFormat (31,0,DT_LEFT);
	m_rc.SetGridFormat (31,3,DT_LEFT);

	m_rc.SetGridContent (4,1,"监督计划是否经执行经理审批，是否按探区统一格式");
	m_rc.SetGridContent (5,1,"是否按探区统一的监督工作流程展示并执行");
	m_rc.SetGridContent (6,1,"是否按要求记录监督工作日志");
	m_rc.SetGridContent (7,1,"如采用工序检查表，是否按统一格式和要求填写");
	m_rc.SetGridContent (8,1,"是否按要求收集、整理监督工作附件");
	m_rc.SetGridContent (9,1,"周报是否按要求、按时统计并上报");
	m_rc.SetGridContent (10,1,"月报是否按要求、按时统计并上报");
	m_rc.SetGridContent (11,1,"日志、周报、月报、备忘录、统计表等是否能相互对应");
	m_rc.SetGridContent (12,1,"备忘录或整改通知书是否按要求使用");
	m_rc.SetGridContent (13,1,"是否认真填写监督工作数据统计分析表");
	m_rc.SetGridContent (14,1,"监理资料展示是否符合探区统一规范");
	m_rc.SetGridContent (15,1,"施工方法、因素等改变或重要问题时是否有投资方的批复意见");
	m_rc.SetGridContent (16,1,"是否有经投资方认可的激发、接收工序量化质量标准");
	m_rc.SetGridContent (17,1,"是否有经投资方认可的原始记录评价标准");
	m_rc.SetGridContent (18,1,"是否与投资方、执行经理和项目经理部随时进行信息沟通");
	m_rc.SetGridContent (19,1,"工作小结或汇报，是否抓住重点，理念是否清晰");
	m_rc.SetGridContent (20,1,"对甲方总监或执行经理检查提出的要求是否记载、整理和落实");
	m_rc.SetGridContent (21,1,"向施工方了解，是否做到监督工作纪律无违反");
	m_rc.SetGridContent (22,1,"向投资方了解，是否做到对承包方领导不得无理");
	m_rc.SetGridContent (23,1,"向施工方了解，是否做到生活待遇不搞特殊化");
	m_rc.SetGridContent (24,1,"抽查经监督检查过的野外激发点，验证结果是否相符");
	m_rc.SetGridContent (25,1,"抽查经监督检查过的野外接收点，验证结果是否相符");
	m_rc.SetGridContent (26,1,"抽查测量标志、特殊点处理等，验证结果是否相符");
	m_rc.SetGridContent (27,1,"现场抽查部分原始记录，是否能达到设计要求");
	m_rc.SetGridContent (28,1,"抽查野外特殊部位、特殊点是否按设计、合同、要求执行");
	m_rc.SetGridContent (29,1,"现场抽查检波器串阻值，是否合格");
	m_rc.SetGridContent (30,1,"是否经常与施工方人员交流质量意识、标准等落实情况");


	for(i=4;i<=30;i++)
	{
		m_rc.SetGridFormat (i,1,DT_LEFT);
	}

	int iRow=0;
	for(i=7;i<=60;i+=2)
	{
		s=pRecord->GetAt (i);
		s.Trim ().MakeUpper();
		s=s.Left (1);

		iRow=(i-7)/2+4;
		if(IsTrue(s))
		{
			m_rc.SetGridContent (iRow,4,"是");
		}
		else
		{
			m_rc.SetGridContent (iRow,5,"否");
		}

		s=pRecord->GetAt (i+1);
		s.Trim ().MakeUpper();
		s=s.Left (1);

		if (s=="A"||s=="1")
		{
			m_rc.SetGridContent (iRow,6,"好");
		}
		else if(s=="B"||s=="2")
		{
			m_rc.SetGridContent (iRow,7,"一般");
		}
		else
		{
			m_rc.SetGridContent (iRow,8,"差");
		}
	}

	return ;

}

/////////////////////////////////////////////////////
// 勘探监理项目运行（日）时效统计表
// 表0301监理工作日报  表24
/////////////////////////////////////////////////////
void CReportView::CreateReport24()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,n;
	CMyDate date;
	CStringArray *pRecord=NULL;
	CString sLine;

	/////////////////////////////////////////////////
	// 建立表格：
	/////////////////////////////////////////////////
	int iRecordQty=pDoc->GetRecordQty ();
	m_rc.SetGridQty (iRecordQty+2,18);

	for(i=0;i<=6;i++)
	{
		m_rc.CombineGrid (0,1,i,i);
	}
	for(i=14;i<=17;i++)
	{
		m_rc.CombineGrid (0,1,i,i);
	}
	m_rc.CombineGrid (0,0,7,13);

	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("%s勘探监理项目运行（日）时效统计表",pDoc->m_sProjectName  );
	m_rc.SetTitle (s);	

    s="探区："+pDoc->m_sProspectArea +"         投资方："
		      +pDoc->m_sClient +"          作业方："
			  +pDoc->m_sServer +pDoc->m_sCrew +"队";
    m_rc.SetLeftUpString (s);

    s="    页 共   页";
    m_rc.SetRightUpString (s);


	m_rc.SetGridContent (0,0,"日期");
	m_rc.SetGridContent (0,1,"离开\r驻地\r时间");
	m_rc.SetGridContent (0,2,"到达\r工地\r时间");
	m_rc.SetGridContent (0,3,"铺首\r排列\r时间");

	m_rc.SetGridContent (0,4,"首炮\r    \r时间");
	m_rc.SetGridContent (0,5,"末炮\r    \r时间");
	m_rc.SetGridContent (0,6,"首末\r炮时\r间差");
	m_rc.SetGridContent (0,7,"影 响 施 工 时 间 统 计");
	m_rc.SetGridContent (1,7,"检查\r排列\r时间");
	m_rc.SetGridContent (1,8,"测量\r因素\r影响");
	m_rc.SetGridContent (1,9,"设备\r因素\r影响");
	m_rc.SetGridContent (1,10,"环境\r噪音\r影响");
	m_rc.SetGridContent (1,11,"自然\r条件\r影响");
	m_rc.SetGridContent (1,12,"地方\r关系\r影响");
	m_rc.SetGridContent (1,13,"其它\r因素\r影响");
	m_rc.SetGridContent (0,14,"实际\r放炮\r时间");
	m_rc.SetGridContent (0,15,"施工\r炮数");
	m_rc.SetGridContent (0,16,"天气\r情况");
	m_rc.SetGridContent (0,17,"备注");
	
    int iShotSum=0,iShot=0;
    CMyTime time, time1,time2;
	CStringArray arrayMonitor;
	
	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
        date.Set(pRecord->GetAt (4),pRecord->GetAt (5),pRecord->GetAt (6));
	    m_rc.SetGridContent (i+2,0,date.GetDateString ());

        time.SetTimeString (pRecord->GetAt (7));
	    m_rc.SetGridContent (i+2,1,time.GetTimeString ());

        time.SetTimeString (pRecord->GetAt (8));
	    m_rc.SetGridContent (i+2,2,time.GetTimeString ());

        time.SetTimeString (pRecord->GetAt (9));
	    m_rc.SetGridContent (i+2,3,time.GetTimeString ());

        time1.SetTimeString (pRecord->GetAt (10));
	    m_rc.SetGridContent (i+2,4,time1.GetTimeString ());

        time2.SetTimeString (pRecord->GetAt (11));
	    m_rc.SetGridContent (i+2,5,time2.GetTimeString ());

		time=time2-time1;
	    m_rc.SetGridContent (i+2,6,time.GetTimeString ());


		for(j=7;j<=14;j++)
		{
			time.SetTimeString (pRecord->GetAt (5+j));
			m_rc.SetGridContent (i+2,j,time.GetTimeString ());
		}

		// 炮数目
		iShotSum=0;
		for(j=22;j<=42;j++)
		{
			iShot=stof(pRecord->GetAt (j));
			iShotSum+=iShot;
		}
		m_rc.SetGridContent (i+2,15,vtos(iShotSum));

		//天气情况
		m_rc.SetGridContent (i+2,16,pRecord->GetAt (20));

		//备注
		m_rc.SetGridContent (i+2,17,pRecord->GetAt (21));

		// 驻队监督
		AddMonitor(arrayMonitor,pRecord->GetAt (43));
	}

	m_rc.SetLeftDownString ("驻队监督:"+GetMonitorString(arrayMonitor));
	return ;
}

///////////////////////////////////////////////////////////
//勘探监理项目      年度（月）时效分析表
//表0301监理工作日报  表25
///////////////////////////////////////////////////////////
void CReportView::CreateReport25()
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

		pMonthStat[i].dateStartWork= month;
		pMonthStat[i].dateStartWork.SetDay (31);
		pMonthStat[i].dateEndWork= month;
		pMonthStat[i].dateEndWork.DecreaseMonth ();
		pMonthStat[i].dateEndWork.SetDay (1);

		pMonthStat[i].iNaturalDay = pMonthStat[i].dateEnd .DayFrom (pMonthStat[i].dateStart)+1;
		pMonthStat[i].iMinShot = 99999;
		pMonthStat[i].iMaxShot = 0;
	}

	/////////////////////////////////////////////////
	// 建立表格：
	/////////////////////////////////////////////////
	int iRecordQty=pDoc->GetRecordQty ();
	m_rc.SetGridQty (iMonthQty+2,18);
	m_rc.CombineGrid (iMonthQty+1,iMonthQty+1,0,2);

	///////////////////////////////////////////////////////////
	// 填入数据
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("%s勘探监理项目%d年度（月）时效分析表",pDoc->m_sProjectName, dateEnd.GetYear () );
	m_rc.SetTitle (s);	

    s="探区："+pDoc->m_sProspectArea +"         投资方："
		      +pDoc->m_sClient +"          作业方："
			  +pDoc->m_sServer +pDoc->m_sCrew +"队";
    m_rc.SetLeftUpString (s);

	m_rc.SetGridContent (0,0,"统计\r日期");
	m_rc.SetGridContent (0,1,"开工\r日期");
	m_rc.SetGridContent (0,2,"收工\r日期");
	m_rc.SetGridContent (0,3,"项目\r设计\r炮数");

	m_rc.SetGridContent (0,4,"本月\r完成\r炮数");
	m_rc.SetGridContent (0,5,"完成\r率％");
	m_rc.SetGridContent (0,6,"本月\r自然\r天数");
	m_rc.SetGridContent (0,7,"本月\r施工\r天数");
	m_rc.SetGridContent (0,8,"本月\r检修\r天数");
	m_rc.SetGridContent (0,9,"本月\r自然\r停工");
	m_rc.SetGridContent (0,10,"本月\r其它\r停工");
	m_rc.SetGridContent (0,11,"本月\r钻井\r进尺");
	m_rc.SetGridContent (0,12,"月小\r折射\r点数");
	m_rc.SetGridContent (0,13,"月微\r测井\r点数");
	m_rc.SetGridContent (0,14,"本月\r最高\r炮数");
	m_rc.SetGridContent (0,15,"本月\r最低\r炮数");
	m_rc.SetGridContent (0,16,"本月\r平均\r日效");
	m_rc.SetGridContent (0,17,"备注");
	m_rc.SetGridContent (iMonthQty+1,0,"项  目  累  计");
	
    int iShotSum=0,iShot=0;
	CStringArray arrayMonitor;
	
	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
        date.Set(pRecord->GetAt (4),pRecord->GetAt (5),pRecord->GetAt (6));

		// 炮数目
		iShotSum=0;
		for(j=9;j<=18;j++)
		{
			iShot=stof(pRecord->GetAt (j));
			iShotSum+=iShot;
		}
		for(j=29;j<=38;j++)
		{
			iShot=stof(pRecord->GetAt (j));
			iShotSum+=iShot;
		}

		for(j=0;j<iMonthQty;j++)
		{
			if(date<pMonthStat[j].dateStart||date>pMonthStat[j].dateEnd)continue;

			if(iShotSum!=0)
			{
				if(date<pMonthStat[j].dateStartWork)
				{
					pMonthStat[j].dateStartWork=date;
				}
				if(date>pMonthStat[j].dateEndWork)
				{
					pMonthStat[j].dateEndWork=date;
				}
			}

			pMonthStat[j].iFinishedShot += iShotSum;

			if(IsTrue(pRecord->GetAt (21)))
			{
				pMonthStat[j].iWorkDay++;
			}

			if(IsTrue(pRecord->GetAt (22)))
			{
				pMonthStat[j].iCheckDay ++;
			}

			if(IsTrue(pRecord->GetAt (23)))
			{
				pMonthStat[j].iNaturalStandByDay ++;
			}

			if(IsTrue(pRecord->GetAt (24)))
			{
				pMonthStat[j].iOtherStandByDay ++;
			}

			pMonthStat[j].fDrillDepth		+=stof(pRecord->GetAt (25));
			pMonthStat[j].iRefQty			+=stof(pRecord->GetAt (26));
			pMonthStat[j].iMicroWellLogQty	+=stof(pRecord->GetAt (27));

			if(iShotSum!=0&&iShotSum>pMonthStat[j].iMaxShot )
			{
				pMonthStat[j].iMaxShot=iShotSum;
			}

			if(iShotSum!=0&&iShotSum<pMonthStat[j].iMinShot )
			{
				pMonthStat[j].iMinShot=iShotSum;
			}

			//备注
			s=pRecord->GetAt (28);
			if(s!="NULL")
			{
				pMonthStat[j].sNote += s;
			}
		}

		// 驻队监督
		AddMonitor(arrayMonitor,pRecord->GetAt (2));
	}

	int iProjectShotQty=stof(pDoc->m_s2DDesiShotQty );
	if(pDoc->m_bIs3D )
	{
		iProjectShotQty=stof(pDoc->m_s3DDesiShotQty );	
	}

	// 写入每月数量：
	for(i=0;i<iMonthQty;i++)
	{
		s.Format("%d年%d月",pMonthStat[i].dateMonth .GetYear (),pMonthStat[i].dateMonth .GetMonth());
		m_rc.SetGridContent (i+1,0,s);

		if(pMonthStat[i].dateEndWork <pMonthStat[i].dateStartWork )continue;
		m_rc.SetGridContent (i+1,1,pMonthStat[i].dateStartWork.GetMonthDayString());
		m_rc.SetGridContent (i+1,2,pMonthStat[i].dateEndWork.GetMonthDayString());
		m_rc.SetGridContent (i+1,3,vtos(iProjectShotQty));

		m_rc.SetGridContent (i+1,4,vtos(pMonthStat[i].iFinishedShot ));
		m_rc.SetGridContent (i+1,5,vtos(pMonthStat[i].iFinishedShot*1.0/iProjectShotQty*100,2));
		m_rc.SetGridContent (i+1,6,vtos(pMonthStat[i].iNaturalDay));
		m_rc.SetGridContent (i+1,7,vtos(pMonthStat[i].iWorkDay ));
		m_rc.SetGridContent (i+1,8,vtos(pMonthStat[i].iCheckDay ));
		m_rc.SetGridContent (i+1,9,vtos(pMonthStat[i].iNaturalStandByDay ));
		m_rc.SetGridContent (i+1,10,vtos(pMonthStat[i].iOtherStandByDay ));
		m_rc.SetGridContent (i+1,11,vtos(pMonthStat[i].fDrillDepth ,1));
		m_rc.SetGridContent (i+1,12,vtos(pMonthStat[i].iRefQty ));
		m_rc.SetGridContent (i+1,13,vtos(pMonthStat[i].iMicroWellLogQty ));
		m_rc.SetGridContent (i+1,14,vtos(pMonthStat[i].iMaxShot ));
		m_rc.SetGridContent (i+1,15,vtos(pMonthStat[i].iMinShot ));
		m_rc.SetGridContent (i+1,16,vtos(pMonthStat[i].iFinishedShot *1.0/pMonthStat[i].iNaturalDay,2));
		m_rc.SetGridContent (i+1,17,pMonthStat[i].sNote);
	}

	// 项目合计：
	CMonthStat projectSum;
	projectSum.iMaxShot =-1000;
	projectSum.iMinShot =999999;
	for(i=0;i<iMonthQty;i++)
	{
		if(pMonthStat[i].dateEndWork <pMonthStat[i].dateStartWork )continue;
		projectSum.iFinishedShot +=pMonthStat[i].iFinishedShot ;
		projectSum.iNaturalDay +=pMonthStat[i].iNaturalDay ;
		projectSum.iWorkDay +=pMonthStat[i].iWorkDay ;
		projectSum.iCheckDay +=pMonthStat[i].iCheckDay ;
		projectSum.iNaturalStandByDay +=pMonthStat[i].iNaturalStandByDay ;
		projectSum.iOtherStandByDay +=pMonthStat[i].iOtherStandByDay ;
		projectSum.fDrillDepth +=pMonthStat[i].fDrillDepth ;
		projectSum.iRefQty +=pMonthStat[i].iRefQty ;
		projectSum.iMicroWellLogQty +=pMonthStat[i].iMicroWellLogQty ;

		if(pMonthStat[i].iMaxShot > projectSum.iMaxShot)
		{
			projectSum.iMaxShot=pMonthStat[i].iMaxShot;
		}

		if(pMonthStat[i].iMinShot < projectSum.iMinShot)
		{
			projectSum.iMinShot=pMonthStat[i].iMinShot;
		}
	}

	int iRow=iMonthQty+1;
	m_rc.SetGridContent (iRow,3,vtos(iProjectShotQty));
	m_rc.SetGridContent (iRow,4,vtos(projectSum.iFinishedShot ));
	m_rc.SetGridContent (iRow,5,vtos(projectSum.iFinishedShot*1.0/iProjectShotQty*100,2));
	m_rc.SetGridContent (iRow,6,vtos(projectSum.iNaturalDay));
	m_rc.SetGridContent (iRow,7,vtos(projectSum.iWorkDay ));
	m_rc.SetGridContent (iRow,8,vtos(projectSum.iCheckDay ));
	m_rc.SetGridContent (iRow,9,vtos(projectSum.iNaturalStandByDay ));
	m_rc.SetGridContent (iRow,10,vtos(projectSum.iOtherStandByDay ));
	m_rc.SetGridContent (iRow,11,vtos(projectSum.fDrillDepth ,1));
	m_rc.SetGridContent (iRow,12,vtos(projectSum.iRefQty ));
	m_rc.SetGridContent (iRow,13,vtos(projectSum.iMicroWellLogQty ));
	m_rc.SetGridContent (iRow,14,vtos(projectSum.iMaxShot ));
	m_rc.SetGridContent (iRow,15,vtos(projectSum.iMinShot ));
	m_rc.SetGridContent (iRow,16,vtos(projectSum.iFinishedShot *1.0/projectSum.iNaturalDay,2));


	m_rc.SetLeftDownString ("驻队监督:"+GetMonitorString(arrayMonitor));

	delete []pMonthStat;

	return ;
}
