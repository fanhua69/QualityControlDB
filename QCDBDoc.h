// QCDBDoc.h :  CQCDBDoc ��Ľӿ�
//


#pragma once

class CQCDBDoc : public CDocument
{
protected: // �������л�����
	CQCDBDoc();
	DECLARE_DYNCREATE(CQCDBDoc)

// ����
public:

// ����
public:

// ��д
	public:
//	virtual BOOL OnNewDocument();
	virtual void    Serialize(CArchive& ar);
	static BOOL     MakeNewDB();
	static bool     MakeNewAccessDB();
	static bool     MakeNewOracleDB();

    static CString  GetAccessSrcFileName();
    static bool     ExistAccessSourceFile();


// ʵ��
public:
	virtual ~CQCDBDoc();
#ifdef _DEBUG
	virtual void    AssertValid() const;
	virtual void    Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnNewDocument();
};


