#include "stdafx.h"
#include "CarTypePartsTable.h"
#include <list>
#include <string>
using namespace std;


CCarTypePartsTable::CCarTypePartsTable(CDbBase* pBase)
	:CTableOperateBase(pBase)
{
}


CCarTypePartsTable::~CCarTypePartsTable(void)
{
}


int CCarTypePartsTable::InitTable()
{
	int iRes = SQLITE_OK;

	iRes = m_pDbBase->m_dbOp.get_table("CarTypePartsInfo");
	if (SQLITE_OK != iRes)
	{
		const char* lpTableInfoSql = "CREATE TABLE CarTypePartsInfo(CarDetailTypeNumber TEXT NOT NULL,CarTypeNum TEXT,DAENum TEXT, MMCNum TEXT,\
									 FOREIGN KEY(CarDetailTypeNumber) REFERENCES CarTypeInfo(CarDetailTypeNum) ON DELETE CASCADE,\
									 FOREIGN KEY(CarTypeNum,DAENum,MMCNum) REFERENCES CarPartInfo(CarTypeNum,DAENum,MMCNum) ON DELETE CASCADE);";  
		iRes = m_pDbBase->m_dbOp.execute_dml(lpTableInfoSql);
	}

	return iRes;
}

int	CCarTypePartsTable::InsertCarTypePartsInfo(const PCarTypePartsTableInfo pInfo,std::vector<std::string>& carTypeInfoList)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	iRes = m_pDbBase->m_dbOp.begin_trans();
	if (SQLITE_OK == iRes)
	{
		for (int i=0;i<carTypeInfoList.size();++i)
		{
			sql.str("");

			sql<<"insert into CarTypePartsInfo values('";
			sql<<carTypeInfoList[i]<<"','";
			sql<<pInfo->csCarTypeNum<<"','";
			sql<<pInfo->csDAENum<<"','";
			sql<<pInfo->csMMCNum<<"');";

			iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(),NULL,NULL,NULL);
			if (SQLITE_OK != iRes)
			{
				break;
			}
		}
	}

	if (SQLITE_OK == iRes)
	{
		iRes = m_pDbBase->m_dbOp.commit_trans();
	}
	else
	{
		iRes = m_pDbBase->m_dbOp.rollback_trans();
	}

	return iRes;
}

int	CCarTypePartsTable::UpdateCarTypePartsInfo(const PCarTypePartsTableInfo pInfo,std::vector<std::string>& carTypeInfoList)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	iRes = m_pDbBase->m_dbOp.begin_trans();
	if (SQLITE_OK == iRes)
	{
		sql <<"delete from CarTypePartsInfo where ";
		sql <<"CarTypeNum='"<<pInfo->csCarTypeNum<<"' and DAENum='"<<pInfo->csDAENum<<"' and MMCNum='"<<pInfo->csMMCNum<<"';";
		iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(),NULL,NULL,NULL);

		if (SQLITE_OK == iRes)
		{
			for (int i=0;i<carTypeInfoList.size();++i)
			{
				sql.str("");

				sql<<"insert into CarTypePartsInfo values('";
				sql<<carTypeInfoList[i]<<"','";
				sql<<pInfo->csCarTypeNum<<"','";
				sql<<pInfo->csDAENum<<"','";
				sql<<pInfo->csMMCNum<<"');";

				iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(),NULL,NULL,NULL);
				if (SQLITE_OK != iRes)
					break;
			}
		}
	}

	if (SQLITE_OK == iRes)
	{
		iRes = m_pDbBase->m_dbOp.commit_trans();
	}
	else
	{
		iRes = m_pDbBase->m_dbOp.rollback_trans();
	}

	return iRes;
}

int CCarTypePartsTable::GetCarTypePartsSuppInfoEx(const PCarTypePartsTableInfo pInfo,std::vector<CarTypeTableInfo>& carTypeInfoList)
{
	int iRes = SQLITE_OK;
	sqlstring sql;
	sql<<"SELECT CarTypeInfo.*  FROM CarTypeInfo,CarTypePartsInfo ON CarTypeInfo.CarDetailTypeNum=CarTypePartsInfo.CarDetailTypeNumber";
	sql<<" where CarTypePartsInfo.CarTypeNum='"<<pInfo->csCarTypeNum<<"' and CarTypePartsInfo.DAENum='"<<pInfo->csDAENum<<"' and CarTypePartsInfo.MMCNum='"<<pInfo->csMMCNum<<"' order by CarTypeInfo.CarDetailTypeNum;";

	iRes =  m_pDbBase->m_dbOp.execute(sql.str().c_str(),CCarTypePartsTable::GetCarTypeDataHandle,&carTypeInfoList,NULL);

	return iRes;
}

