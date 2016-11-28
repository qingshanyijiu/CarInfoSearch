// QuerySuppTypesDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CarInfoSearch.h"
#include "CarInfoSearchDlg.h"
#include "QuerySuppTypesDlg.h"
#include "afxdialogex.h"


// CQuerySuppTypesDlg 对话框

IMPLEMENT_DYNAMIC(CQuerySuppTypesDlg, CDialogEx)

CQuerySuppTypesDlg::CQuerySuppTypesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQuerySuppTypesDlg::IDD, pParent)
{

}

CQuerySuppTypesDlg::~CQuerySuppTypesDlg()
{
}

void CQuerySuppTypesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SUPP_CarType, m_suppCarTypeList);
}


BEGIN_MESSAGE_MAP(CQuerySuppTypesDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CQuerySuppTypesDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CQuerySuppTypesDlg 消息处理程序


BOOL CQuerySuppTypesDlg::OnInitDialog()
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
		SetDlgItemText(IDC_STATIC_CTP_NOTIFY,"请勾选所支持的机型编号:");
	}
	else
	{
		CString strTemp;
		strTemp.Format("零件: 机型编号为%s，DAE件号为%s，MMC件号为%s\n\r\n\r该零件支持的机型信息如下:",
			m_carPartTypeInfoKey.csCarTypeNum,m_carPartTypeInfoKey.csDAENum,m_carPartTypeInfoKey.csMMCNum);
		SetDlgItemText(IDC_STATIC_CTP_NOTIFY,strTemp);
	}

	m_suppCarTypeList.SetExtendedStyle(dwStyle); //设置扩展风格
	m_suppCarTypeList.InsertColumn( 0, "发动机编号", LVCFMT_LEFT, 180 );
	m_suppCarTypeList.InsertColumn( 1, "机型编号", LVCFMT_LEFT, 100 );
	m_suppCarTypeList.InsertColumn( 2, "车厂名称", LVCFMT_LEFT, 150 );
	m_suppCarTypeList.InsertColumn( 3, "机型状态", LVCFMT_LEFT, 120 );
	m_suppCarTypeList.InsertColumn( 4, "车型名称", LVCFMT_LEFT, 180 );

	UpdateDataInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}

void CQuerySuppTypesDlg::SetCartPartInfo(const PCarPartTableInfo pInfo,BYTE bOpType)
{
	m_opType = bOpType;
	m_carPartTypeInfoKey.Clear();
	strcpy(m_carPartTypeInfoKey.csCarTypeNum,pInfo->csCarTypeNum);
	strcpy(m_carPartTypeInfoKey.csDAENum,pInfo->csDAENum);
	strcpy(m_carPartTypeInfoKey.csMMCNum,pInfo->csMMCNum);

	m_suppCarTypeVect.clear();

	switch(bOpType)
	{
	case OPERATE_TYPE_ADD:
		GetCarTypePartsAllInfo(m_suppCarTypeVect);
		break;
	case OPERATE_TYPE_MODIFY:
		GetCarTypePartsSuppInfo(&m_carPartTypeInfoKey,m_suppCarTypeVect);
		break;
	case OPERATE_TYPE_SHOW:
		GetCarTypePartsSuppInfoEx(&m_carPartTypeInfoKey,m_suppCarTypeVect);
		break;
	}		
}


void CQuerySuppTypesDlg::OnOK()
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà

	if (OPERATE_TYPE_SHOW != m_opType)
	{
		vector<string> checkVect;
		GetCheckData(checkVect);

		if(OPERATE_DB_SUCCESS == UpdateCarTypePartsInfo(&m_carPartTypeInfoKey,checkVect))
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


void CQuerySuppTypesDlg::OnCancel()
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà
	if (OPERATE_TYPE_SHOW != m_opType)
	{
		if(IDYES== MessageBox("是否确定放弃修改?","提示",MB_YESNO))
		{
			CDialogEx::OnCancel();
		}
	}
	else
	{
		CDialogEx::OnCancel();
	}
}


void CQuerySuppTypesDlg::OnClose()
{
	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ

	CDialogEx::OnClose();
}


void CQuerySuppTypesDlg::GetCheckData(vector<string>& checkVect)
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

void CQuerySuppTypesDlg::UpdateDataInfo()
{
	m_suppCarTypeList.SetRedraw(FALSE);
	//更新内容
	m_suppCarTypeList.DeleteAllItems();
	int nRow;

	for(int i = 0 ; i < m_suppCarTypeVect.size() ; ++i) 
	{ 
		nRow = m_suppCarTypeList.InsertItem(i, m_suppCarTypeVect[i].csCarDetailTypeNum);//插入行
		m_suppCarTypeList.SetItemText(nRow, 1, m_suppCarTypeVect[i].csCarTypeNum);//设置数据
		m_suppCarTypeList.SetItemText(nRow, 2, m_suppCarTypeVect[i].csCarFactory);
		m_suppCarTypeList.SetItemText(nRow, 3, m_suppCarTypeVect[i].csCarStatus);
		m_suppCarTypeList.SetItemText(nRow, 4, m_suppCarTypeVect[i].csCarDetailName);

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

void CQuerySuppTypesDlg::OnBnClickedOk()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	CQuerySuppTypesDlg::OnOK();
}
