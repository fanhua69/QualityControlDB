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
    if(sTableName=="表0101项目")
    {
        ClearProjectNames       ();
    }
    else if(sTableName=="表0000监理人员基本情况统计表")
    {
        ClearMonitorNames       ();
    }
    else if(sTableName=="表0001技术人员基本情况统计表")
    {
        ClearTechnicianNames    ();
    }
    else if(sTableName=="表0002仪器型号统计表")
    {
        ClearInstrumentNames    ();
    }
    else if(sTableName=="表0201测线")
    {
        ::ClearSurveyLines();
    }
}

bool CQCDBDataBrowseDoc::InputQCData()
{
	CString sFile=GetFileForOpen("QC检测报告","txt");
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
	if(sTable=="表1001SPS检波点资料")
	{
		InputQCData1001(sProjectNo,
						sTestNo,
						&r);
	}
	else if(sTable=="表1002SPS检波点总结")
	{
		InputQCData1002(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="表1003SPS炮点资料")
	{
		InputQCData1003(sProjectNo,
						sTestNo,
						&r);
	}
	else if(sTable=="表1004SPS炮点总结")
	{
		InputQCData1004(sProjectNo,
						sTestNo,
						&r);
	}
	else if(sTable=="表1005炮点资料")
	{
		InputQCData1005(sProjectNo,
						sTestNo,
						&r);
	}
	
	else if(sTable=="表1006单炮分频能量资料")
	{
		InputQCData1006(sProjectNo,
						sTestNo,
						&r);
	}
	
	else if(sTable=="表1007单炮分频能量总结")
	{
		InputQCData1007(sProjectNo,
						sTestNo,
						&r);
	}
	
	else if(sTable=="表1008单炮整体能量资料")
	{
		InputQCData1008(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="表1009单炮整体能量总结")
	{
		InputQCData1009(sProjectNo,
						sTestNo,
						&r);
	}


	else if(sTable=="表1010检波器测试标准")
	{
		InputQCData1010(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="表1011检波器测试情况资料")
	{
		InputQCData1011(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="表1012检波器测试数据")
	{
		InputQCData1012(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="表1013检波器测试总结")
	{
		InputQCData1013(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="表1014井深总结")
	{
		InputQCData1014(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="表1015井深资料")
	{
		InputQCData1015(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="表1016药量总结")
	{
		InputQCData1016(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="表1017药量资料")
	{
		InputQCData1017(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="表1018年月日检标准")
	{
		InputQCData1018(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="表1019年月日检资料")
	{
		InputQCData1019(sProjectNo,
						sTestNo,
						&r);
	}

	else if(sTable=="表1020年月日检总结")
	{
		InputQCData1020(sProjectNo,
						sTestNo,
						&r);
	}
	else
	{
		ASSERT(false);
		AfxMessageBox("请选取正确的QC表!");
	}

	UpdateFromDB ();

    return true;
}

