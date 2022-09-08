
#include "stdafx.h"
#include "QCDB.h"
#include "ReportDoc.h"
#include "DlgReportProperty.h"
#include "MyDate.h"

////////////////////////////////////////
// 物探工程监督整改工作汇总表
// 表0402监督检查备忘录
////////////////////////////////////////
BOOL CReportDoc::GetDataForReport11(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	CString sStartDay="",sEndDay="";
	
	sStartDay=MakeDateCmpString(	"检查年",
									"检查月",
									"检查日",
									">=",
									dlg.m_iStartYear ,
									dlg.m_iStartMonth ,
									dlg.m_iStartDay);
	if(dlg.m_iEndYear!=0)
	{
		sEndDay= MakeDateCmpString(	"检查年",
									"检查月",
									"检查日",
									"<=",
									dlg.m_iEndYear ,
									dlg.m_iEndMonth ,
									dlg.m_iEndDay);
	}

	CString sTable="表0402监督检查备忘录";
	sSQL.Format ("select * from %s where 项目编号 =  '%s' and %s",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo, 
					(LPCTSTR)sStartDay);

	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}


	arrayFields.Add ("检查线束编号");		//0

	arrayFields.Add ("检查年");			//1
	arrayFields.Add ("检查月");			//2
	arrayFields.Add ("检查日");			//3
	arrayFields.Add ("检查项目与位置");	//4
	arrayFields.Add ("检查情况描述");	//5
	arrayFields.Add ("处理及整改意见");	//6
	arrayFields.Add ("整改年");			//7
	arrayFields.Add ("整改月");	
	arrayFields.Add ("整改日");		
	arrayFields.Add ("整改效果");		//10
	arrayFields.Add ("驻队监督签字");	


	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};
	return TRUE;
}
///////////////////////////////////////////////////
//      ___工区地震采集施工参数一览表
//     表0102地震采集施工参数一览表  表12
///////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport12(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;


	CString sTable="表0102项目地震采集施工参数一览表";
	sSQL.Format ("select * from %s where 项目编号 =  '%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo );

	arrayFields.Add ("项目编号");			//0
	arrayFields.Add ("面元尺寸");			//1
	arrayFields.Add ("覆盖次数");			//2
	arrayFields.Add ("观测系统");			//3
	arrayFields.Add ("接收道数");	//4
	arrayFields.Add ("激发方式");	//5
	arrayFields.Add ("采样间隔");	//6
	arrayFields.Add ("记录长度");			//7
	arrayFields.Add ("道距");	
	arrayFields.Add ("炮点距");		
	arrayFields.Add ("线束");		//10
	arrayFields.Add ("接收线距");	
	arrayFields.Add ("炮线距");	
	arrayFields.Add ("接收线条数");	
	arrayFields.Add ("激发位置");	
	arrayFields.Add ("纵向最小炮检距");		//15	
	arrayFields.Add ("纵向最大炮检距");	
	arrayFields.Add ("最大炮检距");	
	arrayFields.Add ("最大非纵距");	
	arrayFields.Add ("最小炮检距");	
	arrayFields.Add ("检波器型号");			//20
	arrayFields.Add ("检波器下井深度");	
	arrayFields.Add ("组合方式");	
	arrayFields.Add ("井组合方式");	
	arrayFields.Add ("前放增益");	
	arrayFields.Add ("检波器个数");			//25
	arrayFields.Add ("仪器型号");	
	arrayFields.Add ("组合参数");	
	arrayFields.Add ("井组合基距");	
	arrayFields.Add ("记录密度");			//29


	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};
	return TRUE;
}


//////////////////////////////////////////////////////////
// 工区主要技术人员到位情况检查表
// 表0107工区主要技术人员到位情况检查表  表13
//////////////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport13(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	int i=0,j=0;


	CString sTable="表0107主要技术人员到位情况检查表";
	sSQL.Format ("select * from %s where 项目编号 =  '%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo );

	arrayFields.Add ("项目编号");			//0
	arrayFields.Add ("姓名");			//1
	arrayFields.Add ("项目负责");			//2
	arrayFields.Add ("队长");			//3
	arrayFields.Add ("书记");	//4
	arrayFields.Add ("副队长");	//5
	arrayFields.Add ("HSE监督");	//6
	arrayFields.Add ("施工组长");			//7
	arrayFields.Add ("施工员");	
	arrayFields.Add ("仪器组长");		
	arrayFields.Add ("操作员");		//10
	arrayFields.Add ("现场处理组长");	
	arrayFields.Add ("现场处理员");	
	arrayFields.Add ("测量组长");	
	arrayFields.Add ("测量员");	
	arrayFields.Add ("到位情况");		//15	

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	//////////////////////////////////////
	// 获得所有姓名
	//////////////////////////////////////
	CStringArray arrayNames;
	CString sName,sName2;
	CStringArray *pRecord=NULL;
	bool bExist=true;
	int iRecordQty=GetRecordQty();
	for(i=0;i<iRecordQty;i++)
	{
		pRecord=GetRecord(i);
		sName=pRecord->GetAt (1);
		bExist=false;
		for(j=0;j<arrayNames.GetCount ();j++)
		{
			if(sName==arrayNames.GetAt (j))
			{
				bExist=true;
				break;
			}
		}

		if(!bExist)
		{
			arrayNames.Add (sName);
		}
	}

	if(arrayNames.GetCount ()<1)
	{
		return false;
	}

	///////////////////////////////////
	//  获得技术人员的资料
	///////////////////////////////////
	sTable="表0001技术人员基本情况统计表";
	CString s;
	sSQL.Format ("select * from %s where ",(LPCTSTR)sTable);
	int iNameQty=arrayNames.GetCount ();
	for(i=0;i<iNameQty;i++)
	{
		s.Format (" 姓名 =  '%s' ",(LPCTSTR)arrayNames.GetAt (i));
		if(i!=iNameQty-1)
		{
			s+=" or ";
		}
		sSQL+=s;
	}

	sSQL.Format ("select * from %s ",(LPCTSTR)sTable);


	arrayFields.RemoveAll ();
	arrayFields.Add ("姓名");			//0
	arrayFields.Add ("职称");			//1
	arrayFields.Add ("出生年");			//2
	arrayFields.Add ("第一学历");		//3
	arrayFields.Add ("第二学历");		//4
	arrayFields.Add ("第三学历");		//5
	arrayFields.Add ("参加工作年");		//6
	arrayFields.Add ("参加工作月");		//7
	arrayFields.Add ("参加工作日");		//8

	CTableDate dateFrom;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateFrom,&arrayFields,&m_docVice,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	return TRUE;
}

//////////////////////////////////////////
//      工区主要设备到位情况检查表
// 表0108工区主要设备到位情况检查表  表14
//////////////////////////////////////////
BOOL CReportDoc::GetDataForReport14(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	int i=0,j=0;


	CString sTable="表0108主要设备到位情况检查表";
	sSQL.Format ("select * from %s where 项目编号 =  '%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo );

	arrayFields.Add ("项目编号");			//0
	arrayFields.Add ("仪器");			//1
	arrayFields.Add ("检波器");			//2
	arrayFields.Add ("采集站");			//3
	arrayFields.Add ("大线");	//4
	arrayFields.Add ("微机");	//5
	arrayFields.Add ("GPS");	//6
	arrayFields.Add ("计算机");			//7
	arrayFields.Add ("打印机");			//8
	arrayFields.Add ("现场处理机");		//9
	arrayFields.Add ("钻机");		//10
	arrayFields.Add ("电动冲击钻");	//11
	arrayFields.Add ("炸药车");		//12
	arrayFields.Add ("雷管车");		//13
	arrayFields.Add ("钻井水罐车");	//14
	arrayFields.Add ("干钻");		//15
	arrayFields.Add ("大客车");		//16
	arrayFields.Add ("倒线车");		//17
	arrayFields.Add ("查线车");		//18
	arrayFields.Add ("放炮车");		//19
	arrayFields.Add ("放线水罐车");	//20
	arrayFields.Add ("车载电台");	//21
	arrayFields.Add ("手持式电台");	//22
	arrayFields.Add ("设备型号");	//23
	arrayFields.Add ("数量");		//24
	arrayFields.Add ("到位情况");	//25	

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};
}

///////////////////////////////////////////////////////
// ________项目野外采集试验工作监督统计表
//  表0109试验工作监督统计表  表15
///////////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport15(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	int i=0,j=0;


	CString sTable="表0109试验工作监督统计表";
	sSQL.Format ("select * from %s where 项目编号 =  '%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo );

	arrayFields.Add ("项目编号");			//0
	arrayFields.Add ("试验点位置");			//1
	arrayFields.Add ("试验项目");			//2
	arrayFields.Add ("试验因素");	//3
	arrayFields.Add ("炸药类型");	//4
	arrayFields.Add ("固定因素");	//5
	arrayFields.Add ("试验效果");			//6
	arrayFields.Add ("试验点点数");			//7
	arrayFields.Add ("试验点记录");		//8
	arrayFields.Add ("试验段段数");		//9 
	arrayFields.Add ("试验段试验记录");	//10
	arrayFields.Add ("试验段长度");		//11
	arrayFields.Add ("试验年");		//12
	arrayFields.Add ("试验月");	//13
	arrayFields.Add ("试验日");		//14
	arrayFields.Add ("驻队监督");	//15

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};
	return true;
}
