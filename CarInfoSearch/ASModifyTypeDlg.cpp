// ASModifyTypeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CarInfoSearch.h"
#include "ASModifyTypeDlg.h"
#include "afxdialogex.h"
#include "CarInfoSearchDlg.h"
extern CCarInfoSearchDlg*	g_pMainDlg;


// CASModifyTypeDlg 对话框

IMPLEMENT_DYNAMIC(CASModifyTypeDlg, CDialogEx)

CASModifyTypeDlg::CASModifyTypeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CASModifyTypeDlg::IDD, pParent)
{
	m_bOperateType = OPERATE_TYPE_ADD;
	m_carTypeInfo.Clear();
}

CASModifyTypeDlg::~CASModifyTypeDlg()
{
}

void CASModifyTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_AS_TYPE_ADD, m_modifyAddButton);
	DDX_Control(pDX, IDC_BUTTON_AS_TYPE_RETURN, m_modifyReturnButton);
}


BEGIN_MESSAGE_MAP(CASModifyTypeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_AS_TYPE_ADD, &CASModifyTypeDlg::OnBnClickedButtonAsTypeAdd)
	ON_BN_CLICKED(IDC_BUTTON_AS_TYPE_RETURN, &CASModifyTypeDlg::OnBnClickedButtonAsTypeReturn)
END_MESSAGE_MAP()


// CASModifyTypeDlg 消息处理程序


BOOL CASModifyTypeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯
	m_modifyReturnButton.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}


BOOL CASModifyTypeDlg::PreTranslateMessage(MSG* pMsg)
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
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CASModifyTypeDlg::OnBnClickedButtonAsTypeAdd()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	CString	strTemp;
	m_carTypeInfo.Clear();

	GetDlgItemText(IDC_EDIT_AS_TYPE_ADD_TypeNum,strTemp);
	strTemp.Trim();
	if (strTemp.IsEmpty())
	{
		CCarInfoSearchDlg::ShowOperateInfo("请输入机型编号！");
		return;
	}
	strncpy(m_carTypeInfo.csCarTypeNum,strTemp.operator LPCSTR(),16);

	GetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarDetailTypeNum,strTemp);
	strTemp.Trim();
	if (strTemp.IsEmpty())
	{
		CCarInfoSearchDlg::ShowOperateInfo("请输入发动机具体编号！");
		return;
	}
	strncpy(m_carTypeInfo.csCarDetailTypeNum,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CustomerCode,strTemp);
	strTemp.Trim();
	strncpy(m_carTypeInfo.csCustomerCode,strTemp.operator LPCSTR(),16);

	GetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarFactory,strTemp);
	strTemp.Trim();
	strncpy(m_carTypeInfo.csCarFactory,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarType,strTemp);
	strTemp.Trim();
	strncpy(m_carTypeInfo.csCarType,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarName,strTemp);
	strTemp.Trim();
	strncpy(m_carTypeInfo.csCarName,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarPattern,strTemp);
	strTemp.Trim();
	strncpy(m_carTypeInfo.csCarPattern,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_AS_TYPE_ADD_EnginePattern,strTemp);
	strTemp.Trim();
	strncpy(m_carTypeInfo.csEnginePattern,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_AS_TYPE_ADD_MarkModel,strTemp);
	strTemp.Trim();
	strncpy(m_carTypeInfo.csMarkModel,strTemp.operator LPCSTR(),16);

	GetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarNotes,strTemp);
	strTemp.Trim();
	m_carTypeInfo.strCarNotes = strTemp.operator LPCSTR();

	if (OPERATE_TYPE_ADD == m_bOperateType)
	{
		if(OPERATE_DB_SUCCESS  == ASInsertCarTypeInfo(&m_carTypeInfo))
		{
			CCarInfoSearchDlg::ShowOperateInfo("插入机型信息成功！");

			SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_TypeNum,"");
			SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarDetailTypeNum,"");
			SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CustomerCode,"");
			SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarFactory,"");
			SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarType,"");
			SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarName,"");
			SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarPattern,"");
			SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_EnginePattern,"");
			SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_MarkModel,"");
			SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarNotes,"");
		}
		else
		{
			CCarInfoSearchDlg::ShowOperateInfo("插入机型信息失败！可能该信息已经存在！");
		}
	}
	else if (OPERATE_TYPE_MODIFY == m_bOperateType)
	{
		if(OPERATE_DB_SUCCESS == ASUpdateCarTypeInfo(&m_carTypeInfo))
		{
			CCarInfoSearchDlg::ShowOperateInfo("修改机型信息成功！");
			g_pMainDlg->RightPageShow(IDD_DIALOG_AS_QUERY_TYPE,true);
		}
		else
		{
			CCarInfoSearchDlg::ShowOperateInfo("修改机型信息失败！可能是无该记录!");
		}
	}
}

