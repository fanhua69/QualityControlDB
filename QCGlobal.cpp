 #include "stdafx.h"
// QCDB.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "rasdlg.h"
#include "fhtable.h"
#include "QCDB.h"
#include "qcglobal.h"
#include "StringExtractor.h"
#include "fhcglobal.h"
#include "passwordManager.h"
#include "Connection.h"
#include "FHMainFrm.h"
#include "math.h"
#include "defines.h"

CStringArray    gArrayMonitorNames,gArrayProjectNames;
CStringArray    gArrayTechnicianNames,gArrayInstNames;
CStringArray    gArrayProjectNoForSurveyLines,gArraySurveyLineNamesOfProject;
CStringArray    gArrayAllLineNames;
char gConnectString[1000]="EMPTY";

#ifdef QCDB_SERVER
	bool	IsServer()
	{ 
		return true;
	};
#else
	bool	IsServer()
	{ 
		return false;
	};
#endif

CString GetIDFieldName()
{
	return CString("���");
}

void GetHandedInField(CString &sName, CString &sYesValue)
{
	sName="���ϴ�������";
	sYesValue="Y";
}

CString GetDBName()
{
	if(IsServer())
	{
		return CString("jldb-server");
	}
	else
	{
		return CString("jldb-client");
	}
}

bool  GetTableNames(CStringArray &array)
{
#ifdef QCDB_ORACLE
		array.Add("��Ŀ");
		array.Add("����");
		array.Add("��Ա");
		array.Add("�ල");
#else
		CFHTable t;
		if(!t.Open (GetDBName()))
		{
			return false;
		}

		t.GetTableNames(array);
#endif
	return true ;
}

void GetReportNames(CStringArray &array)
{
	array.Add ("��01��̽������Ŀ��ƹ�����ͳ�Ʊ�");       // 1
	array.Add ("��02�������ָ�ꡢĿ�Ĳ�ָ�ꡢ��Ҫ���Ų�ָ��ͳ�Ʊ�");  //2
	array.Add ("��03��̽������Ŀ���������ܱ���");  //3
	array.Add ("��04��̽������Ŀ���������±���");  //4
	array.Add ("��05��̽���̲���רҵ�ල�ܱ���");  //5 
	array.Add ("��06��̽��������רҵ�ල�ܱ�");    //6
	array.Add ("��07��̽���̿������ռල����");	//7
	array.Add ("��08��̽����ʩ������ල����");	//8
	array.Add ("��09��̽���̼ල��鱸��¼");		//9
	array.Add ("��10��̽���̼ල��������ͳ�Ʒ�����");	//10
	array.Add ("��11��̽���̼ල���Ĺ������ܱ�");		//11
	array.Add ("��12����ɼ�ʩ������һ����");			//12
	array.Add ("��13������Ҫ������Ա��λ�������");	//13
	array.Add ("��14������Ҫ�豸��λ�������");		//14
	array.Add ("��15��ĿҰ��ɼ����鹤���ලͳ�Ʊ�");	//15
	array.Add ("��16��ĿҰ��ɼ�ʩ�������ලͳ�Ʊ�");		//16
	array.Add ("��17��ĿҰ��ɼ�ʩ�����ʵ�﹤�����ලͳ�Ʊ�");	//17
	array.Add ("��18����̽��������ͳ�Ʊ�");					//18
	array.Add ("��19����ɼ����Ӽ�¼�����������ձ�");			//19
	array.Add ("��20��̽����ԭʼ��¼�ල���������ļ��ǼǱ�");	//20
	array.Add ("��21̽��ִ�о���Ѳ�ؼ���¼");					//21
	array.Add ("��22��Ŀ��������ִ�о���Ѳ�ؼ���¼");		//22
	array.Add ("��23��Ŀ���������ֳ��ලѲ�ؼ���¼");		//23
	array.Add ("��24��̽������Ŀ���У��գ�ʱЧͳ�Ʊ�");		//24
	array.Add ("��25��̽������Ŀ��ȣ��£�ʱЧ������");		//25
	array.Add ("��26��̽������Ŀըҩ���׹ܣ��գ�ʹ�����ͳ�Ʊ�");	//26
	array.Add ("��27��̽������ĿͶ�ʷ���ʩ������ͬ�����");	//27
	array.Add ("��28��̽������Ŀ�ɱ��������£�ͳ�Ʊ�");		//28
	array.Add ("��29��̽������Ŀ�ɱ��������£�������");		//29
	array.Add ("��30��̽�����������ϵͳQC��������嵥");	//30
}

CString GetColNameField(CString sTable)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	return pApp->GetColNameField(sTable);
}

bool GetOneRecord(		CString sTable, 
						CString sField,
						CString sCondition,
						CStringArray &record)
{
	CDataBrowseDoc doc;

	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CString sSQL;
	CStringArray arrayFields,arrayTypes;

	::GetFieldNames (sTable,arrayFields,arrayTypes);

	sSQL.Format ("select * from %s where %s='%s'",
						(LPCTSTR)sTable,
						(LPCTSTR)sField,
						(LPCTSTR)sCondition);

	CTableDate dateStart;
	pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,&doc,::GetMaxHandDownRecord (),false);

	if(doc.GetRecordQty ()==0)
	{
		TRACEERROR("û���ҵ����������ļ�¼:"+sTable);
		return false;
	}

	if(doc.GetRecordQty ()>1)
	{
		TRACEERROR("����"+vtos(doc.GetRecordQty ())+"�����������ļ�¼:"+sTable);
		return false;
	}

	CStringArray *pRecord=doc.GetRecord (0);
	record.Copy (*pRecord);

	return true;
}

