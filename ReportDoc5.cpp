

#include "stdafx.h"
#include "QCDB.h"
#include "ReportDoc.h"
#include "DlgReportProperty.h"
#include "MyDate.h"

///////////////////////////////////////////////
//       ̽��ִ�о���Ѳ�ؼ���¼
//  ��0404ִ�о���Ѳ�ؼ���¼  ��21
///////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport21(CDlgReportProperty &dlg)
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

	CString sTable="��0404ִ�о���Ѳ�ؼ���¼";
	
	sSQL.Format ("select * from %s where ��Ŀ���='%s' and %s ",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo,
				(LPCTSTR)sStartDay);
	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}

	arrayFields.Add ("��Ŀ���");			//0
	arrayFields.Add ("�ֳ��ල");			//1
	arrayFields.Add ("̽��ִ�о���");			//2
	arrayFields.Add ("��ͬ��");	//3 
	arrayFields.Add ("��");	//4 
	arrayFields.Add ("��");	//5 
	arrayFields.Add ("��");	//6 
	arrayFields.Add ("�ල�ƻ��Ƿ�Ҫ��ʱ��д");							//7 
	arrayFields.Add ("�ල���������Ƿ�Ҫ��չʾ��ִ��");					//8 
	arrayFields.Add ("�ල������־�Ƿ�Ҫ���¼�Ƿ��꾡");					//9 
	arrayFields.Add ("��������Ƿ�Ҫ���¼�Ƿ��꾡");					//10 
	arrayFields.Add ("�ල���������Ƿ�Ҫ���ռ�����");						//11 
	arrayFields.Add ("�������ϼ��ʱ�Ƿ����¹����ۼ�");						//12 
	arrayFields.Add ("�ල����ͳ���Ƿ�׼ȷһ��");							//13 
	arrayFields.Add ("�ܱ��Ƿ�Ҫ��ʱͳ�Ʋ��ϱ�");						//14 
	arrayFields.Add ("�±��Ƿ�Ҫ��ʱͳ�Ʋ��ϱ�");						//15
	arrayFields.Add ("��־�ܱ��±�����¼����ල����ͳ�Ʊ��Ƿ�һһ��Ӧ");	//16
	arrayFields.Add ("����¼������֪ͨ���Ƿ�Ҫ��ʹ��");					//17
	arrayFields.Add ("�ල��������ͳ�Ʒ������Ƿ�Ҫ����д�빤����־�Ƿ��ܶ�Ӧ");	//18
	arrayFields.Add ("��������չʾ�Ƿ�Ҫ��ִ��");							//19 
	arrayFields.Add ("�ල��鹤���Ƿ��������������Ƿ��ܴﵽͶ�ʷ�Ҫ��");	//20 
	arrayFields.Add ("Ұ������ʱ�շֲ��Ƿ��ѧ�Ƿ�����Ч��ӳʩ��ȫò");	//21 
	arrayFields.Add ("������ʱ����ָ���Ƿ����Ҫ��������Ƿ�Ҫ��ִ��");	//22 
	arrayFields.Add ("��������������豸��������ʱ�Ƿ񳹵�ͳ���Ƿ���ȫ");	//23
	arrayFields.Add ("��鼤�����չ���ʱ�Ƿ�ȷ������������׼");				//24 
	arrayFields.Add ("�Ƿ��о�Ͷ�ʷ��Ͽɵ�ԭʼ��¼���۱�׼");				//25 
	arrayFields.Add ("ʩ���������صȸı����Ҫ����ʱ�Ƿ���Ͷ�ʷ����������");	//26 
	arrayFields.Add ("�Ƿ���Ͷ�ʷ�ִ�о������Ŀ������ʱ������Ϣ��ͨ");	//27 
	arrayFields.Add ("�Ƿ���ڳ��ÿ�Ҫ������");								//28 
	arrayFields.Add ("�Ƿ������ʩ����һ������Ͷ�ʷ�����");					//29 
	arrayFields.Add ("�Ƿ�����޹��뿪̽�������");							//30 
	arrayFields.Add ("�Ƿ����˽����˽���������ܰ���ͷ����");				//31 
	arrayFields.Add ("�Ƿ���ڶԳа����쵼��������");						//32 
	arrayFields.Add ("�Ƿ����������������⻯������");						//33 
	arrayFields.Add ("��龭�ල������Ұ�⼤�����Ƿ��Դ��ڲ��ϸ�����");	//34 
	arrayFields.Add ("��龭�ල������Ұ����յ��Ƿ��Դ��ڲ��ϸ�����");	//35
	arrayFields.Add ("��������־����㴦����Ƿ��������");				//36 
	arrayFields.Add ("Ұ���ֳ����50-100��ԭʼ��¼�Ƿ��ܵ������Ҫ��");		//37 
	arrayFields.Add ("����ֳ�ʩ�����������Ƿ���д׼ȷ��ȫ");				//38 
	arrayFields.Add ("�������鹤���Ƿ�Ҫ��ʩ�������Ƿ񾭼ල�Ͽ�");	//39 
	arrayFields.Add ("���Ұ�����ⲿλ������Ƿ���ƺ�ͬҪ��ִ��");		//40 
	arrayFields.Add ("�ֳ�����10���ߵļ첨������ֵ�Ƿ�ϸ�");				//41 
	arrayFields.Add ("Ҫ���ƾ�������鱬ը���ƾ�����Ƿ�Ҫ��ִ��");		//42 
	arrayFields.Add ("�¾��첨��ʩ��ʱ���첨���������Ƿ����Ҫ��");		//43 
	arrayFields.Add ("��������Ƿ��������ʩ�������Ƿ�׼ȷ");				//44 
	arrayFields.Add ("��ʩ������Ա�����۲�������ʶ��׼����ʵ���");			//45

	arrayFields.Add ("���μ���������");									//46
	arrayFields.Add ("����Ŀפ�Ӽල�Ƿ��ܼ���ʤ�μල����");				//47 
	arrayFields.Add ("�Ը���Ŀ�²��ල����Ҫ��");							//48 

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	return true;
}

