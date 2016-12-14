// ASQueryPartDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CarInfoSearch.h"
#include "ASQueryPartDlg.h"
#include "CarInfoSearchDlg.h"
#include "ASModifyPartDlg.h"
#include "afxdialogex.h"


extern CCarInfoSearchDlg*	g_pMainDlg;

// CASQueryPartDlg 对话框

IMPLEMENT_DYNAMIC(CASQueryPartDlg, CDialogEx)

CASQueryPartDlg::CASQueryPartDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CASQueryPartDlg::IDD, pParent)
{
	m_curPage = 0;
}

CASQueryPartDlg::~CASQueryPartDlg()
{
}

void CASQueryPartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_AS_PART, m_carPartinfolist);
}


BEGIN_MESSAGE_MAP(CASQueryPartDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_AS_PART_QUERY, &CASQueryPartDlg::OnBnClickedButtonAsPartQuery)
	ON_BN_CLICKED(IDC_BUTTON_AS_QUERY_PART_Before, &CASQueryPartDlg::OnBnClickedButtonAsQueryPartBefore)
	ON_BN_CLICKED(IDC_BUTTON_AS_QUERY_PART_Next, &CASQueryPartDlg::OnBnClickedButtonAsQueryPartNext)
	ON_COMMAND(ID_SMENU_AS_PART_DETAIL, &CASQueryPartDlg::OnSmenuAsPartDetail)
	ON_COMMAND(ID_SMENU_AS_PART_MODIFY, &CASQueryPartDlg::OnSmenuAsPartModify)
	ON_COMMAND(ID_SMENU_AS_PART_DELETE, &CASQueryPartDlg::OnSmenuAsPartDelete)
	ON_COMMAND(ID_SMENU_AS_PART_TYPEDETAIL, &CASQueryPartDlg::OnSmenuAsPartTypedetail)
	ON_COMMAND(ID_SMENU_AS_PART_TYPEMODIFY, &CASQueryPartDlg::OnSmenuAsPartTypemodify)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_AS_PART, &CASQueryPartDlg::OnDblclkListAsPart)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_AS_PART, &CASQueryPartDlg::OnRclickListAsPart)
END_MESSAGE_MAP()


// CASQueryPartDlg 消息处理程序


BOOL CASQueryPartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯

	LONG lStyle;
	lStyle = GetWindowLong(m_carPartinfolist.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_carPartinfolist.m_hWnd, GWL_STYLE, lStyle);//设置style
	DWORD dwStyle = m_carPartinfolist.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件

	int iWidth = m_carPartinfolist.GetListWidth();
	m_carPartinfolist.SetExtendedStyle(dwStyle); //设置扩展风格
	m_carPartinfolist.InsertColumn( 0, "机型编号\nTypeNum", LVCFMT_LEFT, (int)(iWidth*0.06) );
	m_carPartinfolist.InsertColumn( 1, "零件代号\nPartNum", LVCFMT_LEFT, (int)(iWidth*0.12) );
	m_carPartinfolist.InsertColumn( 2, "部件号\nWholeNum", LVCFMT_LEFT, (int)(iWidth*0.06) );
	m_carPartinfolist.InsertColumn( 3, "部件英文名\nWholeEngName", LVCFMT_LEFT, (int)(iWidth*0.13) );
	m_carPartinfolist.InsertColumn( 4, "部件中文名\nWholeChinName", LVCFMT_LEFT, (int)(iWidth*0.13) );
	m_carPartinfolist.InsertColumn( 5, "零件序号\nItemNum", LVCFMT_LEFT, (int)(iWidth*0.06) );
	m_carPartinfolist.InsertColumn( 6, "英文名称\nEngName", LVCFMT_LEFT,(int)(iWidth*0.14) );
	m_carPartinfolist.InsertColumn( 7, "零件名称\nPartName", LVCFMT_LEFT,(int)(iWidth*0.15) );
	m_carPartinfolist.InsertColumn( 8, "零件备注\nPartNotes", LVCFMT_LEFT, (int)(iWidth*0.16) );

	m_carPartinfolist.InitHead();
	m_carPartinfolist.SetMouseWheelCallFunc(std::tr1::bind(&CASQueryPartDlg::OnBnClickedButtonAsQueryPartBefore, this),
		std::tr1::bind(&CASQueryPartDlg::OnBnClickedButtonAsQueryPartNext, this));

	m_iTotalRecord=0;
	m_curPage = 0;

	m_CarPartInfoVect.reserve(MAX_QUERY_COUNT);
	OnBnClickedButtonAsPartQuery();


	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}