bool GetFieldOfAllRecordsInTable(                   CString sTable, 
                                                    CString sField,
                                                    CStringArray &arrayFieldOfAllRecords)
{
    GetFieldOfAllRecordsInTableUnderCondition(sTable,"",sField,arrayFieldOfAllRecords);
    return true;
}

bool GetFieldOfAllRecordsInTableUnderCondition(     CString sTable, 
                                                    CString sCondition,
                                                    CString sField,
                                                    CStringArray &arrayFieldOfAllRecords)
{
    CDataBrowseDoc doc;

    CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
    CString sSQL;
    CStringArray arrayFields;
    arrayFields.Add(sField);

    if(sCondition=="")
    {
        sSQL.Format ("select * from %s",(LPCTSTR)sTable);
    }
    else
    {
        sSQL.Format ("select * from %s where %s",(LPCTSTR)sTable,(LPCTSTR)sCondition);
    }

    CTableDate dateStart;
    pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,&doc,::GetMaxHandDownRecord (),false);

    if(doc.GetRecordQty ()==0)
    {
        TRACEERROR("����"+sTable+"�м�¼��ĿΪ��!");
        return false;
    }

    CStringArray *pRecord=NULL;
    arrayFieldOfAllRecords.RemoveAll();
    CString sData;
    for(int i=0;i<doc.GetRecordQty();i++)
    {
        pRecord=doc.GetRecord (i);
        sData=pRecord->GetAt(0);
        arrayFieldOfAllRecords.Add(sData);
    }

    return true;
}

void ClearProjectNames()
{
    gArrayProjectNames.RemoveAll();
}

void TakeOutProjectNames()
{
    GetFieldOfAllRecordsInTable("��0101��Ŀ", 
                                "���",
                                gArrayProjectNames);
}

void ClearMonitorNames()
{
    gArrayMonitorNames.RemoveAll();
}

void TakeOutMonitorNames()
{
    GetFieldOfAllRecordsInTable("��0000������Ա�������ͳ�Ʊ�", 
                                "����",
                                gArrayMonitorNames);

}

void ClearTechnicianNames()
{
    gArrayTechnicianNames.RemoveAll();
}

void TakeOutTechnicianNames()
{
    GetFieldOfAllRecordsInTable("��0001������Ա�������ͳ�Ʊ�", 
                                "����",
                                gArrayTechnicianNames);

}

void ClearInstrumentNames()
{
    gArrayInstNames.RemoveAll();
}

void TakeOutInstrumentNames()
{
    GetFieldOfAllRecordsInTable("��0002�����ͺ�ͳ�Ʊ�", 
                                "�����ͺ�",
                                gArrayInstNames);
}

void ClearSurveyLines()
{
    gArrayProjectNoForSurveyLines.RemoveAll();
    gArraySurveyLineNamesOfProject.RemoveAll();
    gArrayAllLineNames.RemoveAll();
}

void TakeOutAllLineNames()
{
    GetFieldOfAllRecordsInTable("��0201����", 
                                "���߱��",
                                gArrayAllLineNames);
}


void TakeOutSurveyLineNamesByProject()
{
    GetFieldOfAllRecordsInTable("��0201����", 
                                "��Ŀ���",
                                gArrayProjectNoForSurveyLines);

    GetFieldOfAllRecordsInTable("��0201����", 
                                "���߱��",
                                gArraySurveyLineNamesOfProject);
}


CStringArray & GetProjectNames()
{
    if(gArrayProjectNames.GetCount()==0)
    {
        TakeOutProjectNames();
    }

    return gArrayProjectNames;
}

CStringArray & GetMonitorNames()
{
    if(gArrayMonitorNames.GetCount()==0)
    {
        TakeOutMonitorNames();
        if(gArrayMonitorNames.GetCount()==0)
        {
            gArrayMonitorNames.Add("������");
        }
    }
    return gArrayMonitorNames;
}

CStringArray & GetTechnicianNames()
{
    if(gArrayTechnicianNames.GetCount()==0)
    {
        TakeOutTechnicianNames();
        if(gArrayTechnicianNames.GetCount()==0)
        {
            gArrayTechnicianNames.Add("������");
        }
    }
    return gArrayTechnicianNames;
}

CStringArray & GetInstrumentNames()
{
    if(gArrayInstNames.GetCount()==0)
    {
        TakeOutInstrumentNames();
        if(gArrayInstNames.GetCount()==0)
        {
            gArrayInstNames.Add("������");
        }
    }
    return gArrayInstNames;
}

CStringArray & GetSurveyLines()
{
    if(gArrayAllLineNames.GetCount()==0)
    {
        TakeOutAllLineNames();
        if(gArrayAllLineNames.GetCount()==0)
        {
            gArrayAllLineNames.Add("������");
        }
    }
    return gArrayAllLineNames;
}

