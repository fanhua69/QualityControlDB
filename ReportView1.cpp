
#include "stdafx.h"
#include "QCDB.h"
#include "MemDC.h"

#include "ReportDoc.h"
#include "ReportView.h"
#include "DlgReportShowProperty.h"
#include "MyDate.h"
#include "fhcglobal.h"


//  ��̽������Ŀ��ƹ�����ͳ�Ʊ�
void CReportView::CreateReport01()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();

	int iRecordQty=pDoc->GetRecordQty ();
	m_rc.SetGridQty (iRecordQty+3,18);
	m_rc.CombineGrid (0,1,0,0);
	m_rc.CombineGrid (0,1,1,1);
	m_rc.CombineGrid (0,0,2,5);
	m_rc.CombineGrid (0,0,6,15);
	m_rc.CombineGrid (0,1,16,16);
	m_rc.CombineGrid (0,1,17,17);

	m_rc.CombineGrid (iRecordQty+2,iRecordQty+2,6,13);

	CString s;
	s.Format ("���Ϳ�̽����˾%s���%s̽��%s��̽������Ŀ��ƹ�����ͳ�Ʊ�",
					(LPCTSTR)pDoc->m_sYear ,
					(LPCTSTR)pDoc->m_sProspectArea ,
					(LPCTSTR)pDoc->m_sArea );
	m_rc.SetTitle (s);

	CMyDate date(pDoc->m_iStatYear, 
				pDoc->m_iStatMonth, 
				pDoc->m_iStatDay); 


	s.Format ("ͳ�����ڣ�%s",date.GetDateString ());

	m_rc.SetLeftUpString (s);

	s.Format("ʩ����λ�� %s ��˾ %s ��",pDoc->m_sServer ,pDoc->m_sCrew );
	m_rc.SetRightUpString (s);


	m_rc.SetGridContent (0,0,"���");
	m_rc.SetGridContent (0,1,"���ߺ�\r(������)");
	m_rc.SetGridContent (0,2,"��ά��Ŀ");
	m_rc.SetGridContent (1,2,"�ڵ���\rʼ׮��");
	m_rc.SetGridContent (1,3,"�ڵ���\rֹ׮��");
	m_rc.SetGridContent (1,4,"������\r����Km");
	m_rc.SetGridContent (1,5,"������\r�����");
	m_rc.SetGridContent (0,11,"��ά��Ŀ");
	m_rc.SetGridContent (1,6,"������\rֹ�ߺ�");
	m_rc.SetGridContent (1,7,"����\r���");
	m_rc.SetGridContent (1,8,"�ڵ���\rֹ�ߺ�");
	m_rc.SetGridContent (1,9,"�ڵ�\r���");
	m_rc.SetGridContent (1,10,"������\r��ֹ�ߺ�");
	m_rc.SetGridContent (1,11,"������\r���");
	m_rc.SetGridContent (1,12,"���յ�\r��ֹ���");
	m_rc.SetGridContent (1,13,"���յ�\r���");
	m_rc.SetGridContent (1,14,"������\r����Km");
	m_rc.SetGridContent (1,15,"������\r�����");
	m_rc.SetGridContent (0,16,"С��\r���\r��");
	m_rc.SetGridContent (0,17,"΢��\r����\r��");

	CStringArray *pRecord=NULL;
	float fFullCoverArea=0.0;
	for(int i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)
		{
			ASSERT(false);
			break;
		}
		m_rc.SetGridContent (i+2,0,vtos(i));
		m_rc.SetGridContent (i+2,1,pRecord->GetAt (0));
		m_rc.SetGridContent (i+2,2,pRecord->GetAt (1));
		m_rc.SetGridContent (i+2,3,pRecord->GetAt (2));
		m_rc.SetGridContent (i+2,4,pRecord->GetAt (3));
		m_rc.SetGridContent (i+2,5,pRecord->GetAt (4));

		m_rc.SetGridContent (i+2,6,pRecord->GetAt (5)+"-\r-"+pRecord->GetAt (6));
		m_rc.SetGridContent (i+2,7,pRecord->GetAt (7));
		m_rc.SetGridContent (i+2,8,pRecord->GetAt (8)+"-\r-"+pRecord->GetAt (9));
		m_rc.SetGridContent (i+2,9,pRecord->GetAt (10));

		m_rc.SetGridContent (i+2,10,pRecord->GetAt (11)+"-\r-"+pRecord->GetAt (12));
		m_rc.SetGridContent (i+2,11,pRecord->GetAt (13));
		m_rc.SetGridContent (i+2,12,pRecord->GetAt (14)+"-\r-"+pRecord->GetAt (15));
		m_rc.SetGridContent (i+2,13,pRecord->GetAt (16));

		m_rc.SetGridContent (i+2,14,pRecord->GetAt (17));
		m_rc.SetGridContent (i+2,15,pRecord->GetAt (18));

		m_rc.SetGridContent (i+2,16,pRecord->GetAt (19));
		m_rc.SetGridContent (i+2,17,pRecord->GetAt (20));

	}

	m_rc.SetGridContent (iRecordQty+2,0,"��\r��");
	m_rc.SetGridContent (iRecordQty+2,1,vtos(iRecordQty)+"����");
	
	CString sContent;
	sContent.Format ("���������:%sKm\0012  һ�θ������:%sKm\0012   ʩ�����:%sKm\0012",
			pDoc->m_s3DDesiFullCover ,pDoc->m_s3DDesignSingleCover ,pDoc->m_s3DDesiWorkAreaQty );
	m_rc.SetGridContent (iRecordQty+2,6,sContent);

	if(pRecord)
	{
		s.Format ("פ�Ӽල��%s",pRecord->GetAt (21));
	}
	m_rc.SetLeftDownString (s);
}

