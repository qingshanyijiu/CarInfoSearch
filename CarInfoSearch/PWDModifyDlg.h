#pragma once


// CPWDModifyDlg 对话框

class CPWDModifyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPWDModifyDlg)

public:
	CPWDModifyDlg(UserPwdInfo*	pUserInfo,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPWDModifyDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_Password_Modify };

private:
	UserPwdInfo*	m_pUserInfo;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonPwdModify();
};
