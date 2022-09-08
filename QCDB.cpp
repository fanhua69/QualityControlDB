// QCDB.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "QCDB.h"
#include "MainFrm.h"
#include "fhapp.h"

#include "ChildFrm.h"
#include "QCDBDoc.h"
#include "QCDBView.h"

#include "QCDBDataBrowseDoc.h"
#include "QCDBDataBrowseView.h"

#include "rasdlg.h"

#include "DataChartView.h"


#include "DataTransDoc.h"
#include "DataTranFrame.h"
#include "LinkingsView.h"

#include "fhtable.h"
#include ".\qcdb.h"

#include "DlgGlobalProperty.h"

#include "QCGlobal.h"

#include "DlgInputServer.h"
#include "DlgLocalServerProperty.h"
#include "DlgInterfaceProperty.h"
#include "DlgTranProperty.h"
#include "DlgProjectProperty.h"
#include "DlgUserInfo.h"
#include "DlgReportProperty.h"

#include "DataBrowseFrame.h"
#include "DataBrowseDoc.h"
#include "DataBrowseView.h"

#include "ReportDoc.h"
#include "ReportView.h"

#include "PasswordDoc.h"
#include "PasswordView.h"

#include "SoftDog.h"

#include "defines.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////
// Note:
/*
1.����Ƿ������汾������defines.h�ж��壺
        QCDB_SERVER.
��������ȫ�ֺ���ʶ��÷��ţ�
        bool IsServer()
���ж��Ƿ�������汾��

   ����ǿͻ��˰汾���򲻶���÷��š�

2�����ʹ��Oracle,����defines.h�ж��壺
   QCDB_ORACLE.
   ���ʹ��Excel�汾�������ö���

3������汾�ŵ�ʶ��������
    SoftDog.cpp
    �С�

4��������汾��defines.h�ж���DOG
*/
////////////////////////////////////////////////



// CQCDBApp

BEGIN_MESSAGE_MAP(CQCDBApp, CFHApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, CFHApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CFHApp::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, CFHApp::OnFilePrintSetup)
	ON_COMMAND(ID_CreateOriDB, OnCreateoridb)
	ON_COMMAND(ID_SetGlobalInfo, OnSetglobalinfo)
	ON_COMMAND(ID_GetDataFromServer, OnShowData)
	ON_COMMAND(ID_OutputTable, OnOutputtable)
	ON_COMMAND(ID_ConnectServers, OnConnectservers)
	ON_COMMAND(ID_UserRegister, OnUserregister)
END_MESSAGE_MAP()

// CQCDBApp ����

