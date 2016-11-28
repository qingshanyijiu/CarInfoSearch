#pragma once


// CFileModifyDlg �Ի���

class CFileModifyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileModifyDlg)

public:
	CFileModifyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFileModifyDlg();

public:
	CarFileData			m_carFileData;
	BYTE				m_bOperateType;

public:
	static CString		s_fileSavePath;

public:
	void	SetOperateType(BYTE bType,PCarFileData pInfo=NULL);

// �Ի�������
	enum { IDD = IDD_DIALOG_FILE_MODIFY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
