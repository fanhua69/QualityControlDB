
#include "stdafx.h"
#include "QCDB.h"
#include "MemDC.h"

#include "ReportDoc.h"
#include "ReportView.h"
#include "DlgReportShowProperty.h"
#include "MyDate.h"
#include "fhcglobal.h"
#include "math.h"


////////////////////////////////////////////////
//  ________��ĿҰ��ɼ�ʩ�������ලͳ�Ʊ�
//  ��0110ʩ�������ලͳ�Ʊ� ��16
////////////////////////////////////////////////
void CReportView::CreateReport16()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j;
	CMyDate date;
	CStringArray *pRecord=NULL;
	int iRecordQty=pDoc->GetRecordQty ();

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	m_rc.SetGridQty (iRecordQty+2,20);
	m_rc.CombineGrid (0,1,0,0);
	m_rc.CombineGrid (0,1,1,1);
	m_rc.CombineGrid (0,1,19,19);

	m_rc.CombineGrid (0,0,2,8);
	m_rc.CombineGrid (0,0,9,13);
	m_rc.CombineGrid (0,0,14,18);


	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("%s��ĿҰ��ɼ�ʩ�������ලͳ�Ʊ�",pDoc->m_sProjectName );
	m_rc.SetTitle (s);	

	m_rc.SetGridContent (0,0,"��\r��");
	m_rc.SetGridContent (0,1,"������");
	m_rc.SetGridContent (1,2,"�����ͺ�");
	m_rc.SetGridContent (1,3,"����");
	m_rc.SetGridContent (1,4,"���Ǵ���");
	m_rc.SetGridContent (1,5,"����");
	m_rc.SetGridContent (1,6,"��Ͼ�");
	m_rc.SetGridContent (1,7,"���");
	m_rc.SetGridContent (1,8,"�۲�ϵͳ");
	m_rc.SetGridContent (1,9,"�ͺ�");
	m_rc.SetGridContent (1,10,"����");
	m_rc.SetGridContent (1,11,"Lx");
	m_rc.SetGridContent (1,12,"Ly");
	m_rc.SetGridContent (1,13,"ͼ��");
	m_rc.SetGridContent (1,14,"ǰ��");
	m_rc.SetGridContent (1,15,"�ͽ�");
	m_rc.SetGridContent (1,16,"�߽�");
	m_rc.SetGridContent (1,17,"����");
	m_rc.SetGridContent (1,18,"��¼����");
	m_rc.SetGridContent (1,19,"��ע");

	m_rc.SetGridContent (0,2,"��    Ҫ    ��    ��    ��    ��");
	m_rc.SetGridContent (0,9,"��  ��  ��  ��  ��");
	m_rc.SetGridContent (0,14,"��  Ҫ  ��  ��  ��  ��");
	m_rc.SetGridContent (0,19,"��ע");


	//////////////////////////////////
	// Left:
	CStringArray arrayMonitor;
	CMyDate dateStat;
	CString sWell="";
	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;
		
		m_rc.SetGridContent (i+2,0,vtos(i+1));
		m_rc.SetGridContent (i+2,1,pRecord->GetAt (1));
	
		for(j=2;j<=19;j++)
		{
			m_rc.SetGridContent (i+2,j,pRecord->GetAt (j));
		}

		// ����
		sWell="";
		for(j=0;j<5;j++)
		{
			s=pRecord->GetAt (20+j*2+1);s.Trim ();
			if(stof(s)!=0)
			{
				s+="mX";sWell+=s;
				s=pRecord->GetAt (20+j*2+2);s.Trim ();
				s+="kg\r";sWell+=s;
			}
		}

		m_rc.SetGridContent (i+2,7,sWell);

		// ��Ͼ�
		sWell="";
		for(j=0;j<5;j++)
		{
			s=pRecord->GetAt (30+j*2+1);s.Trim ();
			if(stof(s))
			{
				s+="��X";	sWell+=s;	
				s=pRecord->GetAt (30+j*2+2);s.Trim ();
				s+="mX";sWell+=s;
				s=pRecord->GetAt (30+j*2+3);s.Trim ();
				s+="kg\r";sWell+=s;
			}
		}


		m_rc.SetGridContent (i+2,6,sWell);

		AddMonitor(arrayMonitor, pRecord->GetAt (20));
	}

	s.Format("��ţ�                 ͳ�����ڣ�%d��%d��%d��",
						pDoc->m_iStatYear,
						pDoc->m_iStatMonth,
						pDoc->m_iStatDay);
	m_rc.SetLeftUpString (s);

	s.Format ("ʩ����λ��"+pDoc->m_sServer +"  "+pDoc->m_sCrew +"��");

	m_rc.SetRightUpString (s);

	s="פ�Ӽල��"+GetMonitorString(arrayMonitor);
	m_rc.SetLeftDownString (s);
	return ;
	

}

