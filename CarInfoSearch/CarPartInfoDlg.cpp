// CarPartInfoDlg.cpp : implementation file
//
#include "stdafx.h"
#include "CarInfoSearch.h"
#include "CarPartInfoDlg.h"
#include "afxdialogex.h"
#include "CarInfoSearchDlg.h"
extern CCarInfoSearchDlg*	g_pMainDlg;
// CCarPartInfoDlg dialog
IMPLEMENT_DYNAMIC(CCarPartInfoDlg, CDialogEx)
CCarPartInfoDlg::CCarPartInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCarPartInfoDlg::IDD, pParent)
{
}
CCarPartInfoDlg::~CCarPartInfoDlg()
{
}
void CCarPartInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_CarPartAdd, m_AddModifyButton);
	DDX_Control(pDX, IDC_BUTTON_CP_MODIFY_RETURN, m_modifyReturnButton);
	DDX_Control(pDX, IDC_EDIT_CP_ADD_CarTypeNum, m_editCarTypeNum);
	DDX_Control(pDX, IDC_EDIT_CP_ADD_ChineseName, m_editChineseName);
	DDX_Control(pDX, IDC_EDIT_CP_ADD_DAENum, m_editDAENum);
	DDX_Control(pDX, IDC_EDIT_CP_ADD_EnglishName, m_editEnglishName);
	DDX_Control(pDX, IDC_EDIT_CP_ADD_EPLNum, m_editEPLNum);
	DDX_Control(pDX, IDC_EDIT_CP_ADD_InstallMark, m_editInstallMark);
	DDX_Control(pDX, IDC_EDIT_CP_ADD_InstallNum, m_editInstallNum);
	DDX_Control(pDX, IDC_EDIT_CP_ADD_Level, m_editLevel);
	DDX_Control(pDX, IDC_EDIT_CP_ADD_MMCNum, m_editMMCNum);
	DDX_Control(pDX, IDC_EDIT_CP_ADD_PicNum, m_editPicNum);
	DDX_Control(pDX, IDC_EDIT_CP_ADD_VCNum, m_editVCNum);
}
BEGIN_MESSAGE_MAP(CCarPartInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_CarPartAdd, &CCarPartInfoDlg::OnBnClickedBtnCarPartadd)
	ON_BN_CLICKED(IDC_BUTTON_CP_MODIFY_RETURN, &CCarPartInfoDlg::OnBnClickedButtonCpModifyReturn)
