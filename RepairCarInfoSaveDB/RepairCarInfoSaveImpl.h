// RepairCarInfoSaveImpl.h: interface for the CRepairCarInfoSaveImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPAIRCARINFOSAVEIMPL_H__DD0623E2_56C5_4225_91C5_DDCA939648DB__INCLUDED_)
#define AFX_REPAIRCARINFOSAVEIMPL_H__DD0623E2_56C5_4225_91C5_DDCA939648DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CriticalLock.h"
#include "DbBase.h"
#include "CarTypeTable.h"
#include "CarPartTable.h"
#include "CarTypePartsTable.h"
#include "UserInfoTable.h"
#include "CarFileDataTable.h"

class CCarInfoSaveImpl  
	:public CSingletonInstance<CCarInfoSaveImpl>
{
public:
	CCarInfoSaveImpl();
	virtual ~CCarInfoSaveImpl();

	int OpenDb(const char* lpFileName);
	int CloseDb();

	int	InsertCarTypeInfo(const PCarTypeTableInfo	pInfo);
	int	UpdateCarTypeInfo(const PCarTypeTableInfo	pInfo);
	int GetCarTypeCount(const PCarTypeTableInfo pInfo,int* pTotalCount);
	int GetCarTypeInfo(const PCarTypeTableInfo pInfo,int iPages,int iMaxCount,std::vector<CarTypeTableInfo>& carTypeInfoList,bool bOrderInc=true);
	int	DeleteCarTypeInfo(const char* lpTypeNumer);

	int	InsertCarPartInfo(const PCarPartTableInfo	pInfo);
	int	UpdateCarPartInfo(const PCarPartTableInfo	pInfo);
	int GetCarPartCount(const PCarPartTableInfo pInfo,int* pTotalCount);
	int GetCarPartInfo(const PCarPartTableInfo pInfo,int iPages,int iMaxCount,std::vector<CarPartTableInfo>& carPartInfoList,bool bOrderInc=true);
	int	DeleteCarPartInfo(const PCarPartTableInfo	pInfo);

	int	InsertCarTypePartsInfo(const PCarTypePartsTableInfo pInfo,std::vector<std::string>& carTypeInfoList);
	int	UpdateCarTypePartsInfo(const PCarTypePartsTableInfo pInfo,std::vector<std::string>& carTypeInfoList);
	int GetCarTypePartsAllInfo(std::vector<CarTypeTableInfo>& carTypeInfoList);
	int GetCarTypePartsSuppInfo(const PCarTypePartsTableInfo pInfo,std::vector<CarTypeTableInfo>& carTypeInfoList);
	int GetCarTypePartsSuppInfoEx(const PCarTypePartsTableInfo pInfo,std::vector<CarTypeTableInfo>& carTypeInfoList);
	int GetCarTypePartsCount(const PSearchCarTypePartsInfo pInfo,int* pTotalCount);
	int GetCarTypePartsInfo(const PSearchCarTypePartsInfo pInfo,int iPages,int iMaxCount,std::vector<SearchCarTypePartsInfo>& carTypePartInfoList,bool bOrderInc=true);
	int	DeleteCarTypePartsInfo(const PCarTypePartsTableInfo pInfo);

	int InsertUserInfo(PUserPwdInfo pInfo);
	int UpdateUserInfo(PUserPwdInfo pInfo);
	int QueryUserInfo(PUserPwdInfo pInfo);
	int DeleteUserInfo(const char* lpUserName);

	int InsertCarFileData(const PCarFileData pInfo);
	int UpdateCarFileData(const PCarFileData pInfo);
	int GetCarFileDataCount(const PCarFileData pInfo,int* pTotalCount);
	int GetCarFileData(const PCarFileData pInfo,int iPages,int iMaxCount,std::vector<CarFileData>& carFileDataList,bool bOrderInc=true);
	int	DeleteCarFileData(const char* lpFileName);

protected:
	CDbBase*				m_pDbBase;
	CCarTypeTable*			m_pCarTypeOp;
	CCarPartTable*			m_pCarPartOp;
	CCarTypePartsTable*		m_pCarTypePartsOp;
	CUserInfoTable*			m_pUserInfoOp;
	CCarFileDataTable*		m_pCarFileOp;
	CCriticalLock			m_dbLock;
};

#endif // !defined(AFX_REPAIRCARINFOSAVEIMPL_H__DD0623E2_56C5_4225_91C5_DDCA939648DB__INCLUDED_)