void GetSurveyLinesOfProject(CString sProject,CStringArray &array)
{
    int iCountLines=gArrayProjectNoForSurveyLines.GetCount();
    int iCountProjects=gArraySurveyLineNamesOfProject.GetCount();
    if(iCountLines==0||iCountProjects==0||iCountLines!=iCountProjects)
    {
        TakeOutSurveyLineNamesByProject();
    }

    iCountLines=gArrayProjectNoForSurveyLines.GetCount();
    iCountProjects=gArraySurveyLineNamesOfProject.GetCount();
    if(iCountLines!=iCountProjects)
    {
        TRACEERROR("�����ݿ��л�õĲ�����Ŀ����Ŀ��Ŀ��һ��!");
        return;
    }

    array.RemoveAll();
    CString sProjectName;
    for(int i=0;i<iCountLines;i++)
    {
        sProjectName=gArrayProjectNoForSurveyLines.GetAt(i);
        if(sProjectName==sProject)
        {
            array.Add(gArraySurveyLineNamesOfProject.GetAt(i));
        }
    }

    return;
}

CString GetTableNo(CString sTableName)
{
	CDataBrowseDoc doc;

	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CString sSQL;
	CStringArray array;
	array.Add("���");

	sSQL.Format ("select * from ��0101��Ŀ where ��Ŀ����='%s'",(LPCTSTR)sTableName);
	CTableDate dateStart;
	pApp->m_dt.GetData ("",0,"��0101��Ŀ",sSQL,dateStart,&array,&doc,::GetMaxHandDownRecord (),false);

	if(doc.GetRecordQty ()==0)
	{
		TRACEERROR("û���ҵ���Ŀ:"+sTableName);
		return CString("");
	}

	if(doc.GetRecordQty ()>1)
	{
		TRACEERROR("����"+vtos(doc.GetRecordQty ())+"����Ŀ������ͬ:"+sTableName);
		return CString("");
	}

	CStringArray *pRecord=doc.GetRecord (0);
	return pRecord->GetAt (0);

}

CString GetTableSimpleName(CString sTable)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	return pApp->GetTableSimpleName(sTable);
}

CString GetDBDiscription()
{
	return CString("��̽�������ݿ�");
};

CString GetBlueDBName()
{
	return CString("QCBlueDB.MDB");
};

#include "RasError.h"

void GetDialEntrys(CStringArray &array)
{
	DWORD n;
	RASENTRYNAME *entry=new RASENTRYNAME;
    DWORD dwSize = sizeof(RASENTRYNAME);
	entry->dwSize=sizeof(RASENTRYNAME);

	//ö�ٳ����ص����е����в������ӡ�
	DWORD ret=RasEnumEntriesA(NULL, NULL, entry, &dwSize,&n);
	n=dwSize/sizeof(RASENTRYNAME);
	delete entry;

	entry=new RASENTRYNAME[n+2];
    dwSize = sizeof(RASENTRYNAME)*(n+2);
	for(int i=0;i<n;i++)
	{
		entry->dwSize=sizeof(RASENTRYNAME);
	}
	ret=RasEnumEntriesA(NULL, NULL, entry, &dwSize,&n);

	
	int ii=ERROR_BUFFER_TOO_SMALL;
	int iii=ERROR_INVALID_SIZE;
	int iiii=ERROR_NOT_ENOUGH_MEMORY;

	array.RemoveAll ();

	if(ERROR_SUCCESS == ret)
	{
		for (DWORD i=0;i<n;i++)
		{
			array.Add (entry[i].szEntryName);
		}
	}
	delete[] entry;

	return ;
}

bool Dial(CString sEntryName)
{
	char sError[1000];

	if(sEntryName=="")
	{
		if(!GetPar("GLOBAL_DIAL_ENTRY",sEntryName))
		{
			TRACEERROR("û���趨��������!");
			return false;
		};
	}

	bool bFailed=false;
	BOOL   nRet = FALSE;
	HANDLE hHeap = NULL;
	LPRASDIALDLG  lpInfo = NULL;
	int    dwErr;

	hHeap = GetProcessHeap();

	if( NULL == hHeap )
	{
		dwErr = GetLastError();
		printf("GetProcessHeap() failed: Error = %d\n", dwErr);
		return false;
	}

	lpInfo = (LPRASDIALDLG) HeapAlloc( hHeap, HEAP_ZERO_MEMORY, sizeof(RASDIALDLG));

	if( NULL == lpInfo )
	{
		dwErr = ERROR_OUTOFMEMORY;
		printf("HeapAlloc() failed\n");
		return false;
	}

	lpInfo->dwSize = sizeof(RASDIALDLG);

	//    Calling RasDialDlg()
	nRet = RasDialDlg(NULL, sEntryName.GetBuffer (), NULL, lpInfo);


	if ( FALSE == nRet)
	{
		dwErr = lpInfo->dwError;
		sprintf(sError,"�������Ӵ��󡣴�����: %d\n", dwErr);
		AfxMessageBox(sError);
		bFailed=true;
	}
	else 
	{
		AfxMessageBox("�Ѿ���������.");
	}

	if( NULL != lpInfo )
	{
		HeapFree( hHeap, 0, lpInfo);
	}

	return !bFailed;
}

