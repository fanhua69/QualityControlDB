#include "stdafx.h"
#include "QCDB.h"
#include "MemDC.h"

#include "ReportDoc.h"
#include "ReportView.h"
#include "DlgReportShowProperty.h"
#include "MyDate.h"
#include "MyTime.h"
#include "fhcglobal.h"

///////////////////////////////////////////////
//       ̽��ִ�о���Ѳ�ؼ���¼
//  ��0404ִ�о���Ѳ�ؼ���¼  ��21
///////////////////////////////////////////////
void CReportView::CreateReport21()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,n;
	CMyDate date;
	CStringArray *pRecord=NULL;
	CString sLine;
	
	pRecord=pDoc->GetRecord (0);
	if(!pRecord)
	{
		return;
	}

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	int iRecordQty=pDoc->GetRecordQty ();
	m_rc.SetGridQty (47,8);
	m_rc.CombineGrid (0,0,0,1);
	m_rc.CombineGrid (1,1,0,1);
	m_rc.CombineGrid (0,0,3,7);
	m_rc.CombineGrid (1,1,3,7);

	m_rc.CombineGrid (2,3,0,0);
	m_rc.CombineGrid (2,3,1,2);
	m_rc.CombineGrid (2,2,4,7);


	m_rc.CombineGrid (4,24,0,0);
	m_rc.CombineGrid (25,30,0,0);
	m_rc.CombineGrid (31,42,0,0);

	for(i=4;i<=42;i++)
	{
		m_rc.CombineGrid (i,i,1,2);
	}

	m_rc.CombineGrid (43,43,0,7);
	m_rc.CombineGrid (44,44,0,7);
	m_rc.CombineGrid (45,45,0,7);

	m_rc.CombineGrid (46,46,0,1);
	m_rc.CombineGrid (46,46,2,7);

	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("̽��ִ�о���Ѳ�ؼ���¼" );
	m_rc.SetTitle (s);	


	m_rc.SetGridContent (0,0,"̽��:"+pDoc->m_sProspectArea);
	m_rc.SetGridContent (0,2,"��Ŀ:"+pDoc->m_sProjectName );
	m_rc.SetGridContent (0,4,"���:"+pDoc->m_sReportNumber );

	m_rc.SetGridContent (1,0,"�ֳ��ල:"+pRecord->GetAt (1));

	m_rc.SetGridContent (1,2,"��ͬ��:"+pRecord->GetAt (3));
	m_rc.SetGridContent (1,4,"����:"+pRecord->GetAt (4)+"��"
									+pRecord->GetAt (5)+"��"
									+pRecord->GetAt (6)+"��");

	m_rc.SetGridFormat (0,0,DT_LEFT);
	m_rc.SetGridFormat (0,2,DT_LEFT);
	m_rc.SetGridFormat (0,4,DT_LEFT);
	m_rc.SetGridFormat (1,0,DT_LEFT);
	m_rc.SetGridFormat (1,2,DT_LEFT);
	m_rc.SetGridFormat (1,4,DT_LEFT);


	m_rc.SetGridContent (2,0,"��\rĿ");
	m_rc.SetGridContent (2,1,"��     ��    ��     ��");
	m_rc.SetGridContent (2,3,"��  ��  ��  ��");
	m_rc.SetGridContent (3,3,"��");
	m_rc.SetGridContent (3,4,"��\r��");
	m_rc.SetGridContent (3,5,"һ\r��");
	m_rc.SetGridContent (3,6,"��\r��");
	m_rc.SetGridContent (3,7,"��");


	m_rc.SetGridContent (4,0,"��\r��\r��\r��\r��\r��\r��\r��\r��");
	m_rc.SetGridContent (25,0,"��\r��\r��\r��");
	m_rc.SetGridContent (31,0,"ʩ\r��\r��\r��\r��\r��\r��\��");

	m_rc.SetGridContent (4,1,"�ල�ƻ��Ƿ�Ҫ�󡢰�ʱ��д");
	m_rc.SetGridContent (5,1,"�ල���������Ƿ�Ҫ��չʾ��ִ��");
	m_rc.SetGridContent (6,1,"�ල������־�Ƿ�Ҫ���¼���Ƿ��꾡");
	m_rc.SetGridContent (7,1,"����ù�������Ƿ�Ҫ���¼���Ƿ��꾡");
	m_rc.SetGridContent (8,1,"�ල���������Ƿ�Ҫ���ռ�������");
	m_rc.SetGridContent (9,1,"�������ϼ��ʱ�Ƿ����¹����ۼ�");
	m_rc.SetGridContent (10,1,"�ල����ͳ���Ƿ�׼ȷ��һ��");
	m_rc.SetGridContent (11,1,"�ܱ��Ƿ�Ҫ�󡢰�ʱͳ�Ʋ��ϱ�");
	m_rc.SetGridContent (12,1,"�±��Ƿ�Ҫ�󡢰�ʱͳ�Ʋ��ϱ�");
	m_rc.SetGridContent (13,1,"��־���ܱ����±�������¼����ල����ͳ�Ʊ��Ƿ�һһ��Ӧ");
	m_rc.SetGridContent (14,1,"����¼������֪ͨ���Ƿ�Ҫ��ʹ��");
	m_rc.SetGridContent (15,1,"�ල��������ͳ�Ʒ������Ƿ�Ҫ����д���빤����־�Ƿ��ܶ�Ӧ");
	m_rc.SetGridContent (16,1,"��������չʾ�Ƿ�Ҫ��ִ��");
	m_rc.SetGridContent (17,1,"�ල��鹤���Ƿ����������������Ƿ��ܴﵽͶ�ʷ�Ҫ��");
	m_rc.SetGridContent (18,1,"Ұ������ʱ�շֲ��Ƿ��ѧ���Ƿ�����Ч��ӳʩ��ȫò");
	m_rc.SetGridContent (19,1,"������ʱ����ָ���Ƿ����Ҫ��������Ƿ�Ҫ��ִ��");
	m_rc.SetGridContent (20,1,"��������������豸��������ʱ�Ƿ񳹵ס�ͳ���Ƿ���ȫ");
	m_rc.SetGridContent (21,1,"��鼤�������չ���ʱ�Ƿ�ȷ������������׼");
	m_rc.SetGridContent (22,1,"�Ƿ��о�Ͷ�ʷ��Ͽɵ�ԭʼ��¼���۱�׼");
	m_rc.SetGridContent (23,1,"ʩ�����������صȸı����Ҫ����ʱ�Ƿ���Ͷ�ʷ����������");
	m_rc.SetGridContent (24,1,"�Ƿ���Ͷ�ʷ���ִ�о������Ŀ������ʱ������Ϣ��ͨ");
	m_rc.SetGridContent (25,1,"�Ƿ���ڳԡ��á�����Ҫ��������");
	m_rc.SetGridContent (26,1,"�Ƿ������ʩ����һ������Ͷ�ʷ�����");
	m_rc.SetGridContent (27,1,"�Ƿ�����޹��뿪̽�������");
	m_rc.SetGridContent (28,1,"�Ƿ����˽���񹤡�˽�����������ܰ���ͷ����");
	m_rc.SetGridContent (29,1,"�Ƿ���ڶԳа����쵼��������");
	m_rc.SetGridContent (30,1,"�Ƿ����������������⻯������");
	m_rc.SetGridContent (31,1,"��龭�ල������Ұ�⼤���㣬�Ƿ��Դ��ڲ��ϸ�����");
	m_rc.SetGridContent (32,1,"��龭�ල������Ұ����յ㣬�Ƿ��Դ��ڲ��ϸ�����");
	m_rc.SetGridContent (33,1,"��������־������㴦��ȣ��Ƿ��������");
	m_rc.SetGridContent (34,1,"Ұ���ֳ����50��100��ԭʼ��¼���Ƿ��ܵ������Ҫ��");
	m_rc.SetGridContent (35,1,"����ֳ�ʩ���������ϣ��Ƿ���д׼ȷ����ȫ");
	m_rc.SetGridContent (36,1,"�������鹤�����Ƿ�Ҫ��ʩ���������Ƿ񾭼ල�Ͽ�");
	m_rc.SetGridContent (37,1,"���Ұ�����ⲿλ��������Ƿ���ơ���ͬ��Ҫ��ִ��");
	m_rc.SetGridContent (38,1,"�ֳ�����10���ߵļ첨��������ֵ�Ƿ�ϸ�");
	m_rc.SetGridContent (39,1,"Ҫ���ƾ�������鱬ը���ƾ�������Ƿ�Ҫ��ִ��");
	m_rc.SetGridContent (40,1,"�¾��첨��ʩ��ʱ���첨�����������Ƿ����Ҫ��");
	m_rc.SetGridContent (41,1,"��������Ƿ��������ʩ���������Ƿ�׼ȷ");
	m_rc.SetGridContent (42,1,"��ʩ������Ա�������۲�������ʶ����׼����ʵ���");

	for(i=4;i<=42;i++)
	{
		m_rc.SetGridFormat (i,1,DT_LEFT);
	}


	int iSum[5];
	for(i=0;i<5;i++)
	{
		iSum[i]=0;
	}
	for(i=7;i<=45;i++)
	{
		s=pRecord->GetAt (i);
		s.Trim ().MakeUpper();
		s=s.Left (1);

		if(s=="A"||s=="1")
		{
			m_rc.SetGridContent (i-3,3,"��");
			iSum[0]++;
		}
		else if(s=="B"||s=="2")
		{
			m_rc.SetGridContent (i-3,4,"��");
			iSum[1]++;
		}
		else if(s=="C"||s=="3")
		{
			m_rc.SetGridContent (i-3,5,"��");
			iSum[2]++;
		}
		else if(s=="D"||s=="4")
		{
			m_rc.SetGridContent (i-3,6,"��");
			iSum[3]++;
		}
		else
		{
			m_rc.SetGridContent (i-3,7,"��");
			iSum[4]++;
		}
	}

	s=pRecord->GetAt (46);

	CString ss;
	ss.Format ("���μ���������������%d�����Ϻ�%d����һ��%d�����ϲ�%d������%d����",
		iSum[0],iSum[1],iSum[2],iSum[3],iSum[4]);
	ss+="\r"+s;
	m_rc.SetGridContent (43,0,ss);
	m_rc.SetGridFormat (43,0,DT_LEFT);


	s=pRecord->GetAt (47);
	s.Trim().MakeUpper ();
	if(s=="A"||s=="1")
	{
		s="����Ŀפ�Ӽල�Ƿ��ܼ���ʤ�μල������  ����     ����������ѵ����    ������";
	}
	else if(s=="B"||s=="2")
	{
		s="����Ŀפ�Ӽල�Ƿ��ܼ���ʤ�μල������  ����     ����������ѵ����    ������";
	}
	else
	{
		s="����Ŀפ�Ӽල�Ƿ��ܼ���ʤ�μල������  ����     ����������ѵ����    ������";
	}
	m_rc.SetGridContent (44,0,s);
	m_rc.SetGridFormat (44,0,DT_LEFT);


	s=pRecord->GetAt (48);
	m_rc.SetGridContent (45,0,"�Ը���Ŀ�²��ල����Ҫ��\r"+s);
	m_rc.SetGridFormat (45,0,DT_LEFT);

	s=pRecord->GetAt (1);
	m_rc.SetGridContent (46,0,"�ֳ��ලǩ�֣�\r      "+s+"\r          ��   ��   ��");
	m_rc.SetGridFormat (46,0,DT_LEFT);
	
	s=pRecord->GetAt (2);
	m_rc.SetGridContent (46,2,"̽��ִ�о���\r      "+s+"\r          ��   ��   ��");
	m_rc.SetGridFormat (46,2,DT_LEFT);


	s.Format (" ��  �ţ�");
	m_rc.SetLeftUpString (s);

	return ;

}

