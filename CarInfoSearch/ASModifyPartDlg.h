#pragma once

#include "ASModifySuppTypeDlg.h"

// CASModifyPartDlg �Ի���

class CASModifyPartDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CASModifyPartDlg)

public:
	CASModifyPartDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CASModifyPartDlg();

public:
	void	SetOperateType(BYTE bType,PASCarPartTableInfo pInfo=NULL);

private:
	CASModifySuppTypeDlg		m_queryTypeDlg;
	ASCarPartTableInfo			m_carPartInfo;
	BYTE						m_bOperateType;

// �Ի�������
	enum { IDD = IDD_DIALOG_AS_MODIFY_PART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonAsPartAdd();
	afx_msg void OnBnClickedButtonAsPartReturn();
	CButton m_addModifyButton;
	CButton m_modifyReturnButton;
};
