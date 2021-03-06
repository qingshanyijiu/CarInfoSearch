﻿// LoadDataDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CarInfoSearch.h"
#include "LoadDataDlg.h"
#include "afxdialogex.h"
#include "CarInfoSearchDlg.h"


// CLoadDataDlg 对话框

IMPLEMENT_DYNAMIC(CLoadDataDlg, CDialogEx)

CLoadDataDlg::CLoadDataDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoadDataDlg::IDD, pParent)
{

}

CLoadDataDlg::~CLoadDataDlg()
{
}

void CLoadDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_File_Type, m_loadSelectCombo);
	DDX_Control(pDX, IDC_CHECK_TEST, m_testCheck);
}


BEGIN_MESSAGE_MAP(CLoadDataDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Load_Select, &CLoadDataDlg::OnBnClickedButtonLoadSelect)
	ON_BN_CLICKED(IDC_BUTTON_Load_Begin, &CLoadDataDlg::OnBnClickedButtonLoadBegin)
END_MESSAGE_MAP()


// CLoadDataDlg 消息处理程序


BOOL CLoadDataDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯

	m_loadSelectCombo.InsertString(0,"机型数据");
	m_loadSelectCombo.InsertString(1,"零件数据");
	m_loadSelectCombo.InsertString(2,"机型零件数据");
	m_loadSelectCombo.InsertString(3,"机型/零件数据");
	m_loadSelectCombo.InsertString(4,"机型/零件数据扩展");

	m_loadSelectCombo.SetCurSel(3);
	m_testCheck.SetCheck(TRUE);
	//SetDlgItemText(IDC_EDIT_LoadFileName,"C:\\Users\\Administrator\\Desktop\\CarInfoManager\\bin\\4A9.txt");

	CString strTemp = CCarInfoSearchDlg::s_curPath.c_str();
	strTemp += "北汽动力B20.txt";
	SetDlgItemText(IDC_EDIT_LoadFileName,strTemp);

	SetDlgItemText(IDC_EDIT_LOAD_TYPE,"4A9");


	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}


BOOL CLoadDataDlg::PreTranslateMessage(MSG* pMsg)
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


void CLoadDataDlg::OnBnClickedButtonLoadBegin()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	if (m_loadSelectCombo.GetCurSel()<0)
	{
		CCarInfoSearchDlg::ShowOperateInfo("请选择导入数据的类型");
		return;
	}

	CString strFileName;
	GetDlgItemText(IDC_EDIT_LoadFileName,strFileName);
	if (strFileName.IsEmpty())
	{
		CCarInfoSearchDlg::ShowOperateInfo("请选择要导入的文件！");
		return;
	}

	m_bLog = m_testCheck.GetCheck()?true:false;

	ifstream iFile;
	iFile.open(strFileName.operator LPCSTR());
	if (!iFile.is_open())
	{
		CCarInfoSearchDlg::ShowOperateInfo("请文件打开失败！");
		return;
	}

	string strTemp = strFileName;
	strFileName +="error.txt";
	m_oFile.open(strFileName.operator LPCSTR(),ios::out|ios::app);

	if (m_bLog)
	{
		strTemp += "out.txt";
		m_oFormatFile.open(strTemp.c_str(),ios::out|ios::app);
	}


	string strTypeName = CCarInfoSearchDlg::s_curPath;
	strTypeName += "type.txt";

	vector<string> typeVect;
	TypeMap typeMap;
	char csTempTypeBuffer[100];
	ifstream iTypeFile;
	CString strTypeTemp,strKey;
	int iPos = -1;

	iTypeFile.open(strTypeName.c_str());
	if (!iTypeFile.is_open())
	{
		return;
	}

	do 
	{
		memset(csTempTypeBuffer,0,100);
		iTypeFile.getline(csTempTypeBuffer,100);
		strTypeTemp = csTempTypeBuffer;
		if (!strTypeTemp.IsEmpty())
		{
			if (-1 != (iPos = strTypeTemp.Find(',')))
			{
				strKey = strTypeTemp.Left(iPos);
				typeVect.push_back(strTypeTemp.Right(strTypeTemp.GetLength()-iPos-1).operator LPCSTR());
				TypeMap::iterator it = typeMap.find(strKey.operator LPCSTR());
				if (it == typeMap.end())
				{
					TypeVect tempVect;
					tempVect.push_back(strTypeTemp.Right(strTypeTemp.GetLength()-iPos-1).operator LPCSTR());
					typeMap.insert(pair<string,TypeVect>(strKey,tempVect));
				}
				else
				{
					it->second.push_back(strTypeTemp.Right(strTypeTemp.GetLength()-iPos-1).operator LPCSTR());
				}
			}
			else
			{
				typeVect.push_back(strTypeTemp.operator LPCSTR());
			}
		}
	} while (!iTypeFile.eof());
	iTypeFile.close();

	strTypeName = CCarInfoSearchDlg::s_curPath;
	strTypeName += "typeother.txt";

	vector<string> typeOtherVect;
	ifstream iTypeOtherFile;

	iTypeOtherFile.open(strTypeName.c_str());
	if (iTypeOtherFile.is_open())
	{
		do 
		{
			memset(csTempTypeBuffer,0,100);
			iTypeOtherFile.getline(csTempTypeBuffer,100);

			typeOtherVect.push_back(csTempTypeBuffer);
		} while (!iTypeOtherFile.eof());
		iTypeOtherFile.close();
	}

	char csTempBuffer[4096];
	do 
	{
		memset(csTempBuffer,0,4096);
		iFile.getline(csTempBuffer,4096);

		if (strlen(csTempBuffer)<5)
		{
			continue;
		}
		strTemp = csTempBuffer;
		if (-1 != strTemp.find("适用型号") || -1 != strTemp.find("说明")
			||-1 != strTemp.find("零件名称") || -1 != strTemp.find("PART NAME"))
		{
			continue;
		}
		switch(m_loadSelectCombo.GetCurSel())
		{
		case 0:
			InsertCarTypeData(csTempBuffer);
			break;
		case 1:
			InsertCarPartsData(csTempBuffer);
			break;
		case 2:
			InsertCarTypePartsData(csTempBuffer);
			break;
		case 3:
			InsertCarTypePartsDataEx(csTempBuffer,typeVect,typeOtherVect,typeMap);
			break;
		case 4:
			InsertCarTypePartsDataEx2(csTempBuffer,typeVect,typeOtherVect,typeMap);
			break;
		}
	
	} while (!iFile.eof());

	if (iFile.eof())
	{
		CCarInfoSearchDlg::ShowOperateInfo("导入数据成功！！");
	}
	else
	{
		CCarInfoSearchDlg::ShowOperateInfo("导入数据失败！！");
	}

	iFile.close();
	m_oFile.close();

	if (m_bLog)
		m_oFormatFile.close();
}


