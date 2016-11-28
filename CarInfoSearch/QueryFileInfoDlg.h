#pragma once

#include <vector>
using namespace std;


// CQueryFileInfoDlg �Ի���

class CQueryFileInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CQueryFileInfoDlg)

public:
	CQueryFileInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQueryFileInfoDlg();

private:
	int									m_iTotalRecord;
	int									m_curPage;
	vector<CarFileData>					m_carFileDataVect;
	CarFileData							m_queryInfo;

private:
	void UpdateDataInfo();

// �Ի�������
	enum { IDD = IDD_DIALOG_FILE_QUERY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonFileSearch();
	CListCtrl m_fileInfoList;
	afx_msg void OnBnClickedButtonFileBefore();
	afx_msg void OnBnClickedButtonFileNext();
	afx_msg void OnRclickListFileInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkLisFileInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSmenuFileOpen();
	afx_msg void OnSmenuFileDetail();
	afx_msg void OnSmenuFileModify();
	afx_msg void OnSmenuFileDelete();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	int GetIconIndex(LPCTSTR lpszPath, BOOL bIsDir, BOOL bSelected);
};
