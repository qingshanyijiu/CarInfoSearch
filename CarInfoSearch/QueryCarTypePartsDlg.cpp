// QueryCarTypePartsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CarInfoSearch.h"
#include "CarInfoSearchDlg.h"
#include "QueryCarTypePartsDlg.h"
#include "CarTypeInfoDlg.h"
#include "CarPartInfoDlg.h"
#include "afxdialogex.h"

extern CCarInfoSearchDlg*	g_pMainDlg;


// CQueryCarTypePartsDlg 对话框

IMPLEMENT_DYNAMIC(CQueryCarTypePartsDlg, CDialogEx)

CQueryCarTypePartsDlg::CQueryCarTypePartsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQueryCarTypePartsDlg::IDD, pParent)
{

}

CQueryCarTypePartsDlg::~CQueryCarTypePartsDlg()
{
}

void CQueryCarTypePartsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CTP, m_carTypePartsList);
}


BEGIN_MESSAGE_MAP(CQueryCarTypePartsDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ETP_Search, &CQueryCarTypePartsDlg::OnBnClickedButtonEtpSearch)
	ON_BN_CLICKED(IDC_BUTTON_CTP_Before, &CQueryCarTypePartsDlg::OnBnClickedButtonCtpBefore)
	ON_BN_CLICKED(IDC_BUTTON_ETP_Next, &CQueryCarTypePartsDlg::OnBnClickedButtonEtpNext)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CTP, &CQueryCarTypePartsDlg::OnRclickListCarTypeParts)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CTP, &CQueryCarTypePartsDlg::OnDblclkListCarTypeParts)
	ON_COMMAND(ID_SMENU_CTP_Parts, &CQueryCarTypePartsDlg::OnSmenuCtpParts)
	ON_COMMAND(ID_SMENU_CTP_Type, &CQueryCarTypePartsDlg::OnSmenuCtpType)
	ON_COMMAND(ID_SMENU_CTP_DELETE, &CQueryCarTypePartsDlg::OnSmenuCtpDelete)
END_MESSAGE_MAP()


// CQueryCarTypePartsDlg 消息处理程序


BOOL CQueryCarTypePartsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯

	LONG lStyle;
	lStyle = GetWindowLong(m_carTypePartsList.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_carTypePartsList.m_hWnd, GWL_STYLE, lStyle);//设置style
	DWORD dwStyle = m_carTypePartsList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_carTypePartsList.SetExtendedStyle(dwStyle); //设置扩展风格
	m_carTypePartsList.InsertColumn( 0, "发动机编号", LVCFMT_LEFT, 120 );
	m_carTypePartsList.InsertColumn( 1, "车厂名称", LVCFMT_LEFT, 120 );
	m_carTypePartsList.InsertColumn( 2, "车型名称", LVCFMT_LEFT, 140 );
	m_carTypePartsList.InsertColumn( 3, "机型编号", LVCFMT_LEFT, 100 );
	m_carTypePartsList.InsertColumn( 4, "DAE件号", LVCFMT_LEFT, 155 );
	m_carTypePartsList.InsertColumn( 5, "MMC件号", LVCFMT_LEFT, 155 );
	m_carTypePartsList.InsertColumn( 6, "零件名称", LVCFMT_LEFT, 150 );
	m_carTypePartsList.InsertColumn( 7, "级别", LVCFMT_LEFT, 50 );

	m_iTotalRecord = 0;
	m_curPage = 0;
	m_carTypePartsInfoVect.reserve(MAX_QUERY_COUNT);

	OnBnClickedButtonEtpSearch();

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}