///////////////////////////////////////////////////////////////////
//  ________��ĿҰ��ɼ�ʩ�����ʵ�﹤�����ලͳ�Ʊ�
//  ��ƹ������ڱ�0201�����У�ʵ�ʹ������ڱ�0301�������ձ�  ��17
///////////////////////////////////////////////////////////////////
void CReportView::CreateReport17()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,k;
	CMyDate date;
	CStringArray *pRecord=NULL;
	CString sLine;

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	int iRecordQty=pDoc->GetRecordQty ();
	m_rc.SetGridQty (iRecordQty+3,20);
	m_rc.CombineGrid (0,2,0,0);
	m_rc.CombineGrid (0,2,1,1);
	m_rc.CombineGrid (0,2,19,19);
	m_rc.CombineGrid (0,2,20,20);

	for(i=2;i<=8;i++)
	{
		m_rc.CombineGrid (1,2,i,i);
	}

	for(i=17;i<=18;i++)
	{
		m_rc.CombineGrid (1,2,i,i);
	}

	m_rc.CombineGrid (0,0,2,4);
	m_rc.CombineGrid (0,0,5,18);
	m_rc.CombineGrid (1,1,9,10);
	m_rc.CombineGrid (1,1,11,12);
	m_rc.CombineGrid (1,1,13,14);
	m_rc.CombineGrid (1,1,15,16);

	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("%s��ĿҰ��ɼ�ʩ�����ʵ�﹤�����ලͳ�Ʊ�",pDoc->m_sProjectName );
	m_rc.SetTitle (s);	


	m_rc.SetGridContent (0,0,"��\r��");
	m_rc.SetGridContent (0,1,"������");
	m_rc.SetGridContent (2,2,"������\r����");
	m_rc.SetGridContent (2,3,"������\r���");
	m_rc.SetGridContent (2,4,"����\r����");
	m_rc.SetGridContent (2,5,"������\r����");
	m_rc.SetGridContent (2,6,"������\r���");
	m_rc.SetGridContent (2,7,"����");
	m_rc.SetGridContent (2,8,"��\r��\r��\r��");
	m_rc.SetGridContent (2,9,"��\r��");
	m_rc.SetGridContent (2,10,"%");
	m_rc.SetGridContent (2,11,"��\r��");
	m_rc.SetGridContent (2,12,"%");
	m_rc.SetGridContent (2,13,"��\r��");
	m_rc.SetGridContent (2,14,"%");
	m_rc.SetGridContent (2,15,"��\r��");
	m_rc.SetGridContent (2,16,"%");
	m_rc.SetGridContent (2,17,"�ϸ�\rС����\r����");
	m_rc.SetGridContent (2,18,"�ϸ�\r΢�⾮\r����");
	m_rc.SetGridContent (2,19,"ʩ������");
	m_rc.SetGridContent (2,20,"��ע");

	m_rc.SetGridContent (0,2,"�� �� �� �� ��");
	m_rc.SetGridContent (0,5,"ʵ �� �� �� ʵ �� �� �� ��");
	m_rc.SetGridContent (1,9,"һ��Ʒ");
	m_rc.SetGridContent (1,11,"����Ʒ");
	m_rc.SetGridContent (1,13,"��Ʒ");
	m_rc.SetGridContent (1,15,"�յ�");


	//////////////////////////////////
	// Left:
	float f3DDesiAreaQty=stof(pDoc->m_s3DDesiWorkAreaQty );
	int i2DDesiShotQty=stof(pDoc->m_s2DDesiShotQty);
	int i3DDesiShotQty=stof(pDoc->m_s3DDesiShotQty);

	CString sMonitor="";
	CMyDate dateStat;
	CString sWell="";
	float f2DShotQty=0.0;
	float f3DShotQty=0.0;
	float fAreaQty=0.0;
	float fKiloQty=0.0;
	float fSum[19];
	float f=0.0;
	int  iTotalShot=0,iValidShot=0;
	int iDailyRecordQty=pDoc->m_docVice .GetRecordQty ();
	CStringArray *pDailyRecord=NULL;
	CMyDate dateStart;
	CMyDate dateEnd;
	dateStart.SetYear (100000);
	dateEnd.SetYear (0);

	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;
		
		m_rc.SetGridContent (i+3,0,vtos(i+1));
		m_rc.SetGridContent (i+3,1,pRecord->GetAt (1));

		// �����ǳ���
		fKiloQty=stof(pRecord->GetAt (2));
		m_rc.SetGridContent (i+3,2,vtos(fKiloQty));

		// ���������
		f2DShotQty=stof(pRecord->GetAt (3));
		f3DShotQty=stof(pRecord->GetAt (4));
		if(i3DDesiShotQty!=0)
		{
			fAreaQty=f3DShotQty/i3DDesiShotQty*f3DDesiAreaQty;
		}
		else
		{
			fAreaQty=0;
		}
		m_rc.SetGridContent (i+3,3,vtos(fAreaQty,2));

		// �������
		if(pDoc->m_bIs3D )
		{
			m_rc.SetGridContent (i+3,4,vtos(f3DShotQty,0));
		}
		else
		{
			m_rc.SetGridContent (i+3,4,vtos(f2DShotQty,0));
		}

		// �Ա�������ͣ�
		for(j=0;j<19;j++)
		{
			fSum[j]=0.0;
		}
		for(j=0;j<iDailyRecordQty;j++)
		{
			pDailyRecord=pDoc->m_docVice.GetRecord (j);
			if(pDailyRecord->GetAt (0)!=pRecord->GetAt (0))continue;
			for(k=13;k<=32;k++)
			{
				fSum[7]+=stof(pDailyRecord->GetAt (k));
			}
			
			fSum[8]+=stof(pDailyRecord->GetAt (2));

			fSum[9]+=stof(pDailyRecord->GetAt (3));
			fSum[11]+=stof(pDailyRecord->GetAt (4));
			fSum[13]+=stof(pDailyRecord->GetAt (5));
			fSum[15]+=stof(pDailyRecord->GetAt (6));

			fSum[17]+=stof(pDailyRecord->GetAt (7));
			fSum[18]+=stof(pDailyRecord->GetAt (8));

			// ��ʼʩ������:
			date.Set(pDailyRecord->GetAt (9),pDailyRecord->GetAt (10),pDailyRecord->GetAt (11));
			if(date>dateEnd)
			{
				dateEnd=date;
			}
			if(date<dateStart)
			{
				dateStart=date;
			}

			// פ�Ӽල
			s=pDailyRecord->GetAt (12);
			if(!IsEmpty(s))
			{
				if(sMonitor!="")
				{
					sMonitor+=",";
				}
				sMonitor+=s;
			}
		}

		// 
		iValidShot=fSum[7]-fSum[8];
		if(f2DShotQty!=0)
		{
			fSum[5]=iValidShot/f2DShotQty*fKiloQty;
		}

		if(f3DShotQty!=0)
		{
			fSum[6]=iValidShot/f3DShotQty*fAreaQty;
		}

		iTotalShot=fSum[7]+fSum[8];
		if(iTotalShot!=0)
		{
			fSum[10]=fSum[9]/iTotalShot*100;
			fSum[12]=fSum[11]/iTotalShot*100;
			fSum[14]=fSum[13]/iTotalShot*100;
			fSum[16]=fSum[15]/iTotalShot*100;
		}

		// ��������:
		m_rc.SetGridContent (i+3,5,vtos(fSum[5],2));
		m_rc.SetGridContent (i+3,6,vtos(fSum[6],2));
		m_rc.SetGridContent (i+3,7,vtos(fSum[7],0));
		m_rc.SetGridContent (i+3,8,vtos(fSum[8],0));
		m_rc.SetGridContent (i+3,9,vtos(fSum[9],0));
		m_rc.SetGridContent (i+3,10,vtos(fSum[10],2));
		m_rc.SetGridContent (i+3,11,vtos(fSum[11],0));
		m_rc.SetGridContent (i+3,12,vtos(fSum[12],2));
		m_rc.SetGridContent (i+3,13,vtos(fSum[13],0));
		m_rc.SetGridContent (i+3,14,vtos(fSum[14],2));
		m_rc.SetGridContent (i+3,15,vtos(fSum[15],0));
		m_rc.SetGridContent (i+3,16,vtos(fSum[16],2));
		m_rc.SetGridContent (i+3,17,vtos(fSum[17],0));
		m_rc.SetGridContent (i+3,18,vtos(fSum[18],0));

		// ����
		m_rc.SetGridContent (i+3,19,dateStart.GetDateString ()+"-\r"+dateEnd.GetDateString ());

	}

	s.Format("��ţ�                 ͳ�����ڣ�%d��%d��%d��",pDoc->m_iStatYear ,pDoc->m_iStatMonth ,pDoc->m_iStatDay );
	m_rc.SetLeftUpString (s);

	s.Format ("ʩ����λ��"+pDoc->m_sServer +"  "+pDoc->m_sCrew +"��");

	m_rc.SetRightUpString (s);

	s="פ�Ӽල��"+sMonitor;
	m_rc.SetLeftDownString (s);
	return ;


}

