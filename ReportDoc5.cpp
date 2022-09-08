

#include "stdafx.h"
#include "QCDB.h"
#include "ReportDoc.h"
#include "DlgReportProperty.h"
#include "MyDate.h"

///////////////////////////////////////////////
//       探区执行经理巡回检查记录
//  表0404执行经理巡回检查记录  表21
///////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport21(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	CString sStartDay,sEndDay;

	sStartDay=MakeDateCmpString(	"年",
					"月",
					"日",
					">=",
					dlg.m_iStartYear ,
					dlg.m_iStartMonth ,
					dlg.m_iStartDay );

	if(dlg.m_iEndYear!=0)
	{
		sEndDay=MakeDateCmpString(	"年",
					"月",
					"日",
					"<=",
					dlg.m_iEndYear ,
					dlg.m_iEndMonth ,
					dlg.m_iEndDay );
	}

	CString sTable="表0404执行经理巡回检查记录";
	
	sSQL.Format ("select * from %s where 项目编号='%s' and %s ",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo,
				(LPCTSTR)sStartDay);
	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}

	arrayFields.Add ("项目编号");			//0
	arrayFields.Add ("现场监督");			//1
	arrayFields.Add ("探区执行经理");			//2
	arrayFields.Add ("陪同人");	//3 
	arrayFields.Add ("年");	//4 
	arrayFields.Add ("月");	//5 
	arrayFields.Add ("日");	//6 
	arrayFields.Add ("监督计划是否按要求按时编写");							//7 
	arrayFields.Add ("监督工作流程是否按要求展示并执行");					//8 
	arrayFields.Add ("监督工作日志是否按要求记录是否详尽");					//9 
	arrayFields.Add ("工序检查表是否按要求记录是否详尽");					//10 
	arrayFields.Add ("监督工作附件是否按要求收集整理");						//11 
	arrayFields.Add ("基础资料检查时是否留下工作痕迹");						//12 
	arrayFields.Add ("监督数据统计是否准确一致");							//13 
	arrayFields.Add ("周报是否按要求按时统计并上报");						//14 
	arrayFields.Add ("月报是否按要求按时统计并上报");						//15
	arrayFields.Add ("日志周报月报备忘录等与监督工作统计表是否一一对应");	//16
	arrayFields.Add ("备忘录或整改通知书是否按要求使用");					//17
	arrayFields.Add ("监督工作数据统计分析表是否按要求填写与工作日志是否能对应");	//18
	arrayFields.Add ("监理资料展示是否按要求执行");							//19 
	arrayFields.Add ("监督检查工作是否量化量化数据是否能达到投资方要求");	//20 
	arrayFields.Add ("野外检查点的时空分布是否科学是否能有效反映施工全貌");	//21 
	arrayFields.Add ("检查测量时各项指标是否符合要求特殊点是否按要求执行");	//22 
	arrayFields.Add ("检查仪器及附属设备基础资料时是否彻底统计是否齐全");	//23
	arrayFields.Add ("检查激发接收工序时是否确定量化质量标准");				//24 
	arrayFields.Add ("是否有经投资方认可的原始记录评价标准");				//25 
	arrayFields.Add ("施工方法因素等改变或重要问题时是否有投资方的批复意见");	//26 
	arrayFields.Add ("是否与投资方执行经理和项目经理部随时进行信息沟通");	//27 
	arrayFields.Add ("是否存在吃拿卡要报问题");								//28 
	arrayFields.Add ("是否存在与施工方一起欺瞒投资方问题");					//29 
	arrayFields.Add ("是否存在无故离开探区的情况");							//30 
	arrayFields.Add ("是否存在私带民工私带家属介绍包工头问题");				//31 
	arrayFields.Add ("是否存在对承包方领导无理现象");						//32 
	arrayFields.Add ("是否存在生活待遇搞特殊化的问题");						//33 
	arrayFields.Add ("抽查经监督检查过的野外激发点是否仍存在不合格问题");	//34 
	arrayFields.Add ("抽查经监督检查过的野外接收点是否仍存在不合格问题");	//35
	arrayFields.Add ("抽查测量标志特殊点处理等是否存在问题");				//36 
	arrayFields.Add ("野外现场抽查50-100张原始记录是否能到达设计要求");		//37 
	arrayFields.Add ("抽查现场施工基础资料是否填写准确齐全");				//38 
	arrayFields.Add ("抽查表层调查工作是否按要求施工资料是否经监督认可");	//39 
	arrayFields.Add ("抽查野外特殊部位特殊点是否按设计合同要求执行");		//40 
	arrayFields.Add ("现场测量10道线的检波器串阻值是否合格");				//41 
	arrayFields.Add ("要求闷井地区抽查爆炸后闷井情况是否按要求执行");		//42 
	arrayFields.Add ("下井检波器施工时抽查检波器井质量是否符合要求");		//43 
	arrayFields.Add ("激发深度是否按设计因素施工岩性是否准确");				//44 
	arrayFields.Add ("与施工方人员交流观察质量意识标准等落实情况");			//45

	arrayFields.Add ("本次检查情况简评");									//46
	arrayFields.Add ("该项目驻队监督是否能继续胜任监督工作");				//47 
	arrayFields.Add ("对该项目下步监督工作要求");							//48 

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	return true;
}

