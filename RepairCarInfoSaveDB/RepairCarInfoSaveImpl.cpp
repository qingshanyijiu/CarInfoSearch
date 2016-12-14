// CarPartCarInfoSaveImpl.cpp: implementation of the CCarInfoSaveImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RepairCarInfoSaveImpl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCarInfoSaveImpl::CCarInfoSaveImpl()
{
	m_pDbBase			= NULL;
	m_pCarTypeOp		= NULL;
	m_pCarPartOp		= NULL;
	m_pCarTypePartsOp	= NULL;
	m_pUserInfoOp		= NULL;
	m_pCarFileOp		= NULL;
}

CCarInfoSaveImpl::~CCarInfoSaveImpl()
{

}

int CCarInfoSaveImpl::OpenDb(const char* lpFileName)
{
	CCriticalLock::CAutoLock lock(m_dbLock);
	m_pDbBase		= CDbBase::GetInstance();
	m_pCarTypeOp	= CCarTypeTable::GetInstance(m_pDbBase);
	m_pCarPartOp	= CCarPartTable::GetInstance(m_pDbBase);
	m_pCarTypePartsOp = CCarTypePartsTable::GetInstance(m_pDbBase);
	m_pUserInfoOp   = CUserInfoTable::GetInstance(m_pDbBase);
	m_pCarFileOp	= CCarFileDataTable::GetInstance(m_pDbBase);

	int iRes = m_pDbBase->OpenDb(lpFileName);
	if (SQLITE_OK == iRes)
	{
		m_pCarTypeOp->InitTable();
		m_pCarPartOp->InitTable();
		m_pCarTypePartsOp->InitTable();
		m_pUserInfoOp->InitTable();
		m_pCarFileOp->InitTable();
	}

	return iRes;
}

int CCarInfoSaveImpl::CloseDb()
{
	if (NULL == m_pDbBase)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pDbBase->CloseDb();
}

