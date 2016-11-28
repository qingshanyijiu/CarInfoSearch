#pragma once
#include <vector>
#include <string>
using namespace std;


// CQuerySuppTypesDlg �Ի���

class CQuerySuppTypesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CQuerySuppTypesDlg)

public:
	CQuerySuppTypesDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQuerySuppTypesDlg();

	void SetCartPartInfo(const PCarPartTableInfo pInfo,BYTE bOpType);

private:
	vector<CarTypeTableInfo>			m_suppCarTypeVect;
	CarTypePartsTableInfo				m_carPartTypeInfoKey;
	BYTE								m_opType;

	void GetCheckData(vector<string>&	checkVect);
	void UpdateDataInfo();

// �Ի�������
	enum { IDD = IDD_DIALOG_CTP_QureyTypes };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	CListCtrl m_suppCarTypeList;
	afx_msg void OnBnClickedOk();
};