//�������ָ�ꡢĿ�Ĳ�ָ�ꡢ��Ҫ���Ų�ָ��ͳ�Ʊ�
void CReportView::CreateReport02()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();

	int iRowQty=11;

	int iRecordQty1=pDoc->GetRecordQty ();
	int iRecordQty2=pDoc->m_docVice.GetRecordQty ();
	int n=iRecordQty1+iRecordQty2+4;
	if(n>iRowQty)
	{
		iRowQty=n;
	}

	m_rc.SetGridQty (iRowQty,15);
	m_rc.CombineGrid (0,1,0,0);
	m_rc.CombineGrid (0,0,1,4);
	m_rc.CombineGrid (0,1,5,5);
	m_rc.CombineGrid (0,0,6,13);
	m_rc.CombineGrid (0,1,14,14);


	m_rc.CombineGrid (iRecordQty1+2,iRecordQty1+3,5,5);
	m_rc.CombineGrid (iRecordQty1+2,iRecordQty1+2,6,13);
	m_rc.CombineGrid (iRecordQty1+2,iRecordQty1+3,14,14);

	for(int i=iRecordQty1+3;i<iRowQty;i++)
	{
		m_rc.CombineGrid (i,i,12,13);
	}

	CString s;
	s.Format ("���Ϳ�̽����˾%s���%s̽��%s��̽������Ŀ",
					(LPCTSTR)pDoc->m_sYear ,
					(LPCTSTR)pDoc->m_sProspectArea ,
					(LPCTSTR)pDoc->m_sArea );
	m_rc.SetTitle (s);
	m_rc.SetViceTitle("�������ָ�ꡢĿ�Ĳ�ָ�ꡢ��Ҫ���Ų�ָ��ͳ�Ʊ�");

	CMyDate date(	pDoc->m_iStatYear ,
					pDoc->m_iStatMonth ,
					pDoc->m_iStartDay );

	s.Format ("ͳ�����ڣ�%s",date.GetDateString ());

	m_rc.SetLeftUpString (s);

	s.Format("ʩ����λ�� %s ��˾ %s ��",pDoc->m_sServer ,pDoc->m_sCrew );
	m_rc.SetRightUpString (s);


	m_rc.SetGridContent (0,0,"��\r��");
	m_rc.SetGridContent (0,1,"��   ��   ָ   ��   ��   Ҫ   ��");
	m_rc.SetGridContent (1,1,"��      Ŀ");
	m_rc.SetGridContent (1,2,"����");
	m_rc.SetGridContent (1,3,"ָ��");
	m_rc.SetGridContent (1,4,"Ҫ��");

	m_rc.SetGridContent (2,0,"1");
	m_rc.SetGridContent (2,1,"ȫ��һ��Ʒ��");
	m_rc.SetGridContent (2,2,"��");
	m_rc.SetGridContent (2,3,pDoc->m_arrayProject1 .GetAt (0));
	m_rc.SetGridContent (2,4,pDoc->m_arrayProject1 .GetAt (1));

	m_rc.SetGridContent (3,0,"2");
	m_rc.SetGridContent (3,1,"ȫ���ϸ���");
	m_rc.SetGridContent (3,2,"��");
	m_rc.SetGridContent (3,3,pDoc->m_arrayProject1 .GetAt (2));
	m_rc.SetGridContent (3,4,pDoc->m_arrayProject1 .GetAt (3));

	m_rc.SetGridContent (4,0,"3");
	m_rc.SetGridContent (4,1,"ȫ����Ʒ��");
	m_rc.SetGridContent (4,2,"��");
	m_rc.SetGridContent (4,3,pDoc->m_arrayProject1 .GetAt (4));
	m_rc.SetGridContent (4,4,pDoc->m_arrayProject1 .GetAt (5));

	m_rc.SetGridContent (5,0,"4");
	m_rc.SetGridContent (5,1,"ȫ��������");
	m_rc.SetGridContent (5,2,"��");
	m_rc.SetGridContent (5,3,pDoc->m_arrayProject1 .GetAt (6));
	m_rc.SetGridContent (5,4,pDoc->m_arrayProject1 .GetAt (7));

	m_rc.SetGridContent (6,0,"5");
	m_rc.SetGridContent (6,1,"�����߿�����");
	m_rc.SetGridContent (6,2,"��");
	m_rc.SetGridContent (6,3,pDoc->m_arrayProject1 .GetAt (8));
	m_rc.SetGridContent (6,4,pDoc->m_arrayProject1 .GetAt (9));

	m_rc.SetGridContent (7,0,"6");
	m_rc.SetGridContent (7,1,"�����߷�Ʒ��");
	m_rc.SetGridContent (7,2,"��");
	m_rc.SetGridContent (7,3,pDoc->m_arrayProject1 .GetAt (10));
	m_rc.SetGridContent (7,4,pDoc->m_arrayProject1 .GetAt (11));


	m_rc.SetGridContent (8,0,"7");
	m_rc.SetGridContent (8,1,"ȫ���������Ϻϸ���");
	m_rc.SetGridContent (8,2,"��");
	m_rc.SetGridContent (8,3,pDoc->m_arrayProject1 .GetAt (12));
	m_rc.SetGridContent (8,4,pDoc->m_arrayProject1 .GetAt (13));

	m_rc.SetGridContent (9,0,"8");
	m_rc.SetGridContent (9,1,"ȫ�����������Ϻϸ���");
	m_rc.SetGridContent (9,2,"��");
	m_rc.SetGridContent (9,3,pDoc->m_arrayProject1 .GetAt (14));
	m_rc.SetGridContent (9,4,pDoc->m_arrayProject1 .GetAt (15));

	m_rc.SetGridContent (10,0,"9");
	m_rc.SetGridContent (10,1,"ȫ���ֳ�������");
	m_rc.SetGridContent (10,2,"��");
	m_rc.SetGridContent (10,3,pDoc->m_arrayProject1 .GetAt (16));
	m_rc.SetGridContent (10,4,pDoc->m_arrayProject1 .GetAt (17));
	
	//////////////////////////////////////
	//Ŀ�Ĳ�ָ��
	///////////////////////////////////////
	m_rc.SetGridContent (0,5,"��\r��");
	m_rc.SetGridContent (0,6,"��  Ҫ  Ŀ  ��  ��  ָ  ��  ��  Ҫ  ��");
	m_rc.SetGridContent (1,6,"Ŀ�Ĳ�");
	m_rc.SetGridContent (1,7,"����");
	m_rc.SetGridContent (1,8,"T0ʱ��");
	m_rc.SetGridContent (1,9,"��Ƶ");
	m_rc.SetGridContent (1,10,"�ֱ���");
	m_rc.SetGridContent (1,11,"�����");
	m_rc.SetGridContent (1,12,"����");
	m_rc.SetGridContent (1,13,"Ҫ��");
	m_rc.SetGridContent (1,14,"��ע");

	CStringArray *pRecord=NULL;
	for(int i=0;i<iRecordQty1;i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)
		{
			ASSERT(false);
			break;
		}
		m_rc.SetGridContent (i+2,5,vtos(i+1));
		m_rc.SetGridContent (i+2,6,pRecord->GetAt (0));
		m_rc.SetGridContent (i+2,7,pRecord->GetAt (1));
		m_rc.SetGridContent (i+2,8,pRecord->GetAt (2));
		m_rc.SetGridContent (i+2,9,pRecord->GetAt (3)+"\r-"+pRecord->GetAt (4));
		m_rc.SetGridContent (i+2,10,pRecord->GetAt (5)+"\r-"+pRecord->GetAt (6));
		m_rc.SetGridContent (i+2,11,pRecord->GetAt (7)+"\r-"+pRecord->GetAt (8));
		m_rc.SetGridContent (i+2,12,pRecord->GetAt (9)+"\r-"+pRecord->GetAt (10));
		m_rc.SetGridContent (i+2,13,pRecord->GetAt (11));
		m_rc.SetGridContent (i+2,14,pRecord->GetAt (12));

	}

	//////////////////////////////////////
	//   ��Ҫ���Ų�ָ��ͳ�Ʊ�
	///////////////////////////////////////
	m_rc.SetGridContent (iRecordQty1+2,5,"��\r��");
	m_rc.SetGridContent (iRecordQty1+2,6,"��  Ҫ  ��  ��  ��  ָ  ��  ��  Ҫ  ��");
	m_rc.SetGridContent (iRecordQty1+3,6,"���Ų�");
	m_rc.SetGridContent (iRecordQty1+3,7,"����");
	m_rc.SetGridContent (iRecordQty1+3,8,"��Ƶ��");
	m_rc.SetGridContent (iRecordQty1+3,9,"���ٶ�");
	m_rc.SetGridContent (iRecordQty1+3,10,"�Ӳ���");
	m_rc.SetGridContent (iRecordQty1+3,11,"ǿ��");
	m_rc.SetGridContent (iRecordQty1+3,12,"Ҫ��");
	m_rc.SetGridContent (iRecordQty1+3,14,"��ע");

	CDataBrowseDoc *pDBDoc=&pDoc->m_docVice ;
	for(i=0;i<iRecordQty2;i++)
	{
		pRecord=pDBDoc->GetRecord (i);
		if(!pRecord)
		{
			ASSERT(false);
			break;
		}
		m_rc.SetGridContent (iRecordQty1+4+i,5,vtos(i+1));
		m_rc.SetGridContent (iRecordQty1+4+i,6,pRecord->GetAt (0));
		m_rc.SetGridContent (iRecordQty1+4+i,7,pRecord->GetAt (1));
		m_rc.SetGridContent (iRecordQty1+4+i,8,pRecord->GetAt (2)+"\r"+pRecord->GetAt (3));
		m_rc.SetGridContent (iRecordQty1+4+i,9,pRecord->GetAt (4)+"\r"+pRecord->GetAt (5));
		m_rc.SetGridContent (iRecordQty1+4+i,10,pRecord->GetAt (6)+"\r"+pRecord->GetAt (7));
		m_rc.SetGridContent (iRecordQty1+4+i,11,pRecord->GetAt (8)+"\r"+pRecord->GetAt (9));
		m_rc.SetGridContent (iRecordQty1+4+i,12,pRecord->GetAt (10));
		m_rc.SetGridContent (iRecordQty1+4+i,14,pRecord->GetAt (11)+"12345����1234��123456789012345678901234567890����",CW_COMMONWIDTH);
	}
}


