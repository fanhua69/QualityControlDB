// ReportDoc.cpp : implementation file
//

#include "stdafx.h"
#include "QCDB.h"
#include "ReportDoc.h"
#include "DlgReportProperty.h"
#include "MyDate.h"

// CReportDoc

IMPLEMENT_DYNCREATE(CReportDoc, CDataBrowseDoc)

CReportDoc::CReportDoc()
{
	m_sReportName="";

	m_iStartYear=0;
	m_iStartMonth=0;
	m_iStartDay=0;

	m_iEndYear=0;
	m_iEndMonth=0;
	m_iEndDay=0;
}

BOOL CReportDoc::OnNewDocument()
{
	if (!CDataBrowseDoc::OnNewDocument())
		return FALSE;

	CTime time=CTime::GetCurrentTime ();
	m_iCurrYear=time.GetYear ();
	m_iCurrMonth=time.GetMonth ();
	m_iCurrDay=time.GetDay ();

	CDlgReportProperty dlg;
	if(dlg.DoModal ()==IDCANCEL)return false;

	m_sReportName=dlg.m_sReportName ;
	
	m_iStartYear=dlg.m_iStartYear;
	m_iStartMonth=dlg.m_iStartMonth;
	m_iStartDay=dlg.m_iStartDay;

	m_iEndYear=dlg.m_iEndYear;
	m_iEndMonth=dlg.m_iEndMonth;
	m_iEndDay=dlg.m_iEndDay;

	m_iStatYear=dlg.m_iStatYear ;
	m_iStatMonth=dlg.m_iStatMonth ;
	m_iStatDay=dlg.m_iStatDay ;

	m_sReportCreator=dlg.m_sReportCreator ;
	m_sReportAuditor=dlg.m_sReportAuditor;

	m_sReportNumber=dlg.m_sReportNo ;

	m_iPrintPage=dlg.m_iPrintPage ;

	if(dlg.m_iMonthType ==0)
	{
		m_eMonthType=MT_NATURAL;
	}
	else
	{
		m_eMonthType=MT_STATISTICS;
	}

	GetProjectInfo(dlg.m_sProject);

	m_sLineName=dlg.m_sLineName ;
	m_sLineNo=GetLineNo(m_sProjectNo,m_sLineName);


	CStringArray array;
	GetReportNames(array);

	int iTableOrder=-1;
	for(int i=0;i<array.GetCount ();i++)
	{
		if(m_sReportName==array.GetAt (i))
		{
			iTableOrder=i;
			break;
		}
	}

	if(iTableOrder==-1)
	{
		ASSERT(false);
		TRACEERROR("没有这个表名字:"+m_sReportName);
		return false;
	}

	iTableOrder++;

	switch (iTableOrder)
	{
	case 1:
		return GetDataForReport01(dlg);
	case 2:
		return GetDataForReport02(dlg);
	case 3:
		return GetDataForReport03(dlg);
	case 4:
		return GetDataForReport04(dlg);
	case 5:
		return GetDataForReport05(dlg);
	case 6:
		return GetDataForReport06(dlg);
	case 7:
		return GetDataForReport07(dlg);
	case 8:
		return GetDataForReport08(dlg);
	case 9:
		return GetDataForReport09(dlg);
	case 10:
		return GetDataForReport10(dlg);
	case 11:
		return GetDataForReport11(dlg);
	case 12:
		return GetDataForReport12(dlg);
	case 13:
		return GetDataForReport13(dlg);
	case 14:
		return GetDataForReport14(dlg);
	case 15:
		return GetDataForReport15(dlg);
	case 16:
		return GetDataForReport16(dlg);
	case 17:
		return GetDataForReport17(dlg);
	case 18:
		return GetDataForReport18(dlg);
	case 19:
		return GetDataForReport19(dlg);
	case 20:
		return GetDataForReport20(dlg);
	case 21:
		return GetDataForReport21(dlg);
	case 22:
		return GetDataForReport22(dlg);
	case 23:
		return GetDataForReport23(dlg);
	case 24:
		return GetDataForReport24(dlg);
	case 25:
		return GetDataForReport25(dlg);
	case 26:
		return GetDataForReport26(dlg);
	case 27:
		return GetDataForReport27(dlg);
	case 28:
		return GetDataForReport28(dlg);
	case 29:
		return GetDataForReport29(dlg);
	case 30:
		return GetDataForReport30(dlg);
	default:
		ASSERT(false);
		TRACEERROR("没有建立这个表:"+m_sReportName);
		return false;
	}
}

