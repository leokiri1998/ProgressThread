// DlgProshow.cpp : implementation file
//

#include "pch.h"
#include "ProgressThread.h"
#include "DlgProshow.h"
#include "afxdialogex.h"


// DlgProshow dialog

IMPLEMENT_DYNAMIC(DlgProshow, CDialogEx)

DlgProshow::DlgProshow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROSHOW, pParent)
{
	szProText = L"";
	
	itotal = 100;
	istart = 1, ifinish = 100;
}

DlgProshow::~DlgProshow()
{
	blProPause = true;
}

void DlgProshow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS2, m_progress);
	DDX_Control(pDX, IDC_STATIC_MSGPRO, m_lbl);
}


BEGIN_MESSAGE_MAP(DlgProshow, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// DlgProshow message handlers
BOOL DlgProshow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: Add extra initialization here
	m_progress.AlignText(DT_CENTER);
	m_progress.SetBarColor(RGB(0, 176, 80));
	m_progress.SetBarBkColor(RGB(255, 255, 255));
	m_progress.SetTextColor(RGB(0, 0, 0));
	m_progress.SetTextBkColor(RGB(255, 255, 255));
	m_progress.SetWindowText(szProText);

	itotal = ifinish - istart + 1;
	m_progress.SetRange(0, itotal);
	m_progress.SetPos(0);

	SetTimer(1, 100, NULL);	// 1000ms = 1 second

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void DlgProshow::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_CLOSE) CDialogEx::OnCancel();
	else CDialog::OnSysCommand(nID, lParam);
}


void DlgProshow::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CString str = L"";
	m_progress.SetPos(demPro);
	str.Format(L"Download: (Rand= %03d) %d%s", iNumRand, (int)(100 *demPro/itotal), L"%");
	m_lbl.SetWindowText(str);

	if (demPro >= itotal) CDialogEx::OnOK();
	CDialogEx::OnTimer(nIDEvent);
}
