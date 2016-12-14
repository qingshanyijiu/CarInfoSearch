
// AuthorizationSetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AuthorizationSet.h"
#include "AuthorizationSetDlg.h"
#include "afxdialogex.h"
#include <string>
#include <sstream>
#include <iomanip>
#include "LoginDlg.h"
using namespace  std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAuthorizationSetDlg �Ի���

BOOL GetMacByCmd(CStringArray& strMacArray)
{
	BOOL bret; 

	SECURITY_ATTRIBUTES sa; 
	HANDLE hReadPipe,hWritePipe; 

	sa.nLength = sizeof(SECURITY_ATTRIBUTES); 
	sa.lpSecurityDescriptor = NULL; 
	sa.bInheritHandle = TRUE; 

	//�����ܵ�
	bret = CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);
	if(!bret)
	{
		return FALSE;
	}

	//���������д�����Ϣ
	STARTUPINFO si; 
	//���ؽ�����Ϣ
	PROCESS_INFORMATION pi; 

	si.cb = sizeof(STARTUPINFO); 
	GetStartupInfo(&si); 
	si.hStdError = hWritePipe; 
	si.hStdOutput = hWritePipe; 
	si.wShowWindow = SW_HIDE; //���������д���
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	//��������������С
	const long MAX_COMMAND_SIZE = 10000;

	//��ȡMAC������
	char szFetCmd[] = "ipconfig /all";
	//����MAC��ַ��ǰ����Ϣ
	const string  strSearch[2] = {"�����ַ","Physical Address"};


	//������ȡ�����н���
	bret = CreateProcess (NULL, szFetCmd, NULL, NULL, TRUE, 0, NULL, 
		NULL, &si, &pi ); 

	bool bTerimate = false;

	if (bret) 
	{ 
		bTerimate = WaitForSingleObject (pi.hProcess, 2000)==WAIT_TIMEOUT?true:false; 

		unsigned long count;
		CloseHandle(hWritePipe);

		char szBuffer[MAX_COMMAND_SIZE+1]={0}; //�������������������
		bret  =  ReadFile(hReadPipe,  szBuffer,  MAX_COMMAND_SIZE,  &count,  0);
		if(!bret)
		{
			//�ر����еľ��
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

	//�ر����еľ��
	CloseHandle(pi.hProcess); 
	CloseHandle(pi.hThread); 
	CloseHandle(hReadPipe);
	return TRUE;
}


#define  CONST_ENCRY_DATA_ELN		(64)

void EncryData(const char* lpSrcData,char* lpDestData)
{
	ostringstream ostr;

	int iLen = strlen(lpSrcData),i,j,iDiv,index,ilastindex;
	char chTemp;
	unsigned short usSum=0;

	ostr<<setw(2)<<setfill('0')<<hex<<(iLen/10);
	ostr<<setw(2)<<setfill('0')<<hex<<(iLen%10);

	iDiv = (CONST_ENCRY_DATA_ELN-2)/iLen;

	for(i=0;i<iLen;++i)
	{
		chTemp = ostr.str().at(i*iDiv);
		chTemp ^= lpSrcData[i];
		usSum += chTemp;
		ostr<<setw(2)<<setfill('0')<<hex<<(int)chTemp;
		ilastindex = i*iDiv+4;

		for (j=1;j<iDiv;++j)
		{
			index = i*iDiv+j+3;
			chTemp = ostr.str().at(ilastindex);
			chTemp ^= (CONST_ENCRY_DATA_ELN-index)&0x3C;
			usSum += chTemp;
			ostr<<setw(2)<<setfill('0')<<hex<<(int)chTemp;

			++ilastindex;
		}
	}

	ilastindex = i*iDiv+4;
	for(i=iLen*iDiv+2;i<CONST_ENCRY_DATA_ELN;++i)
	{
		index = i-iDiv;
		chTemp = ostr.str().at(ilastindex);
		chTemp ^= (CONST_ENCRY_DATA_ELN-index)&0x3C;
		usSum += chTemp;
		ostr<<setw(2)<<setfill('0')<<hex<<(int)chTemp;

		++ilastindex;
	}
	strcpy(lpDestData,ostr.str().c_str());

	char csTempBufer[5]={0};
	sprintf(csTempBufer,"%02x%02x",(iLen/10)^((usSum>>8)&0xFF),(iLen%10)^(usSum&0xFF));
	memcpy(lpDestData,csTempBufer,4);
}


CAuthorizationSetDlg::CAuthorizationSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAuthorizationSetDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAuthorizationSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAuthorizationSetDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GETLOCAL, &CAuthorizationSetDlg::OnBnClickedButtonGetLocalMac)
	ON_BN_CLICKED(IDC_BUTTON_CREATE, &CAuthorizationSetDlg::OnBnClickedButtonCreateCode)
END_MESSAGE_MAP()


// CAuthorizationSetDlg ��Ϣ�������

BOOL CAuthorizationSetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������


	OpenDb("CarPartInfoSave.db");

	UserPwdInfo userInfo ;
	CLoginDlg loginDlg(&userInfo,this);
	if (IDOK == loginDlg.DoModal())
	{
		CloseDb();
	}
	else
	{
		//PostMessage(WM_CLOSE,0,0);
		CloseDb();
		exit(0);
		return FALSE;
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAuthorizationSetDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAuthorizationSetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAuthorizationSetDlg::OnBnClickedButtonGetLocalMac()
{
	CStringArray strMacArray;
	GetMacByCmd(strMacArray);

	if (strMacArray.GetSize())
	{
		SetDlgItemText(IDC_EDIT_MAC_ADRESS,strMacArray[0]);
	}

	SetDlgItemText(IDC_EDIT_AuthoCode,"");
}

void CAuthorizationSetDlg::OnBnClickedButtonCreateCode()
{
	CString strMAC;
	GetDlgItemText(IDC_EDIT_MAC_ADRESS,strMAC);
	strMAC.Trim();
	if (strMAC.GetLength()!= 17)
	{
		AfxMessageBox("��д��MAC��ַ����!����������");
	}

	char csTempBuffer[256]={0};
	EncryData(strMAC,csTempBuffer);
	SetDlgItemText(IDC_EDIT_AuthoCode,csTempBuffer);
}

BOOL CAuthorizationSetDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_ESCAPE: //Esc�����¼�
			return true;
		case VK_RETURN: //Enter�����¼�
			return true;
		default:
			;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}