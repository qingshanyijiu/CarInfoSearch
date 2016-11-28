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

protected:
	int GetCarTypeData(const char* lpSql,std::vector<CarTypeTableInfo>& carTypeInfoList);

protected:
	static int GetCarTypeDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName);
};

