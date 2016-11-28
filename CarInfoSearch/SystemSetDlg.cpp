// SystemSetDlg.cpp : implementation file
//
#include "stdafx.h"
#include "CarInfoSearch.h"
#include "CarInfoSearchDlg.h"
#include "SystemSetDlg.h"
#include "afxdialogex.h"
#include <string>
using namespace std;


// CSystemSetDlg dialog
IMPLEMENT_DYNAMIC(CSystemSetDlg, CDialogEx)
CSystemSetDlg::CSystemSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSystemSetDlg::IDD, pParent)
{
}
CSystemSetDlg::~CSystemSetDlg()
{
}
void CSystemSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CSystemSetDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ScanPath, &CSystemSetDlg::OnBnClickedButtonScanpath)
	ON_BN_CLICKED(IDC_BTN_SetSave, &CSystemSetDlg::OnBnClickedBtnSetsave)
END_MESSAGE_MAP()
// CSystemSetDlg message handlers
BOOL CSystemSetDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	// 把Esc和Enter按键事件消息过滤掉，否则该消息会导致对应应用程序调用OnOK（）方法，结束应用程序
	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_ESCAPE: //Esc按键事件
			return true;
		case VK_RETURN: //Enter按键事件
			return true;
		default:
			;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CSystemSetDlg::OnBnClickedButtonScanpath()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
}




BOOL CSystemSetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯

	string strPath=CCarInfoSearchDlg::s_curPath;
	strPath += "SaveInfo\\";
	
	SetDlgItemText(IDC_EDIT_SavePath,strPath.c_str());


	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}


void CSystemSetDlg::OnBnClickedBtnSetsave()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
}
