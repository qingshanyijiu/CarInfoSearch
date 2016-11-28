// FileModifyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CarInfoSearch.h"
#include "CarInfoSearchDlg.h"
#include "FileModifyDlg.h"
#include "afxdialogex.h"
#include <imagehlp.h>

extern CCarInfoSearchDlg*	g_pMainDlg;

#pragma comment(lib,"imagehlp.lib")

// CFileModifyDlg 对话框

IMPLEMENT_DYNAMIC(CFileModifyDlg, CDialogEx)


CString	CFileModifyDlg::s_fileSavePath;

CFileModifyDlg::CFileModifyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileModifyDlg::IDD, pParent)
{
	m_bOperateType = OPERATE_TYPE_ADD;
	m_carFileData.Clear();
}

CFileModifyDlg::~CFileModifyDlg()
{

}

void CFileModifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_FILE_ADD_SELECT, m_fileSelectButton);
	DDX_Control(pDX, IDC_BUTTON_FILE_RETURN, m_fileReturnButton);
	DDX_Control(pDX, IDC_BUTTON_FILE_MODIFY, m_fielModifyButton);
	DDX_Control(pDX, IDC_EDIT_FILE_ADD_FILEPATH, m_fileNameEdit);
}


BEGIN_MESSAGE_MAP(CFileModifyDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_FILE_ADD_SELECT, &CFileModifyDlg::OnBnClickedButtonFileAddSelect)
	ON_BN_CLICKED(IDC_BUTTON_FILE_MODIFY, &CFileModifyDlg::OnBnClickedButtonFileModify)
	ON_BN_CLICKED(IDC_BUTTON_FILE_RETURN, &CFileModifyDlg::OnBnClickedButtonFileReturn)
END_MESSAGE_MAP()


// CFileModifyDlg 消息处理程序


BOOL CFileModifyDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà

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


BOOL CFileModifyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯

	m_fielModifyButton.ShowWindow(SW_HIDE);

	s_fileSavePath = CCarInfoSearchDlg::s_curPath.c_str();
	s_fileSavePath += "SaveInfo\\Resource\\";

	MakeSureDirectoryPathExists(s_fileSavePath);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}


void CFileModifyDlg::OnBnClickedButtonFileAddSelect()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	CFileDialog aDlg(TRUE,NULL,"*.*");
	if(aDlg.DoModal()==IDCANCEL )
		return;
	CString strFilePath = aDlg.GetPathName();
	if (strFilePath.IsEmpty())
		return;

	SetDlgItemText(IDC_EDIT_FILE_ADD_FILEPATH,strFilePath);
}


