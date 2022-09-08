
#include "stdafx.h"
#include "QCDB.h"
#include "QCDBDataBrowseDoc.h"
#include "fhcglobal.h"
#include "FHMainFrm.h"
#include "qcglobal.h"

// 表1006单炮分频能量资料
bool CQCDBDataBrowseDoc::InputQCData1006(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=10)
	{
		AfxMessageBox("QC报告号码不对,应为10,这个文件是:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (8);
	arrayFields.SetAt (0,"编号");
	arrayFields.SetAt (1,"本次测试编号");
	arrayFields.SetAt (2,"炮点文件号");
	arrayFields.SetAt (3,"起始频率");
	arrayFields.SetAt (4,"终止频率");
	arrayFields.SetAt (5,"参考炮能量");
	arrayFields.SetAt (6,"比较炮能量");
	arrayFields.SetAt (7,"已上传服务器");


	CStringArray arrayTypes;

	CString sTable="表1006单炮分频能量资料";
	GetFieldTypes(sTable,arrayFields,arrayTypes);

	CStringArray *pData=NULL;
	CStringArray arrayRecord;
	arrayRecord.SetSize (8);
	arrayRecord.SetAt (1,sTestNo);
	arrayRecord.SetAt (7,"N");

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
		if(pData->GetCount ()<7)continue;

		arrayRecord.SetAt (0,GetUniID());
		arrayRecord.SetAt (2,pData->GetAt (0)); // 
		arrayRecord.SetAt (3,pData->GetAt (3)); // 
		arrayRecord.SetAt (4,pData->GetAt (4)); //
		arrayRecord.SetAt (5,pData->GetAt (6)); //
		arrayRecord.SetAt (6,pData->GetAt (5)); //

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

//////////////////////////////////////////////////////
//          表1007单炮分频能量总结
///////////////////////////////////////////////////////////
bool CQCDBDataBrowseDoc::InputQCData1007(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=10)
	{
		AfxMessageBox("QC报告号码不对,应为10,这个文件是:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (15);
	arrayFields.SetAt (0,"编号");
	arrayFields.SetAt (1,"项目编号");
	arrayFields.SetAt (2,"测线编号");
	arrayFields.SetAt (3,"测试年");
	arrayFields.SetAt (4,"测试月");
	arrayFields.SetAt (5,"测试日");
	arrayFields.SetAt (6,"最小监控文件号");
	arrayFields.SetAt (7,"最大监控文件号");
	arrayFields.SetAt (8,"最小监控站号");
	arrayFields.SetAt (9,"最大监控站号");
	arrayFields.SetAt (10,"低门槛值");
	arrayFields.SetAt (11 ,"高门槛值");
	arrayFields.SetAt (12,"监控总炮数");
	arrayFields.SetAt (13,"能量低炮数");
	arrayFields.SetAt (14,"已上传服务器");


	CMyDate date;
	date.Set (pReader->GetItemValue (8));
	CStringArray arrayValues;

	arrayValues.SetSize (15);
	arrayValues.SetAt(0,sTestNo);
	arrayValues.SetAt(1,sProjectNo);
	arrayValues.SetAt(2,::GetLineNo (sProjectNo,pReader->GetItemValue (6)));
	arrayValues.SetAt(3,vtos(date.GetYear ()));
	arrayValues.SetAt(4,vtos(date.GetMonth()));
	arrayValues.SetAt(5,vtos(date.GetDay()));

	arrayValues.SetAt(6,pReader->GetItemValue (1000));
	arrayValues.SetAt(7,pReader->GetItemValue (1001));
	arrayValues.SetAt(8,pReader->GetItemValue (1002));
	arrayValues.SetAt(9 ,pReader->GetItemValue (1003));
	arrayValues.SetAt(10,pReader->GetItemValue (1006));
	arrayValues.SetAt(11,pReader->GetItemValue (1007));
	arrayValues.SetAt(12,pReader->GetItemValue (1005));
	arrayValues.SetAt(13,pReader->GetItemValue (1008));
	arrayValues.SetAt(14,"N");

	////////////////////////////////////////////
	//
	////////////////////////////////////////////
	CDataBaseManager db;
	CString sTable="表1007单炮分频能量总结";
	db.AddRecord (sTable,arrayFields,arrayValues);

	return true;
}

// 表1008单炮整体能量资料
bool CQCDBDataBrowseDoc::InputQCData1008(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=11)
	{
		AfxMessageBox("QC报告号码不对,应为11,这个文件是:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (12);
	arrayFields.SetAt (0,"编号");
	arrayFields.SetAt (1,"本次测试编号");
	arrayFields.SetAt (2,"炮点文件号");
	arrayFields.SetAt (3,"参考炮能量");
	arrayFields.SetAt (4,"比较炮能量");
	arrayFields.SetAt (5,"参考炮信噪比");
	arrayFields.SetAt (6,"比较炮信噪比");
	arrayFields.SetAt (7,"参考炮主频");
	arrayFields.SetAt (8,"比较炮主频");
	arrayFields.SetAt (9,"参考炮频宽");
	arrayFields.SetAt (10,"比较炮频宽");
	arrayFields.SetAt (11,"已上传服务器");


	CStringArray arrayTypes;

	CString sTable="表1008单炮整体能量资料";
	GetFieldTypes(sTable,arrayFields,arrayTypes);

	CStringArray *pData=NULL;
	CStringArray arrayRecord;
	arrayRecord.SetSize (12);
	arrayRecord.SetAt (1,sTestNo);
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
		if(pData->GetCount ()<14)continue;

		arrayRecord.SetAt (0,GetUniID());
		arrayRecord.SetAt (2,pData->GetAt (3)); // 
		arrayRecord.SetAt (3,pData->GetAt (4)); // 
		arrayRecord.SetAt (4,pData->GetAt (5)); //
		arrayRecord.SetAt (5,pData->GetAt (7)); //
		arrayRecord.SetAt (6,pData->GetAt (8)); //
		arrayRecord.SetAt (7,pData->GetAt (10)); //
		arrayRecord.SetAt (8,pData->GetAt (11)); //
		arrayRecord.SetAt (9,pData->GetAt (12)); //
		arrayRecord.SetAt (10,pData->GetAt (13)); //

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

// 表1009单炮整体能量总结
bool CQCDBDataBrowseDoc::InputQCData1009(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=11)
	{
		AfxMessageBox("QC报告号码不对,应为11:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (15);
	arrayFields.SetAt (0,"编号");
	arrayFields.SetAt (1,"项目编号");
	arrayFields.SetAt (2,"测线编号");
	arrayFields.SetAt (3,"测试年");
	arrayFields.SetAt (4,"测试月");
	arrayFields.SetAt (5,"测试日");
	arrayFields.SetAt (6,"最小监控文件号");
	arrayFields.SetAt (7,"最大监控文件号");
	arrayFields.SetAt (8,"最小监控点号");
	arrayFields.SetAt (9,"最大监控点号");
	arrayFields.SetAt (10,"监控总炮数");
	arrayFields.SetAt (11,"能量低门槛值");
	arrayFields.SetAt (12,"能量高门槛值");
	arrayFields.SetAt (13,"超限炮点数目");
	arrayFields.SetAt (14,"已上传服务器");


	CMyDate date;
	date.Set (pReader->GetItemValue (8));
	CStringArray arrayValues;

	arrayValues.SetSize (15);
	arrayValues.SetAt(0,sTestNo);
	arrayValues.SetAt(1,sProjectNo);
	arrayValues.SetAt(2,::GetLineNo (sProjectNo,pReader->GetItemValue (6)));
	arrayValues.SetAt(3,vtos(date.GetYear ()));
	arrayValues.SetAt(4,vtos(date.GetMonth()));
	arrayValues.SetAt(5,vtos(date.GetDay()));

	arrayValues.SetAt(6,pReader->GetItemValue (1000));
	arrayValues.SetAt(7,pReader->GetItemValue (1001));
	arrayValues.SetAt(8,pReader->GetItemValue (1002));
	arrayValues.SetAt(9 ,pReader->GetItemValue (1003));
	arrayValues.SetAt(10,pReader->GetItemValue (1005));
	arrayValues.SetAt(11,pReader->GetItemValue (1006));
	arrayValues.SetAt(12,pReader->GetItemValue (1007));
	arrayValues.SetAt(13,pReader->GetItemValue (1008));
	arrayValues.SetAt(14,"N");

	////////////////////////////////////////////
	//
	////////////////////////////////////////////
	CDataBaseManager db;
	CString sTable="表1009单炮整体能量总结";
	db.AddRecord (sTable,arrayFields,arrayValues);

	return true;
}


// 表1010检波器测试标准
bool CQCDBDataBrowseDoc::InputQCData1010(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=22)
	{
		AfxMessageBox("QC报告号码不对,应为22:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (17);
	arrayFields.SetAt (0,"编号");
	arrayFields.SetAt (1,"检波器型号");
	arrayFields.SetAt (2,"自然频率标准值(Hz)");
	arrayFields.SetAt (3,"自然频率误差限%");
	arrayFields.SetAt (4,"阻尼系数标准值");
	arrayFields.SetAt (5,"阻尼系数误差限%");
	arrayFields.SetAt (6,"灵敏度标准值(V/m/s)");
	arrayFields.SetAt (7,"灵敏度误差限%");
	arrayFields.SetAt (8,"直流电阻(ohm)");
	arrayFields.SetAt (9,"直流电阻误差限%");
	arrayFields.SetAt (10,"失真度(<%)");
	arrayFields.SetAt (11,"极性标准值");
	arrayFields.SetAt (12,"绝缘电阻标准值(ohm)");
	arrayFields.SetAt (13,"绝缘电阻误差限%");
	arrayFields.SetAt (14,"相位标准值(度)");
	arrayFields.SetAt (15,"相位误差限%");
	arrayFields.SetAt (16,"已上传服务器");


	CStringArray arrayTypes;

	CString sTable="表1010检波器测试标准";
	GetFieldTypes(sTable,arrayFields,arrayTypes);

	CStringArray *pData=NULL;
	CStringArray arrayRecord;
	arrayRecord.SetSize (17);
	arrayRecord.SetAt (16,"N");

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
		if(pData->GetCount ()<16)continue;

		arrayRecord.SetAt (0,GetUniID());
		arrayRecord.SetAt (1,pData->GetAt (1)); // 
		arrayRecord.SetAt (2,pData->GetAt (2)); // 
		arrayRecord.SetAt (3,pData->GetAt (3)); // 
		arrayRecord.SetAt (4,pData->GetAt (4)); //
		arrayRecord.SetAt (5,pData->GetAt (5)); //
		arrayRecord.SetAt (6,pData->GetAt (6)); //
		arrayRecord.SetAt (7,pData->GetAt (7)); //
		arrayRecord.SetAt (8,pData->GetAt (8)); //
		arrayRecord.SetAt (9,pData->GetAt (9)); //
		arrayRecord.SetAt (10,pData->GetAt (10)); //
		arrayRecord.SetAt (11,pData->GetAt (11)); //
		arrayRecord.SetAt (12,pData->GetAt (12)); //
		arrayRecord.SetAt (13,pData->GetAt (13)); //
		arrayRecord.SetAt (14,pData->GetAt (14)); //
		arrayRecord.SetAt (15,pData->GetAt (15)); //
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