void CReportView::CheckWellKindQty(	CDataBrowseDoc *pDoc,
									CWellProperty  *pSingleWell,
									CWellProperty  *pMultiWell,
									int &iSingleWellKindQty,
									int &iMultiWellKindQty)
{
	int iRecordQty=pDoc->GetRecordQty ();
	int i=0,j=0;
	CStringArray *pRecord=NULL;

	iSingleWellKindQty=0;
	iMultiWellKindQty=0;

	int n=0;
	CString s;
	float f;

	int bSingleValid[10],bMultiValid[10];
	memset(bSingleValid,0,sizeof(int)*10);
	memset(bMultiValid,0,sizeof(int)*10);

	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord(i);
		
		for(j=1;j<=10;j++)
		{
			s=pRecord->GetAt (j);
			f=stof(s);
			if(fabs(f)>0.00001)
			{
				bSingleValid[j-1]=1;
			}
		}

		for(j=11;j<=20;j++)
		{
			s=pRecord->GetAt (j);
			f=stof(s);
			if(fabs(f)>0.00001)
			{
				bMultiValid[j-11]=1;
			}
		}
	}

	int iOrder=0;
	for(i=0;i<10;i++)
	{
		pSingleWell[i].iValidOrder=-1;
		if(bSingleValid[i]!=0)
		{
			pSingleWell[i].iValidOrder = iOrder;
			iOrder++;
		}
	}
	iSingleWellKindQty=iOrder;

	iOrder=0;
	for(i=0;i<10;i++)
	{
		pMultiWell[i].iValidOrder=-1;
		if(bMultiValid[i]!=0)
		{
			pMultiWell[i].iValidOrder = iOrder;
			iOrder++;
		}
	}
	iMultiWellKindQty=iOrder;




	return;
}

