// RepairCarInfoSaveDB.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "RepairCarInfoSaveDB.h"
#include "ASInfoInterface.h"
#include "SingletonInstance.h"
#include "RepairCarInfoSaveImpl.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

int REPAIRCARINFOSAVEDB_API OpenDb(const char* lpFileName)
{
	return CCarInfoSaveImpl::GetInstance()->OpenDb(lpFileName);
}

int REPAIRCARINFOSAVEDB_API CloseDb()
{
	return CCarInfoSaveImpl::GetInstance()->CloseDb();
}

int	REPAIRCARINFOSAVEDB_API InsertCarTypeInfo(const PCarTypeTableInfo	pInfo)
{
	return CCarInfoSaveImpl::GetInstance()->InsertCarTypeInfo(pInfo);
}

int	REPAIRCARINFOSAVEDB_API UpdateCarTypeInfo(const PCarTypeTableInfo	pInfo)
{
	return CCarInfoSaveImpl::GetInstance()->UpdateCarTypeInfo(pInfo);
}

int REPAIRCARINFOSAVEDB_API GetCarTypeCount(const PCarTypeTableInfo pInfo,int* pTotalCount)
{
	return CCarInfoSaveImpl::GetInstance()->GetCarTypeCount(pInfo,pTotalCount);
}

int REPAIRCARINFOSAVEDB_API GetCarTypeInfo(const PCarTypeTableInfo pInfo,int iPages,int iMaxCount,std::vector<CarTypeTableInfo>& carTypeInfoList,bool bOrderInc/*=true*/)
{
	return CCarInfoSaveImpl::GetInstance()->GetCarTypeInfo(pInfo,iPages,iMaxCount,carTypeInfoList,bOrderInc);
}

int	REPAIRCARINFOSAVEDB_API DeleteCarTypeInfo(const char* lpTypeNumer)
{
	return CCarInfoSaveImpl::GetInstance()->DeleteCarTypeInfo(lpTypeNumer);
}

int	REPAIRCARINFOSAVEDB_API InsertCarPartInfo(const PCarPartTableInfo	pInfo)
{
	return CCarInfoSaveImpl::GetInstance()->InsertCarPartInfo(pInfo);
}

int	REPAIRCARINFOSAVEDB_API UpdateCarPartInfo(const PCarPartTableInfo	pInfo)
{
	return CCarInfoSaveImpl::GetInstance()->UpdateCarPartInfo(pInfo);
}

int REPAIRCARINFOSAVEDB_API GetCarPartCount(const PCarPartTableInfo pInfo,int* pTotalCount)
{
	return CCarInfoSaveImpl::GetInstance()->GetCarPartCount(pInfo,pTotalCount);
}

int REPAIRCARINFOSAVEDB_API GetCarPartInfo(const PCarPartTableInfo pInfo,int iPages,int iMaxCount,std::vector<CarPartTableInfo>& carPartInfoList,bool bOrderInc/*=true*/)
{
	return CCarInfoSaveImpl::GetInstance()->GetCarPartInfo(pInfo,iPages,iMaxCount,carPartInfoList,bOrderInc);
}

int	REPAIRCARINFOSAVEDB_API DeleteCarPartInfo(const PCarPartTableInfo	pInfo)
{
	return CCarInfoSaveImpl::GetInstance()->DeleteCarPartInfo(pInfo);
}

int	REPAIRCARINFOSAVEDB_API InsertCarTypePartsInfo(const PCarTypePartsTableInfo pInfo,std::vector<std::string>& carTypeInfoList)
{
	return CCarInfoSaveImpl::GetInstance()->InsertCarTypePartsInfo(pInfo,carTypeInfoList);
}

int	REPAIRCARINFOSAVEDB_API UpdateCarTypePartsInfo(const PCarTypePartsTableInfo pInfo,std::vector<std::string>& carTypeInfoList)
{
	return CCarInfoSaveImpl::GetInstance()->UpdateCarTypePartsInfo(pInfo,carTypeInfoList);
}

int REPAIRCARINFOSAVEDB_API GetCarTypePartsAllInfo(std::vector<CarTypeTableInfo>& carTypeInfoList)
{
	return CCarInfoSaveImpl::GetInstance()->GetCarTypePartsAllInfo(carTypeInfoList);
}

int REPAIRCARINFOSAVEDB_API GetCarTypePartsSuppInfo(const PCarTypePartsTableInfo pInfo,std::vector<CarTypeTableInfo>& carTypeInfoList)
{
	return CCarInfoSaveImpl::GetInstance()->GetCarTypePartsSuppInfo(pInfo,carTypeInfoList);
}

