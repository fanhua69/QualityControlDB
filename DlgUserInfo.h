#pragma once


// CDlgUserInfo dialog

class CDlgUserInfo : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgUserInfo)

public:
	CDlgUserInfo();   // standard constructor
	virtual ~CDlgUserInfo();

// Dialog Data
	enum { IDD = IDD_DlgUserInfo };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CString m_sUserNameShort;

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnApply();
};