int CReportView::GetFinishedShotQty(CDataBrowseDoc *pDoc,
									CString sLineNo,
									CWellProperty *pSSP,
									CWellProperty *pMSP,
									int &iHVLQty,
									CString &sNote,
									CString &sMonitor)
{
	sLineNo.Trim();
	sLineNo.MakeUpper();

	CString sNoLine;
	CStringArray *pRecord=NULL;
	CStringArray arrayMonitor;
	int i,j;
	int iShotQty=0;
	CString s;

	for(j=0;j<10;j++)
	{
		pSSP[j].iQty =0;
		pMSP[j].iQty =0;
	}
	iHVLQty=0;

	for(i=0;i<pDoc->GetRecordQty();i++)
	{
		pRecord=pDoc->GetRecord(i);
		sNoLine=pRecord->GetAt(0);
		sNoLine.Trim();
		sNoLine.MakeUpper();
		if(sNoLine==sLineNo)
		{
			for(j=1;j<=10;j++)
			{
				pSSP[j-1].iQty +=stof(pRecord->GetAt (j));
				iShotQty+=pSSP[j-1].iQty;
			}
			for(j=11;j<=20;j++)
			{
				pMSP[j-11].iQty +=stof(pRecord->GetAt (j));
				iShotQty+=pMSP[j-11].iQty;
			}

			iHVLQty+=stof(pRecord->GetAt (11));

			// The note string:
			s=pRecord->GetAt (12);
			s.Trim ().MakeUpper ();
			if(s!=""&&s!="NULL")
			{
				sNote+=s;
			}

			AddMonitor(arrayMonitor,pRecord->GetAt (13));
		}
	}

	sMonitor=GetMonitorString(arrayMonitor);

	return iShotQty;
}


CString CReportView::GetChineseNumber(int i)
{
	switch (i)
	{
	case 0:
		return "��";
	case 1 :
		return "һ";
	case 2 :
		return "��";
	case 3 :
		return "��";
	case 4 :
		return "��";
	case 5 :
		return "��";
	case 6 :
		return "��";
	case 7 :
		return "��";
	case 8 :
		return "��";
	case 9 :
		return "��";
	case 10:
		return "ʮ";
	default:
		ASSERT(false);
		return "����";
	}		
}