/////////////////////////////////////////////////////////
//       ��Ŀ������ִ�о���Ѳ�ؼ���¼
//   ��0405��Ŀ������ִ�о���Ѳ�ؼ���¼  ��22
/////////////////////////////////////////////////////////
void CReportView::CreateReport22()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,n;
	CMyDate date;
	CStringArray *pRecord=NULL;
	CString sLine;
	
	pRecord=pDoc->GetRecord (0);
	if(!pRecord)
	{
		return;
	}

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	int iRecordQty=pDoc->GetRecordQty ();
	m_rc.SetGridQty (29,9);
	m_rc.CombineGrid (0,0,0,1);
	m_rc.CombineGrid (0,0,3,5);
	m_rc.CombineGrid (0,0,6,8);

	m_rc.CombineGrid (1,2,0,0);
	m_rc.CombineGrid (1,2,1,3);
	m_rc.CombineGrid (1,1,4,5);
	m_rc.CombineGrid (1,1,6,8);

	m_rc.CombineGrid (3,22,0,0);
	m_rc.CombineGrid (23,27,0,0);
	m_rc.CombineGrid (28,28,0,2);
	m_rc.CombineGrid (28,28,3,8);

	for(i=3;i<=27;i++)
	{
		m_rc.CombineGrid (i,i,1,3);
	}

	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("��Ŀ������ִ�о���Ѳ�ؼ���¼" );
	m_rc.SetTitle (s);	


	m_rc.SetGridContent (0,0,"̽��:"+pDoc->m_sProspectArea);
	m_rc.SetGridContent (0,2,"ִ�о���:"+pRecord->GetAt (3));
	m_rc.SetGridContent (0,3,"����:"+pRecord->GetAt (4)+"��"
									+pRecord->GetAt (5)+"��"
									+pRecord->GetAt (6)+"��");

	m_rc.SetGridContent (0,6,"���:"+pDoc->m_sReportNumber );

	m_rc.SetGridContent (1,0,"��\rĿ");
	m_rc.SetGridContent (1,1,"��     ��    ��     ��");
	m_rc.SetGridContent (1,4,"�����");
	m_rc.SetGridContent (1,6,"�������");
	m_rc.SetGridContent (2,4,"��");
	m_rc.SetGridContent (2,5,"��");
	m_rc.SetGridContent (2,6,"��");
	m_rc.SetGridContent (2,7,"һ��");
	m_rc.SetGridContent (2,8,"��");

	m_rc.SetGridContent (3,0,"��\r��\r��\r��\r��\r��\r��\r��\r��");
	m_rc.SetGridContent (23,0,"��\rΪ\r��\r��");
	m_rc.SetGridContent (28,0,"̽��ִ�о���ǩ�֣�\r       "
						+pRecord->GetAt (3)
						+"\r        ��    ��    ��");

	m_rc.SetGridContent (28,3,"��Ŀ������\r       "
						+pRecord->GetAt (2)
						+"\r        ��    ��    ��");

	
	s.Format ("��  �ţ�");
	m_rc.SetLeftUpString (s);

	m_rc.SetGridFormat (0,0,DT_LEFT);
	m_rc.SetGridFormat (0,2,DT_LEFT);
	m_rc.SetGridFormat (0,3,DT_LEFT);
	m_rc.SetGridFormat (0,6,DT_LEFT);
	m_rc.SetGridFormat (28,0,DT_LEFT);
	m_rc.SetGridFormat (28,3,DT_LEFT);

	m_rc.SetGridContent (3,1,"�Ƿ�Ҫ�����̽��������Ŀ�ල�����ƻ�����ʽ�Ƿ�ͳһ");
	m_rc.SetGridContent (4,1,"̽�����Ƿ�ͳһ�ල��������");
	m_rc.SetGridContent (5,1,"̽�����Ƿ�ͳһ�ල�ܱ����±��ĸ�ʽ������");
	m_rc.SetGridContent (6,1,"̽�����Ƿ�ͳһ�ල��¼��ʽ");
	m_rc.SetGridContent (7,1,"̽�����Ƿ�ͳһ�ලչʾ���ϸ�ʽ");
	m_rc.SetGridContent (8,1,"̽�����Ƿ�淶�˼ල����ͳ�Ʊ��");
	m_rc.SetGridContent (9,1,"̽�����Ƿ�ͳһ�淶�˼ල�������ݡ���ʽ�������ʽ");
	m_rc.SetGridContent (10,1,"������������Ŀ���Ƿ�Ҫ�����E-mail��ʽ�㱨");
	m_rc.SetGridContent (11,1,"��Ͷ�ʷ��й��쵼�Ƿ�������ͨ�˼ල������ʶ");
	m_rc.SetGridContent (12,1,"�Ƿ���Ͷ�ʷ������˹�˾���ļල��������˼·");
	m_rc.SetGridContent (13,1,"�Ƿ��˽�Ͷ�ʷ��Լල������Ҫ����ص�");
	m_rc.SetGridContent (14,1,"�Ƿ��Ͷ�ʷ�������Ҫ�󴫴ﵽ����Ŀ�ල��Ա");
	m_rc.SetGridContent (15,1,"�Ƿ��˽����Ŀ���ල������̬���");
	m_rc.SetGridContent (16,1,"�Ƿ�Ҫ��Ѳ�ؼ���˸���Ŀ�ල����");
	m_rc.SetGridContent (17,1,"Ѳ�ؼ�������Ƿ���ȫ���淶");
	m_rc.SetGridContent (18,1,"�Ƿ�Ҫ��Լ���֧�ֹ��������˰��ź�ʵʩ");
	m_rc.SetGridContent (19,1,"����֧���Ƿ�ﵽ��Ӧ�е�Ч��");
	m_rc.SetGridContent (20,1,"������¼�Ƿ���ȫ��׼ȷ");
	m_rc.SetGridContent (21,1,"�Ƿ�ʱ��Ͷ�ʷ��й��쵼������Ϣ��ͨ");
	m_rc.SetGridContent (22,1,"�Ƿ�ʱ����Ŀ����������Ϣ��ͨ");
	m_rc.SetGridContent (23,1,"����ʽ�ʹ���Ƿ񾭹���ʾ");
	m_rc.SetGridContent (24,1,"�Ƿ�ע�سɱ���������");
	m_rc.SetGridContent (25,1,"����̬���Ƿ����桢��������и��");
	m_rc.SetGridContent (26,1,"�Ƿ��ܴ����Կ�չ�ල������");
	m_rc.SetGridContent (27,1,"������������Ƿ񲻸����⻯");

	for(i=3;i<=27;i++)
	{
		m_rc.SetGridFormat (i,1,DT_LEFT);
	}

	int iRow=0;
	for(i=7;i<=55;i+=2)
	{
		s=pRecord->GetAt (i);
		s.Trim ().MakeUpper();
		s=s.Left (1);


		iRow=(i-7)/2+3;
		if(IsTrue(s))
		{
			m_rc.SetGridContent (iRow,4,"��");
		}
		else
		{
			m_rc.SetGridContent (iRow,5,"��");
		}

		s=pRecord->GetAt (i+1);
		s.Trim ().MakeUpper();
		s=s.Left (1);

		if (s=="A"||s=="1")
		{
			m_rc.SetGridContent (iRow,6,"��");
		}
		else if(s=="B"||s=="2")
		{
			m_rc.SetGridContent (iRow,7,"һ��");
		}
		else
		{
			m_rc.SetGridContent (iRow,8,"��");
		}
	}

	return ;
}

