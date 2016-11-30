#pragma once
#include <fstream>
using namespace std;

// CLoadDataDlg �Ի���

class CLoadDataDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoadDataDlg)

public:
	CLoadDataDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoadDataDlg();

private:
	ofstream	m_oFile;

private:
	UINT DivStrEx(CString& str,CStringArray& Arr,char ch,int iCount);
	bool InsertCarTypeData(const char* lpStr);
	bool InsertCarPartsData(const char* lpStr);
	bool InsertCarTypePartsData(const char* lpStr);
	bool InsertCarTypePartsDataEx(const char* lpStr);

// �Ի�������
	enum { IDD = IDD_DIALOG_LOAD_DATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_loadSelectCombo;
	afx_msg void OnBnClickedButtonLoadSelect();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonLoadBegin();
};