/////////////////////////////////////////////////////////
//       项目经理部对执行经理巡回检查记录
//   表0405项目经理部对执行经理巡回检查记录  表22
/////////////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport22(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	CString sStartDay,sEndDay;

	sStartDay=MakeDateCmpString(	"年",
					"月",
					"日",
					">=",
					dlg.m_iStartYear ,
					dlg.m_iStartMonth ,
					dlg.m_iStartDay );

	if(dlg.m_iEndYear!=0)
	{
		sEndDay=MakeDateCmpString(	"年",
					"月",
					"日",
					"<=",
					dlg.m_iEndYear ,
					dlg.m_iEndMonth ,
					dlg.m_iEndDay );
	}


	CString sTable="表0405项目经理部对执行经理巡回检查记录";
	
	sSQL.Format ("select * from %s where 项目编号='%s' and %s ",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo,
				(LPCTSTR)sStartDay);
	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}

	arrayFields.Add ("编号");			//0
	arrayFields.Add ("项目编号");			//1
	arrayFields.Add ("项目经理部");			//2
	arrayFields.Add ("执行经理");	//3 
	arrayFields.Add ("年");	//4 
	arrayFields.Add ("月");	//5 
	arrayFields.Add ("日");	//6 

	arrayFields.Add ("是否按要求审查探区所有项目监督工作计划格式是否统一");			//7
	arrayFields.Add ("是否按要求审查探区所有项目监督工作计划格式是否统一评价意见");	//8
	arrayFields.Add ("探区内是否统一监督工作流程");								//9
	arrayFields.Add ("探区内是否统一监督工作流程评价意见");						//10
	arrayFields.Add ("探区内是否统一监督周报月报的格式及内容");					//11
	arrayFields.Add ("探区内是否统一监督周报月报的格式及内容评价意见");			//12
	arrayFields.Add ("探区内是否统一监督记录格式");								//13
	arrayFields.Add ("探区内是否统一监督记录格式评价意见");						//14
	arrayFields.Add ("探区内是否统一监督展示资料格式");							//15
	arrayFields.Add ("探区内是否统一监督展示资料格式评价意见");					//16
	arrayFields.Add ("探区内是否规范了监督工作统计表格");						//17
	arrayFields.Add ("探区内是否规范了监督工作统计表格评价意见");				//18
	arrayFields.Add ("探区内是否统一规范了监督报告内容格式及附表格式");			//19
	arrayFields.Add ("探区内是否统一规范了监督报告内容格式及附表格式评价意见");	//20
	arrayFields.Add ("在有条件的项目是否要求采用EMAIL形式汇报");				//21
	arrayFields.Add ("在有条件的项目是否要求采用EMAIL形式汇报评价意见");		//22
	arrayFields.Add ("与投资方有关领导是否交流沟通了监督工作认识");				//23
	arrayFields.Add ("与投资方有关领导是否交流沟通了监督工作认识评价意见");		//24
	arrayFields.Add ("是否向投资方介绍了公司及的监督工作管理思路");				//25
	arrayFields.Add ("是否向投资方介绍了公司及的监督工作管理思路评价意见");		//26
	arrayFields.Add ("是否了解投资方对监督工作的要求和特点");					//27
	arrayFields.Add ("是否了解投资方对监督工作的要求和特点评价意见");			//28
	arrayFields.Add ("是否把投资方的特殊要求传达到各项目监督人员");				//29
	arrayFields.Add ("是否把投资方的特殊要求传达到各项目监督人员评价意见");		//30
	arrayFields.Add ("是否了解各项目及监督工作动态情况");						//31
	arrayFields.Add ("是否了解各项目及监督工作动态情况评价意见");				//32
	arrayFields.Add ("是否按要求巡回检查了各项目监督工作");						//33
	arrayFields.Add ("是否按要求巡回检查了各项目监督工作评价意见");				//34
	arrayFields.Add ("巡回检查资料是否齐全规范");								//35
	arrayFields.Add ("巡回检查资料是否齐全规范评价意见");						//36
	arrayFields.Add ("是否按要求对技术支持工作进行了安排和实施");				//37
	arrayFields.Add ("是否按要求对技术支持工作进行了安排和实施评价意见");		//38
	arrayFields.Add ("技术支持是否达到了应有的效果");							//39
	arrayFields.Add ("技术支持是否达到了应有的效果评价意见");					//40
	arrayFields.Add ("工作记录是否齐全准确");									//41
	arrayFields.Add ("工作记录是否齐全准确评价意见");							//42
	arrayFields.Add ("是否及时与投资方有关领导进行信息沟通");					//43
	arrayFields.Add ("是否及时与投资方有关领导进行信息沟通评价意见");			//44
	arrayFields.Add ("是否及时与项目经理部进行信息沟通");						//45
	arrayFields.Add ("是否及时与项目经理部进行信息沟通评价意见");				//46
	arrayFields.Add ("大额资金使用是否经过请示");								//47
	arrayFields.Add ("大额资金使用是否经过请示评价意见");						//48
	arrayFields.Add ("是否注重成本控制问题");									//49
	arrayFields.Add ("是否注重成本控制问题评价意见");							//50
	arrayFields.Add ("工作态度是否认真积极不懈怠");								//51
	arrayFields.Add ("工作态度是否认真积极不懈怠评价意见");						//52	
	arrayFields.Add ("是否能创造性开展监督管理工作");							//53
	arrayFields.Add ("是否能创造性开展监督管理工作评价意见");					//54
	arrayFields.Add ("生活待遇方面是否不搞特殊化");								//55
	arrayFields.Add ("生活待遇方面是否不搞特殊化评价意见");						//56



	CTableDate dateStart;

	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	return true;

}

