
// ProgressThreadDlg.h : header file
//

#pragma once
#include "TextProgressCtrl.h"

// CProgressThreadDlg dialog
class CProgressThreadDlg : public CDialogEx
{
// Construction
public:
	CProgressThreadDlg(CWnd* pParent = nullptr);	// standard constructor

	static UINT MyThreadProgress(LPVOID param);
	typedef struct THREADSTRUCT
	{
		CProgressThreadDlg* _this;
	} THREADSTRUCT;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROGRESSTHREAD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CTextProgressCtrl m_progress;

	CString szProText;
	int itotal;
	int istart, ifinish;
	int isleep;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOkstart();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
