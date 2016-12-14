#pragma once

#include <string>
using namespace std;


// CCheckKeyDlg �Ի���

class CCheckKeyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCheckKeyDlg)

public:
	CCheckKeyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCheckKeyDlg();

	bool CheckKeyPass();

private:
	string	m_strIniPath;
	CStringArray m_strMacArray;


// �Ի�������
	enum { IDD = IDD_DIALOG_CHECK_KEY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
