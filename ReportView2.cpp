
#include "stdafx.h"
#include "QCDB.h"
#include "MemDC.h"

#include "ReportDoc.h"
#include "ReportView.h"
#include "DlgReportShowProperty.h"
#include "MyDate.h"
#include "fhcglobal.h"

////////////////////////////////////////////////////
// �� ̽ �� �� �� �� ר ҵ �� �� �� �� ��
// ��0303�����ල�ձ�  ��6
////////////////////////////////////////////////////
void CReportView::CreateReport06()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,k;
	CStringArray *pRecord=NULL;

	///////////////////////////////////////////
	// ����ÿ���ܼƺ���Ŀ�ܼ�
	///////////////////////////////////////////
	CString sData;
	CMyDate date;
	float fWeekSum[22],fProjectSum[22];
	CString sItem[22];
	for(i=0;i<22;i++)
	{
		fWeekSum[i]=0.0;
		fProjectSum[i]=0.0;
	}

	int iWeekRecordQty=0;
	float f=0;
	for(i=0;i<pDoc->GetRecordQty ();i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;

		for(j=4;j<=20;j++)
		{
			sItem[j]=pRecord->GetAt (j+1);
		}

		// ��ͳ�ƣ�
		date.Set (pRecord->GetAt (1),pRecord->GetAt (2),pRecord->GetAt (3));
		if(date>=CMyDate(pDoc->m_iStartYear,
							pDoc->m_iStartMonth,
							pDoc->m_iStartDay))
		{
			iWeekRecordQty++;

			for(k=4;k<=20;k++)
			{
				fWeekSum[k]+=stof(sItem[k]);
			}
		}

		// ��Ŀͳ�ƣ�
		for(k=4;k<=20;k++)
		{
			fProjectSum[k]+=stof(sItem[k]);
		}
	}

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	int iRowQty=iWeekRecordQty+5;

	m_rc.SetGridQty (iRowQty,22);
	m_rc.CombineGrid (0,1,0,0);
	m_rc.CombineGrid (0,1,1,1);
	m_rc.CombineGrid (0,1,2,2);
	m_rc.CombineGrid (0,1,3,3);

	m_rc.CombineGrid (0,0,4,5);
	m_rc.CombineGrid (0,0,6,7);
	m_rc.CombineGrid (0,0,8,9);
	m_rc.CombineGrid (0,0,10,11);
	m_rc.CombineGrid (0,1,12,12);
	m_rc.CombineGrid (0,1,13,13);
	m_rc.CombineGrid (0,0,14,15);
	m_rc.CombineGrid (0,0,16,19);

	m_rc.CombineGrid (0,1,20,20);
	m_rc.CombineGrid (0,1,21,21);
	
	m_rc.CombineGrid (iWeekRecordQty+2,iWeekRecordQty+2,0,3);
	m_rc.CombineGrid (iWeekRecordQty+3,iWeekRecordQty+3,0,3);
	m_rc.CombineGrid (iWeekRecordQty+4,iWeekRecordQty+4,0,21);


	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("�� ̽ �� �� �� �� ר ҵ �� �� �� �� ��");
	m_rc.SetTitle (s);

	m_rc.SetGridContent(0,0,"����");
	m_rc.SetGridContent(0,1,"������Ŀ");
	m_rc.SetGridContent(0,2,"ʩ��\r��λ");
	m_rc.SetGridContent(0,3,"����\r�ͺ�");
	m_rc.SetGridContent(0,4,"�ꡢ�¼���");
	m_rc.SetGridContent(1,4,"ʱ��");
	m_rc.SetGridContent(1,5,"����");

	m_rc.SetGridContent(0,6,"�ռ�");
	m_rc.SetGridContent(1,6,"���ڶ�");
	m_rc.SetGridContent(1,7,"����");
	m_rc.SetGridContent(0,8,"�ɼ�վ����");
	m_rc.SetGridContent(1,8,"ʱ��");
	m_rc.SetGridContent(1,9,"����");


	m_rc.SetGridContent(0,10,"�첨������");
	m_rc.SetGridContent(1,10,"�·�");
	m_rc.SetGridContent(1,11,"����");

	m_rc.SetGridContent(0,12,"ϵͳ\r����");

	m_rc.SetGridContent(0,13,"TB\r�ӳ�");
	m_rc.SetGridContent(0,14,"�����౨");
	m_rc.SetGridContent(1,14,"ʱ���");
	m_rc.SetGridContent(1,15,"����");
	m_rc.SetGridContent(0,16,"Ұ  ��  ��  ��");
	m_rc.SetGridContent(1,16,"����\r����");
	m_rc.SetGridContent(1,17,"����\r��");
	m_rc.SetGridContent(1,18,"����\r����");
	m_rc.SetGridContent(1,19,"�첨��\r�����");
	m_rc.SetGridContent(0,20,"��\r��\r¼");
	m_rc.SetGridContent(0,21,"��ע");

	m_rc.SetGridContent(iWeekRecordQty+2,0,"��   ��");
	m_rc.SetGridContent(iWeekRecordQty+3,0,"��   ��");


	CString sNote="";
	CString sJS="";
	CString sProjectName;

	CStringArray arrayProject;
	for(i=0;i<pDoc->GetRecordQty ();i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;
		date.Set(pRecord->GetAt (1),pRecord->GetAt (2),pRecord->GetAt (3));
		
		if(date<CMyDate(pDoc->m_iStartYear,
							pDoc->m_iStartMonth,
							pDoc->m_iStartDay))
		{
			continue;
		}

		pDoc->GetProjectInfoByNo(pRecord->GetAt (0),&arrayProject);

		m_rc.SetGridContent(2+i,0,date.GetDateString ());
		m_rc.SetGridContent(2+i,1,arrayProject.GetAt (1)); // ��Ŀ����
		m_rc.SetGridContent(2+i,2,arrayProject.GetAt (9)+"��"); // crew number
		

		for(j=3;j<=20;j++)
		{
			sItem[j]=pRecord->GetAt (j+1);
		}

		sNote=pRecord->GetAt (22);
		sNote.Trim ().MakeUpper ();

		for(j=23;j<=26;j++)
		{
			s=pRecord->GetAt (j);
			s.Trim ().MakeUpper ();
			if(s!=""&&s!="NULL")
			{
				sJS+=s;
			}
		}

		for(k=3;k<=20;k++)
		{
			m_rc.SetGridContent(2+i,k,sItem[k]);
		}

		m_rc.SetGridContent(2+i,21,sNote);
	}

	for(k=4;k<=20;k++)
	{
		if(k==4||k==6||k==8||k==14)continue;
		m_rc.SetGridContent(2+iWeekRecordQty,k,vtos(fWeekSum[k]));
		m_rc.SetGridContent(3+iWeekRecordQty,k,vtos(fProjectSum[k]));
	}

	m_rc.SetGridContent(4+iWeekRecordQty,0,"�����������(1����Ŀ�����������������2���ල�������ص��ǶԲ����������ճ���������2�������������ڵ����⼰����Ҫ��3�����ܲ����ල�����ص��):\r"+sJS, CW_GRIDWIDTH);
	m_rc.SetGridFormat(4+iWeekRecordQty,0,DT_LEFT);
	
	return;
}

