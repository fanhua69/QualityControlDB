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
		TRACEERROR("û�����������:"+m_sReportName);
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
		TRACEERROR("û�н��������:"+m_sReportName);
		return false;
	}
}

CString CReportDoc::GetLineName(CString sNo)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	sSQL.Format ("select * from ��0201���� where ���='%s'",(LPCTSTR)sNo);
	arrayFields.Add ("��������");					//0

	CDataBrowseDoc docProject;
	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,"��0201����",sSQL,dateStart,&arrayFields,&docProject,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	if(docProject.GetRecordQty ()==0)
	{
		TRACEERROR("û�з�����������Ŀ:"+sSQL);
		return false;
	}

	if(docProject.GetRecordQty ()>1)
	{
		TRACEERROR("������������Ŀ����һ��:"+sSQL);
		return false;
	}

	CStringArray *pRecord=docProject.GetRecord (0);
	if(!pRecord)
	{
		TRACEERROR("�޷���ü�¼:"+sSQL);
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

	sSQL.Format ("select * from ��0101��Ŀ where ��Ŀ����='%s'",(LPCTSTR)sProjectName);
	arrayFields.Add ("���");					//0
	arrayFields.Add ("��Ŀ����");				//1
	arrayFields.Add ("���");
	arrayFields.Add ("̽��");
	arrayFields.Add ("̽����д");

	arrayFields.Add ("����");					//5
	arrayFields.Add ("������д");
	arrayFields.Add ("ʩ�����");

	arrayFields.Add ("ʩ����λ");
	arrayFields.Add ("�Ӻ�");
	arrayFields.Add ("Ͷ�ʷ�");					//10
	
	arrayFields.Add ("������������");
	arrayFields.Add ("��Ƶ��θ������");
	arrayFields.Add ("���ʩ�����");

	arrayFields.Add ("�Ƿ���ά");				//14
	arrayFields.Add ("��Ʋ�����Ŀ");			//15

	arrayFields.Add ("Ͷ�ʷ���ά������");		//16
	arrayFields.Add ("Ͷ�ʷ���ά���ڹ�����");	//17
	arrayFields.Add ("Ͷ�ʷ���ά��ͬ�ܶ�");		//18
	arrayFields.Add ("Ͷ�ʷ���ά������");		//19
	arrayFields.Add ("Ͷ�ʷ���ά���ڹ�����");	//20
	arrayFields.Add ("Ͷ�ʷ���ά��ͬ�ܶ�");		//21

	arrayFields.Add ("ʩ������ά������");		//22
	arrayFields.Add ("ʩ������ά���ڹ�����");	//23
	arrayFields.Add ("ʩ������ά��ͬ�ܶ�");		//24
	arrayFields.Add ("ʩ������ά������");		//25
	arrayFields.Add ("ʩ������ά���ڹ�����");	//26
	arrayFields.Add ("ʩ������ά��ͬ�ܶ�");		//27

	arrayFields.Add ("���ල");			//28
	arrayFields.Add ("���ල1");		//29
	arrayFields.Add ("���ල2");		//30

	arrayFields.Add ("��ͬ������");		//31

	arrayFields.Add ("����1����");		//32
	arrayFields.Add ("����1ҩ��");		//33
	arrayFields.Add ("����2����");		//34
	arrayFields.Add ("����2ҩ��");		//35
	arrayFields.Add ("����3����");		//36
	arrayFields.Add ("����3ҩ��");		//37
	arrayFields.Add ("����4����");		//38
	arrayFields.Add ("����4ҩ��");		//39
	arrayFields.Add ("����5����");		//40
	arrayFields.Add ("����5ҩ��");		//41
	arrayFields.Add ("����6����");		//42
	arrayFields.Add ("����6ҩ��");		//43
	arrayFields.Add ("����7����");		//44
	arrayFields.Add ("����7ҩ��");		//45
	arrayFields.Add ("����8����");		//46
	arrayFields.Add ("����8ҩ��");		//47
	arrayFields.Add ("����9����");		//48
	arrayFields.Add ("����9ҩ��");		//49
	arrayFields.Add ("����10����");		//50
	arrayFields.Add ("����10ҩ��");		//51

	arrayFields.Add ("��Ͼ�1����");	//52
	arrayFields.Add ("��Ͼ�1����");	//53
	arrayFields.Add ("��Ͼ�1ҩ��");	//54
	arrayFields.Add ("��Ͼ�2����");	//55
	arrayFields.Add ("��Ͼ�2����");	//56
	arrayFields.Add ("��Ͼ�2ҩ��");	//57
	arrayFields.Add ("��Ͼ�3����");	//58
	arrayFields.Add ("��Ͼ�3����");	//59
	arrayFields.Add ("��Ͼ�3ҩ��");	//60
	arrayFields.Add ("��Ͼ�4����");	//61
	arrayFields.Add ("��Ͼ�4����");	//62
	arrayFields.Add ("��Ͼ�4ҩ��");	//63
	arrayFields.Add ("��Ͼ�5����");	//64
	arrayFields.Add ("��Ͼ�5����");	//65
	arrayFields.Add ("��Ͼ�5ҩ��");	//66
	arrayFields.Add ("��Ͼ�6����");	//67
	arrayFields.Add ("��Ͼ�6����");	//68
	arrayFields.Add ("��Ͼ�6ҩ��");	//69
	arrayFields.Add ("��Ͼ�7����");	//70
	arrayFields.Add ("��Ͼ�7����");	//71
	arrayFields.Add ("��Ͼ�7ҩ��");	//72
	arrayFields.Add ("��Ͼ�8����");	//73
	arrayFields.Add ("��Ͼ�8����");	//74
	arrayFields.Add ("��Ͼ�8ҩ��");	//75
	arrayFields.Add ("��Ͼ�9����");	//76
	arrayFields.Add ("��Ͼ�9����");	//77
	arrayFields.Add ("��Ͼ�9ҩ��");	//78
	arrayFields.Add ("��Ͼ�10����");	//89
	arrayFields.Add ("��Ͼ�10����");	//90
	arrayFields.Add ("��Ͼ�10ҩ��");	//91



	CDataBrowseDoc docProject;
	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,"��0101��Ŀ",sSQL,dateStart,&arrayFields,&docProject,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	if(docProject.GetRecordQty ()==0)
	{
		TRACEERROR("û�з�����������Ŀ:"+sSQL);
		return false;
	}

	if(docProject.GetRecordQty ()>1)
	{
		TRACEERROR("������������Ŀ����һ��:"+sSQL);
		return false;
	}

	CStringArray *pRecord=docProject.GetRecord (0);
	if(!pRecord)
	{
		TRACEERROR("�޷���ü�¼:"+sSQL);
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
	CString sTable="��0201����";

	CString sProjectNo=GetProjectNo(sProjectName);
	sSQL.Format ("select * from %s where ��Ŀ���='%s'",sTable,(LPCTSTR)sProjectNo);
	arrayFields.Add ("��������ǳ���");					//0
	
	CDataBrowseDoc doc;

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,&doc,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
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
