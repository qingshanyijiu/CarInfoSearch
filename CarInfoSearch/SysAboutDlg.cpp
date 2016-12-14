// SysAboutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CarInfoSearch.h"
#include "SysAboutDlg.h"
#include "afxdialogex.h"
#include "CarInfoSearchDlg.h"
#include "FileModifyDlg.h"


// CSysAboutDlg 对话框

IMPLEMENT_DYNAMIC(CSysAboutDlg, CDialogEx)

CSysAboutDlg::CSysAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSysAboutDlg::IDD, pParent)
{

}

CSysAboutDlg::~CSysAboutDlg()
{
}

void CSysAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSysAboutDlg, CDialogEx)
	//ON_COMMAND(IDC_SYSLINK_OPERATE, &CSysAboutDlg::OnSyslinkOperate)
	ON_BN_CLICKED(IDC_MFCLINK_OPERATE_LOOK, &CSysAboutDlg::OnClickedMfclinkOperateLook)
	ON_COMMAND(IDC_MFCLINK_OPERATE_LOOK, &CSysAboutDlg::OnClickedMfclinkOperateLook)
	ON_BN_DOUBLECLICKED(IDC_MFCLINK_OPERATE_LOOK, &CSysAboutDlg::OnDoubleclickedMfclinkOperateLook)
	ON_BN_DOUBLECLICKED(IDC_MFCLINK_AUTHOR, &CSysAboutDlg::OnDoubleclickedMfclinkAuthor)
END_MESSAGE_MAP()


// CSysAboutDlg 消息处理程序


void CSysAboutDlg::OnSyslinkOperate()
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌÐò´úÂë
	//AfxMessageBox("HHA");
}


BOOL CSysAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	const char* pInfo = "\t\t\t\t\t\t\t\t广州利迅动力概况\n\
    广州市利迅汽车配件有限公司成立于2000年。是一家致力于打造成为以速度、质量、服务为重点的新概念汽车配件连锁企业\
广州利迅动力始于2003年开始代理经营东风EQ491发动机，这是打造专业三菱发动机服务团队的开始，2006年代理经营航天三菱发\
动机以及东安三菱发动机系列，2016年广州利迅拿下东安三菱华南大区总代理，广州利迅动力服务团队对汽配事业充满热忱和执着\
对汽配工作一丝不苟，逐渐形成懂经营、善管理、会营销、精服务的团队。广州利迅动力以较强的经济实力、一流的售后服务，为客户\
提供出色全方位的服务。\n\
    我们承诺：\n\
	A、所有的产品在东安系统内对外供应\n\
	B、全国统一售价\n\
	C、区域统一物流发货\n\
	D、有符合行业或国家相关政策的质保期限\n\
	\n\n\
    Guangzhou lixun auto parts Co., Ltd. was founded in 2000. Is Guangzhou lixun a commitment to build into a speed,\
quality, service as the focus of the new concept of auto parts chain enterprises began in 2003 began operating agent of \
Dongfeng EQ491 engine, this is the beginning of the MITSUBISHI engine to create a professional service team, in 2006 the \
agency and the Dongan aerospace MITSUBISHI engine MITSUBISHI engine series, 2016 Guangzhou lixun take the general agent \
of Dongan MITSUBISHI Southern China District, Guangzhou lixun power service team full of enthusiasm and dedication to \
the cause of auto parts to work gradually formed strict in demands, understand business, good management and marketing, \
fine service team. Guangzhou lixun power with a strong economic strength, first-class after-sales service, to provide \
customers with a full range of excellent services.\n\
    Our commitment: \n\
    A, all the products in the Dongan system external supply \n\
    B, the national unified price \n\
    C, regional unified logistics delivery \n\
    D, in line with the industry or national policy related to the quality of the period \n\
\n\n\n\n\n\n\n\
哈尔滨东安三菱汽车发动机制造有限公司\t\t\t\t\t沈阳航天三菱汽车发动机制造有限公司\n\
HARBIN DONGAN AUTOMOTIVE ENGINGE MANUFACTURING CO.,LTD\t\t SHENYANG AEROSPACE MITSUBISHI AUTOMOTIVE ENGINGE MANUFACTURING CO.,LTD";


	SetDlgItemText(IDC_STATIC_SYS_ABOUT,pInfo);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}


BOOL CSysAboutDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà

	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_ESCAPE: //Esc按键事件
			return true;
		case VK_RETURN: //Enter按键事件
			return true;
		default:
			;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CSysAboutDlg::OnClickedMfclinkOperateLook()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

}


void CSysAboutDlg::OnDoubleclickedMfclinkOperateLook()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	CString strOperateFilePath = CFileModifyDlg::s_fileSavePath;

	strOperateFilePath += "操作文档外部版.doc";

	ShellExecute(NULL,"open",strOperateFilePath,NULL,NULL,SW_NORMAL );
}


void CSysAboutDlg::OnDoubleclickedMfclinkAuthor()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	AfxMessageBox("Design by ZG！\n\n勿在浮沙筑高台!\n\n542187663@qq.com\n");
}
