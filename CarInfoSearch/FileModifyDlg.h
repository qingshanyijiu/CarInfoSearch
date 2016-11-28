#pragma once


// CFileModifyDlg 对话框

class CFileModifyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileModifyDlg)

public:
	CFileModifyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFileModifyDlg();

public:
	CarFileData			m_carFileData;
	BYTE				m_bOperateType;

public:
	static CString		s_fileSavePath;

public:
	void	SetOperateType(BYTE bType,PCarFileData pInfo=NULL);

// 对话框数据
	enum { IDD = IDD_DIALOG_FILE_MODIFY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonFileAddSelect();
	afx_msg void OnBnClickedButtonFileModify();
	afx_msg void OnBnClickedButtonFileReturn();
	CButton m_fileSelectButton;
	CButton m_fileReturnButton;
	CButton m_fielModifyButton;
	CEdit m_fileNameEdit;
};
