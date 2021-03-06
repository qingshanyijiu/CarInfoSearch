﻿// CarPartInfoQueryDlg.cpp : implementation file
//
#include "stdafx.h"
#include "CarInfoSearch.h"
#include "CarPartInfoQueryDlg.h"
#include "afxdialogex.h"
#include "CarInfoSearchDlg.h"
#include "CarPartInfoDlg.h"
#include "CarTypeMngQueryDlg.h"

extern CCarInfoSearchDlg*	g_pMainDlg;

// CCarPartInfoQueryDlg dialog
IMPLEMENT_DYNAMIC(CCarPartInfoQueryDlg, CDialogEx)
CCarPartInfoQueryDlg::CCarPartInfoQueryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCarPartInfoQueryDlg::IDD, pParent)
{
	m_curPage = 0;
}
CCarPartInfoQueryDlg::~CCarPartInfoQueryDlg()
{
}
void CCarPartInfoQueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CarPartList, m_CarPartinfolist);
}
BEGIN_MESSAGE_MAP(CCarPartInfoQueryDlg, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CarPartList, &CCarPartInfoQueryDlg::OnRclickListCarPartlist)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CarPartList, &CCarPartInfoQueryDlg::OnDblclkListCarPartlist)
	ON_COMMAND(ID_SMENU_CarPartDelete, &CCarPartInfoQueryDlg::OnSmenuCarPartdelete)
	ON_COMMAND(ID_SMENU_CarPartDetail, &CCarPartInfoQueryDlg::OnSmenuCarPartdetail)
	ON_COMMAND(ID_SMENU_CarPartModify, &CCarPartInfoQueryDlg::OnSmenuCarPartmodify)
	ON_COMMAND(ID_SMENU_CarPartQueryCarType, &CCarPartInfoQueryDlg::OnSmenuCarPartqueryCarType)
	ON_BN_CLICKED(IDC_BTN_MT_QCarPartInfo, &CCarPartInfoQueryDlg::OnBnClickedBtnMtQCarPartinfo)
	ON_BN_CLICKED(IDC_BUTTON_QCarPartBefore, &CCarPartInfoQueryDlg::OnBnClickedButtonQCarTypebefore)
	ON_BN_CLICKED(IDC_BUTTON_QCarPartNext, &CCarPartInfoQueryDlg::OnBnClickedButtonQCarTypenext)
	ON_COMMAND(ID_SMENU_CarPartModifyCarType, &CCarPartInfoQueryDlg::OnSmenuCarpartmodifycartype)
