
#include "stdafx.h"
#include "QCDB.h"
#include "ReportDoc.h"
#include "DlgReportProperty.h"
#include "MyDate.h"

BOOL CReportDoc::GetDataForReport01(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;

	CString sTable="��0201����";
	sSQL.Format ("select * from %s where ��Ŀ���='%s'",(LPCTSTR)sTable,(LPCTSTR)m_sProjectNo);

	arrayFields.Add ("��������");			//0

	arrayFields.Add ("����ڵ���ʼ׮��");	//1
	arrayFields.Add ("����ڵ���ֹ׮��");
	arrayFields.Add ("��������ǳ���");
	arrayFields.Add ("��ƶ�ά��������");

	arrayFields.Add ("������߿�ʼ�ߺ�");	//5
	arrayFields.Add ("���������ֹ�ߺ�");
	arrayFields.Add ("������߼��");

	arrayFields.Add ("����ڵ㿪ʼ���");
	arrayFields.Add ("����ڵ���ֹ���");
	arrayFields.Add ("����ڵ���");		//10
	
	arrayFields.Add ("��ƽ����߿�ʼ�ߺ�");
	arrayFields.Add ("��ƽ�������ֹ�ߺ�");
	arrayFields.Add ("��ƽ����߼��");

	arrayFields.Add ("��ƽ��յ㿪ʼ���");
	arrayFields.Add ("��ƽ��յ���ֹ���");	//15
	arrayFields.Add ("��ƽ��յ���");
	arrayFields.Add ("��ƽ����߳���");

	arrayFields.Add ("�����ά��������");
	arrayFields.Add ("���С�������");
	arrayFields.Add ("���΢�⾮����");		//20

	arrayFields.Add ("פ�Ӽල");		//21


	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};
	return TRUE;
}



// ���Ϳ�̽����˾     ���      ̽��        ��̽������Ŀ
//����0103���������ָ�ꡢĿ�Ĳ�ָ�꣨��0104������Ҫ���Ų�ָ��ͳ�Ʊ���0105��

BOOL CReportDoc::GetDataForReport02(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	CString sTable="��0103��Ŀ�������ͳ�Ʊ�";
	sSQL.Format ("select * from %s where ��Ŀ���='%s'",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo);
	arrayFields.Add ("ȫ��һ��Ʒ��ָ��");	//0
	arrayFields.Add ("ȫ��һ��Ʒ��Ҫ��");
	arrayFields.Add ("ȫ���ϸ���ָ��");
	arrayFields.Add ("ȫ���ϸ���Ҫ��");
	arrayFields.Add ("ȫ����Ʒ��ָ��");	//4

	arrayFields.Add ("ȫ����Ʒ��Ҫ��");
	arrayFields.Add ("ȫ��������ָ��");
	arrayFields.Add ("ȫ��������Ҫ��");
	arrayFields.Add ("�����߿�����ָ��");
	arrayFields.Add ("�����߿�����Ҫ��");		//9
	
	arrayFields.Add ("�����߷�Ʒ��ָ��");
	arrayFields.Add ("�����߷�Ʒ��Ҫ��");
	arrayFields.Add ("ȫ���������Ϻϸ���ָ��");
	arrayFields.Add ("ȫ���������Ϻϸ���Ҫ��");
	arrayFields.Add ("ȫ�����������Ϻϸ���ָ��");	//14

	arrayFields.Add ("ȫ�����������Ϻϸ���Ҫ��");
	arrayFields.Add ("ȫ���ֳ�������ָ��");
	arrayFields.Add ("ȫ���ֳ�������Ҫ��");


	CTableDate dateFrom;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateFrom,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	if(GetRecordQty ()==0)
	{
		TRACEERROR("û�з�����������Ŀ:"+sSQL);
		return false;
	}

	if(GetRecordQty ()>1)
	{
		TRACEERROR("������������Ŀ����һ��:"+sSQL);
		return false;
	}

	CStringArray *pRecord=GetRecord (0);
	if(!pRecord)
	{
		TRACEERROR("�޷���ü�¼:"+sSQL);
		return false;
	}

	m_arrayProject1.Copy (*pRecord);

	///////////////////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////////////////
	sTable="��0104Ŀ�Ĳ�ָ��ͳ�Ʊ�";
	sSQL.Format ("select * from %s where ��Ŀ���='%s'",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo);
	arrayFields.RemoveAll ();

	arrayFields.Add ("Ŀ�Ĳ�");			//0

	arrayFields.Add ("����");	//1
	arrayFields.Add ("T0ʱ��");
	arrayFields.Add ("��Ƶ��ʼ");
	arrayFields.Add ("��Ƶ��ֹ");
	arrayFields.Add ("�ֱ�����ʼ");	//5

	arrayFields.Add ("�ֱ�����ֹ");
	arrayFields.Add ("�������ʼ");
	arrayFields.Add ("�������ֹ");
	arrayFields.Add ("������ʼ");
	arrayFields.Add ("������ֹ");		//10
	
	arrayFields.Add ("Ҫ��");
	arrayFields.Add ("��ע");

	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateFrom,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	////////////////////////////////////////
	//
	////////////////////////////////////////
	sTable="��0105���Ų�ָ��";
	sSQL.Format ("select * from %s where ��Ŀ���='%s'",
				(LPCTSTR)sTable,
				(LPCTSTR)m_sProjectNo);
	arrayFields.RemoveAll ();

	arrayFields.Add ("���Ų�");			//0

	arrayFields.Add ("����");	//1
	arrayFields.Add ("��Ƶ����ʼ");
	arrayFields.Add ("��Ƶ����ֹ");
	arrayFields.Add ("���ٶ���ʼ");	//4

	arrayFields.Add ("���ٶ���ֹ"); //5
	arrayFields.Add ("�Ӳ�����ʼ");
	arrayFields.Add ("�Ӳ�����ֹ");
	arrayFields.Add ("ǿ����ʼ");
	arrayFields.Add ("ǿ����ֹ");		//9
	
	arrayFields.Add ("Ҫ��");    // 10
	arrayFields.Add ("��ע");

	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateFrom,&arrayFields,&m_docVice,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};
	return TRUE;
}


