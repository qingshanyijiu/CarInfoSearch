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

	iRes = m_pDbBase->m_dbOp.get_table("ASCarTypePartsInfo");
	if (SQLITE_OK != iRes)
	{
		const char* lpTableInfoSql = "CREATE TABLE ASCarTypePartsInfo(CarDetailTypeNumber TEXT NOT NULL,CarTypeNum TEXT,PartNum TEXT,\
									 FOREIGN KEY(CarDetailTypeNumber) REFERENCES ASCarTypeInfo(CarDetailTypeNum) ON DELETE CASCADE,\
									 FOREIGN KEY(CarTypeNum,PartNum) REFERENCES ASCarPartInfo(CarTypeNum,PartNum) ON DELETE CASCADE);";  
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
	sql<<" CarPartInfo.ChineseName like '%"<<pInfo->csChineseName<<"%' and ";
	sql<<" CarPartInfo.PartReserve like '%"<<pInfo->strPartReserve<<"%';";

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

	sql<<"SELECT CarTypeInfo.CarDetailTypeNum,CarTypeInfo.CarFactory,CarTypeInfo.CarDetailName,CarPartInfo.CarTypeNum,CarPartInfo.DAENum,CarPartInfo.MMCNum,CarPartInfo.ChineseName,CarPartInfo.Level,CarPartInfo.PartReserve  FROM CarTypeInfo,CarPartInfo,CarTypePartsInfo \
		where CarTypeInfo.CarDetailTypeNum=CarTypePartsInfo.CarDetailTypeNumber and CarTypePartsInfo.CarTypeNum=CarPartInfo.CarTypeNum and CarTypePartsInfo.DAENum=CarPartInfo.DAENum and CarTypePartsInfo.MMCNum=CarPartInfo.MMCNum  and ";
	sql<<" CarTypeInfo.CarDetailTypeNum like '%"<<pInfo->csCarDetailTypeNum<<"%' and";
	sql<<" CarTypeInfo.CarFactory like '%"<<pInfo->csCarFactory<<"%' and";
	sql<<" CarTypeInfo.CarDetailName like '%"<<pInfo->csCarDetailName<<"%' and";
	sql<<" CarPartInfo.CarTypeNum like '%"<<pInfo->csCarTypeNum<<"%' and";
	sql<<" CarPartInfo.DAENum like '%"<<pInfo->csDAENum<<"%' and";
	sql<<" CarPartInfo.MMCNum like '%"<<pInfo->csMMCNum<<"%' and";
	sql<<" CarPartInfo.ChineseName like '%"<<pInfo->csChineseName<<"%' and ";
	sql<<" CarPartInfo.PartReserve like '%"<<pInfo->strPartReserve<<"%'";

	sql<<" order by CarTypeInfo.CarDetailTypeNum,CarPartInfo.CarTypeNum,CarPartInfo.DAENum,CarPartInfo.MMCNum ";
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

	strcpy(tempCarTypeInfo.csCarDetailTypeNum,lppColumnValue[0]);
	strcpy(tempCarTypeInfo.csCarFactory,convertChar.ToGBK(lppColumnValue[1]));
	strcpy(tempCarTypeInfo.csCarDetailName,convertChar.ToGBK(lppColumnValue[2]));
	strcpy(tempCarTypeInfo.csCarTypeNum,convertChar.ToGBK(lppColumnValue[3]));
	strcpy(tempCarTypeInfo.csDAENum,lppColumnValue[4]);
	strcpy(tempCarTypeInfo.csMMCNum,lppColumnValue[5]);
	strcpy(tempCarTypeInfo.csChineseName,convertChar.ToGBK(lppColumnValue[6]));
	tempCarTypeInfo.iLevel = atoi(lppColumnValue[7]);
	tempCarTypeInfo.strPartReserve=convertChar.ToGBK(lppColumnValue[8]);

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
			strcpy(tempCarTypeInfo.csCarDetailTypeNum,lppColumnValue[i]);
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



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int	CCarTypePartsTable::ASInsertCarTypePartsInfo(const PASCarTypePartsTableInfo pInfo,std::vector<std::string>& carTypeInfoList)
{
	/*int iRes = SQLITE_OK;
	sqlstring sql;

	iRes = m_pDbBase->m_dbOp.begin_trans();
	if (SQLITE_OK == iRes)
	{
		for (int i=0;i<carTypeInfoList.size();++i)
		{
			sql.str("");

			sql<<"insert into ASCarTypePartsInfo values('";
			sql<<carTypeInfoList[i]<<"','";
			sql<<pInfo->csCarTypeNum<<"','";
			sql<<pInfo->csPartNum<<"');";

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

	return iRes;*/

	int iRes = SQLITE_OK;
	sqlstring sql;

	for (int i=0;i<carTypeInfoList.size();++i)
	{
		sql.str("");

		sql<<"insert into ASCarTypePartsInfo values('";
		sql<<carTypeInfoList[i]<<"','";
		sql<<pInfo->csCarTypeNum<<"','";
		sql<<pInfo->csPartNum<<"');";

		iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(),NULL,NULL,NULL);
	}
	
	return iRes;
}

