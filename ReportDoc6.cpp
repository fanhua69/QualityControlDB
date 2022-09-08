
#include "stdafx.h"
#include "QCDB.h"
#include "ReportDoc.h"
#include "DlgReportProperty.h"
#include "MyDate.h"

///////////////////////////////////////////////////////////
//勘探监理项目炸药、雷管（日）使用情况统计表
//表0301监理工作日报  表26
///////////////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport26(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	CString sStartDay,sEndDay;

	// 获得本项目所有记录，为了计算库存：
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
	
	sSQL.Format ("select * from %s where 项目编号='%s' ",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo);
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

	arrayFields.Add ("雷管入库数量");			//7
	arrayFields.Add ("雷管出库数量");			//8
	arrayFields.Add ("雷管大炮消耗");			//9
	arrayFields.Add ("雷管表层消耗");			//10
	arrayFields.Add ("雷管其他消耗");			//11
	arrayFields.Add ("炸药入库数量");			//12
	arrayFields.Add ("炸药出库数量");			//13
	arrayFields.Add ("炸药大炮消耗");			//14
	arrayFields.Add ("炸药表层消耗");			//15
	arrayFields.Add ("炸药其他消耗");			//16


	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	return true;
}

///////////////////////////////////////////////
// 勘探监理项目投资方及施工方合同情况表
// 表0101项目  表27
///////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport27(CDlgReportProperty &dlg)
{
	// This report does not need daily data.
	return true;
}

///////////////////////////////////////////////
// 勘探监理项目成本管理（月）统计表
// 表0501成本管理月统计表  表28
///////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport28(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	CString sStartDay,sEndDay;

	if(dlg.m_iStartYear!=0)
	{
		sStartDay=MakeDateCmpString(	"年",
					"月",
					"月",
					">=",
					dlg.m_iStartYear ,
					dlg.m_iStartMonth ,
					dlg.m_iStartMonth );
	}

	if(dlg.m_iEndYear!=0)
	{
		sEndDay=MakeDateCmpString(	"年",
					"月",
					"月",
					"<=",
					dlg.m_iEndYear ,
					dlg.m_iEndMonth ,
					dlg.m_iEndMonth );
	}

	CString sTable="表0501成本管理月统计表";
	
	sSQL.Format ("select * from %s where 项目编号='%s' ",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo);
	if(sStartDay!="")
	{
		sSQL+=" and "+sStartDay;
	}

	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}

	arrayFields.Add ("编号");			//0
	arrayFields.Add ("项目编号");		//1
	arrayFields.Add ("驻队监督");		//2
	arrayFields.Add ("备注");			//3 
	arrayFields.Add ("年");				//4 
	arrayFields.Add ("月");				//5 

	arrayFields.Add ("雷管");			//6
	arrayFields.Add ("炸药");			//7
	arrayFields.Add ("炮线");			//8
	arrayFields.Add ("燃油");			//9 
	arrayFields.Add ("材料");			//10
	arrayFields.Add ("工资补贴奖金");	//11
	arrayFields.Add ("其它直接成本");	//12

	arrayFields.Add ("设备租赁");		//13
	arrayFields.Add ("设备折旧");		//14
	arrayFields.Add ("土地补偿");		//15
	arrayFields.Add ("其它间接成本");	//16

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	return true;
}

