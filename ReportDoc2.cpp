
#include "stdafx.h"
#include "QCDB.h"
#include "ReportDoc.h"
#include "DlgReportProperty.h"
#include "MyDate.h"


////////////////////////////////////////////////////
// �� ̽ �� �� �� �� ר ҵ �� �� �� �� ��
// ��0303�����ල�ձ�  ��6
////////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport06(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	CString sEndDay=MakeDateCmpString(	"��",
						"��",
						"��",
						"<=",
						dlg.m_iEndYear ,
						dlg.m_iEndMonth ,
						dlg.m_iEndDay );

	CString sTable="��0303�����ල�ձ�";
	sSQL.Format ("select * from %s where %s",
					(LPCTSTR)sTable,
					(LPCTSTR)sEndDay);


	arrayFields.Add ("��Ŀ���");		//0

	arrayFields.Add ("��");			//1
	arrayFields.Add ("��");			//2
	arrayFields.Add ("��");			//3
	arrayFields.Add ("�����ͺ�");	//4
	arrayFields.Add ("���¼�ʱ��");	//5
	arrayFields.Add ("���¼�����");	
	arrayFields.Add ("�ռ�ʱ���");	
	arrayFields.Add ("�ռ�����");    // �����ʵ�λ��
	arrayFields.Add ("�ɼ�վ����ʱ��");
	arrayFields.Add ("�ɼ�վ��������");		//10
	arrayFields.Add ("�첨�������·�");
	arrayFields.Add ("�첨����������");	
	arrayFields.Add ("ϵͳ����");	
	arrayFields.Add ("TB�ӳ�");
	arrayFields.Add ("�����౨ʱ���");	//15
	arrayFields.Add ("�����౨����");	//16
	arrayFields.Add ("Ұ������������");
	arrayFields.Add ("Ұ���鹤����");			//
	arrayFields.Add ("Ұ���黷������");			//
	arrayFields.Add ("Ұ����첨�������");	//20
	arrayFields.Add ("����¼");	//21
	arrayFields.Add ("��ע");		//
	arrayFields.Add ("��Ŀ���������������");			//
	arrayFields.Add ("�ල�������");		//
	arrayFields.Add ("�����������ڵ����⼰����Ҫ��");	//25
	arrayFields.Add ("���������ල�����ص�");		//26


	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};
	return TRUE;
}


