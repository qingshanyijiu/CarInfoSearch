// QueryCarTypePartsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CarInfoSearch.h"
#include "CarInfoSearchDlg.h"
#include "QueryFileInfoDlg.h"
#include "FileModifyDlg.h"
#include "afxdialogex.h"

extern CCarInfoSearchDlg*	g_pMainDlg;


// CQueryFileInfoDlg 对话框

IMPLEMENT_DYNAMIC(CQueryFileInfoDlg, CDialogEx)

CQueryFileInfoDlg::CQueryFileInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQueryFileInfoDlg::IDD, pParent)
{

}

CQueryFileInfoDlg::~CQueryFileInfoDlg()
{
}

void CQueryFileInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FILE_QUERY, m_fileInfoList);
}


BEGIN_MESSAGE_MAP(CQueryFileInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_FILE_SEARCH, &CQueryFileInfoDlg::OnBnClickedButtonFileSearch)
	ON_BN_CLICKED(IDC_BUTTON_FILE_QUERY_Before, &CQueryFileInfoDlg::OnBnClickedButtonFileBefore)
	ON_BN_CLICKED(IDC_BUTTON_FILE_QUERY_Next, &CQueryFileInfoDlg::OnBnClickedButtonFileNext)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_FILE_QUERY, &CQueryFileInfoDlg::OnRclickListFileInfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FILE_QUERY, &CQueryFileInfoDlg::OnDblclkLisFileInfo)
	ON_COMMAND(ID_SMENU_FILE_OPEN, &CQueryFileInfoDlg::OnSmenuFileOpen)
	ON_COMMAND(ID_SMENU_FILE_Detail, &CQueryFileInfoDlg::OnSmenuFileDetail)
	ON_COMMAND(ID_SMENU_FILE_MODIFY, &CQueryFileInfoDlg::OnSmenuFileModify)
	ON_COMMAND(ID_SMENU_FILE_DELETE, &CQueryFileInfoDlg::OnSmenuFileDelete)
END_MESSAGE_MAP()


// CQueryFileInfoDlg 消息处理程序


BOOL CQueryFileInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯

	LONG lStyle;
	lStyle = GetWindowLong(m_fileInfoList.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_fileInfoList.m_hWnd, GWL_STYLE, lStyle);//设置style
	DWORD dwStyle = m_fileInfoList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_fileInfoList.SetExtendedStyle(dwStyle); //设置扩展风格
	m_fileInfoList.InsertColumn( 0, "文件名", LVCFMT_LEFT, 400 );
	m_fileInfoList.InsertColumn( 1, "机型编号", LVCFMT_LEFT, 150 );
	m_fileInfoList.InsertColumn( 3, "备注", LVCFMT_LEFT, 300 );

	HIMAGELIST himlSmall;
	HIMAGELIST himlLarge;
	SHFILEINFO sfi;
	char  cSysDir[MAX_PATH];
	CString  strBuf;

	memset(cSysDir, 0, MAX_PATH);

	GetWindowsDirectory(cSysDir, MAX_PATH);
	strBuf = cSysDir;
	sprintf(cSysDir, "%s", strBuf.Left(strBuf.Find("//")+1));

	himlSmall = (HIMAGELIST)SHGetFileInfo ((LPCSTR)cSysDir, 
		0, 
		&sfi,
		sizeof(SHFILEINFO), 
		SHGFI_SYSICONINDEX | SHGFI_SMALLICON );

	himlLarge = (HIMAGELIST)SHGetFileInfo((LPCSTR)cSysDir, 
		0, 
		&sfi, 
		sizeof(SHFILEINFO), 
		SHGFI_SYSICONINDEX | SHGFI_LARGEICON);

	if (himlSmall && himlLarge)
	{
		::SendMessage(m_fileInfoList.m_hWnd, LVM_SETIMAGELIST,
			(WPARAM)LVSIL_SMALL, (LPARAM)himlSmall);
		::SendMessage(m_fileInfoList.m_hWnd, LVM_SETIMAGELIST,
			(WPARAM)LVSIL_NORMAL, (LPARAM)himlLarge);
	}

	m_iTotalRecord = 0;
	m_curPage = 0;
	m_carFileDataVect.reserve(MAX_QUERY_COUNT);

	OnBnClickedButtonFileSearch();

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}


