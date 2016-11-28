#pragma once

#include "TableOperateBase.h"
#include "SingletonInstance.h"

class CCarTypePartsTable
	:public	CTableOperateBase,public CSingletonInstance<CCarTypePartsTable>
{
public:
	CCarTypePartsTable(CDbBase* pBase);
	~CCarTypePartsTable(void);

	int InitTable();
	int	InsertCarTypePartsInfo(const PCarTypePartsTableInfo pInfo,std::vector<std::string>& carTypeInfoList);
	int	UpdateCarTypePartsInfo(const PCarTypePartsTableInfo pInfo,std::vector<std::string>& carTypeInfoList);
	int GetCarTypePartsAllInfo(std::vector<CarTypeTableInfo>& carTypeInfoList);
	int GetCarTypePartsSuppInfo(const PCarTypePartsTableInfo pInfo,std::vector<CarTypeTableInfo>& carTypeInfoList);
	int GetCarTypePartsSuppInfoEx(const PCarTypePartsTableInfo pInfo,std::vector<CarTypeTableInfo>& carTypeInfoList);
	int GetCarTypePartsCount(const PSearchCarTypePartsInfo pInfo,int* pTotalCount);
	int GetCarTypePartsInfo(const PSearchCarTypePartsInfo pInfo,int iPages,int iMaxCount,std::vector<SearchCarTypePartsInfo>& carTypePartInfoList,bool bOrderInc=true);
	int	DeleteCarTypePartsInfo(const PCarTypePartsTableInfo pInfo);

private:
	static int GetCarTypeDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName);
	static int GetCarPartsDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName);
};

