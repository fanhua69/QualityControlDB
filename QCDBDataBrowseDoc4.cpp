
#include "stdafx.h"
#include "QCDB.h"
#include "QCDBDataBrowseDoc.h"
#include "fhcglobal.h"
#include "FHMainFrm.h"
#include "qcglobal.h"

// ��1016ҩ���ܽ�
bool CQCDBDataBrowseDoc::InputQCData1016(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{

	int iNo=pReader->GetReportNo ();
	if(iNo!=41)
	{
		AfxMessageBox("QC������벻��,ӦΪ41,����ļ���:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (17);
	arrayFields.SetAt (0,"���");
	arrayFields.SetAt (1,"��Ŀ���");
	arrayFields.SetAt (2,"���߱��");
	arrayFields.SetAt (3,"������");
	arrayFields.SetAt (4,"������");
	arrayFields.SetAt (5,"������");

	arrayFields.SetAt (6,"����ܾ���");
	arrayFields.SetAt (7,"������ƾ���Ŀ");
	arrayFields.SetAt (8,"ʩ������ƾ���Ŀ");
	arrayFields.SetAt (9,"ʵ�ʾ���Ŀ");
	arrayFields.SetAt (10,"�߲���");
	arrayFields.SetAt (11,"�Ͳ���");
	arrayFields.SetAt (12,"��ʩ���������ҩ������");
	arrayFields.SetAt (13,"��ʩ������ƶ�ҩ������");
	arrayFields.SetAt (14,"�ȼ��������ҩ������");
	arrayFields.SetAt (15,"�ȼ�����ƶ�ҩ������");

	arrayFields.SetAt (16,"���ϴ�������");

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
	CString sTable="��1016ҩ���ܽ�";
	db.AddRecord (sTable,arrayFields,arrayValues);

	return true;
}

// ��1017ҩ������
bool CQCDBDataBrowseDoc::InputQCData1017(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=41)
	{
		AfxMessageBox("QC������벻��,ӦΪ41,����ļ���:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (12);
	arrayFields.SetAt (0,"���");
	arrayFields.SetAt (1,"���β��Ա��");
	arrayFields.SetAt (2,"�ߺ�");
	arrayFields.SetAt (3,"���");
	arrayFields.SetAt (4,"�ϱ�����");
	arrayFields.SetAt (5,"��������");
	arrayFields.SetAt (6,"�������ҩ��");
	arrayFields.SetAt (7 ,"ʩ�������ҩ��");
	arrayFields.SetAt (8 ,"ʵ��ҩ��");
	arrayFields.SetAt (9 ,"ʵ�ʼ�����");
	arrayFields.SetAt (10,"ʵ�ʼ�ʩ����");	
	arrayFields.SetAt (11,"���ϴ�������");

	CStringArray arrayTypes;

	CString sTable="��1017ҩ������";
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



// ��1018�����ռ��׼
bool CQCDBDataBrowseDoc::InputQCData1018(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();

	if(iNo!=50)
	{
		AfxMessageBox("QC������벻��,ӦΪ50,����ļ���:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (17);
	arrayFields.SetAt (0,"���");
	arrayFields.SetAt (1,"���β��Ա��");
	arrayFields.SetAt (2,"�����Ŀ����");
	arrayFields.SetAt (3,"�����Ŀ����");
	arrayFields.SetAt (4,"��λ");
	arrayFields.SetAt (5,"K����");
	arrayFields.SetAt (6,"ǰ������");
	arrayFields.SetAt (7 ,"�ź�˥��");
	arrayFields.SetAt (8 ,"���޵���");
	arrayFields.SetAt (9 ,"������");
	arrayFields.SetAt (10,"FDU/GEO");	
	arrayFields.SetAt (11,"���۷�ʽ");	
	arrayFields.SetAt (12,"Ĭ�ϱ�׼ֵ");	
	arrayFields.SetAt (13,"��׼ֵ");	
	arrayFields.SetAt (14,"�����");	
	arrayFields.SetAt (15,"�������");
	arrayFields.SetAt (16,"���ϴ�������");

	CStringArray arrayTypes;

	CString sTable="��1018�����ռ��׼";
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


// ��1019�����ռ�����
bool CQCDBDataBrowseDoc::InputQCData1019(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=50)
	{
		AfxMessageBox("QC������벻��,ӦΪ50,����ļ���:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (40);
	arrayFields.SetAt (0,"���");
	arrayFields.SetAt (1,"���β��Ա��");
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
	arrayFields.SetAt (39,"���ϴ�������");

	CStringArray arrayTypes;

	CString sTable="��1019�����ռ�����";
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


// ��1020�����ռ��ܽ�
bool CQCDBDataBrowseDoc::InputQCData1020(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=50)
	{
		AfxMessageBox("QC������벻��,ӦΪ50,����ļ���:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (22);
	arrayFields.SetAt (0,"���");
	arrayFields.SetAt (1,"��Ŀ���");
	arrayFields.SetAt (2,"���߱��");
	arrayFields.SetAt (3,"������");
	arrayFields.SetAt (4,"������");
	arrayFields.SetAt (5,"������");
	arrayFields.SetAt (6,"�������ͺ�");
	arrayFields.SetAt (7,"�������");
	arrayFields.SetAt (8 ,"������");
	arrayFields.SetAt (9 ,"Ӧ�����Ŀ");
	arrayFields.SetAt (10,"ʵ�����Ŀ");
	arrayFields.SetAt (11,"���ɼ�վ����");
	arrayFields.SetAt (12,"�ɼ�վ��С���");
	arrayFields.SetAt (13,"�ɼ�վ�����");
	arrayFields.SetAt (14,"���òɼ�վ����");
	arrayFields.SetAt (15,"δ���ɼ�վ���");
	arrayFields.SetAt (16,"�����òɼ�վ����");
	arrayFields.SetAt (17,"�����òɼ�վ���");
	arrayFields.SetAt (18,"�ɼ�վͨ������");
	arrayFields.SetAt (19,"���Լ첨������");
	arrayFields.SetAt (20,"�ϸ�첨������");
	arrayFields.SetAt (21,"���ϴ�������");

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
	CString sTable="��1020�����ռ��ܽ�";
	db.AddRecord (sTable,arrayFields,arrayValues);

	return true;
}