void CLoadDataDlg::OnBnClickedButtonLoadSelect()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	CFileDialog aDlg(TRUE,NULL,"*.txt");
	if(aDlg.DoModal()==IDCANCEL )
		return;
	CString strFilePath = aDlg.GetPathName();
	if (strFilePath.IsEmpty())
		return;

	SetDlgItemText(IDC_EDIT_LoadFileName,strFilePath);
}



UINT DivStr(CString& str,CStringArray& Arr,char ch)
{
	int nFindposi  = str.Find(ch);
	if( nFindposi <0 )
		return 0;

	while( nFindposi > -1)
	{
		Arr.Add(str.Left(nFindposi));
		str = str.Right( str.GetLength() - nFindposi -1);
		//str.TrimLeft(ch);    //warning

		nFindposi  = str.Find(ch);
	}

	//if( !str.IsEmpty() )
		Arr.Add(str.Trim());

	return Arr.GetSize();
}


UINT CLoadDataDlg::DivStrEx(CString& str,CStringArray& Arr,char ch,int iCount)
{
	int nFindposi  = str.Find(ch);
	if( nFindposi <0 )
		return 0;

	while( nFindposi > -1)
	{
		Arr.Add(str.Left(nFindposi));
		str = str.Right( str.GetLength() - nFindposi -1);

		if (Arr.GetSize() == iCount-1)
		{
			break;
		}

		//str.TrimLeft(ch);    //warning

		nFindposi  = str.Find(ch);
	}

	if( !str.IsEmpty() )
		Arr.Add(str.Trim());
	 if (Arr.GetSize() < iCount)
	{
		Arr.Add("");
	}

	 if (Arr.GetSize() < iCount)
	 {
		 Arr.Add("");
	 }

	return Arr.GetSize();
}

/*
bool CLoadDataDlg::InsertCarTypeData(const char* lpStr)
{
	CString strData = lpStr;
	CStringArray strArray;
	char ch = 9;

	if (DivStrEx(strData,strArray,ch,6))
	{
		CarTypeTableInfo tempInfo;
		if (strArray[0].Compare("!empty!"))
			strncpy(tempInfo.csCarTypeNum,strArray[0].operator LPCSTR(),16);
		if (strArray[1].Compare("!empty!"))
			strncpy(tempInfo.csCarDetailTypeNum,strArray[1].operator LPCSTR(),32);
		if (strArray[2].Compare("!empty!"))
			strncpy(tempInfo.csCarFactory,strArray[2].operator LPCSTR(),32);
		if (strArray[3].Compare("!empty!"))
			strncpy(tempInfo.csCarStatus,strArray[3].operator LPCSTR(),32);
		if (strArray[4].Compare("!empty!"))
			strncpy(tempInfo.csCarDetailName,strArray[4].operator LPCSTR(),32);
		if (strArray[5].Compare("!empty!"))
			tempInfo.strCarNotes = strArray[5].operator LPCSTR();

		InsertCarTypeInfo(&tempInfo);
		return true;
	}
	else
	{
		return false;
	}
}*/
/*
bool CLoadDataDlg::InsertCarTypeData(const char* lpStr)
{
	CString strData = lpStr;
	CStringArray strArray;
	char ch = 9;
	
	ASCarTypeTableInfo tempInfo;
	strcpy(tempInfo.csCarTypeNum,"4A9");

	if (DivStrEx(strData,strArray,ch,14))
	{
		if (!strArray[0].IsEmpty())
			strncpy(tempInfo.csCarFactory,strArray[0].operator LPCSTR(),32);
		if (!strArray[1].IsEmpty())
			strncpy(tempInfo.csCustomerCode,strArray[1].operator LPCSTR(),16);
		if (!strArray[2].IsEmpty())
			strncpy(tempInfo.csCarDetailTypeNum,strArray[2].operator LPCSTR(),32);
		if (!strArray[3].IsEmpty())
			strncpy(tempInfo.csCarType,strArray[3].operator LPCSTR(),32);
		if (!strArray[4].IsEmpty())
			strncpy(tempInfo.csCarName,strArray[4].operator LPCSTR(),32);
		if (!strArray[5].IsEmpty())
			strncpy(tempInfo.csCarPattern,strArray[5].operator LPCSTR(),32);
		if (!strArray[6].IsEmpty())
			strncpy(tempInfo.csEnginePattern,strArray[6].operator LPCSTR(),32);
		if (!strArray[7].IsEmpty())
			strncpy(tempInfo.csMarkModel,strArray[7].operator LPCSTR(),16);

		CString strNote,strTemp;
		int i=1;
		//排放法规		生产状态	EMS系统	备注	CL
		if (!strArray[8].IsEmpty())
		{
			strTemp.Format("%d、排放法规为%s；",i++,strArray[8]);
			strNote += strTemp;
		}

		if (!strArray[9].IsEmpty())
		{
			strTemp.Format("%d、变速箱%s；",i++,strArray[9]);
			strNote += strTemp;
		}

		if (!strArray[11].IsEmpty())
		{
			strTemp.Format("%d、EMS系统为%s；",i++,strArray[11]);
			strNote += strTemp;
		}

		if (!strArray[12].IsEmpty())
		{
			strTemp.Format("%d、备注为%s；",i++,strArray[12]);
			strNote += strTemp;
		}

		if (!strArray[13].IsEmpty())
		{
			strTemp.Format("%d、CL为%s；",i++,strArray[13]);
			strNote += strTemp;
		}

		tempInfo.strCarNotes = strNote.operator LPCSTR();

		ASInsertCarTypeInfo(&tempInfo);
		return true;
	}
	else
	{
		m_oFile<<lpStr<<endl;
		return false;
	}
}*/

