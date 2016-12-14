#include "stdafx.h"
#include "CarPartTable.h"


CCarPartTable::CCarPartTable(CDbBase* pBase)
	:CTableOperateBase(pBase)
{
}


CCarPartTable::~CCarPartTable(void)
{
}


int CCarPartTable::InitTable()
{
	int iRes = SQLITE_OK;

	iRes = m_pDbBase->m_dbOp.get_table("CarPartInfo");
	if (SQLITE_OK != iRes)
	{
		const char* lpTableInfoSql = "CREATE TABLE CarPartInfo (CarTypeNum TEXT,DAENum TEXT,MMCNum TEXT,EPLNum TEXT,VCNum TEXT,Level INT,\
									 EnglishName TEXT,ChineseName TEXT,PicNum TEXT,InstallNum TEXT,InstallMark INI,PartReserve TEXT,PRIMARY KEY (CarTypeNum,DAENum,MMCNum));";
		iRes = m_pDbBase->m_dbOp.execute_dml(lpTableInfoSql);
	}

	iRes = m_pDbBase->m_dbOp.get_table("ASCarPartInfo");
	if (SQLITE_OK != iRes)
	{
		const char* lpTableInfoSql = "CREATE TABLE ASCarPartInfo (CarTypeNum TEXT,PartNum TEXT,WholeNum TEXT,WholeEngName TEXT,WholeChinName TEXT,ItemNum TEXT,\
									 EngName TEXT,ChinName TEXT,Remark TEXT,PartReserve TEXT,PRIMARY KEY (CarTypeNum,PartNum));";
		iRes = m_pDbBase->m_dbOp.execute_dml(lpTableInfoSql);
	}

	return iRes;
}

int	CCarPartTable::InsertCarPartInfo(const PCarPartTableInfo	pInfo)
{
	int iRes = SQLITE_OK;

	sqlstring sql;
	sql<<"insert into CarPartInfo values('";
	sql<<pInfo->csCarTypeNum<<"','";
	sql<<pInfo->csDAENum<<"','";
	sql<<pInfo->csMMCNum<<"','";
	sql<<pInfo->csEPLNum<<"','";
	sql<<pInfo->csVCNum<<"',";
	sql<<pInfo->iLevel<<",'";
	sql<<pInfo->csEnglishName<<"','";
	sql<<pInfo->csChineseName<<"','";
	sql<<pInfo->csPicNum<<"','";
	sql<<pInfo->csInstallNum<<"',";
	sql<<pInfo->iInstallMark<<",'";
	sql<<pInfo->strPartReserve<<"');";

	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}

int	CCarPartTable::UpdateCarPartInfo(PCarPartTableInfo	pInfo)
{
	int iRes = SQLITE_OK;
	bool bUp = false;
	sqlstring sql;

	sql<<"update CarPartInfo set ";
	sql<<"EPLNum='"<<pInfo->csEPLNum<<"',";
	sql<<"VCNum='"<<pInfo->csVCNum<<"',";
	sql<<"Level="<<pInfo->iLevel<<",";
	sql<<"EnglishName='"<<pInfo->csEnglishName<<"',";
	sql<<"ChineseName='"<<pInfo->csChineseName<<"',";
	sql<<"PicNum='"<<pInfo->csPicNum<<"',";
	sql<<"InstallNum='"<<pInfo->csInstallNum<<"',";
	sql<<"InstallMark="<<pInfo->iInstallMark<<",";
	sql<<"PartReserve='"<<pInfo->strPartReserve<<"'";
	sql<<" where CarTypeNum='"<<pInfo->csCarTypeNum<<"' and DAENum='"<<pInfo->csDAENum<<"' and MMCNum='"<<pInfo->csMMCNum<<"';";

	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}

int CCarPartTable::GetCarPartCount(const PCarPartTableInfo pInfo,int* pTotalCount)
{
	sqlstring sql;
	sql<<"select count(*) from CarPartInfo where ";
	sql<<" CarTypeNum like '%"<<pInfo->csCarTypeNum<<"%' and ";
	sql<<" DAENum like '%"<<pInfo->csDAENum<<"%' and ";
	sql<<" MMCNum like '%"<<pInfo->csMMCNum<<"%' and ";
	sql<<" PicNum like '%"<<pInfo->csPicNum<<"%' and ";
	sql<<" ChineseName like '%"<<pInfo->csChineseName<<"%' and ";
	sql<<" PartReserve like '%"<<pInfo->strPartReserve<<"%';";

	int iCount = GetRecordCount(sql.str().c_str());
	if (pTotalCount)
	{
		*pTotalCount = iCount;
	}

	return SQLITE_OK;
}


