// QCDBView.cpp : CQCDBView ���ʵ��
//

#include "stdafx.h"
#include "QCDB.h"

#include "QCDBDoc.h"
#include "QCDBView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CQCDBView

IMPLEMENT_DYNCREATE(CQCDBView, CView)

BEGIN_MESSAGE_MAP(CQCDBView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CQCDBView ����/����

CQCDBView::CQCDBView()
{
	// TODO: �ڴ˴���ӹ������

}

CQCDBView::~CQCDBView()
{
}

BOOL CQCDBView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ

	return CView::PreCreateWindow(cs);
}

// CQCDBView ����

void CQCDBView::OnDraw(CDC* /*pDC*/)
{
	CQCDBDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CQCDBView ��ӡ

BOOL CQCDBView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CQCDBView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡǰ��Ӷ���ĳ�ʼ��
}

void CQCDBView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡ������������
}


// CQCDBView ���

#ifdef _DEBUG
void CQCDBView::AssertValid() const
{
	CView::AssertValid();
}

void CQCDBView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CQCDBDoc* CQCDBView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CQCDBDoc)));
	return (CQCDBDoc*)m_pDocument;
}
#endif //_DEBUG


// CQCDBView ��Ϣ�������
