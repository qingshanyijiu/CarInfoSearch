
// CarInfoSearchDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "CarInfoSearch.h"
#include "CarInfoSearchDlg.h"
#include "afxdialogex.h"
#include "CarTypeMngQueryDlg.h"
#include "CarTypeInfoDlg.h"
#include "CarPartInfoDlg.h"
#include "CarPartInfoQueryDlg.h"
#include "QueryCarTypePartsDlg.h"
#include "QueryFileInfoDlg.h"
#include "SystemSetDlg.h"
#include "ButtonExd.h"
#include "LoginDlg.h"
#include "PWDModifyDlg.h"
#include "FileModifyDlg.h"
#include "LoadDataDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define  BTN_ROOT 0
#define  BUTTON_SIZE_ADJUST			(10)		
CCarInfoSearchDlg*	g_pMainDlg = NULL;


static UINT s_indicators[]=
{
	IDS_STR_COMPANY,
	IDS_STR_OPRESULT,
	IDS_STR_ListInfo
}; 

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
// 对话框数据
	enum { IDD = IDD_ABOUTBOX };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnSmenuCarTypedelete();
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
};
CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_COMMAND(ID_SMENU_CarTypeDelete, &CAboutDlg::OnSmenuCarTypedelete)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CCarInfoSearchDlg 对话框

void GetThisDllPath(string& strPath)
{
	CHAR tcDllPath[MAX_PATH]={0};

	::GetModuleFileName(NULL,tcDllPath,MAX_PATH);
	strPath = tcDllPath;

	ULONG iPos = strPath.rfind('\\');
	if (string::npos != iPos)
		strPath = strPath.substr(0,iPos+1);
	else
		strPath.empty();
}

unsigned long	CCarInfoSearchDlg::s_dwUserPower=3;
std::string     CCarInfoSearchDlg::s_curPath;

CCarInfoSearchDlg::CCarInfoSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCarInfoSearchDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pCurrentWnd = NULL;
	m_root = new CButtonExd();
	m_root->InitBtnMap();
	g_pMainDlg = this;

	GetThisDllPath(s_curPath);
}

CCarInfoSearchDlg::~CCarInfoSearchDlg()
{
	CloseDb();

	std::map<long,CDialog *>::iterator it = m_pages.begin();
	while (it!= m_pages.end())
	{
		delete it->second;
		++it;
	}

	if (m_root)
	{
		delete m_root;
	}
}

void CCarInfoSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CCarInfoSearchDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_SysAbout, &CCarInfoSearchDlg::OnBnClickedButtonSysabout)
	ON_BN_CLICKED(IDC_BUTTON_PASSWORD_SET, &CCarInfoSearchDlg::OnBnClickedButtonPasswordSet)
	ON_COMMAND_RANGE(IDS_STR_COMPANY,IDS_STR_OPRESULT,NULL)
	ON_WM_CREATE()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()
// CCarInfoSearchDlg 消息处理程序
BOOL CCarInfoSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 将“关于...”菜单项添加到系统菜单中。
	/*// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	*/
	// TODO: 在此添加额外的初始化代码

	OpenDb("CarPartInfoSave.db");

	CLoginDlg loginDlg(&m_userInfo,this);
	if (IDOK == loginDlg.DoModal())
	{
		s_dwUserPower = m_userInfo.uKey;
	}
	else
	{
		//PostMessage(WM_CLOSE,0,0);
		CloseDb();
		exit(0);
		return FALSE;
	}


	CDialog* pWnd = nullptr; 
	//查询
	pWnd = new CCarTypeInfoDlg();
	pWnd->Create(IDD_CarTypeMNG_MODIFY_DLG,this);
	ShowParamDlg(pWnd,FALSE);
	m_pages[IDD_CarTypeMNG_MODIFY_DLG] = pWnd;

	pWnd = new CCarTypeMngQueryDlg();
	pWnd->Create(IDD_CarTypeMNG_QUERY_DLG,this);
	ShowParamDlg(pWnd,FALSE);
	m_pages[IDD_CarTypeMNG_QUERY_DLG] = pWnd;

	pWnd = new CCarPartInfoQueryDlg();
	pWnd->Create(IDD_MaintenanceMng_QUERY_Dlg,this);
	ShowParamDlg(pWnd,FALSE);
	m_pages[IDD_MaintenanceMng_QUERY_Dlg] = pWnd;

	pWnd = new CCarPartInfoDlg();
	pWnd->Create(IDD_MaintenanceMng_MODIFY_Dlg,this);
	ShowParamDlg(pWnd,FALSE);
	m_pages[IDD_MaintenanceMng_MODIFY_Dlg] = pWnd;

	pWnd = new CQueryFileInfoDlg();
	pWnd->Create(IDD_DIALOG_FILE_QUERY,this);
	ShowParamDlg(pWnd,FALSE);
	m_pages[IDD_DIALOG_FILE_QUERY] = pWnd;

	pWnd = new CFileModifyDlg();
	pWnd->Create(IDD_DIALOG_FILE_MODIFY,this);
	ShowParamDlg(pWnd,FALSE);
	m_pages[IDD_DIALOG_FILE_MODIFY] = pWnd;

	pWnd = new CQueryCarTypePartsDlg();
	pWnd->Create(IDD_DIALOG_CarTypeParts,this);
	ShowParamDlg(pWnd,FALSE);
	m_pages[IDD_DIALOG_CarTypeParts] = pWnd;

	//系统设置
	//基本配置
	pWnd = new CSystemSetDlg();
	pWnd->Create(IDD_SYSSET_BASIC_DLG,this);
	ShowParamDlg(pWnd,FALSE);
	m_pages[IDD_SYSSET_BASIC_DLG] = pWnd;

	pWnd = new CPWDModifyDlg(&m_userInfo);
	pWnd->Create(IDD_DIALOG_Password_Modify,this);
	ShowParamDlg(pWnd,FALSE);
	m_pages[IDD_DIALOG_Password_Modify] = pWnd;

	pWnd = new CDialogEx();
	pWnd->Create(IDD_DIALOG_SYSAbout,this);
	ShowParamDlg(pWnd,FALSE);
	m_pages[IDD_DIALOG_SYSAbout] = pWnd;

	pWnd = new CLoadDataDlg();
	pWnd->Create(IDD_DIALOG_LOAD_DATA,this);
	ShowParamDlg(pWnd,FALSE);
	m_pages[IDD_DIALOG_LOAD_DATA] = pWnd;
	
	
	int leftpad =0,toppad =-1;
	CButtonExd *pCurrent=m_root,*pChild =NULL;
	CRect PRect,ChildRect,FuncMenuRC,changeSizeRect(0,0,0,BUTTON_SIZE_ADJUST);
	GetDlgItem(IDC_STATIC_FuncMenu)->GetWindowRect(&FuncMenuRC);
	ScreenToClient(&FuncMenuRC);
	
	GetDlgItem(IDC_BTN_CarTypeMNG)->GetWindowRect(&PRect);
	PRect += changeSizeRect;
	GetDlgItem(IDC_BTN_CarTypeMNG)->MoveWindow(FuncMenuRC.left,FuncMenuRC.top+20,FuncMenuRC.Width(),PRect.Height());
	pChild= new CButtonExd(this,(CButton*)GetDlgItem(IDC_BTN_CarTypeMNG),_T("查询管理"),IDC_BTN_CarTypeMNG,0,toppad);	
	pCurrent->AddChild(pChild);
	pChild->SetAfterLBClickDealFunc(std::tr1::bind(&CCarInfoSearchDlg::AfterButtonClick, this,std::tr1::placeholders::_1));
	pChild->SetAbsolutePos(true);
	pCurrent = pChild;
	GetDlgItem(IDC_BUTTON_QCarTypeParts)->GetWindowRect(&ChildRect);
	pChild= new CButtonExd(this,(CButton*)GetDlgItem(IDC_BUTTON_QCarTypeParts),_T("综合查询"),IDC_BUTTON_QCarTypeParts,PRect.Width()-ChildRect.Width(),toppad);
	pChild->SetAfterLBClickDealFunc(std::tr1::bind(&CCarInfoSearchDlg::OnBnClickedButtonnCarTypePartsQuery, this));
	pCurrent->AddChild(pChild);
	GetDlgItem(IDC_BTN_CarTypeQUERY)->GetWindowRect(&ChildRect);
	pChild= new CButtonExd(this,(CButton*)GetDlgItem(IDC_BTN_CarTypeQUERY),_T("机型查询"),IDC_BTN_CarTypeQUERY,0,toppad);
	pChild->SetAfterLBClickDealFunc(std::tr1::bind(&CCarInfoSearchDlg::OnBnClickedBtnCarTypequery, this));
	pCurrent->AddChild(pChild);
	GetDlgItem(IDC_BTN_MTQUERY)->GetWindowRect(&ChildRect);
	pChild= new CButtonExd(this,(CButton*)GetDlgItem(IDC_BTN_MTQUERY),_T("配件查询"),IDC_BTN_MTQUERY,0,toppad);
	pChild->SetAfterLBClickDealFunc(std::tr1::bind(&CCarInfoSearchDlg::OnBnClickedBtnMtquery, this));
	pCurrent->AddChild(pChild);

	if (s_dwUserPower&USER_POWER_FILE_MANAGER)
	{
		GetDlgItem(IDC_BUTTON_FILE_QUERY)->GetWindowRect(&ChildRect);
		pChild= new CButtonExd(this,(CButton*)GetDlgItem(IDC_BUTTON_FILE_QUERY),_T("资料查询"),IDC_BUTTON_FILE_QUERY,0,toppad);
		pChild->SetAfterLBClickDealFunc(std::tr1::bind(&CCarInfoSearchDlg::OnBnClickedButtonFileQuery, this));
		pCurrent->AddChild(pChild);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_FILE_QUERY)->ShowWindow(SW_HIDE);
	}


	if (s_dwUserPower&USER_POWER_MODIFY)
	{
		pCurrent=m_root;
		GetDlgItem(IDC_BTN_MTINFOMNG)->GetWindowRect(&PRect);
		GetDlgItem(IDC_BTN_CarTypeMNG)->MoveWindow(FuncMenuRC.left,FuncMenuRC.top+20,FuncMenuRC.Width(),PRect.Height());
		pChild= new CButtonExd(this,(CButton*)GetDlgItem(IDC_BTN_MTINFOMNG),_T("信息录入"),IDC_BTN_MTINFOMNG,0,toppad);	
		pChild->SetAfterLBClickDealFunc(std::tr1::bind(&CCarInfoSearchDlg::AfterButtonClick, this,std::tr1::placeholders::_1));
		pCurrent->AddChild(pChild);
		pCurrent = pChild;
		GetDlgItem(IDC_BTN_CarTypeMODIFY)->GetWindowRect(&ChildRect);
		pChild= new CButtonExd(this,(CButton*)GetDlgItem(IDC_BTN_CarTypeMODIFY),_T("车类型信息录入"),IDC_BTN_CarTypeMODIFY,PRect.Width()-ChildRect.Width(),toppad);
		pChild->SetAfterLBClickDealFunc(std::tr1::bind(&CCarInfoSearchDlg::OnBnClickedBtnCarTypemodify, this));
		pCurrent->AddChild(pChild);
		GetDlgItem(IDC_BTN_MTMODIFY)->GetWindowRect(&ChildRect);
		pChild= new CButtonExd(this,(CButton*)GetDlgItem(IDC_BTN_MTMODIFY),_T("配件信息录入"),IDC_BTN_MTMODIFY,0,toppad);
		pChild->SetAfterLBClickDealFunc(std::tr1::bind(&CCarInfoSearchDlg::OnBnClickedBtnMtmodify, this));
		pCurrent->AddChild(pChild);

		if (s_dwUserPower&USER_POWER_FILE_MANAGER)
		{
			GetDlgItem(IDC_BUTTON_FILE_MODUFIY)->GetWindowRect(&ChildRect);
			pChild= new CButtonExd(this,(CButton*)GetDlgItem(IDC_BUTTON_FILE_MODUFIY),_T("资料录入"),IDC_BUTTON_FILE_MODUFIY,0,toppad);
			pChild->SetAfterLBClickDealFunc(std::tr1::bind(&CCarInfoSearchDlg::OnBnClickedButtonFileModify, this));
			pCurrent->AddChild(pChild);
		}
		else
		{
			GetDlgItem(IDC_BUTTON_FILE_MODUFIY)->ShowWindow(SW_HIDE);
		}

		if (s_dwUserPower&USER_POWER_LOAD_DATA)
		{
			GetDlgItem(IDC_BUTTON_FILE_LOAD)->GetWindowRect(&ChildRect);
			pChild= new CButtonExd(this,(CButton*)GetDlgItem(IDC_BUTTON_FILE_LOAD),_T("数据导入"),IDC_BUTTON_FILE_LOAD,0,toppad);
			pChild->SetAfterLBClickDealFunc(std::tr1::bind(&CCarInfoSearchDlg::OnBnClickedButtonFileLoadData, this));
			pCurrent->AddChild(pChild);
		}
		else
		{
			GetDlgItem(IDC_BUTTON_FILE_LOAD)->ShowWindow(SW_HIDE);
		}
	}
	else
	{
		GetDlgItem(IDC_BTN_MTINFOMNG)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_CarTypeMODIFY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_MTMODIFY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_FILE_MODUFIY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_FILE_LOAD)->ShowWindow(SW_HIDE);
	}
	
	pCurrent=m_root;
	GetDlgItem(IDC_BUTTON_SystemSet)->GetWindowRect(&PRect);
	GetDlgItem(IDC_BTN_CarTypeMNG)->MoveWindow(FuncMenuRC.left,FuncMenuRC.top+20,FuncMenuRC.Width(),PRect.Height());
	pChild= new CButtonExd(this,(CButton*)GetDlgItem(IDC_BUTTON_SystemSet),_T("系统设置"),IDC_BUTTON_SystemSet,0,toppad);	
	pChild->SetAfterLBClickDealFunc(std::tr1::bind(&CCarInfoSearchDlg::AfterButtonClick, this,std::tr1::placeholders::_1));
	pCurrent->AddChild(pChild);
	pCurrent = pChild;
	GetDlgItem(IDC_BUTTON_BasicSet)->GetWindowRect(&ChildRect);
	pChild= new CButtonExd(this,(CButton*)GetDlgItem(IDC_BUTTON_BasicSet),_T("基本设置"),IDC_BUTTON_BasicSet,PRect.Width()-ChildRect.Width(),toppad);
	pChild->SetAfterLBClickDealFunc(std::tr1::bind(&CCarInfoSearchDlg::OnBnClickedButtonBasicset, this));
	pCurrent->AddChild(pChild);
	GetDlgItem(IDC_BUTTON_PASSWORD_SET)->GetWindowRect(&ChildRect);
	pChild= new CButtonExd(this,(CButton*)GetDlgItem(IDC_BUTTON_PASSWORD_SET),_T("密码管理"),IDC_BUTTON_PASSWORD_SET,0,toppad);
	pChild->SetAfterLBClickDealFunc(std::tr1::bind(&CCarInfoSearchDlg::OnBnClickedButtonPasswordSet, this));
	pCurrent->AddChild(pChild);
	GetDlgItem(IDC_BUTTON_SysAbout)->GetWindowRect(&ChildRect);
	pChild= new CButtonExd(this,(CButton*)GetDlgItem(IDC_BUTTON_SysAbout),_T("关于"),IDC_BUTTON_SysAbout,0,toppad);
	pChild->SetAfterLBClickDealFunc(std::tr1::bind(&CCarInfoSearchDlg::OnBnClickedButtonSysabout, this));
	pCurrent->AddChild(pChild);
	m_root->Show();
	m_root->Expand();

	CRect rect;
	GetClientRect(rect);
	//添加状态栏信息
	m_statusBar.MoveWindow(14,rect.bottom-23,rect.right,23);// 调整状态栏的位置和大小
	m_statusBar.SetPaneInfo(0,m_statusBar.GetDlgCtrlID(),SBPS_NORMAL,400); 
	m_statusBar.SetPaneInfo(1,m_statusBar.GetDlgCtrlID(),SBPS_NORMAL,600);
	m_statusBar.SetPaneInfo(2,m_statusBar.GetDlgCtrlID(),SBPS_NORMAL,800);

	CString strConfigName = s_curPath.c_str();
	strConfigName += "CarInfoSearch.ini";
	char csTempStr[MAX_PATH]={0};
	GetPrivateProfileString("ShowInfo","CompanyName","广州市利迅汽车配件有限公司",csTempStr,MAX_PATH,strConfigName);
	m_statusBar.UpdateRowString(0,csTempStr);

	AfterButtonClick(m_root);
	OnBnClickedButtonnCarTypePartsQuery();
	ShowResultInfo("欢迎使用利迅博马斯（发动机）查询系统！");
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CCarInfoSearchDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CCarInfoSearchDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();


		/*CPaintDC   dc(this);   
		CRect   rect;   
		GetClientRect(&rect);   
		CDC   dcMem;   
		dcMem.CreateCompatibleDC(&dc);   
		CBitmap   bmpBackground;   
		bmpBackground.LoadBitmap(IDB_BITMAP);   //IDB_BITMAP是你自己的图对应的ID   ，由于我刚刚加入的位图资源 
		//被我命名成了IDB_Bg，因而我这句就是bmpBackground.LoadBitmap(IDB_Bg);  
		BITMAP   bitmap;   
		bmpBackground.GetBitmap(&bitmap);   
		CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   
		dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,   
			bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);  */
	}
}
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCarInfoSearchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
BOOL CCarInfoSearchDlg::ShowParamDlg(CWnd* pWnd, BOOL bShow)
{
	if (pWnd == NULL)
	{
		return FALSE;
	}
	CRect rc;
	GetDlgItem(IDC_PlaceHolder)->GetWindowRect(&rc);
	ScreenToClient(&rc);

	rc.top -= 20;
	pWnd->MoveWindow(&rc);
	return pWnd->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
}
void CCarInfoSearchDlg::TestBofore(void * p)
{
	CButtonExd* pButtonexd = (CButtonExd*)p;
	MessageBox(_T("before"));
	MessageBox(pButtonexd->GetName());
}
void CCarInfoSearchDlg::TestAfter(void* p)
{
	MessageBox(_T("after"));
}
void CCarInfoSearchDlg::AfterButtonClick(void * p)
{
	CButtonExd* pButtonexd = (CButtonExd*)p;
	if(pButtonexd->IsExpand())
		Expand(pButtonexd->GetIndex());
}
void CCarInfoSearchDlg::Expand(int index)
{
	if(m_root == NULL)
		return;
	int BigMenus = m_root->m_Childs.size();
	if(index >BigMenus-1)
		return;
	if( !m_root->m_Childs[index]->IsShow())
		return;
/*
	if(m_root->m_Childs[index]->IsExpand())
		return;
	m_root->m_Childs[index]->Expand();*/
	for (int i=BigMenus-1;i>=0;--i)
	{
		if(i!=index)
		{
			m_root->m_Childs[i]->Folded();
		}
	}
	if(index<BigMenus-1)
	{
		CRect rc = m_root->m_Childs[BigMenus-1]->GetRect();
		CRect FuncMenuRC;
		GetDlgItem(IDC_STATIC_FuncMenu)->GetWindowRect(&FuncMenuRC);
		ScreenToClient(&FuncMenuRC);
		int toppad = FuncMenuRC.bottom-rc.bottom;
		m_root->m_Childs[index]->Revise(0,toppad);
	}
}
void CCarInfoSearchDlg::OnBnClickedBtnCarTypemng()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	/*if (m_pCurrentWnd != NULL)
	{
		m_pCurrentWnd->ShowWindow(SW_HIDE);
	}
	m_pCurrentWnd = m_pages.at(0);
	m_pCurrentWnd->ShowWindow(SW_SHOW);*/
	return;
	if(m_root->m_Childs[0]->IsExpand())
		m_root->m_Childs[0]->Folded();
	else
		Expand(0);
}
void CCarInfoSearchDlg::OnBnClickedBtnMtinfomng()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	if(m_root->m_Childs[1]->IsExpand())
		m_root->m_Childs[1]->Folded();
	else
		Expand(1);
}
void CCarInfoSearchDlg::OnBnClickedButtonSystemset()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	if(m_root->m_Childs[2]->IsExpand())
		m_root->m_Childs[2]->Folded();
	else
		Expand(2);
}
void CCarInfoSearchDlg::RightPageShow(long DLGID,bool bUpdate/*=false*/)
{
	if(m_pages[DLGID] == NULL)
		return;
	if (m_pCurrentWnd != NULL)
	{
		m_pCurrentWnd->ShowWindow(SW_HIDE);
	}
	m_pCurrentWnd = m_pages[DLGID];
	m_pCurrentWnd->ShowWindow(SW_SHOW);

	if (bUpdate)
	{
		m_pCurrentWnd->SendMessage(WM_USER_UPDATE);
	}
}
void CCarInfoSearchDlg::OnBnClickedBtnCarTypequery()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	RightPageShow(IDD_CarTypeMNG_QUERY_DLG);
}
void CCarInfoSearchDlg::OnBnClickedButtonnCarTypePartsQuery()
{
	RightPageShow(IDD_DIALOG_CarTypeParts);
}
void CCarInfoSearchDlg::OnBnClickedBtnCarTypemodify()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	RightPageShow(IDD_CarTypeMNG_MODIFY_DLG);
	((CCarTypeInfoDlg*)m_pages[IDD_CarTypeMNG_MODIFY_DLG])->SetOperateType(OPERATE_TYPE_ADD);
}
void CCarInfoSearchDlg::OnBnClickedBtnMtquery()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	RightPageShow(IDD_MaintenanceMng_QUERY_Dlg);
}
void CCarInfoSearchDlg::OnBnClickedBtnMtmodify()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	RightPageShow(IDD_MaintenanceMng_MODIFY_Dlg);
	((CCarPartInfoDlg*)m_pages[IDD_MaintenanceMng_MODIFY_Dlg])->SetOperateType(OPERATE_TYPE_ADD);
}
void CCarInfoSearchDlg::OnBnClickedButtonBasicset()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	RightPageShow(IDD_SYSSET_BASIC_DLG);
}
BOOL CCarInfoSearchDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà
	if(CButtonExd::OnCommond(m_root,wParam,lParam))
		return true; 
	return CDialogEx::OnCommand(wParam, lParam);
}
BOOL CCarInfoSearchDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà
	return CDialogEx::PreTranslateMessage(pMsg);
}
HBRUSH CCarInfoSearchDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  Change any attributes of the DC here
// 	switch (pWnd->GetDlgCtrlID())
// 	{
// 	case IDC_STATIC_ShowResult:
// 		pDC->SetTextColor(RGB(255,0,0));
// 		break;
// 	case IDS_STR_OPRESULT:
// 		pDC->SetTextColor(RGB(255,0,0));
// 		break;
// 	}

	/*
	if(nCtlColor==CTLCOLOR_BTN)          //更改按钮颜色
	{
	//pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0,0,0));
	pDC->SetBkColor(RGB(121,121,255));   
	HBRUSH b=CreateSolidBrush(RGB(121,121,255));
	return b;
	}
	else if(nCtlColor==CTLCOLOR_SCROLLBAR)  //
	{
	//pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0,0,0));
	pDC->SetBkColor(RGB(233,233,220));
	HBRUSH b=CreateSolidBrush(RGB(233,233,220));
	return b;
	}
	else if(nCtlColor==CTLCOLOR_EDIT)   //更改编辑框
	{
	//pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0,0,0));
	pDC->SetBkColor(RGB(165,254,236));
	HBRUSH b=CreateSolidBrush(RGB(165,254,236));
	return b;
	}
	else if(nCtlColor==CTLCOLOR_STATIC)  //更改静态文本
	{
	pDC->SetTextColor(RGB(0,0,0));
	pDC->SetBkColor(RGB(166,254,1));
	HBRUSH b=CreateSolidBrush(RGB(166,254,1));
	return b;
	}
	else if(nCtlColor==CTLCOLOR_DLG)   //更改对话框背景色
	{
	pDC->SetTextColor(RGB(0,0,0));
	pDC->SetBkColor(RGB(166,254,1));
	HBRUSH b=CreateSolidBrush(RGB(166,254,1));
	return b;
	}
	*/
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
void CCarInfoSearchDlg::ShowResultInfo(const char* lpShowInfo)
{
	m_statusBar.UpdateRowString(1,lpShowInfo);
}
void CCarInfoSearchDlg::ShowOperateInfo(const char* lpShowInfo)
{
	g_pMainDlg->ShowResultInfo(lpShowInfo);
}