//void GetServer(CServer &server)
//{
//	CString sIP,sPort,sUserName,sPassword;
//
//	GetPar("GLOBAL_SERVER_IP",sIP);
//	GetPar("GLOBAL_SERVER_PORT",sPort);
//    sUserName=::GetServerUserName();
//    sPassword=::GetServerPassword();
//
//	strcpy(server.sIP ,(LPCTSTR)sIP);
//	sscanf((LPCTSTR)sPort,"%d",&server.iPort);
//	strcpy(server.sUserName,(LPCTSTR)w.sUserName );
//	strcpy(server.sPassword ,(LPCTSTR)w.sPassword );
//
//	return;
//}

void TakeIP(CString sServer,CString &sIP, int &iPort)
{
	int n=sServer.Find (':');
	sIP=sServer.Left (n);
	iPort=0;
	CString sPort;
	sPort=sServer.Mid(n+1);
	sscanf((LPCTSTR)sPort,"%d",&iPort);

	return ;
}

bool ExistArea(CString sArea)
{
	CStringArray array;
	GetLocalAreaItems(array);

	for(int i=0;i<array.GetCount ();i++)
	{
		if(array[i]==sArea)return true;
	}

	return false;
};

void GetLocalAreaItems(CStringArray &array)
{
	GetMorePar("QCDB_GLOBAL_LOCAL_AREAS",array);
	return;
};

CString GetLocalServerName()
{
	return "�������ݿ�";
};

void RemoveServers()
{
	RemovePar("QCDB_SERVER_PROPERTY");
};

void AddServer(		CString sName,
					CString sIP,
					CString sPort,					
					CString sUserName,
					CString sPassword)
{
	CString sProperty;

	CPassword pass(sUserName,sPassword,USER_COMMONUSER);
	pass.Encrypt();
	sProperty=sName+":"+sIP+":"+sPort+":"+pass.sUserName+":"+pass.sPassword;
	AddMorePar("QCDB_SERVER_PROPERTY",sProperty);	
}

bool GetServer(CString sServerIPAndPort,CServer &serverReturn)
{
	memset(&serverReturn,0,sizeof(CServer));
	CServer server;
	CString sIP;

	// separate IP and port from the server name:
	CString sWantIP;
	int iWantPort;
	int n=sServerIPAndPort.Find (':');
	if(n!=-1)
	{
		sWantIP=sServerIPAndPort.Left(n);
		iWantPort=stof(sServerIPAndPort.Mid(n+1));
	}
	else
	{
		sWantIP=sServerIPAndPort;
	}

    // Search the servers for the IP:
	CServer servers[200];
	int iQty=GetServers(servers,200);

	for(int i=0;i<iQty;i++)
	{
		sIP=servers[i].sIP;
		if(strcmp(servers[i].sIP,(LPCTSTR)sWantIP)==0
			&&servers[i].iPort==iWantPort)
		{
			serverReturn=servers[i];
			break;
		}
	}

	return (serverReturn.sIP!="");
}

int GetServers(	CServer servers[],int iLimit)
{
	CStringArray array;
	GetMorePar("QCDB_SERVER_PROPERTY",array);
	int iQty=array.GetCount ();
	CString sProperty;
	int i;
	CStringExtractor ex;
	ex.SetSepChar (":");
	if(iQty>iLimit)
	{
		iQty=iLimit;
	}


	CString sUserName,sPassword;
	for(i=0;i<iQty;i++)
	{
		sProperty=array[i];
		ex.SetString (array[i].GetBuffer ());
		if(ex.GetSubStringQty ()!=5)continue;

		strcpy(servers[i].sName,(LPCTSTR)ex.GetSubString (0));
		strcpy(servers[i].sIP,(LPCTSTR)ex.GetSubString (1));
		servers[i].iPort = stof(ex.GetSubString (2));

		sUserName =ex.GetSubString (3);
		sPassword =ex.GetSubString (4);
		CPassword pass(sUserName,sPassword,USER_COMMONUSER);
		pass.Decrypt();

		strcpy(servers[i].sUserName ,(LPCTSTR)pass.sUserName);
		strcpy(servers[i].sPassword ,(LPCTSTR)pass.sPassword);
	}

	return iQty;
};

void GetAllAreaItems(CStringArray &array)
{
	GetMorePar("QCDB_GLOBAL_ALL_AREAS",array);
	return;
};

bool IsPicFile(CString sFileName)
{
	sFileName.Trim ().MakeUpper ();
	CString sExt=sFileName.Right (3);
	if(sExt=="JPG"||sExt=="BMP"||sExt=="GIF")
	{
		return true;
	}
	else
	{
		return false;
	}
};

bool IsPicField(CString sFieldName)
{
	sFieldName.Trim ().MakeUpper ();
	if(sFieldName.Find ("��Ƭ")!=-1)return true;
	if(sFieldName.Find ("ͼƬ")!=-1)return true;
	if(sFieldName.Find ("��Ƭ")!=-1)return true;
	if(sFieldName.Find ("PHOTO")!=-1)return true;
	if(sFieldName.Find ("PIC")!=-1)return true;
	return false;
};