BOOL CReportDoc::GetDataForReport03(CDlgReportProperty &dlg)
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

	CString sTable="��0301�������ձ�";
	sSQL.Format ("select * from %s where ��Ŀ���='%s' and %s",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo,
					(LPCTSTR)sEndDay);

	arrayFields.Add ("���߱��");		//0

	arrayFields.Add ("��");			//1
	arrayFields.Add ("��");			//2
	arrayFields.Add ("��");			//3
	arrayFields.Add ("��Ŀ���");	//4
	arrayFields.Add ("��ʵ������");	//5
	arrayFields.Add ("��ʵС�������");	
	arrayFields.Add ("��ʵ΢�⾮����");	
	arrayFields.Add ("����һ��");
	arrayFields.Add ("��������");
	arrayFields.Add ("�����յ�");		//10
	arrayFields.Add ("������Ʒ");
	arrayFields.Add ("��鼤������");		
	arrayFields.Add ("�ϸ񼤷�����");
	arrayFields.Add ("�����յ���");
	arrayFields.Add ("�ϸ���յ���");	//15
	arrayFields.Add ("���ߺϸ�֪ͨ�����");
	arrayFields.Add ("�¼�");			//
	arrayFields.Add ("�ռ�");			//
	arrayFields.Add ("����������");	//
	arrayFields.Add ("�ϸ��������");	//20
	arrayFields.Add ("�ֳ����");		//
	arrayFields.Add ("����¼");			//
	arrayFields.Add ("�������");		//
	arrayFields.Add ("������Ŀ�������");	//
	arrayFields.Add ("�ල�������");		//25
	arrayFields.Add ("�²��ල�����ص�");	//
	arrayFields.Add ("פ�Ӽල");			//27


	arrayFields.Add ("��������1����");		//28
	arrayFields.Add ("��������2����");		//29
	arrayFields.Add ("��������3����");		//30
	arrayFields.Add ("��������4����");		//31
	arrayFields.Add ("��������5����");		//32
	arrayFields.Add ("��������6����");		//33
	arrayFields.Add ("��������7����");		//34
	arrayFields.Add ("��������8����");		//35
	arrayFields.Add ("��������9����");		//36
	arrayFields.Add ("��������10����");		//37


	arrayFields.Add ("��ϼ���1����");		//38
	arrayFields.Add ("��ϼ���2����");		//39
	arrayFields.Add ("��ϼ���3����");		//40
	arrayFields.Add ("��ϼ���4����");		//41
	arrayFields.Add ("��ϼ���5����");		//42
	arrayFields.Add ("��ϼ���6����");		//43
	arrayFields.Add ("��ϼ���7����");		//44
	arrayFields.Add ("��ϼ���8����");		//45
	arrayFields.Add ("��ϼ���9����");		//46
	arrayFields.Add ("��ϼ���10����");		//47


	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};
	return TRUE;
}

