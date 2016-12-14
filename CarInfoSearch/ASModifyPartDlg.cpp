// ASModifyPartDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CarInfoSearch.h"
#include "ASModifyPartDlg.h"
#include "CarInfoSearchDlg.h"
#include "afxdialogex.h"

extern CCarInfoSearchDlg*	g_pMainDlg;

// CASModifyPartDlg 对话框

IMPLEMENT_DYNAMIC(CASModifyPartDlg, CDialogEx)

CASModifyPartDlg::CASModifyPartDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CASModifyPartDlg::IDD, pParent)
{

}

CASModifyPartDlg::~CASModifyPartDlg()
{
}

void CASModifyPartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_AS_PART_ADD, m_addModifyButton);
	DDX_Control(pDX, IDC_BUTTON_AS_PART_RETURN, m_modifyReturnButton);
}


BEGIN_MESSAGE_MAP(CASModifyPartDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_AS_PART_ADD, &CASModifyPartDlg::OnBnClickedButtonAsPartAdd)
	ON_BN_CLICKED(IDC_BUTTON_AS_PART_RETURN, &CASModifyPartDlg::OnBnClickedButtonAsPartReturn)
END_MESSAGE_MAP()


// CASModifyPartDlg 消息处理程序


BOOL CASModifyPartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯

	m_modifyReturnButton.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}


BOOL CASModifyPartDlg::PreTranslateMessage(MSG* pMsg)
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


