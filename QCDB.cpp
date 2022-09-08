// QCDB.cpp : 定义应用程序的类行为。
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
1.如果是服务器版本，则在defines.h中定义：
        QCDB_SERVER.
程序本身以全局函数识别该符号：
        bool IsServer()
来判断是否服务器版本。

   如果是客户端版本，则不定义该符号。

2。如果使用Oracle,则在defines.h中定义：
   QCDB_ORACLE.
   如果使用Excel版本，则不作该定义

3。软件版本号的识别特区在
    SoftDog.cpp
    中。

4。软件狗版本在defines.h中定义DOG
*/
////////////////////////////////////////////////



// CQCDBApp

BEGIN_MESSAGE_MAP(CQCDBApp, CFHApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, CFHApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CFHApp::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, CFHApp::OnFilePrintSetup)
	ON_COMMAND(ID_CreateOriDB, OnCreateoridb)
	ON_COMMAND(ID_SetGlobalInfo, OnSetglobalinfo)
	ON_COMMAND(ID_GetDataFromServer, OnShowData)
	ON_COMMAND(ID_OutputTable, OnOutputtable)
	ON_COMMAND(ID_ConnectServers, OnConnectservers)
	ON_COMMAND(ID_UserRegister, OnUserregister)
END_MESSAGE_MAP()

// CQCDBApp 构造

