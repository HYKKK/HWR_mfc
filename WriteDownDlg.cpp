// WriteDownDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WriteDown.h"
#include "WriteDownDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWriteDownDlg dialog

CWriteDownDlg::CWriteDownDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWriteDownDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWriteDownDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWriteDownDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWriteDownDlg)
	
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWriteDownDlg, CDialog)
	//{{AFX_MSG_MAP(CWriteDownDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_RECOGNIZE, OnRecognize)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_LEARN, OnLearn)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_COMMAND(IDM_EXIT, OnExit)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_COMMAND(IDM_RECOGNIZE, OnRecognize)
	ON_COMMAND(IDM_LEARN, OnLearn)
	ON_COMMAND(IDM_SAVE, OnSave)
	ON_COMMAND(IDM_CLEAR, OnClear)
	ON_COMMAND(IDM_ABOUT, OnAbout)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_PATTERN, &CWriteDownDlg::OnEnChangePattern)
	ON_EN_CHANGE(IDC_EDIT1, &CWriteDownDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTT_CHO, &CWriteDownDlg::OnBnClickedButtCho)
	ON_BN_CLICKED(IDC_BUTT_JUNG, &CWriteDownDlg::OnBnClickedButtJung)
	ON_BN_CLICKED(IDC_BUTT_JONG, &CWriteDownDlg::OnBnClickedButtJong)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWriteDownDlg message handlers

BOOL CWriteDownDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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

	// 컨트롤에 대한 핸들러를 초기화(EDIT BOX의 컨트롤을 넘긴다)
	// 변환된 입력의 컨트롤은 InputWnd에 넘김
	m_InputWnd.m_pPatternEdit = (CEdit*)GetDlgItem(IDC_PATTERN);
	m_InputWnd.m_pPatternEdit1 = (CEdit*)GetDlgItem(IDC_RESULT1);
	m_InputWnd.m_pMaxXEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
	m_InputWnd.m_pMaxYEdit = (CEdit*)GetDlgItem(IDC_EDIT2);
	m_InputWnd.m_pSCodeEdit = (CEdit*)GetDlgItem(IDC_EDIT3);
	m_InputWnd.m_pDebug = (CEdit*)GetDlgItem(IDC_EDIT4);
	

	m_font.CreateFont(  120, 
                        60, 
                        0, 
                        0, 
                        1, 
                        0,
                        0, 
                        0, 
                        0, 
                        OUT_DEFAULT_PRECIS, 
                        0,
                        DEFAULT_QUALITY,
                        DEFAULT_PITCH | FF_DONTCARE,
                        _T("견고딕") );
 
    GetDlgItem(IDC_RESULT1)->SetFont(&m_font);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWriteDownDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWriteDownDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWriteDownDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

int CWriteDownDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// 입력 윈도우를 생성
	m_InputWnd.CreateEx(WS_EX_STATICEDGE, NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0,0,0,0), this, 1000);
	
	return 0;
}

void CWriteDownDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// 입력 윈도우를 그림
	m_InputWnd.MoveWindow(150*2, 30, 282*2.2, 217*2.2);
	//m_InputWnd.MoveWindow(190, 80, 80, 50);
}

void CWriteDownDlg::OnRecognize() 
{
	
}

void CWriteDownDlg::OnClear()
{
	m_InputWnd.Clear();
	GetDlgItem(IDC_BUTT_CHO)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTT_JUNG)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTT_JONG)->ShowWindow(FALSE);
	
}

void CWriteDownDlg::OnLearn() 
{
	m_InputWnd.clear();
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT4);
	pEdit->SetFocus();

	GetDlgItem(IDC_BUTT_CHO)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTT_JUNG)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTT_JONG)->ShowWindow(TRUE);
		

}


void CWriteDownDlg::OnSave() 
{
	
}

void CWriteDownDlg::OnExit() 
{
	exit(0);
}


void CWriteDownDlg::OnAbout() 
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


void CWriteDownDlg::OnEnChangePattern()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



void CWriteDownDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CWriteDownDlg::OnBnClickedButtCho()
{
	m_InputWnd.inputScodeToCho();
}


void CWriteDownDlg::OnBnClickedButtJung()
{
	m_InputWnd.inputScodeToJung();
}


void CWriteDownDlg::OnBnClickedButtJong()
{
	m_InputWnd.inputScodeToJong();
}
