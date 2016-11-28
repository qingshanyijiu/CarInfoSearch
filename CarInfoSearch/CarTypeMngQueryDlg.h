#pragma once
#include <vector>
#include <string>
using namespace std;
// CCarTypeMngQueryDlg 对话框
typedef int (*pQueryfunc)(const char* lpLicNumer,int iPages,int iMaxCount,std::vector<CarTypeTableInfo>& CarTypeInfoList,bool bOrderInc);
class CCarTypeMngQueryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCarTypeMngQueryDlg)
public:
	CCarTypeMngQueryDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCarTypeMngQueryDlg();
// 对话框数据
	enum { IDD = IDD_CarTypeMNG_QUERY_DLG };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	CButton m_groupbox;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnCarTypeCarTypequery();
	afx_msg void OnBnClickedButtonQCarTypebefore();
	afx_msg void OnBnClickedButtonQCarTypenext();
	CButton m_QCarTypeBeforeButton;
	CButton m_QCarTypeNextButton;
	CListCtrl m_CarTypeList;
//	afx_msg void OnLvnItemchangedListCarTypelist(NMHDR *pNMHDR, LRESULT *pResult);
public:
	int							m_iTotalRecord;
	int							m_curPageIndex;
	pQueryfunc					m_pQueryFunc;
	vector<CarTypeTableInfo>	m_CarTypeInfoVect;
	CarTypeTableInfo			m_carTypeSearchInfo;

public:
	void	UpdateDataInfo();

public:
	afx_msg void OnRclickListCarTypelist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkListCarTypelist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSmenuCarTypedelete();
	afx_msg void OnSmenuCarTypedetail();
	afx_msg void OnSmenuCarTypemodify();
	afx_msg void OnSmenuCarTypequeryrepair();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