void CASModifyTypeDlg::SetOperateType(BYTE bType,PASCarTypeTableInfo pInfo/*=NULL*/)
{
	m_bOperateType = bType;
	m_carTypeInfo.Clear();

	switch(bType)
	{
	case OPERATE_TYPE_ADD:
		{
			SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_TypeNum,"");
			SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarDetailTypeNum,"");
			SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CustomerCode,"");
			SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarFactory,"");
			SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarType,"");
			SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarName,"");
			SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarPattern,"");
			SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_EnginePattern,"");
			SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_MarkModel,"");
			SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarNotes,"");

			m_modifyAddButton.SetWindowText("增加\nAdd");
			m_modifyAddButton.ShowWindow(SW_SHOW);
			m_modifyReturnButton.ShowWindow(SW_HIDE);
			((CEdit*)GetDlgItem(IDC_EDIT_AS_TYPE_ADD_CarDetailTypeNum))->SetReadOnly(FALSE);
		}
		break;
	case OPERATE_TYPE_MODIFY:
	case OPERATE_TYPE_SHOW:
	case OPERATE_TYPE_SHOW_EX:
		SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_TypeNum,pInfo->csCarTypeNum);
		SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarDetailTypeNum,pInfo->csCarDetailTypeNum);
		SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CustomerCode,pInfo->csCustomerCode);
		SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarFactory,pInfo->csCarFactory);
		SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarType,pInfo->csCarType);
		SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarName,pInfo->csCarName);
		SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarPattern,pInfo->csCarPattern);
		SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_EnginePattern,pInfo->csEnginePattern);
		SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_MarkModel,pInfo->csMarkModel);
		SetDlgItemText(IDC_EDIT_AS_TYPE_ADD_CarNotes,pInfo->strCarNotes.c_str());

		m_modifyReturnButton.ShowWindow(SW_SHOW);
		((CEdit*)GetDlgItem(IDC_EDIT_AS_TYPE_ADD_CarDetailTypeNum))->SetReadOnly(TRUE);

		if(OPERATE_TYPE_MODIFY == m_bOperateType)
		{
			m_modifyAddButton.SetWindowText("修改\nModify");
			m_modifyAddButton.ShowWindow(SW_SHOW);
		}
		else
		{
			m_modifyAddButton.ShowWindow(SW_HIDE);
		}

		break;
	}
}

void CASModifyTypeDlg::OnBnClickedButtonAsTypeReturn()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	if (OPERATE_TYPE_MODIFY == m_bOperateType)
	{
		if(IDYES== MessageBox("确定要放弃修改数据?\nWhether to give up modification?","提示(Notify)",MB_YESNO))
		{
			g_pMainDlg->RightPageShow(IDD_DIALOG_AS_QUERY_TYPE);
		}
	}
	else if (OPERATE_TYPE_SHOW == m_bOperateType)
	{
		g_pMainDlg->RightPageShow(IDD_DIALOG_AS_QUERY_TYPE);		
	}
	else
	{
		g_pMainDlg->RightPageShow(IDD_DIALOG_AS_QUERY_MULTIL);
	}
}
