
#include "stdafx.h"
#include "QCDB.h"
#include "MemDC.h"

#include "ReportDoc.h"
#include "ReportView.h"
#include "DlgReportShowProperty.h"
#include "MyDate.h"
#include "fhcglobal.h"

///////////////////////////////////////
// ��̽���̼ල���Ĺ������ܱ�
///////////////////////////////////////
void CReportView::CreateReport11()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i;
	CMyDate date;
	CStringArray *pRecord=NULL;
	int iRecordQty=pDoc->GetRecordQty ();

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	m_rc.SetGridQty (iRecordQty+1,6);


	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("��̽���̼ල���Ĺ������ܱ�");
	m_rc.SetTitle (s);

	m_rc.SetGridContent (0,0,"���");
	m_rc.SetGridContent (0,1,"�������");
	m_rc.SetGridContent (0,2,"��������");
	m_rc.SetGridContent (0,3,"��������");
	m_rc.SetGridContent (0,4,"��������");
	m_rc.SetGridContent (0,5,"����Ч��");

	//////////////////////////////////
	// Left:
	CString sMonitor="";
	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;
		date.Set(pRecord->GetAt (1),pRecord->GetAt (2),pRecord->GetAt (3));
		m_rc.SetGridContent (i+1,0,vtos(i+1));
		m_rc.SetGridContent (i+1,1,date.GetDateString ());
		m_rc.SetGridContent (i+1,2,pRecord->GetAt (4)+pRecord->GetAt (5));
		m_rc.SetGridContent (i+1,3,pRecord->GetAt (6));

		date.Set(pRecord->GetAt (7),pRecord->GetAt (8),pRecord->GetAt (9));
		m_rc.SetGridContent (i+1,4,date.GetDateString ());
		m_rc.SetGridContent (i+1,5,pRecord->GetAt (10));
		s=pRecord->GetAt (11);
		if(!IsEmpty(s))
		{
			sMonitor=s;
		}
	}

	s="ʩ��������"+pDoc->m_sArea +"     ʩ����λ��"+pDoc->m_sServer +pDoc->m_sCrew + "��"
		+"       ʩ����Ŀ��"+pDoc->m_sProjectName ;
	m_rc.SetLeftUpString (s);

	s="פ�Ӽල��"+sMonitor+"                   �Ʊ�"+pDoc->m_sReportCreator ;
	m_rc.SetLeftDownString (s);
	return ;
	
}


