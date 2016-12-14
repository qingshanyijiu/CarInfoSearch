#include "stdafx.h"
#include "CarTypeTable.h"


CCarTypeTable::CCarTypeTable(CDbBase* pBase)
	:CTableOperateBase(pBase)
{
}


CCarTypeTable::~CCarTypeTable(void)
{
}


int CCarTypeTable::InitTable()
{
	int iRes = SQLITE_OK;

	iRes = m_pDbBase->m_dbOp.get_table("CarTypeInfo");
	if (SQLITE_OK != iRes)
	{
		const char* lpTableInfoSql = "CREATE TABLE CarTypeInfo (CarTypeNum TEXT,CarDetailTypeNum TEXT PRIMARY KEY NOT NULL,CarFactory TEXT, CarStatus TEXT, CarDetailName TEXT,CarNotes TEXT,CarReserve TEXT);";
		iRes = m_pDbBase->m_dbOp.execute_dml(lpTableInfoSql);
	}

	iRes = m_pDbBase->m_dbOp.get_table("ASCarTypeInfo");
	if (SQLITE_OK != iRes)
	{
		const char* lpTableInfoSql = "CREATE TABLE ASCarTypeInfo (CarTypeNum TEXT,CarDetailTypeNum TEXT PRIMARY KEY NOT NULL,CustomerCode TEXT,CarFactory TEXT,CarType TEXT,CarName TEXT,CarPattern TEXT,EnginePattern TEXT,MarkMode TEXT,CarNotes TEXT,CarReserve TEXT);";
		iRes = m_pDbBase->m_dbOp.execute_dml(lpTableInfoSql);
	}

	return iRes;
}

int	CCarTypeTable::InsertCarTypeInfo(PCarTypeTableInfo	pInfo)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	sql<<"insert into CarTypeInfo values ('";
	sql<<pInfo->csCarTypeNum<<"','";
	sql<<pInfo->csCarDetailTypeNum<<"','";
	sql<<pInfo->csCarFactory<<"','";
	sql<<pInfo->csCarStatus<<"','";
	sql<<pInfo->csCarDetailName<<"','";
	sql<<pInfo->strCarNotes<<"','";
	sql<<pInfo->strCarReserve<<"');";
	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}

int	CCarTypeTable::UpdateCarTypeInfo(PCarTypeTableInfo	pInfo)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	sql<<"update CarTypeInfo set ";
	sql<<"CarTypeNum='"<<pInfo->csCarTypeNum<<"',";
	sql<<"CarFactory='"<<pInfo->csCarFactory<<"',";
	sql<<"CarStatus='"<<pInfo->csCarStatus<<"',";
	sql<<"CarDetailName='"<<pInfo->csCarDetailName<<"',";
	sql<<"CarNotes='"<<pInfo->strCarNotes<<"',";
	sql<<"CarReserve='"<<pInfo->strCarReserve<<"'";
	sql<<" where CarDetailTypeNum='"<<pInfo->csCarDetailTypeNum<<"';";
	
	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}

int CCarTypeTable::GetCarTypeCount(const PCarTypeTableInfo pInfo,int* pTotalCount)
{
	sqlstring sql;
	sql<<"select count(*) from CarTypeInfo where ";
	sql<<" CarTypeNum like '%"<<pInfo->csCarTypeNum<<"%' and ";
	sql<<" CarDetailTypeNum like '%"<<pInfo->csCarDetailTypeNum<<"%' and ";
	sql<<" CarFactory like '%"<<pInfo->csCarFactory<<"%' and ";
	sql<<" CarDetailName like '%"<<pInfo->csCarDetailName<<"%' and ";
	sql<<" CarNotes like '%"<<pInfo->strCarNotes.c_str()<<"%';";

	int iCount = GetRecordCount(sql.str().c_str());
	if (pTotalCount)
	{
		*pTotalCount = iCount;
	}

	return SQLITE_OK;
}

int CCarTypeTable::GetCarTypeInfo(const PCarTypeTableInfo pInfo,int iPages,int iMaxCount,std::vector<CarTypeTableInfo>& carTypeInfoList,bool bOrderInc/*=true*/)
{
	sqlstring sql;
	sql<<"select * from CarTypeInfo where ";
	sql<<" CarTypeNum like '%"<<pInfo->csCarTypeNum<<"%' and ";
	sql<<" CarDetailTypeNum like '%"<<pInfo->csCarDetailTypeNum<<"%' and ";
	sql<<" CarFactory like '%"<<pInfo->csCarFactory<<"%' and ";
	sql<<" CarDetailName like '%"<<pInfo->csCarDetailName<<"%' and ";
	sql<<" CarNotes like '%"<<pInfo->strCarNotes.c_str()<<"%' ";

	sql<<" order by CarTypeNum,CarDetailTypeNum ";
	if (false == bOrderInc)
		sql<<"desc ";
	sql<<"limit "<<iMaxCount<<" offset "<<iMaxCount*iPages<<";";

	return GetCarTypeData(sql.str().c_str(),carTypeInfoList);
}

int CCarTypeTable::GetCarTypeData(const char* lpSql,std::vector<CarTypeTableInfo>& carTypeInfoList)
{
	return m_pDbBase->m_dbOp.execute(lpSql,CCarTypeTable::GetCarTypeDataHandle,&carTypeInfoList,NULL);
}

int CCarTypeTable::GetCarTypeDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName)
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

		if (0== strcmp(lppColumnName[i],"CarReserve"))
		{
			tempCarTypeInfo.strCarReserve = convertChar.ToGBK(lppColumnValue[i]);
		}
	}

	pCarTypeList->push_back(tempCarTypeInfo);

	return SQLITE_OK;
}