/////////////////////////////////////////////////////////
//       ��Ŀ������ִ�о���Ѳ�ؼ���¼
//   ��0405��Ŀ������ִ�о���Ѳ�ؼ���¼  ��22
/////////////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport22(CDlgReportProperty &dlg)
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


	CString sTable="��0405��Ŀ������ִ�о���Ѳ�ؼ���¼";
	
	sSQL.Format ("select * from %s where ��Ŀ���='%s' and %s ",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo,
				(LPCTSTR)sStartDay);
	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}

	arrayFields.Add ("���");			//0
	arrayFields.Add ("��Ŀ���");			//1
	arrayFields.Add ("��Ŀ����");			//2
	arrayFields.Add ("ִ�о���");	//3 
	arrayFields.Add ("��");	//4 
	arrayFields.Add ("��");	//5 
	arrayFields.Add ("��");	//6 

	arrayFields.Add ("�Ƿ�Ҫ�����̽��������Ŀ�ල�����ƻ���ʽ�Ƿ�ͳһ");			//7
	arrayFields.Add ("�Ƿ�Ҫ�����̽��������Ŀ�ල�����ƻ���ʽ�Ƿ�ͳһ�������");	//8
	arrayFields.Add ("̽�����Ƿ�ͳһ�ල��������");								//9
	arrayFields.Add ("̽�����Ƿ�ͳһ�ල���������������");						//10
	arrayFields.Add ("̽�����Ƿ�ͳһ�ල�ܱ��±��ĸ�ʽ������");					//11
	arrayFields.Add ("̽�����Ƿ�ͳһ�ල�ܱ��±��ĸ�ʽ�������������");			//12
	arrayFields.Add ("̽�����Ƿ�ͳһ�ල��¼��ʽ");								//13
	arrayFields.Add ("̽�����Ƿ�ͳһ�ල��¼��ʽ�������");						//14
	arrayFields.Add ("̽�����Ƿ�ͳһ�ලչʾ���ϸ�ʽ");							//15
	arrayFields.Add ("̽�����Ƿ�ͳһ�ලչʾ���ϸ�ʽ�������");					//16
	arrayFields.Add ("̽�����Ƿ�淶�˼ල����ͳ�Ʊ��");						//17
	arrayFields.Add ("̽�����Ƿ�淶�˼ල����ͳ�Ʊ���������");				//18
	arrayFields.Add ("̽�����Ƿ�ͳһ�淶�˼ල�������ݸ�ʽ�������ʽ");			//19
	arrayFields.Add ("̽�����Ƿ�ͳһ�淶�˼ල�������ݸ�ʽ�������ʽ�������");	//20
	arrayFields.Add ("������������Ŀ�Ƿ�Ҫ�����EMAIL��ʽ�㱨");				//21
	arrayFields.Add ("������������Ŀ�Ƿ�Ҫ�����EMAIL��ʽ�㱨�������");		//22
	arrayFields.Add ("��Ͷ�ʷ��й��쵼�Ƿ�����ͨ�˼ල������ʶ");				//23
	arrayFields.Add ("��Ͷ�ʷ��й��쵼�Ƿ�����ͨ�˼ල������ʶ�������");		//24
	arrayFields.Add ("�Ƿ���Ͷ�ʷ������˹�˾���ļල��������˼·");				//25
	arrayFields.Add ("�Ƿ���Ͷ�ʷ������˹�˾���ļල��������˼·�������");		//26
	arrayFields.Add ("�Ƿ��˽�Ͷ�ʷ��Լල������Ҫ����ص�");					//27
	arrayFields.Add ("�Ƿ��˽�Ͷ�ʷ��Լල������Ҫ����ص��������");			//28
	arrayFields.Add ("�Ƿ��Ͷ�ʷ�������Ҫ�󴫴ﵽ����Ŀ�ල��Ա");				//29
	arrayFields.Add ("�Ƿ��Ͷ�ʷ�������Ҫ�󴫴ﵽ����Ŀ�ල��Ա�������");		//30
	arrayFields.Add ("�Ƿ��˽����Ŀ���ල������̬���");						//31
	arrayFields.Add ("�Ƿ��˽����Ŀ���ල������̬����������");				//32
	arrayFields.Add ("�Ƿ�Ҫ��Ѳ�ؼ���˸���Ŀ�ල����");						//33
	arrayFields.Add ("�Ƿ�Ҫ��Ѳ�ؼ���˸���Ŀ�ල�����������");				//34
	arrayFields.Add ("Ѳ�ؼ�������Ƿ���ȫ�淶");								//35
	arrayFields.Add ("Ѳ�ؼ�������Ƿ���ȫ�淶�������");						//36
	arrayFields.Add ("�Ƿ�Ҫ��Լ���֧�ֹ��������˰��ź�ʵʩ");				//37
	arrayFields.Add ("�Ƿ�Ҫ��Լ���֧�ֹ��������˰��ź�ʵʩ�������");		//38
	arrayFields.Add ("����֧���Ƿ�ﵽ��Ӧ�е�Ч��");							//39
	arrayFields.Add ("����֧���Ƿ�ﵽ��Ӧ�е�Ч���������");					//40
	arrayFields.Add ("������¼�Ƿ���ȫ׼ȷ");									//41
	arrayFields.Add ("������¼�Ƿ���ȫ׼ȷ�������");							//42
	arrayFields.Add ("�Ƿ�ʱ��Ͷ�ʷ��й��쵼������Ϣ��ͨ");					//43
	arrayFields.Add ("�Ƿ�ʱ��Ͷ�ʷ��й��쵼������Ϣ��ͨ�������");			//44
	arrayFields.Add ("�Ƿ�ʱ����Ŀ����������Ϣ��ͨ");						//45
	arrayFields.Add ("�Ƿ�ʱ����Ŀ����������Ϣ��ͨ�������");				//46
	arrayFields.Add ("����ʽ�ʹ���Ƿ񾭹���ʾ");								//47
	arrayFields.Add ("����ʽ�ʹ���Ƿ񾭹���ʾ�������");						//48
	arrayFields.Add ("�Ƿ�ע�سɱ���������");									//49
	arrayFields.Add ("�Ƿ�ע�سɱ����������������");							//50
	arrayFields.Add ("����̬���Ƿ����������и��");								//51
	arrayFields.Add ("����̬���Ƿ����������и���������");						//52	
	arrayFields.Add ("�Ƿ��ܴ����Կ�չ�ල������");							//53
	arrayFields.Add ("�Ƿ��ܴ����Կ�չ�ල�������������");					//54
	arrayFields.Add ("������������Ƿ񲻸����⻯");								//55
	arrayFields.Add ("������������Ƿ񲻸����⻯�������");						//56



	CTableDate dateStart;

	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	return true;

}

