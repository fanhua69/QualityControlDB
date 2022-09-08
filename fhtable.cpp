// sqltable.cpp : implementation of the CFHTable class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.


#include "stdafx.h"
#include "fhtable.h"
#include "fhmainfrm.h"
#include "qcglobal.h"
#include "QCDBDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CFHTable implementation

IMPLEMENT_DYNAMIC(CFHTable, CRecordset)

extern char gConnectString[1000];

CFHTable::CFHTable(CDatabase* pDatabase)
	: CRecordset(pDatabase)
{
	//{{AFX_FIELD_INIT(CFHTable)
	m_strQualifier = "";
	m_strOwner = "";
	m_strName = "";
	m_strType = "";
	m_strRemarks = "";
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_strQualifierParam = "";
	m_strOwnerParam = "";
	m_strNameParam = "";
	m_strTypeParam = "";
	m_sDBName="";


	m_pTableProperty=NULL;
}

CFHTable::~CFHTable()
{
	if(m_pTableProperty)
	{
		delete []m_pTableProperty;
	}
}



BOOL CFHTable::Open(	UINT    nOpenType, 
					    LPCSTR  lpszSQL,
					    DWORD   /*dwOptions*/)
{
	ASSERT(lpszSQL == NULL);
	lpszSQL;

#ifndef QCDB_ORACLE
    if(!CQCDBDoc::ExistAccessSourceFile())
    {
        CString sTable=CQCDBDoc::GetAccessSrcFileName();
        if(sTable!="")
        {
            AfxMessageBox("错误：ODBC的Access源数据表不存在:"+sTable);
        }
        return false;
    }
#endif

	RETCODE nRetCode=0;	
	bool bOpened=false;
    CString sUserName="admin";
    CString sPassword=::GetDataBasePassword();
    if(strcmp(gConnectString,"EMPTY")==0)
    {
        sprintf(gConnectString,"ODBC;USER=%s;PWD=%s",sUserName,sPassword);
    }

	if(m_sDBName!="")
	{
		try
		{
			bOpened=m_database.Open (m_sDBName,false,false,_T( gConnectString ));
			if(!bOpened)return false;
            strcpy(gConnectString,m_database.GetConnect());

            ::RetrieveDataBasePassward(m_database);

			m_pDatabase = &m_database;
		}

		catch(CDBException* pException)
		{
			TRACEERROR("错误：无法打开数据库!\r\n错误信息:"+pException->m_strError);
			return false;
		}
	}

	// Cache state info and allocate hstmt
	SetState(nOpenType,NULL,noDirtyFieldCheck);
	if (!AllocHstmt())
		return FALSE;

	TRY
	{
		OnSetOptions(m_hstmt);
		AllocStatusArrays();

		// call the ODBC catalog function with data member params
		AFX_SQL_ASYNC(this, (::SQLTables)(m_hstmt,
			(m_strQualifierParam.IsEmpty()? (UCHAR FAR *)NULL: (UCHAR FAR *)(const char*)m_strQualifierParam), SQL_NTS,
			(m_strOwnerParam.IsEmpty()? (UCHAR FAR *)NULL: (UCHAR FAR *)(const char*)m_strOwnerParam), SQL_NTS,
			(m_strNameParam.IsEmpty()? (UCHAR FAR *)NULL: (UCHAR FAR *)(const char*)m_strNameParam), SQL_NTS,
			(m_strTypeParam.IsEmpty()? (UCHAR FAR *)NULL: (UCHAR FAR *)(const char*)m_strTypeParam), SQL_NTS));
		if (!Check(nRetCode))
			ThrowDBException(nRetCode, m_hstmt);

		// Allocate memory and cache info
		AllocAndCacheFieldInfo();
		AllocRowset();

		// Fetch the first row of data
		MoveNext();

		// If EOF, result set is empty, set BOF as well
		m_bBOF = m_bEOF;
	}

	CATCH_ALL(e)
	{
		Close();
		THROW_LAST();
	}
	END_CATCH_ALL

	return TRUE;
}

CString CFHTable::GetDefaultConnect()
{
	return "ODBC;DSN=jldb;UID=SYSTEM;PWD=COMPUTER";
	//return "ODBC;";
}

CString CFHTable::GetDefaultSQL()
{
	// should SQLTables directly, so GetSQL should never be called
	//ASSERT(FALSE);
	//SQLTables
	return "";
}

void CFHTable::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CFHTable)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, "table_qualifier", m_strQualifier);
	RFX_Text(pFX, "table_owner", m_strOwner);
	RFX_Text(pFX, "table_name", m_strName);
	RFX_Text(pFX, "table_type", m_strType);
	RFX_Text(pFX, "remarks", m_strRemarks);
	//}}AFX_FIELD_MAP
}

BOOL CFHTable::GetTableNames(CStringArray &array)
{
	if(m_pTableProperty)
	{
		delete []m_pTableProperty;
		m_pTableProperty=NULL;
	}
	int iTableQty=GetTableQty();
	m_pTableProperty=new CFHTableProperty[iTableQty+2];

	TRY
	{

		MoveFirst ();
		while(!IsEOF() )
		{
			if(m_strType=="TABLE")
			{
				array.Add (this->m_strName);
			}
			MoveNext();
		}
	}

	CATCH_ALL(e)
	{
		return FALSE;
	}
	END_CATCH_ALL

	return TRUE;

}

long CFHTable::GetTableQty()
{
	int iTableQty=0;
	TRY
	{
		MoveFirst ();
		iTableQty=0;
		while(!IsEOF() )
		{
			if(m_strType=="TABLE")
			{
				iTableQty++; 
			}
			MoveNext();
		}
	}

	CATCH_ALL(e)
	{
		return FALSE;
	}
	END_CATCH_ALL

	return iTableQty;

}


bool CFHTable::Open(CString sDBName)
{
	m_sDBName=sDBName;
	return Open();
}



			/*virtual BOOL Open(
   LPCTSTR lpszDSN,
   BOOL bExclusive = FALSE,
   BOOL bReadOnly = FALSE,
   LPCTSTR lpszConnect = _T("ODBC;"),
   BOOL bUseCursorLib = TRUE 
);*/