///////////////////////////////////////////////////
//  ���           ����̽��������ͳ�Ʊ�
//           ����0201���ߣ�  ��18
///////////////////////////////////////////////////
void CReportView::CreateReport18()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,n;
	CMyDate date;
	CStringArray *pRecord=NULL;
	CString sLine;
	int iStart=0;

	CWellProperty CSingleWell[10];
	CWellProperty CMultiWell[10];
	for(i=0;i<10;i++)
	{
		memcpy(&CSingleWell[i],&pDoc->m_CSingleWell[i],sizeof(CWellProperty));
		memcpy(&CMultiWell[i],&pDoc->m_CMultiWell[i]  ,sizeof(CWellProperty));
	}

	int iSingleWellQty=0,iMultiWellQty=0;
	CheckWellKindQty(pDoc,
					CSingleWell,
					CMultiWell,
					iSingleWellQty,
					iMultiWellQty);

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	int iRecordQty=pDoc->m_docVice .GetRecordQty ();
	m_rc.SetGridQty (iRecordQty+3,iSingleWellQty*3+ iMultiWellQty*4+9 );
	for(i=0;i<=3;i++)
	{
		m_rc.CombineGrid (0,1,i,i);
	}
	for(i=0;i<iSingleWellQty;i++)
	{
		m_rc.CombineGrid (0,0,4+i*3,4+i*3+2);
	}

	for(i=0;i<iMultiWellQty;i++)
	{
		iStart=4+iSingleWellQty*3;
		m_rc.CombineGrid (0,0,iStart+i*4,iStart+i*4+3);
	}

	iStart=4+iSingleWellQty*3+iMultiWellQty*4;
	m_rc.CombineGrid (0,0,iStart,iStart+4);
	m_rc.CombineGrid (iRecordQty+2,iRecordQty+2,0,1);


	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("%s���%s����̽��������ͳ�Ʊ�",pDoc->m_sYear , pDoc->m_sProjectName );
	m_rc.SetTitle (s);	


	m_rc.SetGridContent (0,0,"��\r��");
	m_rc.SetGridContent (0,1,"���ߺ�");
	m_rc.SetGridContent (0,2,"���\r����");
	m_rc.SetGridContent (0,3,"���\r����");

	for(i=0;i<iSingleWellQty;i++)
	{
		iStart=4+i*3;
		m_rc.SetGridContent (0,iStart,"��������("+GetChineseNumber(i+1)+")");
		m_rc.SetGridContent (1,iStart,"����\r(m)");
		m_rc.SetGridContent (1,iStart+1,"ҩ��\r(Kg)");
		m_rc.SetGridContent (1,iStart+2,"����\r����");
	}

	for(i=0;i<iMultiWellQty;i++)
	{
		iStart=4+iSingleWellQty*3+i*4;
		m_rc.SetGridContent (0,iStart,"��ϼ���("+GetChineseNumber(i+1)+")");
		m_rc.SetGridContent (1,iStart,"����");
		m_rc.SetGridContent (1,iStart+1,"����\r(m)");
		m_rc.SetGridContent (1,iStart+2,"ҩ��\r(Kg)");
		m_rc.SetGridContent (1,iStart+3,"����\r����");
	}
	
	iStart=4+iSingleWellQty*3+iMultiWellQty*4;
	
	m_rc.SetGridContent (0,iStart,"����λ��");
	m_rc.SetGridContent (1,iStart,"����\r�㼤\r����");
	m_rc.SetGridContent (1,iStart+1,"ռ����\r��(%)");
	m_rc.SetGridContent (1,iStart+2,"����\r�㼤\r����");
	m_rc.SetGridContent (1,iStart+3,"ռ����\r��(%)");
	m_rc.SetGridContent (1,iStart+4,"��  ע");

	m_rc.SetGridContent (iRecordQty+2,0,"��  ��");

	//////////////////////////////////
	// Left:
	float f3DDesiAreaQty=stof(pDoc->m_s3DDesiWorkAreaQty );
	int i2DDesiShotQty=stof(pDoc->m_s2DDesiShotQty);
	int i3DDesiShotQty=stof(pDoc->m_s3DDesiShotQty);

	CString sMonitor="";
	float f=0.0;

	iRecordQty=pDoc->m_docVice .GetRecordQty(); 

	CString sNo;
	CStringArray *pRecordLine=NULL;
	int iFinishedShotQty=0;

	int iWellOrder=0;
	int iHVLQty=0;
	CString sNote;

	float *pfSum=new float[9+iSingleWellQty*3+iMultiWellQty*4+10];
	memset(pfSum,0,sizeof(float)*(9+iSingleWellQty*3+iMultiWellQty*4+10));

	for(i=0;i<iRecordQty;i++)
	{
		pRecordLine=pDoc->m_docVice .GetRecord (i);
		if(!pRecordLine)break;
		
		m_rc.SetGridContent (i+2,0,vtos(i+1));
		
		sNo=pRecordLine->GetAt (0);
		m_rc.SetGridContent (i+2,1,pRecordLine->GetAt (1));
		if(pDoc->m_bIs3D )
		{
			m_rc.SetGridContent (i+2,2,pRecordLine->GetAt (3));
			pfSum[2]+=stof(pRecordLine->GetAt (3));
		}
		else
		{
			m_rc.SetGridContent (i+2,2,pRecordLine->GetAt (2));
			pfSum[2]+=stof(pRecordLine->GetAt (2));
		}

		sNote="";
		iFinishedShotQty=GetFinishedShotQty(pDoc,
											sNo,
											CSingleWell,
											CMultiWell,
											iHVLQty,
											sNote,
											sMonitor);

		m_rc.SetGridContent (i+2,3,vtos(iFinishedShotQty));
		pfSum[3]+=iFinishedShotQty;

		// ��������
		for(j=0;j<10;j++)
		{
			if(CSingleWell[j].iQty !=0)
			{
				n=4+CSingleWell[j].iValidOrder *3;
				m_rc.SetGridContent (i+2,n,vtos(CSingleWell[j].fDepth ));
				m_rc.SetGridContent (i+2,n+1,vtos(CSingleWell[j].fDynamite ) );
				m_rc.SetGridContent (i+2,n+2,vtos(CSingleWell[j].iQty ));

				pfSum[n]+=CSingleWell[j].fDepth ;
				pfSum[n+1]+=CSingleWell[j].fDynamite ;
				pfSum[n+2]+=CSingleWell[j].iQty ;
			}
		}

		// �ྮ����
		iStart=4+iSingleWellQty*3;
		for(j=0;j<10;j++)
		{
			if(CMultiWell[j].iQty !=0)
			{
				n=iStart+CMultiWell[j].iValidOrder*4;
				m_rc.SetGridContent (i+2,n,vtos(CMultiWell[j].iComboQty ) );
				m_rc.SetGridContent (i+2,n+1,vtos(CMultiWell[j].fDepth ));
				m_rc.SetGridContent (i+2,n+2,vtos(CMultiWell[j].fDynamite ) );
				m_rc.SetGridContent (i+2,n+3,vtos(CMultiWell[j].iQty ));
			
				pfSum[n]+=CMultiWell[j].iComboQty ;
				pfSum[n+1]+=CMultiWell[j].fDepth ;
				pfSum[n+2]+=CMultiWell[j].fDynamite ;
				pfSum[n+3]+=CMultiWell[j].iQty ;
			}
		}

		// ����λ��:
		iStart=4+iSingleWellQty*3+iMultiWellQty*4;
		m_rc.SetGridContent (i+2,iStart,vtos(iHVLQty));
		pfSum[iStart]+=iHVLQty ;

		f=iHVLQty/(float)iFinishedShotQty*100;
		m_rc.SetGridContent (i+2,iStart+1,vtos(f,2));
		pfSum[iStart+1]+=f/iRecordQty ;

		m_rc.SetGridContent (i+2,iStart+2,vtos(iFinishedShotQty-iHVLQty));
		pfSum[iStart+2]+=iFinishedShotQty-iHVLQty ;

		m_rc.SetGridContent (i+2,iStart+3,vtos(100-f,2));
		pfSum[iStart+3]+=(100-f)/iRecordQty ;
		
		//��   ע
		m_rc.SetGridContent (i+2,iStart+4,sNote);
	}

	for(i=2;i<=iStart+3;i++)
	{
		m_rc.SetGridContent (iRecordQty+2,i,vtos((int)(pfSum[i])));
	}
	m_rc.SetGridContent (iRecordQty+2,iStart+1,vtos(pfSum[iStart+1],2));
	m_rc.SetGridContent (iRecordQty+2,iStart+3,vtos(pfSum[iStart+3],2));


	s.Format ("���:         ��Ŀ���ƣ�%s    Ͷ�ʷ���%s    ��ҵ����%s",
		pDoc->m_sProjectName ,
		pDoc->m_sClient ,
		pDoc->m_sServer +pDoc->m_sCrew +"��");
	m_rc.SetLeftUpString (s);

	s="�ֳ��ල��"+sMonitor;
	m_rc.SetRightUpString (s);

	s="�Ʊ� "+pDoc->m_sReportCreator ;
	m_rc.SetLeftDownString (s);

	s="��ˣ� "+pDoc->m_sReportAuditor;
	m_rc.SetRightDownString (s);

	delete []pfSum;

	return ;
}



