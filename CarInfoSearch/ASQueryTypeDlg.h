#pragma once
#include <vector>
#include <string>
#include "ListCtrlExtention.h"
using namespace std;

// CASQueryTypeDlg �Ի���

class CASQueryTypeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CASQueryTypeDlg)

public:
	CASQueryTypeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CASQueryTypeDlg();

public:
	int							m_iTotalRecord;
	int							m_curPageIndex;
	vector<ASCarTypeTableInfo>	m_CarTypeInfoVect;
	ASCarTypeTableInfo			m_carTypeSearchInfo;

public:
	void	UpdateDataInfo();

// �Ի�������
	enum { IDD = IDD_DIALOG_AS_QUERY_TYPE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonAsQueryType();
	afx_msg void OnBnClickedButtonAsQueryTypeBefore();
	afx_msg void OnSmenuAsTypeDetail();
	afx_msg void OnSmenuAsTypeModify();
	afx_msg void OnSmenuAsTypeDelete();
	afx_msg void OnDblclkListAsType(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickListAsType(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonAsQueryTypeNext();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	CListCtrlExtention	m_carTypeList;
};