void CReportView::CreateReport12()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	CMyDate date;
	int iRecordQty=pDoc->GetRecordQty ();
	if(iRecordQty!=1)
	{
		TRACEERROR("��¼����Ϊ1:"+vtos(iRecordQty));
		return ;
	}
	CStringArray *pRecord=pDoc->GetRecord (0);

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	m_rc.SetGridQty (16,4);

	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s=pDoc->m_sArea +"��������ɼ�ʩ������һ����";
	m_rc.SetTitle (s);
	m_rc.SetLeftUpString ("��ţ�");
	m_rc.SetGridContent (0,0,"�� Ŀ");
	m_rc.SetGridContent (0,1,"�� ��");
	m_rc.SetGridContent (0,2,"�� Ŀ");
	m_rc.SetGridContent (0,3,"�� ��");

	m_rc.SetGridContent (1,0,"��Ԫ�ߴ�");		m_rc.SetGridContent (1,1,pRecord->GetAt (1));
	m_rc.SetGridContent (2,0,"���Ǵ���");		m_rc.SetGridContent (2,1,pRecord->GetAt (2));
	m_rc.SetGridContent (3,0,"�۲�ϵͳ");		m_rc.SetGridContent (3,1,pRecord->GetAt (3));
	m_rc.SetGridContent (4,0,"���յ���");		m_rc.SetGridContent (4,1,pRecord->GetAt (4));
	m_rc.SetGridContent (5,0,"������ʽ");		m_rc.SetGridContent (5,1,pRecord->GetAt (5));
	m_rc.SetGridContent (6,0,"�������");		m_rc.SetGridContent (6,1,pRecord->GetAt (6));
	m_rc.SetGridContent (7,0,"��¼����");		m_rc.SetGridContent (7,1,pRecord->GetAt (7));
	m_rc.SetGridContent (8,0,"��    ��");		m_rc.SetGridContent (8,1,pRecord->GetAt (8));
	m_rc.SetGridContent (9,0,"�� �� ��");		m_rc.SetGridContent (9,1,pRecord->GetAt (9));
	m_rc.SetGridContent (11,0,"�첨���ͺ�");	m_rc.SetGridContent (11,1,pRecord->GetAt (20));
	m_rc.SetGridContent (12,0,"�첨���¾����");m_rc.SetGridContent (12,1,pRecord->GetAt (21));
	m_rc.SetGridContent (13,0,"��Ϸ�ʽ");		m_rc.SetGridContent (13,1,pRecord->GetAt (22));
	m_rc.SetGridContent (14,0,"����Ϸ�ʽ");	m_rc.SetGridContent (14,1,pRecord->GetAt (23));
	m_rc.SetGridContent (15,0,"ǰ������");		m_rc.SetGridContent (15,1,pRecord->GetAt (24));


	m_rc.SetGridContent (1,2,"��    ��");		m_rc.SetGridContent (1,3,pRecord->GetAt (10));
	m_rc.SetGridContent (2,2,"�����߾�");		m_rc.SetGridContent (2,3,pRecord->GetAt (11));
	m_rc.SetGridContent (3,2,"�� �� ��");		m_rc.SetGridContent (3,3,pRecord->GetAt (12));
	m_rc.SetGridContent (4,2,"����������");		m_rc.SetGridContent (4,3,pRecord->GetAt (13));
	m_rc.SetGridContent (5,2,"����λ��");		m_rc.SetGridContent (5,3,pRecord->GetAt (14));
	m_rc.SetGridContent (6,2,"������С�ڼ��");	m_rc.SetGridContent (6,3,pRecord->GetAt (15));
	m_rc.SetGridContent (7,2,"��������ڼ��");	m_rc.SetGridContent (7,3,pRecord->GetAt (16));
	m_rc.SetGridContent (8,2,"����ڼ��");		m_rc.SetGridContent (8,3,pRecord->GetAt (17));
	m_rc.SetGridContent (9,2,"�����ݾ�");		m_rc.SetGridContent (9,3,pRecord->GetAt (18));
	m_rc.SetGridContent (10,2,"��С�ڼ��");	m_rc.SetGridContent (10,3,pRecord->GetAt (19));
	m_rc.SetGridContent (11,2,"�첨������");	m_rc.SetGridContent (11,3,pRecord->GetAt (25));
	m_rc.SetGridContent (12,2,"�����ͺ�");		m_rc.SetGridContent (12,3,pRecord->GetAt (26));
	m_rc.SetGridContent (13,2,"��ϲ���");		m_rc.SetGridContent (13,3,pRecord->GetAt (27));
	m_rc.SetGridContent (14,2,"����ϻ���");	m_rc.SetGridContent (14,3,pRecord->GetAt (28));
	m_rc.SetGridContent (15,2,"��¼�ܶ�");		m_rc.SetGridContent (15,3,pRecord->GetAt (29));

	
	return ;
	
}