BOOL CQueryFileInfoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà

	// TODO: Add your specialized code here and/or call the base class
	// 把Esc和Enter按键事件消息过滤掉，否则该消息会导致对应应用程序调用OnOK（）方法，结束应用程序
	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_ESCAPE: //Esc按键事件
			return true;
		case VK_RETURN: //Enter按键事件
			OnBnClickedButtonFileSearch();
			return true;
		default:
			;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CQueryFileInfoDlg::OnBnClickedButtonFileSearch()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	CString strTemp;
	m_queryInfo.Clear();

	GetDlgItemText(IDC_EDIT_FILE_QUERY_NAME,strTemp);
	strTemp.Trim();
	m_queryInfo.strFileName =  strTemp.operator LPCSTR();

	GetDlgItemText(IDC_EDIT_FILE_QUERY_TYPENUM,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csCarTypeNum,strTemp.operator LPCSTR(),16);

	GetDlgItemText(IDC_EDIT_FILE_QUERY_NOTES,strTemp);
	strTemp.Trim();
	m_queryInfo.strNotes = strTemp.operator LPCSTR();

	m_curPage = 0;
	m_carFileDataVect.clear();

	if (OPERATE_DB_SUCCESS == GetCarFileDataCount(&m_queryInfo,&m_iTotalRecord))
	{
		CCarInfoSearchDlg::ShowSearchRecord(m_iTotalRecord,m_curPage+1);
		if (m_iTotalRecord)
		{
			if (OPERATE_DB_SUCCESS == GetCarFileData(&m_queryInfo,
				m_curPage,
				MAX_QUERY_COUNT,
				m_carFileDataVect,
				true))
			{
				CCarInfoSearchDlg::ShowOperateInfo("查询成功！");
				UpdateDataInfo();
			}
			else
			{
				CCarInfoSearchDlg::ShowOperateInfo("查询失败！");
			}


			CCarInfoSearchDlg::ShowSearchRecord(m_iTotalRecord,m_curPage+1);
		}
		else
		{
			CCarInfoSearchDlg::ShowOperateInfo("查询成功,但未查到相关记录！");
			UpdateDataInfo();
		}
	}
	else
	{
		CCarInfoSearchDlg::ShowOperateInfo("查询失败！");
	}
}


void CQueryFileInfoDlg::OnBnClickedButtonFileBefore()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	if (m_curPage)
	{
		m_carFileDataVect.clear();
		--m_curPage;
		if (OPERATE_DB_SUCCESS ==  GetCarFileData(&m_queryInfo,
			m_curPage,
			MAX_QUERY_COUNT,
			m_carFileDataVect,
			true))
		{
			CCarInfoSearchDlg::ShowOperateInfo("查询上一页成功！");
			UpdateDataInfo();
		}
		else
		{
			++m_curPage;
			CCarInfoSearchDlg::ShowOperateInfo("查询上一页失败！");
		}
		CCarInfoSearchDlg::ShowSearchRecord(m_iTotalRecord,m_curPage+1);
	}
	else
	{
		CCarInfoSearchDlg::ShowOperateInfo("没有上一页，不能查询！");
	}
}


void CQueryFileInfoDlg::OnBnClickedButtonFileNext()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	int iTotalPage = (m_iTotalRecord/MAX_QUERY_COUNT)+(m_iTotalRecord%MAX_QUERY_COUNT?1:0);
	if (m_curPage+1<iTotalPage)
	{
		m_carFileDataVect.clear();
		++m_curPage;
		if (OPERATE_DB_SUCCESS ==  GetCarFileData(&m_queryInfo,
			m_curPage,
			MAX_QUERY_COUNT,
			m_carFileDataVect,
			true))
		{
			CCarInfoSearchDlg::ShowOperateInfo("查询下一页成功！");
			UpdateDataInfo();
		}
		else
		{
			--m_curPage;
			CCarInfoSearchDlg::ShowOperateInfo("查询下一页失败！");
		}
		CCarInfoSearchDlg::ShowSearchRecord(m_iTotalRecord,m_curPage+1);
	}
	else
	{
		CCarInfoSearchDlg::ShowOperateInfo("没有下一页，不能查询！");
	}
}


void CQueryFileInfoDlg::OnRclickListFileInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	if(m_fileInfoList.GetSelectedCount()>0)
	{
		NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
		if(pNMListView->iItem != -1)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
			CMenu menu;
			VERIFY( menu.LoadMenu( IDR_MENU_CarFileMenu ) );
			CMenu* popup = menu.GetSubMenu(0);
			ASSERT( popup != NULL );
			popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );
		}
	}

	*pResult = 0;
}


void CQueryFileInfoDlg::OnDblclkLisFileInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	CQueryFileInfoDlg::OnSmenuFileOpen();

	*pResult = 0;
}

int CQueryFileInfoDlg::GetIconIndex(LPCTSTR lpszPath, BOOL bIsDir, BOOL bSelected)
{
	SHFILEINFO sfi;
	memset(&sfi, 0, sizeof(sfi));

	if (bIsDir)
	{
		SHGetFileInfo(lpszPath, 
			FILE_ATTRIBUTE_DIRECTORY, 
			&sfi, 
			sizeof(sfi), 
			SHGFI_SMALLICON | SHGFI_SYSICONINDEX |
			SHGFI_USEFILEATTRIBUTES |(bSelected ? SHGFI_OPENICON : 0)); 
		return  sfi.iIcon;
	}
	else
	{
		SHGetFileInfo (lpszPath, 
			FILE_ATTRIBUTE_NORMAL, 
			&sfi, 
			sizeof(sfi), 
			SHGFI_SMALLICON | SHGFI_SYSICONINDEX | 
			SHGFI_USEFILEATTRIBUTES | (bSelected ? SHGFI_OPENICON : 0));
		return   sfi.iIcon;
	}
	return  -1;
}

