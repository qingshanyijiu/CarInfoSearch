// ASQueryMuotilDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CarInfoSearch.h"
#include "ASQueryMuitilDlg.h"
#include "afxdialogex.h"
#include "CarInfoSearchDlg.h"
#include "ASModifyPartDlg.h"
#include "ASModifyTypeDlg.h"

extern CCarInfoSearchDlg*	g_pMainDlg;

// CASQueryMuitilDlg 对话框

IMPLEMENT_DYNAMIC(CASQueryMuitilDlg, CDialogEx)

CASQueryMuitilDlg::CASQueryMuitilDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CASQueryMuitilDlg::IDD, pParent)
{

}

CASQueryMuitilDlg::~CASQueryMuitilDlg()
{
}

void CASQueryMuitilDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_AS_MULTIL, m_carTypePartsList);
}


BEGIN_MESSAGE_MAP(CASQueryMuitilDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_AS_MUTI_QUERY, &CASQueryMuitilDlg::OnBnClickedButtonAsMutiQuery)
	ON_BN_CLICKED(IDC_BUTTON_AS_MUITIL_Before, &CASQueryMuitilDlg::OnBnClickedButtonAsMuitilBefore)
	ON_BN_CLICKED(IDC_BUTTON_AS_MUITIL_NEXT, &CASQueryMuitilDlg::OnBnClickedButtonAsMuitilNext)
	ON_COMMAND(ID_SMENU_AS_MUITIL_DELETE, &CASQueryMuitilDlg::OnSmenuAsMuitilDelete)
	ON_COMMAND(ID_SMENU_AS_MUITIL_PART, &CASQueryMuitilDlg::OnSmenuAsMuitilPart)
	ON_COMMAND(ID_SMENU_AS_MUITIL_TYPE, &CASQueryMuitilDlg::OnSmenuAsMuitilType)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_AS_MULTIL, &CASQueryMuitilDlg::OnDblclkListAsMultil)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_AS_MULTIL, &CASQueryMuitilDlg::OnRclickListAsMultil)
END_MESSAGE_MAP()


// CASQueryMuitilDlg 消息处理程序


BOOL CASQueryMuitilDlg::OnInitDialog()
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

	int iWidth = m_carTypePartsList.GetListWidth();
	m_carTypePartsList.InsertColumn( 0, "发动机编号\nEngineNum", LVCFMT_LEFT, (int)(iWidth*0.12) );
	m_carTypePartsList.InsertColumn( 1, "车厂名称\nDepotName", LVCFMT_LEFT, (int)(iWidth*0.09) );
	m_carTypePartsList.InsertColumn( 2, "整车车型\nCarType", LVCFMT_LEFT, (int)(iWidth*0.08) );
	m_carTypePartsList.InsertColumn( 3, "整车名称\nCarName", LVCFMT_LEFT, (int)(iWidth*0.12) );
	m_carTypePartsList.InsertColumn( 4, "机型编号\nTypeNum", LVCFMT_LEFT, (int)(iWidth*0.08) );
	m_carTypePartsList.InsertColumn( 5, "零件代号\nPartNum", LVCFMT_LEFT, (int)(iWidth*0.12) );
	m_carTypePartsList.InsertColumn( 6, "部件名称\nWholeName", LVCFMT_LEFT, (int)(iWidth*0.12) );
	m_carTypePartsList.InsertColumn( 7, "序号\nItemNum", LVCFMT_LEFT,(int)(iWidth*0.05) );
	m_carTypePartsList.InsertColumn( 8, "零件名称\nPartName", LVCFMT_LEFT, (int)(iWidth*0.13) );
	m_carTypePartsList.InsertColumn( 9, "零件备注\nPartNotes", LVCFMT_LEFT, (int)(iWidth*0.1) );

	m_carTypePartsList.InitHead();
	m_carTypePartsList.SetMouseWheelCallFunc(std::tr1::bind(&CASQueryMuitilDlg::OnBnClickedButtonAsMuitilBefore, this),
		std::tr1::bind(&CASQueryMuitilDlg::OnBnClickedButtonAsMuitilNext, this));

	m_iTotalRecord = 0;
	m_curPage = 0;
	m_carTypePartsInfoVect.reserve(MAX_QUERY_COUNT);

	OnBnClickedButtonAsMutiQuery();


	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}


