// CarInfoSearchDlg.h : ͷ�ļ�
//
#pragma once
#include <vector>
#include <string>
#include <map>
#include "ColoredStatusBarCtrl.h"
class CButtonExd;

#define  ID_STATUS_BAR		(30000)

// CCarInfoSearchDlg �Ի���
class CCarInfoSearchDlg : public CDialogEx
{
// ����
public:
	CCarInfoSearchDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CCarInfoSearchDlg();
	typedef std::map<long,CDialog *> PageMap;
	PageMap m_pages;
// �Ի�������
	enum { IDD = IDD_CarPartCARINFOMANAGE_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
private:
	
	BOOL ShowParamDlg(CWnd* pWnd, BOOL bShow);

private:
	CWnd*					m_pCurrentWnd;
	CButtonExd*				m_root;
	CColoredStatusBarCtrl	m_statusBar;
	UserPwdInfo				m_userInfo;

// ʵ��
public:
	void RightPageShow(long DLGID,bool bUpdate=false);
protected:
	HICON m_hIcon;
	void Expand(int index);
	
	void AfterButtonClick(void*);
	void TestBofore(void* );
	void TestAfter(void*);
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCarTypemng();
	afx_msg void OnBnClickedBtnMtinfomng();
	afx_msg void OnBnClickedButtonSystemset();
	afx_msg void OnBnClickedBtnCarTypequery();
	afx_msg void OnBnClickedBtnCarTypemodify();
	afx_msg void OnBnClickedBtnMtquery();
	afx_msg void OnBnClickedBtnMtmodify();
	afx_msg void OnBnClickedButtonBasicset();
	afx_msg void OnBnClickedButtonFileModify();
	afx_msg void OnBnClickedButtonFileQuery();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

public:
	void ShowResultInfo(const char* lpShowInfo);
	void ShowSearchInfo(int iTotalCount,int iCurPape);

	static void ShowOperateInfo(const char* lpShowInfo);
	static void ShowOperateInfoEx(const char* lpShowInfo);
	static void ShowSearchRecord(int iTotalCount,int iCurPape);
	static unsigned long	s_dwUserPower;
	static std::string		s_curPath;

	afx_msg void OnBnClickedButtonSysabout();
	afx_msg void OnBnClickedButtonPasswordSet();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnBnClickedButtonnCarTypePartsQuery();
};
