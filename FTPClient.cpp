#include "StdAfx.h"
#include ".\ftpclient.h"

CFTPClient::CFTPClient(void)
{
	m_pInetSession=NULL;
	m_pRemoteFinder=NULL;

	m_pListLocalFiles=NULL;
	m_pListRemoteFiles=NULL;
}

CFTPClient::~CFTPClient(void)
{
	Reset();
}

void CFTPClient::Reset()
{
	if(m_pInetSession)
	{
		delete m_pInetSession;
		m_pInetSession=NULL;
	}

	if(m_pRemoteFinder)
	{
		delete m_pRemoteFinder;
		m_pRemoteFinder=NULL;
	}
}

void CFTPClient::SetNames(CString sAppName,
						  CString sServerName,
						  CString sUserName,
						  CString sPassword)
{
	m_sAppName		=sAppName;
	m_strServer		=sServerName;
	m_strUserName	=sUserName;
	m_strPassword	=sPassword;
}

void CFTPClient::SetRemoteListCtrl(CListCtrl *pListCtrl)
{
	m_pListRemoteFiles=pListCtrl;
}

void CFTPClient::Connect()
{
	if(m_sAppName==""||m_strServer==""||m_strUserName==""||m_strPassword=="")return;

	Reset();

	m_pInetSession=new CInternetSession(m_sAppName,1,PRE_CONFIG_INTERNET_ACCESS);
	
	try
	{
		m_pFTPConnection=m_pInetSession->GetFtpConnection(m_strServer,
			m_strUserName,
			m_strPassword);

	}

	catch(CInternetException *pEx)
	{
		TCHAR szError[1024];
		if(pEx->GetErrorMessage(szError,1024))
			AfxMessageBox(szError);
		else
			AfxMessageBox("There was an exception");

		pEx->Delete ();

		m_pFTPConnection=NULL;

		return;
	}

	m_pRemoteFinder=new CFtpFileFind(m_pFTPConnection);

}

void CFTPClient::BrowseDir(CString strDir, 
						   CListCtrl *pListCtrl,
						   CFileFind *pFinder,
						   CArray<FILEITEM,FILEITEM&>*pFilesArr)
{
	pListCtrl->DeleteAllItems ();
	pFilesArr->RemoveAll ();

	int nIndex=0;
	CString szDir=strDir;
	if(szDir.Right (1)!="\\")
	{
		szDir+="\\";
	}
	szDir+=".";

	// Find files under the dir:
	BOOL res=pFinder->FindFile(szDir);
	while(res)
	{
		res=pFinder->FindNextFile ();

		// is a dir:
		if(pFinder->IsDirectory ()&&!pFinder->IsDots())
		{
			FILEITEM fileitem;
			fileitem.nItem = nIndex;
			fileitem.bDir = true;
			fileitem.strFileName= pFinder->GetFileName ();
			pFilesArr->Add (fileitem);
			AddItem(pListCtrl,nIndex,TRUE,pFinder->GetFileName ());
		}

		// is a file:
		else if(!pFinder->IsDirectory ()&&!pFinder->IsDots())
		{
			FILEITEM fileitem;
			fileitem.nItem = nIndex;
			fileitem.bDir = FALSE;
			fileitem.strFileName= pFinder->GetFileName ();
			pFilesArr->Add (fileitem);
			AddItem(pListCtrl,nIndex,FALSE,pFinder->GetFileName ());
		}
		nIndex++;
	}
}

/////////////////////////////////////////
// ���б������һ����¼
/////////////////////////////////////////
void CFTPClient:: AddItem(	CListCtrl	*pListCtrl,
							int			nIndex,
							BOOL		bDir,
							CString		strText)
{
	LV_ITEM item;
	int iActualItem;
	
	for(int iSubItem=0;iSubItem<2;iSubItem++)
	{
		item.mask = LVIF_TEXT|(iSubItem==0?LVIF_IMAGE:0);
		item.iItem =(iSubItem==0)?nIndex:iActualItem;
		item.iSubItem =iSubItem;
		switch(iSubItem)
		{
		case 0:
			item.pszText =(LPTSTR)(LPCTSTR)strText;
			break;
		case 1:
			if(bDir)
				item.pszText = "�ļ���";
			else
				item.pszText = "�ļ�";
			break;
		}

		if(iSubItem==0)
		{
			iActualItem=pListCtrl->InsertItem (&item);
		}
		else
		{
			pListCtrl->SetItem (&item);
		}
	}
}

void CFTPClient:: DownFile(FILEITEM fileitem)
{
	if(fileitem.bDir =TRUE)
	{
		AfxMessageBox("��ѡ���ļ�����!");
	}
	else
	{
		// ��ʽ���ļ���:
		CString sLocalFile,sRemoteFile;
		
		sRemoteFile.Format ("%s\\%s",m_pRemoteFinder->GetRoot (),fileitem.strFileName );
		sLocalFile.Format ("%s\\%s",m_LocalFinder.GetRoot (),fileitem.strFileName );

		//���أ�
		if(m_pFTPConnection->GetFile (sRemoteFile, sLocalFile))
		{
			CString strMsg;
			strMsg.Format ("�����ļ�:%s�ɹ�!",fileitem.strFileName );
			AfxMessageBox(strMsg);
		}
	}
}


void CFTPClient::DownAllFile()
{
	if(m_pFTPConnection==NULL)
	{
		return;
	}

	POSITION pos=m_pListRemoteFiles->GetFirstSelectedItemPosition ();
	if(pos==NULL)
	{
		AfxMessageBox("��ѡ��Ҫ���ص��ļ�!");
	}
	else
	{
		while(pos)
		{
			int nItem=m_pListRemoteFiles->GetNextSelectedItem (pos);
			DownFile(m_arrRemoteFiles.GetAt(nItem));
		}
	}
}

void CFTPClient::UpFile(FILEITEM fileitem)
{
	if(fileitem.bDir ==TRUE)
	{
		AfxMessageBox("ֻ��ѡ���ļ�����!");
		return;
	}

	CString sLocalFile, sRemoteFile;
	sRemoteFile.Format ("%s\\%s",m_pRemoteFinder->GetRoot (),fileitem.strFileName );
	sLocalFile.Format ("%s\\%s",m_LocalFinder.GetRoot (),fileitem.strFileName );

	if(m_pFTPConnection->PutFile (sLocalFile,sRemoteFile))
	{
		CString s;
		s.Format ("�ϴ��ļ� %s �ɹ�!",fileitem.strFileName);
		AfxMessageBox(s);
	}
}



void CFTPClient::UpAllFile()
{
	if(m_pFTPConnection==NULL)
	{
		return;
	}

	POSITION pos=m_pListLocalFiles->GetFirstSelectedItemPosition ();
	if(pos==NULL)
	{
		AfxMessageBox("��ѡ��Ҫ�ϴ����ļ�!");
	}
	else
	{
		while(pos)
		{
			int nItem=m_pListLocalFiles->GetNextSelectedItem (pos);
			UpFile(m_arrLocalFiles.GetAt(nItem));
		}
	}
}
