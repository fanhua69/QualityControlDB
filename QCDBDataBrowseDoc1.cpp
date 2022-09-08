
#include "stdafx.h"
#include "QCDB.h"
#include "QCDBDataBrowseDoc.h"
#include "fhcglobal.h"
#include "FHMainFrm.h"
#include "qcglobal.h"


// ��1001SPS�첨������
bool CQCDBDataBrowseDoc::InputQCData1001(   CString	        sProjectNo,
									        CString	        sTestNo,
									        CReportReader   *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=60)
	{
		AfxMessageBox("QC������벻��,ӦΪ60,����ļ���:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (12);
	arrayFields.SetAt (0,"���");
	arrayFields.SetAt (1,"��Ŀ���");
	arrayFields.SetAt (2,"���β��Ա��");
	arrayFields.SetAt (3,"�ߺ�");
	arrayFields.SetAt (4,"���");
	arrayFields.SetAt (5,"�Ƿ�ƫ���");
	arrayFields.SetAt (6,"ƫ�뷽��");
	arrayFields.SetAt (7,"ƫ�����");
	arrayFields.SetAt (8,"�Ƿ����ӵ�");
	arrayFields.SetAt (9,"�Ƿ�յ�");
	arrayFields.SetAt (10,"�Ƿ��ڵ��쳣��");
	arrayFields.SetAt (11,"���ϴ�������");

	CStringArray arrayTypes;

	CString sTable="��1001SPS�첨������";
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
		arrayRecord.SetAt (3,pData->GetAt (1)); //�ߺ�
		arrayRecord.SetAt (4,pData->GetAt (2)); //���

		// �Ƿ�ƫ���
		s=pData->GetAt (3);
		if(s!="")
		{
			arrayRecord.SetAt (5,"Y"); 
		}
		else
		{
			arrayRecord.SetAt (5,"N"); 
		}

		// ƫ�뷽��
		arrayRecord.SetAt (6,pData->GetAt (5)); 

		// ƫ�����
		arrayRecord.SetAt (7,pData->GetAt (4)); 

		// �Ƿ����ӵ�
		s=pData->GetAt (6);
		if(s!="")
		{
			arrayRecord.SetAt (8,"Y"); 
		}
		else
		{
			arrayRecord.SetAt (8,"N"); 
		}

		// �Ƿ�յ�
		s=pData->GetAt (7);
		if(s!="")
		{
			arrayRecord.SetAt (9,"Y"); 
		}
		else
		{
			arrayRecord.SetAt (9,"N"); 
		}

		// �����쳣 ��
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

//��1002SPS�첨���ܽ�
bool CQCDBDataBrowseDoc::InputQCData1002(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=60)
	{
		AfxMessageBox("QC������벻��,ӦΪ60,����ļ���:"+vtos(iNo));
		return false;
	}



	CStringArray arrayFields,arrayValues;
	arrayFields.SetSize (24);
	arrayFields.SetAt (0,"���");
	arrayFields.SetAt (1,"��Ŀ���");
	arrayFields.SetAt (2,"���߱��");
	arrayFields.SetAt (3,"�����");
	arrayFields.SetAt (4,"�����");
	arrayFields.SetAt (5,"�����");
	arrayFields.SetAt (6,"��Ƽ첨������");
	arrayFields.SetAt (7,"ʵ�ʼ첨������");
	arrayFields.SetAt (8,"ƫ�������");
	arrayFields.SetAt (9 ,"���ӵ�����");
	arrayFields.SetAt (10,"�յ�����");
	arrayFields.SetAt (11,"���쳣�첨������");
	arrayFields.SetAt (12,"ƫ������ż�1");
	arrayFields.SetAt (13,"ƫ������ż�2");
	arrayFields.SetAt (14,"ƫ������ż�3");
	arrayFields.SetAt (15,"ƫ������ż�4");
	arrayFields.SetAt (16,"ƫ������ż�5");
	arrayFields.SetAt (17,"ƫ������ż�6");
	arrayFields.SetAt (18,"�ż�1��2�������");
	arrayFields.SetAt (19,"�ż�2��3�������");
	arrayFields.SetAt (20,"�ż�3��4�������");
	arrayFields.SetAt (21,"�ż�4��5�������");
	arrayFields.SetAt (22,"�ż�5��6�������");
	arrayFields.SetAt (23,"���ϴ�������");

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
	CString sTable="��1002SPS�첨���ܽ�";
	db.AddRecord (sTable,arrayFields,arrayValues);

	return true;
}

// ��1003SPS�ڵ�����
bool CQCDBDataBrowseDoc::InputQCData1003(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=60)
	{
		AfxMessageBox("QC������벻��,ӦΪ60,����ļ���:"+vtos(iNo));
		return false;
	}


	CStringArray arrayFields;
	arrayFields.SetSize (12);
	arrayFields.SetAt (0,"���");
	arrayFields.SetAt (1,"��Ŀ���");
	arrayFields.SetAt (2,"���β��Ա��");
	arrayFields.SetAt (3,"�ߺ�");
	arrayFields.SetAt (4,"���");
	arrayFields.SetAt (5,"�Ƿ�ƫ���");
	arrayFields.SetAt (6,"ƫ�뷽��");
	arrayFields.SetAt (7,"ƫ�����");
	arrayFields.SetAt (8,"�Ƿ����ӵ�");
	arrayFields.SetAt (9,"�Ƿ�յ�");
	arrayFields.SetAt (10,"�Ƿ������쳣��");
	arrayFields.SetAt (11,"���ϴ�������");


	CStringArray arrayTypes;

	CString sTable="��1003SPS�ڵ�����";
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
		arrayRecord.SetAt (3,pData->GetAt (1)); //�ߺ�
		arrayRecord.SetAt (4,pData->GetAt (2)); //���

		// �Ƿ�ƫ���
		s=pData->GetAt (3);
		if(s!="")
		{
			arrayRecord.SetAt (5,"Y"); 
		}
		else
		{
			arrayRecord.SetAt (5,"N"); 
		}

		// ƫ�뷽��
		arrayRecord.SetAt (6,pData->GetAt (5)); 

		// ƫ�����
		arrayRecord.SetAt (7,pData->GetAt (4)); 

		// �Ƿ����ӵ�
		s=pData->GetAt (6);
		if(s!="")
		{
			arrayRecord.SetAt (8,"Y"); 
		}
		else
		{
			arrayRecord.SetAt (8,"N"); 
		}

		// �Ƿ�յ�
		s=pData->GetAt (7);
		if(s!="")
		{
			arrayRecord.SetAt (9,"Y"); 
		}
		else
		{
			arrayRecord.SetAt (9,"N"); 
		}

		// �����쳣 ��
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

//��1004SPS�ڵ��ܽ�
bool CQCDBDataBrowseDoc::InputQCData1004(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=60)
	{
		AfxMessageBox("QC������벻��,ӦΪ60,����ļ���:"+vtos(iNo));
		return false;
	}



	CStringArray arrayFields,arrayValues;
	arrayFields.SetSize (24);
	arrayFields.SetAt (0,"���");
	arrayFields.SetAt (1,"��Ŀ���");
	arrayFields.SetAt (2,"���߱��");
	arrayFields.SetAt (3,"�����");
	arrayFields.SetAt (4,"�����");
	arrayFields.SetAt (5,"�����");
	arrayFields.SetAt (6,"����ڵ�����");
	arrayFields.SetAt (7,"ʵ���ڵ�����");
	arrayFields.SetAt (8,"ƫ�������");
	arrayFields.SetAt (9 ,"���ӵ�����");
	arrayFields.SetAt (10,"�յ�����");
	arrayFields.SetAt (11,"�����쳣�ڵ�����");
	arrayFields.SetAt (12,"ƫ������ż�1");
	arrayFields.SetAt (13,"ƫ������ż�2");
	arrayFields.SetAt (14,"ƫ������ż�3");
	arrayFields.SetAt (15,"ƫ������ż�4");
	arrayFields.SetAt (16,"ƫ������ż�5");
	arrayFields.SetAt (17,"ƫ������ż�6");
	arrayFields.SetAt (18,"�ż�1��2�������");
	arrayFields.SetAt (19,"�ż�2��3�������");
	arrayFields.SetAt (20,"�ż�3��4�������");
	arrayFields.SetAt (21,"�ż�4��5�������");
	arrayFields.SetAt (22,"�ż�5��6�������");
	arrayFields.SetAt (23,"���ϴ�������");

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
	CString sTable="��1004SPS�ڵ��ܽ�";
	db.AddRecord (sTable,arrayFields,arrayValues);

	return true;
}

