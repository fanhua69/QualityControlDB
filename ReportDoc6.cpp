
#include "stdafx.h"
#include "QCDB.h"
#include "ReportDoc.h"
#include "DlgReportProperty.h"
#include "MyDate.h"

///////////////////////////////////////////////////////////
//��̽������Ŀըҩ���׹ܣ��գ�ʹ�����ͳ�Ʊ�
//��0301�������ձ�  ��26
///////////////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport26(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	CString sStartDay,sEndDay;

	// ��ñ���Ŀ���м�¼��Ϊ�˼����棺
	if(dlg.m_iEndYear!=0)
	{
		sEndDay=MakeDateCmpString(	"��",
					"��",
					"��",
					"<=",
					dlg.m_iEndYear ,
					dlg.m_iEndMonth ,
					dlg.m_iEndDay );
	}

	CString sTable="��0301�������ձ�";
	
	sSQL.Format ("select * from %s where ��Ŀ���='%s' ",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo);
	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}

	arrayFields.Add ("���");			//0
	arrayFields.Add ("��Ŀ���");		//1
	arrayFields.Add ("פ�Ӽල");		//2
	arrayFields.Add ("���߱��");		//3 
	arrayFields.Add ("��");				//4 
	arrayFields.Add ("��");				//5 
	arrayFields.Add ("��");				//6 

	arrayFields.Add ("�׹��������");			//7
	arrayFields.Add ("�׹ܳ�������");			//8
	arrayFields.Add ("�׹ܴ�������");			//9
	arrayFields.Add ("�׹ܱ������");			//10
	arrayFields.Add ("�׹���������");			//11
	arrayFields.Add ("ըҩ�������");			//12
	arrayFields.Add ("ըҩ��������");			//13
	arrayFields.Add ("ըҩ��������");			//14
	arrayFields.Add ("ըҩ�������");			//15
	arrayFields.Add ("ըҩ��������");			//16


	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	return true;
}

///////////////////////////////////////////////
// ��̽������ĿͶ�ʷ���ʩ������ͬ�����
// ��0101��Ŀ  ��27
///////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport27(CDlgReportProperty &dlg)
{
	// This report does not need daily data.
	return true;
}

///////////////////////////////////////////////
// ��̽������Ŀ�ɱ������£�ͳ�Ʊ�
// ��0501�ɱ�������ͳ�Ʊ�  ��28
///////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport28(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	CString sStartDay,sEndDay;

	if(dlg.m_iStartYear!=0)
	{
		sStartDay=MakeDateCmpString(	"��",
					"��",
					"��",
					">=",
					dlg.m_iStartYear ,
					dlg.m_iStartMonth ,
					dlg.m_iStartMonth );
	}

	if(dlg.m_iEndYear!=0)
	{
		sEndDay=MakeDateCmpString(	"��",
					"��",
					"��",
					"<=",
					dlg.m_iEndYear ,
					dlg.m_iEndMonth ,
					dlg.m_iEndMonth );
	}

	CString sTable="��0501�ɱ�������ͳ�Ʊ�";
	
	sSQL.Format ("select * from %s where ��Ŀ���='%s' ",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo);
	if(sStartDay!="")
	{
		sSQL+=" and "+sStartDay;
	}

	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}

	arrayFields.Add ("���");			//0
	arrayFields.Add ("��Ŀ���");		//1
	arrayFields.Add ("פ�Ӽල");		//2
	arrayFields.Add ("��ע");			//3 
	arrayFields.Add ("��");				//4 
	arrayFields.Add ("��");				//5 

	arrayFields.Add ("�׹�");			//6
	arrayFields.Add ("ըҩ");			//7
	arrayFields.Add ("����");			//8
	arrayFields.Add ("ȼ��");			//9 
	arrayFields.Add ("����");			//10
	arrayFields.Add ("���ʲ�������");	//11
	arrayFields.Add ("����ֱ�ӳɱ�");	//12

	arrayFields.Add ("�豸����");		//13
	arrayFields.Add ("�豸�۾�");		//14
	arrayFields.Add ("���ز���");		//15
	arrayFields.Add ("������ӳɱ�");	//16

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	return true;
}