void CASModifyPartDlg::OnBnClickedButtonAsPartAdd()
{
	CString	strTemp;
	m_carPartInfo.Clear();

	GetDlgItemText(IDC_EDIT_AS_PART_ADD_TypeNum,strTemp);
	strTemp.Trim();
	if (strTemp.IsEmpty())
	{
		CCarInfoSearchDlg::ShowOperateInfo("请输入机型编号！");
		return;
	}
	strncpy(m_carPartInfo.csCarTypeNum,strTemp.operator LPCSTR(),16);

	GetDlgItemText(IDC_EDIT_AS_PART_ADD_PartNum,strTemp);
	strTemp.Trim();	
	if (strTemp.IsEmpty())
	{
		CCarInfoSearchDlg::ShowOperateInfo("请输入零件代号！");
		return;
	}
	strncpy(m_carPartInfo.csPartNum,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_AS_PART_ADD_WholeNum,strTemp);
	strTemp.Trim();
	strncpy(m_carPartInfo.csWholeNum,strTemp.operator LPCSTR(),16);

	GetDlgItemText(IDC_EDIT_AS_PART_ADD_WholeEngName,strTemp);
	strTemp.Trim();
	strncpy(m_carPartInfo.csWholeEngName,strTemp.operator LPCSTR(),64);

	GetDlgItemText(IDC_EDIT_AS_PART_ADD_WholeChinName,strTemp);
	strTemp.Trim();
	strncpy(m_carPartInfo.csWholeChinName,strTemp.operator LPCSTR(),64);

	GetDlgItemText(IDC_EDIT_AS_PART_ADD_ItemNum,strTemp);
	strTemp.Trim();
	strncpy(m_carPartInfo.csItemNum,strTemp.operator LPCSTR(),16);

	GetDlgItemText(IDC_EDIT_AS_PART_ADD_EngName,strTemp);
	strTemp.Trim();
	strncpy(m_carPartInfo.csEngName,strTemp.operator LPCSTR(),64);

	GetDlgItemText(IDC_EDIT_AS_PART_ADD_ChinName,strTemp);
	strTemp.Trim();
	strncpy(m_carPartInfo.csChinName,strTemp.operator LPCSTR(),64);

	GetDlgItemText(IDC_EDIT_AS_PART_ADD_Remark,strTemp);
	strTemp.Trim();
	m_carPartInfo.strRemark = strTemp;

	if (OPERATE_TYPE_ADD == m_bOperateType)
	{
		if(OPERATE_DB_SUCCESS  == ASInsertCarPartInfo(&m_carPartInfo))
		{
			CCarInfoSearchDlg::ShowOperateInfo("插入零件信息成功！");

			if(IDYES== MessageBox("\t   现在是否需要增加\n\r\t支持该零件的发动机信息?\n\t Now whether to add type info support this part?","提示(Notify)",MB_YESNO))
			{
				m_queryTypeDlg.SetCartPartInfo(&m_carPartInfo,OPERATE_TYPE_ADD);
				m_queryTypeDlg.DoModal();
			}

			SetDlgItemText(IDC_EDIT_AS_PART_ADD_TypeNum,"");
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_PartNum,"");
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_WholeNum,"");
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_WholeEngName,"");
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_WholeChinName,"");
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_ItemNum,"");
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_EngName,"");
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_ChinName,"");
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_Remark,"");
		}
		else
		{
			CCarInfoSearchDlg::ShowOperateInfo("插入零件信息失败！可能该信息已经存在！");
		}
	}
	else if (OPERATE_TYPE_MODIFY == m_bOperateType)
	{
		if(OPERATE_DB_SUCCESS ==ASUpdateCarPartInfo(&m_carPartInfo))
		{
			CCarInfoSearchDlg::ShowOperateInfo("修改零件信息成功！");

			if(IDYES== MessageBox("\t  现在是否需要修改\n\r\t支持该零件的发动机信息?\n\tNow whether to give up modify the types? ","提示(Notify)",MB_YESNO))
			{
				m_queryTypeDlg.SetCartPartInfo(&m_carPartInfo,OPERATE_TYPE_MODIFY);
				m_queryTypeDlg.DoModal();
			}

			g_pMainDlg->RightPageShow(IDD_DIALOG_AS_QUERY_PART,true);
		}
		else
		{
			CCarInfoSearchDlg::ShowOperateInfo("修改零件信息失败！可能是无该记录!");
		}
	}
}
void CASModifyPartDlg::SetOperateType(BYTE bType,PASCarPartTableInfo pInfo/*=NULL*/)
{
	m_bOperateType = bType;
	m_carPartInfo.Clear();
	if(pInfo != NULL)
		m_carPartInfo.Copy(*pInfo);

	switch(bType)
	{
	case OPERATE_TYPE_ADD:
		{
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_TypeNum,"");
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_PartNum,"");
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_WholeNum,"");
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_WholeEngName,"");
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_WholeChinName,"");
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_ItemNum,"");
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_EngName,"");
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_ChinName,"");
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_Remark,"");

			m_addModifyButton.SetWindowText("增加\nAdd");
			m_addModifyButton.ShowWindow(SW_SHOW);
			m_modifyReturnButton.ShowWindow(SW_HIDE);

			((CEdit*)GetDlgItem(IDC_EDIT_AS_PART_ADD_TypeNum))->SetReadOnly(FALSE);
			((CEdit*)GetDlgItem(IDC_EDIT_AS_PART_ADD_PartNum))->SetReadOnly(FALSE);
		}
		break;
	case OPERATE_TYPE_MODIFY:
	case OPERATE_TYPE_SHOW:
	case OPERATE_TYPE_SHOW_EX:
		{
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_TypeNum,pInfo->csCarTypeNum);
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_PartNum,pInfo->csPartNum);
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_WholeNum,pInfo->csWholeNum);
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_WholeEngName,pInfo->csWholeEngName);
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_WholeChinName,pInfo->csWholeChinName);
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_ItemNum,pInfo->csItemNum);
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_EngName,pInfo->csEngName);
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_ChinName,pInfo->csChinName);
			SetDlgItemText(IDC_EDIT_AS_PART_ADD_Remark,pInfo->strRemark.c_str());

			m_modifyReturnButton.ShowWindow(SW_SHOW);

			((CEdit*)GetDlgItem(IDC_EDIT_AS_PART_ADD_TypeNum))->SetReadOnly(TRUE);
			((CEdit*)GetDlgItem(IDC_EDIT_AS_PART_ADD_PartNum))->SetReadOnly(TRUE);


			if(OPERATE_TYPE_MODIFY == m_bOperateType)
			{
				m_addModifyButton.ShowWindow(SW_SHOW);
				m_addModifyButton.SetWindowText("修改\nModify");
			}
			else
			{
				m_addModifyButton.ShowWindow(SW_HIDE);
			}
		}

		break;
	}
}


void CASModifyPartDlg::OnBnClickedButtonAsPartReturn()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	if (OPERATE_TYPE_MODIFY == m_bOperateType)
	{
		if(IDYES== MessageBox("确定要放弃修改数据?\nWhether to give up modification?","提示(Notify)",MB_YESNO))
		{
			g_pMainDlg->RightPageShow(IDD_DIALOG_AS_QUERY_PART);
		}
	}
	else if (OPERATE_TYPE_SHOW == m_bOperateType)
	{
		g_pMainDlg->RightPageShow(IDD_DIALOG_AS_QUERY_PART);
	}
	else
	{
		g_pMainDlg->RightPageShow(IDD_DIALOG_AS_QUERY_MULTIL);
	}
}