/////////////////////////////////////
// ��̽���̿������ռල����
/////////////////////////////////////
BOOL CReportDoc::GetDataForReport07(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	CString sTable="��0106�������ռ���";
	sSQL.Format ("select * from %s where ��Ŀ���='%s'",(LPCTSTR)sTable,(LPCTSTR)m_sProjectNo);

	arrayFields.Add ("��Ŀ���");		//0

	arrayFields.Add ("�ල�����");			//1
	arrayFields.Add ("�ල�����");			//2
	arrayFields.Add ("�ල�����");			//3
	arrayFields.Add ("�ල����");			//4

	arrayFields.Add ("���������ͺ�������ʹ������");	//5
	arrayFields.Add ("�ɼ�����ִ�б�׼");			//6
	arrayFields.Add ("�ɼ��������¼켰�����¼");	//7
	arrayFields.Add ("�ɼ�վ�ͺ�������ʹ������");	//8
	arrayFields.Add ("��Դվ�ͺ�������ʹ������");	//9
	arrayFields.Add ("����վ�ͺ�������ʹ������");	//10
	arrayFields.Add ("�ɼ�վ��켰�����¼");		//11
	arrayFields.Add ("�ɿ���Դ�ͺ�����");			//12
	arrayFields.Add ("�ɿ���Դ��켰�����¼");		//13
	arrayFields.Add ("�����������ͺż�ʹ������");	//14
	arrayFields.Add ("������������켰�����¼");	//15
	arrayFields.Add ("���������г��Ⱥ͵���У׼��¼");	//16
	arrayFields.Add ("��ը���ͺ�����������˵��");	//17
	arrayFields.Add ("��ը��TB�ӳٲ��Լ�¼");		//18
	arrayFields.Add ("�첨���ͺ�������ʹ������");	//19
	arrayFields.Add ("�����ͺ�������ʹ������");		//20
	arrayFields.Add ("�������ͺ�������ʹ������");	//21
	arrayFields.Add ("�������׼");				//22
	arrayFields.Add ("ϵͳ���Բ������Ϸ���������");	//23
	arrayFields.Add ("ϵͳ�ӳٲ��Լ�¼�Ͱ౨");		//24
	arrayFields.Add ("�첨���������ͺ�������ʹ������");	//25
	arrayFields.Add ("�첨����������ȼ���֤��");	//26
	arrayFields.Add ("�첨�����Լ�¼��������");	//27
	arrayFields.Add ("������첨����鼰�������");	//28
	arrayFields.Add ("���ڼ첨����鼰�������");		//29 // Report_Part_1

	arrayFields.Add ("�����������");					//30
	arrayFields.Add ("���������ͺ�������ʹ������");		//31
	arrayFields.Add ("������������ϸ�֤��");			//32
	arrayFields.Add ("����Ӧ���������״��");			//33
	arrayFields.Add ("��̽����ͼ�͵���ͼ");				//34
	arrayFields.Add ("����̤������");					//35
	arrayFields.Add ("�������У�˺�չͼ�˶�");			//36
	arrayFields.Add ("GPS�ȷ������ܿ��Ƶ�ɹ�");		//37

	arrayFields.Add ("�ɼ���Ŀ��Ƽ��׷��������");		//38
	arrayFields.Add ("��̽�ɼ�������׼���淶");			//39
	arrayFields.Add ("�ɼ��������鷽��");				//40
	arrayFields.Add ("�����������������ռ�");			//41
	arrayFields.Add ("��������ͼ");						//42
	arrayFields.Add ("Ŀ�Ĳ㹹��ͼ");					//43
	arrayFields.Add ("��������ͼ");						//44	
	arrayFields.Add ("�ز�ϵͳ��״ͼ����ͼ��˵����");	//45
	arrayFields.Add ("������Ա�Ե���Ŀ�����ʶ");		//46

	arrayFields.Add ("��Ҫ���쵼�������Ǹɵ�λ���");	//47
	arrayFields.Add ("����ɿ���Դ�������豸��λ���");	//48
	arrayFields.Add ("��ŵ�����������豸��λ���");		//49
	arrayFields.Add ("�ֳ��������Ӳ������");			//50

	arrayFields.Add ("����������׼����ѧϰ��ƺͼ�¼");	//51
	arrayFields.Add ("��λ������ѵ��λ�������");		//52
	arrayFields.Add ("����������֯�������ʩ");			//53
	arrayFields.Add ("������ƻ���Ŀ��");				//54
	arrayFields.Add ("HSE������֯�������ʩ");			//55
	arrayFields.Add ("HSE��ѵ�����");					//56
	arrayFields.Add ("8485��Ʒ��Ź���ʹ�ô�ʩ");		//57
	arrayFields.Add ("�����ص������ǼǼ��Բ�");			//58
	arrayFields.Add ("���ָ�λ����֤");					//59
	arrayFields.Add ("������Ա���֤��");				//60
	arrayFields.Add ("����ˮ���֤��");					//61
	arrayFields.Add ("Ӫ�����������ʩ");				//62
	arrayFields.Add ("��������");						//63
	arrayFields.Add ("�������ϵ����ü���־");			//64
	arrayFields.Add ("Ӫ�����������õ���ʩ����ȫ��ʶ");	//65

	arrayFields.Add ("ʩ�����Լ����");	//66
	arrayFields.Add ("�ල�����");	//67
	arrayFields.Add ("ʩ���������");	//68
	arrayFields.Add ("ʩ���������");	//69
	arrayFields.Add ("ʩ���������");	//70

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};
	return TRUE;
}

BOOL CReportDoc::GetDataForReport08(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	CString sStartDay,sEndDay;

	sStartDay=MakeDateCmpString(	"�����",
					"�����",
					"�����",
					">=",
					dlg.m_iStartYear ,
					dlg.m_iStartMonth ,
					dlg.m_iStartDay );

	if(dlg.m_iEndYear!=0)
	{
		sEndDay=MakeDateCmpString(	"�����",
					"�����",
					"�����",
					"<=",
					dlg.m_iEndYear ,
					dlg.m_iEndMonth ,
					dlg.m_iEndDay );
	}

	CString sTable="��0401ʩ������ල����";
	
	sSQL.Format ("select * from %s where ��Ŀ���='%s' and %s ",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo,
				(LPCTSTR)sStartDay);
	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}

	arrayFields.Add ("��Ŀ���");		//0

	arrayFields.Add ("�����");			//1
	arrayFields.Add ("�����");			//2
	arrayFields.Add ("�����");			//3

	arrayFields.Add ("�����Ŀ����");			//4
	arrayFields.Add ("�����Ŀ����");			//5
	arrayFields.Add ("�����Ŀ����");			//6
	arrayFields.Add ("�����Ŀ����");			//7
	arrayFields.Add ("�����Ŀ����");			//8
	arrayFields.Add ("�����Ŀ������");			//9
	arrayFields.Add ("�����Ŀ�ֳ�����");			//10
	arrayFields.Add ("�����Ŀԭʼ����");			//11
	arrayFields.Add ("���λ��");			//12
	arrayFields.Add ("�������");			//13
	arrayFields.Add ("������");			//14
	arrayFields.Add ("����ͼ�����ϱ��");			//15
	arrayFields.Add ("�����������ϱ��");			//16
	arrayFields.Add ("�����������ϱ��");			//17
	arrayFields.Add ("�����");			//18
	arrayFields.Add ("�������");			//19
	arrayFields.Add ("����Ч��");			//20
	arrayFields.Add ("������");			//21
	arrayFields.Add ("������");			//22
	arrayFields.Add ("������");			//23
	arrayFields.Add ("��ͬ�����");			//24
	arrayFields.Add ("פ�Ӽල");			//25

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};
	return TRUE;
}

