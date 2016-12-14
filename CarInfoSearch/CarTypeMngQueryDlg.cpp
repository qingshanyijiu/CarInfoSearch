// CarTypeMngQueryDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "CarInfoSearch.h"
#include "CarTypeMngQueryDlg.h"
#include "afxdialogex.h"
#include "CarInfoSearchDlg.h"
#include "CarTypeInfoDlg.h"
#include "CarPartInfoQueryDlg.h"
extern CCarInfoSearchDlg*	g_pMainDlg;
// CCarTypeMngQueryDlg 对话框
IMPLEMENT_DYNAMIC(CCarTypeMngQueryDlg, CDialogEx)
CCarTypeMngQueryDlg::CCarTypeMngQueryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCarTypeMngQueryDlg::IDD, pParent)
{
}
CCarTypeMngQueryDlg::~CCarTypeMngQueryDlg()
{
}
void CCarTypeMngQueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_GROUPBOX_CarTypeQUEY, m_groupbox);
	DDX_Control(pDX, IDC_BUTTON_QCarTypeBefore, m_QCarTypeBeforeButton);
	DDX_Control(pDX, IDC_BUTTON_QCarTypeNext, m_QCarTypeNextButton);
	DDX_Control(pDX, IDC_LIST_CarTypeList, m_CarTypeList);
}
BEGIN_MESSAGE_MAP(CCarTypeMngQueryDlg, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_CarType_CarTypeQuery, &CCarTypeMngQueryDlg::OnBnClickedBtnCarTypeCarTypequery)
	ON_BN_CLICKED(IDC_BUTTON_QCarTypeBefore, &CCarTypeMngQueryDlg::OnBnClickedButtonQCarTypebefore)
	ON_BN_CLICKED(IDC_BUTTON_QCarTypeNext, &CCarTypeMngQueryDlg::OnBnClickedButtonQCarTypenext)
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CarTypeList, &CCarTypeMngQueryDlg::OnLvnItemchangedListCarTypelist)
ON_NOTIFY(NM_RCLICK, IDC_LIST_CarTypeList, &CCarTypeMngQueryDlg::OnRclickListCarTypelist)
ON_NOTIFY(NM_DBLCLK, IDC_LIST_CarTypeList, &CCarTypeMngQueryDlg::OnDblclkListCarTypelist)
ON_COMMAND(ID_SMENU_CarTypeDelete, &CCarTypeMngQueryDlg::OnSmenuCarTypedelete)
ON_COMMAND(ID_SMENU_CarTypeDetail, &CCarTypeMngQueryDlg::OnSmenuCarTypedetail)
ON_COMMAND(ID_SMENU_CarTypeModify, &CCarTypeMngQueryDlg::OnSmenuCarTypemodify)
ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()
// CCarTypeMngQueryDlg 消息处理程序
void CCarTypeMngQueryDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
}


