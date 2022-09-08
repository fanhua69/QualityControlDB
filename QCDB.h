// QCDB.h : QCDB Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CQCDBApp:
// �йش����ʵ�֣������ QCDB.cpp
//
#include "FHApp.h"
#include "afxtempl.h"



class CTableProperty
{
public:
	CString sTableName;
	CString sSimpleName;
	CString sColNameField;

	CTableProperty()
	{
		sTableName="";
		sSimpleName="";
		sColNameField="";
	};

	CTableProperty(	CString sTableNameTag,
					CString sSimpleNameTag,
					CString sColNameFieldTag)
	{
		sTableName=sTableNameTag;
		sSimpleName=sSimpleNameTag;
		sColNameField=sColNameFieldTag;
	};
};

#include "DataTransfer.h"
#include "passwordmanager.h"

class CQCDBApp : public CFHApp
{
public:
	CQCDBApp();
	~CQCDBApp();

	CPasswordManager	m_password;
	bool SetPassword(CString sFile);

protected:
	CArray <CTableProperty,CTableProperty&> m_arrayTables;
	void CreateTableProperty();
 

// ��д
public:
	virtual BOOL	InitInstance();
	bool			InitiateClientDataTransfer();

	CDataTransfer   m_dt;

public:
	CString GetColNameField(CString sTable);
	CString GetTableSimpleName(CString sTable);

	void InitiateNet();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnCreateoridb();
	afx_msg void OnSetglobalinfo();
	afx_msg void OnShowData();
	afx_msg void OnOutputtable();
	afx_msg void OnConnectservers();
	afx_msg void OnUserregister();
};

#include "qcglobal.h"
#include "fhmainfrm.h"
#include "FHApp.h"

extern CQCDBApp theApp;

