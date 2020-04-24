
// ProgressThreadDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ProgressThread.h"
#include "ProgressThreadDlg.h"
#include "afxdialogex.h"
#include "DlgProshow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CProgressThreadDlg dialog



CProgressThreadDlg::CProgressThreadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROGRESSTHREAD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	szProText = L"Progress: ";
	istart = 100, ifinish = 250;
	isleep = 100;
}

void CProgressThreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
}

BEGIN_MESSAGE_MAP(CProgressThreadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOKSTART, &CProgressThreadDlg::OnBnClickedOkstart)
	ON_BN_CLICKED(IDOK, &CProgressThreadDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CProgressThreadDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CProgressThreadDlg message handlers

BOOL CProgressThreadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

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

	demPro = 0;
	blProPause = false;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CProgressThreadDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CProgressThreadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CProgressThreadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CProgressThreadDlg::OnBnClickedOkstart()
{
	blProPause = false;

	THREADSTRUCT *_param = new THREADSTRUCT;
	_param->_this = this;
	AfxBeginThread(MyThreadProgress, _param);

	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	DlgProshow p;
	p.szProText = szProText;
	p.istart = istart;
	p.ifinish = ifinish;
	p.DoModal();
}

void CProgressThreadDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}

void CProgressThreadDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

UINT CProgressThreadDlg::MyThreadProgress(LPVOID Param)
{
	try
	{
		THREADSTRUCT* ts = (THREADSTRUCT*)Param;
		CButton* m_btn = (CButton*)ts->_this->GetDlgItem(IDOKSTART);
		
		if(!blProPause) m_btn->SetWindowText(L"Resume");
		else m_btn->SetWindowText(L"Pause");

		CStatic *m_lbl = (CStatic*)ts->_this->GetDlgItem(IDC_STATIC_MSG);
		CString str = L"";

		int i = ts->_this->istart;
		while (!blProPause && i <= ts->_this->ifinish)
		{
			demPro++;
			iNumRand = rand() % 100;
			ts->_this->m_progress.SetPos(demPro);
			str.Format(L"Download: (Rand= %03d) %d%s", iNumRand, (int)(100 * demPro / ts->_this->itotal), L"%");
			m_lbl->SetWindowText(str);
			Sleep(ts->_this->isleep);

			i++;
		}

		if (demPro >= ts->_this->itotal)
		{
			m_btn->SetWindowText(L"Start");
			m_btn->EnableWindow(0);
		}		

		return TRUE;
	}
	catch (...) {}

	return TRUE;
}