BOOL CCarTypeMngQueryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  Add extra initialization here
	LONG lStyle;
	lStyle = GetWindowLong(m_CarTypeList.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_CarTypeList.m_hWnd, GWL_STYLE, lStyle);//设置style
	DWORD dwStyle = m_CarTypeList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_CarTypeList.SetExtendedStyle(dwStyle); //设置扩展风格

	int iWidth = m_CarTypeList.GetListWidth();
	m_CarTypeList.InsertColumn( 0, "机型编号\nTypeNum", LVCFMT_LEFT, (int)(iWidth*0.1) );
	m_CarTypeList.InsertColumn( 1, "发动机编号\nEngineNum", LVCFMT_LEFT, (int)(iWidth*0.15)  );
	m_CarTypeList.InsertColumn( 2, "车厂名称\nDepotName", LVCFMT_LEFT, (int)(iWidth*0.12)  );
	m_CarTypeList.InsertColumn( 3, "机型状态\nTypeStatus", LVCFMT_LEFT, (int)(iWidth*0.12)  );
	m_CarTypeList.InsertColumn( 4, "车型名称\nTypeName", LVCFMT_LEFT, (int)(iWidth*0.15)  );
	m_CarTypeList.InsertColumn( 5, "备注\nTypeNotes", LVCFMT_LEFT,(int)(iWidth*0.36)  );

	m_CarTypeList.InitHead();
	m_CarTypeList.SetMouseWheelCallFunc(std::tr1::bind(&CCarTypeMngQueryDlg::OnBnClickedButtonQCarTypebefore, this),
		std::tr1::bind(&CCarTypeMngQueryDlg::OnBnClickedButtonQCarTypenext, this));


	m_curPageIndex = 0;
	m_iTotalRecord = 0;
	m_CarTypeInfoVect.reserve(MAX_QUERY_COUNT);
	OnBnClickedBtnCarTypeCarTypequery();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CCarTypeMngQueryDlg::OnBnClickedBtnCarTypeCarTypequery()
{
	// TODO: Add your control notification handler code here

	CString	strTemp;
	m_carTypeSearchInfo.Clear();

	GetDlgItemText(IDC_EDIT_CT_CarTypeNum,strTemp);
	strTemp.Trim();
	strncpy(m_carTypeSearchInfo.csCarTypeNum,strTemp.operator LPCSTR(),16);

	GetDlgItemText(IDC_EDIT_CT_CarDetailTypeNum,strTemp);
	strTemp.Trim();
	strncpy(m_carTypeSearchInfo.csCarDetailTypeNum,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_CT_CarDetailName,strTemp);
	strTemp.Trim();
	strncpy(m_carTypeSearchInfo.csCarDetailName,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_CT_CarFactory,strTemp);
	strTemp.Trim();
	strncpy(m_carTypeSearchInfo.csCarFactory,strTemp.operator LPCSTR(),32);
	GetDlgItemText(IDC_EDIT_CT_Note,strTemp);
	strTemp.Trim();
	m_carTypeSearchInfo.strCarNotes = strTemp.operator LPCSTR();

	m_curPageIndex = 0;
	m_CarTypeInfoVect.clear();

	if (OPERATE_DB_SUCCESS == GetCarTypeCount(&m_carTypeSearchInfo,&m_iTotalRecord))
	{
		CCarInfoSearchDlg::ShowSearchRecord(m_iTotalRecord,m_curPageIndex+1);
		if (m_iTotalRecord)
		{
			if (OPERATE_DB_SUCCESS == GetCarTypeInfo(&m_carTypeSearchInfo,
				m_curPageIndex,
				MAX_QUERY_COUNT,
				m_CarTypeInfoVect,
				true))
			{
				CCarInfoSearchDlg::ShowOperateInfo("查询成功！");
				UpdateDataInfo();
			}
			else
			{
				CCarInfoSearchDlg::ShowOperateInfo("查询失败！");
			}

			
			CCarInfoSearchDlg::ShowSearchRecord(m_iTotalRecord,m_curPageIndex+1);
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
void CCarTypeMngQueryDlg::OnBnClickedButtonQCarTypebefore()
{
	// TODO: Add your control notification handler code here
	if (m_curPageIndex)
	{
		m_CarTypeInfoVect.clear();
		--m_curPageIndex;
		if (OPERATE_DB_SUCCESS == GetCarTypeInfo(&m_carTypeSearchInfo,
			m_curPageIndex,
			MAX_QUERY_COUNT,
			m_CarTypeInfoVect,
			true))
		{
			CCarInfoSearchDlg::ShowOperateInfo("查询上一页成功！");
			UpdateDataInfo();
		}
		else
		{
			++m_curPageIndex;
			CCarInfoSearchDlg::ShowOperateInfo("查询上一页失败！");
		}
		CCarInfoSearchDlg::ShowSearchRecord(m_iTotalRecord,m_curPageIndex+1);
	}
	else
	{
		CCarInfoSearchDlg::ShowOperateInfo("没有上一页，不能查询！");
	}
}
void CCarTypeMngQueryDlg::OnBnClickedButtonQCarTypenext()
{
	// TODO: Add your control notification handler code here
	int iTotalPage = (m_iTotalRecord/MAX_QUERY_COUNT)+(m_iTotalRecord%MAX_QUERY_COUNT?1:0);
	if (m_curPageIndex+1<iTotalPage)
	{
		m_CarTypeInfoVect.clear();
		++m_curPageIndex;
		if (OPERATE_DB_SUCCESS == GetCarTypeInfo(&m_carTypeSearchInfo,
			m_curPageIndex,
			MAX_QUERY_COUNT,
			m_CarTypeInfoVect,
			true))
		{
			CCarInfoSearchDlg::ShowOperateInfo("查询下一页成功！");
			UpdateDataInfo();
		}
		else
		{
			--m_curPageIndex;
			CCarInfoSearchDlg::ShowOperateInfo("查询下一页失败！");
		}
		CCarInfoSearchDlg::ShowSearchRecord(m_iTotalRecord,m_curPageIndex+1);
	}
	else
	{
		CCarInfoSearchDlg::ShowOperateInfo("没有下一页，不能查询！");
	}
}
void CCarTypeMngQueryDlg::OnRclickListCarTypelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	if(m_CarTypeList.GetSelectedCount()>0)
	{
		NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
		if(pNMListView->iItem != -1)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
			CMenu menu;
			VERIFY( menu.LoadMenu( IDR_MENU_CarTypeMenu ) );
			CMenu* popup = menu.GetSubMenu(0);
			ASSERT( popup != NULL );
			popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );
		}
	}
	*pResult = 0;
}
void CCarTypeMngQueryDlg::OnDblclkListCarTypelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	OnSmenuCarTypedetail();
	*pResult = 0;
}
void CCarTypeMngQueryDlg::OnSmenuCarTypedelete()
{
	// TODO: Add your command handler code here
	if (!(CCarInfoSearchDlg::s_dwUserPower&USER_POWER_MODIFY))
	{
		CCarInfoSearchDlg::ShowOperateInfo("对不起，您没有操作权限！");
		return;
	}

	int selectIndex = m_CarTypeList.GetSelectionMark();
	if(selectIndex<0)
		return;
	if(IDYES== MessageBox("是否删除当前选中的机型信息?\nWhether to delete this record?","提示(Notify)",MB_YESNO))
	{
		CString strTemp = m_CarTypeList.GetItemText(selectIndex,1);
		if(OPERATE_DB_SUCCESS ==  DeleteCarTypeInfo(strTemp.operator LPCSTR()))
		{
			m_CarTypeList.DeleteItem(selectIndex);
			CCarInfoSearchDlg::ShowOperateInfo("机型信息删除成功！");
		}
		else
		{
			CCarInfoSearchDlg::ShowOperateInfo("机型信息删除失败！");
		}
	}
}
void CCarTypeMngQueryDlg::OnSmenuCarTypedetail()
{
	// TODO: Add your command handler code here
	if(g_pMainDlg == NULL || m_CarTypeList.GetSelectedCount()<=0)
		return;
	int selectIndex = m_CarTypeList.GetSelectionMark();
	((CCarTypeInfoDlg*)(g_pMainDlg->m_pages[IDD_CarTypeMNG_MODIFY_DLG]))->SetOperateType(OPERATE_TYPE_SHOW,&m_CarTypeInfoVect[selectIndex]);
	g_pMainDlg->RightPageShow(IDD_CarTypeMNG_MODIFY_DLG);
	CCarInfoSearchDlg::ShowOperateInfo("查看机型详细信息！");
}
void CCarTypeMngQueryDlg::OnSmenuCarTypemodify()
{
	// TODO: Add your command handler code here
	if (!(CCarInfoSearchDlg::s_dwUserPower&USER_POWER_MODIFY))
	{
		CCarInfoSearchDlg::ShowOperateInfo("对不起，您没有操作权限！");
		return;
	}

	if(g_pMainDlg == NULL || m_CarTypeList.GetSelectedCount()<=0)
		return;
	int selectIndex = m_CarTypeList.GetSelectionMark();
	((CCarTypeInfoDlg*)(g_pMainDlg->m_pages[IDD_CarTypeMNG_MODIFY_DLG]))->SetOperateType(OPERATE_TYPE_MODIFY,&m_CarTypeInfoVect[selectIndex]);
	g_pMainDlg->RightPageShow(IDD_CarTypeMNG_MODIFY_DLG);
	CCarInfoSearchDlg::ShowOperateInfo("修改机型详细信息！");
}
/*
void CCarTypeMngQueryDlg::QueryCarTypeInfoByLicNumber(const char* lpLicNumber)
{
	SetDlgItemText(IDC_EDIT_QCarTypeLicNumber,lpLicNumber);
	SetDlgItemText(IDC_EDIT_QCarTypeName,"");
	SetDlgItemText(IDC_EDIT_QCarTypePhone,"");
	OnBnClickedBtnCarTypeCarTypequery();
}*/

