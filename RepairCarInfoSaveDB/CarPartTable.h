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

	int	ASInsertCarPartInfo(const PASCarPartTableInfo	pInfo);
	int	ASUpdateCarPartInfo(const PASCarPartTableInfo	pInfo);
	int ASGetCarPartCount(const PASCarPartTableInfo pInfo,int* pTotalCount);
	int ASGetCarPartInfo(const PASCarPartTableInfo pInfo,int iPages,int iMaxCount,std::vector<ASCarPartTableInfo>& carPartInfoList,bool bOrderInc);
	int	ASDeleteCarPartInfo(const PASCarPartTableInfo	pInfo);

protected:
	int GetCarPartData(const char* lpSql,std::vector<CarPartTableInfo>& carPartInfoList);

protected:
	static int GetCarPartInfoDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName);
	static int ASGetCarPartInfoDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName);
};

