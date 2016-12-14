// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CarInfoSearch.h"
#include "CarInfoSearchDlg.h"
#include "CheckKeyDlg.h"
#include "afxdialogex.h"


#define WM_KEY_CHECK_ERR	(WM_USER+101)

BOOL GetMacByCmd(CStringArray& strMacArray)
{
	BOOL bret; 

	SECURITY_ATTRIBUTES sa; 
	HANDLE hReadPipe,hWritePipe; 

	sa.nLength = sizeof(SECURITY_ATTRIBUTES); 
	sa.lpSecurityDescriptor = NULL; 
	sa.bInheritHandle = TRUE; 

	//创建管道
	bret = CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);
	if(!bret)
	{
		return FALSE;
	}

	//控制命令行窗口信息
	STARTUPINFO si; 
	//返回进程信息
	PROCESS_INFORMATION pi; 

	si.cb = sizeof(STARTUPINFO); 
	GetStartupInfo(&si); 
	si.hStdError = hWritePipe; 
	si.hStdOutput = hWritePipe; 
	si.wShowWindow = SW_HIDE; //隐藏命令行窗口
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	//命令行输出缓冲大小
	const long MAX_COMMAND_SIZE = 10000;

	//获取MAC命令行
	char szFetCmd[] = "ipconfig /all";
	//网卡MAC地址的前导信息
	const string  strSearch[2] = {"物理地址","Physical Address"};


	//创建获取命令行进程
	bret = CreateProcess (NULL, szFetCmd, NULL, NULL, TRUE, 0, NULL, 
		NULL, &si, &pi ); 

	bool bTerimate = false;

	if (bret) 
	{ 
		bTerimate = WaitForSingleObject (pi.hProcess, 2000)==WAIT_TIMEOUT?true:false; 
		unsigned long count;
		CloseHandle(hWritePipe);

		char szBuffer[MAX_COMMAND_SIZE+1]={0}; //放置命令行输出缓冲区
		bret  =  ReadFile(hReadPipe,  szBuffer,  MAX_COMMAND_SIZE,  &count,  0);
		if(!bret)
		{
			//关闭所有的句柄
			CloseHandle(hWritePipe);
			CloseHandle(pi.hProcess); 
			CloseHandle(pi.hThread); 
			CloseHandle(hReadPipe);
			return FALSE;
		}
		else
		{
			string strBuffer = szBuffer;
			int index = 0,iPos=-1;

			iPos = strBuffer.find(strSearch[index]);
			if (iPos== string::npos)
			{
				++index;
				iPos = strBuffer.find(strSearch[index]);
			}

			string strMac;
			if (iPos != string::npos)
			{
				do 
				{
					iPos = strBuffer.find(':',iPos+strSearch[index].length());
					strBuffer = strBuffer.substr(iPos+2);
					iPos = strBuffer.find("\n");
					strMac = strBuffer.substr(0, iPos-1);

					if (strMac.length() != 17)
					{
						break;
					}
					strMacArray.Add(strMac.c_str());

					strBuffer = strBuffer.substr(iPos);
					if (strBuffer.size()>0)
					{
						iPos = strBuffer.find(strSearch[index]);
					}
					else
					{
						break;
					}
				} while (iPos != string::npos );

			}

		}
	}
	else
	{
		CloseHandle(hWritePipe);
	}

	if(bTerimate)
		TerminateProcess(pi.hProcess,0);


	//关闭所有的句柄
	CloseHandle(pi.hProcess); 
	CloseHandle(pi.hThread); 
	CloseHandle(hReadPipe);
	return TRUE;
}

// CCheckKeyDlg 对话框

IMPLEMENT_DYNAMIC(CCheckKeyDlg, CDialogEx)

CCheckKeyDlg::CCheckKeyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCheckKeyDlg::IDD, pParent)
{
	m_strIniPath = CCarInfoSearchDlg::s_curPath.c_str();
	m_strIniPath += "CarInfoSearch.ini";
	GetMacByCmd(m_strMacArray);
}

CCheckKeyDlg::~CCheckKeyDlg()
{
}

void CCheckKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCheckKeyDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCheckKeyDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCheckKeyDlg::OnBnClickedCancel)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CCheckKeyDlg 消息处理程序


