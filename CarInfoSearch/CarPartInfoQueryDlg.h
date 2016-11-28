#pragma once
#include <vector>
#include "QuerySuppTypesDlg.h"
using namespace std;
// CCarPartInfoQueryDlg dialog
class CCarInfoSearchDlg;

class CCarPartInfoQueryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCarPartInfoQueryDlg)
public:
	CCarPartInfoQueryDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCarPartInfoQueryDlg();
// Dialog Data
	enum { IDD = IDD_MaintenanceMng_QUERY_Dlg };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRclickListCarPartlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkListCarPartlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSmenuCarPartdelete();
	afx_msg void OnSmenuCarPartdetail();
	afx_msg void OnSmenuCarPartmodify();
	afx_msg void OnSmenuCarPartqueryCarType();
	virtual BOOL OnInitDialog();
	CListCtrl m_CarPartinfolist;
	afx_msg void OnBnClickedBtnMtQCarPartinfo();
	afx_msg void OnBnClickedButtonQCarTypebefore();
	afx_msg void OnBnClickedButtonQCarTypenext();
private:
	int								m_iTotalRecord;
	int								m_curPage;
	vector<CarPartTableInfo>		m_CarPartInfoVect;
	CarPartTableInfo				m_queryInfo;
	CQuerySuppTypesDlg				m_querySuppDlg;

public:
	void	UpdateDataInfo();
	void	QueryCarPartInfoByLicNumber(const char* lpLicNumber);	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSelchangeComboQuery();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnSmenuCarpartmodifycartype();
};
