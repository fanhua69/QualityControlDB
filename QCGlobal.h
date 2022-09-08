
#ifndef QC_Global_Tag
#define QC_Global_Tag

#include "passwordmanager.h"

class CServer;

#include "afxdb.h"

void	GetDialEntrys(      CStringArray &array);

bool	Dial(               CString sDial);
CString GetIDFieldName();  // Given value by the database
void	GetHandedInField(   CString &sName, 
                            CString &sYesValue);

bool    GetTableNames(      CStringArray &array);

void	RemoveServers();

void	AddServer(		    CString sName,
						    CString sIP,
						    CString sPort,					
						    CString sUserName,
						    CString sPassword);
 
int		GetServers(		    CServer servers[],int iLimit);
bool	GetServer(		    CString sServerIPAndPort,CServer &serverReturn);

CString GetDBName();
CString GetColNameField(    CString sTable);
CString GetTableSimpleName( CString sTable);
CString GetDBDiscription();
CString GetBlueDBName();

// Database username and password:
CString GetDataBaseUserName();
CString GetDataBasePassword();
void    SetDataBasePassword(CString s);
void    SetDataBaseUserName(CString s);
void    RetrieveDataBasePassward(CDatabase &database);

//
bool	ExistArea(          CString sArea);
void	GetLocalAreaItems(  CStringArray &array);
void	GetAllAreaItems(    CStringArray &array);
bool	IsPicFile(          CString sFileName);
bool	IsPicField(         CString sFieldName);
bool	IsServer();

void	TakeIP(             CString sServer,
                            CString &sIP, 
                            int &iPort);

bool	GetFieldTypes(	    CString sTable,	
						    CStringArray &arrayFields,
						    CStringArray &arrayTypes);

void	SetMaxHandDownRecord(int    iMaxTransferRecord);
int		GetMaxHandDownRecord();
void	SetMaxHandInRecord  (int    iMaxTransferRecord);
int		GetMaxHandInRecord();

CString GetHistoryTableName();

CString GetCurrTime();
CString CombineIP(          CString         sIP,
                            int             iPort);

bool    GetFieldNames(	    CString         sTableName,
                            CStringArray    &arrayNames,
                            CStringArray    &arrayType);

void    GetFieldType(       char            sTemp[],
                            CODBCFieldInfo  &info);

CString GetLocalServerName();

CString SetProjectID();

void    GetReportNames(     CStringArray &array);
CString GetTableNo(         CString sTableName);

bool    GetOneRecord(		CString sTable, 
						    CString sField,
						    CString sCondition,
						    CStringArray &record);

bool    IsTrue(             char c);
bool    IsTrue(             CString s);
bool    IsEmpty(            CString s);

CString GetRatioString(     CString sChild, 
                            CString sMother);

CString GetRatioString(     int iChild, 
                            int iMother);

bool    AddMonitor(         CStringArray &arrayMonitor, 
                            CString sMonitor);

CString GetMonitorString(   CStringArray &array);

CString MakeDateCmpString(  CString sYearField,
                            CString sMonthField,
                            CString sDayField,
                            CString sCmp,
                            CString sYear,
                            CString sMonth,
                            CString sDay);

CString MakeDateCmpString(  CString sYearField,
                            CString sMonthField,
                            CString sDayField,
                            CString sCmp,
                            int     iYear,
                            int     iMonth,
                            int     iDay);

CString GetChineseWeekDay(      int iWeekDay);

bool    UserValid(              char sUser[], 
                                char sPassword[]);


enumUserLevel GetUserLevel(     CString sUser,
                                CString sPassword);

CString GetDataBasePath ();
void    AddDataBasePath(        CString sDataBasePath);

CString GetPicFullPath(         CString sPicFile);

bool    GetFieldOfAllRecordsInTableUnderCondition   (   CString sTable, 
                                                        CString sCondition,
                                                        CString sField,
                                                        CStringArray &arrayFieldOfAllRecords);

bool            GetFieldOfAllRecordsInTable         (   CString sTable, 
                                                        CString sField,
                                                        CStringArray &arrayFieldOfAllRecords);

void            TakeOutProjectNames     ();
void            TakeOutMonitorNames     ();
void            TakeOutTechnicianNames  ();
void            TakeOutInstrumentNames  ();
void            TakeOutSurveyLineNamesByProject  ();
void            TakeOutAllLineNames     ();


CStringArray &  GetProjectNames         ();
CStringArray &  GetMonitorNames         ();
CStringArray &  GetTechnicianNames      ();
CStringArray &  GetInstrumentNames      ();
CStringArray &  GetSurveyLines          ();

void            ClearInstrumentNames    ();
void            ClearTechnicianNames    ();
void            ClearMonitorNames       ();
void            ClearProjectNames       ();


void            ClearSurveyLines        ();

void            GetSurveyLinesOfProject (CString sProject,CStringArray &array);



#endif