//��̽������Ŀ�������ܱ���
void CReportView::CreateReport03()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,k;
	CStringArray *pRecord=NULL;

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
	int iShotNum=0;
	for(i=0;i<pDoc->GetRecordQty ();i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;
		date.Set(pRecord->GetAt (1),pRecord->GetAt (2),pRecord->GetAt (3));

		iShotNum=0;
		for(j=28;j<=47;j++)
		{
			iShotNum+=stof(pRecord->GetAt (j));
		}

		sItem[2]=vtos(iShotNum);
		sItem[3]=pRecord->GetAt (5);
		sItem[4]=pRecord->GetAt (6);
		sItem[5]=pRecord->GetAt (7);
		sItem[6]=pRecord->GetAt (8);
		sItem[7]=pRecord->GetAt (9);
		sItem[8]=pRecord->GetAt (10);
		sItem[9]=pRecord->GetAt (11);
		sItem[10]=pRecord->GetAt (12);
		sItem[11]=pRecord->GetAt (13);
		sItem[12]=pRecord->GetAt (14);
		sItem[13]=pRecord->GetAt (15);
		sItem[14]=pRecord->GetAt (16);
		sItem[15]=pRecord->GetAt (17);
		sItem[16]=pRecord->GetAt (18);
		sItem[17]=pRecord->GetAt (19);
		sItem[18]=pRecord->GetAt (20);
		sItem[19]=pRecord->GetAt (21);
		sItem[20]=pRecord->GetAt (22);
		sItem[21]=pRecord->GetAt (23);

		date.Set (pRecord->GetAt (1),pRecord->GetAt (2),pRecord->GetAt (3));
		if(date>=CMyDate(pDoc->m_iStartYear,
							pDoc->m_iStartMonth,
							pDoc->m_iStartDay))
		{
			iWeekRecordQty++;

			for(k=2;k<=21;k++)
			{
				fWeekSum[k]+=stof(sItem[k]);
			}
		}

		for(k=2;k<=21;k++)
		{
			fProjectSum[k]+=stof(sItem[k]);
		}
	}

	/////////////////////////////////////////////////
	//
	/////////////////////////////////////////////////
	int iRowQty=iWeekRecordQty+6;

	m_rc.SetGridQty (iRowQty,22);
	m_rc.CombineGrid (0,1,0,0);
	m_rc.CombineGrid (0,1,1,1);
	m_rc.CombineGrid (0,0,2,5);
	m_rc.CombineGrid (0,0,6,9);
	
	m_rc.CombineGrid (iWeekRecordQty+3,iWeekRecordQty+3,0,1);
	m_rc.CombineGrid (iWeekRecordQty+2,iWeekRecordQty+2,0,1);
	m_rc.CombineGrid (iWeekRecordQty+4,iWeekRecordQty+5,0,21);

	for(i=10;i<=21;i++)
	{
		m_rc.CombineGrid (0,1,i,i);
	}

	CString s;
	s.Format ("���Ϳ�̽����˾%s���%s̽��%s��̽������Ŀ�������ܱ���",
					(LPCTSTR)pDoc->m_sYear ,
					(LPCTSTR)pDoc->m_sProspectArea ,
					(LPCTSTR)pDoc->m_sArea );
	m_rc.SetTitle (s);
	
	CString sMonitor="";
	pRecord=pDoc->GetRecord (0);
	if(pRecord)
	{
		sMonitor=pRecord->GetAt (27);
	}

	s.Format ("פ�Ӽල:%s          ̽��:%s           ʩ����λ:%s",
		sMonitor,
		pDoc->m_sProspectArea ,
		pDoc->m_sCrew );

	if(pDoc->m_bIs3D )
	{
		s+="        3D";
	}
	else
	{
		s+="        2D";
	}

	CString s2;
	CString sKilometer=pDoc->m_s3DDesiFullCover ;
	CString sShotQty=pDoc->m_s3DDesiShotQty ;
	if(!pDoc->m_bIs3D )
	{
		sKilometer=pDoc->m_s2DDesiFullCover;
		sShotQty=pDoc->m_s2DDesiShotQty ;
	}
	s2.Format ("��Ʋ���: %s ��(��)    ����: %s  ����:%s",
			pDoc->m_sDesiLineQty     ,
			sShotQty,
			sKilometer);

	s+=s2;

	m_rc.SetLeftUpString (s);

	m_rc.SetGridContent(0,0,"����");
	m_rc.SetGridContent(0,1,"����");
	m_rc.SetGridContent(0,2,"��  ��  ��  ʵ  ��  ��  ��");
	m_rc.SetGridContent(1,2,"����");
	m_rc.SetGridContent(1,3,"����");
	m_rc.SetGridContent(1,4,"С����");
	m_rc.SetGridContent(1,5,"΢�⾮");

	m_rc.SetGridContent(0,6,"�� �� �� �� ͳ ��");
	m_rc.SetGridContent(1,6,"һ��");
	m_rc.SetGridContent(1,7,"����");
	m_rc.SetGridContent(1,8,"�յ�");
	m_rc.SetGridContent(1,9,"��Ʒ");

	m_rc.SetGridContent(0,10,"���\r����");
	m_rc.SetGridContent(0,11,"����\r�ϸ�");
	m_rc.SetGridContent(0,12,"���\r����");
	m_rc.SetGridContent(0,13,"����\r�ϸ�");
	m_rc.SetGridContent(0,14,"����\r�ϸ�");
	m_rc.SetGridContent(0,15,"�¼�");
	m_rc.SetGridContent(0,16,"�ռ�");
	m_rc.SetGridContent(0,17,"���\r����\r��־");
	m_rc.SetGridContent(0,18,"�ϸ�\r����\r��־");
	m_rc.SetGridContent(0,19,"�ֳ�\r���");
	m_rc.SetGridContent(0,20,"����¼");
	m_rc.SetGridContent(0,21,"ͼ���\r����\r���");

	m_rc.SetGridContent(iWeekRecordQty+2,0,"�ϼ�");
	m_rc.SetGridContent(iWeekRecordQty+3,0,"�ۼ�");


	CString sNote="";

	


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


		m_rc.SetGridContent(2+i,0,date.GetDateString ());
		m_rc.SetGridContent(2+i,1,pDoc->GetLineName (pRecord->GetAt (0)));
		
		iShotNum=0;
		for(j=28;j<=37;j++)
		{
			iShotNum+=stof(pRecord->GetAt (j));
		}

		sItem[2]=vtos(iShotNum);
		sItem[3]=pRecord->GetAt (5);
		sItem[4]=pRecord->GetAt (6);
		sItem[5]=pRecord->GetAt (7);
		sItem[6]=pRecord->GetAt (8);
		sItem[7]=pRecord->GetAt (9);
		sItem[8]=pRecord->GetAt (10);
		sItem[9]=pRecord->GetAt (11);
		sItem[10]=pRecord->GetAt (12);
		sItem[11]=pRecord->GetAt (13);
		sItem[12]=pRecord->GetAt (14);
		sItem[13]=pRecord->GetAt (15);
		sItem[14]=pRecord->GetAt (16);
		sItem[15]=pRecord->GetAt (17);
		sItem[16]=pRecord->GetAt (18);
		sItem[17]=pRecord->GetAt (19);
		sItem[18]=pRecord->GetAt (20);
		sItem[19]=pRecord->GetAt (21);
		sItem[20]=pRecord->GetAt (22);
		sItem[21]=pRecord->GetAt (23);

		sNote+=pRecord->GetAt (24);
		sNote+=pRecord->GetAt (25);
		sNote+=pRecord->GetAt (26);

		for(k=2;k<=21;k++)
		{
			m_rc.SetGridContent(2+i,k,sItem[k]);
		}
	}

	for(k=2;k<=19;k++)
	{
		m_rc.SetGridContent(2+iWeekRecordQty,k,vtos(fWeekSum[k]));
		m_rc.SetGridContent(3+iWeekRecordQty,k,vtos(fProjectSum[k]));
	}

	m_rc.SetGridContent(4+iWeekRecordQty,0,"�����������(1��������Ŀ���������2���ල���������3���²��ල�����ص��):\r"+sNote, CW_GRIDWIDTH);
	m_rc.SetGridFormat(4+iWeekRecordQty,0,DT_LEFT);
	
	return;
}