int CCarTypePartsTable::GetCarTypePartsSuppInfo(const PCarTypePartsTableInfo pInfo,std::vector<CarTypeTableInfo>& carTypeInfoList)
{
	int iRes = SQLITE_OK;
	sqlstring sql;
	sql<<"SELECT CarTypeInfo.*,TempTable.CarDetailTypeNumber  FROM CarTypeInfo LEFT OUTER JOIN (select  CarDetailTypeNumber from CarTypePartsInfo where CarTypeNum='"<<pInfo->csCarTypeNum<<"' and DAENum='"<<pInfo->csDAENum<<"' and MMCNum='"<<pInfo->csMMCNum;
	sql<< "') TempTable ON CarTypeInfo.CarDetailTypeNum=TempTable.CarDetailTypeNumber  order by CarTypeInfo.CarDetailTypeNum;";

	iRes =  m_pDbBase->m_dbOp.execute(sql.str().c_str(),CCarTypePartsTable::GetCarTypeDataHandle,&carTypeInfoList,NULL);

	return iRes;
}

int CCarTypePartsTable::GetCarTypePartsAllInfo(std::vector<CarTypeTableInfo>& carTypeInfoList)
{
	int iRes = SQLITE_OK;
	sqlstring sql;
	sql<<"SELECT * FROM CarTypeInfo  order by CarDetailTypeNum;";

	iRes =  m_pDbBase->m_dbOp.execute(sql.str().c_str(),CCarTypePartsTable::GetCarTypeDataHandle,&carTypeInfoList,NULL);

	return iRes;
}

int CCarTypePartsTable::GetCarTypePartsCount(const PSearchCarTypePartsInfo pInfo,int* pTotalCount)
{
	sqlstring sql;

	sql<<"SELECT COUNT(*)  FROM CarTypeInfo,CarPartInfo,CarTypePartsInfo \
		 where CarTypeInfo.CarDetailTypeNum=CarTypePartsInfo.CarDetailTypeNumber and CarTypePartsInfo.CarTypeNum=CarPartInfo.CarTypeNum and CarTypePartsInfo.DAENum=CarPartInfo.DAENum and CarTypePartsInfo.MMCNum=CarPartInfo.MMCNum and ";
	sql<<" CarTypeInfo.CarDetailTypeNum like '%"<<pInfo->csCarDetailTypeNum<<"%' and ";
	sql<<" CarTypeInfo.CarFactory like '%"<<pInfo->csCarFactory<<"%' and ";
	sql<<" CarTypeInfo.CarDetailName like '%"<<pInfo->csCarDetailName<<"%' and ";
	sql<<" CarPartInfo.CarTypeNum like '%"<<pInfo->csCarTypeNum<<"%' and";
	sql<<" CarPartInfo.DAENum like '%"<<pInfo->csDAENum<<"%' and ";
	sql<<" CarPartInfo.MMCNum like '%"<<pInfo->csMMCNum<<"%' and ";
	sql<<" CarPartInfo.ChineseName like '%"<<pInfo->csChineseName<<"%';";

	int iCount = GetRecordCount(sql.str().c_str());
	if (pTotalCount)
	{
		*pTotalCount = iCount;
	}

	return SQLITE_OK;
}