int CReportView::GetClassify(CDataBrowseDoc *pDoc,
							CString sLineNo,
							CClassify *pClassify,
							CString &sMonitor)
{
	sLineNo.Trim();
	sLineNo.MakeUpper();

	CString sNoLine;
	CStringArray *pRecord=NULL;
	int i,j;
	int iShotQty=0;
	pClassify->Reset ();
	CStringArray arrayMonitor;

	for(i=0;i<pDoc->GetRecordQty();i++)
	{
		pRecord=pDoc->GetRecord(i);
		sNoLine=pRecord->GetAt(0);
		sNoLine.Trim();
		sNoLine.MakeUpper();
		if(sNoLine==sLineNo)
		{
			pClassify->iInitFirst	= stof(pRecord->GetAt (11));
			pClassify->iInitSecond	= stof(pRecord->GetAt (12));
			pClassify->iInitBad		= stof(pRecord->GetAt (13));
			pClassify->iInitBlank	= stof(pRecord->GetAt (14));

			iShotQty+=pClassify->iInitFirst;
			iShotQty+=pClassify->iInitSecond;
			iShotQty+=pClassify->iInitBad;

			pClassify->iReFirst		= stof(pRecord->GetAt (15));
			pClassify->iReSecond	= stof(pRecord->GetAt (16));
			pClassify->iReBad		= stof(pRecord->GetAt (17));
			pClassify->iReBlank		= stof(pRecord->GetAt (18));


			pClassify->iRefTotal 	= stof(pRecord->GetAt (19));
			pClassify->iRefValid	= stof(pRecord->GetAt (20));
			pClassify->iMicroWellTotal = stof(pRecord->GetAt (21));
			pClassify->iMicroWellValid = stof(pRecord->GetAt (22));
			
			if(!IsEmpty(pRecord->GetAt (23)))
			{
				pClassify->sNote +=pRecord->GetAt (23);
			}

			AddMonitor(arrayMonitor,pRecord->GetAt (24));
		}
	}

	sMonitor=GetMonitorString(arrayMonitor);

	return iShotQty;
}