//////////////////////////////////////////////////////////
// ������Ҫ������Ա��λ�������
// ��0107������Ҫ������Ա��λ�������  ��13
//////////////////////////////////////////////////////////
void CReportView::CreateReport13()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	CMyDate date;
	int iRecordQty=pDoc->GetRecordQty ();

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	m_rc.SetGridQty (iRecordQty+1,7);

	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s=pDoc->m_sArea +"������Ҫ������Ա��λ�������";
	m_rc.SetTitle (s);
	m_rc.SetLeftUpString ("��ţ�");
	m_rc.SetGridContent (0,0,"��λ����");
	m_rc.SetGridContent (0,1,"��  ��");
	m_rc.SetGridContent (0,2,"ְ  ��");
	m_rc.SetGridContent (0,3,"��  ��");
	m_rc.SetGridContent (0,4,"�Ļ��̶�");
	m_rc.SetGridContent (0,5,"����ʱ��");
	m_rc.SetGridContent (0,6,"��λ���");
	
	//��Ŀ����
	int iStartRow=1;
	SetPersonData(	pDoc,
					2,
					"��Ŀ����",
					iStartRow);

	SetPersonData(	pDoc,
					3,
					"��    ��",
					iStartRow);

	SetPersonData(	pDoc,
					4,
					"��    ��",
					iStartRow);

	SetPersonData(	pDoc,
					5,
					"�� �� ��",
					iStartRow);

	SetPersonData(	pDoc,
					6,
					"HSE �� ��",
					iStartRow);

	SetPersonData(	pDoc,
					7,
					"ʩ���鳤",
					iStartRow);

	SetPersonData(	pDoc,
					8,
					"ʩ��Ա",
					iStartRow);

	SetPersonData(	pDoc,
					9,
					"�����鳤",
					iStartRow);

	SetPersonData(	pDoc,
					10,
					"����Ա",
					iStartRow);

	SetPersonData(	pDoc,
					11,
					"�ֳ������鳤",
					iStartRow);

	SetPersonData(	pDoc,
					12,
					"�ֳ�����Ա",
					iStartRow);

	SetPersonData(	pDoc,
					13,
					"�����鳤",
					iStartRow);

	SetPersonData(	pDoc,
					14,
					"����Ա",
					iStartRow);

	return ;
}

void CReportView::SetPersonData(CReportDoc		*pDoc,
								int				iPostOrder,
								CString			sPostName,
								int				&iStartRow)
{
	CStringArray *pRecord=NULL;
	CString sName;
	CString sPositioned;
	int i;

	CDataBrowseDoc	*pViceDoc=&(pDoc->m_docVice );

	int iStart=iStartRow;
	for(i=0;i<pDoc->GetRecordQty ();i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(IsTrue(pRecord->GetAt(iPostOrder)))
		{
			sName=pRecord->GetAt(1);
			sPositioned=pRecord->GetAt (15);
			SetRowData(sName,sPositioned,pViceDoc,iStartRow);
			iStartRow++;
		}
	}

	m_rc.CombineGrid (iStart,iStartRow-1,0,0);
	m_rc.SetGridContent(iStart,0,sPostName);
}

void CReportView::SetRowData(CString	sName, 
							 CString	sPostioned,
							 CDataBrowseDoc *pDoc,
							 int		iRow)
{
	m_rc.SetGridContent (iRow,1,sName);
	if(IsTrue(sPostioned))
	{
		m_rc.SetGridContent (iRow,6,"��λ");
	}
	else
	{
		m_rc.SetGridContent (iRow,6,"δ��λ");
	}

	CStringArray *pRecord=NULL;
	sName.Trim ();
	CString sNameTag;
	int iRecord=-1;
	for(int i=0;i<pDoc->GetRecordQty();i++)
	{
		pRecord=pDoc->GetRecord(i);
		sNameTag=pRecord->GetAt (0);
		sNameTag.Trim ();
		if(sNameTag==sName)
		{
			iRecord=i;
			break;
		}
	}

	if(iRecord==-1)return;

	//ְ��
	m_rc.SetGridContent (iRow,2,pRecord->GetAt(1));


	// ����
	CReportDoc *pDocReport=(CReportDoc *)GetDocument();
	int iAge=pDocReport->m_iCurrYear-stof(pRecord->GetAt (2));
	m_rc.SetGridContent (iRow,3,vtos(iAge));

	// ѧ��:
	CString sEdu=pRecord->GetAt (3);
	CString s=pRecord->GetAt (4);
	if(!IsEmpty(s))
	{
		sEdu=s;
	}
	s=pRecord->GetAt (5);
	if(!IsEmpty(s))
	{
		sEdu=s;
	}
	m_rc.SetGridContent (iRow,4,sEdu);

	// ����ʱ��:
	int iWorkYear=pDocReport->m_iCurrYear-stof(pRecord->GetAt (6));
	m_rc.SetGridContent (iRow,5,vtos(iWorkYear));

	return;
}