void CCarInfoSearchDlg::ShowOperateInfoEx(const char* lpShowInfo)
{
	g_pMainDlg->ShowResultInfo(lpShowInfo);
	g_pMainDlg->m_statusBar.UpdateRowString(2,"");
}

void CCarInfoSearchDlg::OnBnClickedButtonSysabout()
{
	// TODO: Add your control notification handler code here
	RightPageShow(IDD_DIALOG_SYSAbout);
}


void CCarInfoSearchDlg::OnBnClickedButtonPasswordSet()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	RightPageShow(IDD_DIALOG_Password_Modify);
}

BOOL CAboutDlg::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà

	return CDialogEx::Create(lpszTemplateName, pParentWnd);
}


int CAboutDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ÔÚ´ËÌí¼ÓÄú×¨ÓÃµÄ´´½¨´úÂë
	return 0;
}


int CCarInfoSearchDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ÔÚ´ËÌí¼ÓÄú×¨ÓÃµÄ´´½¨´úÂë

	if( !m_statusBar.CreateEx(this,0,WS_CHILD | WS_VISIBLE,AFX_IDW_STATUS_BAR)|| !m_statusBar.SetIndicators(s_indicators,sizeof(s_indicators)/sizeof(UINT)) )
	{
		TRACE0("Can't create status bar\n");
		return FALSE;
	}

	for (int i=0;i<3; i++)
	{
		// Change Status Bar style to make it Owner-drawn
		m_statusBar.GetStatusBarCtrl().SetText("", i, SBT_OWNERDRAW); 

		// Make each pane's of same size
		m_statusBar.SetPaneInfo( i, m_statusBar.GetItemID(i), SBPS_STRETCH, NULL );
	}
	return 0;
}


void CCarInfoSearchDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ	

	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CCarInfoSearchDlg::ShowSearchRecord(int iTotalCount,int iCurPape)
{
	g_pMainDlg->ShowSearchInfo(iTotalCount,iCurPape);
}

void CCarInfoSearchDlg::ShowSearchInfo(int iTotalCount,int iCurPape)
{
	CString strtemp;
	int iTotalPapes = iTotalCount/MAX_QUERY_COUNT;
	if (0 != iTotalCount%MAX_QUERY_COUNT)
	{
		++iTotalPapes;
	}
	strtemp.Format("第%d/%d页,共%d条记录!",iCurPape>iTotalPapes?iTotalPapes:iCurPape,iTotalPapes,iTotalCount);

	m_statusBar.UpdateRowString(2,strtemp.operator LPCSTR());

}

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯



	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}


void CCarInfoSearchDlg::OnBnClickedButtonFileModify()
{
	RightPageShow(IDD_DIALOG_FILE_MODIFY);
	((CFileModifyDlg*)m_pages[IDD_DIALOG_FILE_MODIFY])->SetOperateType(OPERATE_TYPE_ADD);
}

void CCarInfoSearchDlg::OnBnClickedButtonFileQuery()
{
	RightPageShow(IDD_DIALOG_FILE_QUERY);
	
}

void CCarInfoSearchDlg::OnBnClickedButtonFileLoadData()
{
	RightPageShow(IDD_DIALOG_LOAD_DATA);
}