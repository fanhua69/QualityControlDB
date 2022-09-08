
#include "stdafx.h"
#include "QCDB.h"
#include "QCDBDataBrowseDoc.h"
#include "fhcglobal.h"
#include "FHMainFrm.h"
#include "qcglobal.h"

// ��1011�첨�������������
bool CQCDBDataBrowseDoc::InputQCData1011(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	

	int iNo=pReader->GetReportNo ();
	if(iNo!=20&&iNo!=21)
	{
		AfxMessageBox("QC������벻��,ӦΪ20����21,����ļ���:"+vtos(iNo));
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
	arrayFields.SetAt (6,"��������");
	arrayFields.SetAt (7,"�첨���ͺ�");
	arrayFields.SetAt (8,"�������ͺ�(��������)");
	arrayFields.SetAt (9 ,"���ڴ�����(��������)");
	arrayFields.SetAt (10,"���ڲ�����(��������)");
	arrayFields.SetAt (11,"������Ŀ");
	arrayFields.SetAt (12,"������Ŀ");
	arrayFields.SetAt (13,"С�ߵ�����(ohm/100m)");
	arrayFields.SetAt (14,"С�������첨�������(m)");
	arrayFields.SetAt (15,"��һ�첨�������߾���(m)");
	arrayFields.SetAt (16,"���ϴ�������");


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
		arrayValues.SetAt(6,"�����ǲ��Լ첨��");
	}
	else
	{
		arrayValues.SetAt(6,"�����ǲ��Լ첨��");
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
	CString sTable="��1011�첨�������������";
	db.AddRecord (sTable,arrayFields,arrayValues);

	return true;
}

// ��1012�첨����������
bool CQCDBDataBrowseDoc::InputQCData1012(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=20&&iNo!=21)
	{
		AfxMessageBox("QC������벻��,ӦΪ20����21,����ļ���:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (14);
	arrayFields.SetAt (0,"���");
	arrayFields.SetAt (1,"���β��Ա��");
	arrayFields.SetAt (2,"�ɼ�վ��");
	arrayFields.SetAt (3,"�ߺ�");
	arrayFields.SetAt (4,"���");

	arrayFields.SetAt (5,"��ȻƵ��");
	arrayFields.SetAt (6,"����ϵ��");
	arrayFields.SetAt (7,"г��ʧ��");
	arrayFields.SetAt (8 ,"������");
	arrayFields.SetAt (9 ,"ֱ������");
	arrayFields.SetAt (10,"����");
	arrayFields.SetAt (11,"��Ե����");
	arrayFields.SetAt (12,"��λ");
	
	arrayFields.SetAt (13,"���ϴ�������");

	CStringArray arrayTypes;

	CString sTable="��1012�첨����������";
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

// ��1013�첨�������ܽ�
bool CQCDBDataBrowseDoc::InputQCData1013(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=20&&iNo!=21)
	{
		AfxMessageBox("QC������벻��,ӦΪ20����21,����ļ���:"+vtos(iNo));
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

	arrayFields.SetAt (6,"��ʼ����ߺ�");
	arrayFields.SetAt (7,"��ֹ����ߺ�");
	arrayFields.SetAt (8,"��ʼ�����");
	arrayFields.SetAt (9,"��ֹ�����");
	arrayFields.SetAt (10,"���Լ첨������");
	arrayFields.SetAt (11,"�����첨������");
	arrayFields.SetAt (12,"���ü첨������");

	arrayFields.SetAt (13,"��ȻƵ��ʧ������");
	arrayFields.SetAt (14,"����ϵ��ʧ������");
	arrayFields.SetAt (15,"г��ʧ��ʧ������");


	arrayFields.SetAt (16,"������ʧ������");
	arrayFields.SetAt (17,"ֱ������ʧ������");
	arrayFields.SetAt (18,"����ʧ������");
	arrayFields.SetAt (19,"��Ե����ʧ������");
	arrayFields.SetAt (20,"��λʧ������");

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
	CString sTable="��1013�첨�������ܽ�";
	db.AddRecord (sTable,arrayFields,arrayValues);

	return true;
}

// ��1014�����ܽ�
bool CQCDBDataBrowseDoc::InputQCData1014(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{

	int iNo=pReader->GetReportNo ();
	if(iNo!=40)
	{
		AfxMessageBox("QC������벻��,ӦΪ40,����ļ���:"+vtos(iNo));
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
	arrayFields.SetAt (12,"�ȼ������Ŀ");
	arrayFields.SetAt (13,"�ȼ���ǳ����Ŀ");
	arrayFields.SetAt (14,"��ʩ�������Ŀ");
	arrayFields.SetAt (15,"��ʩ����ǳ����Ŀ");

	arrayFields.SetAt (16,"���ϴ�������");

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
	CString sTable="��1014�����ܽ�";
	db.AddRecord (sTable,arrayFields,arrayValues);

	return true;
}


//  ��1015�������� 
bool CQCDBDataBrowseDoc::InputQCData1015(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=40)
	{
		AfxMessageBox("QC������벻��,ӦΪ40,����ļ���:"+vtos(iNo));
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
	arrayFields.SetAt (6,"������ƾ���");
	arrayFields.SetAt (7 ,"ʩ������ƾ���");
	arrayFields.SetAt (8 ,"ʵ�ʾ���");
	arrayFields.SetAt (9 ,"ʵ�ʼ�����");
	arrayFields.SetAt (10,"ʵ�ʼ�ʩ����");	
	arrayFields.SetAt (11,"���ϴ�������");

	CStringArray arrayTypes;

	CString sTable="��1015��������";
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