int REPAIRCARINFOSAVEDB_API GetCarTypePartsSuppInfoEx(const PCarTypePartsTableInfo pInfo,std::vector<CarTypeTableInfo>& carTypeInfoList)
{
	return CCarInfoSaveImpl::GetInstance()->GetCarTypePartsSuppInfoEx(pInfo,carTypeInfoList);
}

int REPAIRCARINFOSAVEDB_API GetCarTypePartsCount(const PSearchCarTypePartsInfo pInfo,int* pTotalCount)
{
	return CCarInfoSaveImpl::GetInstance()->GetCarTypePartsCount(pInfo,pTotalCount);
}

int REPAIRCARINFOSAVEDB_API GetCarTypePartsInfo(const PSearchCarTypePartsInfo pInfo,int iPages,int iMaxCount,std::vector<SearchCarTypePartsInfo>& carTypePartInfoList,bool bOrderInc/*=true*/)
{
	return CCarInfoSaveImpl::GetInstance()->GetCarTypePartsInfo(pInfo,iPages,iMaxCount,carTypePartInfoList,bOrderInc);
}

int	REPAIRCARINFOSAVEDB_API DeleteCarTypePartsInfo(const PCarTypePartsTableInfo pInfo)
{
	return CCarInfoSaveImpl::GetInstance()->DeleteCarTypePartsInfo(pInfo);
}

int REPAIRCARINFOSAVEDB_API InsertUserInfo(PUserPwdInfo pInfo)
{
	return CCarInfoSaveImpl::GetInstance()->InsertUserInfo(pInfo);
}

int REPAIRCARINFOSAVEDB_API UpdateUserInfo(PUserPwdInfo pInfo)
{
	return CCarInfoSaveImpl::GetInstance()->UpdateUserInfo(pInfo);
}

int REPAIRCARINFOSAVEDB_API QueryUserInfo(PUserPwdInfo pInfo)
{
	return CCarInfoSaveImpl::GetInstance()->QueryUserInfo(pInfo);
}

int REPAIRCARINFOSAVEDB_API DeleteUserInfo(const char* lpUserName)
{
	return CCarInfoSaveImpl::GetInstance()->DeleteUserInfo(lpUserName);
}

int REPAIRCARINFOSAVEDB_API InsertCarFileData(const PCarFileData pInfo)
{
	return CCarInfoSaveImpl::GetInstance()->InsertCarFileData(pInfo);
}

int REPAIRCARINFOSAVEDB_API UpdateCarFileData(const PCarFileData pInfo)
{
	return CCarInfoSaveImpl::GetInstance()->UpdateCarFileData(pInfo);
}

int REPAIRCARINFOSAVEDB_API GetCarFileDataCount(const PCarFileData pInfo,int* pTotalCount)
{
	return CCarInfoSaveImpl::GetInstance()->GetCarFileDataCount(pInfo,pTotalCount);
}

int REPAIRCARINFOSAVEDB_API GetCarFileData(const PCarFileData pInfo,int iPages,int iMaxCount,std::vector<CarFileData>& carFileDataList,bool bOrderInc/*=true*/)
{
	return CCarInfoSaveImpl::GetInstance()->GetCarFileData(pInfo,iPages,iMaxCount,carFileDataList,bOrderInc);
}

