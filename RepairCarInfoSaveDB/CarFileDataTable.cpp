#include "stdafx.h"
#include "CarFileDataTable.h"


CCarFileDataTable::CCarFileDataTable(CDbBase* pBase)
	:CTableOperateBase(pBase)
{
}


CCarFileDataTable::~CCarFileDataTable(void)
{
}


int CCarFileDataTable::InitTable()
{
	int iRes = SQLITE_OK;

	iRes = m_pDbBase->m_dbOp.get_table("CarFileData");
	if (SQLITE_OK != iRes)
	{
		const char* lpTableInfoSql = "CREATE TABLE CarFileData (CarTypeNum TEXT,CarFileName TEXT PRIMARY KEY NOT NULL, Notes TEXT);";
		iRes = m_pDbBase->m_dbOp.execute_dml(lpTableInfoSql);
	}

	return iRes;
}

int CCarFileDataTable::InsertCarFileData(const PCarFileData pInfo)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	sql<<"insert into CarFileData values ('";
	sql<<pInfo->csCarTypeNum<<"','";
	sql<<pInfo->strFileName<<"','";
	sql<<pInfo->strNotes<<"');";
	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}

int CCarFileDataTable::UpdateCarFileData(const PCarFileData pInfo)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	sql<<"update CarFileData set ";
	sql<<"CarTypeNum='"<<pInfo->csCarTypeNum<<"',";
	sql<<"Notes='"<<pInfo->strNotes<<"'";
	sql<<" where CarFileName='"<<pInfo->strFileName<<"';";

	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}

int CCarFileDataTable::GetCarFileDataCount(const PCarFileData pInfo,int* pTotalCount)
{
	sqlstring sql;
	sql<<"select count(*) from CarFileData where ";
	sql<<" CarTypeNum like '%"<<pInfo->csCarTypeNum<<"%' and ";
	sql<<" CarFileName like '%"<<pInfo->strFileName<<"%' and ";
	sql<<" Notes like '%"<<pInfo->strNotes<<"%';";

	int iCount = GetRecordCount(sql.str().c_str());
	if (pTotalCount)
	{
		*pTotalCount = iCount;
	}

	return SQLITE_OK;
}

int CCarFileDataTable::GetCarFileData(const PCarFileData pInfo,int iPages,int iMaxCount,std::vector<CarFileData>& carFileDataList,bool bOrderInc/*=true*/)
{
	sqlstring sql;
	sql<<"select * from CarFileData where ";
	sql<<" CarTypeNum like '%"<<pInfo->csCarTypeNum<<"%' and ";
	sql<<" CarFileName like '%"<<pInfo->strFileName<<"%' and ";
	sql<<" Notes like '%"<<pInfo->strNotes<<"%'";

	sql<<" order by CarFileName ";
	if (false == bOrderInc)
		sql<<"desc ";
	sql<<"limit "<<iMaxCount<<" offset "<<iMaxCount*iPages<<";";

	return GetCarFileDataSql(sql.str().c_str(),carFileDataList);
}

int	CCarFileDataTable::DeleteCarFileData(const char* lpFileName)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	sql<<"delete from CarFileData where CarFileName='";
	sql<<lpFileName<<"';";

	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}

int CCarFileDataTable::GetCarFileDataSql(const char* lpSql,std::vector<CarFileData>& carFileDataList)
{
	return m_pDbBase->m_dbOp.execute(lpSql,CCarFileDataTable::GetCarFileDataHandle,&carFileDataList,NULL);
}

int CCarFileDataTable::GetCarFileDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName)
{
	std::vector<CarFileData>* pCarFileDataList = (std::vector<CarFileData>*)lpPara;
	CarFileData tempInfo;

	CConvertChar convertChar;

	for (int i=0;i<nColumn;++i)
	{
		if (0== strcmp(lppColumnName[i],"CarTypeNum"))
		{
			strcpy(tempInfo.csCarTypeNum,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"CarFileName"))
		{
			tempInfo.strFileName = convertChar.ToGBK(lppColumnValue[i]);
			continue;
		}

		if (0== strcmp(lppColumnName[i],"Notes"))
		{
			tempInfo.strNotes = convertChar.ToGBK(lppColumnValue[i]);
		}
	}

	pCarFileDataList->push_back(tempInfo);

	return SQLITE_OK;
}