int	CCarTypePartsTable::ASUpdateCarTypePartsInfo(const PASCarTypePartsTableInfo pInfo,std::vector<std::string>& carTypeInfoList)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	iRes = m_pDbBase->m_dbOp.begin_trans();
	if (SQLITE_OK == iRes)
	{
		sql <<"delete from ASCarTypePartsInfo where ";
		sql <<"CarTypeNum='"<<pInfo->csCarTypeNum<<"' and PartNum='"<<pInfo->csPartNum<<"';";
		iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(),NULL,NULL,NULL);

		if (SQLITE_OK == iRes)
		{
			for (int i=0;i<carTypeInfoList.size();++i)
			{
				sql.str("");

				sql<<"insert into ASCarTypePartsInfo values('";
				sql<<carTypeInfoList[i]<<"','";
				sql<<pInfo->csCarTypeNum<<"','";
				sql<<pInfo->csPartNum<<"');";

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

int CCarTypePartsTable::ASGetCarTypePartsSuppInfoEx(const PASCarTypePartsTableInfo pInfo,std::vector<ASCarTypeTableInfo>& carTypeInfoList)
{
	int iRes = SQLITE_OK;
	sqlstring sql;
	sql<<"SELECT ASCarTypeInfo.*  FROM ASCarTypeInfo,ASCarTypePartsInfo ON ASCarTypeInfo.CarDetailTypeNum=ASCarTypePartsInfo.CarDetailTypeNumber";
	sql<<" where ASCarTypePartsInfo.CarTypeNum='"<<pInfo->csCarTypeNum<<"' and ASCarTypePartsInfo.PartNum='"<<pInfo->csPartNum<<"' order by ASCarTypeInfo.CarDetailTypeNum;";

	iRes =  m_pDbBase->m_dbOp.execute(sql.str().c_str(),CCarTypePartsTable::ASGetCarTypeDataHandle,&carTypeInfoList,NULL);

	return iRes;
}

int CCarTypePartsTable::ASGetCarTypePartsSuppInfo(const PASCarTypePartsTableInfo pInfo,std::vector<ASCarTypeTableInfo>& carTypeInfoList)
{
	int iRes = SQLITE_OK;
	sqlstring sql;
	sql<<"SELECT ASCarTypeInfo.*,TempTable.CarDetailTypeNumber  FROM ASCarTypeInfo LEFT OUTER JOIN (select  CarDetailTypeNumber from ASCarTypePartsInfo where CarTypeNum='"<<pInfo->csCarTypeNum<<"' and PartNum='"<<pInfo->csPartNum;
	sql<< "') TempTable ON ASCarTypeInfo.CarDetailTypeNum=TempTable.CarDetailTypeNumber  order by ASCarTypeInfo.CarDetailTypeNum;";

	iRes =  m_pDbBase->m_dbOp.execute(sql.str().c_str(),CCarTypePartsTable::ASGetCarTypeDataHandle,&carTypeInfoList,NULL);

	return iRes;
}

int CCarTypePartsTable::ASGetCarTypePartsAllInfo(std::vector<ASCarTypeTableInfo>& carTypeInfoList)
{
	int iRes = SQLITE_OK;
	sqlstring sql;
	sql<<"SELECT * FROM ASCarTypeInfo  order by CarDetailTypeNum;";

	iRes =  m_pDbBase->m_dbOp.execute(sql.str().c_str(),CCarTypePartsTable::ASGetCarTypeDataHandle,&carTypeInfoList,NULL);

	return iRes;
}

int CCarTypePartsTable::ASGetCarTypePartsCount(const PASSearchCarTypePartsInfo pInfo,int* pTotalCount)
{
	sqlstring sql;

	sql<<"SELECT COUNT(*)  FROM ASCarTypeInfo,ASCarPartInfo,ASCarTypePartsInfo \
		 where ASCarTypeInfo.CarDetailTypeNum=ASCarTypePartsInfo.CarDetailTypeNumber and ASCarTypePartsInfo.CarTypeNum=ASCarPartInfo.CarTypeNum and ASCarTypePartsInfo.PartNum=ASCarPartInfo.PartNum and ";
	sql<<" ASCarTypeInfo.CarDetailTypeNum like '%"<<pInfo->csCarDetailTypeNum<<"%' and ";
	sql<<" ASCarTypeInfo.CarFactory like '%"<<pInfo->csCarFactory<<"%' and";
	sql<<" ASCarTypeInfo.CarType like '%"<<pInfo->csCarType<<"%' and";
	sql<<" ASCarTypeInfo.CarName like '%"<<pInfo->csCarName<<"%' and"; 
	sql<<" ASCarPartInfo.CarTypeNum like '%"<<pInfo->csCarTypeNum<<"%' and";
	sql<<" ASCarPartInfo.PartNum like '%"<<pInfo->csPartNum<<"%' and";
	sql<<" ASCarPartInfo.WholeChinName like '%"<<pInfo->csWholeChinName<<"%' ;";
	sql<<" ASCarPartInfo.ChinName like '%"<<pInfo->csChinName<<"%' ;";
	sql<<" ASCarPartInfo.Remark like '%"<<pInfo->strRemark<<"%';";

	int iCount = GetRecordCount(sql.str().c_str());
	if (pTotalCount)
	{
		*pTotalCount = iCount;
	}

	return SQLITE_OK;
}

int CCarTypePartsTable::ASGetCarTypePartsInfo(const PASSearchCarTypePartsInfo pInfo,int iPages,int iMaxCount,std::vector<ASSearchCarTypePartsInfo>& carTypePartInfoList,bool bOrderInc/*=true*/)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	sql<<"SELECT ASCarTypeInfo.CarDetailTypeNum,ASCarTypeInfo.CarFactory,ASCarTypeInfo.CarType,ASCarTypeInfo.CarName,ASCarPartInfo.CarTypeNum,ASCarPartInfo.PartNum,ASCarPartInfo.WholeChinName,ASCarPartInfo.ItemNum,ASCarPartInfo.ChinName,ASCarPartInfo.Remark FROM ASCarTypeInfo,ASCarPartInfo,ASCarTypePartsInfo \
		where ASCarTypeInfo.CarDetailTypeNum=ASCarTypePartsInfo.CarDetailTypeNumber and ASCarTypePartsInfo.CarTypeNum=ASCarPartInfo.CarTypeNum and ASCarTypePartsInfo.PartNum=ASCarPartInfo.PartNum and";
	sql<<" ASCarTypeInfo.CarDetailTypeNum like '%"<<pInfo->csCarDetailTypeNum<<"%' and ";
	sql<<" ASCarTypeInfo.CarFactory like '%"<<pInfo->csCarFactory<<"%' and ";
	sql<<" ASCarTypeInfo.CarType like '%"<<pInfo->csCarType<<"%' and ";
	sql<<" ASCarTypeInfo.CarName like '%"<<pInfo->csCarName<<"%' and ";
	sql<<" ASCarPartInfo.CarTypeNum like '%"<<pInfo->csCarTypeNum<<"%' and";
	sql<<" ASCarPartInfo.PartNum like '%"<<pInfo->csPartNum<<"%' and ";
	sql<<" ASCarPartInfo.WholeChinName like '%"<<pInfo->csWholeChinName<<"%' and ";
	sql<<" ASCarPartInfo.ChinName like '%"<<pInfo->csChinName<<"%' and ";
	sql<<" ASCarPartInfo.Remark like '%"<<pInfo->strRemark<<"%' ";

	sql<<" order by ASCarTypeInfo.CarDetailTypeNum,ASCarPartInfo.CarTypeNum,ASCarPartInfo.PartNum ";
	if (false == bOrderInc)
		sql<<"desc ";
	sql<<"limit "<<iMaxCount<<" offset "<<iMaxCount*iPages<<";";

	iRes =  m_pDbBase->m_dbOp.execute(sql.str().c_str(),CCarTypePartsTable::ASGetCarPartsDataHandle,&carTypePartInfoList,NULL);

	return iRes;
}

int	CCarTypePartsTable::ASDeleteCarTypePartsInfo(const PASCarTypePartsTableInfo pInfo)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	sql<<"delete from ASCarTypePartsInfo where CarDetailTypeNumber='"<<pInfo->csCarDetailTypeNum<<"' and CarTypeNum='"<<pInfo->csCarTypeNum<<"' and PartNum='"<<pInfo->csPartNum<<"';";

	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}

