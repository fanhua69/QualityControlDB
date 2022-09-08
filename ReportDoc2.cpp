
#include "stdafx.h"
#include "QCDB.h"
#include "ReportDoc.h"
#include "DlgReportProperty.h"
#include "MyDate.h"


////////////////////////////////////////////////////
// 物 探 工 程 仪 器 专 业 监 督 周 报 表
// 表0303仪器监督日报  表6
////////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport06(CDlgReportProperty &dlg)
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

	CString sTable="表0303仪器监督日报";
	sSQL.Format ("select * from %s where %s",
					(LPCTSTR)sTable,
					(LPCTSTR)sEndDay);


	arrayFields.Add ("项目编号");		//0

	arrayFields.Add ("年");			//1
	arrayFields.Add ("月");			//2
	arrayFields.Add ("日");			//3
	arrayFields.Add ("仪器型号");	//4
	arrayFields.Add ("年月检时间");	//5
	arrayFields.Add ("年月检数量");	
	arrayFields.Add ("日检时间段");	
	arrayFields.Add ("日检数量");    // 复测率的位置
	arrayFields.Add ("采集站测试时间");
	arrayFields.Add ("采集站测试数量");		//10
	arrayFields.Add ("检波器测试月份");
	arrayFields.Add ("检波器测试数量");	
	arrayFields.Add ("系统极性");	
	arrayFields.Add ("TB延迟");
	arrayFields.Add ("仪器班报时间段");	//15
	arrayFields.Add ("仪器班报数量");	//16
	arrayFields.Add ("野外检查仪器参数");
	arrayFields.Add ("野外检查工作道");			//
	arrayFields.Add ("野外检查环境噪音");			//
	arrayFields.Add ("野外检查检波器完好率");	//20
	arrayFields.Add ("备忘录");	//21
	arrayFields.Add ("备注");		//
	arrayFields.Add ("项目仪器工作运行情况");			//
	arrayFields.Add ("监督工作情况");		//
	arrayFields.Add ("仪器工作存在的问题及整改要求");	//25
	arrayFields.Add ("下周仪器监督工作重点");		//26


	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};
	return TRUE;
}