//��̽������Ŀ�������±���
BOOL CReportDoc::GetDataForReport04(CDlgReportProperty &dlg)
{
	CQCDBApp *pApp=(CQCDBApp *)AfxGetApp();
	CStringArray arrayFields;
	CString sSQL;
	int i=0,j=0;


	CString sEndDay=MakeDateCmpString(	"��",
						"��",
						"��",
						"<=",
						dlg.m_iEndYear ,
						dlg.m_iEndMonth ,
						dlg.m_iEndDay );

	CString sTable="��0301�������ձ�";
	sSQL.Format ("select * from %s where ��Ŀ���='%s' and %s",
					(LPCTSTR)sTable,
					(LPCTSTR)m_sProjectNo,
					(LPCTSTR)sEndDay);

	arrayFields.Add ("���߱��");		//0

	arrayFields.Add ("��");			//1
	arrayFields.Add ("��");			//2
	arrayFields.Add ("��");			//3
	arrayFields.Add ("��Ŀ���");	//4
	arrayFields.Add ("��ʵ������");	//5
	arrayFields.Add ("��ʵС�������");	
	arrayFields.Add ("��ʵ΢�⾮����");	
	arrayFields.Add ("����һ��");
	arrayFields.Add ("��������");
	arrayFields.Add ("�����յ�");		//10
	arrayFields.Add ("������Ʒ");
	arrayFields.Add ("��鼤������");		
	arrayFields.Add ("�ϸ񼤷�����");
	arrayFields.Add ("�����յ���");
	arrayFields.Add ("�ϸ���յ���");	//15
	arrayFields.Add ("���ߺϸ�֪ͨ�����");
	arrayFields.Add ("�¼�");			//
	arrayFields.Add ("�ռ�");			//
	arrayFields.Add ("����������");	//
	arrayFields.Add ("�ϸ��������");	//20
	arrayFields.Add ("�ֳ����");		//
	arrayFields.Add ("����¼");			//
	arrayFields.Add ("�������");		//
	arrayFields.Add ("������Ŀ�������");	//
	arrayFields.Add ("�ල�������");		//25
	arrayFields.Add ("�²��ල�����ص�");	//
	arrayFields.Add ("������Ŀ�ſ�");		//
	arrayFields.Add ("פ�Ӽල");
	arrayFields.Add ("���ղ��߿���");
	arrayFields.Add ("���ղ����깤");		// 30

	arrayFields.Add ("��������1����");		//31
	arrayFields.Add ("��������2����");		//32
	arrayFields.Add ("��������3����");		//33
	arrayFields.Add ("��������4����");		//34
	arrayFields.Add ("��������5����");		//35
	arrayFields.Add ("��������6����");		//36
	arrayFields.Add ("��������7����");		//37
	arrayFields.Add ("��������8����");		//38
	arrayFields.Add ("��������9����");		//39
	arrayFields.Add ("��������10����");		//40


	arrayFields.Add ("��ϼ���1����");		//41
	arrayFields.Add ("��ϼ���2����");		//42
	arrayFields.Add ("��ϼ���3����");		//43
	arrayFields.Add ("��ϼ���4����");		//44
	arrayFields.Add ("��ϼ���5����");		//45
	arrayFields.Add ("��ϼ���6����");		//46
	arrayFields.Add ("��ϼ���7����");		//47
	arrayFields.Add ("��ϼ���8����");		//48
	arrayFields.Add ("��ϼ���9����");		//49
	arrayFields.Add ("��ϼ���10����");		//50


	CDataBrowseDoc docBrowse;
	CTableDate dateStart;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateStart,&arrayFields,&docBrowse,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	///////////////////////////////////////
	// ���㹲�ж��������ߣ�����¼���ǵ����֣�
	///////////////////////////////////////
	CStringArray arrayLineNames;
	CStringArray *pRecord=NULL;
	CString sLine;
	bool bExist=false;
	for(i=0;i<docBrowse.GetRecordQty ();i++)
	{
		pRecord=docBrowse.GetRecord (i);
		
		sLine=pRecord->GetAt (0);
		for(j=0;j<arrayLineNames.GetCount ();j++)
		{
			bExist=false;
			if(sLine==arrayLineNames.GetAt (j))
			{
				bExist=true;
				break;
			}
		}
		if(!bExist)
		{
			arrayLineNames.Add (sLine);
		}
	}

	CDailyReportRecord *pMRR=new CDailyReportRecord[arrayLineNames.GetCount ()+2];
	CDailyReportRecord reportTotal;
	CDailyReportRecord reportMonth;


	for(i=0;i<arrayLineNames.GetCount ();i++)
	{
		pMRR[i].sLineName=arrayLineNames.GetAt (i);
	}

	////////////////////////////////////////
	//  ������Щ���ߵ�������ݣ�
	////////////////////////////////////////
	int iPos=0;
	CMyDate dateToday;

	for(i=0;i<docBrowse.GetRecordQty ();i++)
	{
		pRecord=docBrowse.GetRecord (i);
		
		sLine=pRecord->GetAt (0);
		iPos=-1;
		for(j=0;j<arrayLineNames.GetCount ();j++)
		{
			if(sLine==arrayLineNames.GetAt (j))
			{
				iPos=j;	
				break;
			}
		}
		if(iPos==-1)
		{
			ASSERT(false);
			return false;
		}

		dateToday.Set (pRecord->GetAt (1),pRecord->GetAt (2),pRecord->GetAt (3));
		
		// ���ڣ�
		if(IsTrue(pRecord->GetAt (29)))
		{
			pMRR[iPos].iStartYear = dateToday.GetYear();
			pMRR[iPos].iStartMonth =  dateToday.GetMonth ();
			pMRR[iPos].iStartDay =  dateToday.GetDay ();
		}

		if(IsTrue(pRecord->GetAt (30)))
		{
			pMRR[iPos].iEndYear =  dateToday.GetYear();
			pMRR[iPos].iEndMonth =  dateToday.GetMonth();
			pMRR[iPos].iEndDay =  dateToday.GetDay();
		}

		// �ۼƣ�
		for(j=31;j<=50;j++)
		{
			reportTotal.iShotQty +=stof(pRecord->GetAt(j));
		}


		reportTotal.fKilometer +=stof(pRecord->GetAt(5));
		reportTotal.iRefraction +=stof(pRecord->GetAt(6));
		reportTotal.iMicroSurveyWell +=stof(pRecord->GetAt(7));
		reportTotal.iFirstClass +=stof(pRecord->GetAt(8));
		reportTotal.iSecondClass +=stof(pRecord->GetAt(9));
		reportTotal.iEmptyPoint +=stof(pRecord->GetAt(10));
		reportTotal.iBadPoint +=stof(pRecord->GetAt(11));
		reportTotal.iInspectedShot +=stof(pRecord->GetAt(12));

		reportTotal.iShotValid +=stof(pRecord->GetAt(13));
		reportTotal.iInspectedRcv +=stof(pRecord->GetAt(14));
		reportTotal.iRcvValid +=stof(pRecord->GetAt(15));
		reportTotal.iLineValid +=stof(pRecord->GetAt(16));
		reportTotal.iMonthlyCheck +=stof(pRecord->GetAt(17));
		reportTotal.iDailyCheck +=stof(pRecord->GetAt(18));
		reportTotal.iSurveyMark +=stof(pRecord->GetAt(19));
		reportTotal.iValidSurveyMark +=stof(pRecord->GetAt(20));
		reportTotal.iOnPostInspect +=stof(pRecord->GetAt(21));
		reportTotal.iMemo +=stof(pRecord->GetAt(22));

		// �����ۼƣ�
		if(dateToday>=CMyDate (m_iStartYear,m_iStartMonth,m_iStartDay))
		{
			for(j=31;j<=50;j++)
			{
				pMRR[iPos].iShotQty +=stof(pRecord->GetAt(j));
			}


			pMRR[iPos].fKilometer +=stof(pRecord->GetAt(5));
			pMRR[iPos].iRefraction +=stof(pRecord->GetAt(6));
			pMRR[iPos].iMicroSurveyWell +=stof(pRecord->GetAt(7));
			pMRR[iPos].iFirstClass +=stof(pRecord->GetAt(8));
			pMRR[iPos].iSecondClass +=stof(pRecord->GetAt(9));
			pMRR[iPos].iEmptyPoint +=stof(pRecord->GetAt(10));
			pMRR[iPos].iBadPoint +=stof(pRecord->GetAt(11));
			pMRR[iPos].iInspectedShot +=stof(pRecord->GetAt(12));

			pMRR[iPos].iShotValid +=stof(pRecord->GetAt(13));
			pMRR[iPos].iInspectedRcv +=stof(pRecord->GetAt(14));
			pMRR[iPos].iRcvValid +=stof(pRecord->GetAt(15));
			pMRR[iPos].iLineValid +=stof(pRecord->GetAt(16));
			pMRR[iPos].iMonthlyCheck +=stof(pRecord->GetAt(17));
			pMRR[iPos].iDailyCheck +=stof(pRecord->GetAt(18));
			pMRR[iPos].iSurveyMark +=stof(pRecord->GetAt(19));
			pMRR[iPos].iValidSurveyMark +=stof(pRecord->GetAt(20));
			pMRR[iPos].iOnPostInspect +=stof(pRecord->GetAt(21));
			pMRR[iPos].iMemo +=stof(pRecord->GetAt(22));
			pMRR[iPos].sTags +=pRecord->GetAt(23);

			pMRR[iPos].sProjectRun +=pRecord->GetAt(24);
			pMRR[iPos].sProjectWork +=pRecord->GetAt(25);
			pMRR[iPos].sNextStep +=pRecord->GetAt(26);
			pMRR[iPos].sProjectSummary +=pRecord->GetAt(27);
			
			pMRR[iPos].sMonitor =pRecord->GetAt(28);

			for(j=31;j<=50;j++)
			{
				reportMonth.iShotQty +=stof(pRecord->GetAt(j));
			}

			reportMonth.fKilometer +=stof(pRecord->GetAt(5));
			reportMonth.iRefraction +=stof(pRecord->GetAt(6));
			reportMonth.iMicroSurveyWell +=stof(pRecord->GetAt(7));
			reportMonth.iFirstClass +=stof(pRecord->GetAt(8));
			reportMonth.iSecondClass +=stof(pRecord->GetAt(9));
			reportMonth.iEmptyPoint +=stof(pRecord->GetAt(10));
			reportMonth.iBadPoint +=stof(pRecord->GetAt(11));
			reportMonth.iInspectedShot +=stof(pRecord->GetAt(12));

			reportMonth.iShotValid +=stof(pRecord->GetAt(13));
			reportMonth.iInspectedRcv +=stof(pRecord->GetAt(14));
			reportMonth.iRcvValid +=stof(pRecord->GetAt(15));
			reportMonth.iLineValid +=stof(pRecord->GetAt(16));
			reportMonth.iMonthlyCheck +=stof(pRecord->GetAt(17));
			reportMonth.iDailyCheck +=stof(pRecord->GetAt(18));
			reportMonth.iSurveyMark +=stof(pRecord->GetAt(19));
			reportMonth.iValidSurveyMark +=stof(pRecord->GetAt(20));
			reportMonth.iOnPostInspect +=stof(pRecord->GetAt(21));
			reportMonth.iMemo +=stof(pRecord->GetAt(22));

			reportMonth.sProjectRun+=pRecord->GetAt(24);
			reportMonth.sProjectWork+=pRecord->GetAt(25);
			reportMonth.sNextStep+=pRecord->GetAt(26);
			reportMonth.sProjectSummary+=pRecord->GetAt(27);
			reportMonth.sProblem="";			//32
		}
	}

	////////////////////////////////////
	// ���ּ����ĵ����� �ڱ��0402�ල��鱸��¼ ��
	////////////////////////////////////
	sTable="��0402�ල��鱸��¼";
	arrayFields.RemoveAll ();
	arrayFields.Add ("����������");		//0
	arrayFields.Add ("�����");		//1
	arrayFields.Add ("�����");		//2
	arrayFields.Add ("�����");		//3
	arrayFields.Add ("�����Ŀ��λ��");		//4
	arrayFields.Add ("����������");		//5

	CTableDate dateFrom;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateFrom,&arrayFields,&docBrowse,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};

	for(i=0;i<docBrowse.GetRecordQty ();i++)
	{
		pRecord=docBrowse.GetRecord (i);
		dateToday.Set (pRecord->GetAt (1),pRecord->GetAt (2),pRecord->GetAt (3));
		if(dateToday>= CMyDate(m_iStartYear,m_iStartMonth,m_iStartDay))
		{
			reportMonth.sProblem+=pRecord->GetAt (4);
			reportMonth.sProblem+=pRecord->GetAt (5);
		}
	}

	////////////////////////////////////
	// �����ݷŵ����ĵ��У�
	////////////////////////////////////
	CStringArray arrayNames,arrayTypes;

	pMRR[0].GetItemNames(arrayNames, arrayTypes);


	CreateDBFile ();
	SetField(arrayNames, arrayTypes);

	CStringArray arrayRecord;
	for(i=0;i<arrayLineNames.GetCount ();i++)
	{
		pMRR[i].sLineName=GetLineName(pMRR[i].sLineName);
		pMRR[i].WriteIntoArray(arrayRecord);
		AppendRecord(&arrayRecord);
	}

	// �������ۼ�����:
	reportMonth.WriteIntoArray(arrayRecord);
	AppendRecord(&arrayRecord);

	// �������ۼ�����:
	reportTotal.WriteIntoArray(arrayRecord);
	AppendRecord(&arrayRecord);

	delete []pMRR;


	return TRUE;
}


