#pragma once
#include <vector>
#include "ASModifySuppTypeDlg.h"
#include "ListCtrlExtention.h"
using namespace std;

// CASQueryPartDlg �Ի���

class CASQueryPartDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CASQueryPartDlg)

public:
	CASQueryPartDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CASQueryPartDlg();

private:
	int								m_iTotalRecord;
	int								m_curPage;
	vector<ASCarPartTableInfo>		m_CarPartInfoVect;
	ASCarPartTableInfo				m_queryInfo;
	CASModifySuppTypeDlg			m_querySuppDlg;

public:
	void	UpdateDataInfo();

// �Ի�������
	enum { IDD = IDD_DIALOG_AS_QUERY_PART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonAsPartQuery();
	afx_msg void OnBnClickedButtonAsQueryPartBefore();
	afx_msg void OnBnClickedButtonAsQueryPartNext();
	afx_msg void OnSmenuAsPartDetail();
	afx_msg void OnSmenuAsPartModify();
	afx_msg void OnSmenuAsPartDelete();
	afx_msg void OnSmenuAsPartTypedetail();
	afx_msg void OnSmenuAsPartTypemodify();
	afx_msg void OnDblclkListAsPart(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickListAsPart(NMHDR *pNMHDR, LRESULT *pResult);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	CListCtrlExtention m_carPartinfolist;
};
