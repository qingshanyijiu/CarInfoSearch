#pragma once


// CSysAboutDlg �Ի���

class CSysAboutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSysAboutDlg)

public:
	CSysAboutDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSysAboutDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SYSAbout };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSyslinkOperate();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClickedMfclinkOperateLook();
	afx_msg void OnDoubleclickedMfclinkOperateLook();
};
