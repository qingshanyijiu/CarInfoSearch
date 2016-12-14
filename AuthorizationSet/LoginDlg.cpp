// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AuthorizationSet.h"
#include "AuthorizationSetDlg.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(UserPwdInfo*	pUserInfo,CWnd* pParent /*=NULL*/)
	: m_pUserInfo(pUserInfo),CDialogEx(CLoginDlg::IDD, pParent)
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_LogPic, m_logPicShow);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLoginDlg::OnBnClickedCancel)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedOk()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	memset(m_pUserInfo,0,sizeof(UserPwdInfo));

	CString strName;
	GetDlgItemText(IDC_EDIT_LOGIN_Name,strName);
	strName.Trim();
	if (strName.IsEmpty())
	{
		ShowLoginMessage("请输入用户名!");
		return;
	}
	strncpy(m_pUserInfo->csUserName,strName.operator LPCSTR(),16);

	CString strPassword;
	GetDlgItemText(IDC_EDIT_LOGIN_PASSWORD,strPassword);
	strPassword.Trim();
	if (strPassword.IsEmpty())
	{
		ShowLoginMessage("请输入密码!");
		return;
	}

	strncpy(m_pUserInfo->csUserPwd,strPassword.operator LPCSTR(),16);

	if (OPERATE_DB_SUCCESS == QueryUserInfo(m_pUserInfo))
	{
		if (m_pUserInfo->uKey)
		{
			if (m_pUserInfo->uKey&0x0002)
			{
				CDialogEx::OnOK();
			}
			else
			{
				ShowLoginMessage("请用管理员账号登陆!");
			}
			
		}
		else
		{
			ShowLoginMessage("用户名或者密码不正确!");
		}
	}
	else
	{
		ShowLoginMessage("用户名或者密码不正确!");
	}
}


void CLoginDlg::OnBnClickedCancel()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	CDialogEx::OnCancel();
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯

	HBITMAP hBitMap  = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_LOGIN),IMAGE_BITMAP,100,100, LR_CREATEDIBSECTION);
	m_logPicShow.SetBitmap(hBitMap);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}


void CLoginDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ÔÚ´Ë´¦Ìí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂë
	// ²»Îª»æÍ¼ÏûÏ¢µ÷ÓÃ CDialogEx::OnPaint()
}


HBRUSH CLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ÔÚ´Ë¸ü¸Ä DC µÄÈÎºÎÌØÐÔ

	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC_LOGIN_RESULT:
		pDC->SetTextColor(RGB(255,0,0));
		break;
	}

	// TODO:  Èç¹ûÄ¬ÈÏµÄ²»ÊÇËùÐè»­±Ê£¬Ôò·µ»ØÁíÒ»¸ö»­±Ê
	return hbr;
}


void CLoginDlg::ShowLoginMessage(const char* lpMsg)
{
	SetDlgItemText(IDC_STATIC_LOGIN_RESULT,lpMsg);
}