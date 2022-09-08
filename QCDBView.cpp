// QCDBView.cpp : CQCDBView 类的实现
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CQCDBView 构造/析构

CQCDBView::CQCDBView()
{
	// TODO: 在此处添加构造代码

}

CQCDBView::~CQCDBView()
{
}

BOOL CQCDBView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	return CView::PreCreateWindow(cs);
}

// CQCDBView 绘制

void CQCDBView::OnDraw(CDC* /*pDC*/)
{
	CQCDBDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CQCDBView 打印

BOOL CQCDBView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CQCDBView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印前添加额外的初始化
}

void CQCDBView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印后添加清除过程
}


// CQCDBView 诊断

#ifdef _DEBUG
void CQCDBView::AssertValid() const
{
	CView::AssertValid();
}

void CQCDBView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CQCDBDoc* CQCDBView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CQCDBDoc)));
	return (CQCDBDoc*)m_pDocument;
}
#endif //_DEBUG


// CQCDBView 消息处理程序
