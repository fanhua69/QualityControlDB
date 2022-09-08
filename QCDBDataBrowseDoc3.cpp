
#include "stdafx.h"
#include "QCDB.h"
#include "QCDBDataBrowseDoc.h"
#include "fhcglobal.h"
#include "FHMainFrm.h"
#include "qcglobal.h"

// 表1011检波器测试情况资料
bool CQCDBDataBrowseDoc::InputQCData1011(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	

	int iNo=pReader->GetReportNo ();
	if(iNo!=20&&iNo!=21)
	{
		AfxMessageBox("QC报告号码不对,应为20或者21,这个文件是:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (17);
	arrayFields.SetAt (0,"编号");
	arrayFields.SetAt (1,"项目编号");
	arrayFields.SetAt (2,"测线编号");
	arrayFields.SetAt (3,"测试年");
	arrayFields.SetAt (4,"测试月");
	arrayFields.SetAt (5,"测试日");
	arrayFields.SetAt (6,"测试类型");
	arrayFields.SetAt (7,"检波器型号");
	arrayFields.SetAt (8,"地震仪型号(地震仪用)");
	arrayFields.SetAt (9 ,"串内串联数(地震仪用)");
	arrayFields.SetAt (10,"串内并联数(地震仪用)");
	arrayFields.SetAt (11,"串联数目");
	arrayFields.SetAt (12,"并联数目");
	arrayFields.SetAt (13,"小线电阻率(ohm/100m)");
	arrayFields.SetAt (14,"小线上两检波器间距离(m)");
	arrayFields.SetAt (15,"第一检波器到大线距离(m)");
	arrayFields.SetAt (16,"已上传服务器");


	CMyDate date;
	date.Set (pReader->GetItemValue (8));
	CStringArray arrayValues;

	arrayValues.SetSize (17);
	arrayValues.SetAt(0,sTestNo);
	arrayValues.SetAt(1,sProjectNo);
	arrayValues.SetAt(2,::GetLineNo (sProjectNo,pReader->GetItemValue (6)));
	arrayValues.SetAt(3,vtos(date.GetYear ()));
	arrayValues.SetAt(4,vtos(date.GetMonth()));
	arrayValues.SetAt(5,vtos(date.GetDay()));

	if(iNo==20)
	{
		arrayValues.SetAt(6,"地震仪测试检波器");
	}
	else
	{
		arrayValues.SetAt(6,"测试仪测试检波器");
	}

	arrayValues.SetAt(7,pReader->GetItemValue (2002));
	arrayValues.SetAt(8 ,pReader->GetItemValue (11));
	arrayValues.SetAt(9 ,pReader->GetItemValue (2102));
	arrayValues.SetAt(10,pReader->GetItemValue (2103));
	arrayValues.SetAt(11,pReader->GetItemValue (2101));
	arrayValues.SetAt(12,pReader->GetItemValue (2102));
	arrayValues.SetAt(13,pReader->GetItemValue (2106));
	arrayValues.SetAt(14,pReader->GetItemValue (2104));
	arrayValues.SetAt(15,pReader->GetItemValue (2105));

	arrayValues.SetAt(16,"N");

	////////////////////////////////////////////
	//
	////////////////////////////////////////////
	CDataBaseManager db;
	CString sTable="表1011检波器测试情况资料";
	db.AddRecord (sTable,arrayFields,arrayValues);

	return true;
}

// 表1012检波器测试数据
bool CQCDBDataBrowseDoc::InputQCData1012(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=20&&iNo!=21)
	{
		AfxMessageBox("QC报告号码不对,应为20或者21,这个文件是:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (14);
	arrayFields.SetAt (0,"编号");
	arrayFields.SetAt (1,"本次测试编号");
	arrayFields.SetAt (2,"采集站号");
	arrayFields.SetAt (3,"线号");
	arrayFields.SetAt (4,"点号");

	arrayFields.SetAt (5,"自然频率");
	arrayFields.SetAt (6,"阻尼系数");
	arrayFields.SetAt (7,"谐波失真");
	arrayFields.SetAt (8 ,"灵敏度");
	arrayFields.SetAt (9 ,"直流电阻");
	arrayFields.SetAt (10,"极性");
	arrayFields.SetAt (11,"绝缘电阻");
	arrayFields.SetAt (12,"相位");
	
	arrayFields.SetAt (13,"已上传服务器");

	CStringArray arrayTypes;

	CString sTable="表1012检波器测试数据";
	GetFieldTypes(sTable,arrayFields,arrayTypes);

	CStringArray *pData=NULL;
	CStringArray arrayRecord;
	arrayRecord.SetSize (14);
	arrayRecord.SetAt (1 ,sTestNo);
	arrayRecord.SetAt (13,"N");

	CString s;

	if(!pReader->StartGetValue())
	{
		return false;
	}

	CQCDBDataBrowseDoc doc;
	CString sTempDBFile=GetTempFile();
	doc.CreateDBFile (sTempDBFile);
	doc.SetTableName (sTable);
	doc.SetField (arrayFields,arrayTypes);

	int n=0;
	if(iNo==20)
	{
		n=3;
	}

	if(iNo==21)
	{
		arrayRecord.SetAt (2,"  ");
		arrayRecord.SetAt (3,"  ");
		arrayRecord.SetAt (4,"  ");
	}

	while(true)
	{
		pData=pReader->GetValue (LT_DATA);
		if(!pData)break;
		if(pData->GetCount ()<(9+n))continue;

		arrayRecord.SetAt (0,GetUniID());
		if(iNo==20)
		{
			arrayRecord.SetAt (2,pData->GetAt (1)); // 
			arrayRecord.SetAt (3,pData->GetAt (2)); // 
			arrayRecord.SetAt (4,pData->GetAt (3)); //
		}
		arrayRecord.SetAt (5,pData->GetAt (1+n)); //
		arrayRecord.SetAt (6,pData->GetAt (2+n)); //
		arrayRecord.SetAt (7,pData->GetAt (3+n)); //
		arrayRecord.SetAt (8,pData->GetAt (4+n)); //
		arrayRecord.SetAt (9,pData->GetAt (5+n)); //
		arrayRecord.SetAt (10,pData->GetAt (6+n)); //
		arrayRecord.SetAt (11,pData->GetAt (7+n)); //
		arrayRecord.SetAt (12,pData->GetAt (8+n)); //

		doc.AppendRecord (&arrayRecord);
	}
	doc.Close ();

	////////////////////////////////////////////
	//
	////////////////////////////////////////////
	CDataBaseManager db;
	db.AddRecord (sTempDBFile);

	return true;
}

// 表1013检波器测试总结
bool CQCDBDataBrowseDoc::InputQCData1013(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=20&&iNo!=21)
	{
		AfxMessageBox("QC报告号码不对,应为20或者21,这个文件是:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (22);
	arrayFields.SetAt (0,"编号");
	arrayFields.SetAt (1,"项目编号");
	arrayFields.SetAt (2,"测线编号");
	arrayFields.SetAt (3,"测试年");
	arrayFields.SetAt (4,"测试月");
	arrayFields.SetAt (5,"测试日");

	arrayFields.SetAt (6,"起始检测线号");
	arrayFields.SetAt (7,"终止检测线号");
	arrayFields.SetAt (8,"起始检测点号");
	arrayFields.SetAt (9,"终止检测点号");
	arrayFields.SetAt (10,"测试检波器数量");
	arrayFields.SetAt (11,"正常检波器数量");
	arrayFields.SetAt (12,"在用检波器数量");

	arrayFields.SetAt (13,"自然频率失常数量");
	arrayFields.SetAt (14,"阻尼系数失常数量");
	arrayFields.SetAt (15,"谐波失真失常数量");


	arrayFields.SetAt (16,"灵敏度失常数量");
	arrayFields.SetAt (17,"直流电阻失常数量");
	arrayFields.SetAt (18,"极性失常数量");
	arrayFields.SetAt (19,"绝缘电阻失常数量");
	arrayFields.SetAt (20,"相位失常数量");

	arrayFields.SetAt (21,"已上传服务器");

	CMyDate date;
	date.Set (pReader->GetItemValue (8));
	CStringArray arrayValues;

	arrayValues.SetSize (22);
	arrayValues.SetAt(0,sTestNo);
	arrayValues.SetAt(1,sProjectNo);
	arrayValues.SetAt(2,::GetLineNo (sProjectNo,pReader->GetItemValue (6)));
	arrayValues.SetAt(3,vtos(date.GetYear ()));
	arrayValues.SetAt(4,vtos(date.GetMonth()));
	arrayValues.SetAt(5,vtos(date.GetDay()));

	arrayValues.SetAt(6,pReader->GetItemValue (2107));
	arrayValues.SetAt(7,pReader->GetItemValue (2108));
	arrayValues.SetAt(8 ,pReader->GetItemValue (2109));
	arrayValues.SetAt(9 ,pReader->GetItemValue (2110));
	arrayValues.SetAt(10,pReader->GetItemValue (2201));
	arrayValues.SetAt(11,pReader->GetItemValue (2202));
	arrayValues.SetAt(12,pReader->GetItemValue (2200));
	arrayValues.SetAt(13,pReader->GetItemValue (2300));
	arrayValues.SetAt(14,pReader->GetItemValue (2304));
	arrayValues.SetAt(15,pReader->GetItemValue (2306));
	arrayValues.SetAt(16,pReader->GetItemValue (2304));
	arrayValues.SetAt(17,pReader->GetItemValue (2306));
	arrayValues.SetAt(18,pReader->GetItemValue (2310));
	arrayValues.SetAt(19,pReader->GetItemValue (2314));
	arrayValues.SetAt(20,pReader->GetItemValue (2316));
	arrayValues.SetAt(21,"N");

	////////////////////////////////////////////
	//
	////////////////////////////////////////////
	CDataBaseManager db;
	CString sTable="表1013检波器测试总结";
	db.AddRecord (sTable,arrayFields,arrayValues);

	return true;
}

// 表1014井深总结
bool CQCDBDataBrowseDoc::InputQCData1014(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{

	int iNo=pReader->GetReportNo ();
	if(iNo!=40)
	{
		AfxMessageBox("QC报告号码不对,应为40,这个文件是:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (17);
	arrayFields.SetAt (0,"编号");
	arrayFields.SetAt (1,"项目编号");
	arrayFields.SetAt (2,"测线编号");
	arrayFields.SetAt (3,"测试年");
	arrayFields.SetAt (4,"测试月");
	arrayFields.SetAt (5,"测试日");

	arrayFields.SetAt (6,"检测总井数");
	arrayFields.SetAt (7,"监理方设计井数目");
	arrayFields.SetAt (8,"施工方设计井数目");
	arrayFields.SetAt (9,"实际井数目");
	arrayFields.SetAt (10,"高差限");
	arrayFields.SetAt (11,"低差限");
	arrayFields.SetAt (12,"比监理方深井数目");
	arrayFields.SetAt (13,"比监理方浅井数目");
	arrayFields.SetAt (14,"比施工方深井数目");
	arrayFields.SetAt (15,"比施工方浅井数目");

	arrayFields.SetAt (16,"已上传服务器");

	CMyDate date;
	date.Set (pReader->GetItemValue (8));
	CStringArray arrayValues;

	arrayValues.SetSize (17);
	arrayValues.SetAt(0,sTestNo);
	arrayValues.SetAt(1,sProjectNo);
	arrayValues.SetAt(2,::GetLineNo (sProjectNo,pReader->GetItemValue (6)));
	arrayValues.SetAt(3,vtos(date.GetYear ()));
	arrayValues.SetAt(4,vtos(date.GetMonth()));
	arrayValues.SetAt(5,vtos(date.GetDay()));

	arrayValues.SetAt(6,pReader->GetItemValue (4004));
	arrayValues.SetAt(7,pReader->GetItemValue (4000));
	arrayValues.SetAt(8 ,pReader->GetItemValue (4001));
	arrayValues.SetAt(9 ,pReader->GetItemValue (4002));
	arrayValues.SetAt(10,pReader->GetItemValue (4006));
	arrayValues.SetAt(11,pReader->GetItemValue (4005));
	arrayValues.SetAt(12,pReader->GetItemValue (4007));
	arrayValues.SetAt(13,pReader->GetItemValue (4008));
	arrayValues.SetAt(14,pReader->GetItemValue (4009));
	arrayValues.SetAt(15,pReader->GetItemValue (4010));
	arrayValues.SetAt(16,"N");

	////////////////////////////////////////////
	//
	////////////////////////////////////////////
	CDataBaseManager db;
	CString sTable="表1014井深总结";
	db.AddRecord (sTable,arrayFields,arrayValues);

	return true;
}


//  表1015井深资料 
bool CQCDBDataBrowseDoc::InputQCData1015(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=40)
	{
		AfxMessageBox("QC报告号码不对,应为40,这个文件是:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (12);
	arrayFields.SetAt (0,"编号");
	arrayFields.SetAt (1,"本次测试编号");
	arrayFields.SetAt (2,"线号");
	arrayFields.SetAt (3,"点号");
	arrayFields.SetAt (4,"南北坐标");
	arrayFields.SetAt (5,"东西坐标");
	arrayFields.SetAt (6,"监理方设计井深");
	arrayFields.SetAt (7 ,"施工方设计井深");
	arrayFields.SetAt (8 ,"实际井深");
	arrayFields.SetAt (9 ,"实际减监理方");
	arrayFields.SetAt (10,"实际减施工方");	
	arrayFields.SetAt (11,"已上传服务器");

	CStringArray arrayTypes;

	CString sTable="表1015井深资料";
	GetFieldTypes(sTable,arrayFields,arrayTypes);

	CStringArray *pData=NULL;
	CStringArray arrayRecord;
	arrayRecord.SetSize (12);
	arrayRecord.SetAt (1 ,sTestNo);
	arrayRecord.SetAt (11,"N");

	CString s;

	if(!pReader->StartGetValue())
	{
		return false;
	}

	CQCDBDataBrowseDoc doc;
	CString sTempDBFile=GetTempFile();
	doc.CreateDBFile (sTempDBFile);
	doc.SetTableName (sTable);
	doc.SetField (arrayFields,arrayTypes);

	while(true)
	{
		pData=pReader->GetValue (LT_DATA);
		if(!pData)break;
		if(pData->GetCount ()<10)continue;

		arrayRecord.SetAt (0,GetUniID());
		arrayRecord.SetAt (2,pData->GetAt (1 )); //
		arrayRecord.SetAt (3,pData->GetAt (2 )); //
		arrayRecord.SetAt (4,pData->GetAt (3 )); //
		arrayRecord.SetAt (5,pData->GetAt (4 )); //
		arrayRecord.SetAt (6 ,pData->GetAt (5 )); //
		arrayRecord.SetAt (7 ,pData->GetAt (6 )); //
		arrayRecord.SetAt (8 ,pData->GetAt (7 )); //
		arrayRecord.SetAt (9 ,pData->GetAt (8 )); //
		arrayRecord.SetAt (10,pData->GetAt (9 )); //
		doc.AppendRecord (&arrayRecord);
	}
	doc.Close ();

	////////////////////////////////////////////
	//
	////////////////////////////////////////////
	CDataBaseManager db;
	db.AddRecord (sTempDBFile);

	return true;
}