///////////////////////////////////////////////
//  ����ɼ����Ӽ�¼�����������ձ�
//     ����6�����ձ���  ��19
///////////////////////////////////////////////
void CReportView::CreateReport19()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,n;
	CMyDate date;
	CStringArray *pRecord=NULL;
	CString sLine;

	int iSingleWellQty=0,iMultiWellQty=0;

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	int iRecordQty=pDoc->m_docVice .GetRecordQty ();
	m_rc.SetGridQty (iRecordQty+4,26 );
	m_rc.CombineGrid (0,2,0,0);
	m_rc.CombineGrid (0,2,1,1);
	m_rc.CombineGrid (0,2,2,2);
	m_rc.CombineGrid (0,2,3,3);

	m_rc.CombineGrid (0,0,4,11);
	m_rc.CombineGrid (1,1,4,5);
	m_rc.CombineGrid (1,1,6,7);
	m_rc.CombineGrid (1,1,8,9);
	m_rc.CombineGrid (1,1,10,11);

	m_rc.CombineGrid (0,0,12,19);
	m_rc.CombineGrid (1,1,12,13);
	m_rc.CombineGrid (1,1,14,15);
	m_rc.CombineGrid (1,1,16,17);
	m_rc.CombineGrid (1,1,18,19);

	m_rc.CombineGrid (0,2,20,20);

	m_rc.CombineGrid (0,0,21,22);
	m_rc.CombineGrid (1,2,21,21);
	m_rc.CombineGrid (1,2,22,22);
	m_rc.CombineGrid (0,0,23,24);
	m_rc.CombineGrid (1,2,23,23);
	m_rc.CombineGrid (1,2,24,24);

	m_rc.CombineGrid (0,2,25,25);

	m_rc.CombineGrid (iRecordQty+3,iRecordQty+3,0,1);

	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("����ɼ����Ӽ�¼�����������ձ�");
	m_rc.SetTitle (s);	


	m_rc.SetGridContent (0,0,"��\r��");
	m_rc.SetGridContent (0,1,"���ߺ�");
	m_rc.SetGridContent (0,2,"���\r����");
	m_rc.SetGridContent (0,3,"���\r����");

	m_rc.SetGridContent (0,4,"��    ��");
	m_rc.SetGridContent (1,4,"һ��");
	m_rc.SetGridContent (1,6,"����");
	m_rc.SetGridContent (1,8,"����");
	m_rc.SetGridContent (1,10,"�յ�");

	m_rc.SetGridContent (1,12,"һ��");
	m_rc.SetGridContent (1,14,"����");
	m_rc.SetGridContent (1,16,"����");
	m_rc.SetGridContent (1,18,"�յ�");

	for(i=4;i<=18;i+=2)
	{
		m_rc.SetGridContent (2,i,"����");
		m_rc.SetGridContent (2,i+1,"%");
	}

	m_rc.SetGridContent (0,20,"����\r��һ\r����");
	m_rc.SetGridContent (0,21,"С����");
	m_rc.SetGridContent (0,23,"΢�⾮");

	m_rc.SetGridContent (1,21,"����");
	m_rc.SetGridContent (1,22,"�ϸ�");
	m_rc.SetGridContent (1,23,"����");
	m_rc.SetGridContent (1,24,"�ϸ�");
	m_rc.SetGridContent (0,25,"��   ע");


	m_rc.SetGridContent (iRecordQty+3,0,"��  ��");

	//////////////////////////////////
	// Left:
	float f3DDesiAreaQty=stof(pDoc->m_s3DDesiWorkAreaQty );
	int i2DDesiShotQty=stof(pDoc->m_s2DDesiShotQty);
	int i3DDesiShotQty=stof(pDoc->m_s3DDesiShotQty);

	CString sMonitor="";
	float f=0.0;

	iRecordQty=pDoc->m_docVice .GetRecordQty(); 

	CString sNo;
	CStringArray *pRecordLine=NULL;
	int iFinishedShotQty=0;

	int iWellOrder=0;
	int iHVLQty=0;
	CString sNote;

	float *pfSum=new float[25];
	memset(pfSum,0,sizeof(float)*25);

	CClassify classify;
	int iDesiShotQty=0;
	float fRate=0.0;

	for(i=0;i<iRecordQty;i++)
	{
		pRecordLine=pDoc->m_docVice .GetRecord (i);
		if(!pRecordLine)break;
		
		m_rc.SetGridContent (i+3,0,vtos(i+1));
		
		sNo=pRecordLine->GetAt (0);
		m_rc.SetGridContent (i+3,1,pRecordLine->GetAt (1));
		if(pDoc->m_bIs3D )
		{
			m_rc.SetGridContent (i+3,2,pRecordLine->GetAt (3));
			iDesiShotQty=stof(pRecordLine->GetAt (3));
		}
		else
		{
			m_rc.SetGridContent (i+3,2,pRecordLine->GetAt (2));
			iDesiShotQty=stof(pRecordLine->GetAt (2));
		}
		pfSum[2]+=iDesiShotQty;

		iFinishedShotQty=GetClassify(pDoc,sNo,&classify,sMonitor);

		m_rc.SetGridContent (i+3,3,vtos(iFinishedShotQty));
		pfSum[3]+=iFinishedShotQty;

		// ����
		m_rc.SetGridContent (i+3,4,vtos(classify.iInitFirst ));
		pfSum[4]+=classify.iInitFirst;

		fRate=classify.iInitFirst/(float)iDesiShotQty*100.0;
		m_rc.SetGridContent (i+3,5,vtos(fRate,2));
		pfSum[5]+=fRate/iRecordQty;

		m_rc.SetGridContent (i+3,6,vtos(classify.iInitSecond ));
		pfSum[6]+=classify.iInitSecond;

		fRate=classify.iInitSecond/(float)iDesiShotQty*100.0;
		m_rc.SetGridContent (i+3,7,vtos(fRate,2));
		pfSum[7]+=fRate/iRecordQty;

		m_rc.SetGridContent (i+3,8,vtos(classify.iInitBad ));
		pfSum[8]+=classify.iInitBad;

		fRate=classify.iInitBad/(float)iDesiShotQty*100.0;
		m_rc.SetGridContent (i+3,9,vtos(fRate,2));
		pfSum[9]+=fRate/iRecordQty;

		m_rc.SetGridContent (i+3,10,vtos(classify.iInitBlank ));
		pfSum[10]+=classify.iInitBlank;

		fRate=classify.iInitBlank/(float)iDesiShotQty*100.0;
		m_rc.SetGridContent (i+3,11,vtos(fRate,2));
		pfSum[11]+=fRate/iRecordQty;


		// ����
		m_rc.SetGridContent (i+3,12,vtos(classify.iReFirst));
		pfSum[12]+=classify.iReFirst;

		fRate=classify.iReFirst/(float)iDesiShotQty*100.0;
		m_rc.SetGridContent (i+3,13,vtos(fRate,2));
		pfSum[13]+=fRate/iRecordQty;

		m_rc.SetGridContent (i+3,14,vtos(classify.iReSecond ));
		pfSum[14]+=classify.iReSecond;

		fRate=classify.iReSecond/(float)iDesiShotQty*100.0;
		m_rc.SetGridContent (i+3,15,vtos(fRate,2));
		pfSum[15]+=fRate/iRecordQty;

		m_rc.SetGridContent (i+3,16,vtos(classify.iReBad ));
		pfSum[16]+=classify.iReBad;

		fRate=classify.iReBad/(float)iDesiShotQty*100.0;
		m_rc.SetGridContent (i+3,17,vtos(fRate,2));
		pfSum[17]+=fRate/iRecordQty;

		m_rc.SetGridContent (i+3,18,vtos(classify.iReBlank ));
		pfSum[18]+=classify.iReBlank;

		fRate=classify.iReBlank/(float)iDesiShotQty*100.0;
		m_rc.SetGridContent (i+3,19,vtos(fRate,2));
		pfSum[19]+=fRate/iRecordQty;
		
		// 
		m_rc.SetGridContent (i+3,20,vtos(classify.iInitFirst -classify.iReFirst ));
		pfSum[20]+=classify.iInitFirst -classify.iReFirst;
		
		// С����:
		m_rc.SetGridContent (i+3,21,vtos(classify.iRefTotal ));
		pfSum[21]+=classify.iRefTotal;

		m_rc.SetGridContent (i+3,22,vtos(classify.iRefValid ));
		pfSum[22]+=classify.iRefValid;

		// ΢�⾮:
		m_rc.SetGridContent (i+3,23,vtos(classify.iMicroWellTotal ));
		pfSum[23]+=classify.iMicroWellTotal;

		m_rc.SetGridContent (i+3,24,vtos(classify.iMicroWellValid ));
		pfSum[24]+=classify.iMicroWellValid;

		//��   ע
		m_rc.SetGridContent (i+3,25,classify.sNote);
	}

	for(i=2;i<=24;i++)
	{
		m_rc.SetGridContent (iRecordQty+3,i,vtos((int)(pfSum[i])));
	}

	for(i=5;i<=19;i+=2)
	{
		m_rc.SetGridContent (iRecordQty+3,i,vtos(pfSum[i],2));
	}


	s.Format ("���:         ��Ŀ���ƣ�%s    Ͷ�ʷ���%s    ��ҵ����%s",
		pDoc->m_sProjectName ,
		pDoc->m_sClient ,
		pDoc->m_sServer +pDoc->m_sCrew +"��");
	m_rc.SetLeftUpString (s);

	s="�ֳ��ල��"+sMonitor;
	m_rc.SetRightUpString (s);

	s="�Ʊ� "+pDoc->m_sReportCreator ;
	m_rc.SetLeftDownString (s);

	s="��ˣ� "+pDoc->m_sReportAuditor;
	m_rc.SetRightDownString (s);

	delete []pfSum;

	return ;
}