int CCarPartTable::GetCarPartInfo(const PCarPartTableInfo pInfo,int iPages,int iMaxCount,std::vector<CarPartTableInfo>& carPartInfoList,bool bOrderInc/*=true*/)
{
	sqlstring sql;
	sql<<"select * from CarPartInfo where ";
	sql<<" CarTypeNum like '%"<<pInfo->csCarTypeNum<<"%' and ";
	sql<<" DAENum like '%"<<pInfo->csDAENum<<"%' and ";
	sql<<" MMCNum like '%"<<pInfo->csMMCNum<<"%' and ";
	sql<<" PicNum like '%"<<pInfo->csPicNum<<"%' and ";
	sql<<" ChineseName like '%"<<pInfo->csChineseName<<"%' and ";
	sql<<" PartReserve like '%"<<pInfo->strPartReserve<<"%' ";

	sql<<" order by CarTypeNum,DAENum,MMCNum ";
	if (false == bOrderInc)
		sql<<"desc ";
	sql<<"limit "<<iMaxCount<<" offset "<<iMaxCount*iPages<<";";

	return GetCarPartData(sql.str().c_str(),carPartInfoList);
}

int	CCarPartTable::DeleteCarPartInfo(const PCarPartTableInfo	pInfo)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	sql<<"delete from CarPartInfo where CarTypeNum='"<<pInfo->csCarTypeNum<<"' and DAENum='"<<pInfo->csDAENum<<"' and MMCNum='"<<pInfo->csMMCNum<<"';";

	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}


int CCarPartTable::GetCarPartData(const char* lpSql,std::vector<CarPartTableInfo>& carPartInfoList)
{
	return m_pDbBase->m_dbOp.execute(lpSql,CCarPartTable::GetCarPartInfoDataHandle,&carPartInfoList,NULL);
}

int CCarPartTable::GetCarPartInfoDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName)
{
	std::vector<CarPartTableInfo>* pCarPartList = (std::vector<CarPartTableInfo>*)lpPara;
	CarPartTableInfo tempInfo;
	CConvertChar convertChar;

	for (int i=0;i<nColumn;++i)
	{
		if (0== strcmp(lppColumnName[i],"CarTypeNum"))
		{
			strcpy(tempInfo.csCarTypeNum,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"DAENum"))
		{
			strcpy(tempInfo.csDAENum,lppColumnValue[i]);
			continue;
		}

		if (0== strcmp(lppColumnName[i],"MMCNum"))
		{
			strcpy(tempInfo.csMMCNum,lppColumnValue[i]);
			continue;
		}

		if (0== strcmp(lppColumnName[i],"EPLNum"))
		{
			strcpy(tempInfo.csEPLNum,lppColumnValue[i]);
			continue;
		}

		if (0== strcmp(lppColumnName[i],"VCNum"))
		{
			strcpy(tempInfo.csVCNum,lppColumnValue[i]);
			continue;
		}

		if (0== strcmp(lppColumnName[i],"Level"))
		{
			tempInfo.iLevel = atoi(lppColumnValue[i]);
			continue;
		}

		if (0== strcmp(lppColumnName[i],"EnglishName"))
		{
			strcpy(tempInfo.csEnglishName,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"ChineseName"))
		{
			strcpy(tempInfo.csChineseName,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"PicNum"))
		{
			strcpy(tempInfo.csPicNum,lppColumnValue[i]);
			continue;
		}

		if (0== strcmp(lppColumnName[i],"InstallNum"))
		{
			strcpy(tempInfo.csInstallNum,lppColumnValue[i]);
			continue;
		}

		if (0== strcmp(lppColumnName[i],"InstallMark"))
		{
			tempInfo.iInstallMark = atoi(lppColumnValue[i]);
			continue;
		}

		if (0 == strcmp(lppColumnName[i],"PartReserve"))
		{
			tempInfo.strPartReserve = convertChar.ToGBK(lppColumnValue[i]);
		}
	}

	pCarPartList->push_back(tempInfo);

	return SQLITE_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int	CCarPartTable::ASInsertCarPartInfo(const PASCarPartTableInfo	pInfo)
{
	int iRes = SQLITE_OK;

	sqlstring sql;
	sql<<"insert into ASCarPartInfo values('";
	sql<<pInfo->csCarTypeNum<<"','";
	sql<<pInfo->csPartNum<<"','";
	sql<<pInfo->csWholeNum<<"','";
	sql<<pInfo->csWholeEngName<<"','";
	sql<<pInfo->csWholeChinName<<"','";
	sql<<pInfo->csItemNum<<"','";
	sql<<pInfo->csEngName<<"','";
	sql<<pInfo->csChinName<<"','";
	sql<<pInfo->strRemark<<"','";
	sql<<pInfo->strPartReserve<<"');";

	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}

int	CCarPartTable::ASUpdateCarPartInfo(PASCarPartTableInfo	pInfo)
{
	int iRes = SQLITE_OK;
	bool bUp = false;
	sqlstring sql;

	sql<<"update ASCarPartInfo set ";
	sql<<"WholeNum='"<<pInfo->csWholeNum<<"',";
	sql<<"WholeEngName='"<<pInfo->csWholeEngName<<"',";
	sql<<"WholeChinName='"<<pInfo->csWholeChinName<<"',";
	sql<<"ItemNum='"<<pInfo->csItemNum<<"',";
	sql<<"EngName='"<<pInfo->csEngName<<"',";
	sql<<"ChinName='"<<pInfo->csChinName<<"',";
	sql<<"Remark='"<<pInfo->strRemark<<"',";
	sql<<"PartReserve='"<<pInfo->strPartReserve<<"'";
	sql<<" where CarTypeNum='"<<pInfo->csCarTypeNum<<"' and PartNum='"<<pInfo->csPartNum<<"';";

	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}

int CCarPartTable::ASGetCarPartCount(const PASCarPartTableInfo pInfo,int* pTotalCount)
{
	sqlstring sql;
	sql<<"select count(*) from ASCarPartInfo where ";
	sql<<" CarTypeNum like '%"<<pInfo->csCarTypeNum<<"%' and ";
	sql<<" PartNum like '%"<<pInfo->csPartNum<<"%' and ";
	sql<<" WholeChinName like '%"<<pInfo->csWholeChinName<<"%' and ";
	sql<<" ChinName like '%"<<pInfo->csChinName<<"%' and ";
	sql<<" Remark like '%"<<pInfo->strRemark<<"%' and ";
	sql<<" PartReserve like '%"<<pInfo->strPartReserve<<"%';";

	int iCount = GetRecordCount(sql.str().c_str());
	if (pTotalCount)
	{
		*pTotalCount = iCount;
	}

	return SQLITE_OK;
}


int CCarPartTable::ASGetCarPartInfo(const PASCarPartTableInfo pInfo,int iPages,int iMaxCount,std::vector<ASCarPartTableInfo>& carPartInfoList,bool bOrderInc/*=true*/)
{
	sqlstring sql;
	sql<<"select * from ASCarPartInfo where ";
	sql<<" CarTypeNum like '%"<<pInfo->csCarTypeNum<<"%' and ";
	sql<<" PartNum like '%"<<pInfo->csPartNum<<"%' and ";
	sql<<" WholeChinName like '%"<<pInfo->csWholeChinName<<"%' and ";
	sql<<" ChinName like '%"<<pInfo->csChinName<<"%' and ";
	sql<<" Remark like '%"<<pInfo->strRemark<<"%' and ";
	sql<<" PartReserve like '%"<<pInfo->strPartReserve<<"%' ";

	sql<<" order by CarTypeNum,PartNum ";
	if (false == bOrderInc)
		sql<<"desc ";
	sql<<"limit "<<iMaxCount<<" offset "<<iMaxCount*iPages<<";";

	return m_pDbBase->m_dbOp.execute(sql.str().c_str(),CCarPartTable::ASGetCarPartInfoDataHandle,&carPartInfoList,NULL);
}

int	CCarPartTable::ASDeleteCarPartInfo(const PASCarPartTableInfo	pInfo)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	sql<<"delete from ASCarPartInfo where CarTypeNum='"<<pInfo->csCarTypeNum<<"' and PartNum='"<<pInfo->csPartNum<<"';";

	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}