////////////////////////////////////////////////////
//�� ̽ �� �� �� �� ר ҵ �� �� �� �� ��
////////////////////////////////////////////////////
BOOL CReportDoc::GetDataForReport05(CDlgReportProperty &dlg)
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

	CString sTable="��0302�����ල�ձ�";
	sSQL.Format ("select * from %s where %s",
					(LPCTSTR)sTable,
					(LPCTSTR)sEndDay);


	arrayFields.Add ("����������");		//0

	arrayFields.Add ("��");			//1
	arrayFields.Add ("��");			//2
	arrayFields.Add ("��");			//3
	arrayFields.Add ("����������");	//4
	arrayFields.Add ("�ල��ʵ����");	//5
	arrayFields.Add ("�ල��ʵ��������");	
	arrayFields.Add ("�ල��ʵ�������");	
	arrayFields.Add ("�ල��ʵ�������");    // �����ʵ�λ��
	arrayFields.Add ("���������X");
	arrayFields.Add ("���������Y");		//10
	arrayFields.Add ("��󸴲�ϲ�X");
	arrayFields.Add ("��󸴲�ϲ�Y");	
	arrayFields.Add ("��󸴲�ϲ�H");	
	arrayFields.Add ("���⾫��X");
	arrayFields.Add ("���⾫��Y");	//15
	arrayFields.Add ("���⾫��H");	//16
	arrayFields.Add ("Ұ���������־");
	arrayFields.Add ("Ұ���������λ");			//
	arrayFields.Add ("Ұ���鸴�����");			//
	arrayFields.Add ("Ұ����ʩ������");	//20
	arrayFields.Add ("����¼");	//21
	arrayFields.Add ("��ע");		//
	arrayFields.Add ("���������������");			//
	arrayFields.Add ("�ල�������");		//
	arrayFields.Add ("�������⼰�������");	//25
	arrayFields.Add ("���ܲ����ල�����ص�");		//26
	arrayFields.Add ("����");	//
	arrayFields.Add ("�����ල");		// 28
	arrayFields.Add ("��Ŀ���");		// 29


	CTableDate dateFrom;
	if(!pApp->m_dt.GetData ("",0,sTable,sSQL,dateFrom,&arrayFields,this,::GetMaxHandDownRecord (),false))
	{
		TRACEERROR("�޷������ݱ��л������:"+sSQL);
		return false;
	};
	return TRUE;
}
