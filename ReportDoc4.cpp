
#include "stdafx.h"
#include "QCDB.h"
#include "ReportDoc.h"
#include "DlgReportProperty.h"
#include "MyDate.h"

////////////////////////////////////////////////
//  ________��ĿҰ��ɼ�ʩ�������ලͳ�Ʊ�
//  ��0201���� ��16
////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport16(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	int i=0,j=0;


	CString sTable="��0201����";
	sSQL.Format ("select * from %s where ��Ŀ��� =  '%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo );

	arrayFields.Add ("��Ŀ���");		//0
	arrayFields.Add ("��������");		//1
	arrayFields.Add ("�����ͺ�");		//2
	arrayFields.Add ("����");			//3
	arrayFields.Add ("���Ǵ���");		//4
	arrayFields.Add ("����");			//5
	arrayFields.Add ("����");			//6  // for occupy this position
	arrayFields.Add ("����");			//7  // for occupy this position
	arrayFields.Add ("�۲�ϵͳ");		//8
	arrayFields.Add ("�첨���ͺ�");		//9 
	arrayFields.Add ("�첨����ϸ���");	//10
	arrayFields.Add ("�첨�����LX");	//11
	arrayFields.Add ("�첨�����LY");	//12
	arrayFields.Add ("�첨�����ͼ��");	//13
	arrayFields.Add ("ǰ��");			//14
	arrayFields.Add ("�ͽ�");			//15
	arrayFields.Add ("�߽�");			//16
	arrayFields.Add ("������");			//17
	arrayFields.Add ("��¼����");		//18
	arrayFields.Add ("ʩ��������ע");	//19
	arrayFields.Add ("פ�Ӽල");		//20

	arrayFields.Add ("����A����");		//21
	arrayFields.Add ("����Aҩ��");		//22
	arrayFields.Add ("����B����");		//23
	arrayFields.Add ("����Bҩ��");		//24
	arrayFields.Add ("����C����");		//25
	arrayFields.Add ("����Cҩ��");		//26
	arrayFields.Add ("����D����");		//27
	arrayFields.Add ("����Dҩ��");		//28
	arrayFields.Add ("����E����");		//29
	arrayFields.Add ("����Eҩ��");		//30

	arrayFields.Add ("��Ͼ�A����");		//31
	arrayFields.Add ("��Ͼ�A����");		//32
	arrayFields.Add ("��Ͼ�Aҩ��");		//33
	arrayFields.Add ("��Ͼ�B����");		//34
	arrayFields.Add ("��Ͼ�B����");		//35
	arrayFields.Add ("��Ͼ�Bҩ��");		//36
	arrayFields.Add ("��Ͼ�C����");		//37
	arrayFields.Add ("��Ͼ�C����");		//38
	arrayFields.Add ("��Ͼ�Cҩ��");		//39
	arrayFields.Add ("��Ͼ�D����");		//40
	arrayFields.Add ("��Ͼ�D����");		//41
	arrayFields.Add ("��Ͼ�Dҩ��");		//42
	arrayFields.Add ("��Ͼ�E����");		//43
	arrayFields.Add ("��Ͼ�E����");		//44
	arrayFields.Add ("��Ͼ�Eҩ��");		//45

	CTableDate dateStart;

	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};
	return true;
}

