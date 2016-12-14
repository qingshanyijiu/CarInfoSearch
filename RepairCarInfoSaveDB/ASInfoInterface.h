#ifndef ___ASINFOINTERFACE_____H
#define ___ASINFOINTERFACE_____H

#include <string>
#include <vector>

#ifndef REPAIRCARINFOSAVEDB_API
#ifdef REPAIRCARINFOSAVEDB_EXPORTS
#define REPAIRCARINFOSAVEDB_API __declspec(dllexport)
#else
#define REPAIRCARINFOSAVEDB_API __declspec(dllimport)
#endif
#endif


typedef	struct	tagASCarTypeTableInfo
{
	char		csCarTypeNum[16];
	char		csCarDetailTypeNum[32]; //Key
	char		csCustomerCode[16];
	char		csCarFactory[32];
	char		csCarType[32];
	char		csCarName[32];
	char		csCarPattern[32];
	char		csEnginePattern[32];
	char		csMarkModel[16];
	std::string	strCarNotes;
	std::string strCarReserve;

	tagASCarTypeTableInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(csCarTypeNum,0,sizeof(csCarTypeNum));
		memset(csCarDetailTypeNum,0,sizeof(csCarDetailTypeNum));
		memset(csCustomerCode,0,sizeof(csCustomerCode));
		memset(csCarFactory,0,sizeof(csCarFactory));
		memset(csCarType,0,sizeof(csCarType));
		memset(csCarName,0,sizeof(csCarName));
		memset(csCarPattern,0,sizeof(csCarPattern));
		memset(csEnginePattern,0,sizeof(csEnginePattern));
		memset(csMarkModel,0,sizeof(csMarkModel));
		strCarNotes.clear();
		strCarReserve.clear();
	}

}ASCarTypeTableInfo,*PASCarTypeTableInfo;

typedef	struct	tagASCarPartTableInfo
{
	char	csCarTypeNum[16];
	char	csPartNum[32];  //key:csCarTypeNum,csPartNum
	char	csWholeNum[16];
	char	csWholeEngName[64];
	char	csWholeChinName[64];
	char	csItemNum[16];
	char	csEngName[64];
	char	csChinName[64];
	std::string	strRemark;
	std::string strPartReserve;

	tagASCarPartTableInfo()
	{
		Clear();
	}

	void Clear(){
		memset(csCarTypeNum,0,sizeof(csCarTypeNum));
		memset(csPartNum,0,sizeof(csPartNum));
		memset(csWholeNum,0,sizeof(csWholeNum));
		memset(csWholeEngName,0,sizeof(csWholeEngName));
		memset(csWholeChinName,0,sizeof(csWholeChinName));
		memset(csItemNum,0,sizeof(csItemNum));
		memset(csEngName,0,sizeof(csEngName));
		memset(csChinName,0,sizeof(csChinName));
		strRemark.clear();
		strPartReserve.clear();
	}

	void Copy(tagASCarPartTableInfo& info){
		strcpy(csCarTypeNum,info.csCarTypeNum);
		strcpy(csPartNum,info.csPartNum);
		strcpy(csWholeNum,info.csWholeNum);
		strcpy(csWholeEngName,info.csWholeEngName);
		strcpy(csWholeChinName,info.csWholeChinName);
		strcpy(csItemNum,info.csItemNum);
		strcpy(csEngName,info.csEngName);
		strcpy(csChinName,info.csChinName);
		strRemark = info.strRemark;
		strPartReserve = info.strPartReserve;
	}
}ASCarPartTableInfo,*PASCarPartTableInfo;

typedef	struct tagASCarTypePartsTableInfo
{
	char	csCarDetailTypeNum[32];
	char	csCarTypeNum[16];
	char	csPartNum[32];

	tagASCarTypePartsTableInfo()
	{
		Clear();
	}

	void Clear(){
		memset(csCarDetailTypeNum,0,sizeof(csCarDetailTypeNum));
		memset(csCarTypeNum,0,sizeof(csCarTypeNum));
		memset(csPartNum,0,sizeof(csPartNum));
	}
}ASCarTypePartsTableInfo,*PASCarTypePartsTableInfo;

