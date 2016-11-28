#pragma once

#include "TableOperateBase.h"
#include "SingletonInstance.h"

class CCarFileDataTable
	:public	CTableOperateBase,public CSingletonInstance<CCarFileDataTable>
{
public:
	CCarFileDataTable(CDbBase* pBase);
	~CCarFileDataTable(void);

	int InitTable();
	int InsertCarFileData(const PCarFileData pInfo);
	int UpdateCarFileData(const PCarFileData pInfo);
	int GetCarFileDataCount(const PCarFileData pInfo,int* pTotalCount);
	int GetCarFileData(const PCarFileData pInfo,int iPages,int iMaxCount,std::vector<CarFileData>& carFileDataList,bool bOrderInc=true);
	int	DeleteCarFileData(const char* lpFileName);


protected:
	int GetCarFileDataSql(const char* lpSql,std::vector<CarFileData>& carFileDataList);

protected:
	static int GetCarFileDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName);


};