bool CLoadDataDlg::InsertCarTypeData(const char* lpStr)
{
	CString strData = lpStr;
	CStringArray strArray;
	char ch = 9;

	static ASCarTypeTableInfo tempInfo;
	strcpy(tempInfo.csCarTypeNum,"4G6");
	memset(tempInfo.csCarDetailTypeNum,0,sizeof(tempInfo.csCarDetailTypeNum));
	memset(tempInfo.csCarType,0,sizeof(tempInfo.csCarType));
	memset(tempInfo.csCarName,0,sizeof(tempInfo.csCarName));
	memset(tempInfo.csCarPattern,0,sizeof(tempInfo.csCarPattern));
	memset(tempInfo.csEnginePattern,0,sizeof(tempInfo.csEnginePattern));
	memset(tempInfo.csMarkModel,0,sizeof(tempInfo.csMarkModel));
	tempInfo.strCarNotes.clear();

	if (DivStrEx(strData,strArray,ch,15) == 15)
	{
		if (!strArray[0].IsEmpty())
			strncpy(tempInfo.csCarFactory,strArray[0].operator LPCSTR(),32);
		if (!strArray[1].IsEmpty())
			strncpy(tempInfo.csCustomerCode,strArray[1].operator LPCSTR(),16);
		if (!strArray[3].IsEmpty())
			strncpy(tempInfo.csCarDetailTypeNum,strArray[3].operator LPCSTR(),32);
		if (!strArray[4].IsEmpty())
			strncpy(tempInfo.csCarType,strArray[4].operator LPCSTR(),32);
		if (!strArray[5].IsEmpty())
			strncpy(tempInfo.csCarName,strArray[5].operator LPCSTR(),32);
		if (!strArray[6].IsEmpty())
			strncpy(tempInfo.csCarPattern,strArray[6].operator LPCSTR(),32);
		if (!strArray[7].IsEmpty())
			strncpy(tempInfo.csEnginePattern,strArray[7].operator LPCSTR(),32);
		if (!strArray[8].IsEmpty())
			strncpy(tempInfo.csMarkModel,strArray[8].operator LPCSTR(),16);

		CString strNote,strTemp;
		int i=1;
		//排放法规		生产状态	EMS系统	备注	CL
		if (!strArray[9].IsEmpty())
		{
			strTemp.Format("%d、排放法规为%s；",i++,strArray[9]);
			strNote += strTemp;
		}

		if (!strArray[10].IsEmpty())
		{
			strTemp.Format("%d、变速箱%s；",i++,strArray[10]);
			strNote += strTemp;
		}

		if (!strArray[12].IsEmpty())
		{
			strTemp.Format("%d、EMS系统为%s；",i++,strArray[12]);
			strNote += strTemp;
		}

		if (!strArray[13].IsEmpty())
		{
			strTemp.Format("%d、备注为%s；",i++,strArray[13]);
			strNote += strTemp;
		}

		if (!strArray[14].IsEmpty())
		{
			strTemp.Format("%d、CL为%s；",i++,strArray[14]);
			strNote += strTemp;
		}

		tempInfo.strCarNotes = strNote.operator LPCSTR();

		ASInsertCarTypeInfo(&tempInfo);
		return true;
	}
	else
	{
		m_oFile<<lpStr<<endl;
		return false;
	}
}


bool CLoadDataDlg::InsertCarPartsData(const char* lpStr)
{
	CString strData = lpStr;
	CStringArray strArray;
	char ch = 9;

	if (DivStrEx(strData,strArray,ch,7)==7)
	{
		CarPartTableInfo tempInfo;
		strncpy(tempInfo.csCarTypeNum,"4G15V",16);
		if (!strArray[0].IsEmpty())
			tempInfo.iLevel = atoi(strArray[0].operator LPCSTR());
		if (!strArray[1].IsEmpty())
			strncpy(tempInfo.csDAENum,strArray[1].operator LPCSTR(),32);
		if (!strArray[2].IsEmpty())
			strncpy(tempInfo.csChineseName,strArray[2].operator LPCSTR(),64);
		if (!strArray[4].IsEmpty())
			strncpy(tempInfo.csPicNum,strArray[4].operator LPCSTR(),32);
		if (!strArray[5].IsEmpty())
			strncpy(tempInfo.csInstallNum,strArray[5].operator LPCSTR(),32);
		if (!strArray[6].IsEmpty())
			tempInfo.iInstallMark = atoi(strArray[6].operator LPCSTR());

		InsertCarPartInfo(&tempInfo);
		return true;
	}
	else
	{
		m_oFile<<lpStr<<endl;
		return true;
	}
}

bool CLoadDataDlg::InsertCarTypePartsData(const char* lpStr)
{
	CString strData = lpStr;
	CStringArray strArray,strTypeArray;
	char ch = 9;
	vector<string> typeVect;
	int index;
	typeVect.reserve(5);

	strTypeArray.Add("4G93-D4");strTypeArray.Add("4G93-D1D");strTypeArray.Add("4G93-D11");strTypeArray.Add("4G93-D13");
	strTypeArray.Add("4G93-D14");

	if (DivStrEx(strData,strArray,ch,7) ==7)
	{
		CarTypePartsTableInfo tempInfo;
		strcpy(tempInfo.csCarTypeNum,"5G");

		typeVect.clear();

		for (int i=0;i<5;++i)
		{
			if (!strArray[i].IsEmpty())
			{
				typeVect.push_back(strTypeArray[i].operator LPCSTR());

			}
		}

		//int iCount = typeVect.size();
		if (typeVect.size())
		{
			//UpdateCarTypePartsInfo(&tempInfo,typeVect);
		}

		return true;
	}
	else
	{
		m_oFile<<lpStr<<endl;
		return true;
	}
}

#define DIV_ROW_COUNT		(8)
#define DIV_ROW_INDEX		(3)

/*
bool CLoadDataDlg::InsertCarTypePartsDataEx(const char* lpStr)
{
//38-49
	CString strData = lpStr;
	CStringArray strArray,strTypeArray;
	char ch = 9;
	vector<string> typeVect;
	int index;
	typeVect.reserve(DIV_ROW_INDEX);

	strTypeArray.Add("4G93-D4");strTypeArray.Add("4G93-D1D");strTypeArray.Add("4G93-D11");strTypeArray.Add("4G93-D13");
	strTypeArray.Add("4G93-D14");strTypeArray.Add("4G93-DCD");strTypeArray.Add("4G93-DC1");strTypeArray.Add("4G93-DC2");
	strTypeArray.Add("4G93-DC3");strTypeArray.Add("4G93-DCL");strTypeArray.Add("4G93D-8L");strTypeArray.Add("4G93D-8A");
	strTypeArray.Add("4G93-D9L");strTypeArray.Add("4G93-D91");strTypeArray.Add("4G93D-JA");strTypeArray.Add("4G93D-DL");
	strTypeArray.Add("4G93D-DA");strTypeArray.Add("4G93D-HL");strTypeArray.Add("4G93D-H1");strTypeArray.Add("4G93M-9L");
	strTypeArray.Add("4G93M-ML");strTypeArray.Add("4G93M-MA");strTypeArray.Add("4G94-S81");strTypeArray.Add("4G94-S8L");
	strTypeArray.Add("4G94-S84");strTypeArray.Add("4G94-SGL");strTypeArray.Add("4G94-S9L");strTypeArray.Add("DAE481Q-E2");
	strTypeArray.Add("4G94S-TD2");strTypeArray.Add("4G94-S2L");strTypeArray.Add("4G94S-21");strTypeArray.Add("4G94-S82");
	strTypeArray.Add("4G94D-NL");strTypeArray.Add("4G94D-NA");strTypeArray.Add("4G94D-F1");strTypeArray.Add("4G94D-F2");
	strTypeArray.Add("4G94D-F3");strTypeArray.Add("4G94D-6A");

	if (DivStrEx(strData,strArray,ch,DIV_ROW_COUNT)==DIV_ROW_COUNT)
	{
		CarPartTableInfo tempPartInfo;
		strncpy(tempPartInfo.csCarTypeNum,"4G9",16);
		index = DIV_ROW_INDEX;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csEPLNum,strArray[index].operator LPCSTR(),32);

		++index;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csVCNum,strArray[index].operator LPCSTR(),16);

		++index;
		if (!strArray[index].IsEmpty())
			tempPartInfo.iLevel = atoi(strArray[index].operator LPCSTR());

		++index;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csMMCNum,strArray[index].operator LPCSTR(),32);

		++index;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csDAENum,strArray[index].operator LPCSTR(),32);

		++index;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csChineseName,strArray[index].operator LPCSTR(),64);

		++index;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csPicNum,strArray[index].operator LPCSTR(),32);

		index += 3;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csInstallNum,strArray[index].operator LPCSTR(),32);

		++index;
		if (!strArray[index].IsEmpty())
			tempPartInfo.iInstallMark = atoi(strArray[index].operator LPCSTR());

		InsertCarPartInfo(&tempPartInfo);

		CarTypePartsTableInfo tempInfo;
		strcpy(tempInfo.csCarTypeNum,tempPartInfo.csCarTypeNum);
		strcpy(tempInfo.csDAENum,tempPartInfo.csDAENum);
		strcpy(tempInfo.csMMCNum,tempPartInfo.csMMCNum);

		typeVect.clear();

		for (int i=0;i<DIV_ROW_INDEX;++i)
		{
			if (!strArray[i].IsEmpty())
			{
				typeVect.push_back(strTypeArray[i].operator LPCSTR());

			}
		}

		//int iCount = typeVect.size();
		if (typeVect.size())
		{
			UpdateCarTypePartsInfo(&tempInfo,typeVect);
		}

		return true;
	}
	else
	{
		m_oFile<<lpStr;
		return true;
	}
}*/