bool GetFieldTypes(CString sTable,
				   CStringArray &arrayFields,
				   CStringArray &arrayTypes)
{
	CStringArray arrayAllNames,arrayAllTypes;
	GetFieldNames (					sTable,
									arrayAllNames,
									arrayAllTypes);

	arrayTypes.RemoveAll ();
	CString sName;
	int i,j;
	int nNeedQty=arrayFields.GetCount ();
	int nAllQty=arrayAllNames.GetCount ();
	bool bFound=false;
	for(i=0;i<nNeedQty;i++)
	{
		sName=arrayFields.GetAt(i);
		bFound=false;

		if(sName.Find ("=SUM(")!=-1)
		{
			arrayTypes.Add ("���");
			continue;
		}
		else if(sName.Find ("=TOTAL_UNIT")!=-1)
		{
			arrayTypes.Add ("��Ԫ�ۼ�");
			continue;
		}
		else if(sName.Find ("=TOTAL_PROJECT")!=-1)
		{
			arrayTypes.Add ("��Ŀ�ۼ�");
			continue;
		}

		else
		{
			for(j=0;j<nAllQty;j++)
			{
				if(arrayAllNames.GetAt (j)==sName)
				{
					arrayTypes.Add (arrayAllTypes.GetAt (j));
					bFound=true;
					break;
				}
			}

			if(!bFound)
			{
				TRACEERROR("�޷������ݱ�: "+sTable+" ���ҵ��ֶ�:"+sName);
				return false;
			}
		}
	}

	return true;
}

void SetMaxHandDownRecord(int iMaxTransferRecord)
{
	AddPar("QCDB_GLOBAL_MAX_HANDDOWN_RECORD",iMaxTransferRecord);
	return;
}

int GetMaxHandDownRecord()
{
	int n=-1;
	GetPar("QCDB_GLOBAL_MAX_HANDDOWN_RECORD",n);
	if(n==-1)
	{
		n=1000;
	}

	return n;
}

void SetMaxHandInRecord(int iMaxTransferRecord)
{
	AddPar("QCDB_GLOBAL_MAX_HANDIN_RECORD",iMaxTransferRecord);
	return;
}

int GetMaxHandInRecord()
{
	int n=-1;
	GetPar("QCDB_GLOBAL_MAX_HANDIN_RECORD",n);
	if(n==-1)
	{
		n=1000;
	}

	return n;
}

bool IsLocalServer(CString sServer)
{
	sServer.MakeUpper ();
	if(   sServer==""
		||sServer=="���ط�����"
		||sServer.Left (5)=="LOCAL"
		||sServer.Left(4)=="����")
	{
		return true;
	}
	else
	{
		return false;
	}
}

CString GetHistoryTableName()
{
	return CString("������ʷ");
}


CString GetCurrTime()
{
	CTime time=CTime::GetCurrentTime ();
	CString sTime=time.Format ("%Y%m%d%H%M%S");
	return sTime;
}
	


CString CombineIP(CString sIP,int iPort)
{
	sIP+=":"+vtos(iPort);
	return sIP;
}

void GetFieldType(char sTemp[],CODBCFieldInfo &info)
{
	switch(info.m_nSQLType)
	{
	case 1:
		sprintf(sTemp,"TEXT(%d)",info.m_nPrecision );// �� Oracle����������⣿
		break;
	case -7:
		sprintf(sTemp,"BOOL");
		break;
	case -6:  // ���֣��ֽ�
		sprintf(sTemp,"CHAR(%d)",1);
		break;
	case -1:  //��ע 
		sprintf(sTemp,"NOTE"); // ��ע�����ǲ������ġ�
		break;
	case 4:   // long
		sprintf(sTemp,"INTEGER");
		break;
	case 5:   // ����
		sprintf(sTemp,"INTEGER");
		break;
	case 7:   // ��������
		sprintf(sTemp,"FLOAT");
		break;
	case 8: // ˫������
		sprintf(sTemp,"DOUBLE");  // �� Oracle����������⣿
		break;
	case 11: //����
		sprintf(sTemp,"DATE");
		break;
	case 12: //�ַ���
		sprintf(sTemp,"CHAR(%d)",info.m_nPrecision);
		break;
	default: // Ĭ������
		sprintf(sTemp,"FLOAT");
		break;
	}
}



bool GetFieldNames(	CString sTableName,
					CStringArray &arrayNames,
					CStringArray &arrayType)