int	CCarTypeTable::DeleteCarTypeInfo(const char* lpTypeNumer)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	sql<<"delete from CarTypeInfo where CarDetailTypeNum='";
	sql<<lpTypeNumer<<"';";

	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}

////////////////////////////////////////////////////////////////////////////////////////////


int	CCarTypeTable::ASInsertCarTypeInfo(PASCarTypeTableInfo	pInfo)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	sql<<"insert into ASCarTypeInfo values ('";
	sql<<pInfo->csCarTypeNum<<"','";
	sql<<pInfo->csCarDetailTypeNum<<"','";
	sql<<pInfo->csCustomerCode<<"','";
	sql<<pInfo->csCarFactory<<"','";
	sql<<pInfo->csCarType<<"','";
	sql<<pInfo->csCarName<<"','";
	sql<<pInfo->csCarPattern<<"','";
	sql<<pInfo->csEnginePattern<<"','";
	sql<<pInfo->csMarkModel<<"','";
	sql<<pInfo->strCarNotes<<"','";
	sql<<pInfo->strCarReserve<<"');";
	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}

int	CCarTypeTable::ASUpdateCarTypeInfo(PASCarTypeTableInfo	pInfo)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	sql<<"update ASCarTypeInfo set ";
	sql<<"CarTypeNum='"<<pInfo->csCarTypeNum<<"',";
	sql<<"CustomerCode='"<<pInfo->csCustomerCode<<"',";
	sql<<"CarFactory='"<<pInfo->csCarFactory<<"',";
	sql<<"CarType='"<<pInfo->csCarType<<"',";
	sql<<"CarName='"<<pInfo->csCarName<<"',";
	sql<<"CarPattern='"<<pInfo->csCarPattern<<"',";
	sql<<"EnginePattern='"<<pInfo->csEnginePattern<<"',";
	sql<<"MarkMode='"<<pInfo->csMarkModel<<"',";
	sql<<"CarNotes='"<<pInfo->strCarNotes<<"',";
	sql<<"CarReserve='"<<pInfo->strCarReserve<<"'";
	sql<<" where CarDetailTypeNum='"<<pInfo->csCarDetailTypeNum<<"';";

	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}

int CCarTypeTable::ASGetCarTypeCount(const PASCarTypeTableInfo pInfo,int* pTotalCount)
{
	sqlstring sql;
	sql<<"select count(*) from ASCarTypeInfo where ";
	sql<<" CarTypeNum like '%"<<pInfo->csCarTypeNum<<"%' and ";
	sql<<" CarDetailTypeNum like '%"<<pInfo->csCarDetailTypeNum<<"%' and ";
	sql<<" CarFactory like '%"<<pInfo->csCarFactory<<"%' and ";
	sql<<" CarName like '%"<<pInfo->csCarName<<"%' and ";
	sql<<" CarType like '%"<<pInfo->csCarType<<"%' and ";
	sql<<" CarNotes like '%"<<pInfo->strCarNotes.c_str()<<"%';";

	int iCount = GetRecordCount(sql.str().c_str());
	if (pTotalCount)
	{
		*pTotalCount = iCount;
	}

	return SQLITE_OK;
}

int CCarTypeTable::ASGetCarTypeInfo(const PASCarTypeTableInfo pInfo,int iPages,int iMaxCount,std::vector<ASCarTypeTableInfo>& carTypeInfoList,bool bOrderInc/*=true*/)
{
	sqlstring sql;
	sql<<"select * from ASCarTypeInfo where ";
	sql<<" CarTypeNum like '%"<<pInfo->csCarTypeNum<<"%' and ";
	sql<<" CarDetailTypeNum like '%"<<pInfo->csCarDetailTypeNum<<"%' and ";
	sql<<" CarFactory like '%"<<pInfo->csCarFactory<<"%' and ";
	sql<<" CarName like '%"<<pInfo->csCarName<<"%' and ";
	sql<<" CarType like '%"<<pInfo->csCarType<<"%' and ";
	sql<<" CarNotes like '%"<<pInfo->strCarNotes.c_str()<<"%' ";

	sql<<" order by CarTypeNum,CarDetailTypeNum ";
	if (false == bOrderInc)
		sql<<"desc ";
	sql<<"limit "<<iMaxCount<<" offset "<<iMaxCount*iPages<<";";

	return m_pDbBase->m_dbOp.execute(sql.str().c_str(),CCarTypeTable::ASGetCarTypeDataHandle,&carTypeInfoList,NULL);
}


int CCarTypeTable::ASGetCarTypeDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName)
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

		if (0== strcmp(lppColumnName[i],"MarkMode"))
		{
			strcpy(tempCarTypeInfo.csMarkModel,lppColumnValue[i]);
			continue;
		}


		if (0== strcmp(lppColumnName[i],"CarNotes"))
		{
			tempCarTypeInfo.strCarNotes = convertChar.ToGBK(lppColumnValue[i]);
		}

		if (0== strcmp(lppColumnName[i],"CarReserve"))
		{
			tempCarTypeInfo.strCarReserve = convertChar.ToGBK(lppColumnValue[i]);
		}
	}

	pCarTypeList->push_back(tempCarTypeInfo);

	return SQLITE_OK;
}

int	CCarTypeTable::ASDeleteCarTypeInfo(const char* lpTypeNumer)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	sql<<"delete from ASCarTypeInfo where CarDetailTypeNum='";
	sql<<lpTypeNumer<<"';";

	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}