int	REPAIRCARINFOSAVEDB_API DeleteCarFileData(const char* lpFileName)
{
	return CCarInfoSaveImpl::GetInstance()->DeleteCarFileData(lpFileName);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int	REPAIRCARINFOSAVEDB_API ASInsertCarTypeInfo(const PASCarTypeTableInfo	pInfo)
{
	return CCarInfoSaveImpl::GetInstance()->ASInsertCarTypeInfo(pInfo);
}

int	REPAIRCARINFOSAVEDB_API ASUpdateCarTypeInfo(const PASCarTypeTableInfo	pInfo)
{
	return CCarInfoSaveImpl::GetInstance()->ASUpdateCarTypeInfo(pInfo);
}

int REPAIRCARINFOSAVEDB_API ASGetCarTypeCount(const PASCarTypeTableInfo pInfo,int* pTotalCount)
{
	return CCarInfoSaveImpl::GetInstance()->ASGetCarTypeCount(pInfo,pTotalCount);
}

int REPAIRCARINFOSAVEDB_API ASGetCarTypeInfo(const PASCarTypeTableInfo pInfo,int iPages,int iMaxCount,std::vector<ASCarTypeTableInfo>& carTypeInfoList,bool bOrderInc/*=true*/)
{
	return CCarInfoSaveImpl::GetInstance()->ASGetCarTypeInfo(pInfo,iPages,iMaxCount,carTypeInfoList,bOrderInc);
}

int	REPAIRCARINFOSAVEDB_API ASDeleteCarTypeInfo(const char* lpTypeNumer)
{
	return CCarInfoSaveImpl::GetInstance()->ASDeleteCarTypeInfo(lpTypeNumer);
}

int	REPAIRCARINFOSAVEDB_API ASInsertCarPartInfo(const PASCarPartTableInfo	pInfo)
{
	return CCarInfoSaveImpl::GetInstance()->ASInsertCarPartInfo(pInfo);
}

int	REPAIRCARINFOSAVEDB_API ASUpdateCarPartInfo(const PASCarPartTableInfo	pInfo)
{
	return CCarInfoSaveImpl::GetInstance()->ASUpdateCarPartInfo(pInfo);
}

int REPAIRCARINFOSAVEDB_API ASGetCarPartCount(const PASCarPartTableInfo pInfo,int* pTotalCount)
{
	return CCarInfoSaveImpl::GetInstance()->ASGetCarPartCount(pInfo,pTotalCount);
}

int REPAIRCARINFOSAVEDB_API ASGetCarPartInfo(const PASCarPartTableInfo pInfo,int iPages,int iMaxCount,std::vector<ASCarPartTableInfo>& carPartInfoList,bool bOrderInc)
{
	return CCarInfoSaveImpl::GetInstance()->ASGetCarPartInfo(pInfo,iPages,iMaxCount,carPartInfoList,bOrderInc);
}

int	REPAIRCARINFOSAVEDB_API ASDeleteCarPartInfo(const PASCarPartTableInfo	pInfo)
{
	return CCarInfoSaveImpl::GetInstance()->ASDeleteCarPartInfo(pInfo);
}

int	REPAIRCARINFOSAVEDB_API ASInsertCarTypePartsInfo(const PASCarTypePartsTableInfo pInfo,std::vector<std::string>& carTypeInfoList)
{
	return CCarInfoSaveImpl::GetInstance()->ASInsertCarTypePartsInfo(pInfo,carTypeInfoList);
}

int	REPAIRCARINFOSAVEDB_API ASUpdateCarTypePartsInfo(const PASCarTypePartsTableInfo pInfo,std::vector<std::string>& carTypeInfoList)
{
	return CCarInfoSaveImpl::GetInstance()->ASUpdateCarTypePartsInfo(pInfo,carTypeInfoList);
}

int REPAIRCARINFOSAVEDB_API ASGetCarTypePartsAllInfo(std::vector<ASCarTypeTableInfo>& carTypeInfoList)
{
	return CCarInfoSaveImpl::GetInstance()->ASGetCarTypePartsAllInfo(carTypeInfoList);
}

int REPAIRCARINFOSAVEDB_API ASGetCarTypePartsSuppInfo(const PASCarTypePartsTableInfo pInfo,std::vector<ASCarTypeTableInfo>& carTypeInfoList)
{
	return CCarInfoSaveImpl::GetInstance()->ASGetCarTypePartsSuppInfo(pInfo,carTypeInfoList);
}

int REPAIRCARINFOSAVEDB_API ASGetCarTypePartsSuppInfoEx(const PASCarTypePartsTableInfo pInfo,std::vector<ASCarTypeTableInfo>& carTypeInfoList)
{
	return CCarInfoSaveImpl::GetInstance()->ASGetCarTypePartsSuppInfoEx(pInfo,carTypeInfoList);
}

int REPAIRCARINFOSAVEDB_API ASGetCarTypePartsCount(const PASSearchCarTypePartsInfo pInfo,int* pTotalCount)
{
	return CCarInfoSaveImpl::GetInstance()->ASGetCarTypePartsCount(pInfo,pTotalCount);
}

int REPAIRCARINFOSAVEDB_API ASGetCarTypePartsInfo(const PASSearchCarTypePartsInfo pInfo,int iPages,int iMaxCount,std::vector<ASSearchCarTypePartsInfo>& carTypePartInfoList,bool bOrderInc)
{
	return CCarInfoSaveImpl::GetInstance()->ASGetCarTypePartsInfo(pInfo,iPages,iMaxCount,carTypePartInfoList,bOrderInc);
}

int	REPAIRCARINFOSAVEDB_API ASDeleteCarTypePartsInfo(const PASCarTypePartsTableInfo pInfo)
{
	return CCarInfoSaveImpl::GetInstance()->ASDeleteCarTypePartsInfo(pInfo);
}