/*
bool CLoadDataDlg::InsertCarTypePartsDataEx(const char* lpStr)
{
	//9-20
	CString strData = lpStr;
	CStringArray strArray,strTypeArray;
	char ch = 9;
	vector<string> typeVect;
	int index;
	typeVect.reserve(DIV_ROW_INDEX);

	strTypeArray.Add("4G15-Z-32");strTypeArray.Add("4G15-Z-F3");strTypeArray.Add("4G15T-TA2");strTypeArray.Add("4G15M-2L");
	strTypeArray.Add("4G15M-2J");strTypeArray.Add("4G15M-M3");strTypeArray.Add("4G15M-M4");strTypeArray.Add("4G15M-TC1");
	strTypeArray.Add("4G15M-TC2");

	if (DivStrEx(strData,strArray,ch,DIV_ROW_COUNT)==DIV_ROW_COUNT)
	{
		CarPartTableInfo tempPartInfo;
		strncpy(tempPartInfo.csCarTypeNum,"4G15M",16);
		index = DIV_ROW_INDEX;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csEPLNum,strArray[index].operator LPCSTR(),32);

		++index;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csVCNum,strArray[index].operator LPCSTR(),16);

		++index;
		if (!strArray[index].IsEmpty())
			tempPartInfo.iLevel = atoi(strArray[index].operator LPCSTR());

		++index;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csDAENum,strArray[index].operator LPCSTR(),32);

		++index;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csMMCNum,strArray[index].operator LPCSTR(),32);

		++index;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csEnglishName,strArray[index].operator LPCSTR(),64);

		++index;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csChineseName,strArray[index].operator LPCSTR(),64);

		++index;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csPicNum,strArray[index].operator LPCSTR(),32);

		index += 2;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csInstallNum,strArray[index].operator LPCSTR(),32);

		++index;
		if (!strArray[index].IsEmpty())
			tempPartInfo.iInstallMark = atoi(strArray[index].operator LPCSTR());

		InsertCarPartInfo(&tempPartInfo);

		CarTypePartsTableInfo tempInfo;
		strcpy(tempInfo.csCarTypeNum,tempPartInfo.csCarTypeNum);
		strcpy(tempInfo.csDAENum,tempPartInfo.csDAENum);
		strcpy(tempInfo.csMMCNum,tempPartInfo.csMMCNum);

		typeVect.clear();

		for (int i=0;i<DIV_ROW_INDEX;++i)
		{
			if (!strArray[i].IsEmpty())
			{
				typeVect.push_back(strTypeArray[i].operator LPCSTR());

			}
		}

		//int iCount = typeVect.size();
		if (typeVect.size())
		{
			UpdateCarTypePartsInfo(&tempInfo,typeVect);
		}

		return true;
	}
	else
	{
		m_oFile<<lpStr<<endl;
		return true;
	}
}*/
/*
bool CLoadDataDlg::InsertCarTypePartsDataEx(const char* lpStr)
{
	//83-91
	CString strData = lpStr;
	CStringArray strArray,strTypeArray;
	char ch = 9;
	vector<string> typeVect;
	int index;
	typeVect.reserve(DIV_ROW_INDEX);

	strTypeArray.Add("DA47Q-1");strTypeArray.Add("DA47Q-1L");strTypeArray.Add("DA47Q-12");strTypeArray.Add("4G13-1L");strTypeArray.Add("4G13-25");
	strTypeArray.Add("4G13-26");strTypeArray.Add("4G13-29");strTypeArray.Add("4G13-2C");strTypeArray.Add("4G13S1-2H");strTypeArray.Add("4G13S1-2J");
	strTypeArray.Add("4G13S1-2K");strTypeArray.Add("4G13S1-THA");strTypeArray.Add("4G13-6L");strTypeArray.Add("4G13S1-61");strTypeArray.Add("4G13-62");
	strTypeArray.Add("4G13S-7L");strTypeArray.Add("4G13S-71");strTypeArray.Add("4G13S-PY1");strTypeArray.Add("4G13S-PY2");strTypeArray.Add("4G13S-PY3");
	strTypeArray.Add("4G13S1-PB");strTypeArray.Add("4G13S1-PC");strTypeArray.Add("4G13S1-D2");strTypeArray.Add("4G13S1-DL");strTypeArray.Add("4G13S1-D1");
	strTypeArray.Add("4G13S-C1");strTypeArray.Add("DA476Q-1");strTypeArray.Add("DA476Q-1L");strTypeArray.Add("DA4G18-A2");strTypeArray.Add("DA4G18-A3");
	strTypeArray.Add("DA4G18-A4");strTypeArray.Add("DA4G18-A6");strTypeArray.Add("DA4G18-A7");strTypeArray.Add("DA4G18-A8");strTypeArray.Add("DA4G18-A9");
	strTypeArray.Add("DA476Q-2L");strTypeArray.Add("DA476Q-2G");strTypeArray.Add("DA476Q-22");strTypeArray.Add("DA476Q-23");strTypeArray.Add("DA476Q-24");
	strTypeArray.Add("4G18-25");strTypeArray.Add("4G18-29");strTypeArray.Add("DA4G18-2A");strTypeArray.Add("DA4G18-2E");strTypeArray.Add("DA4G18-2D");
	strTypeArray.Add("4G18-3L");strTypeArray.Add("DA4G18-4D");strTypeArray.Add("DA4G18-4L");strTypeArray.Add("DA4G18-4C");strTypeArray.Add("DA4G18-41");
	strTypeArray.Add("DA4G18-43");strTypeArray.Add("4G18-CD");strTypeArray.Add("4G18S-C1");strTypeArray.Add("4G18S-C2");strTypeArray.Add("DA4G18-6L");
	strTypeArray.Add("DA4G18-62");strTypeArray.Add("4G18S-7L");strTypeArray.Add("4G18S-72");strTypeArray.Add("4G18S-J1");strTypeArray.Add("4G18S-JL");
	strTypeArray.Add("4G18S-5L");strTypeArray.Add("4G18S1-93");	strTypeArray.Add("4G15S-16");strTypeArray.Add("4G15S-1L");strTypeArray.Add("4G15S-11");
	strTypeArray.Add("4G15S-TD1");strTypeArray.Add("4G15S-TD8");strTypeArray.Add("4G15S-TA5");strTypeArray.Add("4G15S-TA6");strTypeArray.Add("4G15S-TA9");
	strTypeArray.Add("4G15S-4D");strTypeArray.Add("4G15S-4C");strTypeArray.Add("DA4G15S-4D");strTypeArray.Add("4G15S-4L");strTypeArray.Add("4G15S-4A");
	strTypeArray.Add("4G15S-D1");strTypeArray.Add("4G15S-DL");strTypeArray.Add("4G15S-6L");strTypeArray.Add("4G15S-72");strTypeArray.Add("4G15S-73");
	strTypeArray.Add("4G15S-7A");strTypeArray.Add("4G15S-8D");strTypeArray.Add("4G15S-92");

	if (DivStrEx(strData,strArray,ch,DIV_ROW_COUNT)==DIV_ROW_COUNT)
	{
		CarPartTableInfo tempPartInfo;
		strncpy(tempPartInfo.csCarTypeNum,"4G1",16);
		index = DIV_ROW_INDEX;
		if (!strArray[index].IsEmpty())
			tempPartInfo.iLevel = atoi(strArray[index].operator LPCSTR());

		++index;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csDAENum,strArray[index].operator LPCSTR(),32);

		++index;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csMMCNum,strArray[index].operator LPCSTR(),32);

		++index;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csEnglishName,strArray[index].operator LPCSTR(),64);

		++index;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csChineseName,strArray[index].operator LPCSTR(),64);

		++index;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csPicNum,strArray[index].operator LPCSTR(),32);

		++index;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csInstallNum,strArray[index].operator LPCSTR(),32);

		++index;
		if (!strArray[index].IsEmpty())
			tempPartInfo.iInstallMark = atoi(strArray[index].operator LPCSTR());

		InsertCarPartInfo(&tempPartInfo);

		CarTypePartsTableInfo tempInfo;
		strcpy(tempInfo.csCarTypeNum,tempPartInfo.csCarTypeNum);
		strcpy(tempInfo.csDAENum,tempPartInfo.csDAENum);
		strcpy(tempInfo.csMMCNum,tempPartInfo.csMMCNum);

		typeVect.clear();

		for (int i=0;i<DIV_ROW_INDEX;++i)
		{
			if (!strArray[i].IsEmpty())
			{
				typeVect.push_back(strTypeArray[i].operator LPCSTR());

			}
		}

		//int iCount = typeVect.size();
		if (typeVect.size())
		{
			UpdateCarTypePartsInfo(&tempInfo,typeVect);
		}

		return true;
	}
	else
	{
		m_oFile<<lpStr<<endl;
		return true;
	}
}*/

