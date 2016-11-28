#pragma once
#include <vector>
#include <string>
using namespace std;


// CQuerySuppTypesDlg 对话框

class CQuerySuppTypesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CQuerySuppTypesDlg)

public:
	CQuerySuppTypesDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQuerySuppTypesDlg();

	void SetCartPartInfo(const PCarPartTableInfo pInfo,BYTE bOpType);

private:
	vector<CarTypeTableInfo>			m_suppCarTypeVect;
	CarTypePartsTableInfo				m_carPartTypeInfoKey;
	BYTE								m_opType;

	void GetCheckData(vector<string>&	checkVect);
	void UpdateDataInfo();

// 对话框数据
	enum { IDD = IDD_DIALOG_CTP_QureyTypes };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	CListCtrl m_suppCarTypeList;
	afx_msg void OnBnClickedOk();
};