// ��1005�ڵ�����
bool CQCDBDataBrowseDoc::InputQCData1005(CString	sProjectNo,
									 CString	sTestNo,
									 CReportReader *pReader)
{
	int iNo=pReader->GetReportNo ();
	if(iNo!=12)
	{
		AfxMessageBox("QC������벻��,ӦΪ12,����ļ���:"+vtos(iNo));
		return false;
	}

	CStringArray arrayFields;
	arrayFields.SetSize (13);
	arrayFields.SetAt (0,"���");
	arrayFields.SetAt (1,"��Ŀ���");
	arrayFields.SetAt (2,"���β��Ա��");
	arrayFields.SetAt (3,"�ߺ�");
	arrayFields.SetAt (4,"���");
	arrayFields.SetAt (5,"�ļ���");
	arrayFields.SetAt (6,"�ϱ�����");
	arrayFields.SetAt (7,"��������");
	arrayFields.SetAt (8,"����");
	arrayFields.SetAt (9,"������");
	arrayFields.SetAt (10 ,"������λ");
	arrayFields.SetAt (11,"���θ߳�");
	arrayFields.SetAt (12,"���ϴ�������");


	CStringArray arrayTypes;

	CString sTable="��1005�ڵ�����";
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
		arrayRecord.SetAt (3,pData->GetAt (1)); //�ߺ�
		arrayRecord.SetAt (4,pData->GetAt (2)); //���
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