/*
bool CLoadDataDlg::InsertCarTypePartsDataEx(const char* lpStr)
{
	//3-8
	CString strData = lpStr;
	CStringArray strArray,strTypeArray;
	char ch = 9;
	vector<string> typeVect;
	int index;
	typeVect.reserve(DIV_ROW_INDEX);

	strTypeArray.Add("D20VVT-B");strTypeArray.Add("D20VVT-C");strTypeArray.Add("D20VVT-F");

	if (DivStrEx(strData,strArray,ch,DIV_ROW_COUNT)==DIV_ROW_COUNT)
	{
		CarPartTableInfo tempPartInfo;
		strncpy(tempPartInfo.csCarTypeNum,"D系列",16);
		index = DIV_ROW_INDEX;
		if (!strArray[index].IsEmpty())
			tempPartInfo.iLevel = atoi(strArray[index].operator LPCSTR());

		++index;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csDAENum,strArray[index].operator LPCSTR(),32);

		++index;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csChineseName,strArray[index].operator LPCSTR(),64);

		index += 2;
		if (!strArray[index].IsEmpty())
			strncpy(tempPartInfo.csPicNum,strArray[index].operator LPCSTR(),32);

		InsertCarPartInfo(&tempPartInfo);

		CarTypePartsTableInfo tempInfo;
		strcpy(tempInfo.csCarTypeNum,tempPartInfo.csCarTypeNum);
		strcpy(tempInfo.csDAENum,tempPartInfo.csDAENum);
		//strcpy(tempInfo.csMMCNum,tempPartInfo.csMMCNum);

		typeVect.clear();

		for (int i=0;i<DIV_ROW_INDEX;++i)
		{
			if (!strArray[i].IsEmpty())
			{
				typeVect.push_back(strTypeArray[i].operator LPCSTR());

			}
		}

		//int iCount = typeVect.size();
		if (typeVect.size())
		{
			UpdateCarTypePartsInfo(&tempInfo,typeVect);
		}

		return true;
	}
	else
	{
		m_oFile<<lpStr<<endl;
		return true;
	}

}*/

#define  DATA_TYPE_HEAD_E		(0)
#define  DATA_TYPE_HEAD_C		(1)
#define  DATA_TYPE_DATA			(2)
#define  DATA_TYPE_DATA_NAME	(3)
#define  DATA_TYPE_DATA_SUPP	(4)

bool IsHaveItem(vector<string>& typeVect,const char* lpType)
{
	for (int i=0;i<typeVect.size();++i)
	{
		if (0 == typeVect[i].compare(lpType))
		{
			return true;
		}
	}

	return false;
}

bool JudgeDataType(CStringArray& strArray)
{
	for (int i=1;i<strArray.GetSize();++i)
	{
		if (!strArray[i].IsEmpty())
		{
			return false;
		}
	}

	return true;
}

