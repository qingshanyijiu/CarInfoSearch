// CarTypeInfoDlg.cpp : implementation file
//
#include "stdafx.h"
#include "CarInfoSearch.h"
#include "CarTypeInfoDlg.h"
#include "afxdialogex.h"
#include "CarInfoSearchDlg.h"
extern CCarInfoSearchDlg*	g_pMainDlg;

// CCarTypeInfoDlg dialog
IMPLEMENT_DYNAMIC(CCarTypeInfoDlg, CDialogEx)
CCarTypeInfoDlg::CCarTypeInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCarTypeInfoDlg::IDD, pParent)
{
	m_bOperateType = OPERATE_TYPE_ADD;
	m_CarTypeInfo.Clear();
}
CCarTypeInfoDlg::~CCarTypeInfoDlg()
{
}
void CCarTypeInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_CarType_ADD, m_addMotifyButton);
	DDX_Control(pDX, IDC_BUTTON_CT_MODIFY_RETURN, m_modifyReturnButton);
	DDX_Control(pDX, IDC_EDIT_CT_ADD_CarDetailName, m_editDetailName);
	DDX_Control(pDX, IDC_EDIT_CT_ADD_CarDetailTypeNum, m_editDetailTypeNum);
	DDX_Control(pDX, IDC_EDIT_CT_ADD_CarFactory, m_editCarFactory);
	DDX_Control(pDX, IDC_EDIT_CT_ADD_CarStatus, m_editCarStatus);
	DDX_Control(pDX, IDC_EDIT_CT_ADD_CarTypeNum, m_editCarTypeNum);
	DDX_Control(pDX, IDC_EDIT_CT_ADD_Notes, m_editCarNotes);
}
BEGIN_MESSAGE_MAP(CCarTypeInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_CarType_ADD, &CCarTypeInfoDlg::OnBnClickedBtnCarTypeAdd)
	ON_BN_CLICKED(IDC_BUTTON_CT_MODIFY_RETURN, &CCarTypeInfoDlg::OnBnClickedButtonCtModifyReturn)