///////////////////////////////////////////////////////////
// ��̽������Ŀ�ɱ������£�������
//��0501�ɱ�������ͳ�Ʊ���ͬ���ڳɱ���ӱ�0101��Ŀ���ó�  ��29
//����ʩ��������������������ȴӱ�0301�ձ��еó�
///////////////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport29(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	CString sStartDay,sEndDay;

	if(dlg.m_iStartYear!=0)
	{
		sStartDay=MakeDateCmpString(	"��",
					"��",
					"��",
					">=",
					dlg.m_iStartYear ,
					dlg.m_iStartMonth ,
					dlg.m_iStartMonth );
	}

	if(dlg.m_iEndYear!=0)
	{
		sEndDay=MakeDateCmpString(	"��",
					"��",
					"��",
					"<=",
					dlg.m_iEndYear ,
					dlg.m_iEndMonth ,
					dlg.m_iEndMonth );
	}

	//////////////////////////////////////////////
	// ��һ��ñ���ֱ�ӳɱ��ͼ�ӳɱ�
	//////////////////////////////////////////////
	CString sTable="��0501�ɱ�������ͳ�Ʊ�";
	
	sSQL.Format ("select * from %s where ��Ŀ���='%s' ",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo);
	if(sStartDay!="")
	{
		sSQL+=" and "+sStartDay;
	}

	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}

	arrayFields.Add ("���");			//0
	arrayFields.Add ("��Ŀ���");		//1
	arrayFields.Add ("פ�Ӽල");		//2
	arrayFields.Add ("��ע");			//3 
	arrayFields.Add ("��");				//4 
	arrayFields.Add ("��");				//5 

	arrayFields.Add ("�׹�");			//6
	arrayFields.Add ("ըҩ");			//7
	arrayFields.Add ("����");			//8
	arrayFields.Add ("ȼ��");			//9 
	arrayFields.Add ("����");			//10
	arrayFields.Add ("���ʲ�������");	//11
	arrayFields.Add ("����ֱ�ӳɱ�");	//12

	arrayFields.Add ("�豸����");		//13
	arrayFields.Add ("�豸�۾�");		//14
	arrayFields.Add ("���ز���");		//15
	arrayFields.Add ("������ӳɱ�");	//16

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	//////////////////////////////////////////
	// �ڶ���ñ�������������ʩ������
	/////////////////////////////////////////
	sTable="��0301�������ձ�";
	
	sSQL.Format ("select * from %s where ��Ŀ���='%s' and %s ",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo,
				(LPCTSTR)sStartDay);
	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}

	arrayFields.RemoveAll ();
	arrayFields.Add ("��");				//0 
	arrayFields.Add ("��");				//1 
	arrayFields.Add ("��");				//2 

	arrayFields.Add ("��������1����");			//3
	arrayFields.Add ("��������2����");			//4 
	arrayFields.Add ("��������3����");			//5 
	arrayFields.Add ("��������4����");			//6 
	arrayFields.Add ("��������5����");			//7 
	arrayFields.Add ("��������6����");			//8
	arrayFields.Add ("��������7����");			//9 
	arrayFields.Add ("��������8����");			//10
	arrayFields.Add ("��������9����");			//11
	arrayFields.Add ("��������10����");			//12

	arrayFields.Add ("��������ʩ��");			//13

	arrayFields.Add ("��ϼ���1����");			//14
	arrayFields.Add ("��ϼ���2����");			//15
	arrayFields.Add ("��ϼ���3����");			//16
	arrayFields.Add ("��ϼ���4����");			//17
	arrayFields.Add ("��ϼ���5����");			//18
	arrayFields.Add ("��ϼ���6����");			//19
	arrayFields.Add ("��ϼ���7����");			//20
	arrayFields.Add ("��ϼ���8����");			//21
	arrayFields.Add ("��ϼ���9����");			//22
	arrayFields.Add ("��ϼ���10����");			//23


	CTableDate dateFrom;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateFrom,&arrayFields,&m_docVice,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	return true;
}

///////////////////////////////////////////////////
//   ��̽�����������ϵͳQC��������嵥
//   ��0304QC��������嵥  ��30
///////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport30(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	CString sStartDay,sEndDay;

	if(dlg.m_iStartYear!=0)
	{
		sStartDay=MakeDateCmpString(	"��",
					"��",
					"��",
					">=",
					dlg.m_iStartYear ,
					dlg.m_iStartMonth ,
					dlg.m_iStartMonth );
	}

	if(dlg.m_iEndYear!=0)
	{
		sEndDay=MakeDateCmpString(	"��",
					"��",
					"��",
					"<=",
					dlg.m_iEndYear ,
					dlg.m_iEndMonth ,
					dlg.m_iEndMonth );
	}

	//////////////////////////////////////////////
	// 
	//////////////////////////////////////////////
	CString sTable="��0304QC��������嵥";
	
	sSQL.Format ("select * from %s where ��Ŀ���='%s' ",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo);
	if(sStartDay!="")
	{
		sSQL+=" and "+sStartDay;
	}

	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}

	arrayFields.Add ("���");			//0
	arrayFields.Add ("��Ŀ���");		//1
	arrayFields.Add ("פ�Ӽල");		//2
	arrayFields.Add ("��");				//3 
	arrayFields.Add ("��");				//4 
	arrayFields.Add ("��");				//5 

	arrayFields.Add ("�ο������");		//6	
	arrayFields.Add ("SPS");			//7
	arrayFields.Add ("�첨������");		//8
	arrayFields.Add ("�����������");	//9
	arrayFields.Add ("��У��");			//10
	arrayFields.Add ("�����ռ�");		//11
	arrayFields.Add ("��������");		//12
	arrayFields.Add ("�ɿ���Դ");		//13
	arrayFields.Add ("�����ɹ�");		//14

	arrayFields.Add ("��ע");			//15

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};
}