///////////////////////////////////////////////////////////////////
//  ________��ĿҰ��ɼ�ʩ�����ʵ�﹤�����ලͳ�Ʊ�
//  ��ƹ������ڱ�0201�����У�ʵ�ʹ������ڱ�0301�������ձ�  ��17
///////////////////////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport17(CDlgReportProperty &dlg)
{

	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	int i=0,j=0;


	///////////////////////
	// ���߱�
	///////////////////////
	CString sTable="��0201����";
	sSQL.Format ("select * from %s where ��Ŀ��� =  '%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo );

	arrayFields.Add ("���߱��");			//0
	arrayFields.Add ("��������");			//1
	arrayFields.Add ("��������ǳ���");		//2
	arrayFields.Add ("��ƶ�ά��������");	//3
	arrayFields.Add ("�����ά��������");	//4
	arrayFields.Add ("��ɹ�������ע");		//5
	
	CTableDate dateStart;

	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	//////////////////////////////////////////////
	// ��0301�������ձ�
	//////////////////////////////////////////////
	sTable="��0301�������ձ�";
	sSQL.Format ("select * from %s where ��Ŀ��� =  '%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo );

	arrayFields.RemoveAll ();
	arrayFields.Add ("���߱��");		//0
	arrayFields.Add ("���߱��");		//1  // Occupy position
	arrayFields.Add ("��ʵ��������");	//2
	arrayFields.Add ("����һ��");		//3
	arrayFields.Add ("��������");		//4
	arrayFields.Add ("������Ʒ");		//5
	arrayFields.Add ("�����յ�");		//6
	arrayFields.Add ("�ϸ�С�������");	//7
	arrayFields.Add ("�ϸ�΢�⾮����");	//8

	arrayFields.Add ("��");	//9
	arrayFields.Add ("��");	//10
	arrayFields.Add ("��");	//11

	arrayFields.Add ("פ�Ӽල");  //12

	arrayFields.Add ("��������1����");		//13
	arrayFields.Add ("��������2����");		//14
	arrayFields.Add ("��������3����");		//15
	arrayFields.Add ("��������4����");		//16
	arrayFields.Add ("��������5����");		//17
	arrayFields.Add ("��������6����");		//18
	arrayFields.Add ("��������7����");		//19
	arrayFields.Add ("��������8����");		//20
	arrayFields.Add ("��������9����");		//21
	arrayFields.Add ("��������10����");		//22


	arrayFields.Add ("��ϼ���1����");		//23
	arrayFields.Add ("��ϼ���2����");		//24
	arrayFields.Add ("��ϼ���3����");		//25
	arrayFields.Add ("��ϼ���4����");		//26
	arrayFields.Add ("��ϼ���5����");		//27
	arrayFields.Add ("��ϼ���6����");		//28
	arrayFields.Add ("��ϼ���7����");		//29
	arrayFields.Add ("��ϼ���8����");		//30
	arrayFields.Add ("��ϼ���9����");		//31
	arrayFields.Add ("��ϼ���10����");		//32
	
	CTableDate dateFrom;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateFrom,&arrayFields,&m_docVice ,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	return true;
}


///////////////////////////////////////////////////
//  ���           ����̽��������ͳ�Ʊ�
//           ����0201���ߣ�  ��18
///////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport18(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	int i=0,j=0;

	///////////////////////
	// ���߱�
	///////////////////////
	CString sTable="��0201����";
	sSQL.Format ("select * from %s where ��Ŀ��� =  '%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo );

	arrayFields.Add ("���߱��");			//0
	arrayFields.Add ("��������");			//1
	arrayFields.Add ("��ƶ�ά��������");	//2
	arrayFields.Add ("�����ά��������");	//3 
	
	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,&m_docVice,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	//////////////////////////////////////////////
	// ��0301�������ձ�
	//////////////////////////////////////////////
	sTable="��0301�������ձ�";
	sSQL.Format ("select * from %s where ��Ŀ��� =  '%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo );

	arrayFields.RemoveAll ();
	arrayFields.Add ("���߱��");			//0

	arrayFields.Add ("��������1����");		//1
	arrayFields.Add ("��������2����");		//2
	arrayFields.Add ("��������3����");		//3
	arrayFields.Add ("��������4����");		//4
	arrayFields.Add ("��������5����");		//5
	arrayFields.Add ("��������6����");		//6
	arrayFields.Add ("��������7����");		//7
	arrayFields.Add ("��������8����");		//8
	arrayFields.Add ("��������9����");		//9
	arrayFields.Add ("��������10����");		//10

	arrayFields.Add ("��ϼ���1����");		//11
	arrayFields.Add ("��ϼ���2����");		//12
	arrayFields.Add ("��ϼ���3����");		//13
	arrayFields.Add ("��ϼ���4����");		//14
	arrayFields.Add ("��ϼ���5����");		//15
	arrayFields.Add ("��ϼ���6����");		//16
	arrayFields.Add ("��ϼ���7����");		//17
	arrayFields.Add ("��ϼ���8����");		//18
	arrayFields.Add ("��ϼ���9����");		//19
	arrayFields.Add ("��ϼ���10����");		//20

	arrayFields.Add ("���ٲ㼤������");		//21

	arrayFields.Add ("�������ر�ע");		//22
	
	arrayFields.Add ("פ�Ӽල");  //13


	
	CTableDate dateFrom;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateFrom,&arrayFields,this ,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	return true;
}


///////////////////////////////////////////////
//  ����ɼ����Ӽ�¼�����������ձ�
//     ����6�����ձ���  ��19
///////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport19(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	int i=0,j=0;

	///////////////////////
	// ���߱�
	///////////////////////
	CString sTable="��0201����";
	sSQL.Format ("select * from %s where ��Ŀ��� =  '%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo );

	arrayFields.Add ("���߱��");			//0
	arrayFields.Add ("��������");			//1
	arrayFields.Add ("��ƶ�ά��������");	//2
	arrayFields.Add ("�����ά��������");	//3 
	
	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,&m_docVice,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	//////////////////////////////////////////////
	// ��0301�������ձ�
	//////////////////////////////////////////////
	sTable="��0301�������ձ�";
	sSQL.Format ("select * from %s where ��Ŀ��� =  '%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo );

	arrayFields.RemoveAll ();
	arrayFields.Add ("���߱��");		//0
	arrayFields.Add ("��������1����");		//1
	arrayFields.Add ("��������2����");		//2
	arrayFields.Add ("��������3����");		//3
	arrayFields.Add ("��������4����");		//4
	arrayFields.Add ("��������5����");		//5
	arrayFields.Add ("��������6����");		//6
	arrayFields.Add ("��������7����");		//7
	arrayFields.Add ("��������8����");		//8
	arrayFields.Add ("��������9����");		//9
	arrayFields.Add ("��������10����");		//10

	arrayFields.Add ("����һ��");		//11
	arrayFields.Add ("��������");		//12
	arrayFields.Add ("�����յ�");		//13
	arrayFields.Add ("������Ʒ");		//14
	arrayFields.Add ("����һ��");		//15
	arrayFields.Add ("��������");		//16
	arrayFields.Add ("�����յ�");		//17
	arrayFields.Add ("������Ʒ");		//18
	arrayFields.Add ("��ʵС�������");		//19
	arrayFields.Add ("�ϸ�С�������");		//20
	arrayFields.Add ("��ʵ΢�⾮����");		//21
	arrayFields.Add ("�ϸ�΢�⾮����");		//22
	arrayFields.Add ("������ע");			//23
	
	arrayFields.Add ("פ�Ӽල");			//24

	arrayFields.Add ("��ϼ���1����");		//25
	arrayFields.Add ("��ϼ���2����");		//26
	arrayFields.Add ("��ϼ���3����");		//27
	arrayFields.Add ("��ϼ���4����");		//28
	arrayFields.Add ("��ϼ���5����");		//39
	arrayFields.Add ("��ϼ���6����");		//30
	arrayFields.Add ("��ϼ���7����");		//31
	arrayFields.Add ("��ϼ���8����");		//32
	arrayFields.Add ("��ϼ���9����");		//33
	arrayFields.Add ("��ϼ���10����");		//34
	
	CTableDate dateFrom;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateFrom,&arrayFields,this ,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	return true;
}


/////////////////////////////////////////////////
//  ��̽����ԭʼ��¼�ල���������ļ��ǼǱ�
//��0403ԭʼ��¼�ල���������ļ��ǼǱ�  ��20 
/////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport20(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	int i=0,j=0;

	///////////////////////
	// ���߱�
	///////////////////////
	CString sTable="��0403ԭʼ��¼�ල���������ļ��ǼǱ�";
	sSQL.Format ("select * from %s where ��Ŀ��� =  '%s' and ���߱��='%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo,
					(LPCTSTR)m_sLineNo);

	arrayFields.Add ("�ļ���");			//0
	arrayFields.Add ("�ϸ�");			//1
	arrayFields.Add ("��Ʒ");			//2
	arrayFields.Add ("����ԭ��Ŀ�Ĳ�");	//3 
	arrayFields.Add ("����ԭ������");	//4 
	arrayFields.Add ("����ԭ�����ʱ��");	//5 
	arrayFields.Add ("����ԭ������");	//6 
	arrayFields.Add ("����ԭ�����");	//7 
	arrayFields.Add ("����ԭ��Tֵ");	//8 
	arrayFields.Add ("����ԭ������");	//9 
	
	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	//////////////////////////////////////////////
	// ��0301�������ձ�
	//////////////////////////////////////////////
	sTable="��0301�������ձ�";
	sSQL.Format ("select * from %s where ��Ŀ��� =  '%s' and ���߱��='%s'",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo,
					(LPCTSTR)m_sLineNo);

	arrayFields.RemoveAll ();
	arrayFields.Add ("פ�Ӽල");		//0
	
	CTableDate dateFrom;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateFrom,&arrayFields,&m_docVice  ,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	return true;
}

