#pragma once


#include "DataBrowseView.h"

class CQCDBDataBrowseView : public CDataBrowseView
{
	DECLARE_DYNCREATE(CQCDBDataBrowseView)

protected:
	CQCDBDataBrowseView();           // protected constructor used by dynamic creation
	virtual ~CQCDBDataBrowseView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
    virtual void SetComboxContents( CString         sTableName,
                                    CFieldData      *pField,
                                    int             iFieldQty,
                                    int             iFixedRowOrColQty, 
                                    bool            bSetRowToCol);

    void    ComboModified(int iRow,int iCol,CString sNewName);


protected:
	DECLARE_MESSAGE_MAP()
public:
protected:
public:
    afx_msg void OnUpdatedb();
    afx_msg void OnDbbrowseInputqcdata();
    afx_msg void OnUpdateDbbrowseInputqcdata(CCmdUI *pCmdUI);
};