bool JudgeDataHead(CStringArray& strArray)
{
	int iCount=0;
	for (int i=0;i<strArray.GetSize();++i)
	{
		if (!strArray[i].IsEmpty())
		{
			++iCount;
		}
	}

	return iCount==1?true:false;
}

bool JudgeDataTypeEx(CStringArray& strArray)
{
	for (int i=0;i<strArray.GetSize();++i)
	{
		if (!strArray[i].IsEmpty())
		{
			return false;
		}
	}

	return true;
}

bool CLoadDataDlg::InsertCarTypePartsDataEx(const char* lpStr,vector<string>& typeVect)
{
	CString strData = lpStr;
	CStringArray strArray;
	char ch = 9;
	int index;
	const int nRowCount = 6;

	static ASCarPartTableInfo tempPartInfo;
	static BYTE bType = DATA_TYPE_HEAD_E;

	strncpy(tempPartInfo.csCarTypeNum,"4A9",16);

	int iCount = DivStr(strData,strArray,ch);

	if (JudgeDataTypeEx(strArray))
	{
		return true;
	}

	if (iCount != nRowCount)
	{
		m_oFile<<lpStr<<endl;
		return true;
	}
	else if(JudgeDataType(strArray))
	{
		if (DATA_TYPE_HEAD_E == bType)
		{
			bType = DATA_TYPE_HEAD_C;
			strArray[0].Trim();
			int iPos = strArray[0].Find(' ');
			strncpy(tempPartInfo.csWholeNum,strArray[0].Left(iPos).operator LPCSTR(),16);
			strncpy(tempPartInfo.csWholeEngName,strArray[0].Right(strArray[0].GetLength()-iPos-1).Trim().operator LPCSTR(),64);

			memset(tempPartInfo.csPartNum,0,sizeof(tempPartInfo.csPartNum));
			memset(tempPartInfo.csWholeChinName,0,sizeof(tempPartInfo.csWholeChinName));
			memset(tempPartInfo.csItemNum,0,sizeof(tempPartInfo.csItemNum));
			memset(tempPartInfo.csEngName,0,sizeof(tempPartInfo.csEngName));
			memset(tempPartInfo.csChinName,0,sizeof(tempPartInfo.csChinName));
			tempPartInfo.strRemark.clear();
		}
		else
		{
			bType = DATA_TYPE_HEAD_E;
			if (!strArray[0].IsEmpty())
				strncpy(tempPartInfo.csWholeChinName,strArray[0].operator LPCSTR(),64);
		}
	}
	else
	{
		if (!strArray[0].IsEmpty())
		{
			if (!strArray[0].IsEmpty())
				strncpy(tempPartInfo.csItemNum,strArray[0].operator LPCSTR(),16);
			if (!strArray[1].IsEmpty())
				strncpy(tempPartInfo.csEngName,strArray[1].operator LPCSTR(),64);

			memset(tempPartInfo.csPartNum,0,sizeof(tempPartInfo.csPartNum));
			memset(tempPartInfo.csChinName,0,sizeof(tempPartInfo.csChinName));
			tempPartInfo.strRemark.clear();
		}
		else
		{
			if (strArray[3].IsEmpty())
			{
				strncpy(tempPartInfo.csChinName,strArray[1].operator LPCSTR(),64);
			}
			else
			{
				strncpy(tempPartInfo.csPartNum,strArray[3].operator LPCSTR(),32);
				tempPartInfo.strRemark = strArray[5].operator LPCSTR();

				ASCarTypePartsTableInfo tempInfo;
				strcpy(tempInfo.csCarTypeNum,tempPartInfo.csCarTypeNum);
				strcpy(tempInfo.csPartNum,tempPartInfo.csPartNum);

				if (0 == strArray[1].CompareNoCase("ALL"))
				{
					if(m_bLog)
					{
						FormatResult(&tempPartInfo,typeVect);
					}
					else
					{
						ASInsertCarPartInfo(&tempPartInfo);
						ASInsertCarTypePartsInfo(&tempInfo,typeVect);
					}
				}
				else if (IsHaveItem(typeVect,strArray[1].operator LPCSTR()))
				{
					std::vector<string> tempVect;
					tempVect.push_back(strArray[1].operator LPCSTR());

					if (m_bLog)
					{
						FormatResult(&tempPartInfo,tempVect);
					}
					else
					{
						ASInsertCarPartInfo(&tempPartInfo);
						ASInsertCarTypePartsInfo(&tempInfo,tempVect);
					}
				}
				else
				{
					strncpy(tempPartInfo.csChinName,strArray[1].operator LPCSTR(),64);

					if (m_bLog)
					{
						FormatResult(&tempPartInfo,typeVect,false);
					}
					else
					{
						ASInsertCarPartInfo(&tempPartInfo);
						//ASInsertCarTypePartsInfo(&tempInfo,typeVect);
					}
				}
			}
		}
	
	}

	return true;
}

TypeMap::iterator IsTheKeyValue(TypeMap& typeMap,const char* lpValue)
{

	TypeMap::iterator it = typeMap.find(lpValue);

	return it;

}