//��̽������Ŀ�������±���
void CReportView::CreateReport04()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j;
	CStringArray *pRecord=NULL;

	CString sData;
	CMyDate date;
	
	/////////////////////////////////////////////////
	//
	/////////////////////////////////////////////////
	int iRecordQty=pDoc->GetRecordQty ()-2;  // The 2 records left is month total and project total;
	if(iRecordQty<0)
	{
		iRecordQty=0;
	}
	int iRowQty=iRecordQty+5;

	m_rc.SetGridQty (iRowQty,22);
	m_rc.CombineGrid (0,1,0,0);
	m_rc.CombineGrid (0,1,1,1);
	m_rc.CombineGrid (0,0,2,5);
	m_rc.CombineGrid (0,0,6,9);
	
	m_rc.CombineGrid (iRecordQty+3,iRecordQty+3,0,1);
	m_rc.CombineGrid (iRecordQty+2,iRecordQty+2,0,1);
	m_rc.CombineGrid (iRecordQty+4,iRecordQty+5,0,21);

	for(i=10;i<=21;i++)
	{
		m_rc.CombineGrid (0,1,i,i);
	}

	CString s;
	s.Format ("���Ϳ�̽����˾%s���%s̽��%s��̽������Ŀ�������±���",
					(LPCTSTR)pDoc->m_sYear ,
					(LPCTSTR)pDoc->m_sProspectArea ,
					(LPCTSTR)pDoc->m_sArea );
	m_rc.SetTitle (s);
	
	CString sMonitor="";
	pRecord=pDoc->GetRecord (0);
	if(pRecord)
	{
		sMonitor=pRecord->GetAt (32);
	}

	s.Format ("פ�Ӽල:%s          ̽��:%s           ʩ����λ:%s",
		sMonitor,
		pDoc->m_sProspectArea ,
		pDoc->m_sCrew );

	if(pDoc->m_bIs3D )
	{
		s+="        3D";
	}
	else
	{
		s+="        2D";
	}

	CString s2;
	CString sKilometer=pDoc->m_s3DDesiFullCover ;
	CString sShotQty=pDoc->m_s3DDesiShotQty ;
	if(!pDoc->m_bIs3D )
	{
		sKilometer=pDoc->m_s2DDesiFullCover;
		sShotQty=pDoc->m_s2DDesiShotQty ;
	}
	s2.Format ("��Ʋ���: %s ��(��)    ����: %s  ����:%s",
			pDoc->m_sDesiLineQty,
			sShotQty,
			sKilometer);
	s+=s2;

	m_rc.SetLeftUpString (s);

	m_rc.SetGridContent(0,0,"���߻�\r������");
	m_rc.SetGridContent(0,1,"��ֹ����");
	m_rc.SetGridContent(0,2,"��  ��  ��  ʵ  ��  ��  ��");
	m_rc.SetGridContent(1,2,"����");
	m_rc.SetGridContent(1,3,"����");
	m_rc.SetGridContent(1,4,"С����");
	m_rc.SetGridContent(1,5,"΢�⾮");

	m_rc.SetGridContent(0,6,"�� �� �� �� ͳ ��");
	m_rc.SetGridContent(1,6,"һ��");
	m_rc.SetGridContent(1,7,"����");
	m_rc.SetGridContent(1,8,"�յ�");
	m_rc.SetGridContent(1,9,"��Ʒ");

	m_rc.SetGridContent(0,10,"���\r����");
	m_rc.SetGridContent(0,11,"����\r�ϸ�");
	m_rc.SetGridContent(0,12,"���\r����");
	m_rc.SetGridContent(0,13,"����\r�ϸ�");
	m_rc.SetGridContent(0,14,"����\r�ϸ�");
	m_rc.SetGridContent(0,15,"�¼�");
	m_rc.SetGridContent(0,16,"�ռ�");
	m_rc.SetGridContent(0,17,"���\r����\r��־");
	m_rc.SetGridContent(0,18,"�ϸ�\r����\r��־");
	m_rc.SetGridContent(0,19,"�ֳ�\r���");
	m_rc.SetGridContent(0,20,"����¼");
	m_rc.SetGridContent(0,21,"ͼ���\r����\r���");

	m_rc.SetGridContent(iRecordQty+2,0,"�ϼ�");
	m_rc.SetGridContent(iRecordQty+3,0,"�ۼ�");


	CString sNote[5];

	for(i=0;i<pDoc->GetRecordQty ();i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;

		if(i<iRecordQty)
		{
			// ������
			m_rc.SetGridContent(2+i,0,pRecord->GetAt (0));

			// ��ֹ���ڣ�
			date.Set(pRecord->GetAt(1),pRecord->GetAt(2),pRecord->GetAt(3));
			s="";
			//if(date.GetYear() !=0)
			{
				s=date.GetDateString ();
			}

			date.Set(pRecord->GetAt(4),pRecord->GetAt(5),pRecord->GetAt(6));
			//if(date.GetYear() !=0)
			{
				s+="--"+date.GetDateString ();
			}		
			
			m_rc.SetGridContent(2+i,1,s);
		}

		for(j=2;j<=21;j++)
		{
			s=pRecord->GetAt (j+5);
			s.Trim ();
			m_rc.SetGridContent(2+i,j,s);
		}
	
		for(j=0;j<5;j++)
		{
			s=pRecord->GetAt (27+j);
			s.Trim ().MakeUpper ();
			if(s!="NULL")
			{
				sNote[j]+=s;
			}
		}
	}

	m_rc.SetGridContent(4+iRecordQty,0,"�����������(1����Ŀ���м���������2���ල�������ල����ͳ�������3�����ּ����ĵ����⣻4���²��ල�����ص㣻5����һ����Ҫ��������Ŀ�ſ�):\r"
					+sNote[0]+sNote[1]+sNote[2]+sNote[3]+sNote[4], CW_GRIDWIDTH);
	m_rc.SetGridFormat(4+iRecordQty,0,DT_LEFT);
	
	return;
}