/////////////////////////////////////////////////////////////
//    项目经理部对现场监督巡回检查记录
//   表0406项目经理部对现场监督巡回检查记录  表23
/////////////////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport23(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	CString sStartDay,sEndDay;

	sStartDay=MakeDateCmpString(	"年",
					"月",
					"日",
					">=",
					dlg.m_iStartYear ,
					dlg.m_iStartMonth ,
					dlg.m_iStartDay );

	if(dlg.m_iEndYear!=0)
	{
		sEndDay=MakeDateCmpString(	"年",
					"月",
					"日",
					"<=",
					dlg.m_iEndYear ,
					dlg.m_iEndMonth ,
					dlg.m_iEndDay );
	}


	CString sTable="表0406项目经理部对现场监督巡回检查记录";
	
	sSQL.Format ("select * from %s where 项目编号='%s' and %s ",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo,
				(LPCTSTR)sStartDay);
	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}

	arrayFields.Add ("项目编号");			//0
	arrayFields.Add ("项目经理部");			//1
	arrayFields.Add ("现场监督");			//2
	arrayFields.Add ("陪同人");	//3 
	arrayFields.Add ("年");	//4 
	arrayFields.Add ("月");	//5 
	arrayFields.Add ("日");	//6 

	arrayFields.Add ("监督计划是否经执行经理审批是否按探区统一格式");			//7
	arrayFields.Add ("监督计划是否经执行经理审批是否按探区统一格式评价意见");	//8
	arrayFields.Add ("是否按探区统一的监督工作流程展示并执行");								//9
	arrayFields.Add ("是否按探区统一的监督工作流程展示并执行评价意见");						//10
	arrayFields.Add ("是否按要求记录监督工作日志");					//11
	arrayFields.Add ("是否按要求记录监督工作日志评价意见");			//12
	arrayFields.Add ("如采用工序检查表是否按统一格式和要求填写");								//13
	arrayFields.Add ("如采用工序检查表是否按统一格式和要求填写评价意见");						//14
	arrayFields.Add ("是否按要求收集整理监督工作附件");							//15
	arrayFields.Add ("是否按要求收集整理监督工作附件评价意见");					//16
	arrayFields.Add ("周报是否按要求按时统计并上报");						//17
	arrayFields.Add ("周报是否按要求按时统计并上报评价意见");				//18
	arrayFields.Add ("月报是否按要求按时统计并上报");			//19
	arrayFields.Add ("月报是否按要求按时统计并上报评价意见");	//20
	arrayFields.Add ("日志周报月报备忘录统计表等是否能相互对应");				//21
	arrayFields.Add ("日志周报月报备忘录统计表等是否能相互对应评价意见");		//22
	arrayFields.Add ("备忘录或整改通知书是否按要求使用");				//23
	arrayFields.Add ("备忘录或整改通知书是否按要求使用评价意见");		//24
	arrayFields.Add ("是否认真填写监督工作数据统计分析表");				//25
	arrayFields.Add ("是否认真填写监督工作数据统计分析表评价意见");		//26
	arrayFields.Add ("监理资料展示是否符合探区统一规范");					//27
	arrayFields.Add ("监理资料展示是否符合探区统一规范评价意见");			//28
	arrayFields.Add ("施工方法因素等改变或重要问题时是否有投资方的批复意见");				//29
	arrayFields.Add ("施工方法因素等改变或重要问题时是否有投资方的批复意见评价意见");		//30
	arrayFields.Add ("是否有经投资方认可的激发接收工序量化质量标准");						//31
	arrayFields.Add ("是否有经投资方认可的激发接收工序量化质量标准评价意见");				//32
	arrayFields.Add ("是否有经投资方认可的原始记录评价标准");						//33
	arrayFields.Add ("是否有经投资方认可的原始记录评价标准评价意见");				//34
	arrayFields.Add ("是否有经投资方认可的原始记录评价标准评价意见");								//35
	arrayFields.Add ("是否与投资方执行经理和项目经理部随时进行信息沟通");						//36
	arrayFields.Add ("是否与投资方执行经理和项目经理部随时进行信息沟通评价意见");				//37
	arrayFields.Add ("工作小结或汇报是否抓住重点理念是否清晰");		//38
	arrayFields.Add ("工作小结或汇报是否抓住重点理念是否清晰评价意见");							//39
	arrayFields.Add ("对甲方总监或执行经理检查提出的要求是否记载整理和落实");					//40
	arrayFields.Add ("对甲方总监或执行经理检查提出的要求是否记载整理和落实评价意见");									//41
	arrayFields.Add ("向施工方了解是否做到监督工作纪律无违反");							//42
	arrayFields.Add ("向施工方了解是否做到监督工作纪律无违反评价意见");					//43
	arrayFields.Add ("向投资方了解是否做到对承包方领导不得无理");			//44
	arrayFields.Add ("向投资方了解是否做到对承包方领导不得无理评价意见");						//45
	arrayFields.Add ("向施工方了解是否做到生活待遇不搞特殊化");				//46
	arrayFields.Add ("向施工方了解是否做到生活待遇不搞特殊化评价意见");								//47
	arrayFields.Add ("抽查经监督检查过的野外激发点验证结果是否相符");						//48
	arrayFields.Add ("抽查经监督检查过的野外激发点验证结果是否相符评价意见");									//49
	arrayFields.Add ("抽查经监督检查过的野外接收点验证结果是否相符");							//50
	arrayFields.Add ("抽查经监督检查过的野外接收点验证结果是否相符评价意见");								//51
	arrayFields.Add ("抽查测量标志特殊点处理等验证结果是否相符");						//52	
	arrayFields.Add ("抽查测量标志特殊点处理等验证结果是否相符评价意见");							//53
	arrayFields.Add ("现场抽查部分原始记录是否能达到设计要求");					//54
	arrayFields.Add ("现场抽查部分原始记录是否能达到设计要求评价意见");								//55
	arrayFields.Add ("抽查野外特殊部位特殊点是否按设计合同要求执行");						//56
	arrayFields.Add ("现场抽查检波器串阻值是否合格");						//57
	arrayFields.Add ("现场抽查检波器串阻值是否合格评价意见");						//58
	arrayFields.Add ("是否经常与施工方人员交流质量意识标准等落实情况");						//59
	arrayFields.Add ("是否经常与施工方人员交流质量意识标准等落实情况评价意见");						//60

	CTableDate dateStart;

	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	return true;
}