END_MESSAGE_MAP()
// CCarPartInfoDlg message handlers
void CCarPartInfoDlg::OnBnClickedBtnCarPartadd()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	CString	strTemp;
	m_CarPartInfo.Clear();

	GetDlgItemText(IDC_EDIT_CP_ADD_CarTypeNum,strTemp);
	strTemp.Trim();
	if (strTemp.IsEmpty())
	{
		CCarInfoSearchDlg::ShowOperateInfo("请输入机型编号！");
		return;
	}
	strncpy(m_CarPartInfo.csCarTypeNum,strTemp.operator LPCSTR(),16);

	GetDlgItemText(IDC_EDIT_CP_ADD_DAENum,strTemp);
	strTemp.Trim();
	strncpy(m_CarPartInfo.csDAENum,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_CP_ADD_MMCNum,strTemp);
	strTemp.Trim();
	strncpy(m_CarPartInfo.csMMCNum,strTemp.operator LPCSTR(),32);

	if (0==strlen(m_CarPartInfo.csDAENum)&&0==strlen(m_CarPartInfo.csMMCNum))
	{
		CCarInfoSearchDlg::ShowOperateInfo("请输入DAE件号或者MMC件号！");
		return;
	}

	GetDlgItemText(IDC_EDIT_CP_ADD_ChineseName,strTemp);
	strTemp.Trim();
	strncpy(m_CarPartInfo.csChineseName,strTemp.operator LPCSTR(),64);

	GetDlgItemText(IDC_EDIT_CP_ADD_EnglishName,strTemp);
	strTemp.Trim();
	strncpy(m_CarPartInfo.csEnglishName,strTemp.operator LPCSTR(),64);

	GetDlgItemText(IDC_EDIT_CP_ADD_EPLNum,strTemp);
	strTemp.Trim();
	strncpy(m_CarPartInfo.csEPLNum,strTemp.operator LPCSTR(),32);
	GetDlgItemText(IDC_EDIT_CP_ADD_VCNum,strTemp);
	strTemp.Trim();
	strncpy(m_CarPartInfo.csVCNum,strTemp.operator LPCSTR(),16);

	GetDlgItemText(IDC_EDIT_CP_ADD_Level,strTemp);
	strTemp.Trim();
	m_CarPartInfo.iLevel = atoi(strTemp.operator LPCSTR());

	GetDlgItemText(IDC_EDIT_CP_ADD_PicNum,strTemp);
	strTemp.Trim();
	strncpy(m_CarPartInfo.csPicNum,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_CP_ADD_InstallMark,strTemp);
	strTemp.Trim();
	m_CarPartInfo.iInstallMark = atoi(strTemp.operator LPCSTR());

	GetDlgItemText(IDC_EDIT_CP_ADD_InstallNum,strTemp);
	strTemp.Trim();
	strncpy(m_CarPartInfo.csInstallNum,strTemp.operator LPCSTR(),32);

	if (OPERATE_TYPE_ADD == m_bOperateType)
	{
		if(OPERATE_DB_SUCCESS  ==InsertCarPartInfo(&m_CarPartInfo))
		{
			CCarInfoSearchDlg::ShowOperateInfo("插入零件信息成功！");

			if(IDYES== MessageBox("\t   现在是否需要增加\n\r\t支持该零件的发动机信息?","提示",MB_YESNO))
			{
				m_queryTypeDlg.SetCartPartInfo(&m_CarPartInfo,OPERATE_TYPE_ADD);
				m_queryTypeDlg.DoModal();
			}

			m_editCarTypeNum.SetWindowText("");
			m_editChineseName.SetWindowText("");
			m_editDAENum.SetWindowText("");
			m_editEnglishName.SetWindowText("");
			m_editEPLNum.SetWindowText("");
			m_editInstallMark.SetWindowText("");
			m_editInstallNum.SetWindowText("");
			m_editLevel.SetWindowText("");
			m_editMMCNum.SetWindowText("");
			m_editPicNum.SetWindowText("");
			m_editVCNum.SetWindowText("");
		}
		else
		{
			CCarInfoSearchDlg::ShowOperateInfo("插入零件信息失败！可能该信息已经存在！");
		}
	}
	else if (OPERATE_TYPE_MODIFY == m_bOperateType)
	{
		if(OPERATE_DB_SUCCESS ==UpdateCarPartInfo(&m_CarPartInfo))
		{
			CCarInfoSearchDlg::ShowOperateInfo("修改零件信息成功！");

			if(IDYES== MessageBox("\t   现在是否需要修改\n\r\t支持该零件的发动机信息?","提示",MB_YESNO))
			{
				m_queryTypeDlg.SetCartPartInfo(&m_CarPartInfo,OPERATE_TYPE_MODIFY);
				m_queryTypeDlg.DoModal();
			}

			g_pMainDlg->RightPageShow(IDD_MaintenanceMng_QUERY_Dlg,true);
		}
		else
		{
			CCarInfoSearchDlg::ShowOperateInfo("修改零件信息失败！可能是无该记录!");
		}
	}
}
void CCarPartInfoDlg::SetOperateType(BYTE bType,PCarPartTableInfo pInfo/*=NULL*/)
{
	m_bOperateType = bType;
	m_CarPartInfo.Clear();
	if(pInfo != NULL)
		m_CarPartInfo.Copy(*pInfo);

	switch(bType)
	{
	case OPERATE_TYPE_ADD:
		{
			m_editCarTypeNum.SetWindowText("");
			m_editChineseName.SetWindowText("");
			m_editDAENum.SetWindowText("");
			m_editEnglishName.SetWindowText("");
			m_editEPLNum.SetWindowText("");
			m_editInstallMark.SetWindowText("");
			m_editInstallNum.SetWindowText("");
			m_editLevel.SetWindowText("");
			m_editMMCNum.SetWindowText("");
			m_editPicNum.SetWindowText("");
			m_editVCNum.SetWindowText("");

			m_AddModifyButton.SetWindowText("增加");
			m_AddModifyButton.ShowWindow(SW_SHOW);
			m_modifyReturnButton.ShowWindow(SW_HIDE);

			m_editCarTypeNum.SetReadOnly(FALSE);
			m_editDAENum.SetReadOnly(FALSE);
			m_editMMCNum.SetReadOnly(FALSE);
		}
		break;
	case OPERATE_TYPE_MODIFY:
	case OPERATE_TYPE_SHOW:
	case OPERATE_TYPE_SHOW_EX:
		{
			m_editCarTypeNum.SetWindowText(pInfo->csCarTypeNum);
			m_editChineseName.SetWindowText(pInfo->csChineseName);
			m_editDAENum.SetWindowText(pInfo->csDAENum);
			m_editEnglishName.SetWindowText(pInfo->csEnglishName);
			m_editEPLNum.SetWindowText(pInfo->csEPLNum);
			CString strTemp;
			strTemp.Format("%d",pInfo->iInstallMark);
			m_editInstallMark.SetWindowText(strTemp);
			m_editInstallNum.SetWindowText(pInfo->csInstallNum);
			strTemp.Format("%d",pInfo->iLevel);
			m_editLevel.SetWindowText(strTemp);
			m_editMMCNum.SetWindowText(pInfo->csMMCNum);
			m_editPicNum.SetWindowText(pInfo->csPicNum);
			m_editVCNum.SetWindowText(pInfo->csVCNum);

			m_modifyReturnButton.ShowWindow(SW_SHOW);

			m_editCarTypeNum.SetReadOnly(TRUE);
			m_editDAENum.SetReadOnly(TRUE);
			m_editMMCNum.SetReadOnly(TRUE);


			if(OPERATE_TYPE_MODIFY == m_bOperateType)
			{
				m_AddModifyButton.ShowWindow(SW_SHOW);
				m_AddModifyButton.SetWindowText("修改");
			}
			else
			{
				m_AddModifyButton.ShowWindow(SW_HIDE);
			}
		}

		break;
	}
}
BOOL CCarPartInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯

	m_modifyReturnButton.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}
BOOL CCarPartInfoDlg::PreTranslateMessage(MSG* pMsg)
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


void CCarPartInfoDlg::OnBnClickedButtonSetsupptypes()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
}


void CCarPartInfoDlg::OnBnClickedButtonCpModifyReturn()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	if (OPERATE_TYPE_MODIFY == m_bOperateType)
	{
		if(IDYES== MessageBox("确定要放弃修改数据?","提示",MB_YESNO))
		{
			g_pMainDlg->RightPageShow(IDD_MaintenanceMng_QUERY_Dlg);
		}
	}
	else if (OPERATE_TYPE_SHOW == m_bOperateType)
	{
		g_pMainDlg->RightPageShow(IDD_MaintenanceMng_QUERY_Dlg);
	}
	else
	{
		g_pMainDlg->RightPageShow(IDD_DIALOG_CarTypeParts);
	}
}