CQCDBApp::CQCDBApp()
{
	EnableHtmlHelp();

	CreateTableProperty();

    CSplashWnd::SetCover (IDB_QCDB_COVER);


    /////////////////////////////////
    // 主参数文件：
    SetParFile(m_sWorkDir+"\\QCDB.par");

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
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


// 唯一的一个 CQCDBApp 对象

CQCDBApp theApp;

// CQCDBApp 初始化

BOOL CQCDBApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControls()。否则，将无法创建窗口。
	InitCommonControls();

	CFHApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)
	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CMultiDocTemplate* pDocTemplate=NULL;

	pDocTemplate = new CMultiDocTemplate(IDR_DBBrowse,
		RUNTIME_CLASS(CQCDBDataBrowseDoc),
		RUNTIME_CLASS(CDataBrowseFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CQCDBDataBrowseView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMultiDocTemplate(IDR_ReportCreator,
		RUNTIME_CLASS(CReportDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CReportView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	pDocTemplate = new CMultiDocTemplate(IDR_QCDBTYPE,
		RUNTIME_CLASS(CQCDBDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CQCDBView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMultiDocTemplate(IDR_DBChart,
		RUNTIME_CLASS(CDataBrowseDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CDataChartView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMultiDocTemplate(IDR_DataTransfer,
		RUNTIME_CLASS(CDataTransDoc),
		RUNTIME_CLASS(CDataTranFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CLinkingsView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	if(IsServer())
	{
		pDocTemplate = new CMultiDocTemplate(IDR_Password,
			RUNTIME_CLASS(CPasswordDoc),
			RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
			RUNTIME_CLASS(CPasswordView));
		if (!pDocTemplate)
			return FALSE;
		AddDocTemplate(pDocTemplate);
	}

	// 创建主 MDI 框架窗口
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



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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

// 用于运行对话框的应用程序命令
void CQCDBApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CQCDBApp::CreateTableProperty()
{
	m_arrayTables.Add(CTableProperty("表0000监理人员基本情况统计表","Monitor","姓名"));
	m_arrayTables.Add(CTableProperty("表0001技术人员基本情况统计表","Technician","姓名"));
	m_arrayTables.Add(CTableProperty("表0101项目","Project","项目名称"));
	m_arrayTables.Add(CTableProperty("表0102项目地震采集施工参数一览表","ProjectAquiPar","项目编号"));
	m_arrayTables.Add(CTableProperty("表0103项目设计质量统计表","ProjectQuality","项目编号"));
	m_arrayTables.Add(CTableProperty("表0104目的层指标统计表","ProjectTarget","项目编号"));
	m_arrayTables.Add(CTableProperty("表0105干扰波指标","ProjectNoise","项目编号"));
	m_arrayTables.Add(CTableProperty("表0106开工验收检查表","ProjectAccept","项目编号"));
	m_arrayTables.Add(CTableProperty("表0107主要技术人员到位情况检查表","ProjectTecnician","项目编号"));
	m_arrayTables.Add(CTableProperty("表0108主要设备到位情况检查表","ProjectEquipment","项目编号"));
	m_arrayTables.Add(CTableProperty("表0109试验工作监督统计表","ProjectTest","项目编号"));
	m_arrayTables.Add(CTableProperty("表0201测线","Line","测线名称"));
	m_arrayTables.Add(CTableProperty("表0301监理工作日报","MonitorDaily","日"));
	m_arrayTables.Add(CTableProperty("表0302测量监督日报","SurveyDaily","日"));
	m_arrayTables.Add(CTableProperty("表0303仪器监督日报","InstrumentDaily","日"));
	m_arrayTables.Add(CTableProperty("表0304QC报告入库清单","QCReportDaily","日"));
	m_arrayTables.Add(CTableProperty("表0401施工工序监督检查表","WorkPrecedure","检查日"));
	m_arrayTables.Add(CTableProperty("表0402监督检查备忘录","MonitorInspect","检查日"));
	m_arrayTables.Add(CTableProperty("表0403原始记录监督复评降级文件登记表","RecordDegrade","文件号"));
	m_arrayTables.Add(CTableProperty("表0404执行经理巡回检查记录","ManagerInspect","日"));
	m_arrayTables.Add(CTableProperty("表0405项目经理部对执行经理巡回检查记录","DeparmentInspectManager","日"));
	m_arrayTables.Add(CTableProperty("表0406项目经理部对现场监督巡回检查记录","DeparmentInspectMonitor","日"));
	m_arrayTables.Add(CTableProperty("表0501成本管理月统计表","CostManage","月"));
	m_arrayTables.Add(CTableProperty("表1001SPS检波点资料","SPSReceiverData","点号"));
	m_arrayTables.Add(CTableProperty("表1002SPS检波点总结","SPSReceiverStat","检测日"));
	m_arrayTables.Add(CTableProperty("表1003SPS炮点资料","SPSShotData","点号"));
	m_arrayTables.Add(CTableProperty("表1004SPS炮点总结","SPSShotStat","检测日"));
	m_arrayTables.Add(CTableProperty("表1005单炮详细资料","ShotData","点号"));
	m_arrayTables.Add(CTableProperty("表1006单炮总结资料","ShotStat","本次测试编号"));
	m_arrayTables.Add(CTableProperty("表1007检波器测试标准","ReceiverTestRuler","检波器型号"));
	m_arrayTables.Add(CTableProperty("表1008检波器测试数据","ReceiverTestData","本次测试编号"));
	m_arrayTables.Add(CTableProperty("表1009检波器测试总结","ReceiverTestStat","本次测试编号"));
	m_arrayTables.Add(CTableProperty("表1010井深资料","WellDepthData","本次测试编号"));
	m_arrayTables.Add(CTableProperty("表1011井深总结","WellDapthStat","本次测试编号"));
	m_arrayTables.Add(CTableProperty("表1012年月日检标准","YMDTestRuler","检测项目"));
	m_arrayTables.Add(CTableProperty("表1013年月日检资料","YMDTestData","本次测试编号"));
	m_arrayTables.Add(CTableProperty("表1014年月日检总结","YMDTestStat","本期测试编号"));
	m_arrayTables.Add(CTableProperty("表1015药量资料","DynamiteData","本次测试编号"));
	m_arrayTables.Add(CTableProperty("表1016药量总结","DynamiteStat","本次测试编号"));
}


// CQCDBApp 消息处理程序

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

	AfxMessageBox("尚未加入表格属性!");
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

	AfxMessageBox("尚未加入表格属性!");
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
		CPropertySheet			sheet("数据库参数");
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
		CPropertySheet			sheet("数据库参数");
		CDlgInputServer			page1;
		CDlgLocalServerProperty page2;
		CDlgTranProperty		page3;
		CDlgInterfaceProperty	page4;
		CDlgUserInfo			page5;
		CDlgProjectProperty		page6;


		/*///////////////////////////////////
		//  获得所有项目名称
		CDataBrowseDoc doc;
		CStringArray arrayFields;
		arrayFields.Add ("项目名称");

		m_dt.GetData ("LOCAL",
						0,
						"表0101项目",
						"select * from 表0101项目",
						&arrayFields,
						&doc,
						GetMaxHandDownRecord());
		
		CStringArray *pRecord=NULL;
		for(int i=0;i<doc.GetRecordQty ();i++)
		{
			pRecord=doc.GetRecord (i);
			page5.AddProjectName (pRecord->GetAt (0));
		}
		//  获得所有项目名称
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
			// 重新显示信息窗口:
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
		TRACEERROR("客户端不具备口令管理功能!");
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