/////////////////////////////////////////////////////////////
//    ��Ŀ�������ֳ��ලѲ�ؼ���¼
//   ��0406��Ŀ�������ֳ��ලѲ�ؼ���¼  ��23
/////////////////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport23(CDlgReportProperty &dlg)
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


	CString sTable="��0406��Ŀ�������ֳ��ලѲ�ؼ���¼";
	
	sSQL.Format ("select * from %s where ��Ŀ���='%s' and %s ",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo,
				(LPCTSTR)sStartDay);
	if(sEndDay!="")
	{
		sSQL+=" and "+sEndDay;
	}

	arrayFields.Add ("��Ŀ���");			//0
	arrayFields.Add ("��Ŀ����");			//1
	arrayFields.Add ("�ֳ��ල");			//2
	arrayFields.Add ("��ͬ��");	//3 
	arrayFields.Add ("��");	//4 
	arrayFields.Add ("��");	//5 
	arrayFields.Add ("��");	//6 

	arrayFields.Add ("�ල�ƻ��Ƿ�ִ�о��������Ƿ�̽��ͳһ��ʽ");			//7
	arrayFields.Add ("�ල�ƻ��Ƿ�ִ�о��������Ƿ�̽��ͳһ��ʽ�������");	//8
	arrayFields.Add ("�Ƿ�̽��ͳһ�ļල��������չʾ��ִ��");								//9
	arrayFields.Add ("�Ƿ�̽��ͳһ�ļල��������չʾ��ִ���������");						//10
	arrayFields.Add ("�Ƿ�Ҫ���¼�ල������־");					//11
	arrayFields.Add ("�Ƿ�Ҫ���¼�ල������־�������");			//12
	arrayFields.Add ("����ù�������Ƿ�ͳһ��ʽ��Ҫ����д");								//13
	arrayFields.Add ("����ù�������Ƿ�ͳһ��ʽ��Ҫ����д�������");						//14
	arrayFields.Add ("�Ƿ�Ҫ���ռ�����ල��������");							//15
	arrayFields.Add ("�Ƿ�Ҫ���ռ�����ල���������������");					//16
	arrayFields.Add ("�ܱ��Ƿ�Ҫ��ʱͳ�Ʋ��ϱ�");						//17
	arrayFields.Add ("�ܱ��Ƿ�Ҫ��ʱͳ�Ʋ��ϱ��������");				//18
	arrayFields.Add ("�±��Ƿ�Ҫ��ʱͳ�Ʋ��ϱ�");			//19
	arrayFields.Add ("�±��Ƿ�Ҫ��ʱͳ�Ʋ��ϱ��������");	//20
	arrayFields.Add ("��־�ܱ��±�����¼ͳ�Ʊ���Ƿ����໥��Ӧ");				//21
	arrayFields.Add ("��־�ܱ��±�����¼ͳ�Ʊ���Ƿ����໥��Ӧ�������");		//22
	arrayFields.Add ("����¼������֪ͨ���Ƿ�Ҫ��ʹ��");				//23
	arrayFields.Add ("����¼������֪ͨ���Ƿ�Ҫ��ʹ���������");		//24
	arrayFields.Add ("�Ƿ�������д�ල��������ͳ�Ʒ�����");				//25
	arrayFields.Add ("�Ƿ�������д�ල��������ͳ�Ʒ������������");		//26
	arrayFields.Add ("��������չʾ�Ƿ����̽��ͳһ�淶");					//27
	arrayFields.Add ("��������չʾ�Ƿ����̽��ͳһ�淶�������");			//28
	arrayFields.Add ("ʩ���������صȸı����Ҫ����ʱ�Ƿ���Ͷ�ʷ����������");				//29
	arrayFields.Add ("ʩ���������صȸı����Ҫ����ʱ�Ƿ���Ͷ�ʷ�����������������");		//30
	arrayFields.Add ("�Ƿ��о�Ͷ�ʷ��Ͽɵļ������չ�������������׼");						//31
	arrayFields.Add ("�Ƿ��о�Ͷ�ʷ��Ͽɵļ������չ�������������׼�������");				//32
	arrayFields.Add ("�Ƿ��о�Ͷ�ʷ��Ͽɵ�ԭʼ��¼���۱�׼");						//33
	arrayFields.Add ("�Ƿ��о�Ͷ�ʷ��Ͽɵ�ԭʼ��¼���۱�׼�������");				//34
	arrayFields.Add ("�Ƿ��о�Ͷ�ʷ��Ͽɵ�ԭʼ��¼���۱�׼�������");								//35
	arrayFields.Add ("�Ƿ���Ͷ�ʷ�ִ�о������Ŀ������ʱ������Ϣ��ͨ");						//36
	arrayFields.Add ("�Ƿ���Ͷ�ʷ�ִ�о������Ŀ������ʱ������Ϣ��ͨ�������");				//37
	arrayFields.Add ("����С���㱨�Ƿ�ץס�ص������Ƿ�����");		//38
	arrayFields.Add ("����С���㱨�Ƿ�ץס�ص������Ƿ������������");							//39
	arrayFields.Add ("�Լ׷��ܼ��ִ�о����������Ҫ���Ƿ�����������ʵ");					//40
	arrayFields.Add ("�Լ׷��ܼ��ִ�о����������Ҫ���Ƿ�����������ʵ�������");									//41
	arrayFields.Add ("��ʩ�����˽��Ƿ������ල����������Υ��");							//42
	arrayFields.Add ("��ʩ�����˽��Ƿ������ල����������Υ���������");					//43
	arrayFields.Add ("��Ͷ�ʷ��˽��Ƿ������Գа����쵼��������");			//44
	arrayFields.Add ("��Ͷ�ʷ��˽��Ƿ������Գа����쵼���������������");						//45
	arrayFields.Add ("��ʩ�����˽��Ƿ�������������������⻯");				//46
	arrayFields.Add ("��ʩ�����˽��Ƿ�������������������⻯�������");								//47
	arrayFields.Add ("��龭�ල������Ұ�⼤������֤����Ƿ����");						//48
	arrayFields.Add ("��龭�ල������Ұ�⼤������֤����Ƿ�����������");									//49
	arrayFields.Add ("��龭�ල������Ұ����յ���֤����Ƿ����");							//50
	arrayFields.Add ("��龭�ල������Ұ����յ���֤����Ƿ�����������");								//51
	arrayFields.Add ("��������־����㴦�����֤����Ƿ����");						//52	
	arrayFields.Add ("��������־����㴦�����֤����Ƿ�����������");							//53
	arrayFields.Add ("�ֳ���鲿��ԭʼ��¼�Ƿ��ܴﵽ���Ҫ��");					//54
	arrayFields.Add ("�ֳ���鲿��ԭʼ��¼�Ƿ��ܴﵽ���Ҫ���������");								//55
	arrayFields.Add ("���Ұ�����ⲿλ������Ƿ���ƺ�ͬҪ��ִ��");						//56
	arrayFields.Add ("�ֳ����첨������ֵ�Ƿ�ϸ�");						//57
	arrayFields.Add ("�ֳ����첨������ֵ�Ƿ�ϸ��������");						//58
	arrayFields.Add ("�Ƿ񾭳���ʩ������Ա����������ʶ��׼����ʵ���");						//59
	arrayFields.Add ("�Ƿ񾭳���ʩ������Ա����������ʶ��׼����ʵ����������");						//60

	CTableDate dateStart;

	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	return true;
}