/////////////////////////////////////
// 物探工程开工验收监督检查表
/////////////////////////////////////
BOOL CReportDoc::GetDataForReport07(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	CString sTable="表0106开工验收检查表";
	sSQL.Format ("select * from %s where 项目编号='%s'",(LPCTSTR)sTable,(LPCTSTR)m_sProjectNo);

	arrayFields.Add ("项目编号");		//0

	arrayFields.Add ("监督检查年");			//1
	arrayFields.Add ("监督检查月");			//2
	arrayFields.Add ("监督检查日");			//3
	arrayFields.Add ("监督姓名");			//4

	arrayFields.Add ("地震仪器型号数量及使用年限");	//5
	arrayFields.Add ("采集仪器执行标准");			//6
	arrayFields.Add ("采集仪器年月检及检验记录");	//7
	arrayFields.Add ("采集站型号数量及使用年限");	//8
	arrayFields.Add ("电源站型号数量及使用年限");	//9
	arrayFields.Add ("交叉站型号数量及使用年限");	//10
	arrayFields.Add ("采集站年检及检验记录");		//11
	arrayFields.Add ("可控震源型号数量");			//12
	arrayFields.Add ("可控震源年检及检验记录");		//13
	arrayFields.Add ("表层调查仪器型号及使用年限");	//14
	arrayFields.Add ("表层调查仪器年检及检验记录");	//15
	arrayFields.Add ("表层调查排列长度和道距校准记录");	//16
	arrayFields.Add ("爆炸机型号数量及更改说明");	//17
	arrayFields.Add ("爆炸机TB延迟测试记录");		//18
	arrayFields.Add ("检波器型号数量及使用年限");	//19
	arrayFields.Add ("大线型号数量及使用年限");		//20
	arrayFields.Add ("交叉线型号数量及使用年限");	//21
	arrayFields.Add ("外设检测标准");				//22
	arrayFields.Add ("系统极性测试资料方法及数量");	//23
	arrayFields.Add ("系统延迟测试记录和班报");		//24
	arrayFields.Add ("检波器测试仪型号数量及使用年限");	//25
	arrayFields.Add ("检波器测试仪年度鉴定证书");	//26
	arrayFields.Add ("检波器测试记录及检查情况");	//27
	arrayFields.Add ("表层调查检波器检查及测试情况");	//28
	arrayFields.Add ("井口检波器检查及测试情况");		//29 // Report_Part_1

	arrayFields.Add ("测量技术设计");					//30
	arrayFields.Add ("测量仪器型号数量及使用年限");		//31
	arrayFields.Add ("测量仪器检验合格证书");			//32
	arrayFields.Add ("测量应用软件运行状况");			//33
	arrayFields.Add ("勘探部署图和地形图");				//34
	arrayFields.Add ("工区踏勘报告");					//35
	arrayFields.Add ("设计坐标校核和展图核对");			//36
	arrayFields.Add ("GPS等方法加密控制点成果");		//37

	arrayFields.Add ("采集项目设计及甲方批复意见");		//38
	arrayFields.Add ("物探采集技术标准及规范");			//39
	arrayFields.Add ("采集方法试验方案");				//40
	arrayFields.Add ("工区以往典型剖面收集");			//41
	arrayFields.Add ("工区部署图");						//42
	arrayFields.Add ("目的层构造图");					//43
	arrayFields.Add ("工区地形图");						//44	
	arrayFields.Add ("地层系统柱状图地质图幅说明书");	//45
	arrayFields.Add ("技术人员对地质目标的认识");		//46

	arrayFields.Add ("主要队领导及技术骨干到位情况");	//47
	arrayFields.Add ("钻机可控震源等特种设备到位情况");	//48
	arrayFields.Add ("承诺车辆及其它设备到位情况");		//49
	arrayFields.Add ("现场处理机软硬件配置");			//50

	arrayFields.Add ("质量教育标准宣贯学习设计和记录");	//51
	arrayFields.Add ("岗位技术培训岗位练兵情况");		//52
	arrayFields.Add ("质量管理组织及管理措施");			//53
	arrayFields.Add ("质量活动计划和目标");				//54
	arrayFields.Add ("HSE管理组织及管理措施");			//55
	arrayFields.Add ("HSE培训和审核");					//56
	arrayFields.Add ("8485物品存放管理使用措施");		//57
	arrayFields.Add ("工区重点隐患登记及对策");			//58
	arrayFields.Add ("特种岗位操作证");					//59
	arrayFields.Add ("炊事人员体检证明");				//60
	arrayFields.Add ("饮用水检测证明");					//61
	arrayFields.Add ("营地垃圾处理措施");				//62
	arrayFields.Add ("厕所设置");						//63
	arrayFields.Add ("紧急集合点设置及标志");			//64
	arrayFields.Add ("营地宿舍消防用电设施及安全标识");	//65

	arrayFields.Add ("施工方自检情况");	//66
	arrayFields.Add ("监督检查结果");	//67
	arrayFields.Add ("施工方检查年");	//68
	arrayFields.Add ("施工方检查月");	//69
	arrayFields.Add ("施工方检查日");	//70

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};
	return TRUE;
}

BOOL CReportDoc::GetDataForReport08(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	CString sStartDay,sEndDay;

	sStartDay=MakeDateCmpString(	"检查年",
					"检查月",
					"检查日",
					">=",
					dlg.m_iStartYear ,
					dlg.m_iStartMonth ,
					dlg.m_iStartDay );

	if(dlg.m_iEndYear!=0)
	{
		sEndDay=MakeDateCmpString(	"检查年",
					"检查月",
					"检查日",
					"<=",
					dlg.m_iEndYear ,
					dlg.m_iEndMonth ,
					dlg.m_iEndDay );
	}

	CString sTable="表0401施工工序监督检查表";
	
	sSQL.Format ("select * from %s where 项目编号='%s' and %s ",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo,
				(LPCTSTR)sStartDay);
	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}

	arrayFields.Add ("项目编号");		//0

	arrayFields.Add ("检查年");			//1
	arrayFields.Add ("检查月");			//2
	arrayFields.Add ("检查日");			//3

	arrayFields.Add ("检查项目试验");			//4
	arrayFields.Add ("检查项目测量");			//5
	arrayFields.Add ("检查项目激发");			//6
	arrayFields.Add ("检查项目接收");			//7
	arrayFields.Add ("检查项目仪器");			//8
	arrayFields.Add ("检查项目表层调查");			//9
	arrayFields.Add ("检查项目现场处理");			//10
	arrayFields.Add ("检查项目原始资料");			//11
	arrayFields.Add ("检查位置");			//12
	arrayFields.Add ("检查数量");			//13
	arrayFields.Add ("检查情况");			//14
	arrayFields.Add ("附件图像资料编号");			//15
	arrayFields.Add ("附件基础资料编号");			//16
	arrayFields.Add ("附件其它资料编号");			//17
	arrayFields.Add ("检查结果");			//18
	arrayFields.Add ("整改意见");			//19
	arrayFields.Add ("整改效果");			//20
	arrayFields.Add ("整改年");			//21
	arrayFields.Add ("整改月");			//22
	arrayFields.Add ("整改日");			//23
	arrayFields.Add ("陪同检查人");			//24
	arrayFields.Add ("驻队监督");			//25

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};
	return TRUE;
}