//////////////////////////////////////////
//      ������Ҫ�豸��λ�������
// ��0108������Ҫ�豸��λ�������  ��14
//////////////////////////////////////////
void CReportView::CreateReport14()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	CMyDate date;
	int iRecordQty=pDoc->GetRecordQty ();

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	m_rc.SetGridQty (iRecordQty+1,5);

	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s=pDoc->m_sArea +"������Ҫ�豸��λ�������";
	m_rc.SetTitle (s);
	m_rc.SetLeftUpString ("��ţ�");
	m_rc.SetGridContent (0,0," ��; ");
	m_rc.SetGridContent (0,1,"  �豸����  ");
	m_rc.SetGridContent (0,2,"  �豸�ͺ�  ");
	m_rc.SetGridContent (0,3,"    ����    ");
	m_rc.SetGridContent (0,4,"  ��λ���  ");
	
	//��Ŀ����
	int iStartRow=1;

	int iStart=iStartRow;
	SetInstData(pDoc,1,"����",iStartRow);
	SetInstData(pDoc,2,"�첨��",iStartRow);
	SetInstData(pDoc,3,"�ɼ�վ",iStartRow);
	SetInstData(pDoc,4,"����",iStartRow);
	SetInstData(pDoc,5,"΢��",iStartRow);
	SetInstData(pDoc,6,"GPS",iStartRow);
	SetInstData(pDoc,7,"�����",iStartRow);
	SetInstData(pDoc,8,"��ӡ��",iStartRow);
	SetInstData(pDoc,9,"�ֳ������",iStartRow);

	m_rc.CombineGrid (iStart,iStartRow-1,0,0);
	m_rc.SetGridContent (iStart,0,"��\r��\r��\r��\r��");

	iStart=iStartRow;
	SetInstData(pDoc,10,"���",iStartRow);
	SetInstData(pDoc,11,"�綯�����",iStartRow);
	SetInstData(pDoc,12,"ըҩ��",iStartRow);
	SetInstData(pDoc,13,"�׹ܳ�",iStartRow);
	SetInstData(pDoc,14,"�꾮ˮ�޳�",iStartRow);
	
	m_rc.CombineGrid (iStart,iStartRow-1,0,0);
	m_rc.SetGridContent (iStart,0,"��\r��\r��\r��");
	
	iStart=iStartRow;
	SetInstData(pDoc,15,"����",iStartRow);
	SetInstData(pDoc,16,"��ͳ�",iStartRow);
	SetInstData(pDoc,17,"���߳�",iStartRow);
	SetInstData(pDoc,18,"���߳�",iStartRow);
	SetInstData(pDoc,19,"���ڳ�",iStartRow);
	SetInstData(pDoc,20,"����ˮ�޳�",iStartRow);
	m_rc.CombineGrid (iStart,iStartRow-1,0,0);
	m_rc.SetGridContent (iStart,0,"��\r��");


	iStart=iStartRow;
	SetInstData(pDoc,21,"���ص�̨",iStartRow);
	SetInstData(pDoc,22,"�ֳ�ʽ��̨",iStartRow);
	m_rc.CombineGrid (iStart,iStartRow-1,0,0);
	m_rc.SetGridContent (iStart,0,"");

	return ;

}