void CFileModifyDlg::OnBnClickedButtonFileModify()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	CString	strTemp,strFilePath;
	m_carFileData.Clear();

	GetDlgItemText(IDC_EDIT_FILE_ADD_TYPENUM,strTemp);
	strTemp.Trim();
	if (strTemp.IsEmpty())
	{
		CCarInfoSearchDlg::ShowOperateInfo("请输入机型编号！");
		return;
	}
	strncpy(m_carFileData.csCarTypeNum,strTemp.operator LPCSTR(),16);

	GetDlgItemText(IDC_EDIT_FILE_ADD_FILEPATH,strFilePath);
	strFilePath.Trim();
	if (strFilePath.IsEmpty())
	{
		CCarInfoSearchDlg::ShowOperateInfo("请选择要上传的文件！");
		return;
	}
	int iPos = strFilePath.ReverseFind('\\');
	m_carFileData.strFileName = strFilePath.Mid(iPos+1,strFilePath.GetLength()-iPos-1).operator LPCSTR();

	GetDlgItemText(IDC_EDIT_FILE_ADD_NOTES,strTemp);
	strTemp.Trim();
	m_carFileData.strNotes = strTemp.operator LPCSTR();

	if (OPERATE_TYPE_ADD == m_bOperateType)
	{
		if(OPERATE_DB_SUCCESS  == InsertCarFileData(&m_carFileData))
		{
			CString strSaveFilePath = s_fileSavePath;
			strSaveFilePath += m_carFileData.strFileName.c_str();
			CopyFile(strFilePath,strSaveFilePath,FALSE);

			CCarInfoSearchDlg::ShowOperateInfo("插入机型资料成功！");

			GetDlgItem(IDC_EDIT_FILE_ADD_TYPENUM)->SetWindowText("");
			GetDlgItem(IDC_EDIT_FILE_ADD_FILEPATH)->SetWindowText("");
			GetDlgItem(IDC_EDIT_FILE_ADD_NOTES)->SetWindowText("");
		}
		else
		{
			CCarInfoSearchDlg::ShowOperateInfo("插入机型资料失败！可能该资料已经存在！");
		}
	}
	else if (OPERATE_TYPE_MODIFY == m_bOperateType)
	{
		if(OPERATE_DB_SUCCESS ==UpdateCarFileData(&m_carFileData))
		{
			CCarInfoSearchDlg::ShowOperateInfo("修改机型资料成功！");
			g_pMainDlg->RightPageShow(IDD_DIALOG_FILE_QUERY,true);
		}
		else
		{
			CCarInfoSearchDlg::ShowOperateInfo("修改机型资料失败！可能是无该记录!");
		}
	}
}

void CFileModifyDlg::SetOperateType(BYTE bType,PCarFileData pInfo)
{
	m_bOperateType = bType;
	m_carFileData.Clear();

	switch(bType)
	{
	case OPERATE_TYPE_ADD:
		{
			GetDlgItem(IDC_EDIT_FILE_ADD_TYPENUM)->SetWindowText("");
			GetDlgItem(IDC_EDIT_FILE_ADD_FILEPATH)->SetWindowText("");
			GetDlgItem(IDC_EDIT_FILE_ADD_NOTES)->SetWindowText("");

			m_fielModifyButton.SetWindowText("增加");
			m_fielModifyButton.ShowWindow(SW_SHOW);
			m_fileSelectButton.ShowWindow(SW_SHOW);
			m_fileReturnButton.ShowWindow(SW_HIDE);
			m_fileNameEdit.SetReadOnly(FALSE);
		}
		break;
	case OPERATE_TYPE_MODIFY:
	case OPERATE_TYPE_SHOW:
		{
			GetDlgItem(IDC_EDIT_FILE_ADD_TYPENUM)->SetWindowText(pInfo->csCarTypeNum);
			CString strFilePath = s_fileSavePath;
			strFilePath += pInfo->strFileName.c_str();
			GetDlgItem(IDC_EDIT_FILE_ADD_FILEPATH)->SetWindowText(strFilePath);
			GetDlgItem(IDC_EDIT_FILE_ADD_NOTES)->SetWindowText(pInfo->strNotes.c_str());

			m_fileReturnButton.ShowWindow(SW_SHOW);
			m_fileNameEdit.SetReadOnly(TRUE);
			m_fileSelectButton.ShowWindow(SW_HIDE);

			if(OPERATE_TYPE_MODIFY == m_bOperateType)
			{
				m_fielModifyButton.SetWindowText("修改");
				m_fielModifyButton.ShowWindow(SW_SHOW);
			}
			else
			{
				m_fielModifyButton.ShowWindow(SW_HIDE);
			}
		}
		break;
	}
}


void CFileModifyDlg::OnBnClickedButtonFileReturn()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	if (OPERATE_TYPE_MODIFY == m_bOperateType)
	{
		if(IDYES== MessageBox("确定要放弃修改数据?","提示",MB_YESNO))
		{
			g_pMainDlg->RightPageShow(IDD_DIALOG_FILE_QUERY);
		}
	}
	else 
	{
		g_pMainDlg->RightPageShow(IDD_DIALOG_FILE_QUERY);		
	}
}
