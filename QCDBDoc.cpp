// QCDBDoc.cpp :  CQCDBDoc 类的实现
//

#include "stdafx.h"
#include "QCDB.h"

#include "QCDBDoc.h"
#include "FHCGlobal.h"

#include "atlpath.h"
#include "DataBaseManager.h"
#include "treeviewdb.h"
#include "fhmainfrm.h"
#include "QCGlobal.h"

#include "defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CQCDBDoc

IMPLEMENT_DYNCREATE(CQCDBDoc, CDocument)

BEGIN_MESSAGE_MAP(CQCDBDoc, CDocument)
END_MESSAGE_MAP()


// CQCDBDoc 构造/析构

CQCDBDoc::CQCDBDoc()
{
	// TODO: 在此添加一次性构造代码

}

CQCDBDoc::~CQCDBDoc()
{
}

//BOOL CQCDBDoc::OnNewDocument()
//{
//	if (!CDocument::OnNewDocument())
//		return FALSE;
//
//	// TODO: 在此添加重新初始化代码
//	// (SDI 文档将重用该文档)
//
//	return TRUE;
//}




// CQCDBDoc 序列化

void CQCDBDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CQCDBDoc 诊断

#ifdef _DEBUG
void CQCDBDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CQCDBDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CQCDBDoc 命令

BOOL CQCDBDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  Add your specialized creation code here

	return TRUE;
}

BOOL CQCDBDoc::OnNewDocument()
{
	return MakeNewDB();
}

BOOL CQCDBDoc::MakeNewDB()
{
	// TODO: Add your specialized code here and/or call the base class
#ifdef QCDB_ORACLE
	MakeNewOracleDB();
#else
    MakeNewAccessDB();
#endif

	CTreeViewDB *pTree=(CTreeViewDB*)GetTree("TreeViewDB");
	if(!pTree)
	{
		ASSERT(false);
	}
	else
	{
		pTree->OpenDataBase (true);
	}
	return false;
}

bool CQCDBDoc::MakeNewOracleDB()
{
	CString sDBName=GetDBName();
	
	CString sBlueDBAccess=GetBlueDBName();
	CString sAccessPath=GetWorkDir()+"\\"+sBlueDBAccess;
	if(!ATLPath::FileExists(sAccessPath))
	{
		sAccessPath=GetFileForOpen("请给出文件位置:"+sBlueDBAccess,"MDB");
		if(sAccessPath=="")return false;
	}
	
	// 需要首先注册，才能获得表名：
	CDataBaseManager db;
	if(!db.RegisterDBSrc (sAccessPath,"temp","delete me",true))
	{
		AfxMessageBox("错误：无法注册数据库!");
		return false;
	}

#ifdef DOG
    CFHApp *pApp=(CFHApp *)AfxGetApp();
    if(!pApp->m_dog.CheckRand (0))
    {
        return false;
    }
    pApp->m_dog.WriteRand (0);
#endif


	bool b= CDataBaseManager::CreateTablesFromBlueDB (sDBName,"temp");

	db.RegisterDBSrc (sAccessPath,"temp","delete me",false);


	return b;
}

bool CQCDBDoc::MakeNewAccessDB()
{
#ifdef DOG
    CFHApp *pApp=(CFHApp*)AfxGetApp();
    if(!pApp->m_dog .m_bMarkChecked )
    {
        return false;
    }
#endif

    // Get the blue DB file name and the new DB Name:
	CString sBlueDBAccess=GetBlueDBName();
	CString sAccessPath=GetWorkDir()+"\\"+sBlueDBAccess;
	if(!ATLPath::FileExists(sAccessPath))
	{
		sAccessPath=GetFileForOpen("请给出源数据库文件位置(*.mdb)","MDB");
		if(sAccessPath=="")return false;
	}
	CString sNewAccess=GetFileForSave("请给出新数据库文件存放位置和名称(*.mdb)","MDB");
	if(sNewAccess=="")return false;


    // Create the new database
    ::CopyFile(sAccessPath,sNewAccess,false);

    // Register the new DB:
	CDataBaseManager db;
	db.RegisterDBSrc (sNewAccess,GetDBName(),GetDBDiscription(),false);  // 删除ODBC注册

	if(!db.RegisterDBSrc (sNewAccess,GetDBName(),GetDBDiscription(),true))
	{
		AfxMessageBox("错误：无法注册数据库!");
		return false;
	}

    AddPar("ACCESS_SOURCE_TABLE_PATHNAME",sNewAccess);

    // Clear the new database:
    CDataBaseManager dbNew;
    dbNew.Initiate(GetDBName());
    dbNew.ClearDB();

    // return:	
	AfxMessageBox("恭喜：已经建好原始数据库并注册完毕!");
	return false; // 不显示数据库视．
}

CString CQCDBDoc::GetAccessSrcFileName()
{
    CString sAccessPath;
    GetPar("ACCESS_SOURCE_TABLE_PATHNAME",sAccessPath);
    return sAccessPath;
}

bool CQCDBDoc::ExistAccessSourceFile()
{
    CString sAccessPath=GetAccessSrcFileName();
    bool bExists=ATLPath::FileExists(sAccessPath);
    return bExists;
}