{
	CString sDBName=GetDBName();					
	CString sUserID=GetDataBaseUserName();
	CString sPassword=GetDataBasePassword();

#ifndef QCDB_ORACLE
    sUserID="admin";
#endif

	arrayNames.RemoveAll ();
	arrayType.RemoveAll ();

    static char sSQL[1000];
    if(strcmp(gConnectString,"EMPTY")==0)
    {
        sprintf(gConnectString,"ODBC;USER=%s;PWD=%s",sUserID,sPassword);
    }

	if(sTableName=="")return false;

	try
	{
		CDatabase database;

		if(!database.Open (sDBName,0,0,gConnectString))
		{
			TRACEERROR("�޷������ݿ�:"+sDBName);
			return false;
		}
        strcpy(gConnectString,database.GetConnect());

        ::RetrieveDataBasePassward(database);


		CRecordset record (&database);

#ifdef QCDB_ORACLE
		sprintf(sSQL,"select * from SYSTEM.%s",sTableName);
#else
		sprintf(sSQL,"select * from %s",sTableName);
#endif

		if(!record.Open (CRecordset::forwardOnly,sSQL))
		{
			TRACEERROR("�޷������ݱ�:"+sTableName);
			return false;
		}

		int iFieldQty=record.GetODBCFieldCount ();
		arrayNames.SetSize (iFieldQty);
		arrayType.SetSize (iFieldQty);
		CODBCFieldInfo info;

		char sFieldType[200];
		for(int j=0;j<iFieldQty;j++)
		{
			record.GetODBCFieldInfo (j,info);
			arrayNames.SetAt (j,info.m_strName );

			GetFieldType(sFieldType,info);
			arrayType.SetAt (j,sFieldType);
		}
	}


	catch(CDBException* pException)
	{
		TRACEERROR("�޷�����ֶ�����!\r\n������Ϣ:"+pException->m_strError);
		// delete pException; can not delete here. I do not why. Apr.18,2005
		return false;
	}

	return true;

}

int giUniIDOrder=0;
CString gsProjectID="";
CString gsUiIDTemp="";


CString SetProjectID()
{
	gsProjectID="TESTPROJECT";

	///////////////////////////////////
	//  ���������Ŀ����
	CString sArea,sCrew,sYear,sMonth,sUserNameShort;

	//GetPar("QCDB_CURR_AREA",sArea);
	GetPar("QCDB_CURR_CREW",sCrew);
	GetPar("QCDB_CURR_YEAR",sYear);
	GetPar("QCDB_CURR_MONTH",sMonth);
	GetPar("QCDB_USERNAME_SHORT",sUserNameShort);
	/*
	if(sArea=="")
	{
		TRACEERROR("��ǰ������δ��д!");
		return gsProjectID;
	}
*/
	if(sCrew=="")
	{
		TRACEERROR("��ǰ�Ӻ���δ��д!");
		return gsProjectID;
	}

	if(sYear=="")
	{
		TRACEERROR("ʩ�������δ��д!");
		return gsProjectID;
	}
	if(sMonth=="")
	{
		TRACEERROR("��ʼʩ������δ��д!");
		return gsProjectID;
	}
	if(sUserNameShort=="")
	{
		TRACEERROR("�û�����д��δ��д!");
		return gsProjectID;
	}
	
	while(sMonth.GetLength ()<2)
	{
		sMonth="0"+sMonth;
	}

	while(sCrew.GetLength ()<2)
	{
		sCrew="0"+sCrew;
	}

	sUserNameShort.MakeUpper ();
	
	gsProjectID=sUserNameShort+sCrew+sYear+sMonth;

	return gsProjectID;
}

bool IsTrue(char c)
{
	return IsTrue(CString(c));
}

bool IsTrue(CString s)
{
	s.MakeUpper ();
	char c= s.GetAt (0);
	if(c!=0&&c!='N'&&c!='0'&&c!='F')
	{
		return true;
	}
	else
	{
		return false;
	}
}

CString GetRatioString(int iChild, int iMother)
{
	return GetRatioString(vtos(iChild),vtos(iMother));
}

CString GetRatioString(CString sChild, CString sMother)
{
	float fValue=stof(sMother);
	float fRatio=0.0;
	char s[100];
	if(fabs(fValue)>0.0000001)
	{
		fRatio=stof(sChild)/fValue*100;
		sprintf(s,"%4.2f%%",fRatio);
		return s;
	}
	else
	{
		return "0.0%";
	}
}

bool IsEmpty(CString s)
{
	s.Trim ();
	s.MakeUpper ();

	if(s=="")return true;
	if(s=="NULL")return true;

	return false;
}

CString GetProjectName(CString sNo)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	sSQL.Format ("select * from ��0101��Ŀ where ���='%s'",(LPCTSTR)sNo);
	arrayFields.Add ("��Ŀ����");					//0

	CDataBrowseDoc docProject;
	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,"��0101��Ŀ",sSQL,dateStart,&arrayFields,&docProject,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return CString("");
	};

	if(docProject.GetRecordQty ()==0)
	{
		TRACEERROR("û�з�����������Ŀ:"+sSQL);
		return CString("");
	}

	if(docProject.GetRecordQty ()>1)
	{
		TRACEERROR("������������Ŀ����һ��:"+sSQL);
		return CString("");
	}

	CStringArray *pRecord=docProject.GetRecord (0);
	if(!pRecord)
	{
		TRACEERROR("�޷���ü�¼:"+sSQL);
		return CString("");
	}

	return pRecord->GetAt (0);
}


CString GetProjectNo(CString sName)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	sSQL.Format ("select * from ��0101��Ŀ where ��Ŀ����='%s'",(LPCTSTR)sName);
	arrayFields.Add ("���");					//0

	CDataBrowseDoc docProject;
	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,"��0101��Ŀ",sSQL,dateStart,&arrayFields,&docProject,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return CString("");
	};

	if(docProject.GetRecordQty ()==0)
	{
		TRACEERROR("û�з�����������Ŀ:"+sSQL);
		return CString("");
	}

	if(docProject.GetRecordQty ()>1)
	{
		TRACEERROR("������������Ŀ����һ��:"+sSQL);
		return CString("");
	}

	CStringArray *pRecord=docProject.GetRecord (0);
	if(!pRecord)
	{
		TRACEERROR("�޷���ü�¼:"+sSQL);
		return CString("");
	}

	return pRecord->GetAt (0);
}