int CCarTypePartsTable::ASGetCarPartsDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName)
{
	std::vector<ASSearchCarTypePartsInfo>* pCarTypeList = (std::vector<ASSearchCarTypePartsInfo>*)lpPara;
	ASSearchCarTypePartsInfo tempCarTypeInfo;

	CConvertChar convertChar;

	strcpy(tempCarTypeInfo.csCarDetailTypeNum,lppColumnValue[0]);
	strcpy(tempCarTypeInfo.csCarFactory,convertChar.ToGBK(lppColumnValue[1]));
	strcpy(tempCarTypeInfo.csCarType,convertChar.ToGBK(lppColumnValue[2]));
	strcpy(tempCarTypeInfo.csCarName,convertChar.ToGBK(lppColumnValue[3]));
	strcpy(tempCarTypeInfo.csCarTypeNum,convertChar.ToGBK(lppColumnValue[4]));
	strcpy(tempCarTypeInfo.csPartNum,lppColumnValue[5]);
	strcpy(tempCarTypeInfo.csWholeChinName,convertChar.ToGBK(lppColumnValue[6]));
	strcpy(tempCarTypeInfo.csItemNum,lppColumnValue[7]);
	strcpy(tempCarTypeInfo.csChinName,convertChar.ToGBK(lppColumnValue[8]));
	tempCarTypeInfo.strRemark=convertChar.ToGBK(lppColumnValue[9]);

	pCarTypeList->push_back(tempCarTypeInfo);

	return SQLITE_OK;
}

