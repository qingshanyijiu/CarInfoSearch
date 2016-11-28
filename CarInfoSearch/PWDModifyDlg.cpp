// PWDModifyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CarInfoSearch.h"
#include "CarInfoSearchDlg.h"
#include "PWDModifyDlg.h"
#include "afxdialogex.h"


// CPWDModifyDlg 对话框

IMPLEMENT_DYNAMIC(CPWDModifyDlg, CDialogEx)

CPWDModifyDlg::CPWDModifyDlg(UserPwdInfo*	pUserInfo,CWnd* pParent /*=NULL*/)
	: m_pUserInfo(pUserInfo),CDialogEx(CPWDModifyDlg::IDD, pParent)
{

}

CPWDModifyDlg::~CPWDModifyDlg()
{
}

void CPWDModifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPWDModifyDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PWD_Modify, &CPWDModifyDlg::OnBnClickedButtonPwdModify)
END_MESSAGE_MAP()


// CPWDModifyDlg 消息处理程序


BOOL CPWDModifyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}


BOOL CPWDModifyDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà

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


void CPWDModifyDlg::OnBnClickedButtonPwdModify()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	CString strOldPwd;
	GetDlgItemText(IDC_EDIT_PWD_OLD,strOldPwd);
	strOldPwd.Trim();
	if (strOldPwd.IsEmpty())
	{
		CCarInfoSearchDlg::ShowOperateInfo("请输入原始密码!");
		return;
	}

	if (0 !=strOldPwd.Compare(m_pUserInfo->csUserPwd))
	{
		CCarInfoSearchDlg::ShowOperateInfo("请原始密码输入有误!");
		return;
	}

	CString strNewPassword;
	GetDlgItemText(IDC_EDIT_PWD_NEW,strNewPassword);
	strNewPassword.Trim();
	if (strNewPassword.IsEmpty())
	{
		CCarInfoSearchDlg::ShowOperateInfo("请输入新密码!");
		return;
	}

	CString strNewPassword2;
	GetDlgItemText(IDC_EDIT_PWD_NEW2,strNewPassword2);
	strNewPassword2.Trim();
	if (strNewPassword2.IsEmpty())
	{
		CCarInfoSearchDlg::ShowOperateInfo("请输入确认密码!");
		return;
	}

	if (0!=strNewPassword.Compare(strNewPassword2))
	{
		CCarInfoSearchDlg::ShowOperateInfo("两次输入的密码不一样！");
		return;
	}

	strncpy(m_pUserInfo->csUserPwd,strNewPassword.operator LPCSTR(),16);

	if (OPERATE_DB_SUCCESS == UpdateUserInfo(m_pUserInfo))
	{
		CCarInfoSearchDlg::ShowOperateInfo("修改密码成功!");
		SetDlgItemText(IDC_EDIT_PWD_OLD,"");
		SetDlgItemText(IDC_EDIT_PWD_NEW,"");
		SetDlgItemText(IDC_EDIT_PWD_NEW2,"");
	}
	else
	{
		CCarInfoSearchDlg::ShowOperateInfo("修改密码失败!");
	}
}
