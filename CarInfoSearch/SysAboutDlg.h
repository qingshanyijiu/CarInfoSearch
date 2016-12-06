#pragma once


// CSysAboutDlg 对话框

class CSysAboutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSysAboutDlg)

public:
	CSysAboutDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSysAboutDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_SYSAbout };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSyslinkOperate();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClickedMfclinkOperateLook();
	afx_msg void OnDoubleclickedMfclinkOperateLook();
};
