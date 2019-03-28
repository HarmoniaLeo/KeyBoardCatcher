
// kbMsgCthMFCDlg.h: 头文件
//

#pragma once


// CkbMsgCthMFCDlg 对话框
class CkbMsgCthMFCDlg : public CDialogEx
{
// 构造
public:
	CkbMsgCthMFCDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KBMSGCTHMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedStart2();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnClickedStop2();
	afx_msg void OnClickedHide();
	LRESULT OnHookKey(WPARAM wParam,LPARAM lParam);
};