/////////////////////////////////////////////////////
// ��̽������Ŀ���У��գ�ʱЧͳ�Ʊ�
// ��0301�������ձ�  ��24
/////////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport24(CDlgReportProperty &dlg)
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

	arrayFields.Add ("���");			//0
	arrayFields.Add ("��Ŀ���");			//1
	arrayFields.Add ("פ�Ӽල");			//2
	arrayFields.Add ("���߱��");	//3 
	arrayFields.Add ("��");	//4 
	arrayFields.Add ("��");	//5 
	arrayFields.Add ("��");	//6 

	arrayFields.Add ("�뿪פ��ʱ��");			//7
	arrayFields.Add ("���﹤��ʱ��");			//8
	arrayFields.Add ("��������ʱ��");			//9
	arrayFields.Add ("����ʱ��");				//10
	arrayFields.Add ("ĩ��ʱ��");				//11
	arrayFields.Add ("�������ʱ��");			//12
	arrayFields.Add ("��������Ӱ��");			//13
	arrayFields.Add ("�豸����Ӱ��");			//14
	arrayFields.Add ("��������Ӱ��");			//15
	arrayFields.Add ("��Ȼ����Ӱ��");			//16
	arrayFields.Add ("�ط���ϵӰ��");			//17
	arrayFields.Add ("��������Ӱ��");			//18
	arrayFields.Add ("ʵ�ʷ���ʱ��");			//19
	arrayFields.Add ("�������");				//20
	arrayFields.Add ("ʱЧ�ձ�ע");				//21

	arrayFields.Add ("��������1����");			//22
	arrayFields.Add ("��������2����");			//23
	arrayFields.Add ("��������3����");			//24
	arrayFields.Add ("��������4����");			//25
	arrayFields.Add ("��������5����");			//26
	arrayFields.Add ("��������6����");			//27
	arrayFields.Add ("��������7����");			//28
	arrayFields.Add ("��������8����");			//29
	arrayFields.Add ("��������9����");			//30
	arrayFields.Add ("��������10����");			//31

	arrayFields.Add ("��ϼ���1����");			//32
	arrayFields.Add ("��ϼ���2����");			//33
	arrayFields.Add ("��ϼ���3����");			//34
	arrayFields.Add ("��ϼ���4����");			//35
	arrayFields.Add ("��ϼ���5����");			//36
	arrayFields.Add ("��ϼ���6����");			//37
	arrayFields.Add ("��ϼ���7����");			//38
	arrayFields.Add ("��ϼ���8����");			//39
	arrayFields.Add ("��ϼ���9����");			//40
	arrayFields.Add ("��ϼ���10����");			//41



	arrayFields.Add ("��ʵ��������");			//42
	arrayFields.Add ("פ�Ӽල");				//43

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	return true;
}