int CCarPartTable::ASGetCarPartInfoDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName)
{
	std::vector<ASCarPartTableInfo>* pCarPartList = (std::vector<ASCarPartTableInfo>*)lpPara;
	ASCarPartTableInfo tempInfo;
	CConvertChar convertChar;

	for (int i=0;i<nColumn;++i)
	{
		if (0== strcmp(lppColumnName[i],"CarTypeNum"))
		{
			strcpy(tempInfo.csCarTypeNum,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"PartNum"))
		{
			strcpy(tempInfo.csPartNum,lppColumnValue[i]);
			continue;
		}

		if (0== strcmp(lppColumnName[i],"WholeNum"))
		{
			strcpy(tempInfo.csWholeNum,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"WholeEngName"))
		{
			strcpy(tempInfo.csWholeEngName,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"WholeChinName"))
		{
			strcpy(tempInfo.csWholeChinName,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}


		if (0== strcmp(lppColumnName[i],"ItemNum"))
		{
			strcpy(tempInfo.csItemNum,lppColumnValue[i]);
			continue;
		}

		if (0== strcmp(lppColumnName[i],"EngName"))
		{
			strcpy(tempInfo.csEngName,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"ChinName"))
		{
			strcpy(tempInfo.csChinName,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"Remark"))
		{
			tempInfo.strRemark = convertChar.ToGBK(lppColumnValue[i]);
			continue;
		}

		if (0 == strcmp(lppColumnName[i],"PartReserve"))
		{
			tempInfo.strPartReserve = convertChar.ToGBK(lppColumnValue[i]);
		}
	}

	pCarPartList->push_back(tempInfo);

	return SQLITE_OK;
}