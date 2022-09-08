
#include "stdafx.h"
#include "QCDB.h"
#include "ReportDoc.h"
#include "DlgReportProperty.h"
#include "MyDate.h"

////////////////////////////////////////////////
//  ________项目野外采集施工方法监督统计表
//  表0201测线 表16
////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport16(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	int i=0,j=0;


	CString sTable="表0201测线";
	sSQL.Format ("select * from %s where 项目编号 =  '%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo );

	arrayFields.Add ("项目编号");		//0
	arrayFields.Add ("测线名称");		//1
	arrayFields.Add ("仪器型号");		//2
	arrayFields.Add ("道数");			//3
	arrayFields.Add ("覆盖次数");		//4
	arrayFields.Add ("道距");			//5
	arrayFields.Add ("道距");			//6  // for occupy this position
	arrayFields.Add ("道距");			//7  // for occupy this position
	arrayFields.Add ("观测系统");		//8
	arrayFields.Add ("检波器型号");		//9 
	arrayFields.Add ("检波器组合个数");	//10
	arrayFields.Add ("检波器组合LX");	//11
	arrayFields.Add ("检波器组合LY");	//12
	arrayFields.Add ("检波器组合图形");	//13
	arrayFields.Add ("前放");			//14
	arrayFields.Add ("低截");			//15
	arrayFields.Add ("高截");			//16
	arrayFields.Add ("采样率");			//17
	arrayFields.Add ("记录长度");		//18
	arrayFields.Add ("施工方法备注");	//19
	arrayFields.Add ("驻队监督");		//20

	arrayFields.Add ("单井A井深");		//21
	arrayFields.Add ("单井A药量");		//22
	arrayFields.Add ("单井B井深");		//23
	arrayFields.Add ("单井B药量");		//24
	arrayFields.Add ("单井C井深");		//25
	arrayFields.Add ("单井C药量");		//26
	arrayFields.Add ("单井D井深");		//27
	arrayFields.Add ("单井D药量");		//28
	arrayFields.Add ("单井E井深");		//29
	arrayFields.Add ("单井E药量");		//30

	arrayFields.Add ("组合井A口数");		//31
	arrayFields.Add ("组合井A井深");		//32
	arrayFields.Add ("组合井A药量");		//33
	arrayFields.Add ("组合井B口数");		//34
	arrayFields.Add ("组合井B井深");		//35
	arrayFields.Add ("组合井B药量");		//36
	arrayFields.Add ("组合井C口数");		//37
	arrayFields.Add ("组合井C井深");		//38
	arrayFields.Add ("组合井C药量");		//39
	arrayFields.Add ("组合井D口数");		//40
	arrayFields.Add ("组合井D井深");		//41
	arrayFields.Add ("组合井D药量");		//42
	arrayFields.Add ("组合井E口数");		//43
	arrayFields.Add ("组合井E井深");		//44
	arrayFields.Add ("组合井E药量");		//45

	CTableDate dateStart;

	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};
	return true;
}

