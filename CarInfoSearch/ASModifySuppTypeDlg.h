#pragma once
#include <vector>
#include <string>
#include "ListCtrlExtention.h"
using namespace std;

// CASModifySuppTypeDlg �Ի���

class CASModifySuppTypeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CASModifySuppTypeDlg)

public:
	CASModifySuppTypeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CASModifySuppTypeDlg();


	void SetCartPartInfo(const PASCarPartTableInfo pInfo,BYTE bOpType);

private:
	vector<ASCarTypeTableInfo>			m_suppCarTypeVect;
	ASCarTypePartsTableInfo				m_carPartTypeInfoKey;
	BYTE								m_opType;

	void GetCheckData(vector<string>&	checkVect);
	void UpdateDataInfo();

// �Ի�������
	enum { IDD = IDD_DIALOG_AS_MODIFY_SUPP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBnClickedOk();
	CListCtrlExtention m_suppCarTypeList;
};