void CQueryFileInfoDlg::UpdateDataInfo()
{
	m_fileInfoList.SetRedraw(FALSE);
	//更新内容
	m_fileInfoList.DeleteAllItems();

	int nRow,nIcon;
	CString strTemp;
	for(int i = 0 ; i < m_carFileDataVect.size() ; ++i) 
	{ 
		strTemp = CFileModifyDlg::s_fileSavePath;
		strTemp += m_carFileDataVect[i].strFileName.c_str();

		nIcon = GetIconIndex(strTemp, FALSE, FALSE);

		nRow = m_fileInfoList.InsertItem(i, m_carFileDataVect[i].strFileName.c_str(), nIcon);
		m_fileInfoList.SetItemText(nRow, 1, m_carFileDataVect[i].csCarTypeNum);//设置数据
		m_fileInfoList.SetItemText(nRow, 2, m_carFileDataVect[i].strNotes.c_str());
	} 

	m_fileInfoList.SetRedraw(TRUE);
	m_fileInfoList.Invalidate();
	m_fileInfoList.UpdateWindow();
}

void CQueryFileInfoDlg::OnSmenuFileOpen()
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌÐò´úÂë
	if(g_pMainDlg == NULL || m_fileInfoList.GetSelectedCount()<=0)
		return;
	int selectIndex = m_fileInfoList.GetSelectionMark();

	CString strTemp = CFileModifyDlg::s_fileSavePath;
	strTemp += m_fileInfoList.GetItemText(selectIndex,0);

	ShellExecute(NULL,"open",strTemp,NULL,NULL,SW_NORMAL );
}

void CQueryFileInfoDlg::OnSmenuFileDetail()
{
	if(g_pMainDlg == NULL || m_fileInfoList.GetSelectedCount()<=0)
		return;
	int selectIndex = m_fileInfoList.GetSelectionMark();

	((CFileModifyDlg*)(g_pMainDlg->m_pages[IDD_DIALOG_FILE_MODIFY]))->SetOperateType(OPERATE_TYPE_SHOW,&m_carFileDataVect[selectIndex]);
	g_pMainDlg->RightPageShow(IDD_DIALOG_FILE_MODIFY);
	CCarInfoSearchDlg::ShowOperateInfo("查看车型资料信息 - 详细内容！");
}


void CQueryFileInfoDlg::OnSmenuFileModify()
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌÐò´úÂë
	if (!(CCarInfoSearchDlg::s_dwUserPower&USER_POWER_MODIFY))
	{
		CCarInfoSearchDlg::ShowOperateInfo("对不起，您没有操作权限！");
		return;
	}

	if(g_pMainDlg == NULL || m_fileInfoList.GetSelectedCount()<=0)
		return;
	int selectIndex = m_fileInfoList.GetSelectionMark();

	((CFileModifyDlg*)(g_pMainDlg->m_pages[IDD_DIALOG_FILE_MODIFY]))->SetOperateType(OPERATE_TYPE_MODIFY,&m_carFileDataVect[selectIndex]);
	g_pMainDlg->RightPageShow(IDD_DIALOG_FILE_MODIFY);
	CCarInfoSearchDlg::ShowOperateInfo("修改车型资料信息 - 详细内容！");
}


void CQueryFileInfoDlg::OnSmenuFileDelete()
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌÐò´úÂë

	if (!(CCarInfoSearchDlg::s_dwUserPower&USER_POWER_MODIFY))
	{
		CCarInfoSearchDlg::ShowOperateInfo("对不起，您没有操作权限！");
		return;
	}

	int selectIndex = m_fileInfoList.GetSelectionMark();
	if(selectIndex<0)
		return;
	if(IDYES== MessageBox("是否删除当前选中的车型资料信息?","提示",MB_YESNO))
	{
		CString strName = m_fileInfoList.GetItemText(selectIndex,0);
		if(OPERATE_DB_SUCCESS == DeleteCarFileData(strName))
		{
			strName = CFileModifyDlg::s_fileSavePath+strName;
			DeleteFile(strName);
			m_fileInfoList.DeleteItem(selectIndex);
			CCarInfoSearchDlg::ShowOperateInfo("车型资料信息删除成功！");
		}
		else
		{
			CCarInfoSearchDlg::ShowOperateInfo("车型资料信息删除失败！");
		}
	}
}


LRESULT CQueryFileInfoDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà

	if (WM_USER_UPDATE == message)
	{
		m_carFileDataVect.clear();
		GetCarFileData(&m_queryInfo,m_curPage,MAX_QUERY_COUNT,m_carFileDataVect,true);
		UpdateDataInfo();

		return TRUE;
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}