CString GetLineNo(CString sProjectNo, CString sLineName)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	sSQL.Format ("select * from ��0201���� where ��Ŀ���='%s' and ��������='%s' ",
			(LPCTSTR)sProjectNo,
			(LPCTSTR)sLineName);

	arrayFields.Add ("���߱��");					//0

	CDataBrowseDoc docProject;
	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,"��0201����",sSQL,dateStart,&arrayFields,&docProject,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return CString("");
	};

	if(docProject.GetRecordQty ()==0)
	{
		TRACEERROR("û�з�����������Ŀ:"+sSQL);
		return CString("");
	}

	if(docProject.GetRecordQty ()>1)
	{
		TRACEERROR("������������Ŀ����һ��:"+sSQL);
		return CString("");
	}

	CStringArray *pRecord=docProject.GetRecord (0);
	if(!pRecord)
	{
		TRACEERROR("�޷���ü�¼:"+sSQL);
		return CString("");
	}

	return pRecord->GetAt (0);
}

bool GetLineNames(CString sProjectName, CStringArray &arrayLines)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	CString  sNo=GetProjectNo(sProjectName);
	if(sNo=="")return false;

	sSQL.Format ("select * from ��0201���� where ��Ŀ���='%s'",(LPCTSTR)sNo);
	arrayFields.Add ("��������");					//0

	arrayLines.RemoveAll ();

	CDataBrowseDoc docProject;
	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,"��0201����",sSQL,dateStart,&arrayFields,&docProject,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	CStringArray *pRecord=NULL;
	for(int i=0;i<docProject.GetRecordQty ();i++)
	{
        pRecord=docProject.GetRecord (i);
		arrayLines.Add (pRecord->GetAt (0));
	}

	return true;
}


bool AddMonitor(CStringArray &arrayMonitor, CString sMonitor)
{
	sMonitor.Trim().MakeUpper();
	if(sMonitor=="NULL"||sMonitor=="")return false;

	bool bExist=false;
	for(int j=0;j<arrayMonitor.GetCount ();j++)
	{
		if(arrayMonitor.GetAt (j)==sMonitor)
		{
			bExist=true;
		}
	}

	if(!bExist)
	{
		arrayMonitor.Add (sMonitor);
	}

	return !bExist;
}

CString GetMonitorString(CStringArray &array)
{
	CString s;
	for(int i=0;i<array.GetCount ();i++)
	{
		if(s!="")
		{
			s+=",";
		}

		s+=array.GetAt (i);
	}

	return s;
}

CString MakeDateCmpString(CString sYearField,
						CString sMonthField,
						CString sDayField,
						CString sCmp,
						int     iYear,
						int     iMonth,
						int     iDay)
{
	return MakeDateCmpString( sYearField,
						 sMonthField,
						 sDayField,
						 sCmp,
						vtos(iYear),
						vtos(iMonth),
						vtos(iDay));
}

CString MakeDateCmpString(CString sYearField,
						CString sMonthField,
						CString sDayField,
						CString sCmp,
						CString sYear,
						CString sMonth,
						CString sDay)
{
	CString s;
	if(sCmp=="")return CString("");
	if(sYearField!=""&&sMonthField!=""&&sDayField!=""&&sYear!=""&&sMonth!=""&&sDay!="")
	{
		s.Format(" (%s %s %s) or (%s = %s and %s %s %s ) or (%s = %s and %s = %s and %s %s %s)",
			(LPCTSTR)sYearField,
			(LPCTSTR)sCmp,
			(LPCTSTR)sYear,

			// Month
			(LPCTSTR)sYearField,
			(LPCTSTR)sYear,

			(LPCTSTR)sMonthField,
			(LPCTSTR)sCmp,
			(LPCTSTR)sMonth,

			// Day:
			(LPCTSTR)sYearField,
			(LPCTSTR)sYear,

			(LPCTSTR)sMonthField,
			(LPCTSTR)sMonth,

			(LPCTSTR)sDayField,
			(LPCTSTR)sCmp,
			(LPCTSTR)sDay);
	}

	else if(sYearField!=""&&sMonthField==""&&sDayField==""&&sYear!="")
	{
		s.Format("%s %s %s",
			(LPCTSTR)sYearField,
			(LPCTSTR)sCmp,
			(LPCTSTR)sYear);
	}

	else if(sYearField==""&&sMonthField!=""&&sDayField==""&&sMonth!="")
	{
		s.Format("%s %s %s",
			(LPCTSTR)sMonthField,
			(LPCTSTR)sCmp,
			(LPCTSTR)sMonth);
	}

	else if(sYearField==""&&sMonthField==""&&sDayField!=""&&sDay!="")
	{
		s.Format("%s %s %s",
			(LPCTSTR)sDayField,
			(LPCTSTR)sCmp,
			(LPCTSTR)sDay);
	}


	else if(sYearField!=""&&sMonthField!=""&&sDayField==""&&sYear!=""&&sMonth!="")
	{
		s.Format(" (%s %s %s) or (%s = %s and %s %s %s )",
			(LPCTSTR)sYearField,
			(LPCTSTR)sCmp,
			(LPCTSTR)sYear,

			// Month
			(LPCTSTR)sYearField,
			(LPCTSTR)sYear,

			(LPCTSTR)sMonthField,
			(LPCTSTR)sCmp,
			(LPCTSTR)sMonth);
	}

	else if(sYearField==""&&sMonthField!=""&&sDayField!=""&&sMonth!=""&&sDay!="")
	{
		s.Format(" (%s %s %s) or (%s = %s and %s %s %s )",
			(LPCTSTR)sMonthField,
			(LPCTSTR)sCmp,
			(LPCTSTR)sMonth,

			// Month
			(LPCTSTR)sMonthField,
			(LPCTSTR)sMonth,

			(LPCTSTR)sDayField,
			(LPCTSTR)sCmp,
			(LPCTSTR)sDay);
	}

	else if(sYearField!=""&&sMonthField==""&&sDayField!=""&&sYear!=""&&sDay!="")
	{
		s.Format(" (%s %s %s) or (%s = %s and %s %s %s )",
			(LPCTSTR)sYearField,
			(LPCTSTR)sCmp,
			(LPCTSTR)sYear,

			// Month
			(LPCTSTR)sYearField,
			(LPCTSTR)sYear,

			(LPCTSTR)sDayField,
			(LPCTSTR)sCmp,
			(LPCTSTR)sDay);
	}
	else
	{
		return CString("");
	}


	s="("+s+")";

	return s;
}