CQCDBApp::CQCDBApp()
{
	EnableHtmlHelp();

	CreateTableProperty();

    CSplashWnd::SetCover (IDB_QCDB_COVER);


    /////////////////////////////////
    // �������ļ���
    SetParFile(m_sWorkDir+"\\QCDB.par");

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

CQCDBApp::~CQCDBApp()
{
	bool bSavePassword;
	GetPar("GLOBAL_SAVE_PASSWORD",bSavePassword);
	if(!bSavePassword)
	{
		RemovePar("GLOBAL_PASSWORD");
	}
}


// Ψһ��һ�� CQCDBApp ����

CQCDBApp theApp;

// CQCDBApp ��ʼ��

BOOL CQCDBApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();

	CFHApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)
	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CMultiDocTemplate* pDocTemplate=NULL;

	pDocTemplate = new CMultiDocTemplate(IDR_DBBrowse,
		RUNTIME_CLASS(CQCDBDataBrowseDoc),
		RUNTIME_CLASS(CDataBrowseFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CQCDBDataBrowseView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMultiDocTemplate(IDR_ReportCreator,
		RUNTIME_CLASS(CReportDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CReportView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	pDocTemplate = new CMultiDocTemplate(IDR_QCDBTYPE,
		RUNTIME_CLASS(CQCDBDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CQCDBView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMultiDocTemplate(IDR_DBChart,
		RUNTIME_CLASS(CDataBrowseDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CDataChartView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMultiDocTemplate(IDR_DataTransfer,
		RUNTIME_CLASS(CDataTransDoc),
		RUNTIME_CLASS(CDataTranFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CLinkingsView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	if(IsServer())
	{
		pDocTemplate = new CMultiDocTemplate(IDR_Password,
			RUNTIME_CLASS(CPasswordDoc),
			RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
			RUNTIME_CLASS(CPasswordView));
		if (!pDocTemplate)
			return FALSE;
		AddDocTemplate(pDocTemplate);
	}

	// ������ MDI ��ܴ���
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;


	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	if(IsServer())
	{
		pMainFrame->SetWindowText ("QCDB-Server");
	}
	else
	{
		pMainFrame->SetWindowText ("QCDB-Client");
	}


	CString sFile;
	GetPar("QCDB_PASSWORD_FILE",sFile);
	if(sFile!="")
	{
		SetPassword (sFile);
	}

	InitiateNet();

	/////////////////////////////
	//
	SetProjectID();

#ifdef DOG
    if(!m_dog.CheckMark ())
    {
        return false;
    }

    if(!m_dog.CheckUserID ())
    {
        return false;
    }

    WORD v1=3;
    WORD v2=4;
    WORD v3=5;
    WORD v4=6;

    if(!m_dog.CheckCalc(v1,v2,v3,v4))
    {
        return false;
    }

    if(!m_dog.WriteRand (0))
    {
        return false;
    }

    if(!m_dog.CheckRand (0))
    {
        return false;
    }

#endif


#ifdef PASSWORD
    CPasswordManager p;
    p.Read ("up.dat");	
    return p.Check ();
#endif

	return TRUE;
}



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
    CString m_sSerial;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
, m_sSerial(_T(""))
{
    CSoftDog dog;
    m_sSerial="ZYWT-JLGS-";
    char s[10];
    long n=10000+dog.GetSerNumber();
    sprintf(s,"%ld",n);
    m_sSerial+=s;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_editSerial, m_sSerial);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CQCDBApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CQCDBApp::CreateTableProperty()
{
	m_arrayTables.Add(CTableProperty("��0000������Ա�������ͳ�Ʊ�","Monitor","����"));
	m_arrayTables.Add(CTableProperty("��0001������Ա�������ͳ�Ʊ�","Technician","����"));
	m_arrayTables.Add(CTableProperty("��0101��Ŀ","Project","��Ŀ����"));
	m_arrayTables.Add(CTableProperty("��0102��Ŀ����ɼ�ʩ������һ����","ProjectAquiPar","��Ŀ���"));
	m_arrayTables.Add(CTableProperty("��0103��Ŀ�������ͳ�Ʊ�","ProjectQuality","��Ŀ���"));
	m_arrayTables.Add(CTableProperty("��0104Ŀ�Ĳ�ָ��ͳ�Ʊ�","ProjectTarget","��Ŀ���"));
	m_arrayTables.Add(CTableProperty("��0105���Ų�ָ��","ProjectNoise","��Ŀ���"));
	m_arrayTables.Add(CTableProperty("��0106�������ռ���","ProjectAccept","��Ŀ���"));
	m_arrayTables.Add(CTableProperty("��0107��Ҫ������Ա��λ�������","ProjectTecnician","��Ŀ���"));
	m_arrayTables.Add(CTableProperty("��0108��Ҫ�豸��λ�������","ProjectEquipment","��Ŀ���"));
	m_arrayTables.Add(CTableProperty("��0109���鹤���ලͳ�Ʊ�","ProjectTest","��Ŀ���"));
	m_arrayTables.Add(CTableProperty("��0201����","Line","��������"));
	m_arrayTables.Add(CTableProperty("��0301�������ձ�","MonitorDaily","��"));
	m_arrayTables.Add(CTableProperty("��0302�����ල�ձ�","SurveyDaily","��"));
	m_arrayTables.Add(CTableProperty("��0303�����ල�ձ�","InstrumentDaily","��"));
	m_arrayTables.Add(CTableProperty("��0304QC��������嵥","QCReportDaily","��"));
	m_arrayTables.Add(CTableProperty("��0401ʩ������ල����","WorkPrecedure","�����"));
	m_arrayTables.Add(CTableProperty("��0402�ල��鱸��¼","MonitorInspect","�����"));
	m_arrayTables.Add(CTableProperty("��0403ԭʼ��¼�ල���������ļ��ǼǱ�","RecordDegrade","�ļ���"));
	m_arrayTables.Add(CTableProperty("��0404ִ�о���Ѳ�ؼ���¼","ManagerInspect","��"));
	m_arrayTables.Add(CTableProperty("��0405��Ŀ������ִ�о���Ѳ�ؼ���¼","DeparmentInspectManager","��"));
	m_arrayTables.Add(CTableProperty("��0406��Ŀ�������ֳ��ලѲ�ؼ���¼","DeparmentInspectMonitor","��"));
	m_arrayTables.Add(CTableProperty("��0501�ɱ�������ͳ�Ʊ�","CostManage","��"));
	m_arrayTables.Add(CTableProperty("��1001SPS�첨������","SPSReceiverData","���"));
	m_arrayTables.Add(CTableProperty("��1002SPS�첨���ܽ�","SPSReceiverStat","�����"));
	m_arrayTables.Add(CTableProperty("��1003SPS�ڵ�����","SPSShotData","���"));
	m_arrayTables.Add(CTableProperty("��1004SPS�ڵ��ܽ�","SPSShotStat","�����"));
	m_arrayTables.Add(CTableProperty("��1005������ϸ����","ShotData","���"));
	m_arrayTables.Add(CTableProperty("��1006�����ܽ�����","ShotStat","���β��Ա��"));
	m_arrayTables.Add(CTableProperty("��1007�첨�����Ա�׼","ReceiverTestRuler","�첨���ͺ�"));
	m_arrayTables.Add(CTableProperty("��1008�첨����������","ReceiverTestData","���β��Ա��"));
	m_arrayTables.Add(CTableProperty("��1009�첨�������ܽ�","ReceiverTestStat","���β��Ա��"));
	m_arrayTables.Add(CTableProperty("��1010��������","WellDepthData","���β��Ա��"));
	m_arrayTables.Add(CTableProperty("��1011�����ܽ�","WellDapthStat","���β��Ա��"));
	m_arrayTables.Add(CTableProperty("��1012�����ռ��׼","YMDTestRuler","�����Ŀ"));
	m_arrayTables.Add(CTableProperty("��1013�����ռ�����","YMDTestData","���β��Ա��"));
	m_arrayTables.Add(CTableProperty("��1014�����ռ��ܽ�","YMDTestStat","���ڲ��Ա��"));
	m_arrayTables.Add(CTableProperty("��1015ҩ������","DynamiteData","���β��Ա��"));
	m_arrayTables.Add(CTableProperty("��1016ҩ���ܽ�","DynamiteStat","���β��Ա��"));
}


// CQCDBApp ��Ϣ�������

CString CQCDBApp::GetColNameField(CString sTable)
{
	if(sTable=="")return CString("");
	for(int i=0;i<m_arrayTables.GetCount ();i++)
	{
		CTableProperty &table=m_arrayTables.GetAt (i);
		if(table.sTableName == sTable)
		{
			return table.sColNameField ;
		}
	}

	AfxMessageBox("��δ����������!");
	return CString("");

}

CString CQCDBApp::GetTableSimpleName(CString sTable)
{
	if(sTable=="")return CString("");
	for(int i=0;i<m_arrayTables.GetCount ();i++)
	{
		CTableProperty &table=m_arrayTables.GetAt (i);
		if(table.sTableName == sTable)
		{
			return table.sSimpleName ;
		}
	}

	AfxMessageBox("��δ����������!");
	return CString("");

}



void CQCDBApp::OnCreateoridb()
{
	CMultiDocTemplate *pTemplate=GetTemplate("QCDB");
	if(!pTemplate)return;
	pTemplate->OpenDocumentFile (NULL);
}


void CQCDBApp::OnSetglobalinfo()
{
	if(!IsServer())
	{
		CPropertySheet			sheet("���ݿ����");
        CDlgInputServer			page1;
		CDlgGlobalProperty		page2;
		CDlgTranProperty		page3;
		CDlgInterfaceProperty	page4;
        CDlgUserInfo			page5;
		CDlgProjectProperty		page6;
		if(sheet.DoModal ()==IDCANCEL)return;

        sheet.AddPage (&page1);        
		sheet.AddPage (&page2);
		sheet.AddPage (&page3);
		sheet.AddPage (&page4);
        sheet.AddPage (&page5);
		sheet.AddPage (&page6);

		if(sheet.DoModal ()==IDOK)
		{
			SetProjectID();
		}
	}
	else
	{
		CPropertySheet			sheet("���ݿ����");
		CDlgInputServer			page1;
		CDlgLocalServerProperty page2;
		CDlgTranProperty		page3;
		CDlgInterfaceProperty	page4;
		CDlgUserInfo			page5;
		CDlgProjectProperty		page6;


		/*///////////////////////////////////
		//  ���������Ŀ����
		CDataBrowseDoc doc;
		CStringArray arrayFields;
		arrayFields.Add ("��Ŀ����");

		m_dt.GetData ("LOCAL",
						0,
						"��0101��Ŀ",
						"select * from ��0101��Ŀ",
						&arrayFields,
						&doc,
						GetMaxHandDownRecord());
		
		CStringArray *pRecord=NULL;
		for(int i=0;i<doc.GetRecordQty ();i++)
		{
			pRecord=doc.GetRecord (i);
			page5.AddProjectName (pRecord->GetAt (0));
		}
		//  ���������Ŀ����
		///////////////////////////////////*/

		sheet.AddPage (&page1);
		sheet.AddPage (&page2);
		sheet.AddPage (&page3);
		sheet.AddPage (&page4);
		sheet.AddPage (&page5);
		sheet.AddPage (&page6);


		if(sheet.DoModal ()==IDOK)
		{
			SetProjectID();

			///////////////////////////////////////////////////
			// ������ʾ��Ϣ����:
			///////////////////////////////////////////////////
			CMainFrame *pMain= (CMainFrame *)AfxGetMainWnd();
			pMain->ReShowInfoWnd();

			CString sFile;
			GetPar("QCDB_PASSWORD_FILE",sFile);
			SetPassword (sFile);
		}
		else
		{
			return ;
		}
	}

	InitiateNet();

}

void CQCDBApp::OnShowData()
{	
	CDataBrowseDoc * pDoc=NULL;
	CMultiDocTemplate *pTemplate=GetTemplate("DBBrowse");
	if(pTemplate!=NULL)
	{
		pDoc=(CDataBrowseDoc *)pTemplate->OpenDocumentFile (NULL);
		if(!pDoc)
		{
			ASSERT(false);
			return;
		}
		else
		{
			pDoc->OnModifyData ();
		}
	}
	else
	{
		ASSERT(false);
		return;
	}
}

void CQCDBApp::InitiateNet()
{
	bool bConnectServer=false;
	GetPar("QCDB_LINK_SERVER_AT_BEGIN",bConnectServer);

	if(IsServer())
	{
		m_dt.Initiate (true);
	}
	else
	{
		m_dt.Initiate (false);
	}

	if(bConnectServer)
	{
		m_dt.ConnectServers (IsServer());
	}
}

void CQCDBApp::OnOutputtable()
{
	CMultiDocTemplate* pDocTemplate=GetTemplate("ReportCreator");
	if(!pDocTemplate)
	{
		ASSERT(false);
		return;
	}

	pDocTemplate->OpenDocumentFile (NULL);
}

void CQCDBApp::OnConnectservers()
{
	m_dt.ConnectServers (IsServer());
}

void CQCDBApp::OnUserregister()
{
	CString sFile;
	if(IsServer())
	{
		GetPar("QCDB_PASSWORD_FILE",sFile);
		CMultiDocTemplate* pDocTemplate=GetTemplate("Password");
		if(!pDocTemplate)return;

		if(sFile!="")
		{
			pDocTemplate->OpenDocumentFile (sFile);
		}
		else
		{
			pDocTemplate->OpenDocumentFile (NULL);
		}
	}
	else
	{
		TRACEERROR("�ͻ��˲��߱����������!");
	}
	
}

bool CQCDBApp::SetPassword(CString sFile)
{
	if(sFile=="")return false;
	if(!m_password.Read (sFile))
	{
		return false;
	}

	return true;
}