BOOL CQueryCarTypePartsDlg::PreTranslateMessage(MSG* pMsg)
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
			OnBnClickedButtonEtpSearch();
			return true;
		default:
			;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CQueryCarTypePartsDlg::OnBnClickedButtonEtpSearch()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	CString strTemp;
	m_queryInfo.Clear();

	GetDlgItemText(IDC_EDIT_CTP_CarDetailTypeNum,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csCarDetailTypeNum,strTemp.operator LPCSTR(),16);

	GetDlgItemText(IDC_EDIT_CTP_CarTypeNum,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csCarTypeNum,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_CTP_DAENum,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csDAENum,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_CTP_MMCNum,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csMMCNum,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_CTP_ChineseName,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csChineseName,strTemp.operator LPCSTR(),64)
		;
	GetDlgItemText(IDC_EDIT_CTP_CarFactory,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csCarFactory,strTemp.operator LPCSTR(),32);


	GetDlgItemText(IDC_EDIT_CTP_CarDetailName,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csCarDetailName,strTemp.operator LPCSTR(),32);

	m_curPage = 0;
	m_carTypePartsInfoVect.clear();

	if (OPERATE_DB_SUCCESS == GetCarTypePartsCount(&m_queryInfo,&m_iTotalRecord))
	{
		CCarInfoSearchDlg::ShowSearchRecord(m_iTotalRecord,m_curPage+1);
		if (m_iTotalRecord)
		{
			if (OPERATE_DB_SUCCESS == GetCarTypePartsInfo(&m_queryInfo,
				m_curPage,
				MAX_QUERY_COUNT,
				m_carTypePartsInfoVect,
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


void CQueryCarTypePartsDlg::OnBnClickedButtonCtpBefore()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	if (m_curPage)
	{
		m_carTypePartsInfoVect.clear();
		--m_curPage;
		if (OPERATE_DB_SUCCESS ==  GetCarTypePartsInfo(&m_queryInfo,
			m_curPage,
			MAX_QUERY_COUNT,
			m_carTypePartsInfoVect,
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


void CQueryCarTypePartsDlg::OnBnClickedButtonEtpNext()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	int iTotalPage = (m_iTotalRecord/MAX_QUERY_COUNT)+(m_iTotalRecord%MAX_QUERY_COUNT?1:0);
	if (m_curPage+1<iTotalPage)
	{
		m_carTypePartsInfoVect.clear();
		++m_curPage;
		if (OPERATE_DB_SUCCESS ==  GetCarTypePartsInfo(&m_queryInfo,
			m_curPage,
			MAX_QUERY_COUNT,
			m_carTypePartsInfoVect,
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


void CQueryCarTypePartsDlg::OnRclickListCarTypeParts(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	if(m_carTypePartsList.GetSelectedCount()>0)
	{
		NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
		if(pNMListView->iItem != -1)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
			CMenu menu;
			VERIFY( menu.LoadMenu( IDR_MENU_CarTypePartsMenu ) );
			CMenu* popup = menu.GetSubMenu(0);
			ASSERT( popup != NULL );
			popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );
		}
	}

	*pResult = 0;
}


void CQueryCarTypePartsDlg::OnDblclkListCarTypeParts(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	CQueryCarTypePartsDlg::OnSmenuCtpParts();

	*pResult = 0;
}

void CQueryCarTypePartsDlg::UpdateDataInfo()
{
	m_carTypePartsList.SetRedraw(FALSE);
	//更新内容
	m_carTypePartsList.DeleteAllItems();

	int nRow;
	CString strTemp;
	for(int i = 0 ; i < m_carTypePartsInfoVect.size() ; ++i) 
	{ 
		nRow = m_carTypePartsList.InsertItem(i, m_carTypePartsInfoVect[i].csCarDetailTypeNum);//插入行
		m_carTypePartsList.SetItemText(nRow, 1, m_carTypePartsInfoVect[i].csCarFactory);//设置数据
		m_carTypePartsList.SetItemText(nRow, 2, m_carTypePartsInfoVect[i].csCarDetailName);
		m_carTypePartsList.SetItemText(nRow, 3, m_carTypePartsInfoVect[i].csCarTypeNum);
		m_carTypePartsList.SetItemText(nRow, 4, m_carTypePartsInfoVect[i].csDAENum);
		m_carTypePartsList.SetItemText(nRow, 5, m_carTypePartsInfoVect[i].csMMCNum);
		m_carTypePartsList.SetItemText(nRow, 6, m_carTypePartsInfoVect[i].csChineseName);
		strTemp.Format("%d",m_carTypePartsInfoVect[i].iLevel);
		m_carTypePartsList.SetItemText(nRow, 7, strTemp);
	} 

	m_carTypePartsList.SetRedraw(TRUE);
	m_carTypePartsList.Invalidate();
	m_carTypePartsList.UpdateWindow();
}

void CQueryCarTypePartsDlg::OnSmenuCtpParts()
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌÐò´úÂë
	if(g_pMainDlg == NULL || m_carTypePartsList.GetSelectedCount()<=0)
		return;
	int selectIndex = m_carTypePartsList.GetSelectionMark();

	CString strTemp;
	CarPartTableInfo tempInfo;
	strncpy(tempInfo.csCarTypeNum,m_carTypePartsList.GetItemText(selectIndex,3).operator LPCSTR(),16);
	strncpy(tempInfo.csDAENum,m_carTypePartsList.GetItemText(selectIndex,4).operator LPCSTR(),32);
	strncpy(tempInfo.csMMCNum,m_carTypePartsList.GetItemText(selectIndex,5).operator LPCSTR(),32);
	vector<CarPartTableInfo>	tempVect;
	if (OPERATE_DB_SUCCESS == GetCarPartInfo(&tempInfo,0,MAX_QUERY_COUNT,tempVect)&&tempVect.size())
	{
		((CCarPartInfoDlg*)(g_pMainDlg->m_pages[IDD_MaintenanceMng_MODIFY_Dlg]))->SetOperateType(OPERATE_TYPE_SHOW_EX,&tempVect[0]);
		g_pMainDlg->RightPageShow(IDD_MaintenanceMng_MODIFY_Dlg);
		CCarInfoSearchDlg::ShowOperateInfo("查看零件信息 - 详细内容！");
	}
}


void CQueryCarTypePartsDlg::OnSmenuCtpType()
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌÐò´úÂë

	if(g_pMainDlg == NULL || m_carTypePartsList.GetSelectedCount()<=0)
		return;
	int selectIndex = m_carTypePartsList.GetSelectionMark();

	CString strTemp;
	CarTypeTableInfo tempInfo;
	strncpy(tempInfo.csCarDetailTypeNum,m_carTypePartsList.GetItemText(selectIndex,0).operator LPCSTR(),16);
	vector<CarTypeTableInfo>	tempVect;
	if (OPERATE_DB_SUCCESS == GetCarTypeInfo(&tempInfo,0,MAX_QUERY_COUNT,tempVect)&&tempVect.size())
	{
		((CCarTypeInfoDlg*)(g_pMainDlg->m_pages[IDD_CarTypeMNG_MODIFY_DLG]))->SetOperateType(OPERATE_TYPE_SHOW_EX,&tempVect[0]);
		g_pMainDlg->RightPageShow(IDD_CarTypeMNG_MODIFY_DLG);
		CCarInfoSearchDlg::ShowOperateInfo("查看机型详细信息！");
	}
}


void CQueryCarTypePartsDlg::OnSmenuCtpDelete()
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌÐò´úÂë

	if (!(CCarInfoSearchDlg::s_dwUserPower&USER_POWER_MODIFY))
	{
		CCarInfoSearchDlg::ShowOperateInfo("对不起，您没有操作权限！");
		return;
	}

	int selectIndex = m_carTypePartsList.GetSelectionMark();
	if(selectIndex<0)
		return;
	if(IDYES== MessageBox("是否删除当前选中的机型零件记录?","提示",MB_YESNO))
	{
		CString strTemp;
		CarTypePartsTableInfo tempInfo;
		strncpy(tempInfo.csCarDetailTypeNum,m_carTypePartsList.GetItemText(selectIndex,0).operator LPCSTR(),16);
		strncpy(tempInfo.csCarTypeNum,m_carTypePartsList.GetItemText(selectIndex,3).operator LPCSTR(),16);
		strncpy(tempInfo.csDAENum,m_carTypePartsList.GetItemText(selectIndex,4).operator LPCSTR(),32);
		strncpy(tempInfo.csMMCNum,m_carTypePartsList.GetItemText(selectIndex,5).operator LPCSTR(),32);

		if(OPERATE_DB_SUCCESS == DeleteCarTypePartsInfo(&tempInfo))
		{
			m_carTypePartsList.DeleteItem(selectIndex);
			CCarInfoSearchDlg::ShowOperateInfo("机型零件信息删除成功！");
		}
		else
		{
			CCarInfoSearchDlg::ShowOperateInfo("机型零件信息删除失败！");
		}
	}
}
