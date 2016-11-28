#pragma once

#include "QuerySuppTypesDlg.h"

// CCarPartInfoDlg dialog
class CCarPartInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCarPartInfoDlg)
public:
	void	SetOperateType(BYTE bType,PCarPartTableInfo pInfo=NULL);

private:
	CQuerySuppTypesDlg			m_queryTypeDlg;
	CarPartTableInfo			m_CarPartInfo;
	BYTE						m_bOperateType;

public:
	CCarPartInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCarPartInfoDlg();
// Dialog Data
	enum { IDD = IDD_MaintenanceMng_MODIFY_Dlg };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCarPartadd();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonSetsupptypes();
	afx_msg void OnBnClickedButtonCpModifyReturn();
	CButton m_modifyReturnButton;
	CButton m_AddModifyButton;
	CEdit m_editCarTypeNum;
	CEdit m_editChineseName;
	CEdit m_editDAENum;
	CEdit m_editEnglishName;
	CEdit m_editEPLNum;
	CEdit m_editInstallMark;
	CEdit m_editInstallNum;
	CEdit m_editLevel;
	CEdit m_editMMCNum;
	CEdit m_editPicNum;
	CEdit m_editVCNum;
	
};