/////////////////////////////////////////////////
//  ��̽����ԭʼ��¼�ල���������ļ��ǼǱ�
//��0403ԭʼ��¼�ල���������ļ��ǼǱ�  ��20 
/////////////////////////////////////////////////
void CReportView::CreateReport20()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,n;
	CMyDate date;
	CStringArray *pRecord=NULL;
	CString sLine;

	int iSingleWellQty=0,iMultiWellQty=0;

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	int iRecordQty=pDoc->GetRecordQty ();
	m_rc.SetGridQty (iRecordQty+3,11);
	m_rc.CombineGrid (0,1,0,0);
	m_rc.CombineGrid (0,1,1,1);
	m_rc.CombineGrid (0,1,2,2);
	m_rc.CombineGrid (0,1,3,3);

	m_rc.CombineGrid (0,0,4,10);

	m_rc.CombineGrid (iRecordQty+2,iRecordQty+2,0,1);

	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("��̽����ԭʼ��¼�ල���������ļ��ǼǱ�");
	m_rc.SetTitle (s);	


	m_rc.SetGridContent (0,0,"��\r��");
	m_rc.SetGridContent (0,1,"�ļ���");
	m_rc.SetGridContent (0,2,"�ϸ�");
	m_rc.SetGridContent (0,3,"��Ʒ");

	m_rc.SetGridContent (0,4,"��       ��       ԭ       ��");
	m_rc.SetGridContent (1,4,"Ŀ�Ĳ�");
	m_rc.SetGridContent (1,5,"������");
	m_rc.SetGridContent (1,6,"����ʱ��");
	m_rc.SetGridContent (1,7,"����");

	m_rc.SetGridContent (1,8,"����");
	m_rc.SetGridContent (1,9,"��ֵ");
	m_rc.SetGridContent (1,10,"����");



	m_rc.SetGridContent (iRecordQty+2,0,"��  ��");

	//////////////////////////////////
	// Left:
	CString sMonitor="";
	float f=0.0;

	iRecordQty=pDoc->GetRecordQty(); 

	CStringArray *pRecordLine=NULL;
	int iFinishedShotQty=0;

	float *pfSum=new float[11];
	memset(pfSum,0,sizeof(float)*11);

	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;
		
		m_rc.SetGridContent (i+2,0,vtos(i+1));
		m_rc.SetGridContent (i+2,1,pRecord->GetAt (0));

		for(j=1;j<=9;j++)
		{
			s=pRecord->GetAt (j);
			if(IsTrue(s))
			{
				m_rc.SetGridContent (i+2,j+1,"��");
				pfSum[j+1]+=stof(s);
			}
		}
	}

	//�ܺͣ�
	for(i=2;i<=10;i++)
	{
		m_rc.SetGridContent (iRecordQty+2,i,vtos((int)(pfSum[i])));
	}


	s.Format ("������%s      ���߻������ţ�%s",
		pDoc->m_sArea ,
		pDoc->m_sLineName );
	m_rc.SetLeftUpString (s);

	// �ֳ��ල:
	sMonitor="";
	for(i=0;i<pDoc->m_docVice.GetRecordQty();i++)
	{
		pRecord=pDoc->m_docVice.GetRecord (i);

		// פ�Ӽල
		s=pRecord->GetAt (0);
		if(!IsEmpty(s))
		{
			if(sMonitor!="")
			{
				sMonitor+=",";
			}
			sMonitor+=s;
		}
	}
	s="�ֳ��ල��"+sMonitor;
	m_rc.SetRightUpString (s);

	s="�Ʊ� "+pDoc->m_sReportCreator ;
	m_rc.SetLeftDownString (s);


	delete []pfSum;

	return ;
}