CString CReportDoc::GetLineName(CString sNo)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	sSQL.Format ("select * from 表0201测线 where 编号='%s'",(LPCTSTR)sNo);
	arrayFields.Add ("测线名称");					//0

	CDataBrowseDoc docProject;
	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,"表0201测线",sSQL,dateStart,&arrayFields,&docProject,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	if(docProject.GetRecordQty ()==0)
	{
		TRACEERROR("没有符合条件的项目:"+sSQL);
		return false;
	}

	if(docProject.GetRecordQty ()>1)
	{
		TRACEERROR("符合条件的项目多于一个:"+sSQL);
		return false;
	}

	CStringArray *pRecord=docProject.GetRecord (0);
	if(!pRecord)
	{
		TRACEERROR("无法获得记录:"+sSQL);
		return false;
	}

	return pRecord->GetAt (0);
}

BOOL CReportDoc::GetProjectInfoByNo(CString sProjectNo, CStringArray *pArrayProject)
{
	CString sProjectName=GetProjectName(sProjectNo);
	return GetProjectInfo(sProjectName, pArrayProject);
}

BOOL CReportDoc::GetProjectInfo(CString sProjectName, CStringArray *pArrayProject)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	int i,j,k,n;

	sSQL.Format ("select * from 表0101项目 where 项目名称='%s'",(LPCTSTR)sProjectName);
	arrayFields.Add ("编号");					//0
	arrayFields.Add ("项目名称");				//1
	arrayFields.Add ("盆地");
	arrayFields.Add ("探区");
	arrayFields.Add ("探区缩写");

	arrayFields.Add ("工区");					//5
	arrayFields.Add ("工区缩写");
	arrayFields.Add ("施工年度");

	arrayFields.Add ("施工单位");
	arrayFields.Add ("队号");
	arrayFields.Add ("投资方");					//10
	
	arrayFields.Add ("设计满覆盖面积");
	arrayFields.Add ("设计单次覆盖面积");
	arrayFields.Add ("设计施工面积");

	arrayFields.Add ("是否三维");				//14
	arrayFields.Add ("设计测线数目");			//15

	arrayFields.Add ("投资方二维总炮数");		//16
	arrayFields.Add ("投资方二维总炮公里数");	//17
	arrayFields.Add ("投资方二维合同总额");		//18
	arrayFields.Add ("投资方三维总炮数");		//19
	arrayFields.Add ("投资方三维总炮公里数");	//20
	arrayFields.Add ("投资方三维合同总额");		//21

	arrayFields.Add ("施工方二维总炮数");		//22
	arrayFields.Add ("施工方二维总炮公里数");	//23
	arrayFields.Add ("施工方二维合同总额");		//24
	arrayFields.Add ("施工方三维总炮数");		//25
	arrayFields.Add ("施工方三维总炮公里数");	//26
	arrayFields.Add ("施工方三维合同总额");		//27

	arrayFields.Add ("主监督");			//28
	arrayFields.Add ("副监督1");		//29
	arrayFields.Add ("副监督2");		//30

	arrayFields.Add ("合同期限月");		//31

	arrayFields.Add ("单井1井深");		//32
	arrayFields.Add ("单井1药量");		//33
	arrayFields.Add ("单井2井深");		//34
	arrayFields.Add ("单井2药量");		//35
	arrayFields.Add ("单井3井深");		//36
	arrayFields.Add ("单井3药量");		//37
	arrayFields.Add ("单井4井深");		//38
	arrayFields.Add ("单井4药量");		//39
	arrayFields.Add ("单井5井深");		//40
	arrayFields.Add ("单井5药量");		//41
	arrayFields.Add ("单井6井深");		//42
	arrayFields.Add ("单井6药量");		//43
	arrayFields.Add ("单井7井深");		//44
	arrayFields.Add ("单井7药量");		//45
	arrayFields.Add ("单井8井深");		//46
	arrayFields.Add ("单井8药量");		//47
	arrayFields.Add ("单井9井深");		//48
	arrayFields.Add ("单井9药量");		//49
	arrayFields.Add ("单井10井深");		//50
	arrayFields.Add ("单井10药量");		//51

	arrayFields.Add ("组合井1口数");	//52
	arrayFields.Add ("组合井1井深");	//53
	arrayFields.Add ("组合井1药量");	//54
	arrayFields.Add ("组合井2口数");	//55
	arrayFields.Add ("组合井2井深");	//56
	arrayFields.Add ("组合井2药量");	//57
	arrayFields.Add ("组合井3口数");	//58
	arrayFields.Add ("组合井3井深");	//59
	arrayFields.Add ("组合井3药量");	//60
	arrayFields.Add ("组合井4口数");	//61
	arrayFields.Add ("组合井4井深");	//62
	arrayFields.Add ("组合井4药量");	//63
	arrayFields.Add ("组合井5口数");	//64
	arrayFields.Add ("组合井5井深");	//65
	arrayFields.Add ("组合井5药量");	//66
	arrayFields.Add ("组合井6口数");	//67
	arrayFields.Add ("组合井6井深");	//68
	arrayFields.Add ("组合井6药量");	//69
	arrayFields.Add ("组合井7口数");	//70
	arrayFields.Add ("组合井7井深");	//71
	arrayFields.Add ("组合井7药量");	//72
	arrayFields.Add ("组合井8口数");	//73
	arrayFields.Add ("组合井8井深");	//74
	arrayFields.Add ("组合井8药量");	//75
	arrayFields.Add ("组合井9口数");	//76
	arrayFields.Add ("组合井9井深");	//77
	arrayFields.Add ("组合井9药量");	//78
	arrayFields.Add ("组合井10口数");	//89
	arrayFields.Add ("组合井10井深");	//90
	arrayFields.Add ("组合井10药量");	//91



	CDataBrowseDoc docProject;
	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,"表0101项目",sSQL,dateStart,&arrayFields,&docProject,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	if(docProject.GetRecordQty ()==0)
	{
		TRACEERROR("没有符合条件的项目:"+sSQL);
		return false;
	}

	if(docProject.GetRecordQty ()>1)
	{
		TRACEERROR("符合条件的项目多于一个:"+sSQL);
		return false;
	}

	CStringArray *pRecord=docProject.GetRecord (0);
	if(!pRecord)
	{
		TRACEERROR("无法获得记录:"+sSQL);
		return false;
	}

	m_arrayProject.Copy (*pRecord);


	m_sProjectNo			=m_arrayProject.GetAt (0);
	m_sProjectName			=m_arrayProject.GetAt (1);
	m_sBasin				=m_arrayProject.GetAt (2);
	m_sProspectArea			=m_arrayProject.GetAt (3);
	m_sProspectAreaShort	=m_arrayProject.GetAt (4);
	m_sArea					=m_arrayProject.GetAt (5);
	m_sAreaShort			=m_arrayProject.GetAt (6);
	m_sYear					=m_arrayProject.GetAt (7);
	m_sServer				=m_arrayProject.GetAt (8);
	m_sCrew					=m_arrayProject.GetAt (9);
	m_sClient				=m_arrayProject.GetAt (10);
	m_s3DDesiFullCover		=m_arrayProject.GetAt (11);
	m_s3DDesignSingleCover	=m_arrayProject.GetAt (12);
	m_s3DDesiWorkAreaQty	=m_arrayProject.GetAt (13);
	
	m_sDesiLineQty			=m_arrayProject.GetAt (15);
	m_s2DDesiShotQty		=m_arrayProject.GetAt (16);
	m_s3DDesiShotQty		=m_arrayProject.GetAt (19);
	m_s2DDesiFullCover		=Get2DProjectFullCover(sProjectName);

	m_Client2D.iShotQty			= stof(m_arrayProject.GetAt (16));
	m_Client2D.fShotKilometer	= stof(m_arrayProject.GetAt (17));
	m_Client2D.fMoney			= stof(m_arrayProject.GetAt (18));
	m_Client3D.iShotQty			= stof(m_arrayProject.GetAt (19));
	m_Client3D.fShotKilometer	= stof(m_arrayProject.GetAt (20));
	m_Client3D.fMoney			= stof(m_arrayProject.GetAt (21));
	m_Server2D.iShotQty			= stof(m_arrayProject.GetAt (22));
	m_Server2D.fShotKilometer	= stof(m_arrayProject.GetAt (23));
	m_Server2D.fMoney			= stof(m_arrayProject.GetAt (24));
	m_Server3D.iShotQty			= stof(m_arrayProject.GetAt (25));
	m_Server3D.fShotKilometer	= stof(m_arrayProject.GetAt (26));
	m_Server3D.fMoney			= stof(m_arrayProject.GetAt (27));

	CStringArray arrayMonitor;
	AddMonitor(arrayMonitor,m_arrayProject.GetAt(28));
	AddMonitor(arrayMonitor,m_arrayProject.GetAt(29));
	AddMonitor(arrayMonitor,m_arrayProject.GetAt(30));
	m_sMonitor=GetMonitorString(arrayMonitor);

	m_iProjectMonth				= stof(m_arrayProject.GetAt (31));


	for(i=0;i<10;i++)
	{
        m_CSingleWell[i].fDepth = stof(m_arrayProject.GetAt (32+i*2));
        m_CSingleWell[i].fDynamite = stof(m_arrayProject.GetAt (32+i*2+1));
	}

	for(i=0;i<10;i++)
	{
        m_CMultiWell[i].iComboQty	= stof(m_arrayProject.GetAt (52+i*3));
        m_CMultiWell[i].fDepth		= stof(m_arrayProject.GetAt (52+i*3+1));
		m_CMultiWell[i].fDynamite	= stof(m_arrayProject.GetAt (52+i*3+2));
	}

	CString s=m_arrayProject.GetAt (14);
	int i3D=0;
	sscanf(s.GetBuffer(),"%d",&i3D);
	if(i3D!=0)
	{
		m_bIs3D=true;
	}
	else
	{
		m_bIs3D=false;
	}

	if(pArrayProject)
	{
		pArrayProject->Copy (m_arrayProject);
	}

	return TRUE;
}