/////////////////////////////////////////////////////////////
//    ��Ŀ�������ֳ��ලѲ�ؼ���¼
//   ��0406��Ŀ�������ֳ��ලѲ�ؼ���¼  ��23
/////////////////////////////////////////////////////////////
void CReportView::CreateReport23()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,n;
	CMyDate date;
	CStringArray *pRecord=NULL;
	CString sLine;
	
	pRecord=pDoc->GetRecord (0);
	if(!pRecord)
	{
		return;
	}

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	int iRecordQty=pDoc->GetRecordQty ();
	m_rc.SetGridQty (32,9);
	m_rc.CombineGrid (0,0,0,1);
	m_rc.CombineGrid (0,0,2,3);
	m_rc.CombineGrid (0,0,4,8);

	m_rc.CombineGrid (1,1,0,1);
	m_rc.CombineGrid (1,1,2,3);
	m_rc.CombineGrid (1,1,4,8);
	
	m_rc.CombineGrid (2,3,0,0);
	m_rc.CombineGrid (2,3,1,3);
	m_rc.CombineGrid (2,2,4,5);
	m_rc.CombineGrid (2,2,6,8);
	
	
	m_rc.CombineGrid (4,24,0,0);
	m_rc.CombineGrid (25,30,0,0);
	m_rc.CombineGrid (31,31,0,2);
	m_rc.CombineGrid (31,31,3,8);

	for(i=4;i<=30;i++)
	{
		m_rc.CombineGrid (i,i,1,3);
	}

	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("��Ŀ�������ֳ��ලѲ�ؼ���¼" );
	m_rc.SetTitle (s);	


	m_rc.SetGridContent (0,0,"̽��:"+pDoc->m_sProspectArea);
	m_rc.SetGridContent (0,2,"��Ŀ:"+pDoc->m_sProjectName );
	m_rc.SetGridContent (0,4,"���:"+pDoc->m_sReportNumber );

	m_rc.SetGridContent (1,0,"�ֳ��ල:"+pRecord->GetAt (2));

	m_rc.SetGridContent (1,2,"��ͬ��:"+pRecord->GetAt (3));
	m_rc.SetGridContent (1,4,"����:"+pRecord->GetAt (4)+"��"+pRecord->GetAt (5)+"��"+pRecord->GetAt (6)+"��");


	m_rc.SetGridContent (2,0,"��\rĿ",CW_FIXEDBYCONTENT);
	m_rc.SetGridContent (2,1,"��     ��    ��     ��");
	m_rc.SetGridContent (2,4,"�����");
	m_rc.SetGridContent (2,6,"�������");

	m_rc.SetGridContent (3,4,"��");
	m_rc.SetGridContent (3,5,"��");
	m_rc.SetGridContent (3,6,"��");
	m_rc.SetGridContent (3,7,"һ��");
	m_rc.SetGridContent (3,8,"��");

	m_rc.SetGridContent (4,0,"��\r��\r��\r��\r��\r��\r��\r��\r��\r��",CW_FIXEDBYCONTENT);

	m_rc.SetGridContent (25,0,"ʩ\r��\r��\r��",CW_FIXEDBYCONTENT);
	m_rc.SetGridContent (31,0,"�ֳ��ලǩ�֣�\r        "
						+pRecord->GetAt (2)
						+CString("\r        ��    ��    ��"));

	m_rc.SetGridContent (31,3,"��Ŀ������\r       "
						+pRecord->GetAt (1)
						+"\r        ��    ��    ��");

	
	s.Format ("��  �ţ�");
	m_rc.SetLeftUpString (s);

	m_rc.SetGridFormat (0,0,DT_LEFT);
	m_rc.SetGridFormat (0,2,DT_LEFT);
	m_rc.SetGridFormat (0,4,DT_LEFT);
	m_rc.SetGridFormat (1,0,DT_LEFT);
	m_rc.SetGridFormat (1,2,DT_LEFT);
	m_rc.SetGridFormat (1,4,DT_LEFT);
	m_rc.SetGridFormat (31,0,DT_LEFT);
	m_rc.SetGridFormat (31,3,DT_LEFT);

	m_rc.SetGridContent (4,1,"�ල�ƻ��Ƿ�ִ�о����������Ƿ�̽��ͳһ��ʽ");
	m_rc.SetGridContent (5,1,"�Ƿ�̽��ͳһ�ļල��������չʾ��ִ��");
	m_rc.SetGridContent (6,1,"�Ƿ�Ҫ���¼�ල������־");
	m_rc.SetGridContent (7,1,"����ù�������Ƿ�ͳһ��ʽ��Ҫ����д");
	m_rc.SetGridContent (8,1,"�Ƿ�Ҫ���ռ�������ල��������");
	m_rc.SetGridContent (9,1,"�ܱ��Ƿ�Ҫ�󡢰�ʱͳ�Ʋ��ϱ�");
	m_rc.SetGridContent (10,1,"�±��Ƿ�Ҫ�󡢰�ʱͳ�Ʋ��ϱ�");
	m_rc.SetGridContent (11,1,"��־���ܱ����±�������¼��ͳ�Ʊ���Ƿ����໥��Ӧ");
	m_rc.SetGridContent (12,1,"����¼������֪ͨ���Ƿ�Ҫ��ʹ��");
	m_rc.SetGridContent (13,1,"�Ƿ�������д�ල��������ͳ�Ʒ�����");
	m_rc.SetGridContent (14,1,"��������չʾ�Ƿ����̽��ͳһ�淶");
	m_rc.SetGridContent (15,1,"ʩ�����������صȸı����Ҫ����ʱ�Ƿ���Ͷ�ʷ����������");
	m_rc.SetGridContent (16,1,"�Ƿ��о�Ͷ�ʷ��Ͽɵļ��������չ�������������׼");
	m_rc.SetGridContent (17,1,"�Ƿ��о�Ͷ�ʷ��Ͽɵ�ԭʼ��¼���۱�׼");
	m_rc.SetGridContent (18,1,"�Ƿ���Ͷ�ʷ���ִ�о������Ŀ������ʱ������Ϣ��ͨ");
	m_rc.SetGridContent (19,1,"����С���㱨���Ƿ�ץס�ص㣬�����Ƿ�����");
	m_rc.SetGridContent (20,1,"�Լ׷��ܼ��ִ�о����������Ҫ���Ƿ���ء��������ʵ");
	m_rc.SetGridContent (21,1,"��ʩ�����˽⣬�Ƿ������ල����������Υ��");
	m_rc.SetGridContent (22,1,"��Ͷ�ʷ��˽⣬�Ƿ������Գа����쵼��������");
	m_rc.SetGridContent (23,1,"��ʩ�����˽⣬�Ƿ�������������������⻯");
	m_rc.SetGridContent (24,1,"��龭�ල������Ұ�⼤���㣬��֤����Ƿ����");
	m_rc.SetGridContent (25,1,"��龭�ල������Ұ����յ㣬��֤����Ƿ����");
	m_rc.SetGridContent (26,1,"��������־������㴦��ȣ���֤����Ƿ����");
	m_rc.SetGridContent (27,1,"�ֳ���鲿��ԭʼ��¼���Ƿ��ܴﵽ���Ҫ��");
	m_rc.SetGridContent (28,1,"���Ұ�����ⲿλ��������Ƿ���ơ���ͬ��Ҫ��ִ��");
	m_rc.SetGridContent (29,1,"�ֳ����첨������ֵ���Ƿ�ϸ�");
	m_rc.SetGridContent (30,1,"�Ƿ񾭳���ʩ������Ա����������ʶ����׼����ʵ���");


	for(i=4;i<=30;i++)
	{
		m_rc.SetGridFormat (i,1,DT_LEFT);
	}

	int iRow=0;
	for(i=7;i<=60;i+=2)
	{
		s=pRecord->GetAt (i);
		s.Trim ().MakeUpper();
		s=s.Left (1);

		iRow=(i-7)/2+4;
		if(IsTrue(s))
		{
			m_rc.SetGridContent (iRow,4,"��");
		}
		else
		{
			m_rc.SetGridContent (iRow,5,"��");
		}

		s=pRecord->GetAt (i+1);
		s.Trim ().MakeUpper();
		s=s.Left (1);

		if (s=="A"||s=="1")
		{
			m_rc.SetGridContent (iRow,6,"��");
		}
		else if(s=="B"||s=="2")
		{
			m_rc.SetGridContent (iRow,7,"һ��");
		}
		else
		{
			m_rc.SetGridContent (iRow,8,"��");
		}
	}

	return ;

}