END_MESSAGE_MAP()
// CCarPartInfoQueryDlg message handlers
void CCarPartInfoQueryDlg::OnRclickListCarPartlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	if(m_CarPartinfolist.GetSelectedCount()>0)
	{
		NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
		if(pNMListView->iItem != -1)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
			CMenu menu;
			VERIFY( menu.LoadMenu( IDR_MENU_CarPartMenu ) );
			CMenu* popup = menu.GetSubMenu(0);
			ASSERT( popup != NULL );
			popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );
		}
	}
	
	*pResult = 0;
}
void CCarPartInfoQueryDlg::OnDblclkListCarPartlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	CCarPartInfoQueryDlg::OnSmenuCarPartdetail();
	*pResult = 0;
}
void CCarPartInfoQueryDlg::OnSmenuCarPartdelete()
{
	// TODO: Add your command handler code here
	if (!(CCarInfoSearchDlg::s_dwUserPower&USER_POWER_MODIFY))
	{
		CCarInfoSearchDlg::ShowOperateInfo("对不起，您没有操作权限！");
		return;
	}

	int selectIndex = m_CarPartinfolist.GetSelectionMark();
	if(selectIndex<0)
		return;
	if(IDYES== MessageBox("是否删除当前选中的零件信息?\nWhether to delete this record?","提示(Notify)",MB_YESNO))
	{
		CString strTemp;
		CarPartTableInfo tempInfo;
		strncpy(tempInfo.csCarTypeNum,m_CarPartinfolist.GetItemText(selectIndex,0).operator LPCSTR(),16);
		strncpy(tempInfo.csDAENum,m_CarPartinfolist.GetItemText(selectIndex,1).operator LPCSTR(),32);
		strncpy(tempInfo.csMMCNum,m_CarPartinfolist.GetItemText(selectIndex,2).operator LPCSTR(),32);

		if(OPERATE_DB_SUCCESS == DeleteCarPartInfo(&tempInfo))
		{
			m_CarPartinfolist.DeleteItem(selectIndex);
			CCarInfoSearchDlg::ShowOperateInfo("零件信息删除成功！");
		}
		else
		{
			CCarInfoSearchDlg::ShowOperateInfo("零件信息删除失败！");
		}
	}
}
void CCarPartInfoQueryDlg::OnSmenuCarPartdetail()
{
	// TODO: Add your command handler code here
	if(g_pMainDlg == NULL || m_CarPartinfolist.GetSelectedCount()<=0)
		return;
	int selectIndex = m_CarPartinfolist.GetSelectionMark();
	((CCarPartInfoDlg*)(g_pMainDlg->m_pages[IDD_MaintenanceMng_MODIFY_Dlg]))->SetOperateType(OPERATE_TYPE_SHOW,&m_CarPartInfoVect[selectIndex]);
	g_pMainDlg->RightPageShow(IDD_MaintenanceMng_MODIFY_Dlg);
	CCarInfoSearchDlg::ShowOperateInfo("查看零件信息 - 详细内容！");

}
void CCarPartInfoQueryDlg::OnSmenuCarPartmodify()
{
	// TODO: Add your command handler code here
	if (!(CCarInfoSearchDlg::s_dwUserPower&USER_POWER_MODIFY))
	{
		CCarInfoSearchDlg::ShowOperateInfo("对不起，您没有操作权限！");
		return;
	}

	if(g_pMainDlg == NULL || m_CarPartinfolist.GetSelectedCount()<=0)
		return;
	int selectIndex = m_CarPartinfolist.GetSelectionMark();
	((CCarPartInfoDlg*)(g_pMainDlg->m_pages[IDD_MaintenanceMng_MODIFY_Dlg]))->SetOperateType(OPERATE_TYPE_MODIFY,&m_CarPartInfoVect[selectIndex]);
	g_pMainDlg->RightPageShow(IDD_MaintenanceMng_MODIFY_Dlg);
	CCarInfoSearchDlg::ShowOperateInfo("修改零件信息 ！");
}
void CCarPartInfoQueryDlg::OnSmenuCarPartqueryCarType()
{
	// TODO: Add your command handler code here
	if(g_pMainDlg == NULL || m_CarPartinfolist.GetSelectedCount()<=0)
		return;
	int selectIndex = m_CarPartinfolist.GetSelectionMark();

	CString strTemp;
	CarPartTableInfo tempInfo;
	strncpy(tempInfo.csCarTypeNum,m_CarPartinfolist.GetItemText(selectIndex,0).operator LPCSTR(),16);
	strncpy(tempInfo.csDAENum,m_CarPartinfolist.GetItemText(selectIndex,1).operator LPCSTR(),32);
	strncpy(tempInfo.csMMCNum,m_CarPartinfolist.GetItemText(selectIndex,2).operator LPCSTR(),32);

	m_querySuppDlg.SetCartPartInfo(&tempInfo,OPERATE_TYPE_SHOW);
	m_querySuppDlg.DoModal();	

	m_CarPartinfolist.SetFocus();
}