BOOL CASQueryPartDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà

	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_ESCAPE: //Esc按键事件
			return true;
		case VK_RETURN: //Enter按键事件
			OnBnClickedButtonAsPartQuery();
			return true;
		case VK_PRIOR:
			OnBnClickedButtonAsQueryPartBefore();
			return true;
		case VK_NEXT:
			OnBnClickedButtonAsQueryPartNext();
			return true;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CASQueryPartDlg::OnBnClickedButtonAsPartQuery()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	CString strTemp;
	m_queryInfo.Clear();

	GetDlgItemText(IDC_EDIT_AS_QUERY_PART_TypeNum,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csCarTypeNum,strTemp.operator LPCSTR(),16);

	GetDlgItemText(IDC_EDIT_AS_QUERY_PART_PartNum,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csPartNum,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_AS_QUERY_PART_WholeName,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csWholeChinName,strTemp.operator LPCSTR(),64);

	GetDlgItemText(IDC_EDIT_AS_QUERY_PART_ChinName,strTemp);
	strTemp.Trim();
	strncpy(m_queryInfo.csChinName,strTemp.operator LPCSTR(),64);

	GetDlgItemText(IDC_EDIT_AS_QUERY_PART_Remark,strTemp);
	strTemp.Trim();
	m_queryInfo.strRemark = strTemp;

	m_curPage = 0;
	m_CarPartInfoVect.clear();

	if (OPERATE_DB_SUCCESS == ASGetCarPartCount(&m_queryInfo,&m_iTotalRecord))
	{
		CCarInfoSearchDlg::ShowSearchRecord(m_iTotalRecord,m_curPage+1);
		if (m_iTotalRecord)
		{
			if (OPERATE_DB_SUCCESS == ASGetCarPartInfo(&m_queryInfo,
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


void CASQueryPartDlg::OnBnClickedButtonAsQueryPartBefore()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	if (m_curPage)
	{
		m_CarPartInfoVect.clear();
		--m_curPage;
		if (OPERATE_DB_SUCCESS == ASGetCarPartInfo(&m_queryInfo,
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


void CASQueryPartDlg::OnBnClickedButtonAsQueryPartNext()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	int iTotalPage = (m_iTotalRecord/MAX_QUERY_COUNT)+(m_iTotalRecord%MAX_QUERY_COUNT?1:0);
	if (m_curPage+1<iTotalPage)
	{
		m_CarPartInfoVect.clear();
		++m_curPage;
		if (OPERATE_DB_SUCCESS == ASGetCarPartInfo(&m_queryInfo,
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

void	CASQueryPartDlg::UpdateDataInfo()
{
	m_carPartinfolist.SetRedraw(FALSE);
	//更新内容
	m_carPartinfolist.DeleteAllItems();

	int nRow;
	CString strTemp;
	for(int i = 0 ; i < m_CarPartInfoVect.size() ; ++i) 
	{ 
		nRow = m_carPartinfolist.InsertItem(i,m_CarPartInfoVect[i].csCarTypeNum);
		m_carPartinfolist.SetItemText(nRow,1,m_CarPartInfoVect[i].csPartNum);
		m_carPartinfolist.SetItemText(nRow,2,m_CarPartInfoVect[i].csWholeNum);
		m_carPartinfolist.SetItemText(nRow,3,m_CarPartInfoVect[i].csWholeEngName);
		m_carPartinfolist.SetItemText(nRow,4,m_CarPartInfoVect[i].csWholeChinName);
		m_carPartinfolist.SetItemText(nRow,5,m_CarPartInfoVect[i].csItemNum);
		m_carPartinfolist.SetItemText(nRow,6,m_CarPartInfoVect[i].csEngName);
		m_carPartinfolist.SetItemText(nRow,7,m_CarPartInfoVect[i].csChinName);
		m_carPartinfolist.SetItemText(nRow,8,m_CarPartInfoVect[i].strRemark.c_str());
	} 

	m_carPartinfolist.SetRedraw(TRUE);
	m_carPartinfolist.Invalidate();
	m_carPartinfolist.UpdateWindow();
}


void CASQueryPartDlg::OnSmenuAsPartDetail()
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌÐò´úÂë

	if(g_pMainDlg == NULL || m_carPartinfolist.GetSelectedCount()<=0)
		return;
	int selectIndex = m_carPartinfolist.GetSelectionMark();
	((CASModifyPartDlg*)(g_pMainDlg->m_pages[IDD_DIALOG_AS_MODIFY_PART]))->SetOperateType(OPERATE_TYPE_SHOW,&m_CarPartInfoVect[selectIndex]);
	g_pMainDlg->RightPageShow(IDD_DIALOG_AS_MODIFY_PART);
	CCarInfoSearchDlg::ShowOperateInfo("查看零件信息 - 详细内容！");

}


void CASQueryPartDlg::OnSmenuAsPartModify()
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌÐò´úÂë

	if (!(CCarInfoSearchDlg::s_dwUserPower&USER_POWER_MODIFY))
	{
		CCarInfoSearchDlg::ShowOperateInfo("对不起，您没有操作权限！");
		return;
	}

	if(g_pMainDlg == NULL || m_carPartinfolist.GetSelectedCount()<=0)
		return;
	int selectIndex = m_carPartinfolist.GetSelectionMark();
	((CASModifyPartDlg*)(g_pMainDlg->m_pages[IDD_DIALOG_AS_MODIFY_PART]))->SetOperateType(OPERATE_TYPE_MODIFY,&m_CarPartInfoVect[selectIndex]);
	g_pMainDlg->RightPageShow(IDD_DIALOG_AS_MODIFY_PART);
	CCarInfoSearchDlg::ShowOperateInfo("修改零件信息 ！");

}


void CASQueryPartDlg::OnSmenuAsPartDelete()
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌÐò´úÂë

	if (!(CCarInfoSearchDlg::s_dwUserPower&USER_POWER_MODIFY))
	{
		CCarInfoSearchDlg::ShowOperateInfo("对不起，您没有操作权限！");
		return;
	}

	int selectIndex = m_carPartinfolist.GetSelectionMark();
	if(selectIndex<0)
		return;
	if(IDYES== MessageBox("是否删除当前选中的零件信息?\nWhether to delete this record?","提示(Notify)",MB_YESNO))
	{
		CString strTemp;
		ASCarPartTableInfo tempInfo;
		strncpy(tempInfo.csCarTypeNum,m_carPartinfolist.GetItemText(selectIndex,0).operator LPCSTR(),16);
		strncpy(tempInfo.csPartNum,m_carPartinfolist.GetItemText(selectIndex,1).operator LPCSTR(),32);

		if(OPERATE_DB_SUCCESS == ASDeleteCarPartInfo(&tempInfo))
		{
			m_carPartinfolist.DeleteItem(selectIndex);
			CCarInfoSearchDlg::ShowOperateInfo("零件信息删除成功！");
		}
		else
		{
			CCarInfoSearchDlg::ShowOperateInfo("零件信息删除失败！");
		}
	}
}


void CASQueryPartDlg::OnSmenuAsPartTypedetail()
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌÐò´úÂë
	if(g_pMainDlg == NULL || m_carPartinfolist.GetSelectedCount()<=0)
		return;
	int selectIndex = m_carPartinfolist.GetSelectionMark();

	CString strTemp;
	ASCarPartTableInfo tempInfo;
	strncpy(tempInfo.csCarTypeNum,m_carPartinfolist.GetItemText(selectIndex,0).operator LPCSTR(),16);
	strncpy(tempInfo.csPartNum,m_carPartinfolist.GetItemText(selectIndex,1).operator LPCSTR(),32);

	m_querySuppDlg.SetCartPartInfo(&tempInfo,OPERATE_TYPE_SHOW);
	m_querySuppDlg.DoModal();	

	m_carPartinfolist.SetFocus();

}


void CASQueryPartDlg::OnSmenuAsPartTypemodify()
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌÐò´úÂë

	if (!(CCarInfoSearchDlg::s_dwUserPower&USER_POWER_MODIFY))
	{
		CCarInfoSearchDlg::ShowOperateInfo("对不起，您没有操作权限！");
		return;
	}

	if(m_carPartinfolist.GetSelectedCount()<=0)
		return;
	int selectIndex = m_carPartinfolist.GetSelectionMark();

	CString strTemp;
	ASCarPartTableInfo tempInfo;
	strncpy(tempInfo.csCarTypeNum,m_carPartinfolist.GetItemText(selectIndex,0).operator LPCSTR(),16);
	strncpy(tempInfo.csPartNum,m_carPartinfolist.GetItemText(selectIndex,1).operator LPCSTR(),32);

	m_querySuppDlg.SetCartPartInfo(&tempInfo,OPERATE_TYPE_MODIFY);
	m_querySuppDlg.DoModal();	

	m_carPartinfolist.SetFocus();

}


void CASQueryPartDlg::OnDblclkListAsPart(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	OnSmenuAsPartDetail();

	*pResult = 0;
}


void CASQueryPartDlg::OnRclickListAsPart(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	if(m_carPartinfolist.GetSelectedCount()>0)
	{
		NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
		if(pNMListView->iItem != -1)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
			CMenu menu;
			VERIFY( menu.LoadMenu( IDR_MENU_AS_CarPartMenu ) );
			CMenu* popup = menu.GetSubMenu(0);
			ASSERT( popup != NULL );
			popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );
		}
	}


	*pResult = 0;
}


LRESULT CASQueryPartDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà

	if (WM_USER_UPDATE == message)
	{
		m_CarPartInfoVect.clear();
		ASGetCarPartInfo(&m_queryInfo,m_curPage,MAX_QUERY_COUNT,m_CarPartInfoVect,true);
		UpdateDataInfo();

		return TRUE;
	}


	return CDialogEx::WindowProc(message, wParam, lParam);
}
