#pragma once
#include "afxwin.h"
// CCarTypeInfoDlg dialog
class CCarTypeInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCarTypeInfoDlg)
public:
	CCarTypeInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCarTypeInfoDlg();
public:
	CarTypeTableInfo	m_CarTypeInfo;
	BYTE				m_bOperateType;

public:
	void	SetOperateType(BYTE bType,PCarTypeTableInfo pInfo=NULL);

// Dialog Data
	enum { IDD = IDD_CarTypeMNG_MODIFY_DLG };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreInitDialog();
	CButton m_modifyReturnButton;
	CEdit m_editDetailName;
	CEdit m_editDetailTypeNum;
	CEdit m_editCarFactory;
	CEdit m_editCarStatus;
	CEdit m_editCarTypeNum;
	CEdit m_editCarNotes;
	CButton m_addMotifyButton;
	afx_msg void OnBnClickedBtnCarTypeAdd();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonCtModifyReturn();
};