/////////////////////////////////////////////////////
// ��̽������Ŀ���У��գ�ʱЧͳ�Ʊ�
// ��0301�������ձ�  ��24
/////////////////////////////////////////////////////
void CReportView::CreateReport24()
{
	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,n;
	CMyDate date;
	CStringArray *pRecord=NULL;
	CString sLine;

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	int iRecordQty=pDoc->GetRecordQty ();
	m_rc.SetGridQty (iRecordQty+2,18);

	for(i=0;i<=6;i++)
	{
		m_rc.CombineGrid (0,1,i,i);
	}
	for(i=14;i<=17;i++)
	{
		m_rc.CombineGrid (0,1,i,i);
	}
	m_rc.CombineGrid (0,0,7,13);

	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("%s��̽������Ŀ���У��գ�ʱЧͳ�Ʊ�",pDoc->m_sProjectName  );
	m_rc.SetTitle (s);	

    s="̽����"+pDoc->m_sProspectArea +"         Ͷ�ʷ���"
		      +pDoc->m_sClient +"          ��ҵ����"
			  +pDoc->m_sServer +pDoc->m_sCrew +"��";
    m_rc.SetLeftUpString (s);

    s="    ҳ ��   ҳ";
    m_rc.SetRightUpString (s);


	m_rc.SetGridContent (0,0,"����");
	m_rc.SetGridContent (0,1,"�뿪\rפ��\rʱ��");
	m_rc.SetGridContent (0,2,"����\r����\rʱ��");
	m_rc.SetGridContent (0,3,"����\r����\rʱ��");

	m_rc.SetGridContent (0,4,"����\r    \rʱ��");
	m_rc.SetGridContent (0,5,"ĩ��\r    \rʱ��");
	m_rc.SetGridContent (0,6,"��ĩ\r��ʱ\r���");
	m_rc.SetGridContent (0,7,"Ӱ �� ʩ �� ʱ �� ͳ ��");
	m_rc.SetGridContent (1,7,"���\r����\rʱ��");
	m_rc.SetGridContent (1,8,"����\r����\rӰ��");
	m_rc.SetGridContent (1,9,"�豸\r����\rӰ��");
	m_rc.SetGridContent (1,10,"����\r����\rӰ��");
	m_rc.SetGridContent (1,11,"��Ȼ\r����\rӰ��");
	m_rc.SetGridContent (1,12,"�ط�\r��ϵ\rӰ��");
	m_rc.SetGridContent (1,13,"����\r����\rӰ��");
	m_rc.SetGridContent (0,14,"ʵ��\r����\rʱ��");
	m_rc.SetGridContent (0,15,"ʩ��\r����");
	m_rc.SetGridContent (0,16,"����\r���");
	m_rc.SetGridContent (0,17,"��ע");
	
    int iShotSum=0,iShot=0;
    CMyTime time, time1,time2;
	CStringArray arrayMonitor;
	
	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
        date.Set(pRecord->GetAt (4),pRecord->GetAt (5),pRecord->GetAt (6));
	    m_rc.SetGridContent (i+2,0,date.GetDateString ());

        time.SetTimeString (pRecord->GetAt (7));
	    m_rc.SetGridContent (i+2,1,time.GetTimeString ());

        time.SetTimeString (pRecord->GetAt (8));
	    m_rc.SetGridContent (i+2,2,time.GetTimeString ());

        time.SetTimeString (pRecord->GetAt (9));
	    m_rc.SetGridContent (i+2,3,time.GetTimeString ());

        time1.SetTimeString (pRecord->GetAt (10));
	    m_rc.SetGridContent (i+2,4,time1.GetTimeString ());

        time2.SetTimeString (pRecord->GetAt (11));
	    m_rc.SetGridContent (i+2,5,time2.GetTimeString ());

		time=time2-time1;
	    m_rc.SetGridContent (i+2,6,time.GetTimeString ());


		for(j=7;j<=14;j++)
		{
			time.SetTimeString (pRecord->GetAt (5+j));
			m_rc.SetGridContent (i+2,j,time.GetTimeString ());
		}

		// ����Ŀ
		iShotSum=0;
		for(j=22;j<=42;j++)
		{
			iShot=stof(pRecord->GetAt (j));
			iShotSum+=iShot;
		}
		m_rc.SetGridContent (i+2,15,vtos(iShotSum));

		//�������
		m_rc.SetGridContent (i+2,16,pRecord->GetAt (20));

		//��ע
		m_rc.SetGridContent (i+2,17,pRecord->GetAt (21));

		// פ�Ӽල
		AddMonitor(arrayMonitor,pRecord->GetAt (43));
	}

	m_rc.SetLeftDownString ("פ�Ӽල:"+GetMonitorString(arrayMonitor));
	return ;
}