// �� ̽ �� �� �� �� ר ҵ �� �� �� �� ��
void CReportView::CreateReport05()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,k;
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
		
		sItem[4]=pRecord->GetAt (5);
		sItem[5]=pRecord->GetAt (6);
		sItem[6]=pRecord->GetAt (7);
		
		f=stof(sItem[6]);
		if(f!=0)
		{
			sItem[7]=vtos(stof(pRecord->GetAt (8))/f);
		}
		else
		{
			sItem[7]="";
		}

		sItem[8]=pRecord->GetAt (9);
		sItem[9]=pRecord->GetAt (10);
		sItem[10]=pRecord->GetAt (11);
		sItem[11]=pRecord->GetAt (12);
		sItem[12]=pRecord->GetAt (13);
		sItem[13]=pRecord->GetAt (14);
		sItem[14]=pRecord->GetAt (15);
		sItem[15]=pRecord->GetAt (16);
		sItem[16]=pRecord->GetAt (17);
		sItem[17]=pRecord->GetAt (18);
		sItem[18]=pRecord->GetAt (19);
		sItem[19]=pRecord->GetAt (20);

		date.Set (pRecord->GetAt (1),pRecord->GetAt (2),pRecord->GetAt (3));
		if(date>=CMyDate(pDoc->m_iStartYear,
							pDoc->m_iStartMonth,
							pDoc->m_iStartDay))
		{
			iWeekRecordQty++;

			for(k=4;k<=19;k++)
			{
				fWeekSum[k]+=stof(sItem[k]);
			}
		}

		for(k=4;k<=19;k++)
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

	m_rc.CombineGrid (0,0,4,7);
	m_rc.CombineGrid (0,0,8,9);
	m_rc.CombineGrid (0,0,10,12);
	m_rc.CombineGrid (0,0,13,15);
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
	m_rc.SetGridContent(0,3,"���\r������");
	m_rc.SetGridContent(0,4,"�ල��ʵ������");
	m_rc.SetGridContent(1,4,"����");
	m_rc.SetGridContent(1,5,"����\r����");

	m_rc.SetGridContent(1,6,"����\r����");
	m_rc.SetGridContent(1,7,"������");
	m_rc.SetGridContent(0,8,"�������(���)");
	m_rc.SetGridContent(1,8,"��x");
	m_rc.SetGridContent(1,9,"��y");

	m_rc.SetGridContent(0,10,"����ϲ�(���)");
	m_rc.SetGridContent(1,10,"��x");
	m_rc.SetGridContent(1,11,"��y");
	m_rc.SetGridContent(1,12,"��h");
	m_rc.SetGridContent(0,13,"���⾫��(��������)");
	m_rc.SetGridContent(1,13,"Mx(+/-)");
	m_rc.SetGridContent(1,14,"My(+/-)");
	m_rc.SetGridContent(1,15,"Mh(+/-)");
	m_rc.SetGridContent(0,16,"Ұ  ��  ��  ��");
	m_rc.SetGridContent(1,16,"����\r��־");
	m_rc.SetGridContent(1,17,"����\r��λ");
	m_rc.SetGridContent(1,18,"����\r����");
	m_rc.SetGridContent(1,19,"ʩ��\r����");
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

		pDoc->GetProjectInfoByNo(pRecord->GetAt (29),&arrayProject);

		m_rc.SetGridContent(2+i,0,date.GetDateString ());
		m_rc.SetGridContent(2+i,1,arrayProject.GetAt (1));
		m_rc.SetGridContent(2+i,2,arrayProject.GetAt (8));
		m_rc.SetGridContent(2+i,3,pDoc->GetLineName (pRecord->GetAt (0)));
		
		sItem[4]=pRecord->GetAt (5);
		sItem[5]=pRecord->GetAt (6);
		sItem[6]=pRecord->GetAt (7);
		sItem[7]=pRecord->GetAt (8);
		sItem[8]=pRecord->GetAt (9);
		sItem[9]=pRecord->GetAt (10);
		sItem[10]=pRecord->GetAt (11);
		sItem[11]=pRecord->GetAt (12);
		sItem[12]=pRecord->GetAt (13);
		sItem[13]=pRecord->GetAt (14);
		sItem[14]=pRecord->GetAt (15);
		sItem[15]=pRecord->GetAt (16);
		sItem[16]=pRecord->GetAt (17);
		sItem[17]=pRecord->GetAt (18);
		sItem[18]=pRecord->GetAt (19);
		sItem[19]=pRecord->GetAt (20);

		sNote=pRecord->GetAt (22);

		sJS+=pRecord->GetAt (23);
		sJS+=pRecord->GetAt (24);
		sJS+=pRecord->GetAt (25);
		sJS+=pRecord->GetAt (26);
		sJS+=pRecord->GetAt (27);

		for(k=4;k<=19;k++)
		{
			m_rc.SetGridContent(2+i,k,sItem[k]);
		}

		m_rc.SetGridContent(2+i,20,sNote);
	}

	for(k=4;k<=19;k++)
	{
		m_rc.SetGridContent(2+iWeekRecordQty,k,vtos(fWeekSum[k]));
		m_rc.SetGridContent(3+iWeekRecordQty,k,vtos(fProjectSum[k]));
	}

	// fanhua test:
	m_rc.SetGridContent(4+iWeekRecordQty,0,"�����������(1����Ŀ�����������������2���ල�������ص��ǶԲ����������ճ���������2�������������ڵ����⼰����Ҫ��3�����ܲ����ල�����ص��):\r"+sJS, CW_GRIDWIDTH);
	m_rc.SetGridFormat(4+iWeekRecordQty,0,DT_LEFT);
	
	return;
}


