// ASQueryTypeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CarInfoSearch.h"
#include "ASQueryTypeDlg.h"
#include "afxdialogex.h"
#include "CarInfoSearchDlg.h"
#include "ASModifyTypeDlg.h"

extern CCarInfoSearchDlg*	g_pMainDlg;

// CASQueryTypeDlg 对话框

IMPLEMENT_DYNAMIC(CASQueryTypeDlg, CDialogEx)

CASQueryTypeDlg::CASQueryTypeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CASQueryTypeDlg::IDD, pParent)
{

}

CASQueryTypeDlg::~CASQueryTypeDlg()
{
}

void CASQueryTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_AS_TYPE, m_carTypeList);
}


BEGIN_MESSAGE_MAP(CASQueryTypeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_AS_QUERY_TYPE, &CASQueryTypeDlg::OnBnClickedButtonAsQueryType)
	ON_BN_CLICKED(IDC_BUTTON_AS_QUERY_TYPE_Before, &CASQueryTypeDlg::OnBnClickedButtonAsQueryTypeBefore)
	ON_COMMAND(ID_SMENU_AS_TYPE_DETAIL, &CASQueryTypeDlg::OnSmenuAsTypeDetail)
	ON_COMMAND(ID_SMENU_AS_TYPE_MODIFY, &CASQueryTypeDlg::OnSmenuAsTypeModify)
	ON_COMMAND(ID_SMENU_AS_TYPE_DELETE, &CASQueryTypeDlg::OnSmenuAsTypeDelete)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_AS_TYPE, &CASQueryTypeDlg::OnDblclkListAsType)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_AS_TYPE, &CASQueryTypeDlg::OnRclickListAsType)
	ON_BN_CLICKED(IDC_BUTTON_AS_QUERY_TYPE_Next, &CASQueryTypeDlg::OnBnClickedButtonAsQueryTypeNext)
END_MESSAGE_MAP()


// CASQueryTypeDlg 消息处理程序


BOOL CASQueryTypeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯

	LONG lStyle;
	lStyle = GetWindowLong(m_carTypeList.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_carTypeList.m_hWnd, GWL_STYLE, lStyle);//设置style
	DWORD dwStyle = m_carTypeList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_carTypeList.SetExtendedStyle(dwStyle); //设置扩展风格

	int iWidth = m_carTypeList.GetListWidth();
	m_carTypeList.InsertColumn( 0, "机型编号\nTypeNum", LVCFMT_LEFT, (int)(iWidth*0.06) );
	m_carTypeList.InsertColumn( 1, "发动机编号\nEngineNum", LVCFMT_LEFT, (int)(iWidth*0.12)  );
	m_carTypeList.InsertColumn( 2, "客户代号\nCusCode", LVCFMT_LEFT, (int)(iWidth*0.06)  );
	m_carTypeList.InsertColumn( 3, "车厂名称\nDepotName", LVCFMT_LEFT, (int)(iWidth*0.1)  );
	m_carTypeList.InsertColumn( 4, "整机类型\nCarType", LVCFMT_LEFT, (int)(iWidth*0.12)  );
	m_carTypeList.InsertColumn( 5, "车型名称\nTypeName", LVCFMT_LEFT, (int)(iWidth*0.12)  );
	m_carTypeList.InsertColumn( 6, "整车型式\nCarPattern", LVCFMT_LEFT, (int)(iWidth*0.1)  );
	m_carTypeList.InsertColumn( 7, "发动机型式\nEnginePattern", LVCFMT_LEFT, (int)(iWidth*0.12)  );
	m_carTypeList.InsertColumn( 8, "打刻型号\nMarkModel", LVCFMT_LEFT, (int)(iWidth*0.08)  );
	m_carTypeList.InsertColumn( 9, "备注\nCarNotes", LVCFMT_LEFT,(int)(iWidth*0.13)  );

	m_carTypeList.InitHead();
	m_carTypeList.SetMouseWheelCallFunc(std::tr1::bind(&CASQueryTypeDlg::OnBnClickedButtonAsQueryTypeBefore, this),
		std::tr1::bind(&CASQueryTypeDlg::OnBnClickedButtonAsQueryTypeNext, this));
	
	m_curPageIndex = 0;
	m_iTotalRecord = 0;
	m_CarTypeInfoVect.reserve(MAX_QUERY_COUNT);
	OnBnClickedButtonAsQueryType();

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}


