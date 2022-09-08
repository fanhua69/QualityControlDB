// QCDB.h : QCDB 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error 在包含用于 PCH 的此文件之前包含“stdafx.h” 
#endif

#include "resource.h"       // 主符号


// CQCDBApp:
// 有关此类的实现，请参阅 QCDB.cpp
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
 

// 重写
public:
	virtual BOOL	InitInstance();
	bool			InitiateClientDataTransfer();

	CDataTransfer   m_dt;

public:
	CString GetColNameField(CString sTable);
	CString GetTableSimpleName(CString sTable);

	void InitiateNet();

// 实现
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

