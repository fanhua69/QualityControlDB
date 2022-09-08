// DataBrowseDoc.cpp : implementation file
//

#include "stdafx.h"
#include "QCDB.h"
#include "QCDBDataBrowseDoc.h"
#include "fhcglobal.h"
#include "FHMainFrm.h"
#include "qcglobal.h"
#include "DlgEditShowProperty.h"
#include "DlgDBPicProperty.h"
#include "DlgDBShowProperty.h"
#include "DlgDataSelector.h"
#include "QCReportReader.h"
#include "QCDBDataBrowseView.h"


// CQCDBDataBrowseDoc

IMPLEMENT_DYNCREATE(CQCDBDataBrowseDoc, CDataBrowseDoc)

CQCDBDataBrowseDoc::CQCDBDataBrowseDoc()
{
}

CQCDBDataBrowseDoc::~CQCDBDataBrowseDoc()
{
}


BEGIN_MESSAGE_MAP(CQCDBDataBrowseDoc, CDataBrowseDoc)
END_MESSAGE_MAP()


// CQCDBDataBrowseDoc diagnostics

#ifdef _DEBUG
void CQCDBDataBrowseDoc::AssertValid() const
{
	CDataBrowseDoc::AssertValid();
}

void CQCDBDataBrowseDoc::Dump(CDumpContext& dc) const
{
	CDataBrowseDoc::Dump(dc);
}
#endif //_DEBUG

void CQCDBDataBrowseDoc::UpdateDB()
{
    CDataBrowseDoc::UpdateDB();

    //////////////////////////////////////////////
    //
    //////////////////////////////////////////////
    CString sTableName=GetTableName();
    if(sTableName=="��0101��Ŀ")
    {
        ClearProjectNames       ();
    }
    else if(sTableName=="��0000������Ա�������ͳ�Ʊ�")
    {
        ClearMonitorNames       ();
    }
    else if(sTableName=="��0001������Ա�������ͳ�Ʊ�")
    {
        ClearTechnicianNames    ();
    }
    else if(sTableName=="��0002�����ͺ�ͳ�Ʊ�")
    {
        ClearInstrumentNames    ();
    }
    else if(sTableName=="��0201����")
    {
        ::ClearSurveyLines();
    }
}

bool CQCDBDataBrowseDoc::InputQCData()
{
	CString sFile=GetFileForOpen("QC��ⱨ��","txt");
	if(sFile=="")return false;

	CQCReportReader r;
	if(!r.OpenFile (sFile))
	{
		return false;
	}

	CString sProjectName=r.GetItemValue (0);
	CString sProjectNo=GetProjectNo(sProjectName);
	CString sTestNo=r.GetItemValue (10);

	////////////////////////////////////////////
	//
	////////////////////////////////////////////
	CString sTable=GetTableName();
	if(sTable=="��1001SPS�첨������")
	{
		InputQCData1001(sProjectNo,
						sTestNo,
						&r);
	}
	else if(sTable=="��1002SPS�첨���ܽ�")
	{
		InputQCData1002(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="��1003SPS�ڵ�����")
	{
		InputQCData1003(sProjectNo,
						sTestNo,
						&r);
	}
	else if(sTable=="��1004SPS�ڵ��ܽ�")
	{
		InputQCData1004(sProjectNo,
						sTestNo,
						&r);
	}
	else if(sTable=="��1005�ڵ�����")
	{
		InputQCData1005(sProjectNo,
						sTestNo,
						&r);
	}
	
	else if(sTable=="��1006���ڷ�Ƶ��������")
	{
		InputQCData1006(sProjectNo,
						sTestNo,
						&r);
	}
	
	else if(sTable=="��1007���ڷ�Ƶ�����ܽ�")
	{
		InputQCData1007(sProjectNo,
						sTestNo,
						&r);
	}
	
	else if(sTable=="��1008����������������")
	{
		InputQCData1008(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="��1009�������������ܽ�")
	{
		InputQCData1009(sProjectNo,
						sTestNo,
						&r);
	}


	else if(sTable=="��1010�첨�����Ա�׼")
	{
		InputQCData1010(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="��1011�첨�������������")
	{
		InputQCData1011(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="��1012�첨����������")
	{
		InputQCData1012(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="��1013�첨�������ܽ�")
	{
		InputQCData1013(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="��1014�����ܽ�")
	{
		InputQCData1014(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="��1015��������")
	{
		InputQCData1015(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="��1016ҩ���ܽ�")
	{
		InputQCData1016(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="��1017ҩ������")
	{
		InputQCData1017(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="��1018�����ռ��׼")
	{
		InputQCData1018(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="��1019�����ռ�����")
	{
		InputQCData1019(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="��1020�����ռ��ܽ�")
	{
		InputQCData1020(sProjectNo,
						sTestNo,
						&r);
	}
	else
	{
		ASSERT(false);
		AfxMessageBox("��ѡȡ��ȷ��QC��!");
	}

	UpdateFromDB ();

    return true;
}

