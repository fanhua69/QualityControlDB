
#include "stdafx.h"
#include "QCDB.h"
#include "ReportDoc.h"
#include "DlgReportProperty.h"
#include "MyDate.h"

////////////////////////////////////////
// ��̽���̼ල���Ĺ������ܱ�
// ��0402�ල��鱸��¼
////////////////////////////////////////
BOOL CReportDoc::GetDataForReport11(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	CString sStartDay="",sEndDay="";
	
	sStartDay=MakeDateCmpString(	"�����",
									"�����",
									"�����",
									">=",
									dlg.m_iStartYear ,
									dlg.m_iStartMonth ,
									dlg.m_iStartDay);
	if(dlg.m_iEndYear!=0)
	{
		sEndDay= MakeDateCmpString(	"�����",
									"�����",
									"�����",
									"<=",
									dlg.m_iEndYear ,
									dlg.m_iEndMonth ,
									dlg.m_iEndDay);
	}

	CString sTable="��0402�ල��鱸��¼";
	sSQL.Format ("select * from %s where ��Ŀ��� =  '%s' and %s",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo, 
					(LPCTSTR)sStartDay);

	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}


	arrayFields.Add ("����������");		//0

	arrayFields.Add ("�����");			//1
	arrayFields.Add ("�����");			//2
	arrayFields.Add ("�����");			//3
	arrayFields.Add ("�����Ŀ��λ��");	//4
	arrayFields.Add ("����������");	//5
	arrayFields.Add ("�����������");	//6
	arrayFields.Add ("������");			//7
	arrayFields.Add ("������");	
	arrayFields.Add ("������");		
	arrayFields.Add ("����Ч��");		//10
	arrayFields.Add ("פ�Ӽලǩ��");	


	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};
	return TRUE;
}
///////////////////////////////////////////////////
//      ___��������ɼ�ʩ������һ����
//     ��0102����ɼ�ʩ������һ����  ��12
///////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport12(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;


	CString sTable="��0102��Ŀ����ɼ�ʩ������һ����";
	sSQL.Format ("select * from %s where ��Ŀ��� =  '%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo );

	arrayFields.Add ("��Ŀ���");			//0
	arrayFields.Add ("��Ԫ�ߴ�");			//1
	arrayFields.Add ("���Ǵ���");			//2
	arrayFields.Add ("�۲�ϵͳ");			//3
	arrayFields.Add ("���յ���");	//4
	arrayFields.Add ("������ʽ");	//5
	arrayFields.Add ("�������");	//6
	arrayFields.Add ("��¼����");			//7
	arrayFields.Add ("����");	
	arrayFields.Add ("�ڵ��");		
	arrayFields.Add ("����");		//10
	arrayFields.Add ("�����߾�");	
	arrayFields.Add ("���߾�");	
	arrayFields.Add ("����������");	
	arrayFields.Add ("����λ��");	
	arrayFields.Add ("������С�ڼ��");		//15	
	arrayFields.Add ("��������ڼ��");	
	arrayFields.Add ("����ڼ��");	
	arrayFields.Add ("�����ݾ�");	
	arrayFields.Add ("��С�ڼ��");	
	arrayFields.Add ("�첨���ͺ�");			//20
	arrayFields.Add ("�첨���¾����");	
	arrayFields.Add ("��Ϸ�ʽ");	
	arrayFields.Add ("����Ϸ�ʽ");	
	arrayFields.Add ("ǰ������");	
	arrayFields.Add ("�첨������");			//25
	arrayFields.Add ("�����ͺ�");	
	arrayFields.Add ("��ϲ���");	
	arrayFields.Add ("����ϻ���");	
	arrayFields.Add ("��¼�ܶ�");			//29


	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};
	return TRUE;
}