int	CCarInfoSaveImpl::InsertCarTypeInfo(PCarTypeTableInfo	pInfo)
{
	if (NULL == m_pCarTypeOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypeOp->InsertCarTypeInfo(pInfo);
}

int	CCarInfoSaveImpl::UpdateCarTypeInfo(PCarTypeTableInfo	pInfo)
{
	if (NULL == m_pCarTypeOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypeOp->UpdateCarTypeInfo(pInfo);
}

int CCarInfoSaveImpl::GetCarTypeCount(const PCarTypeTableInfo pInfo,int* pTotalCount)
{
	if (NULL == m_pCarTypeOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypeOp->GetCarTypeCount(pInfo,pTotalCount);
}

int CCarInfoSaveImpl::GetCarTypeInfo(const PCarTypeTableInfo pInfo,int iPages,int iMaxCount,std::vector<CarTypeTableInfo>& carTypeInfoList,bool bOrderInc/*=true*/)
{
	if (NULL == m_pCarTypeOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypeOp->GetCarTypeInfo(pInfo,iPages,iMaxCount,carTypeInfoList,bOrderInc);
}

int	CCarInfoSaveImpl::DeleteCarTypeInfo(const char* lpTypeNumer)
{
	if (NULL == m_pCarTypeOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypeOp->DeleteCarTypeInfo(lpTypeNumer);
}

int	CCarInfoSaveImpl::InsertCarPartInfo(PCarPartTableInfo	pInfo)
{
	if (NULL == m_pCarPartOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarPartOp->InsertCarPartInfo(pInfo);
}

int	CCarInfoSaveImpl::UpdateCarPartInfo(PCarPartTableInfo	pInfo)
{
	if (NULL == m_pCarPartOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarPartOp->UpdateCarPartInfo(pInfo);
}

int CCarInfoSaveImpl::GetCarPartCount(const PCarPartTableInfo pInfo,int* pTotalCount)
{
	if (NULL == m_pCarPartOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarPartOp->GetCarPartCount(pInfo,pTotalCount);
}

int CCarInfoSaveImpl::GetCarPartInfo(const PCarPartTableInfo pInfo,int iPages,int iMaxCount,std::vector<CarPartTableInfo>& carPartInfoList,bool bOrderInc/* =true */)
{
	if (NULL == m_pCarPartOp)
		return OPERATE_DB_ERROR;
	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarPartOp->GetCarPartInfo(pInfo,iPages,iMaxCount,carPartInfoList,bOrderInc);
}

int	CCarInfoSaveImpl::DeleteCarPartInfo(const PCarPartTableInfo	pInfo)
{
	if (NULL == m_pCarPartOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarPartOp->DeleteCarPartInfo(pInfo);
}

int	CCarInfoSaveImpl::InsertCarTypePartsInfo(const PCarTypePartsTableInfo pInfo,std::vector<std::string>& carTypeInfoList)
{
	if (NULL ==m_pCarTypePartsOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypePartsOp->InsertCarTypePartsInfo(pInfo,carTypeInfoList);
}

int	CCarInfoSaveImpl::UpdateCarTypePartsInfo(const PCarTypePartsTableInfo pInfo,std::vector<std::string>& carTypeInfoList)
{
	if (NULL ==m_pCarTypePartsOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypePartsOp->UpdateCarTypePartsInfo(pInfo,carTypeInfoList);
}

int CCarInfoSaveImpl::GetCarTypePartsAllInfo(std::vector<CarTypeTableInfo>& carTypeInfoList)
{
	if (NULL ==m_pCarTypePartsOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypePartsOp->GetCarTypePartsAllInfo(carTypeInfoList);
}

int CCarInfoSaveImpl::GetCarTypePartsSuppInfo(const PCarTypePartsTableInfo pInfo,std::vector<CarTypeTableInfo>& carTypeInfoList)
{
	if (NULL ==m_pCarTypePartsOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypePartsOp->GetCarTypePartsSuppInfo(pInfo,carTypeInfoList);
}

int CCarInfoSaveImpl::GetCarTypePartsSuppInfoEx(const PCarTypePartsTableInfo pInfo,std::vector<CarTypeTableInfo>& carTypeInfoList)
{
	if (NULL ==m_pCarTypePartsOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypePartsOp->GetCarTypePartsSuppInfoEx(pInfo,carTypeInfoList);
}

int CCarInfoSaveImpl::GetCarTypePartsCount(const PSearchCarTypePartsInfo pInfo,int* pTotalCount)
{
	if (NULL ==m_pCarTypePartsOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypePartsOp->GetCarTypePartsCount(pInfo,pTotalCount);
}

int CCarInfoSaveImpl::GetCarTypePartsInfo(const PSearchCarTypePartsInfo pInfo,int iPages,int iMaxCount,std::vector<SearchCarTypePartsInfo>& carTypePartInfoList,bool bOrderInc/*=true*/)
{
	if (NULL ==m_pCarTypePartsOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypePartsOp->GetCarTypePartsInfo(pInfo,iPages,iMaxCount,carTypePartInfoList,bOrderInc);
}

int	CCarInfoSaveImpl::DeleteCarTypePartsInfo(const PCarTypePartsTableInfo pInfo)
{
	if (NULL ==m_pCarTypePartsOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypePartsOp->DeleteCarTypePartsInfo(pInfo);
}

int CCarInfoSaveImpl::InsertUserInfo(PUserPwdInfo pInfo)
{
	if (NULL ==m_pUserInfoOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pUserInfoOp->InsertUserInfo(pInfo);
}

int CCarInfoSaveImpl::UpdateUserInfo(PUserPwdInfo pInfo)
{
	if (NULL ==m_pUserInfoOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pUserInfoOp->UpdateUserInfo(pInfo);
}

int CCarInfoSaveImpl::QueryUserInfo(PUserPwdInfo pInfo)
{
	if (NULL ==m_pUserInfoOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pUserInfoOp->QueryUserInfo(pInfo);
}

int CCarInfoSaveImpl::DeleteUserInfo(const char* lpUserName)
{
	if (NULL ==m_pUserInfoOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pUserInfoOp->DeleteUserInfo(lpUserName);
}

int CCarInfoSaveImpl::InsertCarFileData(const PCarFileData pInfo)
{
	if (NULL ==m_pCarFileOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarFileOp->InsertCarFileData(pInfo);
}

int CCarInfoSaveImpl::UpdateCarFileData(const PCarFileData pInfo)
{
	if (NULL ==m_pCarFileOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarFileOp->UpdateCarFileData(pInfo);
}

int CCarInfoSaveImpl::GetCarFileDataCount(const PCarFileData pInfo,int* pTotalCount)
{
	if (NULL ==m_pCarFileOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarFileOp->GetCarFileDataCount(pInfo,pTotalCount);
}

int CCarInfoSaveImpl::GetCarFileData(const PCarFileData pInfo,int iPages,int iMaxCount,std::vector<CarFileData>& carFileDataList,bool bOrderInc/*=true*/)
{
	if (NULL ==m_pCarFileOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarFileOp->GetCarFileData(pInfo,iPages,iMaxCount,carFileDataList,bOrderInc);
}

int CCarInfoSaveImpl::DeleteCarFileData(const char* lpFileName)
{
	if (NULL ==m_pCarFileOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarFileOp->DeleteCarFileData(lpFileName);
}


//////////////////////////////////////////////////////////////////////////////////////////////////*************************************************////////////////////////////////

int	CCarInfoSaveImpl::ASInsertCarTypeInfo(PASCarTypeTableInfo	pInfo)
{
	if (NULL == m_pCarTypeOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypeOp->ASInsertCarTypeInfo(pInfo);
}

int	CCarInfoSaveImpl::ASUpdateCarTypeInfo(PASCarTypeTableInfo	pInfo)
{
	if (NULL == m_pCarTypeOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypeOp->ASUpdateCarTypeInfo(pInfo);
}

int CCarInfoSaveImpl::ASGetCarTypeCount(const PASCarTypeTableInfo pInfo,int* pTotalCount)
{
	if (NULL == m_pCarTypeOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypeOp->ASGetCarTypeCount(pInfo,pTotalCount);
}

int CCarInfoSaveImpl::ASGetCarTypeInfo(const PASCarTypeTableInfo pInfo,int iPages,int iMaxCount,std::vector<ASCarTypeTableInfo>& carTypeInfoList,bool bOrderInc/*=true*/)
{
	if (NULL == m_pCarTypeOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypeOp->ASGetCarTypeInfo(pInfo,iPages,iMaxCount,carTypeInfoList,bOrderInc);
}

int	CCarInfoSaveImpl::ASDeleteCarTypeInfo(const char* lpTypeNumer)
{
	if (NULL == m_pCarTypeOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypeOp->ASDeleteCarTypeInfo(lpTypeNumer);
}

int	CCarInfoSaveImpl::ASInsertCarPartInfo(PASCarPartTableInfo	pInfo)
{
	if (NULL == m_pCarPartOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarPartOp->ASInsertCarPartInfo(pInfo);
}

int	CCarInfoSaveImpl::ASUpdateCarPartInfo(PASCarPartTableInfo	pInfo)
{
	if (NULL == m_pCarPartOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarPartOp->ASUpdateCarPartInfo(pInfo);
}

int CCarInfoSaveImpl::ASGetCarPartCount(const PASCarPartTableInfo pInfo,int* pTotalCount)
{
	if (NULL == m_pCarPartOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarPartOp->ASGetCarPartCount(pInfo,pTotalCount);
}

int CCarInfoSaveImpl::ASGetCarPartInfo(const PASCarPartTableInfo pInfo,int iPages,int iMaxCount,std::vector<ASCarPartTableInfo>& carPartInfoList,bool bOrderInc/* =true */)
{
	if (NULL == m_pCarPartOp)
		return OPERATE_DB_ERROR;
	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarPartOp->ASGetCarPartInfo(pInfo,iPages,iMaxCount,carPartInfoList,bOrderInc);
}

int	CCarInfoSaveImpl::ASDeleteCarPartInfo(const PASCarPartTableInfo	pInfo)
{
	if (NULL == m_pCarPartOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarPartOp->ASDeleteCarPartInfo(pInfo);
}

int	CCarInfoSaveImpl::ASInsertCarTypePartsInfo(const PASCarTypePartsTableInfo pInfo,std::vector<std::string>& carTypeInfoList)
{
	if (NULL ==m_pCarTypePartsOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypePartsOp->ASInsertCarTypePartsInfo(pInfo,carTypeInfoList);
}

int	CCarInfoSaveImpl::ASUpdateCarTypePartsInfo(const PASCarTypePartsTableInfo pInfo,std::vector<std::string>& carTypeInfoList)
{
	if (NULL ==m_pCarTypePartsOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypePartsOp->ASUpdateCarTypePartsInfo(pInfo,carTypeInfoList);
}

int CCarInfoSaveImpl::ASGetCarTypePartsAllInfo(std::vector<ASCarTypeTableInfo>& carTypeInfoList)
{
	if (NULL ==m_pCarTypePartsOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypePartsOp->ASGetCarTypePartsAllInfo(carTypeInfoList);
}

int CCarInfoSaveImpl::ASGetCarTypePartsSuppInfo(const PASCarTypePartsTableInfo pInfo,std::vector<ASCarTypeTableInfo>& carTypeInfoList)
{
	if (NULL ==m_pCarTypePartsOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypePartsOp->ASGetCarTypePartsSuppInfo(pInfo,carTypeInfoList);
}

int CCarInfoSaveImpl::ASGetCarTypePartsSuppInfoEx(const PASCarTypePartsTableInfo pInfo,std::vector<ASCarTypeTableInfo>& carTypeInfoList)
{
	if (NULL ==m_pCarTypePartsOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypePartsOp->ASGetCarTypePartsSuppInfoEx(pInfo,carTypeInfoList);
}

int CCarInfoSaveImpl::ASGetCarTypePartsCount(const PASSearchCarTypePartsInfo pInfo,int* pTotalCount)
{
	if (NULL ==m_pCarTypePartsOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypePartsOp->ASGetCarTypePartsCount(pInfo,pTotalCount);
}

int CCarInfoSaveImpl::ASGetCarTypePartsInfo(const PASSearchCarTypePartsInfo pInfo,int iPages,int iMaxCount,std::vector<ASSearchCarTypePartsInfo>& carTypePartInfoList,bool bOrderInc/*=true*/)
{
	if (NULL ==m_pCarTypePartsOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypePartsOp->ASGetCarTypePartsInfo(pInfo,iPages,iMaxCount,carTypePartInfoList,bOrderInc);
}

int	CCarInfoSaveImpl::ASDeleteCarTypePartsInfo(const PASCarTypePartsTableInfo pInfo)
{
	if (NULL ==m_pCarTypePartsOp)
		return OPERATE_DB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pCarTypePartsOp->ASDeleteCarTypePartsInfo(pInfo);
}
