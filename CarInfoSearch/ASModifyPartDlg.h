#pragma once

#include "ASModifySuppTypeDlg.h"

// CASModifyPartDlg 对话框

class CASModifyPartDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CASModifyPartDlg)

public:
	CASModifyPartDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CASModifyPartDlg();

public:
	void	SetOperateType(BYTE bType,PASCarPartTableInfo pInfo=NULL);

private:
	CASModifySuppTypeDlg		m_queryTypeDlg;
	ASCarPartTableInfo			m_carPartInfo;
	BYTE						m_bOperateType;

// 对话框数据
	enum { IDD = IDD_DIALOG_AS_MODIFY_PART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonAsPartAdd();
	afx_msg void OnBnClickedButtonAsPartReturn();
	CButton m_addModifyButton;
	CButton m_modifyReturnButton;
};
