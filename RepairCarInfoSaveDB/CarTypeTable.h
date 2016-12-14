#pragma once

#include "TableOperateBase.h"
#include "SingletonInstance.h"

class CCarTypeTable	
	:public	CTableOperateBase,public CSingletonInstance<CCarTypeTable>
{
public:
	CCarTypeTable(CDbBase* pBase);
	~CCarTypeTable(void);

	int InitTable();
	int	InsertCarTypeInfo(const PCarTypeTableInfo	pInfo);
	int	UpdateCarTypeInfo(const PCarTypeTableInfo	pInfo);
	int GetCarTypeCount(const PCarTypeTableInfo pInfo,int* pTotalCount);
	int GetCarTypeInfo(const PCarTypeTableInfo pInfo,int iPages,int iMaxCount,std::vector<CarTypeTableInfo>& carTypeInfoList,bool bOrderInc=true);
	int	DeleteCarTypeInfo(const char* lpTypeNumer);

	int	ASInsertCarTypeInfo(const PASCarTypeTableInfo	pInfo);
	int	ASUpdateCarTypeInfo(const PASCarTypeTableInfo	pInfo);
	int ASGetCarTypeCount(const PASCarTypeTableInfo pInfo,int* pTotalCount);
	int ASGetCarTypeInfo(const PASCarTypeTableInfo pInfo,int iPages,int iMaxCount,std::vector<ASCarTypeTableInfo>& carTypeInfoList,bool bOrderInc);
	int	ASDeleteCarTypeInfo(const char* lpTypeNumer);

protected:
	int GetCarTypeData(const char* lpSql,std::vector<CarTypeTableInfo>& carTypeInfoList);

protected:
	static int GetCarTypeDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName);
	static int ASGetCarTypeDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName);
};