void CReportView::SetInstData(	CReportDoc		*pDoc,
								int				iPostOrder,
								CString			sPostName,
								int				&iStartRow)
{
	CStringArray *pRecord=NULL;
	CString sType,sQty,sPositioned;
	int i;

	int iStart=iStartRow;
	for(i=0;i<pDoc->GetRecordQty ();i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(IsTrue(pRecord->GetAt(iPostOrder)))
		{
			sType=pRecord->GetAt(23);
			sQty=pRecord->GetAt(24);
			sPositioned=pRecord->GetAt(25);
			if(IsTrue(sPositioned))
			{
				sPositioned="��λ";
			}
			else
			{
				sPositioned="δ��λ";
			}
			m_rc.SetGridContent(iStartRow,2,sType);
			m_rc.SetGridContent(iStartRow,3,sQty);
			m_rc.SetGridContent(iStartRow,4,sPositioned);

			iStartRow++;
		}
	}

	m_rc.CombineGrid (iStart,iStartRow-1,1,1);
	m_rc.SetGridContent(iStart,1,sPostName);
}

void CReportView::CreateReport15()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j;
	CMyDate date;
	CStringArray *pRecord=NULL;
	int iRecordQty=pDoc->GetRecordQty ();

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	m_rc.SetGridQty (iRecordQty+2,13);
	for(i=0;i<=6;i++)
	{
		m_rc.CombineGrid (0,1,i,i);
	}
	m_rc.CombineGrid (0,0,7,8);
	m_rc.CombineGrid (0,0,9,11);
	m_rc.CombineGrid (0,1,12,12);


	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("%s��ĿҰ��ɼ����鹤���ලͳ�Ʊ�",pDoc->m_sProjectName );
	m_rc.SetTitle (s);	

	m_rc.SetGridContent (0,0,"��\r��");
	m_rc.SetGridContent (0,1,"�����λ��");
	m_rc.SetGridContent (0,2,"������Ŀ");
	m_rc.SetGridContent (0,3,"��������");
	m_rc.SetGridContent (0,4,"ըҩ\r����");
	m_rc.SetGridContent (0,5,"�̶�\r����");
	m_rc.SetGridContent (0,6,"����\rЧ��");
	m_rc.SetGridContent (0,7,"�����");
	m_rc.SetGridContent (1,7,"����");
	m_rc.SetGridContent (1,8,"�����¼");
	m_rc.SetGridContent (0,9,"�����");
	m_rc.SetGridContent (1,9,"����");
	m_rc.SetGridContent (1,10,"�����¼");
	m_rc.SetGridContent (1,11,"����");
	m_rc.SetGridContent (1,12,"��������");

	//////////////////////////////////
	// Left:
	CString sMonitor="";
	CMyDate dateStat;
	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
		if(!pRecord)break;
		
		m_rc.SetGridContent (i+2,0,vtos(i+1));
		
		for(j=1;j<=11;j++)
		{
			m_rc.SetGridContent (i+2,j,pRecord->GetAt (j));
		}

		date.Set(pRecord->GetAt (12),pRecord->GetAt (13),pRecord->GetAt (14));
		m_rc.SetGridContent (i+2,12,date.GetDateString ());

		s=pRecord->GetAt (15);
		if(!IsEmpty(s))
		{
			sMonitor=s;
		}
	}

	s.Format("��ţ�                 ͳ�����ڣ�%d��%d��%d��",
							pDoc->m_iStatYear ,
							pDoc->m_iStatMonth ,
							pDoc->m_iStatDay);

	m_rc.SetLeftUpString (s);

	s.Format ("ʩ����λ��"+pDoc->m_sServer +"  "+pDoc->m_sCrew +"��");

	m_rc.SetRightUpString (s);

	s="פ�Ӽල��"+sMonitor;
	m_rc.SetLeftDownString (s);
	return ;
	
}