///////////////////////////////////////////////////////////
//��̽������Ŀ      ��ȣ��£�ʱЧ������
//��0301�������ձ�  ��25
///////////////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport25(CDlgReportProperty &dlg)
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

	arrayFields.Add ("���");			//0
	arrayFields.Add ("��Ŀ���");		//1
	arrayFields.Add ("פ�Ӽල");		//2
	arrayFields.Add ("���߱��");		//3 
	arrayFields.Add ("��");				//4 
	arrayFields.Add ("��");				//5 
	arrayFields.Add ("��");				//6 

	arrayFields.Add ("���ղ��߿���");			//7
	arrayFields.Add ("���ղ����깤");			//8

	arrayFields.Add ("��������1����");			//9
	arrayFields.Add ("��������2����");			//10
	arrayFields.Add ("��������3����");			//11
	arrayFields.Add ("��������4����");			//12
	arrayFields.Add ("��������5����");			//13
	arrayFields.Add ("��������6����");			//14
	arrayFields.Add ("��������7����");			//15
	arrayFields.Add ("��������8����");			//16
	arrayFields.Add ("��������9����");			//17
	arrayFields.Add ("��������10����");			//18
	
	arrayFields.Add ("��ʵ��������");			//19
	arrayFields.Add ("�����յ�");				//20

	arrayFields.Add ("��������ʩ��");				//21
	arrayFields.Add ("���ռ���ͣ��");				//22
	arrayFields.Add ("������Ȼͣ��");				//23
	arrayFields.Add ("��������ͣ��");				//24

	arrayFields.Add ("�꾮����");					//25
	arrayFields.Add ("�ϸ�С�������");				//26
	arrayFields.Add ("�ϸ�΢�⾮����");				//27

	arrayFields.Add ("ʱЧ�±�ע");					//28

	arrayFields.Add ("��ϼ���1����");			//29
	arrayFields.Add ("��ϼ���2����");			//30
	arrayFields.Add ("��ϼ���3����");			//31
	arrayFields.Add ("��ϼ���4����");			//32
	arrayFields.Add ("��ϼ���5����");			//33
	arrayFields.Add ("��ϼ���6����");			//34
	arrayFields.Add ("��ϼ���7����");			//35
	arrayFields.Add ("��ϼ���8����");			//36
	arrayFields.Add ("��ϼ���9����");			//37
	arrayFields.Add ("��ϼ���10����");			//38

	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	return true;
}