/////////////////////////////////////////////////////
// 勘探监理项目运行（日）时效统计表
// 表0301监理工作日报  表24
/////////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport24(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	CString sStartDay,sEndDay;

	sStartDay=MakeDateCmpString(	"年",
					"月",
					"日",
					">=",
					dlg.m_iStartYear ,
					dlg.m_iStartMonth ,
					dlg.m_iStartDay );

	if(dlg.m_iEndYear!=0)
	{
		sEndDay=MakeDateCmpString(	"年",
					"月",
					"日",
					"<=",
					dlg.m_iEndYear ,
					dlg.m_iEndMonth ,
					dlg.m_iEndDay );
	}


	CString sTable="表0301监理工作日报";
	
	sSQL.Format ("select * from %s where 项目编号='%s' and %s ",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo,
				(LPCTSTR)sStartDay);
	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}

	arrayFields.Add ("编号");			//0
	arrayFields.Add ("项目编号");			//1
	arrayFields.Add ("驻队监督");			//2
	arrayFields.Add ("测线编号");	//3 
	arrayFields.Add ("年");	//4 
	arrayFields.Add ("月");	//5 
	arrayFields.Add ("日");	//6 

	arrayFields.Add ("离开驻地时间");			//7
	arrayFields.Add ("到达工地时间");			//8
	arrayFields.Add ("铺首排列时间");			//9
	arrayFields.Add ("首炮时间");				//10
	arrayFields.Add ("末炮时间");				//11
	arrayFields.Add ("检查排列时间");			//12
	arrayFields.Add ("测量因素影响");			//13
	arrayFields.Add ("设备因素影响");			//14
	arrayFields.Add ("环境噪音影响");			//15
	arrayFields.Add ("自然条件影响");			//16
	arrayFields.Add ("地方关系影响");			//17
	arrayFields.Add ("其它因素影响");			//18
	arrayFields.Add ("实际放炮时间");			//19
	arrayFields.Add ("天气情况");				//20
	arrayFields.Add ("时效日备注");				//21

	arrayFields.Add ("单井激发1点数");			//22
	arrayFields.Add ("单井激发2点数");			//23
	arrayFields.Add ("单井激发3点数");			//24
	arrayFields.Add ("单井激发4点数");			//25
	arrayFields.Add ("单井激发5点数");			//26
	arrayFields.Add ("单井激发6点数");			//27
	arrayFields.Add ("单井激发7点数");			//28
	arrayFields.Add ("单井激发8点数");			//29
	arrayFields.Add ("单井激发9点数");			//30
	arrayFields.Add ("单井激发10点数");			//31

	arrayFields.Add ("组合激发1点数");			//32
	arrayFields.Add ("组合激发2点数");			//33
	arrayFields.Add ("组合激发3点数");			//34
	arrayFields.Add ("组合激发4点数");			//35
	arrayFields.Add ("组合激发5点数");			//36
	arrayFields.Add ("组合激发6点数");			//37
	arrayFields.Add ("组合激发7点数");			//38
	arrayFields.Add ("组合激发8点数");			//39
	arrayFields.Add ("组合激发9点数");			//40
	arrayFields.Add ("组合激发10点数");			//41



	arrayFields.Add ("核实加密炮数");			//42
	arrayFields.Add ("驻队监督");				//43

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	return true;
}

