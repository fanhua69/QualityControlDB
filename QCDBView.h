// QCDBView.h : CQCDBView ��Ľӿ�
//


#pragma once


class CQCDBView : public CView
{
protected: // �������л�����
	CQCDBView();
	DECLARE_DYNCREATE(CQCDBView)

// ����
public:
	CQCDBDoc* GetDocument() const;

// ����
public:

// ��д
	public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CQCDBView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // QCDBView.cpp �ĵ��԰汾
inline CQCDBDoc* CQCDBView::GetDocument() const
   { return reinterpret_cast<CQCDBDoc*>(m_pDocument); }
#endif

