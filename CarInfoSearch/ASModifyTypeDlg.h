#pragma once


// CASModifyTypeDlg 对话框

class CASModifyTypeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CASModifyTypeDlg)

public:
	CASModifyTypeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CASModifyTypeDlg();

public:
	ASCarTypeTableInfo	m_carTypeInfo;
	BYTE				m_bOperateType;

public:
	void	SetOperateType(BYTE bType,PASCarTypeTableInfo pInfo=NULL);

// 对话框数据
	enum { IDD = IDD_DIALOG_AS_MODIFY_TYPE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonAsTypeAdd();
	afx_msg void OnBnClickedButtonAsTypeReturn();
	CButton m_modifyAddButton;
	CButton m_modifyReturnButton;
};