/////////////////////////////////////
// ��̽���̿������ռල����
// ��0106�������ռ���  ��7
/////////////////////////////////////
void CReportView::CreateReport07()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j;
	CStringArray *pRecord=NULL;

	int iPrintPage=pDoc->m_iPrintPage ;

	if(iPrintPage==1)
	{
		CreateReport07_1();
	}
	else if(iPrintPage==2)
	{
		CreateReport07_2();
	}
	else if(iPrintPage==3)
	{
		CreateReport07_3();
	}
	else
	{
		CreateReport07_1();
	}
}
void CReportView::CreateReport07_2()
{
	int i,j;
	CStringArray *pRecord=NULL;
	CReportDoc *pDoc=GetDocument();

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	m_rc.SetGridQty (20,5);
	m_rc.CombineGrid (0,0,3,4);
	m_rc.CombineGrid (1,1,3,4);

	m_rc.CombineGrid (3,10,0,0);
	m_rc.CombineGrid (11,19,0,0);

	
	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("��̽���̿������ռල����");
	m_rc.SetTitle (s);

	m_rc.SetGridContent(0,0,"ʩ������");
	m_rc.SetGridContent(1,0,"������Ŀ");
	m_rc.SetGridContent(0,2,"ʩ����λ");
	m_rc.SetGridContent(1,2,"���ʱ��");
	m_rc.SetGridContent(2,0,"�����Ŀ");
	m_rc.SetGridContent(2,1,"��   ��   ��   ��");
	m_rc.SetGridContent(2,2,"ʩ�����Լ����");

	m_rc.SetGridContent(2,3,"�� �� �� �� �� ��");
	m_rc.SetGridContent(2,4,"�������");
	m_rc.SetGridContent(3,0,"��\r��\r��\r��\r��\r��");
	m_rc.SetGridContent(11,0,"��\r��\r��\r��\r��\r��\r��");

	
	m_rc.SetGridContent(3,1,"�����������");
	m_rc.SetGridContent(4 ,1,"���������ͺš�������ʹ������");
	m_rc.SetGridContent(5 ,1,"������������ϸ�֤��");
	m_rc.SetGridContent(6 ,1,"����Ӧ���������״��");
	m_rc.SetGridContent(7 ,1,"��̽����ͼ�͵���ͼ");
	m_rc.SetGridContent(8 ,1,"����̤������");
	m_rc.SetGridContent(9 ,1,"�������У�˺�չͼ�˶�");
	m_rc.SetGridContent(10,1,"GPS�ȷ������ܿ��Ƶ�ɹ�");
	m_rc.SetGridContent(11,1,"�ɼ���Ŀ��Ƽ��׷��������");
	m_rc.SetGridContent(12,1,"��̽�ɼ�������׼���淶");
	m_rc.SetGridContent(13,1,"�ɼ��������鷽��");
	m_rc.SetGridContent(14,1,"�����������������ռ�");
	m_rc.SetGridContent(15,1,"��������ͼ");
	m_rc.SetGridContent(16,1,"Ŀ�Ĳ㹹��ͼ");
	m_rc.SetGridContent(17,1,"��������ͼ");
	m_rc.SetGridContent(18,1,"�ز�ϵͳ��״ͼ������ͼ��˵����");
	m_rc.SetGridContent(19,1,"������Ա�Ե���Ŀ�����ʶ");

	m_rc.SetGridContent(0,1,pDoc->m_sBasin +"��� "+pDoc->m_sArea +"����");
	m_rc.SetGridContent(0,3,pDoc->m_sServer +pDoc->m_sCrew +"��");
	m_rc.SetGridContent(1,1,pDoc->m_sProjectName );

	CMyDate dateCheck;
	//
	int iRow=0;
	int iYear=0,iMonth=0,iDay=0;

	CStringArray arrayMonitor;
	for(i=0;i<pDoc->GetRecordQty ();i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;

		iRow=-1;
		for(j=30;j<=46;j++)
		{
			if(IsTrue(pRecord->GetAt(j)))
			{
				iRow=j-27;
				break;
			}
		}
		if(iRow==-1)
		{
			TRACEERROR("���󣺸ü�¼û��ָ��������ݡ��������:"+pRecord->GetAt(68)+"��"+pRecord->GetAt(69)+"��"+pRecord->GetAt(70)+"��");
			continue;
		}

		//
		m_rc.SetGridContent(iRow,2,pRecord->GetAt(66));
		m_rc.SetGridContent(iRow,3,pRecord->GetAt(67));
		m_rc.SetGridContent(iRow,4,pRecord->GetAt(68)+"��"+pRecord->GetAt(69)+"��"+pRecord->GetAt(70)+"��");

		iYear=stof(pRecord->GetAt(1));
		iMonth=stof(pRecord->GetAt(2));
		iDay=stof(pRecord->GetAt(3));

		if(iYear!=0&&iMonth!=0&&iDay!=0)
		{
			dateCheck.Set(iYear,iMonth,iDay);
		}
		AddMonitor(arrayMonitor,pRecord->GetAt(4));
	}

	m_rc.SetGridContent (1,3,dateCheck.GetDateString ());
	m_rc.SetLeftDownString ("��̽�ල:"+GetMonitorString(arrayMonitor));
	
	return;
}
void CReportView::CreateReport07_3()
{
	int i,j;
	CStringArray *pRecord=NULL;
	CReportDoc *pDoc=GetDocument();

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	m_rc.SetGridQty (22,5);
	m_rc.CombineGrid (0,0,3,4);
	m_rc.CombineGrid (1,1,3,4);

	m_rc.CombineGrid (3,6,0,0);
	m_rc.CombineGrid (7,21,0,0);


	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("��̽���̿������ռල����");
	m_rc.SetTitle (s);

	m_rc.SetGridContent(0,0,"ʩ������");
	m_rc.SetGridContent(1,0,"������Ŀ");
	m_rc.SetGridContent(0,2,"ʩ����λ");
	m_rc.SetGridContent(1,2,"���ʱ��");
	m_rc.SetGridContent(2,0,"�����Ŀ");
	m_rc.SetGridContent(2,1,"��   ��   ��   ��");
	m_rc.SetGridContent(2,2,"ʩ�����Լ����");

	m_rc.SetGridContent(2,3,"�� �� �� �� �� ��");
	m_rc.SetGridContent(2,4,"�������");
	m_rc.SetGridContent(3,0,"��\r��\r��\r��");
	m_rc.SetGridContent(7,0,"Q\rH\rS\rE\r��\r��");

	m_rc.SetGridContent(3 ,1,"��Ҫ���쵼�������Ǹɵ�λ���");
	m_rc.SetGridContent(4 ,1,"������ɿ���Դ�������豸��λ���");
	m_rc.SetGridContent(5 ,1,"��ŵ�����������豸��λ���");
	m_rc.SetGridContent(6 ,1,"�ֳ��������Ӳ������");
	m_rc.SetGridContent(7 ,1,"������������׼���ᡢѧϰ��ƺͼ�¼");
	m_rc.SetGridContent(8 ,1,"��λ������ѵ����λ�������");
	m_rc.SetGridContent(9 ,1,"����������֯�������ʩ");
	m_rc.SetGridContent(10,1,"������ƻ���Ŀ��");
	m_rc.SetGridContent(11,1,"HSE������֯�������ʩ");
	m_rc.SetGridContent(12,1,"HSE��ѵ�����");
	m_rc.SetGridContent(13,1,"85#��85#��Ʒ��š�����ʹ�ô�ʩ");
	m_rc.SetGridContent(14,1,"�����ص������ǼǼ��Բ�");
	m_rc.SetGridContent(15,1,"���ָ�λ����֤");
	m_rc.SetGridContent(16,1,"������Ա���֤��");
	m_rc.SetGridContent(17,1,"����ˮ���֤��");
	m_rc.SetGridContent(18,1,"Ӫ�����������ʩ");
	m_rc.SetGridContent(19,1,"��������");
	m_rc.SetGridContent(20,1,"�������ϵ����ü���־");
	m_rc.SetGridContent(21,1,"Ӫ�ء������������õ���ʩ����ȫ��ʶ");


	m_rc.SetGridContent(0,1,pDoc->m_sBasin +"��� "+pDoc->m_sArea +"����");
	m_rc.SetGridContent(0,3,pDoc->m_sServer +pDoc->m_sCrew +"��");
	m_rc.SetGridContent(1,1,pDoc->m_sProjectName );

	CMyDate dateCheck;
	//
	int iRow=0;
	int iYear=0,iMonth=0,iDay=0;

	CStringArray arrayMonitor;
	for(i=0;i<pDoc->GetRecordQty ();i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;

		iRow=-1;
		for(j=47;j<=65;j++)
		{
			if(IsTrue(pRecord->GetAt(j)))
			{
				iRow=j-44;
				break;
			}
		}
		if(iRow==-1)
		{
			TRACEERROR("���󣺸ü�¼û��ָ��������ݡ��������:"+pRecord->GetAt(68)+"��"+pRecord->GetAt(69)+"��"+pRecord->GetAt(70)+"��");
			continue;
		}

		//
		m_rc.SetGridContent(iRow,2,pRecord->GetAt(66));
		m_rc.SetGridContent(iRow,3,pRecord->GetAt(67));
		m_rc.SetGridContent(iRow,4,pRecord->GetAt(68)+"��"+pRecord->GetAt(69)+"��"+pRecord->GetAt(70)+"��");

		iYear=stof(pRecord->GetAt(1));
		iMonth=stof(pRecord->GetAt(2));
		iDay=stof(pRecord->GetAt(3));

		if(iYear!=0&&iMonth!=0&&iDay!=0)
		{
			dateCheck.Set(iYear,iMonth,iDay);
		}
		AddMonitor(arrayMonitor,pRecord->GetAt(4));
	}

	m_rc.SetGridContent (1,3,dateCheck.GetDateString ());
	m_rc.SetLeftDownString ("��̽�ල:"+GetMonitorString(arrayMonitor));
	
	return;

}