BOOL CCarPartInfoQueryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  Add extra initialization here
	LONG lStyle;
	lStyle = GetWindowLong(m_CarPartinfolist.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_CarPartinfolist.m_hWnd, GWL_STYLE, lStyle);//设置style
	DWORD dwStyle = m_CarPartinfolist.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件

	int iWidth = m_CarPartinfolist.GetListWidth();
	m_CarPartinfolist.SetExtendedStyle(dwStyle); //设置扩展风格
	m_CarPartinfolist.InsertColumn( 0, "机型编号\nTypeNum", LVCFMT_LEFT, (int)(iWidth*0.07) );
	m_CarPartinfolist.InsertColumn( 1, "DAE件号\nDAE Num", LVCFMT_LEFT, (int)(iWidth*0.12) );
	m_CarPartinfolist.InsertColumn( 2, "MMC件号\nMMC Num", LVCFMT_LEFT, (int)(iWidth*0.11) );
	m_CarPartinfolist.InsertColumn( 3, "零件名称\nPartName", LVCFMT_LEFT,(int)(iWidth*0.13) );
	m_CarPartinfolist.InsertColumn( 4, "EPL号\nEPLNUM", LVCFMT_LEFT, (int)(iWidth*0.06) );
	m_CarPartinfolist.InsertColumn( 5, "VC号\nVCNum", LVCFMT_LEFT, (int)(iWidth*0.04) );
	m_CarPartinfolist.InsertColumn( 6, "级别\nLevel", LVCFMT_LEFT, (int)(iWidth*0.04) );
	m_CarPartinfolist.InsertColumn( 7, "英文名称\nEngName", LVCFMT_LEFT,(int)(iWidth*0.09) );
	m_CarPartinfolist.InsertColumn( 8, "参考图号\nDrawName", LVCFMT_LEFT, (int)(iWidth*0.11) );
	m_CarPartinfolist.InsertColumn( 9, "安装图号\nInsNum", LVCFMT_LEFT, (int)(iWidth*0.1) );
	m_CarPartinfolist.InsertColumn( 10, "安装记号\nInsMark", LVCFMT_LEFT, (int)(iWidth*0.06) );
	m_CarPartinfolist.InsertColumn( 11, "零件备注\nPartNotes", LVCFMT_LEFT, (int)(iWidth*0.08) );

	m_CarPartinfolist.InitHead();
	m_CarPartinfolist.SetMouseWheelCallFunc(std::tr1::bind(&CCarPartInfoQueryDlg::OnBnClickedButtonQCarTypebefore, this),
		std::tr1::bind(&CCarPartInfoQueryDlg::OnBnClickedButtonQCarTypenext, this));

	m_iTotalRecord=0;
	m_curPage = 0;

	m_CarPartInfoVect.reserve(MAX_QUERY_COUNT);
	OnBnClickedBtnMtQCarPartinfo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CCarPartInfoQueryDlg::OnBnClickedBtnMtQCarPartinfo()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	CString strTemp;
	m_queryInfo.Clear();

	GetDlgItemText(IDC_EDIT_CP_CarTypeNum,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csCarTypeNum,strTemp.operator LPCSTR(),16);

	GetDlgItemText(IDC_EDIT_CP_DAENum,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csDAENum,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_cP_MMCNum,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csMMCNum,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_CP_ChineseName,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csChineseName,strTemp.operator LPCSTR(),64)
		;
	GetDlgItemText(IDC_EDIT_CP_PicNum,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csPicNum,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_CP_PartNotes,strTemp);
	strTemp.Trim();
	m_queryInfo.strPartReserve = strTemp;
	
	m_curPage = 0;
	m_CarPartInfoVect.clear();

	if (OPERATE_DB_SUCCESS == GetCarPartCount(&m_queryInfo,&m_iTotalRecord))
	{
		CCarInfoSearchDlg::ShowSearchRecord(m_iTotalRecord,m_curPage+1);
		if (m_iTotalRecord)
		{
			if (OPERATE_DB_SUCCESS == GetCarPartInfo(&m_queryInfo,
				m_curPage,
				MAX_QUERY_COUNT,
				m_CarPartInfoVect,
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

void CCarPartInfoQueryDlg::OnBnClickedButtonQCarTypebefore()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	if (m_curPage)
	{
		m_CarPartInfoVect.clear();
		--m_curPage;
		if (OPERATE_DB_SUCCESS == GetCarPartInfo(&m_queryInfo,
			m_curPage,
			MAX_QUERY_COUNT,
			m_CarPartInfoVect,
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
void CCarPartInfoQueryDlg::OnBnClickedButtonQCarTypenext()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	int iTotalPage = (m_iTotalRecord/MAX_QUERY_COUNT)+(m_iTotalRecord%MAX_QUERY_COUNT?1:0);
	if (m_curPage+1<iTotalPage)
	{
		m_CarPartInfoVect.clear();
		++m_curPage;
		if (OPERATE_DB_SUCCESS == GetCarPartInfo(&m_queryInfo,
			m_curPage,
			MAX_QUERY_COUNT,
			m_CarPartInfoVect,
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
void	CCarPartInfoQueryDlg::UpdateDataInfo()
{
	m_CarPartinfolist.SetRedraw(FALSE);
	//更新内容
	m_CarPartinfolist.DeleteAllItems();

	int nRow;
	CString strTemp;
	for(int i = 0 ; i < m_CarPartInfoVect.size() ; ++i) 
	{ 
		nRow = m_CarPartinfolist.InsertItem(i,m_CarPartInfoVect[i].csCarTypeNum);
		m_CarPartinfolist.SetItemText(nRow,1,m_CarPartInfoVect[i].csDAENum);
		m_CarPartinfolist.SetItemText(nRow,2,m_CarPartInfoVect[i].csMMCNum);
		m_CarPartinfolist.SetItemText(nRow,3,m_CarPartInfoVect[i].csChineseName);
		m_CarPartinfolist.SetItemText(nRow,4,m_CarPartInfoVect[i].csEPLNum);
		m_CarPartinfolist.SetItemText(nRow,5,m_CarPartInfoVect[i].csVCNum);
		strTemp.Format("%d",m_CarPartInfoVect[i].iLevel);
		m_CarPartinfolist.SetItemText(nRow,6,strTemp);
		m_CarPartinfolist.SetItemText(nRow,7,m_CarPartInfoVect[i].csEnglishName);
		m_CarPartinfolist.SetItemText(nRow,8,m_CarPartInfoVect[i].csPicNum);
		m_CarPartinfolist.SetItemText(nRow,9,m_CarPartInfoVect[i].csInstallNum);
		strTemp.Format("%d",m_CarPartInfoVect[i].iInstallMark);
		m_CarPartinfolist.SetItemText(nRow,10,strTemp);
		m_CarPartinfolist.SetItemText(nRow,11,m_CarPartInfoVect[i].strPartReserve.c_str());
	} 

	m_CarPartinfolist.SetRedraw(TRUE);
	m_CarPartinfolist.Invalidate();
	m_CarPartinfolist.UpdateWindow();
}
BOOL CCarPartInfoQueryDlg::PreTranslateMessage(MSG* pMsg)
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
			OnBnClickedBtnMtQCarPartinfo();
			return true;
		case VK_PRIOR:
			OnBnClickedButtonQCarTypebefore();
			return true;
		case VK_NEXT:
			OnBnClickedButtonQCarTypenext();
			return true;
		default:
			;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
void CCarPartInfoQueryDlg::OnSelchangeComboQuery()
{
	// TODO: Add your control notification handler code here
}


LRESULT CCarPartInfoQueryDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà

	if (WM_USER_UPDATE == message)
	{
		m_CarPartInfoVect.clear();
		GetCarPartInfo(&m_queryInfo,m_curPage,MAX_QUERY_COUNT,m_CarPartInfoVect,true);
		UpdateDataInfo();

		return TRUE;
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}


void CCarPartInfoQueryDlg::OnSmenuCarpartmodifycartype()
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌÐò´úÂë
	if (!(CCarInfoSearchDlg::s_dwUserPower&USER_POWER_MODIFY))
	{
		CCarInfoSearchDlg::ShowOperateInfo("对不起，您没有操作权限！");
		return;
	}

	if(m_CarPartinfolist.GetSelectedCount()<=0)
		return;
	int selectIndex = m_CarPartinfolist.GetSelectionMark();

	CString strTemp;
	CarPartTableInfo tempInfo;
	strncpy(tempInfo.csCarTypeNum,m_CarPartinfolist.GetItemText(selectIndex,0).operator LPCSTR(),16);
	strncpy(tempInfo.csDAENum,m_CarPartinfolist.GetItemText(selectIndex,1).operator LPCSTR(),32);
	strncpy(tempInfo.csMMCNum,m_CarPartinfolist.GetItemText(selectIndex,2).operator LPCSTR(),32);

	m_querySuppDlg.SetCartPartInfo(&tempInfo,OPERATE_TYPE_MODIFY);
	m_querySuppDlg.DoModal();	

	m_CarPartinfolist.SetFocus();
}
