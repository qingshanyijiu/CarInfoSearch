#pragma once


// CPWDModifyDlg �Ի���

class CPWDModifyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPWDModifyDlg)

public:
	CPWDModifyDlg(UserPwdInfo*	pUserInfo,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPWDModifyDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_Password_Modify };

private:
	UserPwdInfo*	m_pUserInfo;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonPwdModify();
};