///////////////////////////////////////////////////////////
// 勘探监理项目成本管理（月）分析表
//表0501成本管理月统计表，合同月炮成本额从表0101项目中拿出  表29
//本月施工天数、本月完成炮数等从表0301日报中得出
///////////////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport29(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	CString sStartDay,sEndDay;

	if(dlg.m_iStartYear!=0)
	{
		sStartDay=MakeDateCmpString(	"年",
					"月",
					"月",
					">=",
					dlg.m_iStartYear ,
					dlg.m_iStartMonth ,
					dlg.m_iStartMonth );
	}

	if(dlg.m_iEndYear!=0)
	{
		sEndDay=MakeDateCmpString(	"年",
					"月",
					"月",
					"<=",
					dlg.m_iEndYear ,
					dlg.m_iEndMonth ,
					dlg.m_iEndMonth );
	}

	//////////////////////////////////////////////
	// 第一获得本月直接成本和间接成本
	//////////////////////////////////////////////
	CString sTable="表0501成本管理月统计表";
	
	sSQL.Format ("select * from %s where 项目编号='%s' ",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo);
	if(sStartDay!="")
	{
		sSQL+=" and "+sStartDay;
	}

	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}

	arrayFields.Add ("编号");			//0
	arrayFields.Add ("项目编号");		//1
	arrayFields.Add ("驻队监督");		//2
	arrayFields.Add ("备注");			//3 
	arrayFields.Add ("年");				//4 
	arrayFields.Add ("月");				//5 

	arrayFields.Add ("雷管");			//6
	arrayFields.Add ("炸药");			//7
	arrayFields.Add ("炮线");			//8
	arrayFields.Add ("燃油");			//9 
	arrayFields.Add ("材料");			//10
	arrayFields.Add ("工资补贴奖金");	//11
	arrayFields.Add ("其它直接成本");	//12

	arrayFields.Add ("设备租赁");		//13
	arrayFields.Add ("设备折旧");		//14
	arrayFields.Add ("土地补偿");		//15
	arrayFields.Add ("其它间接成本");	//16

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	//////////////////////////////////////////
	// 第二获得本月炮数，本月施工天数
	/////////////////////////////////////////
	sTable="表0301监理工作日报";
	
	sSQL.Format ("select * from %s where 项目编号='%s' and %s ",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo,
				(LPCTSTR)sStartDay);
	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}

	arrayFields.RemoveAll ();
	arrayFields.Add ("年");				//0 
	arrayFields.Add ("月");				//1 
	arrayFields.Add ("日");				//2 

	arrayFields.Add ("单井激发1点数");			//3
	arrayFields.Add ("单井激发2点数");			//4 
	arrayFields.Add ("单井激发3点数");			//5 
	arrayFields.Add ("单井激发4点数");			//6 
	arrayFields.Add ("单井激发5点数");			//7 
	arrayFields.Add ("单井激发6点数");			//8
	arrayFields.Add ("单井激发7点数");			//9 
	arrayFields.Add ("单井激发8点数");			//10
	arrayFields.Add ("单井激发9点数");			//11
	arrayFields.Add ("单井激发10点数");			//12

	arrayFields.Add ("本日正常施工");			//13

	arrayFields.Add ("组合激发1点数");			//14
	arrayFields.Add ("组合激发2点数");			//15
	arrayFields.Add ("组合激发3点数");			//16
	arrayFields.Add ("组合激发4点数");			//17
	arrayFields.Add ("组合激发5点数");			//18
	arrayFields.Add ("组合激发6点数");			//19
	arrayFields.Add ("组合激发7点数");			//20
	arrayFields.Add ("组合激发8点数");			//21
	arrayFields.Add ("组合激发9点数");			//22
	arrayFields.Add ("组合激发10点数");			//23


	CTableDate dateFrom;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateFrom,&arrayFields,&m_docVice,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	return true;
}

///////////////////////////////////////////////////
//   物探工程质量监控系统QC报告入库清单
//   表0304QC报告入库清单  表30
///////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport30(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	CString sStartDay,sEndDay;

	if(dlg.m_iStartYear!=0)
	{
		sStartDay=MakeDateCmpString(	"年",
					"月",
					"月",
					">=",
					dlg.m_iStartYear ,
					dlg.m_iStartMonth ,
					dlg.m_iStartMonth );
	}

	if(dlg.m_iEndYear!=0)
	{
		sEndDay=MakeDateCmpString(	"年",
					"月",
					"月",
					"<=",
					dlg.m_iEndYear ,
					dlg.m_iEndMonth ,
					dlg.m_iEndMonth );
	}

	//////////////////////////////////////////////
	// 
	//////////////////////////////////////////////
	CString sTable="表0304QC报告入库清单";
	
	sSQL.Format ("select * from %s where 项目编号='%s' ",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo);
	if(sStartDay!="")
	{
		sSQL+=" and "+sStartDay;
	}

	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}

	arrayFields.Add ("编号");			//0
	arrayFields.Add ("项目编号");		//1
	arrayFields.Add ("驻队监督");		//2
	arrayFields.Add ("年");				//3 
	arrayFields.Add ("月");				//4 
	arrayFields.Add ("日");				//5 

	arrayFields.Add ("参考物理点");		//6	
	arrayFields.Add ("SPS");			//7
	arrayFields.Add ("检波器测试");		//8
	arrayFields.Add ("激发因素设计");	//9
	arrayFields.Add ("静校正");			//10
	arrayFields.Add ("年月日检");		//11
	arrayFields.Add ("环境噪音");		//12
	arrayFields.Add ("可控震源");		//13
	arrayFields.Add ("测量成果");		//14

	arrayFields.Add ("备注");			//15

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};
}