int CCarTypePartsTable::GetCarTypePartsInfo(const PSearchCarTypePartsInfo pInfo,int iPages,int iMaxCount,std::vector<SearchCarTypePartsInfo>& carTypePartInfoList,bool bOrderInc/*=true*/)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	sql<<"SELECT CarTypeInfo.CarDetailTypeNum,CarTypeInfo.CarFactory,CarTypeInfo.CarDetailName,CarPartInfo.CarTypeNum,CarPartInfo.DAENum,CarPartInfo.MMCNum,CarPartInfo.ChineseName,CarPartInfo.Level  FROM CarTypeInfo,CarPartInfo,CarTypePartsInfo \
		where CarTypeInfo.CarDetailTypeNum=CarTypePartsInfo.CarDetailTypeNumber and CarTypePartsInfo.CarTypeNum=CarPartInfo.CarTypeNum and CarTypePartsInfo.DAENum=CarPartInfo.DAENum and CarTypePartsInfo.MMCNum=CarPartInfo.MMCNum  and ";
	sql<<" CarTypeInfo.CarDetailTypeNum like '%"<<pInfo->csCarDetailTypeNum<<"%' and";
	sql<<" CarTypeInfo.CarFactory like '%"<<pInfo->csCarFactory<<"%' and";
	sql<<" CarTypeInfo.CarDetailName like '%"<<pInfo->csCarDetailName<<"%' and";
	sql<<" CarPartInfo.CarTypeNum like '%"<<pInfo->csCarTypeNum<<"%' and";
	sql<<" CarPartInfo.DAENum like '%"<<pInfo->csDAENum<<"%' and";
	sql<<" CarPartInfo.MMCNum like '%"<<pInfo->csMMCNum<<"%' and";
	sql<<" CarPartInfo.ChineseName like '%"<<pInfo->csChineseName<<"%'";

	sql<<" order by CarTypeInfo.CarDetailTypeNum ";
	if (false == bOrderInc)
		sql<<"desc ";
	sql<<"limit "<<iMaxCount<<" offset "<<iMaxCount*iPages<<";";

	iRes =  m_pDbBase->m_dbOp.execute(sql.str().c_str(),CCarTypePartsTable::GetCarPartsDataHandle,&carTypePartInfoList,NULL);

	return iRes;
}

int	CCarTypePartsTable::DeleteCarTypePartsInfo(const PCarTypePartsTableInfo pInfo)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	sql<<"delete from CarTypePartsInfo where CarDetailTypeNumber='"<<pInfo->csCarDetailTypeNum<<"' and CarTypeNum='"<<pInfo->csCarTypeNum<<"' and DAENum='"<<pInfo->csDAENum<<"' and MMCNum='"<<pInfo->csMMCNum<<"';";

	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}

int CCarTypePartsTable::GetCarPartsDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName)
{
	std::vector<SearchCarTypePartsInfo>* pCarTypeList = (std::vector<SearchCarTypePartsInfo>*)lpPara;
	SearchCarTypePartsInfo tempCarTypeInfo;

	CConvertChar convertChar;

	for (int i=0;i<nColumn;++i)
	{
		//,,,,,,ChineseName,
		if (0== strcmp(lppColumnName[i],"CarDetailTypeNum"))
		{
			strcpy(tempCarTypeInfo.csCarDetailTypeNum,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"CarFactory"))
		{
			strcpy(tempCarTypeInfo.csCarFactory,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"CarDetailName"))
		{
			strcpy(tempCarTypeInfo.csCarDetailName,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"CarTypeNum"))
		{
			strcpy(tempCarTypeInfo.csCarTypeNum,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"DAENum"))
		{
			strcpy(tempCarTypeInfo.csDAENum,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"MMCNum"))
		{
			strcpy(tempCarTypeInfo.csMMCNum,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"ChineseName"))
		{
			strcpy(tempCarTypeInfo.csChineseName,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"Level"))
		{
			tempCarTypeInfo.iLevel = atoi(lppColumnValue[i]);
		}
	}

	pCarTypeList->push_back(tempCarTypeInfo);

	return SQLITE_OK;
}

int CCarTypePartsTable::GetCarTypeDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName)
{
	std::vector<CarTypeTableInfo>* pCarTypeList = (std::vector<CarTypeTableInfo>*)lpPara;
	CarTypeTableInfo tempCarTypeInfo;

	CConvertChar convertChar;

	for (int i=0;i<nColumn;++i)
	{
		if (0== strcmp(lppColumnName[i],"CarTypeNum"))
		{
			strcpy(tempCarTypeInfo.csCarTypeNum,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"CarDetailTypeNum"))
		{
			strcpy(tempCarTypeInfo.csCarDetailTypeNum,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"CarFactory"))
		{
			strcpy(tempCarTypeInfo.csCarFactory,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"CarStatus"))
		{
			strcpy(tempCarTypeInfo.csCarStatus,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"CarDetailName"))
		{
			strcpy(tempCarTypeInfo.csCarDetailName,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"CarNotes"))
		{
			tempCarTypeInfo.strCarNotes = convertChar.ToGBK(lppColumnValue[i]);
		}

		if (0== strcmp(lppColumnName[i],"CarDetailTypeNumber"))
		{
			if (lppColumnValue[i])
			{
				tempCarTypeInfo.strCarReserve = "1";
			}
			else
			{
				tempCarTypeInfo.strCarReserve = "";
			}
		}
	}

	pCarTypeList->push_back(tempCarTypeInfo);

	return SQLITE_OK;
}