CReportDoc::~CReportDoc()
{
}


BEGIN_MESSAGE_MAP(CReportDoc, CDataBrowseDoc)
END_MESSAGE_MAP()


// CReportDoc diagnostics

#ifdef _DEBUG
void CReportDoc::AssertValid() const
{
	CDataBrowseDoc::AssertValid();
}

void CReportDoc::Dump(CDumpContext& dc) const
{
	CDataBrowseDoc::Dump(dc);
}
#endif //_DEBUG


// CReportDoc serialization

void CReportDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CReportDoc commands



CString CReportDoc::Get2DProjectFullCover(CString sProjectName)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	CString sTable="表0201测线";

	CString sProjectNo=GetProjectNo(sProjectName);
	sSQL.Format ("select * from %s where 项目编号='%s'",sTable,(LPCTSTR)sProjectNo);
	arrayFields.Add ("设计满覆盖长度");					//0
	
	CDataBrowseDoc doc;

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,&doc,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("无法从数据表中获得数据:"+sSQL);
		return false;
	};

	float fKilometer=0.0;
	CStringArray *pRecord=NULL;
	for(int i=0;i<doc.GetRecordQty ();i++)
	{
		pRecord=doc.GetRecord (i);
		fKilometer+=stof(pRecord->GetAt (0));
	}

	m_s2DDesiFullCover=vtos(fKilometer,2);  // for 2D


	return m_s2DDesiFullCover;
}
