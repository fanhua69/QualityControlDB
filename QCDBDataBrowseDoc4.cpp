
#include "stdafx.h"
#include "QCDB.h"
#include "QCDBDataBrowseDoc.h"
#include "fhcglobal.h"
#include "FHMainFrm.h"
#include "qcglobal.h"

// 表1016药量总结
bool CQCDBDataBrowseDoc::InputQCData1016(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{

	int iNo=pReader->GetReportNo ();
	if(iNo!=41)
	{
		AfxMessageBox("QC报告号码不对,应为41,这个文件是:"+vtos(iNo));
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
	arrayFields.SetAt (12,"比施工方设计少药量井数");
	arrayFields.SetAt (13,"比施工方设计多药量井数");
	arrayFields.SetAt (14,"比监理方设计少药量井数");
	arrayFields.SetAt (15,"比监理方设计多药量井数");

	arrayFields.SetAt (16,"已上传服务器");

	CMyDate date;
	date.Set(pReader->GetItemValue (8));
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
	arrayValues.SetAt(12,pReader->GetItemValue (4104));
	arrayValues.SetAt(13,pReader->GetItemValue (4105));
	arrayValues.SetAt(14,pReader->GetItemValue (4106));
	arrayValues.SetAt(15,pReader->GetItemValue (4107));
	arrayValues.SetAt(16,"N");

	////////////////////////////////////////////
	//
	////////////////////////////////////////////
	CDataBaseManager db;
	CString sTable="表1016药量总结";
	db.AddRecord (sTable,arrayFields,arrayValues);

	return true;
}

// 表1017药量资料
bool CQCDBDataBrowseDoc::InputQCData1017(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=41)
	{
		AfxMessageBox("QC报告号码不对,应为41,这个文件是:"+vtos(iNo));
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
	arrayFields.SetAt (6,"监理方设计药量");
	arrayFields.SetAt (7 ,"施工方设计药量");
	arrayFields.SetAt (8 ,"实际药量");
	arrayFields.SetAt (9 ,"实际减监理方");
	arrayFields.SetAt (10,"实际减施工方");	
	arrayFields.SetAt (11,"已上传服务器");

	CStringArray arrayTypes;

	CString sTable="表1017药量资料";
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



// 表1018年月日检标准
bool CQCDBDataBrowseDoc::InputQCData1018(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();

	if(iNo!=50)
	{
		AfxMessageBox("QC报告号码不对,应为50,这个文件是:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (17);
	arrayFields.SetAt (0,"编号");
	arrayFields.SetAt (1,"本次测试编号");
	arrayFields.SetAt (2,"检测项目代码");
	arrayFields.SetAt (3,"检测项目名称");
	arrayFields.SetAt (4,"单位");
	arrayFields.SetAt (5,"K增益");
	arrayFields.SetAt (6,"前放增益");
	arrayFields.SetAt (7 ,"信号衰减");
	arrayFields.SetAt (8 ,"有无电缆");
	arrayFields.SetAt (9 ,"采样率");
	arrayFields.SetAt (10,"FDU/GEO");	
	arrayFields.SetAt (11,"评价方式");	
	arrayFields.SetAt (12,"默认标准值");	
	arrayFields.SetAt (13,"标准值");	
	arrayFields.SetAt (14,"误差限");	
	arrayFields.SetAt (15,"参与分析");
	arrayFields.SetAt (16,"已上传服务器");

	CStringArray arrayTypes;

	CString sTable="表1018年月日检标准";
	GetFieldTypes(sTable,arrayFields,arrayTypes);

	CStringArray *pData=NULL;
	CStringArray arrayRecord;
	arrayRecord.SetSize (17);
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
		pData=pReader->GetValue (LT_DATA|LT_PROPERTY);
		if(!pData)break;
		if(pData->GetCount ()<15)continue;

		arrayRecord.SetAt (0,GetUniID());
		arrayRecord.SetAt (2,pData->GetAt (0 )); //
		arrayRecord.SetAt (3,pData->GetAt (1 )); //
		arrayRecord.SetAt (4,pData->GetAt (2 )); //
		arrayRecord.SetAt (5,pData->GetAt (3 )); //
		arrayRecord.SetAt (6 ,pData->GetAt (4 )); //
		arrayRecord.SetAt (7 ,pData->GetAt (5 )); //
		arrayRecord.SetAt (8 ,pData->GetAt (6 )); //
		arrayRecord.SetAt (9 ,pData->GetAt (7 )); //
		arrayRecord.SetAt (10,pData->GetAt (8 )); //
		arrayRecord.SetAt (11,pData->GetAt (9 )); //
		arrayRecord.SetAt (12,pData->GetAt (10)); //
		arrayRecord.SetAt (13,pData->GetAt (11)); //
		arrayRecord.SetAt (14,pData->GetAt (12)); //
		arrayRecord.SetAt (15,pData->GetAt (13)); //
		arrayRecord.SetAt (16,pData->GetAt (14)); //


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


// 表1019年月日检资料
bool CQCDBDataBrowseDoc::InputQCData1019(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=50)
	{
		AfxMessageBox("QC报告号码不对,应为50,这个文件是:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (40);
	arrayFields.SetAt (0,"编号");
	arrayFields.SetAt (1,"本次测试编号");
	arrayFields.SetAt (2,"AA");
	arrayFields.SetAt (3,"AB");
	arrayFields.SetAt (4,"AC");
	arrayFields.SetAt (5,"AD");
	arrayFields.SetAt (6,"AE");
	arrayFields.SetAt (7,"AF");
	arrayFields.SetAt (8,"AG");
	arrayFields.SetAt (9,"AH");
	arrayFields.SetAt (10,"AI");
	arrayFields.SetAt (11,"AJ");
	arrayFields.SetAt (12,"AK");
	arrayFields.SetAt (13,"AL");
	arrayFields.SetAt (14,"AM");
	arrayFields.SetAt (15,"AN");
	arrayFields.SetAt (16,"AO");
	arrayFields.SetAt (17,"AP");
	arrayFields.SetAt (18,"AQ");
	arrayFields.SetAt (19,"AR");
	arrayFields.SetAt (20,"AS");
	arrayFields.SetAt (21,"AT");
	arrayFields.SetAt (22,"AU");
	arrayFields.SetAt (23,"AV");
	arrayFields.SetAt (24,"AW");
	arrayFields.SetAt (25,"AX");
	arrayFields.SetAt (26,"AY");
	arrayFields.SetAt (27,"AZ");
	arrayFields.SetAt (28,"BA");
	arrayFields.SetAt (29,"BB");
	arrayFields.SetAt (30,"BC");
	arrayFields.SetAt (31,"BD");
	arrayFields.SetAt (32,"BE");
	arrayFields.SetAt (33,"BF");
	arrayFields.SetAt (34,"BG");
	arrayFields.SetAt (35,"BH");
	arrayFields.SetAt (36,"BI");
	arrayFields.SetAt (37,"BJ");
	arrayFields.SetAt (38,"BK");
	arrayFields.SetAt (39,"已上传服务器");

	CStringArray arrayTypes;

	CString sTable="表1019年月日检资料";
	GetFieldTypes(sTable,arrayFields,arrayTypes);

	CStringArray *pData=NULL;
	CStringArray arrayRecord;
	arrayRecord.SetSize (40);
	arrayRecord.SetAt (1,sTestNo);
	arrayRecord.SetAt (39,"N");

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

	int i=0;
	int iDataQty=37;


	while(true)
	{
		pData=pReader->GetValue (LT_DATA|LT_BOX);
		if(!pData)break;

		
		arrayRecord.SetAt (0,GetUniID());

		iDataQty=37;
		if(pData->GetCount ()<iDataQty)
		{
			iDataQty=pData->GetCount ();
		}
		for(i=0;i<iDataQty;i++)
		{
			arrayRecord.SetAt (i+2,pData->GetAt (i)); //
		}
		for(i=iDataQty;i<37;i++)
		{
			arrayRecord.SetAt (i+2,""); //
		}

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


// 表1020年月日检总结
bool CQCDBDataBrowseDoc::InputQCData1020(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=50)
	{
		AfxMessageBox("QC报告号码不对,应为50,这个文件是:"+vtos(iNo));
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
	arrayFields.SetAt (6,"地震仪型号");
	arrayFields.SetAt (7,"检测类型");
	arrayFields.SetAt (8 ,"采样率");
	arrayFields.SetAt (9 ,"应检测项目");
	arrayFields.SetAt (10,"实检测项目");
	arrayFields.SetAt (11,"检测采集站数量");
	arrayFields.SetAt (12,"采集站最小编号");
	arrayFields.SetAt (13,"采集站最大编号");
	arrayFields.SetAt (14,"在用采集站数量");
	arrayFields.SetAt (15,"未检测采集站编号");
	arrayFields.SetAt (16,"非在用采集站数量");
	arrayFields.SetAt (17,"非在用采集站编号");
	arrayFields.SetAt (18,"采集站通过数量");
	arrayFields.SetAt (19,"测试检波器数量");
	arrayFields.SetAt (20,"合格检波器数量");
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

	arrayValues.SetAt(6,pReader->GetItemValue (11));
	arrayValues.SetAt(7,pReader->GetItemValue (5000));
	arrayValues.SetAt(8 ,pReader->GetItemValue (5001));
	arrayValues.SetAt(9 ,pReader->GetItemValue (5002));
	arrayValues.SetAt(10,pReader->GetItemValue (5003));
	arrayValues.SetAt(11,pReader->GetItemValue (5004));
	arrayValues.SetAt(12,pReader->GetItemValue (5005));
	arrayValues.SetAt(13,pReader->GetItemValue (5006));
	arrayValues.SetAt(14,pReader->GetItemValue (5007));

	CString s=pReader->GetManyItemValue (5009);
	s.Remove (' ');
	if(s.GetLength ()>=255)
	{
		s=s.Left (254);
	}
	arrayValues.SetAt(15,s);
	arrayValues.SetAt(16,pReader->GetItemValue (5010));

	s=pReader->GetManyItemValue (5011);
	s.Remove (' ');
	if(s.GetLength ()>=255)
	{
		s=s.Left (254);
	}
	arrayValues.SetAt(17,s);
	arrayValues.SetAt(18,pReader->GetItemValue (5015));

	// Geophones:
	arrayValues.SetAt(19,pReader->GetItemValue (5014));
	arrayValues.SetAt(20,pReader->GetItemValue (5016));

	arrayValues.SetAt(21,"N");

	////////////////////////////////////////////
	//
	////////////////////////////////////////////
	CDataBaseManager db;
	CString sTable="表1020年月日检总结";
	db.AddRecord (sTable,arrayFields,arrayValues);

	return true;
}