bool CLoadDataDlg::InsertCarTypePartsDataEx(const char* lpStr,vector<string>& typeVect,TypeMap& typeMap)
{
	CString strData = lpStr;
	CStringArray strArray;
	char ch = 9;
	int index;
	const int nRowCount = 6;
	TypeMap::iterator it = typeMap.end();

	static ASCarPartTableInfo tempPartInfo;
	static BYTE bType = DATA_TYPE_HEAD_E;

	strncpy(tempPartInfo.csCarTypeNum,"4A9",16);

	int iCount = DivStr(strData,strArray,ch);

	if (JudgeDataTypeEx(strArray))
	{
		return true;
	}

	if (iCount != nRowCount)
	{
		m_oFile<<lpStr<<endl;
		return true;
	}
	else if(JudgeDataType(strArray))
	{
		if (DATA_TYPE_HEAD_E == bType)
		{
			bType = DATA_TYPE_HEAD_C;
			strArray[0].Trim();
			int iPos = strArray[0].Find(' ');
			strncpy(tempPartInfo.csWholeNum,strArray[0].Left(iPos).operator LPCSTR(),16);
			strncpy(tempPartInfo.csWholeEngName,strArray[0].Right(strArray[0].GetLength()-iPos-1).Trim().operator LPCSTR(),64);

			memset(tempPartInfo.csPartNum,0,sizeof(tempPartInfo.csPartNum));
			memset(tempPartInfo.csWholeChinName,0,sizeof(tempPartInfo.csWholeChinName));
			memset(tempPartInfo.csItemNum,0,sizeof(tempPartInfo.csItemNum));
			memset(tempPartInfo.csEngName,0,sizeof(tempPartInfo.csEngName));
			memset(tempPartInfo.csChinName,0,sizeof(tempPartInfo.csChinName));
			tempPartInfo.strRemark.clear();
		}
		else
		{
			bType = DATA_TYPE_HEAD_E;
			if (!strArray[0].IsEmpty())
				strncpy(tempPartInfo.csWholeChinName,strArray[0].Trim().operator LPCSTR(),64);
		}
	}
	else
	{
		if (!strArray[0].IsEmpty())
		{
			if (!strArray[0].IsEmpty())
				strncpy(tempPartInfo.csItemNum,strArray[0].operator LPCSTR(),16);
			if (!strArray[1].IsEmpty())
				strncpy(tempPartInfo.csEngName,strArray[1].operator LPCSTR(),64);

			memset(tempPartInfo.csPartNum,0,sizeof(tempPartInfo.csPartNum));
			memset(tempPartInfo.csChinName,0,sizeof(tempPartInfo.csChinName));
			tempPartInfo.strRemark.clear();
		}
		else
		{
			if (strArray[3].IsEmpty())
			{
				strncpy(tempPartInfo.csChinName,strArray[1].operator LPCSTR(),64);
			}
			else
			{
				strncpy(tempPartInfo.csPartNum,strArray[3].operator LPCSTR(),32);
				tempPartInfo.strRemark = strArray[5].operator LPCSTR();

				ASCarTypePartsTableInfo tempInfo;
				strcpy(tempInfo.csCarTypeNum,tempPartInfo.csCarTypeNum);
				strcpy(tempInfo.csPartNum,tempPartInfo.csPartNum);

				if (0 == strArray[1].CompareNoCase("ALL"))
				{
					if(m_bLog)
					{
						FormatResult(&tempPartInfo,typeVect);
					}
					else
					{
						ASInsertCarPartInfo(&tempPartInfo);
						ASInsertCarTypePartsInfo(&tempInfo,typeVect);
					}
				}
				else if (typeMap.end() != (it=typeMap.find( strArray[1].operator LPCSTR())))
				{
					if(m_bLog)
					{
						FormatResult(&tempPartInfo,it->second);
					}
					else
					{
						ASInsertCarPartInfo(&tempPartInfo);
						ASInsertCarTypePartsInfo(&tempInfo,it->second);
					}
				}
				else if (IsHaveItem(typeVect,strArray[1].operator LPCSTR()))
				{
					std::vector<string> tempVect;
					tempVect.push_back(strArray[1].operator LPCSTR());

					if (m_bLog)
					{
						FormatResult(&tempPartInfo,tempVect);
					}
					else
					{
						ASInsertCarPartInfo(&tempPartInfo);
						ASInsertCarTypePartsInfo(&tempInfo,tempVect);
					}
				}
				else
				{
					strncpy(tempPartInfo.csChinName,strArray[1].operator LPCSTR(),64);

					if (m_bLog)
					{
						FormatResult(&tempPartInfo,typeVect,false);
					}
					else
					{
						ASInsertCarPartInfo(&tempPartInfo);
						//ASInsertCarTypePartsInfo(&tempInfo,typeVect);
					}
				}
			}
		}

	}

	return true;
}

bool CLoadDataDlg::InsertCarTypePartsDataEx(const char* lpStr,vector<string>& typeVect,vector<string>& typeOtherVect,TypeMap& typeMap)
{		
	CString strData = lpStr;
	CStringArray strArray;
	char ch = 9;
	int index;
	const int nRowCount = 6;
	TypeMap::iterator it = typeMap.end();

	static ASCarPartTableInfo tempPartInfo;
	static BYTE bType = DATA_TYPE_HEAD_E;

	CString strGetTypeTemp;
	GetDlgItemText(IDC_EDIT_LOAD_TYPE,strGetTypeTemp);
	strncpy(tempPartInfo.csCarTypeNum,strGetTypeTemp.operator LPCSTR(),16);

	int iCount = DivStr(strData,strArray,ch);

	if (JudgeDataTypeEx(strArray))
	{
		return true;
	}

	if (iCount != nRowCount)
	{
		m_oFile<<lpStr<<endl;
		return true;
	}
	else if(JudgeDataType(strArray))
	{
		if (DATA_TYPE_HEAD_E == bType)
		{
			bType = DATA_TYPE_HEAD_C;
			strArray[0].Trim();
			int iPos = strArray[0].Find(' ');
			strncpy(tempPartInfo.csWholeNum,strArray[0].Left(iPos).operator LPCSTR(),16);
			strncpy(tempPartInfo.csWholeEngName,strArray[0].Right(strArray[0].GetLength()-iPos-1).Trim().operator LPCSTR(),64);

			memset(tempPartInfo.csPartNum,0,sizeof(tempPartInfo.csPartNum));
			memset(tempPartInfo.csWholeChinName,0,sizeof(tempPartInfo.csWholeChinName));
			memset(tempPartInfo.csItemNum,0,sizeof(tempPartInfo.csItemNum));
			memset(tempPartInfo.csEngName,0,sizeof(tempPartInfo.csEngName));
			memset(tempPartInfo.csChinName,0,sizeof(tempPartInfo.csChinName));
			tempPartInfo.strRemark.clear();
		}
		else
		{
			bType = DATA_TYPE_HEAD_E;
			if (!strArray[0].IsEmpty())
				strncpy(tempPartInfo.csWholeChinName,strArray[0].Trim().operator LPCSTR(),64);
		}
	}
	else
	{
		if (!strArray[0].IsEmpty())
		{
			if (!strArray[0].IsEmpty())
				strncpy(tempPartInfo.csItemNum,strArray[0].operator LPCSTR(),16);
			if (!strArray[1].IsEmpty())
				strncpy(tempPartInfo.csEngName,strArray[1].operator LPCSTR(),64);

			memset(tempPartInfo.csPartNum,0,sizeof(tempPartInfo.csPartNum));
			memset(tempPartInfo.csChinName,0,sizeof(tempPartInfo.csChinName));
			tempPartInfo.strRemark.clear();
		}
		else
		{
			if (strArray[3].IsEmpty())
			{
				strncpy(tempPartInfo.csChinName,strArray[1].operator LPCSTR(),64);
			}
			else
			{
				strncpy(tempPartInfo.csPartNum,strArray[3].operator LPCSTR(),32);
				tempPartInfo.strRemark = strArray[5].operator LPCSTR();

				ASCarTypePartsTableInfo tempInfo;
				strcpy(tempInfo.csCarTypeNum,tempPartInfo.csCarTypeNum);
				strcpy(tempInfo.csPartNum,tempPartInfo.csPartNum);

				if (0 == strArray[1].CompareNoCase("ALL"))
				{
					if(m_bLog)
					{
						FormatResult(&tempPartInfo,typeVect);
					}
					else
					{
						ASInsertCarPartInfo(&tempPartInfo);
						ASInsertCarTypePartsInfo(&tempInfo,typeVect);
					}
				}
				else if (typeMap.end() != (it=typeMap.find( strArray[1].operator LPCSTR())))
				{
					if(m_bLog)
					{
						FormatResult(&tempPartInfo,it->second);
					}
					else
					{
						ASInsertCarPartInfo(&tempPartInfo);
						ASInsertCarTypePartsInfo(&tempInfo,it->second);
					}
				}
				else if (IsHaveItem(typeVect,strArray[1].operator LPCSTR())||
					IsHaveItem(typeOtherVect,strArray[1].operator LPCSTR()))
				{
					std::vector<string> tempVect;
					tempVect.push_back(strArray[1].operator LPCSTR());

					if (m_bLog)
					{
						FormatResult(&tempPartInfo,tempVect);
					}
					else
					{
						ASInsertCarPartInfo(&tempPartInfo);
						ASInsertCarTypePartsInfo(&tempInfo,tempVect);
					}
				}
				else
				{
					strncpy(tempPartInfo.csChinName,strArray[1].operator LPCSTR(),64);

					if (m_bLog)
					{
						FormatResult(&tempPartInfo,typeVect,false);
					}
					else
					{
						ASInsertCarPartInfo(&tempPartInfo);
						//ASInsertCarTypePartsInfo(&tempInfo,typeVect);
					}
				}
			}
		}

	}

	return true;
}

