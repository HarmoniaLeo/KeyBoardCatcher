
// kbMsgCthMFCDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "kbMsgCthMFC.h"
#include "kbMsgCthMFCDlg.h"
#include "afxdialogex.h"
#include ".\kbMsgCth.h"

#pragma comment(lib,"kbMsgCth")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CkbMsgCthMFCDlg 对话框



CkbMsgCthMFCDlg::CkbMsgCthMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KBMSGCTHMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CkbMsgCthMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CkbMsgCthMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START2, &CkbMsgCthMFCDlg::OnBnClickedStart2)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_STOP2, &CkbMsgCthMFCDlg::OnClickedStop2)
	ON_BN_CLICKED(IDC_HIDE, &CkbMsgCthMFCDlg::OnClickedHide)
	ON_MESSAGE(HM_KEY, OnHookKey)
END_MESSAGE_MAP()


// CkbMsgCthMFCDlg 消息处理程序

BOOL CkbMsgCthMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CkbMsgCthMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CkbMsgCthMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CkbMsgCthMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL set = false;
HMODULE hModule;

typedef BOOL (WINAPI *PFNEXPORTFUNC)(HWND);
typedef BOOL (WINAPI *PFNEXPORTFUNC2)();

void CkbMsgCthMFCDlg::OnBnClickedStart2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!set)
	{
		hModule = ::LoadLibrary(TEXT("kbMsgCth.dll"));
		if (hModule != NULL)
		{
			PFNEXPORTFUNC FUNC = (PFNEXPORTFUNC)::GetProcAddress(hModule, "SetKeyHook");
			if (FUNC != NULL)
			{
				if (FUNC(m_hWnd))
				{
					set = true;
					CString tmp;
					GetDlgItem(IDC_OUTPUT)->GetWindowText(tmp);
					GetDlgItem(IDC_OUTPUT)->SetWindowText(tmp + "开始抓取\r\n");
					SendDlgItemMessage(IDC_OUTPUT, WM_VSCROLL, SB_BOTTOM, 0);
				}
			}
		}
	}
}

int CkbMsgCthMFCDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	set = false;
	return 0;
}

void CkbMsgCthMFCDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO: 在此处添加消息处理程序代码
	if (hModule != NULL)
	{
		if (set)
		{
			PFNEXPORTFUNC2 FUNC = (PFNEXPORTFUNC2)::GetProcAddress(hModule, "RemoveKeyHook");
			if (FUNC != NULL)
				FUNC();
			::FreeLibrary(hModule);
		}
	}
}


void CkbMsgCthMFCDlg::OnClickedStop2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (set)
	{
		if (hModule != NULL)
		{
			PFNEXPORTFUNC2 FUNC = (PFNEXPORTFUNC2)::GetProcAddress(hModule, "RemoveKeyHook");
			if (FUNC != NULL)
			{
				FUNC();
				set = false;
				CString tmp;
				GetDlgItem(IDC_OUTPUT)->GetWindowText(tmp);
				GetDlgItem(IDC_OUTPUT)->SetWindowText(tmp + "结束抓取\r\n");
				::FreeLibrary(hModule);
				SendDlgItemMessage(IDC_OUTPUT, WM_VSCROLL, SB_BOTTOM, 0);
			}
		}
	}
}


void CkbMsgCthMFCDlg::OnClickedHide()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}

LRESULT CkbMsgCthMFCDlg::OnHookKey(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此处添加实现代码.
	char szKey[80];
	::GetKeyNameText(lParam, (LPWSTR)szKey, 80);
	CString item;
	item.Format(_T("%s"),szKey);
	CString tmp;
	GetDlgItem(IDC_OUTPUT)->GetWindowText(tmp);
	GetDlgItem(IDC_OUTPUT)->SetWindowText(tmp+item+"\r\n");
	SendDlgItemMessage(IDC_OUTPUT, WM_VSCROLL, SB_BOTTOM, 0);
	return 0;
}
