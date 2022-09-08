
#include "stdafx.h"
#include "QCDB.h"
#include "QCDBDataBrowseDoc.h"
#include "fhcglobal.h"
#include "FHMainFrm.h"
#include "qcglobal.h"

// ��1006���ڷ�Ƶ��������
bool CQCDBDataBrowseDoc::InputQCData1006(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=10)
	{
		AfxMessageBox("QC������벻��,ӦΪ10,����ļ���:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (8);
	arrayFields.SetAt (0,"���");
	arrayFields.SetAt (1,"���β��Ա��");
	arrayFields.SetAt (2,"�ڵ��ļ���");
	arrayFields.SetAt (3,"��ʼƵ��");
	arrayFields.SetAt (4,"��ֹƵ��");
	arrayFields.SetAt (5,"�ο�������");
	arrayFields.SetAt (6,"�Ƚ�������");
	arrayFields.SetAt (7,"���ϴ�������");


	CStringArray arrayTypes;

	CString sTable="��1006���ڷ�Ƶ��������";
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
//          ��1007���ڷ�Ƶ�����ܽ�
///////////////////////////////////////////////////////////
bool CQCDBDataBrowseDoc::InputQCData1007(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=10)
	{
		AfxMessageBox("QC������벻��,ӦΪ10,����ļ���:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (15);
	arrayFields.SetAt (0,"���");
	arrayFields.SetAt (1,"��Ŀ���");
	arrayFields.SetAt (2,"���߱��");
	arrayFields.SetAt (3,"������");
	arrayFields.SetAt (4,"������");
	arrayFields.SetAt (5,"������");
	arrayFields.SetAt (6,"��С����ļ���");
	arrayFields.SetAt (7,"������ļ���");
	arrayFields.SetAt (8,"��С���վ��");
	arrayFields.SetAt (9,"�����վ��");
	arrayFields.SetAt (10,"���ż�ֵ");
	arrayFields.SetAt (11 ,"���ż�ֵ");
	arrayFields.SetAt (12,"���������");
	arrayFields.SetAt (13,"����������");
	arrayFields.SetAt (14,"���ϴ�������");


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
	CString sTable="��1007���ڷ�Ƶ�����ܽ�";
	db.AddRecord (sTable,arrayFields,arrayValues);

	return true;
}

// ��1008����������������
bool CQCDBDataBrowseDoc::InputQCData1008(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=11)
	{
		AfxMessageBox("QC������벻��,ӦΪ11,����ļ���:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (12);
	arrayFields.SetAt (0,"���");
	arrayFields.SetAt (1,"���β��Ա��");
	arrayFields.SetAt (2,"�ڵ��ļ���");
	arrayFields.SetAt (3,"�ο�������");
	arrayFields.SetAt (4,"�Ƚ�������");
	arrayFields.SetAt (5,"�ο��������");
	arrayFields.SetAt (6,"�Ƚ��������");
	arrayFields.SetAt (7,"�ο�����Ƶ");
	arrayFields.SetAt (8,"�Ƚ�����Ƶ");
	arrayFields.SetAt (9,"�ο���Ƶ��");
	arrayFields.SetAt (10,"�Ƚ���Ƶ��");
	arrayFields.SetAt (11,"���ϴ�������");


	CStringArray arrayTypes;

	CString sTable="��1008����������������";
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

// ��1009�������������ܽ�
bool CQCDBDataBrowseDoc::InputQCData1009(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=11)
	{
		AfxMessageBox("QC������벻��,ӦΪ11:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (15);
	arrayFields.SetAt (0,"���");
	arrayFields.SetAt (1,"��Ŀ���");
	arrayFields.SetAt (2,"���߱��");
	arrayFields.SetAt (3,"������");
	arrayFields.SetAt (4,"������");
	arrayFields.SetAt (5,"������");
	arrayFields.SetAt (6,"��С����ļ���");
	arrayFields.SetAt (7,"������ļ���");
	arrayFields.SetAt (8,"��С��ص��");
	arrayFields.SetAt (9,"����ص��");
	arrayFields.SetAt (10,"���������");
	arrayFields.SetAt (11,"�������ż�ֵ");
	arrayFields.SetAt (12,"�������ż�ֵ");
	arrayFields.SetAt (13,"�����ڵ���Ŀ");
	arrayFields.SetAt (14,"���ϴ�������");


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
	CString sTable="��1009�������������ܽ�";
	db.AddRecord (sTable,arrayFields,arrayValues);

	return true;
}


// ��1010�첨�����Ա�׼
bool CQCDBDataBrowseDoc::InputQCData1010(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=22)
	{
		AfxMessageBox("QC������벻��,ӦΪ22:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (17);
	arrayFields.SetAt (0,"���");
	arrayFields.SetAt (1,"�첨���ͺ�");
	arrayFields.SetAt (2,"��ȻƵ�ʱ�׼ֵ(Hz)");
	arrayFields.SetAt (3,"��ȻƵ�������%");
	arrayFields.SetAt (4,"����ϵ����׼ֵ");
	arrayFields.SetAt (5,"����ϵ�������%");
	arrayFields.SetAt (6,"�����ȱ�׼ֵ(V/m/s)");
	arrayFields.SetAt (7,"�����������%");
	arrayFields.SetAt (8,"ֱ������(ohm)");
	arrayFields.SetAt (9,"ֱ�����������%");
	arrayFields.SetAt (10,"ʧ���(<%)");
	arrayFields.SetAt (11,"���Ա�׼ֵ");
	arrayFields.SetAt (12,"��Ե�����׼ֵ(ohm)");
	arrayFields.SetAt (13,"��Ե���������%");
	arrayFields.SetAt (14,"��λ��׼ֵ(��)");
	arrayFields.SetAt (15,"��λ�����%");
	arrayFields.SetAt (16,"���ϴ�������");


	CStringArray arrayTypes;

	CString sTable="��1010�첨�����Ա�׼";
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