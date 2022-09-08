
#include "stdafx.h"
#include "QCDB.h"
#include "QCDBDataBrowseDoc.h"
#include "fhcglobal.h"
#include "FHMainFrm.h"
#include "qcglobal.h"


// 表1001SPS检波点资料
bool CQCDBDataBrowseDoc::InputQCData1001(   CString	        sProjectNo,
									        CString	        sTestNo,
									        CReportReader   *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=60)
	{
		AfxMessageBox("QC报告号码不对,应为60,这个文件是:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (12);
	arrayFields.SetAt (0,"编号");
	arrayFields.SetAt (1,"项目编号");
	arrayFields.SetAt (2,"本次测试编号");
	arrayFields.SetAt (3,"线号");
	arrayFields.SetAt (4,"点号");
	arrayFields.SetAt (5,"是否偏离点");
	arrayFields.SetAt (6,"偏离方向");
	arrayFields.SetAt (7,"偏离距离");
	arrayFields.SetAt (8,"是否增加点");
	arrayFields.SetAt (9,"是否空点");
	arrayFields.SetAt (10,"是否炮点异常点");
	arrayFields.SetAt (11,"已上传服务器");

	CStringArray arrayTypes;

	CString sTable="表1001SPS检波点资料";
	GetFieldTypes(sTable,arrayFields,arrayTypes);

	CStringArray *pData=NULL;
	CStringArray arrayRecord;
	arrayRecord.SetSize (12);
	arrayRecord.SetAt (1,sProjectNo);
	arrayRecord.SetAt (2,sTestNo);
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
		pData=pReader->GetValue (LT_DATA|LT_RCV);
		if(!pData)break;
		arrayRecord.SetAt (0,GetUniID());
		arrayRecord.SetAt (3,pData->GetAt (1)); //线号
		arrayRecord.SetAt (4,pData->GetAt (2)); //点号

		// 是否偏离点
		s=pData->GetAt (3);
		if(s!="")
		{
			arrayRecord.SetAt (5,"Y"); 
		}
		else
		{
			arrayRecord.SetAt (5,"N"); 
		}

		// 偏离方向
		arrayRecord.SetAt (6,pData->GetAt (5)); 

		// 偏离距离
		arrayRecord.SetAt (7,pData->GetAt (4)); 

		// 是否增加点
		s=pData->GetAt (6);
		if(s!="")
		{
			arrayRecord.SetAt (8,"Y"); 
		}
		else
		{
			arrayRecord.SetAt (8,"N"); 
		}

		// 是否空点
		s=pData->GetAt (7);
		if(s!="")
		{
			arrayRecord.SetAt (9,"Y"); 
		}
		else
		{
			arrayRecord.SetAt (9,"N"); 
		}

		// 排列异常 点
		s=pData->GetAt (8);
		if(s!="")
		{
			arrayRecord.SetAt (10,"Y"); 
		}
		else
		{
			arrayRecord.SetAt (10,"N"); 
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

//表1002SPS检波点总结
bool CQCDBDataBrowseDoc::InputQCData1002(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=60)
	{
		AfxMessageBox("QC报告号码不对,应为60,这个文件是:"+vtos(iNo));
		return false;
	}



	CStringArray arrayFields,arrayValues;
	arrayFields.SetSize (24);
	arrayFields.SetAt (0,"编号");
	arrayFields.SetAt (1,"项目编号");
	arrayFields.SetAt (2,"测线编号");
	arrayFields.SetAt (3,"检测年");
	arrayFields.SetAt (4,"检测月");
	arrayFields.SetAt (5,"检测日");
	arrayFields.SetAt (6,"设计检波点数量");
	arrayFields.SetAt (7,"实际检波点数量");
	arrayFields.SetAt (8,"偏离点数量");
	arrayFields.SetAt (9 ,"增加点数量");
	arrayFields.SetAt (10,"空点数量");
	arrayFields.SetAt (11,"炮异常检波点数量");
	arrayFields.SetAt (12,"偏离距离门槛1");
	arrayFields.SetAt (13,"偏离距离门槛2");
	arrayFields.SetAt (14,"偏离距离门槛3");
	arrayFields.SetAt (15,"偏离距离门槛4");
	arrayFields.SetAt (16,"偏离距离门槛5");
	arrayFields.SetAt (17,"偏离距离门槛6");
	arrayFields.SetAt (18,"门槛1和2间点数量");
	arrayFields.SetAt (19,"门槛2和3间点数量");
	arrayFields.SetAt (20,"门槛3和4间点数量");
	arrayFields.SetAt (21,"门槛4和5间点数量");
	arrayFields.SetAt (22,"门槛5和6间点数量");
	arrayFields.SetAt (23,"已上传服务器");

	CMyDate date;
	date.Set (pReader->GetItemValue (8));

	arrayValues.SetSize (24);
	arrayValues.SetAt(0,sTestNo);
	arrayValues.SetAt(1,sProjectNo);
	arrayValues.SetAt(2,::GetLineNo (sProjectNo,pReader->GetItemValue (6)));
	arrayValues.SetAt(3,vtos(date.GetYear ()));
	arrayValues.SetAt(4,vtos(date.GetMonth()));
	arrayValues.SetAt(5,vtos(date.GetDay()));
	arrayValues.SetAt(6,pReader->GetItemValue (6024));
	arrayValues.SetAt(7,pReader->GetItemValue (6023));
	arrayValues.SetAt(8,pReader->GetItemValue (6027));
	arrayValues.SetAt(9 ,pReader->GetItemValue (6028));
	arrayValues.SetAt(10,pReader->GetItemValue (6029));
	arrayValues.SetAt(11,pReader->GetItemValue (6030));
	arrayValues.SetAt(12,pReader->GetItemValue (6009));
	arrayValues.SetAt(13,pReader->GetItemValue (6010));
	arrayValues.SetAt(14,pReader->GetItemValue (6011));
	arrayValues.SetAt(15,pReader->GetItemValue (6012));
	arrayValues.SetAt(16,pReader->GetItemValue (6013));
	arrayValues.SetAt(17,pReader->GetItemValue (6014));
	arrayValues.SetAt(18,pReader->GetItemValue (6015));
	arrayValues.SetAt(19,pReader->GetItemValue (6016));
	arrayValues.SetAt(20,pReader->GetItemValue (6017));
	arrayValues.SetAt(21,pReader->GetItemValue (6018));
	arrayValues.SetAt(22,pReader->GetItemValue (6019));
	arrayValues.SetAt(23,"N");

	////////////////////////////////////////////
	//
	////////////////////////////////////////////
	CDataBaseManager db;
	CString sTable="表1002SPS检波点总结";
	db.AddRecord (sTable,arrayFields,arrayValues);

	return true;
}

// 表1003SPS炮点资料
bool CQCDBDataBrowseDoc::InputQCData1003(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=60)
	{
		AfxMessageBox("QC报告号码不对,应为60,这个文件是:"+vtos(iNo));
		return false;
	}


	CStringArray arrayFields;
	arrayFields.SetSize (12);
	arrayFields.SetAt (0,"编号");
	arrayFields.SetAt (1,"项目编号");
	arrayFields.SetAt (2,"本次测试编号");
	arrayFields.SetAt (3,"线号");
	arrayFields.SetAt (4,"点号");
	arrayFields.SetAt (5,"是否偏离点");
	arrayFields.SetAt (6,"偏离方向");
	arrayFields.SetAt (7,"偏离距离");
	arrayFields.SetAt (8,"是否增加点");
	arrayFields.SetAt (9,"是否空点");
	arrayFields.SetAt (10,"是否排列异常点");
	arrayFields.SetAt (11,"已上传服务器");


	CStringArray arrayTypes;

	CString sTable="表1003SPS炮点资料";
	GetFieldTypes(sTable,arrayFields,arrayTypes);

	CStringArray *pData=NULL;
	CStringArray arrayRecord;
	arrayRecord.SetSize (12);
	arrayRecord.SetAt (1,sProjectNo);
	arrayRecord.SetAt (2,sTestNo);
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
		pData=pReader->GetValue (LT_DATA|LT_SHOT);
		if(!pData)break;
		arrayRecord.SetAt (0,GetUniID());
		arrayRecord.SetAt (3,pData->GetAt (1)); //线号
		arrayRecord.SetAt (4,pData->GetAt (2)); //点号

		// 是否偏离点
		s=pData->GetAt (3);
		if(s!="")
		{
			arrayRecord.SetAt (5,"Y"); 
		}
		else
		{
			arrayRecord.SetAt (5,"N"); 
		}

		// 偏离方向
		arrayRecord.SetAt (6,pData->GetAt (5)); 

		// 偏离距离
		arrayRecord.SetAt (7,pData->GetAt (4)); 

		// 是否增加点
		s=pData->GetAt (6);
		if(s!="")
		{
			arrayRecord.SetAt (8,"Y"); 
		}
		else
		{
			arrayRecord.SetAt (8,"N"); 
		}

		// 是否空点
		s=pData->GetAt (7);
		if(s!="")
		{
			arrayRecord.SetAt (9,"Y"); 
		}
		else
		{
			arrayRecord.SetAt (9,"N"); 
		}

		// 排列异常 点
		s=pData->GetAt (8);
		if(s!="")
		{
			arrayRecord.SetAt (10,"Y"); 
		}
		else
		{
			arrayRecord.SetAt (10,"N"); 
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

//表1004SPS炮点总结
bool CQCDBDataBrowseDoc::InputQCData1004(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=60)
	{
		AfxMessageBox("QC报告号码不对,应为60,这个文件是:"+vtos(iNo));
		return false;
	}



	CStringArray arrayFields,arrayValues;
	arrayFields.SetSize (24);
	arrayFields.SetAt (0,"编号");
	arrayFields.SetAt (1,"项目编号");
	arrayFields.SetAt (2,"测线编号");
	arrayFields.SetAt (3,"检测年");
	arrayFields.SetAt (4,"检测月");
	arrayFields.SetAt (5,"检测日");
	arrayFields.SetAt (6,"设计炮点数量");
	arrayFields.SetAt (7,"实际炮点数量");
	arrayFields.SetAt (8,"偏离点数量");
	arrayFields.SetAt (9 ,"增加点数量");
	arrayFields.SetAt (10,"空点数量");
	arrayFields.SetAt (11,"排列异常炮点数量");
	arrayFields.SetAt (12,"偏离距离门槛1");
	arrayFields.SetAt (13,"偏离距离门槛2");
	arrayFields.SetAt (14,"偏离距离门槛3");
	arrayFields.SetAt (15,"偏离距离门槛4");
	arrayFields.SetAt (16,"偏离距离门槛5");
	arrayFields.SetAt (17,"偏离距离门槛6");
	arrayFields.SetAt (18,"门槛1和2间点数量");
	arrayFields.SetAt (19,"门槛2和3间点数量");
	arrayFields.SetAt (20,"门槛3和4间点数量");
	arrayFields.SetAt (21,"门槛4和5间点数量");
	arrayFields.SetAt (22,"门槛5和6间点数量");
	arrayFields.SetAt (23,"已上传服务器");

	CMyDate date;
	date.Set (pReader->GetItemValue (8));

	arrayValues.SetSize (24);
	arrayValues.SetAt(0,sTestNo);
	arrayValues.SetAt(1,sProjectNo);
	arrayValues.SetAt(2,::GetLineNo (sProjectNo,pReader->GetItemValue (6)));
	arrayValues.SetAt(3,vtos(date.GetYear ()));
	arrayValues.SetAt(4,vtos(date.GetMonth()));
	arrayValues.SetAt(5,vtos(date.GetDay()));
	arrayValues.SetAt(6,pReader->GetItemValue (6001));
	arrayValues.SetAt(7,pReader->GetItemValue (6000));
	arrayValues.SetAt(8,pReader->GetItemValue (6008));
	arrayValues.SetAt(9 ,pReader->GetItemValue (6020));
	arrayValues.SetAt(10,pReader->GetItemValue (6021));
	arrayValues.SetAt(11,pReader->GetItemValue (6022));
	arrayValues.SetAt(12,pReader->GetItemValue (6009));
	arrayValues.SetAt(13,pReader->GetItemValue (6010));
	arrayValues.SetAt(14,pReader->GetItemValue (6011));
	arrayValues.SetAt(15,pReader->GetItemValue (6012));
	arrayValues.SetAt(16,pReader->GetItemValue (6013));
	arrayValues.SetAt(17,pReader->GetItemValue (6014));
	arrayValues.SetAt(18,pReader->GetItemValue (6015));
	arrayValues.SetAt(19,pReader->GetItemValue (6016));
	arrayValues.SetAt(20,pReader->GetItemValue (6017));
	arrayValues.SetAt(21,pReader->GetItemValue (6018));
	arrayValues.SetAt(22,pReader->GetItemValue (6019));
	arrayValues.SetAt(23,"N");

	////////////////////////////////////////////
	//
	////////////////////////////////////////////
	CDataBaseManager db;
	CString sTable="表1004SPS炮点总结";
	db.AddRecord (sTable,arrayFields,arrayValues);

	return true;
}

// 表1005炮点资料
bool CQCDBDataBrowseDoc::InputQCData1005(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=12)
	{
		AfxMessageBox("QC报告号码不对,应为12,这个文件是:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (13);
	arrayFields.SetAt (0,"编号");
	arrayFields.SetAt (1,"项目编号");
	arrayFields.SetAt (2,"本次测试编号");
	arrayFields.SetAt (3,"线号");
	arrayFields.SetAt (4,"点号");
	arrayFields.SetAt (5,"文件号");
	arrayFields.SetAt (6,"南北坐标");
	arrayFields.SetAt (7,"东西坐标");
	arrayFields.SetAt (8,"井深");
	arrayFields.SetAt (9,"激发量");
	arrayFields.SetAt (10 ,"激发单位");
	arrayFields.SetAt (11,"海拔高程");
	arrayFields.SetAt (12,"已上传服务器");


	CStringArray arrayTypes;

	CString sTable="表1005炮点资料";
	GetFieldTypes(sTable,arrayFields,arrayTypes);

	CStringArray *pData=NULL;
	CStringArray arrayRecord;
	arrayRecord.SetSize (13);
	arrayRecord.SetAt (1,sProjectNo);
	arrayRecord.SetAt (2,sTestNo);
	arrayRecord.SetAt (12,"N");

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
		pData=pReader->GetValue (LT_DATA|LT_SHOT);
		if(!pData)break;
		if(pData->GetCount ()<10)continue;

		arrayRecord.SetAt (0,GetUniID());
		arrayRecord.SetAt (3,pData->GetAt (1)); //线号
		arrayRecord.SetAt (4,pData->GetAt (2)); //点号
		arrayRecord.SetAt (5,pData->GetAt (3)); //
		arrayRecord.SetAt (6,pData->GetAt (4)); //
		arrayRecord.SetAt (7,pData->GetAt (5)); //
		arrayRecord.SetAt (8,pData->GetAt (6)); //
		arrayRecord.SetAt (9,pData->GetAt (7)); //
		arrayRecord.SetAt (10,pData->GetAt (8)); //
		arrayRecord.SetAt (11,pData->GetAt (9)); //


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