///////////////////////////////////////
// ��̽���̼ල��鱸��¼
///////////////////////////////////////
BOOL CReportDoc::GetDataForReport09(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	CString sStartDay,sEndDay;

	sStartDay=MakeDateCmpString(	"�����",
					"�����",
					"�����",
					">=",
					dlg.m_iStartYear ,
					dlg.m_iStartMonth ,
					dlg.m_iStartDay );

	if(dlg.m_iEndYear!=0)
	{
		sEndDay=MakeDateCmpString(	"�����",
					"�����",
					"�����",
					"<=",
					dlg.m_iEndYear ,
					dlg.m_iEndMonth ,
					dlg.m_iEndDay );
	}

	CString sTable="��0402�ල��鱸��¼";
	sSQL.Format ("select * from %s where ��Ŀ���='%s' and %s ",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo,
				(LPCTSTR)sStartDay);
	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}

	arrayFields.Add ("��Ŀ���");		//0

	arrayFields.Add ("�����");			//1
	arrayFields.Add ("�����");			//2
	arrayFields.Add ("�����");			//3

	arrayFields.Add ("����¼���");			//4
	arrayFields.Add ("����������");			//5
	arrayFields.Add ("�����");			//6
	arrayFields.Add ("����");			//7
	arrayFields.Add ("�����Ŀ��λ��");			//8
	arrayFields.Add ("����������");			//9
	arrayFields.Add ("�����������");			//10
	arrayFields.Add ("����Ч��");			//11
	arrayFields.Add ("������");			//12
	arrayFields.Add ("������");			//13
	arrayFields.Add ("������");			//14
	arrayFields.Add ("������֤��");			//15
	arrayFields.Add ("������֤��");			//16
	arrayFields.Add ("������֤��");			//17
	arrayFields.Add ("ʩ����λ�쵼ǩ��");			//18
	arrayFields.Add ("ʩ����λ�쵼ǩ����");			//19
	arrayFields.Add ("ʩ����λ�쵼ǩ����");			//20
	arrayFields.Add ("ʩ����λ�쵼ǩ����");			//21
	arrayFields.Add ("פ�Ӽලǩ��");			//22
	arrayFields.Add ("פ�Ӽලǩ����");			//23
	arrayFields.Add ("פ�Ӽලǩ����");			//24
	arrayFields.Add ("פ�Ӽලǩ����");			//25

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};
	return TRUE;
}


////////////////////////////////////////////////
//  ��̽���̼ල��������ͳ�Ʒ�����
////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport10(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	CString sStartDay,sEndDay;

	sStartDay=MakeDateCmpString(	"��",
					"��",
					"��",
					">=",
					dlg.m_iStartYear ,
					dlg.m_iStartMonth ,
					dlg.m_iStartDay );

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
	sSQL.Format ("select * from %s where ��Ŀ���='%s' and %s ",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo,
				(LPCTSTR)sStartDay);
	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}

	arrayFields.Add ("��Ŀ���");		//0

	arrayFields.Add ("��");			//1
	arrayFields.Add ("��");			//2
	arrayFields.Add ("��");			//3

	arrayFields.Add ("��鼤������");			//4
	arrayFields.Add ("�ϸ񼤷�����");			//5
	arrayFields.Add ("�����յ���");			//6
	arrayFields.Add ("�ϸ���յ���");			//7
	arrayFields.Add ("����¼����");			//8
	arrayFields.Add ("����һ��");			//9
	arrayFields.Add ("��������");			//10
	arrayFields.Add ("������Ʒ");			//11
	arrayFields.Add ("��ʵС�������");			//12 // = ���С�������
	arrayFields.Add ("�ϸ�С�������");			//13
	arrayFields.Add ("��ʵ΢�⾮����");			//14//  = ���΢�⾮����
	arrayFields.Add ("�ϸ�΢�⾮����");			//15
	arrayFields.Add ("����������");			//16
	arrayFields.Add ("�ϸ��������");			//17
	arrayFields.Add ("������ע");			//18
	arrayFields.Add ("פ�Ӽල");			//19

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};
	return TRUE;
}