///////////////////////////////////////////////////////////////////
//  ________项目野外采集施工完成实物工作量监督统计表
//  设计工作量在表0201测线中，实际工作量在表0301监理工作日报  表17
///////////////////////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport17(CDlgReportProperty &dlg)
{

	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	int i=0,j=0;


	///////////////////////
	// 测线表
	///////////////////////
	CString sTable="表0201测线";
	sSQL.Format ("select * from %s where 项目编号 =  '%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo );

	arrayFields.Add ("测线编号");			//0
	arrayFields.Add ("测线名称");			//1
	arrayFields.Add ("设计满覆盖长度");		//2
	arrayFields.Add ("设计二维激发点数");	//3
	arrayFields.Add ("设计三维激发点数");	//4
	arrayFields.Add ("完成工作量备注");		//5
	
	CTableDate dateStart;

	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	//////////////////////////////////////////////
	// 表0301监理工作日报
	//////////////////////////////////////////////
	sTable="表0301监理工作日报";
	sSQL.Format ("select * from %s where 项目编号 =  '%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo );

	arrayFields.RemoveAll ();
	arrayFields.Add ("测线编号");		//0
	arrayFields.Add ("测线编号");		//1  // Occupy position
	arrayFields.Add ("核实加密炮数");	//2
	arrayFields.Add ("复评一级");		//3
	arrayFields.Add ("复评二级");		//4
	arrayFields.Add ("复评废品");		//5
	arrayFields.Add ("复评空点");		//6
	arrayFields.Add ("合格小折射点数");	//7
	arrayFields.Add ("合格微测井点数");	//8

	arrayFields.Add ("年");	//9
	arrayFields.Add ("月");	//10
	arrayFields.Add ("日");	//11

	arrayFields.Add ("驻队监督");  //12

	arrayFields.Add ("单井激发1点数");		//13
	arrayFields.Add ("单井激发2点数");		//14
	arrayFields.Add ("单井激发3点数");		//15
	arrayFields.Add ("单井激发4点数");		//16
	arrayFields.Add ("单井激发5点数");		//17
	arrayFields.Add ("单井激发6点数");		//18
	arrayFields.Add ("单井激发7点数");		//19
	arrayFields.Add ("单井激发8点数");		//20
	arrayFields.Add ("单井激发9点数");		//21
	arrayFields.Add ("单井激发10点数");		//22


	arrayFields.Add ("组合激发1点数");		//23
	arrayFields.Add ("组合激发2点数");		//24
	arrayFields.Add ("组合激发3点数");		//25
	arrayFields.Add ("组合激发4点数");		//26
	arrayFields.Add ("组合激发5点数");		//27
	arrayFields.Add ("组合激发6点数");		//28
	arrayFields.Add ("组合激发7点数");		//29
	arrayFields.Add ("组合激发8点数");		//30
	arrayFields.Add ("组合激发9点数");		//31
	arrayFields.Add ("组合激发10点数");		//32
	
	CTableDate dateFrom;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateFrom,&arrayFields,&m_docVice ,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	return true;
}


///////////////////////////////////////////////////
//  年度           地震勘探激发因素统计表
//           （表0201测线）  表18
///////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport18(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	int i=0,j=0;

	///////////////////////
	// 测线表
	///////////////////////
	CString sTable="表0201测线";
	sSQL.Format ("select * from %s where 项目编号 =  '%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo );

	arrayFields.Add ("测线编号");			//0
	arrayFields.Add ("测线名称");			//1
	arrayFields.Add ("设计二维激发点数");	//2
	arrayFields.Add ("设计三维激发点数");	//3 
	
	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,&m_docVice,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	//////////////////////////////////////////////
	// 表0301监理工作日报
	//////////////////////////////////////////////
	sTable="表0301监理工作日报";
	sSQL.Format ("select * from %s where 项目编号 =  '%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo );

	arrayFields.RemoveAll ();
	arrayFields.Add ("测线编号");			//0

	arrayFields.Add ("单井激发1点数");		//1
	arrayFields.Add ("单井激发2点数");		//2
	arrayFields.Add ("单井激发3点数");		//3
	arrayFields.Add ("单井激发4点数");		//4
	arrayFields.Add ("单井激发5点数");		//5
	arrayFields.Add ("单井激发6点数");		//6
	arrayFields.Add ("单井激发7点数");		//7
	arrayFields.Add ("单井激发8点数");		//8
	arrayFields.Add ("单井激发9点数");		//9
	arrayFields.Add ("单井激发10点数");		//10

	arrayFields.Add ("组合激发1点数");		//11
	arrayFields.Add ("组合激发2点数");		//12
	arrayFields.Add ("组合激发3点数");		//13
	arrayFields.Add ("组合激发4点数");		//14
	arrayFields.Add ("组合激发5点数");		//15
	arrayFields.Add ("组合激发6点数");		//16
	arrayFields.Add ("组合激发7点数");		//17
	arrayFields.Add ("组合激发8点数");		//18
	arrayFields.Add ("组合激发9点数");		//19
	arrayFields.Add ("组合激发10点数");		//20

	arrayFields.Add ("高速层激发点数");		//21

	arrayFields.Add ("激发因素备注");		//22
	
	arrayFields.Add ("驻队监督");  //13


	
	CTableDate dateFrom;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateFrom,&arrayFields,this ,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	return true;
}


///////////////////////////////////////////////
//  地震采集监视记录初、复评对照表
//     （表6监理日报）  表19
///////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport19(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	int i=0,j=0;

	///////////////////////
	// 测线表
	///////////////////////
	CString sTable="表0201测线";
	sSQL.Format ("select * from %s where 项目编号 =  '%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo );

	arrayFields.Add ("测线编号");			//0
	arrayFields.Add ("测线名称");			//1
	arrayFields.Add ("设计二维激发点数");	//2
	arrayFields.Add ("设计三维激发点数");	//3 
	
	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,&m_docVice,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	//////////////////////////////////////////////
	// 表0301监理工作日报
	//////////////////////////////////////////////
	sTable="表0301监理工作日报";
	sSQL.Format ("select * from %s where 项目编号 =  '%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo );

	arrayFields.RemoveAll ();
	arrayFields.Add ("测线编号");		//0
	arrayFields.Add ("单井激发1点数");		//1
	arrayFields.Add ("单井激发2点数");		//2
	arrayFields.Add ("单井激发3点数");		//3
	arrayFields.Add ("单井激发4点数");		//4
	arrayFields.Add ("单井激发5点数");		//5
	arrayFields.Add ("单井激发6点数");		//6
	arrayFields.Add ("单井激发7点数");		//7
	arrayFields.Add ("单井激发8点数");		//8
	arrayFields.Add ("单井激发9点数");		//9
	arrayFields.Add ("单井激发10点数");		//10

	arrayFields.Add ("初评一级");		//11
	arrayFields.Add ("初评二级");		//12
	arrayFields.Add ("初评空点");		//13
	arrayFields.Add ("初评废品");		//14
	arrayFields.Add ("复评一级");		//15
	arrayFields.Add ("复评二级");		//16
	arrayFields.Add ("复评空点");		//17
	arrayFields.Add ("复评废品");		//18
	arrayFields.Add ("核实小折射点数");		//19
	arrayFields.Add ("合格小折射点数");		//20
	arrayFields.Add ("核实微测井点数");		//21
	arrayFields.Add ("合格微测井点数");		//22
	arrayFields.Add ("复评备注");			//23
	
	arrayFields.Add ("驻队监督");			//24

	arrayFields.Add ("组合激发1点数");		//25
	arrayFields.Add ("组合激发2点数");		//26
	arrayFields.Add ("组合激发3点数");		//27
	arrayFields.Add ("组合激发4点数");		//28
	arrayFields.Add ("组合激发5点数");		//39
	arrayFields.Add ("组合激发6点数");		//30
	arrayFields.Add ("组合激发7点数");		//31
	arrayFields.Add ("组合激发8点数");		//32
	arrayFields.Add ("组合激发9点数");		//33
	arrayFields.Add ("组合激发10点数");		//34
	
	CTableDate dateFrom;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateFrom,&arrayFields,this ,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	return true;
}


/////////////////////////////////////////////////
//  物探工程原始记录监督复评降级文件登记表
//表0403原始记录监督复评降级文件登记表  表20 
/////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport20(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	int i=0,j=0;

	///////////////////////
	// 测线表
	///////////////////////
	CString sTable="表0403原始记录监督复评降级文件登记表";
	sSQL.Format ("select * from %s where 项目编号 =  '%s' and 测线编号='%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo,
					(LPCTSTR)m_sLineNo);

	arrayFields.Add ("文件号");			//0
	arrayFields.Add ("合格");			//1
	arrayFields.Add ("废品");			//2
	arrayFields.Add ("降级原因目的层");	//3 
	arrayFields.Add ("降级原因工作道");	//4 
	arrayFields.Add ("降级原因初至时间");	//5 
	arrayFields.Add ("降级原因能量");	//6 
	arrayFields.Add ("降级原因干扰");	//7 
	arrayFields.Add ("降级原因T值");	//8 
	arrayFields.Add ("降级原因其他");	//9 
	
	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	//////////////////////////////////////////////
	// 表0301监理工作日报
	//////////////////////////////////////////////
	sTable="表0301监理工作日报";
	sSQL.Format ("select * from %s where 项目编号 =  '%s' and 测线编号='%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo,
					(LPCTSTR)m_sLineNo);

	arrayFields.RemoveAll ();
	arrayFields.Add ("驻队监督");		//0
	
	CTableDate dateFrom;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateFrom,&arrayFields,&m_docVice  ,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	return true;
}

