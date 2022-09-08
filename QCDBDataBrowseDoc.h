#pragma once

#include "databrowsedoc.h"

class CQCDBDataBrowseDoc : public CDataBrowseDoc
{
	DECLARE_DYNCREATE(CQCDBDataBrowseDoc)
	friend class CQCDBDataBrowseView;
public:
	CQCDBDataBrowseDoc();
	virtual ~CQCDBDataBrowseDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


public:
    void            UpdateDB();

	bool			InputQCData();
	bool			InputQCData1001(CString sProjectNo,CString sTestNo,	CReportReader *pReader);
	bool			InputQCData1002(CString sProjectNo,CString sTestNo,	CReportReader *pReader);
	bool			InputQCData1003(CString sProjectNo,CString sTestNo,	CReportReader *pReader);
  	bool			InputQCData1004(CString sProjectNo,CString sTestNo,	CReportReader *pReader);
	bool			InputQCData1005(CString sProjectNo,CString sTestNo,	CReportReader *pReader);
	bool			InputQCData1006(CString sProjectNo,CString sTestNo,	CReportReader *pReader);
	bool			InputQCData1007(CString sProjectNo,CString sTestNo,	CReportReader *pReader);
	bool			InputQCData1008(CString sProjectNo,CString sTestNo,	CReportReader *pReader);
	bool			InputQCData1009(CString sProjectNo,CString sTestNo,	CReportReader *pReader);
	bool			InputQCData1010(CString sProjectNo,CString sTestNo,	CReportReader *pReader);
	bool			InputQCData1011(CString sProjectNo,CString sTestNo,	CReportReader *pReader);
	bool			InputQCData1012(CString sProjectNo,CString sTestNo,	CReportReader *pReader);
	bool			InputQCData1013(CString sProjectNo,CString sTestNo,	CReportReader *pReader);
	bool			InputQCData1014(CString sProjectNo,CString sTestNo,	CReportReader *pReader);
	bool			InputQCData1015(CString sProjectNo,CString sTestNo,	CReportReader *pReader);
	bool			InputQCData1016(CString sProjectNo,CString sTestNo,	CReportReader *pReader);
	bool			InputQCData1017(CString sProjectNo,CString sTestNo,	CReportReader *pReader);
	bool			InputQCData1018(CString sProjectNo,CString sTestNo,	CReportReader *pReader);
	bool			InputQCData1019(CString sProjectNo,CString sTestNo,	CReportReader *pReader);
	bool			InputQCData1020(CString sProjectNo,CString sTestNo,	CReportReader *pReader);

	/////////////////////////////
	//
	/////////////////////////////

protected:

	DECLARE_MESSAGE_MAP()
public:
public:
};