int CCarTypePartsTable::ASGetCarTypeDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName)
{
	std::vector<ASCarTypeTableInfo>* pCarTypeList = (std::vector<ASCarTypeTableInfo>*)lpPara;
	ASCarTypeTableInfo tempCarTypeInfo;

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
			strcpy(tempCarTypeInfo.csCarDetailTypeNum,lppColumnValue[i]);
			continue;
		}

		if (0== strcmp(lppColumnName[i],"CustomerCode"))
		{
			strcpy(tempCarTypeInfo.csCustomerCode,lppColumnValue[i]);
			continue;
		}

		if (0== strcmp(lppColumnName[i],"CarFactory"))
		{
			strcpy(tempCarTypeInfo.csCarFactory,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"CarType"))
		{
			strcpy(tempCarTypeInfo.csCarType,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"CarName"))
		{
			strcpy(tempCarTypeInfo.csCarName,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"CarPattern"))
		{
			strcpy(tempCarTypeInfo.csCarPattern,convertChar.ToGBK(lppColumnValue[i]));
			continue;
		}

		if (0== strcmp(lppColumnName[i],"EnginePattern"))
		{
			strcpy(tempCarTypeInfo.csEnginePattern,lppColumnValue[i]);
			continue;
		}

		if (0== strcmp(lppColumnName[i],"MarkModel"))
		{
			strcpy(tempCarTypeInfo.csMarkModel,lppColumnValue[i]);
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
