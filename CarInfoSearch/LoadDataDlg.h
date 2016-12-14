#pragma once
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
using namespace std;

typedef vector<string>   TypeVect;
typedef map<string,vector<string> >  TypeMap;

// CLoadDataDlg 对话框

class CLoadDataDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoadDataDlg)

public:
	CLoadDataDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoadDataDlg();

private:
	ofstream	m_oFile;
	ofstream	m_oFormatFile;
	bool		m_bLog;

private:
	UINT DivStrEx(CString& str,CStringArray& Arr,char ch,int iCount);
	bool InsertCarTypeData(const char* lpStr);
	bool InsertCarPartsData(const char* lpStr);
	bool InsertCarTypePartsData(const char* lpStr);
	bool InsertCarTypePartsDataEx(const char* lpStr);
	bool InsertCarTypePartsDataEx(const char* lpStr,vector<string>& typeVect);
	bool InsertCarTypePartsDataEx(const char* lpStr,vector<string>& typeVect,TypeMap& typeMap);
	bool InsertCarTypePartsDataEx(const char* lpStr,vector<string>& typeVect,vector<string>& typeOtherVect,TypeMap& typeMap);
	bool InsertCarTypePartsDataEx2(const char* lpStr,vector<string>& typeVect,vector<string>& typeOtherVect,TypeMap& typeMap);

	void FormatResult(void* lpResult,vector<string>& typeVect,bool bShow=true);

// 对话框数据
	enum { IDD = IDD_DIALOG_LOAD_DATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_loadSelectCombo;
	afx_msg void OnBnClickedButtonLoadSelect();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonLoadBegin();
	CButton m_testCheck;
};
