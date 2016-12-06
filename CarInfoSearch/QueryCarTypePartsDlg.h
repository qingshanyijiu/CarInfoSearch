#pragma once

#include <vector>
#include "ListCtrlExtention.h"
using namespace std;


// CQueryCarTypePartsDlg 对话框

class CQueryCarTypePartsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CQueryCarTypePartsDlg)

public:
	CQueryCarTypePartsDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQueryCarTypePartsDlg();

private:
	int									m_iTotalRecord;
	int									m_curPage;
	vector<SearchCarTypePartsInfo>		m_carTypePartsInfoVect;
	SearchCarTypePartsInfo				m_queryInfo;

private:
	void UpdateDataInfo();

// 对话框数据
	enum { IDD = IDD_DIALOG_CarTypeParts };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonEtpSearch();
	CListCtrlExtention m_carTypePartsList;
	afx_msg void OnBnClickedButtonCtpBefore();
	afx_msg void OnBnClickedButtonEtpNext();
	afx_msg void OnRclickListCarTypeParts(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkListCarTypeParts(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSmenuCtpParts();
	afx_msg void OnSmenuCtpType();
	afx_msg void OnSmenuCtpDelete();
};