///////////////////////////////////////////////////////////
//勘探监理项目      年度（月）时效分析表
//表0301监理工作日报  表25
///////////////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport25(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	CString sStartDay,sEndDay;

	sStartDay=MakeDateCmpString(	"年",
					"月",
					"日",
					">=",
					dlg.m_iStartYear ,
					dlg.m_iStartMonth ,
					dlg.m_iStartDay );

	if(dlg.m_iEndYear!=0)
	{
		sEndDay=MakeDateCmpString(	"年",
					"月",
					"日",
					"<=",
					dlg.m_iEndYear ,
					dlg.m_iEndMonth ,
					dlg.m_iEndDay );
	}


	CString sTable="表0301监理工作日报";
	
	sSQL.Format ("select * from %s where 项目编号='%s' and %s ",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo,
				(LPCTSTR)sStartDay);
	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}

	arrayFields.Add ("编号");			//0
	arrayFields.Add ("项目编号");		//1
	arrayFields.Add ("驻队监督");		//2
	arrayFields.Add ("测线编号");		//3 
	arrayFields.Add ("年");				//4 
	arrayFields.Add ("月");				//5 
	arrayFields.Add ("日");				//6 

	arrayFields.Add ("本日测线开工");			//7
	arrayFields.Add ("本日测线完工");			//8

	arrayFields.Add ("单井激发1点数");			//9
	arrayFields.Add ("单井激发2点数");			//10
	arrayFields.Add ("单井激发3点数");			//11
	arrayFields.Add ("单井激发4点数");			//12
	arrayFields.Add ("单井激发5点数");			//13
	arrayFields.Add ("单井激发6点数");			//14
	arrayFields.Add ("单井激发7点数");			//15
	arrayFields.Add ("单井激发8点数");			//16
	arrayFields.Add ("单井激发9点数");			//17
	arrayFields.Add ("单井激发10点数");			//18
	
	arrayFields.Add ("核实加密炮数");			//19
	arrayFields.Add ("复评空点");				//20

	arrayFields.Add ("本日正常施工");				//21
	arrayFields.Add ("本日检修停工");				//22
	arrayFields.Add ("本日自然停工");				//23
	arrayFields.Add ("本日其他停工");				//24

	arrayFields.Add ("钻井进尺");					//25
	arrayFields.Add ("合格小折射点数");				//26
	arrayFields.Add ("合格微测井点数");				//27

	arrayFields.Add ("时效月备注");					//28

	arrayFields.Add ("组合激发1点数");			//29
	arrayFields.Add ("组合激发2点数");			//30
	arrayFields.Add ("组合激发3点数");			//31
	arrayFields.Add ("组合激发4点数");			//32
	arrayFields.Add ("组合激发5点数");			//33
	arrayFields.Add ("组合激发6点数");			//34
	arrayFields.Add ("组合激发7点数");			//35
	arrayFields.Add ("组合激发8点数");			//36
	arrayFields.Add ("组合激发9点数");			//37
	arrayFields.Add ("组合激发10点数");			//38

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	return true;
}
