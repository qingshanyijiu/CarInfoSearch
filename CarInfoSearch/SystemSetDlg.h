#pragma once
// CSystemSetDlg dialog
class CSystemSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSystemSetDlg)
public:
	CSystemSetDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSystemSetDlg();
// Dialog Data
	enum { IDD = IDD_SYSSET_BASIC_DLG };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonScanpath();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSetsave();
};
