// tableset.h : interface of the CFHTable class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

/////////////////////////////////////////////////////////////////////////////

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

class CFHTableProperty
{
public:
	CString sQualifierParam ;
	CString sOwnerParam ;
	CString sNameParam ;
	CString sTypeParam ;
};

#include "afxdb.h"

class CFHTable : public CRecordset
{
DECLARE_DYNAMIC(CFHTable)

public:
	CFHTable(CDatabase* pDatabase = NULL);
	~CFHTable();

	BOOL Open(UINT nOpenType = snapshot      , LPCSTR lpszSQL = NULL,
		DWORD dwOptions = readOnly);

	CDatabase m_database;
	CString   m_sDBName;
// Field/Param Data
	//{{AFX_FIELD(CFHTable, CRecordset)
	CString m_strQualifier;
	CString m_strOwner;
	CString m_strName;
	CString m_strType;
	CString m_strRemarks;
	//}}AFX_FIELD

	CString m_strQualifierParam;
	CString m_strOwnerParam;
	CString m_strNameParam;
	CString m_strTypeParam;

	CFHTableProperty *m_pTableProperty;

	bool Open(CString sDBName);
	BOOL GetTableNames(CStringArray &array);
	long GetTableQty();


// Implementation
protected:
	virtual CString GetDefaultConnect();    // default connection string
	virtual CString GetDefaultSQL();    // default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
};
