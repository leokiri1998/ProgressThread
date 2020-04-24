#pragma once
#include "TextProgressCtrl.h"

// DlgProshow dialog

class DlgProshow : public CDialogEx
{
	DECLARE_DYNAMIC(DlgProshow)

public:
	DlgProshow(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgProshow();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROSHOW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

public:
	CTextProgressCtrl m_progress;
	CStatic m_lbl;

	CString szProText;

	int itotal;
	int istart, ifinish;
	
};
