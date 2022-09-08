#pragma once


#include "PasswordDoc.h"

class CQCDBPasswordDoc : public CPasswordDoc
{
	DECLARE_DYNCREATE(CQCDBPasswordDoc)

public:
	CQCDBPasswordDoc();
	virtual ~CQCDBPasswordDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnNewDocument();

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
};
