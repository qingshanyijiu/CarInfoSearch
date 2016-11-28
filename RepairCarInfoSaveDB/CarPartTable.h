#pragma once

#include "TableOperateBase.h"
#include "SingletonInstance.h"

class CCarPartTable	
	:public	CTableOperateBase,public CSingletonInstance<CCarPartTable>
{
public:
	CCarPartTable(CDbBase* pBase);
	~CCarPartTable(void);

	int InitTable();
	int	InsertCarPartInfo(const PCarPartTableInfo	pInfo);
	int	UpdateCarPartInfo(const PCarPartTableInfo	pInfo);
	int GetCarPartCount(const PCarPartTableInfo pInfo,int* pTotalCount);
	int GetCarPartInfo(const PCarPartTableInfo pInfo,int iPages,int iMaxCount,std::vector<CarPartTableInfo>& carPartInfoList,bool bOrderInc=true);
	int	DeleteCarPartInfo(const PCarPartTableInfo	pInfo);

protected:
	int GetCarPartData(const char* lpSql,std::vector<CarPartTableInfo>& carPartInfoList);

protected:
	static int GetCarPartInfoDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName);

};