//////////////////////////////////////////
// ��̽���̿������ռල����, ��һ����
// ��0106�������ռ���  ��7
//////////////////////////////////////////
void CReportView::CreateReport07_1()
{
	int i,j;
	CStringArray *pRecord=NULL;
	CReportDoc *pDoc=GetDocument();

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	m_rc.SetGridQty (28,5);
	m_rc.CombineGrid (0,0,3,4);
	m_rc.CombineGrid (1,1,3,4);

	m_rc.CombineGrid (3,27,0,0);
	/*m_rc.CombineGrid (28,35,0,0);

	m_rc.CombineGrid (36,44,0,0);
	m_rc.CombineGrid (45,48,0,0);
	m_rc.CombineGrid (49,63,0,0);
	*/

	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("��̽���̿������ռල����");
	m_rc.SetTitle (s);

	m_rc.SetGridContent(0,0,"ʩ������");
	m_rc.SetGridContent(1,0,"������Ŀ");
	m_rc.SetGridContent(0,2,"ʩ����λ");
	m_rc.SetGridContent(1,2,"���ʱ��");
	m_rc.SetGridContent(2,0,"�����Ŀ");
	m_rc.SetGridContent(2,1,"��   ��   ��   ��");
	m_rc.SetGridContent(2,2,"ʩ�����Լ����");

	m_rc.SetGridContent(2,3,"�� �� �� �� �� ��");
	m_rc.SetGridContent(2,4,"�������");
	m_rc.SetGridContent(3,0,"��\r��\r��\r��\r��\r��\r��\r��\r��\r��\r��\r��\r��\r��\r��\r��");
	/*m_rc.SetGridContent(28,0,"��\r��\r��\r��\r��\r��");
	m_rc.SetGridContent(36,0,"��\r��\r��\r��\r��\r��\r��");
	m_rc.SetGridContent(45,0,"��\r��\r��\r��");
	m_rc.SetGridContent(49,0,"Q\rH\rS\rE\r��\r��");*/


	m_rc.SetGridContent(3,1,"���������ͺš�������ʹ������");
	m_rc.SetGridContent(4,1,"�ɼ�����ִ�б�׼");
	m_rc.SetGridContent(5,1,"�ɼ������ꡢ�¼켰�����¼");
	m_rc.SetGridContent(6,1,"�ɼ�վ�ͺš�������ʹ������");
	m_rc.SetGridContent(7,1,"��Դվ�ͺš�������ʹ������");
	m_rc.SetGridContent(8,1,"����վ�ͺš�������ʹ������");
	m_rc.SetGridContent(9,1,"�ɼ�վ��켰�����¼");
	m_rc.SetGridContent(10,1,"�ɿ���Դ�ͺż�����");
	m_rc.SetGridContent(11,1,"�ɿ���Դ��켰�����¼");
	m_rc.SetGridContent(12,1,"�����������ͺż�ʹ������");
	m_rc.SetGridContent(13,1,"������������켰�����¼");
	m_rc.SetGridContent(14,1,"���������г��Ⱥ͵���У׼��¼");
	m_rc.SetGridContent(15,1,"��ը���ͺš�����������˵��");
	m_rc.SetGridContent(16,1,"��ը��TB�ӳٲ��Լ�¼");
	m_rc.SetGridContent(17,1,"�첨���ͺš�������ʹ������");
	m_rc.SetGridContent(18,1,"�����ͺš�������ʹ������");
	m_rc.SetGridContent(19,1,"�������ͺš�������ʹ������");
	m_rc.SetGridContent(20,1,"�������׼");
	m_rc.SetGridContent(21,1,"ϵͳ���Բ������ϡ�����������");
	m_rc.SetGridContent(22,1,"ϵͳ�ӳٲ��Լ�¼�Ͱ౨");
	m_rc.SetGridContent(23,1,"�첨���������ͺš�������ʹ������");
	m_rc.SetGridContent(24,1,"�첨����������ȼ���֤��");
	m_rc.SetGridContent(25,1,"�첨�����Լ�¼��������");
	m_rc.SetGridContent(26,1,"������첨����鼰�������");
	m_rc.SetGridContent(27,1,"���ڼ첨����鼰�������");

	/*
	m_rc.SetGridContent(28,1,"�����������");
	m_rc.SetGridContent(29,1,"���������ͺš�������ʹ������");
	m_rc.SetGridContent(30,1,"������������ϸ�֤��");
	m_rc.SetGridContent(31,1,"����Ӧ���������״��");
	m_rc.SetGridContent(32,1,"��̽����ͼ�͵���ͼ");
	m_rc.SetGridContent(33,1,"����̤������");
	m_rc.SetGridContent(34,1,"�������У�˺�չͼ�˶�");
	m_rc.SetGridContent(35,1,"GPS�ȷ������ܿ��Ƶ�ɹ�");
	m_rc.SetGridContent(36,1,"�ɼ���Ŀ��Ƽ��׷��������");
	m_rc.SetGridContent(37,1,"��̽�ɼ�������׼���淶");
	m_rc.SetGridContent(38,1,"�ɼ��������鷽��");
	m_rc.SetGridContent(39,1,"�����������������ռ�");
	m_rc.SetGridContent(40,1,"��������ͼ");
	m_rc.SetGridContent(41,1,"Ŀ�Ĳ㹹��ͼ");
	m_rc.SetGridContent(42,1,"��������ͼ");
	m_rc.SetGridContent(43,1,"�ز�ϵͳ��״ͼ������ͼ��˵����");
	m_rc.SetGridContent(44,1,"������Ա�Ե���Ŀ�����ʶ");
	m_rc.SetGridContent(45,1,"��Ҫ���쵼�������Ǹɵ�λ���");
	m_rc.SetGridContent(46,1,"������ɿ���Դ�������豸��λ���");
	m_rc.SetGridContent(47,1,"��ŵ�����������豸��λ���");
	m_rc.SetGridContent(48,1,"�ֳ��������Ӳ������");
	m_rc.SetGridContent(49,1,"������������׼���ᡢѧϰ��ƺͼ�¼");
	m_rc.SetGridContent(50,1,"��λ������ѵ����λ�������");
	m_rc.SetGridContent(51,1,"����������֯�������ʩ");
	m_rc.SetGridContent(52,1,"������ƻ���Ŀ��");
	m_rc.SetGridContent(53,1,"HSE������֯�������ʩ");
	m_rc.SetGridContent(54,1,"HSE��ѵ�����");
	m_rc.SetGridContent(55,1,"85#��85#��Ʒ��š�����ʹ�ô�ʩ");
	m_rc.SetGridContent(56,1,"�����ص������ǼǼ��Բ�");
	m_rc.SetGridContent(57,1,"���ָ�λ����֤");
	m_rc.SetGridContent(58,1,"������Ա���֤��");
	m_rc.SetGridContent(59,1,"����ˮ���֤��");
	m_rc.SetGridContent(60,1,"Ӫ�����������ʩ");
	m_rc.SetGridContent(61,1,"��������");
	m_rc.SetGridContent(62,1,"�������ϵ����ü���־");
	m_rc.SetGridContent(63,1,"Ӫ�ء������������õ���ʩ����ȫ��ʶ");

*/

	m_rc.SetGridContent(0,1,pDoc->m_sBasin +"��� "+pDoc->m_sArea +"����");
	m_rc.SetGridContent(0,3,pDoc->m_sServer +pDoc->m_sCrew +"��");
	m_rc.SetGridContent(1,1,pDoc->m_sProjectName );

	CMyDate dateCheck;
	//
	int iRow=0;
	int iYear=0,iMonth=0,iDay=0;

	CStringArray arrayMonitor;
	for(i=0;i<pDoc->GetRecordQty ();i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;

		iRow=-1;
		for(j=5;j<=29;j++)
		{
			if(IsTrue(pRecord->GetAt(j)))
			{
				iRow=j-2;
				break;
			}
		}
		if(iRow==-1)
		{
			TRACEERROR("���󣺸ü�¼û��ָ��������ݡ��������:"+pRecord->GetAt(68)+"��"+pRecord->GetAt(69)+"��"+pRecord->GetAt(70)+"��");
			continue;
		}

		//
		m_rc.SetGridContent(iRow,2,pRecord->GetAt(66));
		m_rc.SetGridContent(iRow,3,pRecord->GetAt(67));
		m_rc.SetGridContent(iRow,4,pRecord->GetAt(68)+"��"+pRecord->GetAt(69)+"��"+pRecord->GetAt(70)+"��");

		iYear=stof(pRecord->GetAt(1));
		iMonth=stof(pRecord->GetAt(2));
		iDay=stof(pRecord->GetAt(3));

		if(iYear!=0&&iMonth!=0&&iDay!=0)
		{
			dateCheck.Set(iYear,iMonth,iDay);
		}
		AddMonitor(arrayMonitor,pRecord->GetAt(4));
	}

	m_rc.SetGridContent (1,3,dateCheck.GetDateString ());
	m_rc.SetLeftDownString ("��̽�ල:"+GetMonitorString(arrayMonitor));
	
	return;
}