void CLoadDataDlg::FormatResult(void* lpResult,vector<string>& typeVect,bool bShow/*=true*/)
{
	ASCarPartTableInfo* pInfo = (ASCarPartTableInfo*)lpResult;

	ostringstream ostr;
	ostr<<pInfo->csCarTypeNum<<",";
	ostr<<pInfo->csPartNum<<",";
	ostr<<pInfo->csWholeNum<<",";
	ostr<<pInfo->csWholeEngName<<",";
	ostr<<pInfo->csWholeChinName<<",";
	ostr<<pInfo->csItemNum<<",";
	ostr<<pInfo->csEngName<<",";
	ostr<<pInfo->csChinName<<",";
	ostr<<pInfo->strRemark<<",";

	if (bShow)
	{
		ostr<<"<";
		for (int i=0;i<typeVect.size();++i)
			ostr<<typeVect[i]<<",";
		ostr<<">\n";
	}
	else
	{
		ostr<<"<>\n";
	}

	m_oFormatFile<<ostr.str();
}

bool CLoadDataDlg::InsertCarTypePartsDataEx2(const char* lpStr,vector<string>& typeVect,vector<string>& typeOtherVect,TypeMap& typeMap)
{
	CString strData = lpStr;
	CStringArray strArray;
	char ch = 9;
	int index;
	const int nRowCount = 9;
	TypeMap::iterator it = typeMap.end();

	static ASCarPartTableInfo tempPartInfo;
	static BYTE bType = DATA_TYPE_HEAD_E;

	CString strGetTypeTemp;
	GetDlgItemText(IDC_EDIT_LOAD_TYPE,strGetTypeTemp);
	strncpy(tempPartInfo.csCarTypeNum,strGetTypeTemp.operator LPCSTR(),16);

	int iCount = DivStr(strData,strArray,ch);

	if (JudgeDataTypeEx(strArray))
	{
		return true;
	}

	if (iCount != nRowCount)
	{
		m_oFile<<lpStr<<endl;
		return true;
	}
	else if(JudgeDataHead(strArray))
	{
		strArray[0].Trim();
		int iPos = strArray[0].Find(' '),iNext;
		strncpy(tempPartInfo.csWholeNum,strArray[0].Left(iPos).operator LPCSTR(),16);
		iNext = strArray[0].ReverseFind(' ');
		strncpy(tempPartInfo.csWholeEngName,strArray[0].Mid(iPos+1,iNext-iPos-1).Trim().operator LPCSTR(),64);
		strncpy(tempPartInfo.csWholeChinName,strArray[0].Right(strArray[0].GetLength()-iNext-1).Trim().operator LPCSTR(),64);

		memset(tempPartInfo.csPartNum,0,sizeof(tempPartInfo.csPartNum));
		memset(tempPartInfo.csItemNum,0,sizeof(tempPartInfo.csItemNum));
		memset(tempPartInfo.csEngName,0,sizeof(tempPartInfo.csEngName));
		memset(tempPartInfo.csChinName,0,sizeof(tempPartInfo.csChinName));
		tempPartInfo.strRemark.clear();
	}
	else
	{
		if (!strArray[0].IsEmpty())
			strncpy(tempPartInfo.csItemNum,strArray[0].operator LPCSTR(),16);
		if (!strArray[1].IsEmpty())
			strncpy(tempPartInfo.csChinName,strArray[1].operator LPCSTR(),64);
		if (!strArray[2].IsEmpty())
			strncpy(tempPartInfo.csEngName,strArray[2].operator LPCSTR(),64);
		if (!strArray[3].IsEmpty())
			strncpy(tempPartInfo.csPartNum,strArray[3].operator LPCSTR(),32);
		tempPartInfo.strRemark = strArray[8].operator LPCSTR();

		ASCarTypePartsTableInfo tempInfo;
		strcpy(tempInfo.csCarTypeNum,tempPartInfo.csCarTypeNum);
		strcpy(tempInfo.csPartNum,tempPartInfo.csPartNum);

		if (0 == strArray[4].CompareNoCase("ALL"))
		{
			if(m_bLog)
			{
				FormatResult(&tempPartInfo,typeVect);
			}
			else
			{
				ASInsertCarPartInfo(&tempPartInfo);
				ASInsertCarTypePartsInfo(&tempInfo,typeVect);
			}
		}
		else if (typeMap.end() != (it=typeMap.find( strArray[4].operator LPCSTR())))
		{
			if(m_bLog)
			{
				FormatResult(&tempPartInfo,it->second);
			}
			else
			{
				ASInsertCarPartInfo(&tempPartInfo);
				ASInsertCarTypePartsInfo(&tempInfo,it->second);
			}
		}
		else if (IsHaveItem(typeVect,strArray[4].operator LPCSTR())||
			IsHaveItem(typeOtherVect,strArray[4].operator LPCSTR()))
		{
			std::vector<string> tempVect;
			tempVect.push_back(strArray[4].operator LPCSTR());

			if (m_bLog)
			{
				FormatResult(&tempPartInfo,tempVect);
			}
			else
			{
				ASInsertCarPartInfo(&tempPartInfo);
				ASInsertCarTypePartsInfo(&tempInfo,tempVect);
			}
		}
		else
		{
			strncpy(tempPartInfo.csChinName,strArray[4].operator LPCSTR(),64);

			if (m_bLog)
			{
				FormatResult(&tempPartInfo,typeVect,false);
			}
			else
			{
				ASInsertCarPartInfo(&tempPartInfo);
				//ASInsertCarTypePartsInfo(&tempInfo,typeVect);
			}
		}
	}

	return true;
}