void CCheckKeyDlg::OnBnClickedOk()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	CString strTemp;
	GetDlgItemText(IDC_EDIT_CheckKey,strTemp);
	strTemp.Trim();
	if (strTemp.IsEmpty())
	{
		::AfxMessageBox("请输入授权码！");
		return ;
	}

	WritePrivateProfileString("UseKey","KeyValue",strTemp,m_strIniPath.c_str());
	if (CheckKeyPass())
	{
		CDialogEx::OnOK();
	}
	else
	{
		::AfxMessageBox("授权码不正确，请重新输入！");
	}
}


void CCheckKeyDlg::OnBnClickedCancel()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	CDialogEx::OnCancel();
}




BOOL CCheckKeyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯

	char csTempStr[MAX_PATH]={0};
	GetPrivateProfileString("UseKey","KeyValue","",csTempStr,MAX_PATH,m_strIniPath.c_str());

	SetDlgItemText(IDC_EDIT_CheckKey,csTempStr);

	if (strlen(csTempStr))
	{
		PostMessage(WM_KEY_CHECK_ERR,0,0);
	}
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}


void CCheckKeyDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ÔÚ´Ë´¦Ìí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂë
	// ²»Îª»æÍ¼ÏûÏ¢µ÷ÓÃ CDialogEx::OnPaint()
}


HBRUSH CCheckKeyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ÔÚ´Ë¸ü¸Ä DC µÄÈÎºÎÌØÐÔ

	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC_LOGIN_RESULT:
		pDC->SetTextColor(RGB(255,0,0));
		break;
	}

	// TODO:  Èç¹ûÄ¬ÈÏµÄ²»ÊÇËùÐè»­±Ê£¬Ôò·µ»ØÁíÒ»¸ö»­±Ê
	return hbr;
}

#define  CONST_ENCRY_DATA_ELN		(64)

void DecodeData(const char* lpSrcData,char* lpDestData)
{
	char bData[10]={0};
	int bValue;
	int iLen,i,j;
	unsigned short usSum=0;

	iLen = strlen(lpSrcData);
	for (i=4;i<iLen;i+=2)
	{
		strncpy(bData,lpSrcData+i,2);
		sscanf(bData, "%02x",&bValue); 
		usSum += bValue;
	}

	strncpy(bData,lpSrcData,2);
	sscanf(bData, "%02x",&bValue);  
	bValue ^= (usSum>>8)&0xFF;
	iLen = bValue*10;

	strncpy(bData,lpSrcData+2,2);
	sscanf(bData, "%02x",&bValue);  
	bValue ^= (usSum&0xFF);
	iLen += bValue;

	if (iLen != 17)
		return;

	char csTempBufffer[256]={0};
	sprintf(csTempBufffer,"%02x%02x%s",iLen/10,iLen%10,lpSrcData+4);

	int iDiv = (CONST_ENCRY_DATA_ELN-2)/iLen,index;
	for (i=0,j=4;i<iLen;++i,j+=iDiv*2)
	{
		index = i*iDiv;
		strncpy(bData,csTempBufffer+j,2);
		sscanf(bData, "%02x",&bValue);
		bValue ^= csTempBufffer[index];

		lpDestData[i] = bValue;
	}
	//lpDestData[iLen] ='\0'; 
}

bool CCheckKeyDlg::CheckKeyPass()
{
	char csTempStr[MAX_PATH]={0};
	GetPrivateProfileString("UseKey","KeyValue","",csTempStr,MAX_PATH,m_strIniPath.c_str());
	CString strKey = csTempStr;
	strKey.Trim();

	if (strKey.GetLength() != 128)
	{
		return false;
	}

	char csValue[128]={0};
	DecodeData(strKey,csValue);
	if (strlen(csValue) != 17)
	{
		return false;
	}

	for (int i=0;i<m_strMacArray.GetSize();++i)
	{
		if (0 == m_strMacArray[i].CompareNoCase(csValue))
		{
			return true;
		}
	}

	return false;
}

LRESULT CCheckKeyDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà

	if (WM_KEY_CHECK_ERR == message)
	{
		AfxMessageBox("您的授权码不正确！请重新输入！");
		return TRUE;
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}