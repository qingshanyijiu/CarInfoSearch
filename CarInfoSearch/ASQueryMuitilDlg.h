#pragma once

#include <vector>
#include "ListCtrlExtention.h"
using namespace std;


// CASQueryMuitilDlg 对话框

class CASQueryMuitilDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CASQueryMuitilDlg)

public:
	CASQueryMuitilDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CASQueryMuitilDlg();

private:
	int									m_iTotalRecord;
	int									m_curPage;
	vector<ASSearchCarTypePartsInfo>	m_carTypePartsInfoVect;
	ASSearchCarTypePartsInfo			m_queryInfo;

private:
	void UpdateDataInfo();

// 对话框数据
	enum { IDD = IDD_DIALOG_AS_QUERY_MULTIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonAsMutiQuery();
	afx_msg void OnBnClickedButtonAsMuitilBefore();
	afx_msg void OnBnClickedButtonAsMuitilNext();
	afx_msg void OnSmenuAsMuitilDelete();
	afx_msg void OnSmenuAsMuitilPart();
	afx_msg void OnSmenuAsMuitilType();
	afx_msg void OnDblclkListAsMultil(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickListAsMultil(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrlExtention m_carTypePartsList;
};