//////////////////////////////////////////////////////////
// ������Ҫ������Ա��λ�������
// ��0107������Ҫ������Ա��λ�������  ��13
//////////////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport13(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	int i=0,j=0;


	CString sTable="��0107��Ҫ������Ա��λ�������";
	sSQL.Format ("select * from %s where ��Ŀ��� =  '%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo );

	arrayFields.Add ("��Ŀ���");			//0
	arrayFields.Add ("����");			//1
	arrayFields.Add ("��Ŀ����");			//2
	arrayFields.Add ("�ӳ�");			//3
	arrayFields.Add ("���");	//4
	arrayFields.Add ("���ӳ�");	//5
	arrayFields.Add ("HSE�ල");	//6
	arrayFields.Add ("ʩ���鳤");			//7
	arrayFields.Add ("ʩ��Ա");	
	arrayFields.Add ("�����鳤");		
	arrayFields.Add ("����Ա");		//10
	arrayFields.Add ("�ֳ������鳤");	
	arrayFields.Add ("�ֳ�����Ա");	
	arrayFields.Add ("�����鳤");	
	arrayFields.Add ("����Ա");	
	arrayFields.Add ("��λ���");		//15	

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	//////////////////////////////////////
	// �����������
	//////////////////////////////////////
	CStringArray arrayNames;
	CString sName,sName2;
	CStringArray *pRecord=NULL;
	bool bExist=true;
	int iRecordQty=GetRecordQty();
	for(i=0;i<iRecordQty;i++)
	{
		pRecord=GetRecord(i);
		sName=pRecord->GetAt (1);
		bExist=false;
		for(j=0;j<arrayNames.GetCount ();j++)
		{
			if(sName==arrayNames.GetAt (j))
			{
				bExist=true;
				break;
			}
		}

		if(!bExist)
		{
			arrayNames.Add (sName);
		}
	}

	if(arrayNames.GetCount ()<1)
	{
		return false;
	}

	///////////////////////////////////
	//  ��ü�����Ա������
	///////////////////////////////////
	sTable="��0001������Ա�������ͳ�Ʊ�";
	CString s;
	sSQL.Format ("select * from %s where ",(LPCTSTR)sTable);
	int iNameQty=arrayNames.GetCount ();
	for(i=0;i<iNameQty;i++)
	{
		s.Format (" ���� =  '%s' ",(LPCTSTR)arrayNames.GetAt (i));
		if(i!=iNameQty-1)
		{
			s+=" or ";
		}
		sSQL+=s;
	}

	sSQL.Format ("select * from %s ",(LPCTSTR)sTable);


	arrayFields.RemoveAll ();
	arrayFields.Add ("����");			//0
	arrayFields.Add ("ְ��");			//1
	arrayFields.Add ("������");			//2
	arrayFields.Add ("��һѧ��");		//3
	arrayFields.Add ("�ڶ�ѧ��");		//4
	arrayFields.Add ("����ѧ��");		//5
	arrayFields.Add ("�μӹ�����");		//6
	arrayFields.Add ("�μӹ�����");		//7
	arrayFields.Add ("�μӹ�����");		//8

	CTableDate dateFrom;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateFrom,&arrayFields,&m_docVice,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	return TRUE;
}

//////////////////////////////////////////
//      ������Ҫ�豸��λ�������
// ��0108������Ҫ�豸��λ�������  ��14
//////////////////////////////////////////
BOOL CReportDoc::GetDataForReport14(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	int i=0,j=0;


	CString sTable="��0108��Ҫ�豸��λ�������";
	sSQL.Format ("select * from %s where ��Ŀ��� =  '%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo );

	arrayFields.Add ("��Ŀ���");			//0
	arrayFields.Add ("����");			//1
	arrayFields.Add ("�첨��");			//2
	arrayFields.Add ("�ɼ�վ");			//3
	arrayFields.Add ("����");	//4
	arrayFields.Add ("΢��");	//5
	arrayFields.Add ("GPS");	//6
	arrayFields.Add ("�����");			//7
	arrayFields.Add ("��ӡ��");			//8
	arrayFields.Add ("�ֳ������");		//9
	arrayFields.Add ("���");		//10
	arrayFields.Add ("�綯�����");	//11
	arrayFields.Add ("ըҩ��");		//12
	arrayFields.Add ("�׹ܳ�");		//13
	arrayFields.Add ("�꾮ˮ�޳�");	//14
	arrayFields.Add ("����");		//15
	arrayFields.Add ("��ͳ�");		//16
	arrayFields.Add ("���߳�");		//17
	arrayFields.Add ("���߳�");		//18
	arrayFields.Add ("���ڳ�");		//19
	arrayFields.Add ("����ˮ�޳�");	//20
	arrayFields.Add ("���ص�̨");	//21
	arrayFields.Add ("�ֳ�ʽ��̨");	//22
	arrayFields.Add ("�豸�ͺ�");	//23
	arrayFields.Add ("����");		//24
	arrayFields.Add ("��λ���");	//25	

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};
}

///////////////////////////////////////////////////////
// ________��ĿҰ��ɼ����鹤���ලͳ�Ʊ�
//  ��0109���鹤���ලͳ�Ʊ�  ��15
///////////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport15(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	int i=0,j=0;


	CString sTable="��0109���鹤���ලͳ�Ʊ�";
	sSQL.Format ("select * from %s where ��Ŀ��� =  '%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo );

	arrayFields.Add ("��Ŀ���");			//0
	arrayFields.Add ("�����λ��");			//1
	arrayFields.Add ("������Ŀ");			//2
	arrayFields.Add ("��������");	//3
	arrayFields.Add ("ըҩ����");	//4
	arrayFields.Add ("�̶�����");	//5
	arrayFields.Add ("����Ч��");			//6
	arrayFields.Add ("��������");			//7
	arrayFields.Add ("������¼");		//8
	arrayFields.Add ("����ζ���");		//9 
	arrayFields.Add ("����������¼");	//10
	arrayFields.Add ("����γ���");		//11
	arrayFields.Add ("������");		//12
	arrayFields.Add ("������");	//13
	arrayFields.Add ("������");		//14
	arrayFields.Add ("פ�Ӽල");	//15

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};
	return true;
}