typedef struct tagASSearchCarTypePartsInfo
{
	char	csCarDetailTypeNum[32];
	char	csCarFactory[32];
	char	csCarType[32];
	char	csCarName[32];
	char	csCarTypeNum[16];
	char	csPartNum[32];
	char	csWholeChinName[64];
	char	csItemNum[16];
	char	csChinName[64];
	std::string	strRemark;

	tagASSearchCarTypePartsInfo()
	{
		Clear();
	}

	void Clear(){
		memset(csCarDetailTypeNum,0,sizeof(csCarDetailTypeNum));
		memset(csCarFactory,0,sizeof(csCarFactory));
		memset(csCarType,0,sizeof(csCarType));
		memset(csCarName,0,sizeof(csCarName));
		memset(csCarTypeNum,0,sizeof(csCarTypeNum));
		memset(csPartNum,0,sizeof(csPartNum));
		memset(csWholeChinName,0,sizeof(csWholeChinName));
		memset(csItemNum,0,sizeof(csItemNum));
		memset(csChinName,0,sizeof(csChinName));
		strRemark.clear();
	}
}ASSearchCarTypePartsInfo,*PASSearchCarTypePartsInfo;



#ifdef __cplusplus
extern "C"
{
#endif

int	REPAIRCARINFOSAVEDB_API ASInsertCarTypeInfo(const PASCarTypeTableInfo	pInfo);

int	REPAIRCARINFOSAVEDB_API ASUpdateCarTypeInfo(const PASCarTypeTableInfo	pInfo);

int REPAIRCARINFOSAVEDB_API ASGetCarTypeCount(const PASCarTypeTableInfo pInfo,int* pTotalCount);

int REPAIRCARINFOSAVEDB_API ASGetCarTypeInfo(const PASCarTypeTableInfo pInfo,int iPages,int iMaxCount,std::vector<ASCarTypeTableInfo>& carTypeInfoList,bool bOrderInc=true);

int	REPAIRCARINFOSAVEDB_API ASDeleteCarTypeInfo(const char* lpTypeNumer);

int	REPAIRCARINFOSAVEDB_API ASInsertCarPartInfo(const PASCarPartTableInfo	pInfo);

int	REPAIRCARINFOSAVEDB_API ASUpdateCarPartInfo(const PASCarPartTableInfo	pInfo);

int REPAIRCARINFOSAVEDB_API ASGetCarPartCount(const PASCarPartTableInfo pInfo,int* pTotalCount);


int REPAIRCARINFOSAVEDB_API ASGetCarPartInfo(const PASCarPartTableInfo pInfo,int iPages,int iMaxCount,std::vector<ASCarPartTableInfo>& carPartInfoList,bool bOrderInc=true);

int	REPAIRCARINFOSAVEDB_API ASDeleteCarPartInfo(const PASCarPartTableInfo	pInfo);

int	REPAIRCARINFOSAVEDB_API ASInsertCarTypePartsInfo(const PASCarTypePartsTableInfo pInfo,std::vector<std::string>& carTypeInfoList);

int	REPAIRCARINFOSAVEDB_API ASUpdateCarTypePartsInfo(const PASCarTypePartsTableInfo pInfo,std::vector<std::string>& carTypeInfoList);

int REPAIRCARINFOSAVEDB_API ASGetCarTypePartsAllInfo(std::vector<ASCarTypeTableInfo>& carTypeInfoList);

int REPAIRCARINFOSAVEDB_API ASGetCarTypePartsSuppInfo(const PASCarTypePartsTableInfo pInfo,std::vector<ASCarTypeTableInfo>& carTypeInfoList);

int REPAIRCARINFOSAVEDB_API ASGetCarTypePartsSuppInfoEx(const PASCarTypePartsTableInfo pInfo,std::vector<ASCarTypeTableInfo>& carTypeInfoList);

int REPAIRCARINFOSAVEDB_API ASGetCarTypePartsCount(const PASSearchCarTypePartsInfo pInfo,int* pTotalCount);

int REPAIRCARINFOSAVEDB_API ASGetCarTypePartsInfo(const PASSearchCarTypePartsInfo pInfo,int iPages,int iMaxCount,std::vector<ASSearchCarTypePartsInfo>& carTypePartInfoList,bool bOrderInc=true);

int	REPAIRCARINFOSAVEDB_API ASDeleteCarTypePartsInfo(const PASCarTypePartsTableInfo pInfo);

#ifdef __cplusplus
}
#endif

#endif