BOOL CASQueryMuitilDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà

	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_ESCAPE: //Esc按键事件
			return true;
		case VK_RETURN: //Enter按键事件
			OnBnClickedButtonAsMutiQuery();
			return true;
		case VK_PRIOR:
			OnBnClickedButtonAsMuitilBefore();
			return true;
		case VK_NEXT:
			OnBnClickedButtonAsMuitilNext();
			return true;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CASQueryMuitilDlg::OnBnClickedButtonAsMutiQuery()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	CString strTemp;
	m_queryInfo.Clear();

	GetDlgItemText(IDC_EDIT_AS_MUITIL_CarDetailTypeNum,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csCarDetailTypeNum,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_AS_MUITIL_CarFactory,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csCarFactory,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_AS_MUITIL_CarType,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csCarType,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_AS_MUITIL_CarName,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csCarName,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_AS_MUITIL_TYPENUM,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csCarTypeNum,strTemp.operator LPCSTR(),16);

	GetDlgItemText(IDC_EDIT_AS_MUITIL_PartNum,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csPartNum,strTemp.operator LPCSTR(),64)
		;
	GetDlgItemText(IDC_EDIT_AS_MUITIL_WholeChinName,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csWholeChinName,strTemp.operator LPCSTR(),64);

	GetDlgItemText(IDC_EDIT_AS_MUITIL_ChinName,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csChinName,strTemp.operator LPCSTR(),64);

	GetDlgItemText(IDC_EDIT_AS_MUITIL_Remark,strTemp);
	strTemp.Trim();
	m_queryInfo.strRemark = strTemp;

	m_curPage = 0;
	m_carTypePartsInfoVect.clear();

	if (OPERATE_DB_SUCCESS == ASGetCarTypePartsCount(&m_queryInfo,&m_iTotalRecord))
	{
		CCarInfoSearchDlg::ShowSearchRecord(m_iTotalRecord,m_curPage+1);
		if (m_iTotalRecord)
		{
			if (OPERATE_DB_SUCCESS == ASGetCarTypePartsInfo(&m_queryInfo,
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


void CASQueryMuitilDlg::OnBnClickedButtonAsMuitilBefore()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	if (m_curPage)
	{
		m_carTypePartsInfoVect.clear();
		--m_curPage;
		if (OPERATE_DB_SUCCESS ==  ASGetCarTypePartsInfo(&m_queryInfo,
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


void CASQueryMuitilDlg::OnBnClickedButtonAsMuitilNext()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	int iTotalPage = (m_iTotalRecord/MAX_QUERY_COUNT)+(m_iTotalRecord%MAX_QUERY_COUNT?1:0);
	if (m_curPage+1<iTotalPage)
	{
		m_carTypePartsInfoVect.clear();
		++m_curPage;
		if (OPERATE_DB_SUCCESS ==  ASGetCarTypePartsInfo(&m_queryInfo,
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


void CASQueryMuitilDlg::OnSmenuAsMuitilDelete()
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
	if(IDYES== MessageBox("是否删除当前选中的机型零件记录?\nWhether to delete this record?","提示(Notify)",MB_YESNO))
	{
		CString strTemp;
		ASCarTypePartsTableInfo tempInfo;
		strncpy(tempInfo.csCarDetailTypeNum,m_carTypePartsList.GetItemText(selectIndex,0).operator LPCSTR(),32);
		strncpy(tempInfo.csCarTypeNum,m_carTypePartsList.GetItemText(selectIndex,4).operator LPCSTR(),16);
		strncpy(tempInfo.csPartNum,m_carTypePartsList.GetItemText(selectIndex,5).operator LPCSTR(),32);

		if(OPERATE_DB_SUCCESS == ASDeleteCarTypePartsInfo(&tempInfo))
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


void CASQueryMuitilDlg::OnSmenuAsMuitilPart()
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌÐò´úÂë
	if(g_pMainDlg == NULL || m_carTypePartsList.GetSelectedCount()<=0)
		return;
	int selectIndex = m_carTypePartsList.GetSelectionMark();

	CString strTemp;
	ASCarPartTableInfo tempInfo;
	strncpy(tempInfo.csCarTypeNum,m_carTypePartsList.GetItemText(selectIndex,4).operator LPCSTR(),16);
	strncpy(tempInfo.csPartNum,m_carTypePartsList.GetItemText(selectIndex,5).operator LPCSTR(),32);
	vector<ASCarPartTableInfo>	tempVect;
	if (OPERATE_DB_SUCCESS == ASGetCarPartInfo(&tempInfo,0,MAX_QUERY_COUNT,tempVect)&&tempVect.size())
	{
		((CASModifyPartDlg*)(g_pMainDlg->m_pages[IDD_DIALOG_AS_MODIFY_PART]))->SetOperateType(OPERATE_TYPE_SHOW_EX,&tempVect[0]);
		g_pMainDlg->RightPageShow(IDD_DIALOG_AS_MODIFY_PART);
		CCarInfoSearchDlg::ShowOperateInfo("查看零件信息 - 详细内容！");
	}

}


void CASQueryMuitilDlg::OnSmenuAsMuitilType()
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌÐò´úÂë
	if(g_pMainDlg == NULL || m_carTypePartsList.GetSelectedCount()<=0)
		return;
	int selectIndex = m_carTypePartsList.GetSelectionMark();

	CString strTemp;
	ASCarTypeTableInfo tempInfo;
	strncpy(tempInfo.csCarDetailTypeNum,m_carTypePartsList.GetItemText(selectIndex,0).operator LPCSTR(),32);
	vector<ASCarTypeTableInfo>	tempVect;
	if (OPERATE_DB_SUCCESS == ASGetCarTypeInfo(&tempInfo,0,MAX_QUERY_COUNT,tempVect)&&tempVect.size())
	{
		((CASModifyTypeDlg*)(g_pMainDlg->m_pages[IDD_DIALOG_AS_MODIFY_TYPE]))->SetOperateType(OPERATE_TYPE_SHOW_EX,&tempVect[0]);
		g_pMainDlg->RightPageShow(IDD_DIALOG_AS_MODIFY_TYPE);
		CCarInfoSearchDlg::ShowOperateInfo("查看机型详细信息！");
	}

}


void CASQueryMuitilDlg::OnDblclkListAsMultil(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	OnSmenuAsMuitilPart();

	*pResult = 0;
}


void CASQueryMuitilDlg::OnRclickListAsMultil(NMHDR *pNMHDR, LRESULT *pResult)
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
			VERIFY( menu.LoadMenu( IDR_MENU_AS_CarMuitil ) );
			CMenu* popup = menu.GetSubMenu(0);
			ASSERT( popup != NULL );
			popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );
		}
	}


	*pResult = 0;
}

void CASQueryMuitilDlg::UpdateDataInfo()
{
	m_carTypePartsList.SetRedraw(FALSE);
	//更新内容
	m_carTypePartsList.DeleteAllItems();

	int nRow;
	for(int i = 0 ; i < m_carTypePartsInfoVect.size() ; ++i) 
	{ 
		nRow = m_carTypePartsList.InsertItem(i, m_carTypePartsInfoVect[i].csCarDetailTypeNum);//插入行
		m_carTypePartsList.SetItemText(nRow, 1, m_carTypePartsInfoVect[i].csCarFactory);//设置数据
		m_carTypePartsList.SetItemText(nRow, 2, m_carTypePartsInfoVect[i].csCarType);
		m_carTypePartsList.SetItemText(nRow, 3, m_carTypePartsInfoVect[i].csCarName);
		m_carTypePartsList.SetItemText(nRow, 4, m_carTypePartsInfoVect[i].csCarTypeNum);
		m_carTypePartsList.SetItemText(nRow, 5, m_carTypePartsInfoVect[i].csPartNum);
		m_carTypePartsList.SetItemText(nRow, 6, m_carTypePartsInfoVect[i].csWholeChinName);
		m_carTypePartsList.SetItemText(nRow, 7, m_carTypePartsInfoVect[i].csItemNum);
		m_carTypePartsList.SetItemText(nRow, 8, m_carTypePartsInfoVect[i].csChinName);
		m_carTypePartsList.SetItemText(nRow, 9, m_carTypePartsInfoVect[i].strRemark.c_str());
	} 

	m_carTypePartsList.SetRedraw(TRUE);
	m_carTypePartsList.Invalidate();
	m_carTypePartsList.UpdateWindow();
}
