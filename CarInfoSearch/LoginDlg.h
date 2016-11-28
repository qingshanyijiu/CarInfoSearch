#pragma once


// CLoginDlg 对话框

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(UserPwdInfo*	pUserInfo,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginDlg();

private:
	void ShowLoginMessage(const char* lpMsg);
	UserPwdInfo*		m_pUserInfo;

// 对话框数据
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CStatic m_logPicShow;
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