////////////////////////////////////////////////
//  ��̽����ʩ������ල����
////////////////////////////////////////////////
void CReportView::CreateReport08()
{
//	 ������

	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j;
	CStringArray *pRecord=pDoc->GetRecord (0);
	CString sItem="";

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	m_rc.SetGridQty (7,2);
	for(i=0;i<6;i++)
	{
		m_rc.CombineGrid (i,i,0,1);
	}

	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("��̽����ʩ������ල����");
	m_rc.SetTitle (s);

	s="ʩ������:"+pDoc->m_sArea ;

	if(pDoc->m_bIs3D)
	{
		s+="��2D_��3D";
	}
	else
	{
		s+="��2D_��3D";
	}

	s+="   ʩ����λ:"+pDoc->m_sServer +pDoc->m_sCrew+"��";
	s+="   �������:";
	if(pRecord)
	{
		s+=pRecord->GetAt (1)+"��"+pRecord->GetAt (2)+"��"+pRecord->GetAt (3)+"��";
	}
	m_rc.SetGridContent (0,0,s);

	s="";
	if(pRecord)
	{
		if(IsTrue(pRecord->GetAt (4)))
		{
			s="������   ������   ������   ������   ������   ��������   ���ֳ�����   ��ԭʼ����";
		}
		else if(IsTrue(pRecord->GetAt (5)))
		{
			s="������   ������   ������   ������   ������   ��������   ���ֳ�����   ��ԭʼ����";
		}
		else if(IsTrue(pRecord->GetAt (6)))
		{
			s="������   ������   ������   ������   ������   ��������   ���ֳ�����   ��ԭʼ����";
		}
		else if(IsTrue(pRecord->GetAt (7)))
		{
			s="������   ������   ������   ������   ������   ��������   ���ֳ�����   ��ԭʼ����";
		}
		else if(IsTrue(pRecord->GetAt (8)))
		{
			s="������   ������   ������   ������   ������   ��������   ���ֳ�����   ��ԭʼ����";
		}
		else if(IsTrue(pRecord->GetAt (9)))
		{
			s="������   ������   ������   ������   ������   ��������   ���ֳ�����   ��ԭʼ����";
		}
		else if(IsTrue(pRecord->GetAt (10)))
		{
			s="������   ������   ������   ������   ������   ��������   ���ֳ�����   ��ԭʼ����";
		}
		else if(IsTrue(pRecord->GetAt (11)))
		{
			s="������   ������   ������   ������   ������   ��������   ���ֳ�����   ��ԭʼ����";
		}
		else
		{
			s="������   ������   ������   ������   ������   ��������   ���ֳ�����   ��ԭʼ����";
		}

	}
	else
	{
		s="������   ������   ������   ������   ������   ��������   ���ֳ�����   ��ԭʼ����";
	}

	m_rc.SetGridContent(1,0,s);

	s="��������������λ�á������������\r";
	if(pRecord)
	{
		s+=pRecord->GetAt (12)+"\r";
		s+=pRecord->GetAt (13)+"\r";
		s+=pRecord->GetAt (14);
	}

	m_rc.SetGridContent(2,0,s);

	s="������";
	sItem="";
	{
		sItem=pRecord->GetAt (15);
		sItem.Trim ();
	}
	if(sItem!="")
	{
		s+="��ͼ������(��ţ�"+sItem+")";
	}
	else
	{
		s+="��ͼ������(��ţ�  )";
	}

	sItem="";
	if(pRecord)
	{
		sItem=pRecord->GetAt (16);
		sItem.Trim ();
	}
	if(sItem!="")
	{
		s+="    ����������(��ţ�"+sItem+")";
	}
	else
	{
		s+="    ����������(��ţ�  )";
	}

	sItem="";
	if(pRecord)
	{
		sItem=pRecord->GetAt (17);
		sItem.Trim ();
	}
	if(sItem!="")
	{
		s+="    ������(��ţ�"+sItem+")";
	}
	else
	{
		s+="    ������(��ţ�    )";
	}

	m_rc.SetGridContent (3,0,s);

	s="����������������\r";
	sItem="";
	if(pRecord)
	{
		sItem=pRecord->GetAt (18);
		sItem.Trim ();
	}
	s+=sItem+"\r";
	sItem=pRecord->GetAt (19);
	sItem.Trim ();
	s+=sItem+"\r";

	m_rc.SetGridContent (4,0,s);

	s="����Ч����\r";
	sItem="";
	if(pRecord)
	{
		sItem=pRecord->GetAt (20);
		sItem.Trim ();
	}
	s+=sItem+"\r";
	
	CMyDate d;
	if(pRecord)
	{
		d.Set (pRecord->GetAt (21),pRecord->GetAt (22),pRecord->GetAt (23));
	}
	s+="�������ڣ�"+d.GetDateString ();
	m_rc.SetGridContent (5,0,s);

	
	s="��ͬ�����:";
	sItem="";
	if(pRecord)
	{
		sItem=pRecord->GetAt (24);
		sItem.Trim ();
	}
	s+=sItem;
	m_rc.SetGridContent (6,0,s);

	s="פ�Ӽල:";
	sItem="";
	if(pRecord)
	{
		sItem=pRecord->GetAt (25);
		sItem.Trim ();
	}
	s+=sItem;
	m_rc.SetGridContent (6,1,s);


	//////////////////////////////////
	// Left:
	for(i=0;i<7;i++)
	{
		m_rc.SetGridFormat (i,0,DT_LEFT);
	}
	m_rc.SetGridFormat (6,1,DT_LEFT);


	return ;
	

}
void CReportView::CreateReport09()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j;
	CMyDate date;
	CStringArray *pRecord=pDoc->GetRecord (0);
	if(!pRecord)return;


	CString sItem="";

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	m_rc.SetGridQty (8,7);
	m_rc.CombineGrid (0,0,0,1);
	m_rc.CombineGrid (1,1,0,1);
	m_rc.CombineGrid (2,2,0,6);


	for(i=3;i<=6;i++)
	{
		m_rc.CombineGrid (i,i,1,6);
	}
	m_rc.CombineGrid (7,7,0,1);
	m_rc.CombineGrid (7,7,2,3);
	m_rc.CombineGrid (7,7,5,6);


	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("��̽���̼ල��鱸��¼");
	m_rc.SetTitle (s);

	m_rc.SetGridContent (0,0,"ʩ������");
	m_rc.SetGridContent (0,2,pDoc->m_sArea);
	m_rc.SetGridContent (0,3,"ʩ����λ");
	m_rc.SetGridContent (0,4,pDoc->m_sServer+ pDoc->m_sCrew+"��");
	m_rc.SetGridContent (0,5,"����¼���");
	m_rc.SetGridContent (0,6,pRecord->GetAt (4));

	m_rc.SetGridContent (1,0,"�������");
	m_rc.SetGridContent (1,2,pDoc->GetLineName (pRecord->GetAt ( 5)));
	m_rc.SetGridContent (1,3,"�����");
	m_rc.SetGridContent (1,4,pRecord->GetAt( 6));
	m_rc.SetGridContent (1,5,"�������");

	date.Set(pRecord->GetAt (1),pRecord->GetAt (2),pRecord->GetAt (3));
	m_rc.SetGridContent (1,6,date.GetDateString ());
	
	s="����:"+pRecord->GetAt (7);
	m_rc.SetGridContent (2,0,s);

	m_rc.SetGridContent (3,0,"��\r��\r��\rĿ\r��\rλ\r��");
	m_rc.SetGridContent (3,1,pRecord->GetAt ( 8));

	m_rc.SetGridContent (4,0,"��\r��\r��\r��\r��\r��");
	m_rc.SetGridContent (4,1,pRecord->GetAt ( 9));

	m_rc.SetGridContent (5,0,"��\r��\r��\r��\r��\r��\r��");
	m_rc.SetGridContent (5,1,pRecord->GetAt ( 10));

	m_rc.SetGridContent (6,0,"��\r��\rЧ\r��");
	date.Set(pRecord->GetAt (15),pRecord->GetAt (16),pRecord->GetAt (17));
	s=pRecord->GetAt (11)+"\r                         ��֤���ڣ�"+date.GetDateString ();
	m_rc.SetGridContent (6,1,s);

	m_rc.SetGridContent (7,0,"ʩ����λ\r�쵼ǩ��");
	date.Set(pRecord->GetAt (19),pRecord->GetAt (20),pRecord->GetAt (21));
	m_rc.SetGridContent (7,2,"  \r  \r  "+date.GetDateString ());

	date.Set(pRecord->GetAt (23),pRecord->GetAt (24),pRecord->GetAt (25));
	m_rc.SetGridContent (7,4,"פ�Ӽල\rǩ   ��");
	m_rc.SetGridContent (7,5,"  \r  \r  "+date.GetDateString ());

	//////////////////////////////////
	// Left:
	for(i=3;i<=6;i++)
	{
		m_rc.SetGridFormat (i,1,DT_LEFT);
	}
	m_rc.SetGridFormat (2,0,DT_LEFT);

	return ;
}


