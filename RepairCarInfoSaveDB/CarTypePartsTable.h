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

	int	ASInsertCarTypePartsInfo(const PASCarTypePartsTableInfo pInfo,std::vector<std::string>& carTypeInfoList);
	int	ASUpdateCarTypePartsInfo(const PASCarTypePartsTableInfo pInfo,std::vector<std::string>& carTypeInfoList);
	int ASGetCarTypePartsAllInfo(std::vector<ASCarTypeTableInfo>& carTypeInfoList);
	int ASGetCarTypePartsSuppInfo(const PASCarTypePartsTableInfo pInfo,std::vector<ASCarTypeTableInfo>& carTypeInfoList);
	int ASGetCarTypePartsSuppInfoEx(const PASCarTypePartsTableInfo pInfo,std::vector<ASCarTypeTableInfo>& carTypeInfoList);
	int ASGetCarTypePartsCount(const PASSearchCarTypePartsInfo pInfo,int* pTotalCount);
	int ASGetCarTypePartsInfo(const PASSearchCarTypePartsInfo pInfo,int iPages,int iMaxCount,std::vector<ASSearchCarTypePartsInfo>& carTypePartInfoList,bool bOrderInc=true);
	int	ASDeleteCarTypePartsInfo(const PASCarTypePartsTableInfo pInfo);

private:
	static int GetCarTypeDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName);
	static int GetCarPartsDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName);

	static int ASGetCarTypeDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName);
	static int ASGetCarPartsDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName);
};