BOOL CASQueryTypeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà


	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_ESCAPE: //Esc按键事件
			return true;
		case VK_RETURN: //Enter按键事件
			OnBnClickedButtonAsQueryType();
			return true;
		case VK_PRIOR:
			OnBnClickedButtonAsQueryTypeBefore();
			return true;
		case VK_NEXT:
			OnBnClickedButtonAsQueryTypeNext();
			return true;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CASQueryTypeDlg::OnBnClickedButtonAsQueryType()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	CString	strTemp;
	m_carTypeSearchInfo.Clear();

	GetDlgItemText(IDC_EDIT_AS_QUERY_TYPE_TypeNum,strTemp);
	strTemp.Trim();
	strncpy(m_carTypeSearchInfo.csCarTypeNum,strTemp.operator LPCSTR(),16);

	GetDlgItemText(IDC_EDIT_AS_QUERY_TYPE_CarDetailTypeNum,strTemp);
	strTemp.Trim();
	strncpy(m_carTypeSearchInfo.csCarDetailTypeNum,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_AS_QUERY_TYPE_CarFactory,strTemp);
	strTemp.Trim();
	strncpy(m_carTypeSearchInfo.csCarFactory,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_AS_QUERY_TYPE_CarType,strTemp);
	strTemp.Trim();
	strncpy(m_carTypeSearchInfo.csCarType,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_AS_QUERY_TYPE_CarName,strTemp);
	strTemp.Trim();
	strncpy(m_carTypeSearchInfo.csCarName,strTemp.operator LPCSTR(),32);

	GetDlgItemText(IDC_EDIT_AS_QUERY_TYPE_CarNotes,strTemp);
	strTemp.Trim();
	m_carTypeSearchInfo.strCarNotes = strTemp.operator LPCSTR();

	m_curPageIndex = 0;
	m_CarTypeInfoVect.clear();

	if (OPERATE_DB_SUCCESS == ASGetCarTypeCount(&m_carTypeSearchInfo,&m_iTotalRecord))
	{
		CCarInfoSearchDlg::ShowSearchRecord(m_iTotalRecord,m_curPageIndex+1);
		if (m_iTotalRecord)
		{
			if (OPERATE_DB_SUCCESS == ASGetCarTypeInfo(&m_carTypeSearchInfo,
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


void CASQueryTypeDlg::OnBnClickedButtonAsQueryTypeBefore()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	if (m_curPageIndex)
	{
		m_CarTypeInfoVect.clear();
		--m_curPageIndex;
		if (OPERATE_DB_SUCCESS == ASGetCarTypeInfo(&m_carTypeSearchInfo,
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

void CASQueryTypeDlg::OnBnClickedButtonAsQueryTypeNext()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	int iTotalPage = (m_iTotalRecord/MAX_QUERY_COUNT)+(m_iTotalRecord%MAX_QUERY_COUNT?1:0);
	if (m_curPageIndex+1<iTotalPage)
	{
		m_CarTypeInfoVect.clear();
		++m_curPageIndex;
		if (OPERATE_DB_SUCCESS == ASGetCarTypeInfo(&m_carTypeSearchInfo,
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



void CASQueryTypeDlg::OnSmenuAsTypeDetail()
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌÐò´úÂë
	if(g_pMainDlg == NULL || m_carTypeList.GetSelectedCount()<=0)
		return;
	int selectIndex = m_carTypeList.GetSelectionMark();
	((CASModifyTypeDlg*)(g_pMainDlg->m_pages[IDD_DIALOG_AS_MODIFY_TYPE]))->SetOperateType(OPERATE_TYPE_SHOW,&m_CarTypeInfoVect[selectIndex]);
	g_pMainDlg->RightPageShow(IDD_DIALOG_AS_MODIFY_TYPE);
	CCarInfoSearchDlg::ShowOperateInfo("查看机型详细信息！");
}


void CASQueryTypeDlg::OnSmenuAsTypeModify()
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌÐò´úÂë
	if (!(CCarInfoSearchDlg::s_dwUserPower&USER_POWER_MODIFY))
	{
		CCarInfoSearchDlg::ShowOperateInfo("对不起，您没有操作权限！");
		return;
	}

	if(g_pMainDlg == NULL || m_carTypeList.GetSelectedCount()<=0)
		return;
	int selectIndex = m_carTypeList.GetSelectionMark();
	((CASModifyTypeDlg*)(g_pMainDlg->m_pages[IDD_DIALOG_AS_MODIFY_TYPE]))->SetOperateType(OPERATE_TYPE_MODIFY,&m_CarTypeInfoVect[selectIndex]);
	g_pMainDlg->RightPageShow(IDD_DIALOG_AS_MODIFY_TYPE);
	CCarInfoSearchDlg::ShowOperateInfo("修改机型详细信息！");
}


void CASQueryTypeDlg::OnSmenuAsTypeDelete()
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌÐò´úÂë
	if (!(CCarInfoSearchDlg::s_dwUserPower&USER_POWER_MODIFY))
	{
		CCarInfoSearchDlg::ShowOperateInfo("对不起，您没有操作权限！");
		return;
	}

	int selectIndex = m_carTypeList.GetSelectionMark();
	if(selectIndex<0)
		return;
	if(IDYES== MessageBox("是否删除当前选中的机型信息?\nWhether to delete this record?","提示(Notify)",MB_YESNO))
	{
		CString strTemp = m_carTypeList.GetItemText(selectIndex,1);
		if(OPERATE_DB_SUCCESS ==  ASDeleteCarTypeInfo(strTemp.operator LPCSTR()))
		{
			m_carTypeList.DeleteItem(selectIndex);
			CCarInfoSearchDlg::ShowOperateInfo("机型信息删除成功！");
		}
		else
		{
			CCarInfoSearchDlg::ShowOperateInfo("机型信息删除失败！");
		}
	}
}


void CASQueryTypeDlg::OnDblclkListAsType(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	OnSmenuAsTypeDetail();
	*pResult = 0;
}


void CASQueryTypeDlg::OnRclickListAsType(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	if(m_carTypeList.GetSelectedCount()>0)
	{
		NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
		if(pNMListView->iItem != -1)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
			CMenu menu;
			VERIFY( menu.LoadMenu( IDR_MENU_AS_CarTypeMenu ) );
			CMenu* popup = menu.GetSubMenu(0);
			ASSERT( popup != NULL );
			popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );
		}
	}
	*pResult = 0;
}




LRESULT CASQueryTypeDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà

	if (WM_USER_UPDATE == message)
	{
		m_CarTypeInfoVect.clear();
		ASGetCarTypeInfo(&m_carTypeSearchInfo,m_curPageIndex,MAX_QUERY_COUNT,m_CarTypeInfoVect,true);
		UpdateDataInfo();

		return TRUE;
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}


void CASQueryTypeDlg::UpdateDataInfo()
{
	m_carTypeList.SetRedraw(FALSE);
	//更新内容
	m_carTypeList.DeleteAllItems();
	int nRow;

	for(int i = 0 ; i < m_CarTypeInfoVect.size() ; ++i) 
	{ 
		nRow = m_carTypeList.InsertItem(i, m_CarTypeInfoVect[i].csCarTypeNum);//插入行
		m_carTypeList.SetItemText(nRow, 1, m_CarTypeInfoVect[i].csCarDetailTypeNum);//设置数据
		m_carTypeList.SetItemText(nRow, 2, m_CarTypeInfoVect[i].csCustomerCode);
		m_carTypeList.SetItemText(nRow, 3, m_CarTypeInfoVect[i].csCarFactory);
		m_carTypeList.SetItemText(nRow, 4, m_CarTypeInfoVect[i].csCarType);
		m_carTypeList.SetItemText(nRow, 5, m_CarTypeInfoVect[i].csCarName);
		m_carTypeList.SetItemText(nRow, 6, m_CarTypeInfoVect[i].csCarPattern);
		m_carTypeList.SetItemText(nRow, 7, m_CarTypeInfoVect[i].csEnginePattern);
		m_carTypeList.SetItemText(nRow, 8, m_CarTypeInfoVect[i].csMarkModel);
		m_carTypeList.SetItemText(nRow, 9, m_CarTypeInfoVect[i].strCarNotes.c_str());
	} 

	m_carTypeList.SetRedraw(TRUE);
	m_carTypeList.Invalidate();
	m_carTypeList.UpdateWindow();
}