END_MESSAGE_MAP()
// CCarTypeInfoDlg message handlers
void CCarTypeInfoDlg::OnBnClickedBtnCarTypeAdd()
{
	// TODO: Add your control notification handler code here
	CString	strTemp;
	m_CarTypeInfo.Clear();

	GetDlgItemText(IDC_EDIT_CT_ADD_CarTypeNum,strTemp);
	strTemp.Trim();
	if (strTemp.IsEmpty())
	{
		CCarInfoSearchDlg::ShowOperateInfo("请输入机型编号！");
		return;
	}
	strncpy(m_CarTypeInfo.csCarTypeNum,strTemp.operator LPCSTR(),16);

	GetDlgItemText(IDC_EDIT_CT_ADD_CarDetailTypeNum,strTemp);
	strTemp.Trim();
	if (strTemp.IsEmpty())
	{
		CCarInfoSearchDlg::ShowOperateInfo("请输入发动机具体编号！");
		return;
	}
	strncpy(m_CarTypeInfo.csCarDetailTypeNum,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_CT_ADD_CarDetailName,strTemp);
	strTemp.Trim();
	strncpy(m_CarTypeInfo.csCarDetailName,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_CT_ADD_CarFactory,strTemp);
	strTemp.Trim();
	strncpy(m_CarTypeInfo.csCarFactory,strTemp.operator LPCSTR(),32);
	GetDlgItemText(IDC_EDIT_CT_ADD_CarStatus,strTemp);
	strTemp.Trim();
	strncpy(m_CarTypeInfo.csCarStatus,strTemp.operator LPCSTR(),32);
	GetDlgItemText(IDC_EDIT_CT_ADD_Notes,strTemp);
	m_CarTypeInfo.strCarNotes = strTemp.operator LPCSTR();

	if (OPERATE_TYPE_ADD == m_bOperateType)
	{
		if(OPERATE_DB_SUCCESS  ==InsertCarTypeInfo(&m_CarTypeInfo))
		{
			CCarInfoSearchDlg::ShowOperateInfo("插入机型信息成功！");

			m_editDetailName.SetWindowText("");
			m_editDetailTypeNum.SetWindowText("");
			m_editCarFactory.SetWindowText("");
			m_editCarStatus.SetWindowText("");
			m_editCarTypeNum.SetWindowText("");
			m_editCarNotes.SetWindowText("");
		}
		else
		{
			CCarInfoSearchDlg::ShowOperateInfo("插入机型信息失败！可能该信息已经存在！");
		}
	}
	else if (OPERATE_TYPE_MODIFY == m_bOperateType)
	{
		if(OPERATE_DB_SUCCESS ==UpdateCarTypeInfo(&m_CarTypeInfo))
		{
			CCarInfoSearchDlg::ShowOperateInfo("修改机型信息成功！");
			g_pMainDlg->RightPageShow(IDD_CarTypeMNG_QUERY_DLG,true);
		}
		else
		{
			CCarInfoSearchDlg::ShowOperateInfo("修改机型信息失败！可能是无该记录!");
		}
	}
}
void CCarTypeInfoDlg::SetOperateType(BYTE bType,PCarTypeTableInfo pInfo/*=NULL*/)
{
	m_bOperateType = bType;
	m_CarTypeInfo.Clear();

	switch(bType)
	{
	case OPERATE_TYPE_ADD:
		{
			m_editDetailName.SetWindowText("");
			m_editDetailTypeNum.SetWindowText("");
			m_editCarFactory.SetWindowText("");
			m_editCarStatus.SetWindowText("");
			m_editCarTypeNum.SetWindowText("");
			m_editCarNotes.SetWindowText("");

			m_addMotifyButton.SetWindowText("增加\nAdd");
			m_addMotifyButton.ShowWindow(SW_SHOW);
			m_modifyReturnButton.ShowWindow(SW_HIDE);
			m_editDetailTypeNum.SetReadOnly(FALSE);
		}
		break;
	case OPERATE_TYPE_MODIFY:
	case OPERATE_TYPE_SHOW:
	case OPERATE_TYPE_SHOW_EX:
		m_editDetailName.SetWindowText(pInfo->csCarDetailName);
		m_editDetailTypeNum.SetWindowText(pInfo->csCarDetailTypeNum);
		m_editCarFactory.SetWindowText(pInfo->csCarFactory);
		m_editCarStatus.SetWindowText(pInfo->csCarStatus);
		m_editCarTypeNum.SetWindowText(pInfo->csCarTypeNum);
		m_editCarNotes.SetWindowText(pInfo->strCarNotes.c_str());

		m_modifyReturnButton.ShowWindow(SW_SHOW);
		m_editDetailTypeNum.SetReadOnly(TRUE);

		if(OPERATE_TYPE_MODIFY == m_bOperateType)
		{
			m_addMotifyButton.SetWindowText("修改\nModify");
			m_addMotifyButton.ShowWindow(SW_SHOW);
		}
		else
		{
			m_addMotifyButton.ShowWindow(SW_HIDE);
		}
		
		break;
	}
}
BOOL CCarTypeInfoDlg::PreTranslateMessage(MSG* pMsg)
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
void CCarTypeInfoDlg::PreInitDialog()
{
	// TODO: Add your specialized code here and/or call the base class
	CDialogEx::PreInitDialog();
}


BOOL CCarTypeInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯

	m_modifyReturnButton.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}


void CCarTypeInfoDlg::OnBnClickedButtonCtModifyReturn()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	if (OPERATE_TYPE_MODIFY == m_bOperateType)
	{
		if(IDYES== MessageBox("确定要放弃修改数据?\nWhether to give up modification?","提示(Notify)",MB_YESNO))
		{
			g_pMainDlg->RightPageShow(IDD_CarTypeMNG_QUERY_DLG);
		}
	}
	else if (OPERATE_TYPE_SHOW == m_bOperateType)
	{
		g_pMainDlg->RightPageShow(IDD_CarTypeMNG_QUERY_DLG);		
	}
	else
	{
		g_pMainDlg->RightPageShow(IDD_DIALOG_CarTypeParts);
	}
}