///////////////////////////////////////////////////////////
//��̽������Ŀ      ��ȣ��£�ʱЧ������
//��0301�������ձ�  ��25
///////////////////////////////////////////////////////////
void CReportView::CreateReport25()
{
	int iProjectDesignShot=0;

	CReportDoc *pDoc=(CReportDoc *)GetDocument();
	int i,j,n;
	CMyDate date;
	CStringArray *pRecord=NULL;
	CString sLine;

	CMyDate dateStart,dateEnd;
	dateStart.Set(pDoc->m_iStartYear ,pDoc->m_iStartMonth,pDoc->m_iStartDay );
	dateEnd.Set(pDoc->m_iEndYear ,pDoc->m_iEndMonth,pDoc->m_iEndDay );

	dateStart.SetType(pDoc->m_eMonthType);
	if(pDoc->m_eMonthType == MT_STATISTICS)
	{
		dateStart.IncreaseMonth ();
	}

	int iMonthQty=dateEnd.MonthFrom (dateStart)+1;
	CMonthStat *pMonthStat=new CMonthStat[iMonthQty];
	CMyDate month=dateStart;
	month.DecreaseMonth ();
	for(i=0;i<iMonthQty;i++)
	{
		month.IncreaseMonth ();
		pMonthStat[i].dateMonth =month;
		pMonthStat[i].dateMonth.GetMonthDate (	pMonthStat[i].dateStart ,
												pMonthStat[i].dateEnd);

		pMonthStat[i].dateStartWork= month;
		pMonthStat[i].dateStartWork.SetDay (31);
		pMonthStat[i].dateEndWork= month;
		pMonthStat[i].dateEndWork.DecreaseMonth ();
		pMonthStat[i].dateEndWork.SetDay (1);

		pMonthStat[i].iNaturalDay = pMonthStat[i].dateEnd .DayFrom (pMonthStat[i].dateStart)+1;
		pMonthStat[i].iMinShot = 99999;
		pMonthStat[i].iMaxShot = 0;
	}

	/////////////////////////////////////////////////
	// �������
	/////////////////////////////////////////////////
	int iRecordQty=pDoc->GetRecordQty ();
	m_rc.SetGridQty (iMonthQty+2,18);
	m_rc.CombineGrid (iMonthQty+1,iMonthQty+1,0,2);

	///////////////////////////////////////////////////////////
	// ��������
	///////////////////////////////////////////////////////////
	CString s;
	s.Format ("%s��̽������Ŀ%d��ȣ��£�ʱЧ������",pDoc->m_sProjectName, dateEnd.GetYear () );
	m_rc.SetTitle (s);	

    s="̽����"+pDoc->m_sProspectArea +"         Ͷ�ʷ���"
		      +pDoc->m_sClient +"          ��ҵ����"
			  +pDoc->m_sServer +pDoc->m_sCrew +"��";
    m_rc.SetLeftUpString (s);

	m_rc.SetGridContent (0,0,"ͳ��\r����");
	m_rc.SetGridContent (0,1,"����\r����");
	m_rc.SetGridContent (0,2,"�չ�\r����");
	m_rc.SetGridContent (0,3,"��Ŀ\r���\r����");

	m_rc.SetGridContent (0,4,"����\r���\r����");
	m_rc.SetGridContent (0,5,"���\r�ʣ�");
	m_rc.SetGridContent (0,6,"����\r��Ȼ\r����");
	m_rc.SetGridContent (0,7,"����\rʩ��\r����");
	m_rc.SetGridContent (0,8,"����\r����\r����");
	m_rc.SetGridContent (0,9,"����\r��Ȼ\rͣ��");
	m_rc.SetGridContent (0,10,"����\r����\rͣ��");
	m_rc.SetGridContent (0,11,"����\r�꾮\r����");
	m_rc.SetGridContent (0,12,"��С\r����\r����");
	m_rc.SetGridContent (0,13,"��΢\r�⾮\r����");
	m_rc.SetGridContent (0,14,"����\r���\r����");
	m_rc.SetGridContent (0,15,"����\r���\r����");
	m_rc.SetGridContent (0,16,"����\rƽ��\r��Ч");
	m_rc.SetGridContent (0,17,"��ע");
	m_rc.SetGridContent (iMonthQty+1,0,"��  Ŀ  ��  ��");
	
    int iShotSum=0,iShot=0;
	CStringArray arrayMonitor;
	
	for(i=0;i<iRecordQty;i++)
	{
		pRecord=pDoc->GetRecord (i);
        date.Set(pRecord->GetAt (4),pRecord->GetAt (5),pRecord->GetAt (6));

		// ����Ŀ
		iShotSum=0;
		for(j=9;j<=18;j++)
		{
			iShot=stof(pRecord->GetAt (j));
			iShotSum+=iShot;
		}
		for(j=29;j<=38;j++)
		{
			iShot=stof(pRecord->GetAt (j));
			iShotSum+=iShot;
		}

		for(j=0;j<iMonthQty;j++)
		{
			if(date<pMonthStat[j].dateStart||date>pMonthStat[j].dateEnd)continue;

			if(iShotSum!=0)
			{
				if(date<pMonthStat[j].dateStartWork)
				{
					pMonthStat[j].dateStartWork=date;
				}
				if(date>pMonthStat[j].dateEndWork)
				{
					pMonthStat[j].dateEndWork=date;
				}
			}

			pMonthStat[j].iFinishedShot += iShotSum;

			if(IsTrue(pRecord->GetAt (21)))
			{
				pMonthStat[j].iWorkDay++;
			}

			if(IsTrue(pRecord->GetAt (22)))
			{
				pMonthStat[j].iCheckDay ++;
			}

			if(IsTrue(pRecord->GetAt (23)))
			{
				pMonthStat[j].iNaturalStandByDay ++;
			}

			if(IsTrue(pRecord->GetAt (24)))
			{
				pMonthStat[j].iOtherStandByDay ++;
			}

			pMonthStat[j].fDrillDepth		+=stof(pRecord->GetAt (25));
			pMonthStat[j].iRefQty			+=stof(pRecord->GetAt (26));
			pMonthStat[j].iMicroWellLogQty	+=stof(pRecord->GetAt (27));

			if(iShotSum!=0&&iShotSum>pMonthStat[j].iMaxShot )
			{
				pMonthStat[j].iMaxShot=iShotSum;
			}

			if(iShotSum!=0&&iShotSum<pMonthStat[j].iMinShot )
			{
				pMonthStat[j].iMinShot=iShotSum;
			}

			//��ע
			s=pRecord->GetAt (28);
			if(s!="NULL")
			{
				pMonthStat[j].sNote += s;
			}
		}

		// פ�Ӽල
		AddMonitor(arrayMonitor,pRecord->GetAt (2));
	}

	int iProjectShotQty=stof(pDoc->m_s2DDesiShotQty );
	if(pDoc->m_bIs3D )
	{
		iProjectShotQty=stof(pDoc->m_s3DDesiShotQty );	
	}

	// д��ÿ��������
	for(i=0;i<iMonthQty;i++)
	{
		s.Format("%d��%d��",pMonthStat[i].dateMonth .GetYear (),pMonthStat[i].dateMonth .GetMonth());
		m_rc.SetGridContent (i+1,0,s);

		if(pMonthStat[i].dateEndWork <pMonthStat[i].dateStartWork )continue;
		m_rc.SetGridContent (i+1,1,pMonthStat[i].dateStartWork.GetMonthDayString());
		m_rc.SetGridContent (i+1,2,pMonthStat[i].dateEndWork.GetMonthDayString());
		m_rc.SetGridContent (i+1,3,vtos(iProjectShotQty));

		m_rc.SetGridContent (i+1,4,vtos(pMonthStat[i].iFinishedShot ));
		m_rc.SetGridContent (i+1,5,vtos(pMonthStat[i].iFinishedShot*1.0/iProjectShotQty*100,2));
		m_rc.SetGridContent (i+1,6,vtos(pMonthStat[i].iNaturalDay));
		m_rc.SetGridContent (i+1,7,vtos(pMonthStat[i].iWorkDay ));
		m_rc.SetGridContent (i+1,8,vtos(pMonthStat[i].iCheckDay ));
		m_rc.SetGridContent (i+1,9,vtos(pMonthStat[i].iNaturalStandByDay ));
		m_rc.SetGridContent (i+1,10,vtos(pMonthStat[i].iOtherStandByDay ));
		m_rc.SetGridContent (i+1,11,vtos(pMonthStat[i].fDrillDepth ,1));
		m_rc.SetGridContent (i+1,12,vtos(pMonthStat[i].iRefQty ));
		m_rc.SetGridContent (i+1,13,vtos(pMonthStat[i].iMicroWellLogQty ));
		m_rc.SetGridContent (i+1,14,vtos(pMonthStat[i].iMaxShot ));
		m_rc.SetGridContent (i+1,15,vtos(pMonthStat[i].iMinShot ));
		m_rc.SetGridContent (i+1,16,vtos(pMonthStat[i].iFinishedShot *1.0/pMonthStat[i].iNaturalDay,2));
		m_rc.SetGridContent (i+1,17,pMonthStat[i].sNote);
	}

	// ��Ŀ�ϼƣ�
	CMonthStat projectSum;
	projectSum.iMaxShot =-1000;
	projectSum.iMinShot =999999;
	for(i=0;i<iMonthQty;i++)
	{
		if(pMonthStat[i].dateEndWork <pMonthStat[i].dateStartWork )continue;
		projectSum.iFinishedShot +=pMonthStat[i].iFinishedShot ;
		projectSum.iNaturalDay +=pMonthStat[i].iNaturalDay ;
		projectSum.iWorkDay +=pMonthStat[i].iWorkDay ;
		projectSum.iCheckDay +=pMonthStat[i].iCheckDay ;
		projectSum.iNaturalStandByDay +=pMonthStat[i].iNaturalStandByDay ;
		projectSum.iOtherStandByDay +=pMonthStat[i].iOtherStandByDay ;
		projectSum.fDrillDepth +=pMonthStat[i].fDrillDepth ;
		projectSum.iRefQty +=pMonthStat[i].iRefQty ;
		projectSum.iMicroWellLogQty +=pMonthStat[i].iMicroWellLogQty ;

		if(pMonthStat[i].iMaxShot > projectSum.iMaxShot)
		{
			projectSum.iMaxShot=pMonthStat[i].iMaxShot;
		}

		if(pMonthStat[i].iMinShot < projectSum.iMinShot)
		{
			projectSum.iMinShot=pMonthStat[i].iMinShot;
		}
	}

	int iRow=iMonthQty+1;
	m_rc.SetGridContent (iRow,3,vtos(iProjectShotQty));
	m_rc.SetGridContent (iRow,4,vtos(projectSum.iFinishedShot ));
	m_rc.SetGridContent (iRow,5,vtos(projectSum.iFinishedShot*1.0/iProjectShotQty*100,2));
	m_rc.SetGridContent (iRow,6,vtos(projectSum.iNaturalDay));
	m_rc.SetGridContent (iRow,7,vtos(projectSum.iWorkDay ));
	m_rc.SetGridContent (iRow,8,vtos(projectSum.iCheckDay ));
	m_rc.SetGridContent (iRow,9,vtos(projectSum.iNaturalStandByDay ));
	m_rc.SetGridContent (iRow,10,vtos(projectSum.iOtherStandByDay ));
	m_rc.SetGridContent (iRow,11,vtos(projectSum.fDrillDepth ,1));
	m_rc.SetGridContent (iRow,12,vtos(projectSum.iRefQty ));
	m_rc.SetGridContent (iRow,13,vtos(projectSum.iMicroWellLogQty ));
	m_rc.SetGridContent (iRow,14,vtos(projectSum.iMaxShot ));
	m_rc.SetGridContent (iRow,15,vtos(projectSum.iMinShot ));
	m_rc.SetGridContent (iRow,16,vtos(projectSum.iFinishedShot *1.0/projectSum.iNaturalDay,2));


	m_rc.SetLeftDownString ("פ�Ӽල:"+GetMonitorString(arrayMonitor));

	delete []pMonthStat;

	return ;
}
