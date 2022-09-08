// QCDBDoc.cpp :  CQCDBDoc ���ʵ��
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


// CQCDBDoc ����/����

CQCDBDoc::CQCDBDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CQCDBDoc::~CQCDBDoc()
{
}

//BOOL CQCDBDoc::OnNewDocument()
//{
//	if (!CDocument::OnNewDocument())
//		return FALSE;
//
//	// TODO: �ڴ�������³�ʼ������
//	// (SDI �ĵ������ø��ĵ�)
//
//	return TRUE;
//}




// CQCDBDoc ���л�

void CQCDBDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CQCDBDoc ���

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


// CQCDBDoc ����

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
		sAccessPath=GetFileForOpen("������ļ�λ��:"+sBlueDBAccess,"MDB");
		if(sAccessPath=="")return false;
	}
	
	// ��Ҫ����ע�ᣬ���ܻ�ñ�����
	CDataBaseManager db;
	if(!db.RegisterDBSrc (sAccessPath,"temp","delete me",true))
	{
		AfxMessageBox("�����޷�ע�����ݿ�!");
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
		sAccessPath=GetFileForOpen("�����Դ���ݿ��ļ�λ��(*.mdb)","MDB");
		if(sAccessPath=="")return false;
	}
	CString sNewAccess=GetFileForSave("����������ݿ��ļ����λ�ú�����(*.mdb)","MDB");
	if(sNewAccess=="")return false;


    // Create the new database
    ::CopyFile(sAccessPath,sNewAccess,false);

    // Register the new DB:
	CDataBaseManager db;
	db.RegisterDBSrc (sNewAccess,GetDBName(),GetDBDiscription(),false);  // ɾ��ODBCע��

	if(!db.RegisterDBSrc (sNewAccess,GetDBName(),GetDBDiscription(),true))
	{
		AfxMessageBox("�����޷�ע�����ݿ�!");
		return false;
	}

    AddPar("ACCESS_SOURCE_TABLE_PATHNAME",sNewAccess);

    // Clear the new database:
    CDataBaseManager dbNew;
    dbNew.Initiate(GetDBName());
    dbNew.ClearDB();

    // return:	
	AfxMessageBox("��ϲ���Ѿ�����ԭʼ���ݿⲢע�����!");
	return false; // ����ʾ���ݿ��ӣ�
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