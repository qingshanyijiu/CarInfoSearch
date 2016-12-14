// ASModifySuppTypeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CarInfoSearch.h"
#include "ASModifySuppTypeDlg.h"
#include "CarInfoSearchDlg.h"
#include "afxdialogex.h"


// CASModifySuppTypeDlg 对话框

IMPLEMENT_DYNAMIC(CASModifySuppTypeDlg, CDialogEx)

CASModifySuppTypeDlg::CASModifySuppTypeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CASModifySuppTypeDlg::IDD, pParent)
{

}

CASModifySuppTypeDlg::~CASModifySuppTypeDlg()
{
}

void CASModifySuppTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_AS_SUPP, m_suppCarTypeList);
}


BEGIN_MESSAGE_MAP(CASModifySuppTypeDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CASModifySuppTypeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CASModifySuppTypeDlg 消息处理程序


BOOL CASModifySuppTypeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯

	LONG lStyle;
	lStyle = GetWindowLong(m_suppCarTypeList.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_suppCarTypeList.m_hWnd, GWL_STYLE, lStyle);//设置style
	DWORD dwStyle = m_suppCarTypeList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）

	if (OPERATE_TYPE_SHOW != m_opType)
	{
		dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
		SetDlgItemText(IDC_STATIC_ADD_SUPP_SHOW,"请勾选所支持的机型编号:\nPlease check the supported type number:");
	}
	else
	{
		CString strTemp;
		strTemp.Format("零件: 机型编号-%s,零件代号-%s,\t该零件支持的机型信息如下:\nPart: TypeNum-%s,PartNum-%s\t\tthe type supported the part of:", \
			m_carPartTypeInfoKey.csCarTypeNum,m_carPartTypeInfoKey.csPartNum,m_carPartTypeInfoKey.csCarTypeNum,m_carPartTypeInfoKey.csPartNum);
		SetDlgItemText(IDC_STATIC_ADD_SUPP_SHOW,strTemp);
	}
	m_suppCarTypeList.SetExtendedStyle(dwStyle); //设置扩展风格


	int iWidth = m_suppCarTypeList.GetListWidth();
	m_suppCarTypeList.InsertColumn( 0, "发动机编号\nEngineNum", LVCFMT_LEFT, (int)(iWidth*0.2) );
	m_suppCarTypeList.InsertColumn( 1, "机型编号\nTypeNum", LVCFMT_LEFT, (int)(iWidth*0.12) );
	m_suppCarTypeList.InsertColumn( 2, "客户代号\nTypeNum", LVCFMT_LEFT, (int)(iWidth*0.1) );
	m_suppCarTypeList.InsertColumn( 3, "车厂名称\nDepotName", LVCFMT_LEFT, (int)(iWidth*0.15) );
	m_suppCarTypeList.InsertColumn( 4, "整机类型\nCarType", LVCFMT_LEFT, (int)(iWidth*0.15) );
	m_suppCarTypeList.InsertColumn( 5, "车型名称\nTypeName", LVCFMT_LEFT, (int)(iWidth*0.2) );

	m_suppCarTypeList.InitHead();


	UpdateDataInfo();


	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}

void CASModifySuppTypeDlg::SetCartPartInfo(const PASCarPartTableInfo pInfo,BYTE bOpType)
{
	m_opType = bOpType;
	m_carPartTypeInfoKey.Clear();
	strcpy(m_carPartTypeInfoKey.csCarTypeNum,pInfo->csCarTypeNum);
	strcpy(m_carPartTypeInfoKey.csPartNum,pInfo->csPartNum);

	m_suppCarTypeVect.clear();

	switch(bOpType)
	{
	case OPERATE_TYPE_ADD:
		ASGetCarTypePartsAllInfo(m_suppCarTypeVect);
		break;
	case OPERATE_TYPE_MODIFY:
		ASGetCarTypePartsSuppInfo(&m_carPartTypeInfoKey,m_suppCarTypeVect);
		break;
	case OPERATE_TYPE_SHOW:
		ASGetCarTypePartsSuppInfoEx(&m_carPartTypeInfoKey,m_suppCarTypeVect);
		break;
	}		
}


BOOL CASModifySuppTypeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà

	/*if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_ESCAPE: //Esc按键事件
			return true;
		case VK_RETURN: //Enter按键事件
			return true;
		}
	}*/

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CASModifySuppTypeDlg::OnOK()
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà

	if (OPERATE_TYPE_SHOW != m_opType)
	{
		vector<string> checkVect;
		GetCheckData(checkVect);

		if(OPERATE_DB_SUCCESS == ASUpdateCarTypePartsInfo(&m_carPartTypeInfoKey,checkVect))
		{
			CCarInfoSearchDlg::ShowOperateInfo("增加修改零件支持的机型成功！");
			CDialogEx::OnOK();
		}
		else
		{
			CCarInfoSearchDlg::ShowOperateInfo("增加修改零件支持的机型失败！");
		}
	}
	else
	{
		CDialogEx::OnOK();
	}
}


void CASModifySuppTypeDlg::OnCancel()
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà

	if (OPERATE_TYPE_SHOW != m_opType)
	{
		if(IDYES== MessageBox("是否确定放弃修改?\nWhether to give up modification?","提示(Notify)",MB_YESNO))
		{
			CDialogEx::OnCancel();
		}
	}
	else
	{
		CDialogEx::OnCancel();
	}
}


void CASModifySuppTypeDlg::OnBnClickedOk()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	CASModifySuppTypeDlg::OnOK();
}


void CASModifySuppTypeDlg::GetCheckData(vector<string>& checkVect)
{
	CString strTemp;
	for (int i=0;i<m_suppCarTypeList.GetItemCount();++i)
	{
		if (m_suppCarTypeList.GetCheck(i))
		{
			strTemp = m_suppCarTypeList.GetItemText(i,0);
			checkVect.push_back(strTemp.operator LPCSTR());
		}
	}
}

void CASModifySuppTypeDlg::UpdateDataInfo()
{
	m_suppCarTypeList.SetRedraw(FALSE);
	//更新内容
	m_suppCarTypeList.DeleteAllItems();
	int nRow;

	for(int i = 0 ; i < m_suppCarTypeVect.size() ; ++i) 
	{ 
		nRow = m_suppCarTypeList.InsertItem(i, m_suppCarTypeVect[i].csCarDetailTypeNum);//插入行
		m_suppCarTypeList.SetItemText(nRow, 1, m_suppCarTypeVect[i].csCarTypeNum);//设置数据
		m_suppCarTypeList.SetItemText(nRow, 2, m_suppCarTypeVect[i].csCustomerCode);
		m_suppCarTypeList.SetItemText(nRow, 3, m_suppCarTypeVect[i].csCarFactory);
		m_suppCarTypeList.SetItemText(nRow, 4, m_suppCarTypeVect[i].csCarType);
		m_suppCarTypeList.SetItemText(nRow, 5, m_suppCarTypeVect[i].csCarName);

		if (m_opType != OPERATE_TYPE_SHOW)
		{
			if (m_suppCarTypeVect[i].strCarReserve.size())
			{
				m_suppCarTypeList.SetCheck(i);
			}
		}
	} 

	m_suppCarTypeList.SetRedraw(TRUE);
	m_suppCarTypeList.Invalidate();
	m_suppCarTypeList.UpdateWindow();
}