/////////////////////////////////////////////
//   ��̽���̼ල��������ͳ�Ʒ�����
/////////////////////////////////////////////
void CReportView::CreateReport10()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j;
	CMyDate date;
	CStringArray *pRecord=NULL;
	int iRecordQty=pDoc->GetRecordQty ();

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	m_rc.SetGridQty (iRecordQty+2,21);


	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("��̽���̼ල��������ͳ�Ʒ�����");
	m_rc.SetTitle (s);

	m_rc.SetGridContent (0,0,"��\r��");
	m_rc.SetGridContent (0,1,"���\r����\r����");
	m_rc.SetGridContent (0,2,"�ϸ�\r����\r����");
	m_rc.SetGridContent (0,3,"����\r�ϸ�\r��");
	m_rc.SetGridContent (0,4,"���\r����\r����");
	m_rc.SetGridContent (0,5,"�ϸ�\r����\r����");
	m_rc.SetGridContent (0,6,"����\r�ϸ�\r��");
	m_rc.SetGridContent (0,7,"���\r��¼\r����");
	m_rc.SetGridContent (0,8,"һ��\rƷ��");
	m_rc.SetGridContent (0,9,"һ��\rƷ��");
	m_rc.SetGridContent (0,10,"����\rƷ��");
	m_rc.SetGridContent (0,11,"����\rƷ��");
	m_rc.SetGridContent (0,12,"��Ʒ\r��");
	m_rc.SetGridContent (0,13,"��Ʒ\r��");
	m_rc.SetGridContent (0,14,"���\rС��\r����");
	m_rc.SetGridContent (0,15,"�ϸ�\rС��\r����");
	m_rc.SetGridContent (0,16,"���\r΢��\r����");
	m_rc.SetGridContent (0,17,"�ϸ�\r΢��\r����");
	m_rc.SetGridContent (0,18,"���\r����\r����");
	m_rc.SetGridContent (0,19,"�ϸ�\r����\r����");
	m_rc.SetGridContent (0,20,"��ע");
	m_rc.SetGridContent (iRecordQty+1,0,"��");


	//////////////////////////////////
	// Left:
	CString sItem[21];

	int iMonthSum[21];
	for(i=0;i<21;i++)
	{
		iMonthSum[i]=0;
	}

	CString sMonitor="";
	float fValue=0.0;
	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;
		date.Set(pRecord->GetAt (1),pRecord->GetAt (2),pRecord->GetAt (3));

		sItem[0]=pRecord->GetAt (2)+"��"+pRecord->GetAt (3)+"��";
		sItem[1]=pRecord->GetAt (4);
		sItem[2]=pRecord->GetAt (5);
		
		sItem[3]=GetRatioString(sItem[2],sItem[1]);

		sItem[4]=pRecord->GetAt (6);
		sItem[5]=pRecord->GetAt (7);
		sItem[6]=GetRatioString(sItem[5],sItem[4]);
		sItem[7]=pRecord->GetAt (8);
		sItem[8]=pRecord->GetAt (9);
		sItem[9]=GetRatioString(sItem[8],sItem[7]);
		sItem[10]=pRecord->GetAt (10);
		sItem[11]=GetRatioString(sItem[10],sItem[7]);
		sItem[12]=pRecord->GetAt (11);
		sItem[13]=GetRatioString(sItem[12],sItem[7]);
		sItem[14]=pRecord->GetAt (12);
		sItem[15]=pRecord->GetAt (13);
		sItem[16]=pRecord->GetAt (14);
		sItem[17]=pRecord->GetAt (15);
		sItem[18]=pRecord->GetAt (16);
		sItem[19]=pRecord->GetAt (17);
		sItem[20]=pRecord->GetAt (18);

		for(j=0;j<21;j++)
		{
            m_rc.SetGridContent (i+1,j,sItem[j]);
			iMonthSum[j]+=stof(sItem[j]);
		}

		s=pRecord->GetAt (19);
		if(!IsEmpty(s))
		{
			sMonitor=s;
		}
	}

	for(j=1;j<=19;j++)
	{
        m_rc.SetGridContent (iRecordQty+1,j,vtos(iMonthSum[j]));
	}

	m_rc.SetGridContent (iRecordQty+1,3,GetRatioString(iMonthSum[2],iMonthSum[1]));
	m_rc.SetGridContent (iRecordQty+1,6,GetRatioString(iMonthSum[5],iMonthSum[4]));
	m_rc.SetGridContent (iRecordQty+1,9,GetRatioString(iMonthSum[8],iMonthSum[7]));
	m_rc.SetGridContent (iRecordQty+1,11,GetRatioString(iMonthSum[10],iMonthSum[7]));
	m_rc.SetGridContent (iRecordQty+1,13,GetRatioString(iMonthSum[12],iMonthSum[7]));


	s="��̽�ֳ��ල��"+sMonitor+ "      ������Ŀ��"+pDoc->m_sProjectName +"   ʱ�䣺"+date.GetDateString ();
	m_rc.SetLeftUpString (s);
	return ;
	


}

