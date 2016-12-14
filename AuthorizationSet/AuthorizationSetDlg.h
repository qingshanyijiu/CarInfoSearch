
// AuthorizationSetDlg.h : 头文件
//

#pragma once


// CAuthorizationSetDlg 对话框
class CAuthorizationSetDlg : public CDialogEx
{
// 构造
public:
	CAuthorizationSetDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AUTHORIZATIONSET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButtonGetLocalMac();
	afx_msg void OnBnClickedButtonCreateCode();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
};