///////////////////////////////////////
// 物探工程监督检查备忘录
///////////////////////////////////////
BOOL CReportDoc::GetDataForReport09(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	CString sStartDay,sEndDay;

	sStartDay=MakeDateCmpString(	"检查年",
					"检查月",
					"检查日",
					">=",
					dlg.m_iStartYear ,
					dlg.m_iStartMonth ,
					dlg.m_iStartDay );

	if(dlg.m_iEndYear!=0)
	{
		sEndDay=MakeDateCmpString(	"检查年",
					"检查月",
					"检查日",
					"<=",
					dlg.m_iEndYear ,
					dlg.m_iEndMonth ,
					dlg.m_iEndDay );
	}

	CString sTable="表0402监督检查备忘录";
	sSQL.Format ("select * from %s where 项目编号='%s' and %s ",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo,
				(LPCTSTR)sStartDay);
	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}

	arrayFields.Add ("项目编号");		//0

	arrayFields.Add ("检查年");			//1
	arrayFields.Add ("检查月");			//2
	arrayFields.Add ("检查日");			//3

	arrayFields.Add ("备忘录编号");			//4
	arrayFields.Add ("检查线束编号");			//5
	arrayFields.Add ("检查人");			//6
	arrayFields.Add ("关于");			//7
	arrayFields.Add ("检查项目与位置");			//8
	arrayFields.Add ("检查情况描述");			//9
	arrayFields.Add ("处理及整改意见");			//10
	arrayFields.Add ("整改效果");			//11
	arrayFields.Add ("整改年");			//12
	arrayFields.Add ("整改月");			//13
	arrayFields.Add ("整改日");			//14
	arrayFields.Add ("整改验证年");			//15
	arrayFields.Add ("整改验证月");			//16
	arrayFields.Add ("整改验证日");			//17
	arrayFields.Add ("施工单位领导签字");			//18
	arrayFields.Add ("施工单位领导签字年");			//19
	arrayFields.Add ("施工单位领导签字月");			//20
	arrayFields.Add ("施工单位领导签字日");			//21
	arrayFields.Add ("驻队监督签字");			//22
	arrayFields.Add ("驻队监督签字年");			//23
	arrayFields.Add ("驻队监督签字月");			//24
	arrayFields.Add ("驻队监督签字日");			//25

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};
	return TRUE;
}


////////////////////////////////////////////////
//  物探工程监督工作数据统计分析表
////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport10(CDlgReportProperty &dlg)
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

	arrayFields.Add ("项目编号");		//0

	arrayFields.Add ("年");			//1
	arrayFields.Add ("月");			//2
	arrayFields.Add ("日");			//3

	arrayFields.Add ("检查激发点数");			//4
	arrayFields.Add ("合格激发点数");			//5
	arrayFields.Add ("检查接收点数");			//6
	arrayFields.Add ("合格接收点数");			//7
	arrayFields.Add ("检查记录张数");			//8
	arrayFields.Add ("复评一级");			//9
	arrayFields.Add ("复评二级");			//10
	arrayFields.Add ("复评废品");			//11
	arrayFields.Add ("核实小折射点数");			//12 // = 检查小折射点数
	arrayFields.Add ("合格小折射点数");			//13
	arrayFields.Add ("核实微测井点数");			//14//  = 检查微测井点数
	arrayFields.Add ("合格微测井点数");			//15
	arrayFields.Add ("检查测量点数");			//16
	arrayFields.Add ("合格测量点数");			//17
	arrayFields.Add ("复评备注");			//18
	arrayFields.Add ("驻队监督");			//19

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};
	return TRUE;
}