CString GetChineseWeekDay(int iWeekDay)
{
	CString sWeekDay;
	switch(iWeekDay)
	{
	case 1:
		sWeekDay="������";
		break;
	case 2:
		sWeekDay="����һ";
		break;
	case 3:
		sWeekDay="���ڶ�";
		break;
	case 4:
		sWeekDay="������";
		break;
	case 5:
		sWeekDay="������";
		break;
	case 6:
		sWeekDay="������";
		break;
	case 7:
		sWeekDay="������";
		break;
	default:
		sWeekDay="����δ֪";
	}

	return sWeekDay;
}

enumUserLevel GetUserLevel(CString sUser,CString sPassword)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	enumUserLevel eL=pApp->m_password.GetUserLevel(sUser.GetBuffer (),sPassword.GetBuffer());
	sUser.ReleaseBuffer ();
	sPassword.ReleaseBuffer ();
	return eL;
}


bool UserValid(char     sUser[], 
               char     sPassword[])
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	return pApp->m_password.IsValid (   sUser,
                                        sPassword);
}

CString GetDataBasePath()
{
    CString sDataBasePath;
    GetPar("QCDB_GLOBAL_DataBasePath",	sDataBasePath);
    return sDataBasePath;
}

void    AddDataBasePath(CString sDataBasePath)
{
    AddPar("QCDB_GLOBAL_DataBasePath",	sDataBasePath);
}


CString GetPicFullPath(CString sPicFile)
{
    CString sDataBasePath=GetDataBasePath();
	if(sDataBasePath=="")
	{
		sDataBasePath=GetMyTempPath();
	}

    if(sDataBasePath.GetLength()==1)
    {
        sDataBasePath=sDataBasePath+":";
    }

    if(sDataBasePath.Right (1)!="\\")
    {
        sDataBasePath+="\\";
    }

    if(sDataBasePath.Left (1)=="\\")
    {
        sDataBasePath=sDataBasePath.Mid(1);
    }

	return sDataBasePath+sPicFile;
}

CString GetDataBaseUserName()
{
    CString sUserName;
    GetPar("DATABASE_USERNAME",sUserName);
    if(sUserName=="")
    {
        return sUserName;
    }

    CPassword w;
    w.Set(sUserName,"",USER_COMMONUSER,CMyDate(2000,1,1),CMyDate(3000,12,31));
    w.Decrypt ();

    return CString(w.sUserName);
}

void SetDataBaseUserName(CString s)
{
    CPassword w;
    w.Set(s,"",USER_COMMONUSER,CMyDate(2000,1,1),CMyDate(3000,12,31));
    w.Encrypt();

    AddPar("DATABASE_USERNAME",w.sUserName);
}

CString GetDataBasePassword()
{
    return "qscwdv123#";


    CString sPassword;
    GetPar("DATABASE_PASSWORD",sPassword);

    CPassword w;
    w.Set("",sPassword,USER_COMMONUSER,CMyDate(2000,1,1),CMyDate(3000,12,31));
    w.Decrypt ();

    return CString(w.sPassword );
}

void SetDataBasePassword(CString s)
{
    CPassword w;
    w.Set("",s,USER_COMMONUSER,CMyDate(2000,1,1),CMyDate(3000,12,31));
    w.Encrypt();

    AddPar("DATABASE_PASSWORD",w.sPassword);
}

void RetrieveDataBasePassward(CDatabase &database)
{
    CString sConnection=database.GetConnect();
    int nPasswordPos=sConnection.Find("PWD");
    int n1=sConnection.Find("=",nPasswordPos);
    int n2=sConnection.Find(";",n1+1);
    CString sPassword=sConnection.Mid(n1+1,n2-n1-1);
    SetDataBasePassword(sPassword);
}