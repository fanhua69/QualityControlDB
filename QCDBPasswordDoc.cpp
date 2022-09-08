// QCDBPasswordDoc.cpp : implementation file
//

#include "stdafx.h"
#include "QCDB.h"
#include "QCDBPasswordDoc.h"


// CQCDBPasswordDoc

IMPLEMENT_DYNCREATE(CQCDBPasswordDoc, CPasswordDoc)

CQCDBPasswordDoc::CQCDBPasswordDoc()
{
}

BOOL CQCDBPasswordDoc::OnNewDocument()
{
	if (!CPasswordDoc::OnNewDocument())
		return FALSE;
	return TRUE;
}

CQCDBPasswordDoc::~CQCDBPasswordDoc()
{
}


BEGIN_MESSAGE_MAP(CQCDBPasswordDoc, CPasswordDoc)
END_MESSAGE_MAP()


// CQCDBPasswordDoc diagnostics

#ifdef _DEBUG
void CQCDBPasswordDoc::AssertValid() const
{
	CPasswordDoc::AssertValid();
}

void CQCDBPasswordDoc::Dump(CDumpContext& dc) const
{
	CPasswordDoc::Dump(dc);
}
#endif //_DEBUG


// CQCDBPasswordDoc serialization

void CQCDBPasswordDoc::Serialize(CArchive& ar)
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

// CQCDBPasswordDoc commands
BOOL CQCDBPasswordDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
   if(CPasswordDoc::OnSaveDocument(lpszPathName))
   {
       CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
       pApp->SetPassword(lpszPathName);
       return true;
   }
   else
   {
       return false;
   }
}
