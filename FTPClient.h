#pragma once

#include "afxinet.h"
#include "afxtempl.h"

struct FILEITEM
{
	int nItem;
	BOOL bDir;
	CString strFileName;
};

class CFTPClient
{
public:
	CFTPClient(void);
	~CFTPClient(void);

	void Connect();
	void SetRemoteListCtrl(CListCtrl *pListCtrl);
	
	void SetNames(	CString sAppName,
					CString sServerName,
					CString sUserName,
					CString sPassword);

	void BrowseDir(	CString strDir, 
					CListCtrl *pListCtrl,
					CFileFind *pFinder,
					CArray<FILEITEM,FILEITEM&>*pFileArr);

	void AddItem(	CListCtrl	*pListCtrl,
					int			nIndex,
					BOOL		bDir,
					CString		strText);
	
	void DownFile(	FILEITEM	fileitem);
	void DownAllFile();
	void UpFile(FILEITEM item);
	void UpAllFile();


protected:
	CString m_sAppName;
	CString m_strServer;
	CString m_strUserName;
	CString m_strPassword;

	CListCtrl *m_pListRemoteFiles;
	CListCtrl *m_pListLocalFiles;

	CArray <FILEITEM,FILEITEM&> m_arrRemoteFiles;
	CArray <FILEITEM,FILEITEM&> m_arrLocalFiles;

protected:
	CInternetSession*	m_pInetSession;
	CFtpConnection*		m_pFTPConnection;
	CFtpFileFind*		m_pRemoteFinder;
	CFileFind			m_LocalFinder;

	void Reset();

};