void CCarTypeMngQueryDlg::OnSmenuCarTypequeryrepair()
{
	// TODO: Add your command handler code here
	if(g_pMainDlg == NULL || m_CarTypeList.GetSelectedCount()<=0)
		return;
	int selectIndex = m_CarTypeList.GetSelectionMark();
	//((CCarPartInfoQueryDlg*)(g_pMainDlg->m_pages[IDD_MaintenanceMng_QUERY_Dlg]))->QueryCarPartInfoByLicNumber(m_CarTypeInfoVect[selectIndex].csLicenseNumber);
	g_pMainDlg->RightPageShow(IDD_MaintenanceMng_QUERY_Dlg);
	CCarInfoSearchDlg::ShowOperateInfo("修车信息 - 详细内容！");
}

void CCarTypeMngQueryDlg::UpdateDataInfo()
{
	m_CarTypeList.SetRedraw(FALSE);
	//更新内容
	m_CarTypeList.DeleteAllItems();
	int nRow;
	
	for(int i = 0 ; i < m_CarTypeInfoVect.size() ; ++i) 
	{ 
		nRow = m_CarTypeList.InsertItem(i, m_CarTypeInfoVect[i].csCarTypeNum);//插入行
		m_CarTypeList.SetItemText(nRow, 1, m_CarTypeInfoVect[i].csCarDetailTypeNum);//设置数据
		m_CarTypeList.SetItemText(nRow, 2, m_CarTypeInfoVect[i].csCarFactory);
		m_CarTypeList.SetItemText(nRow, 3, m_CarTypeInfoVect[i].csCarStatus);
		m_CarTypeList.SetItemText(nRow, 4, m_CarTypeInfoVect[i].csCarDetailName);
		m_CarTypeList.SetItemText(nRow, 5, m_CarTypeInfoVect[i].strCarNotes.c_str());
	} 

	m_CarTypeList.SetRedraw(TRUE);
	m_CarTypeList.Invalidate();
	m_CarTypeList.UpdateWindow();
}
BOOL CCarTypeMngQueryDlg::PreTranslateMessage(MSG* pMsg)
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
			OnBnClickedBtnCarTypeCarTypequery();
			return true;
		case VK_PRIOR:
			OnBnClickedButtonQCarTypebefore();
			return true;
		case VK_NEXT:
			OnBnClickedButtonQCarTypenext();
			return true;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


LRESULT CCarTypeMngQueryDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà

	if (WM_USER_UPDATE == message)
	{
		m_CarTypeInfoVect.clear();
		GetCarTypeInfo(&m_carTypeSearchInfo,m_curPageIndex,MAX_QUERY_COUNT,m_CarTypeInfoVect,true);
		UpdateDataInfo();

		return TRUE;
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}


BOOL CCarTypeMngQueryDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ



	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}
