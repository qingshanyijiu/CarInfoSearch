#ifndef ___REPAIRCARINFOSAVEDB_____H
#define ___REPAIRCARINFOSAVEDB_____H

#include <string>
#include <vector>

#ifdef REPAIRCARINFOSAVEDB_EXPORTS
#define REPAIRCARINFOSAVEDB_API __declspec(dllexport)
#else
#define REPAIRCARINFOSAVEDB_API __declspec(dllimport)
#endif

//**********************************************table info struct and define **************************************//

#define	OPERATE_DB_SUCCESS		(0)
#define	OPERATE_DB_ERROR		(1)

typedef	struct	tagCarTypeTableInfo
{
	char		csCarTypeNum[16];
	char		csCarDetailTypeNum[32]; //Key
	char		csCarFactory[32];
	char		csCarStatus[32];
	char		csCarDetailName[32];
	std::string	strCarNotes;
	std::string strCarReserve;

	tagCarTypeTableInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(csCarTypeNum,0,sizeof(csCarTypeNum));
		memset(csCarDetailTypeNum,0,sizeof(csCarDetailTypeNum));
		memset(csCarFactory,0,sizeof(csCarFactory));
		memset(csCarStatus,0,sizeof(csCarStatus));
		memset(csCarDetailName,0,sizeof(csCarDetailName));
		strCarNotes.clear();
		strCarReserve.clear();
	}

}CarTypeTableInfo,*PCarTypeTableInfo;

typedef	struct	tagCarPartTableInfo
{
	char	csCarTypeNum[16];
	char	csDAENum[32];
	char	csMMCNum[32]; //key TypeNum,DAENum MMCNum
	char	csEPLNum[32];
	char	csVCNum[16];
	int		iLevel;
	char	csEnglishName[64];
	char	csChineseName[64];
	char	csPicNum[32];
	char	csInstallNum[32];
	int		iInstallMark;

	tagCarPartTableInfo()
	{
		Clear();
	}

	void Clear(){
		memset(csCarTypeNum,0,sizeof(csCarTypeNum));
		memset(csEPLNum,0,sizeof(csEPLNum));
		memset(csVCNum,0,sizeof(csVCNum));
		iLevel = 0;
		memset(csDAENum,0,sizeof(csDAENum));
		memset(csMMCNum,0,sizeof(csMMCNum));
		memset(csEnglishName,0,sizeof(csEnglishName));
		memset(csChineseName,0,sizeof(csChineseName));
		memset(csPicNum,0,sizeof(csPicNum));
		memset(csInstallNum,0,sizeof(csInstallNum));
		iInstallMark = 0;
	}

	void Copy(tagCarPartTableInfo& info){
		strcpy(csCarTypeNum,info.csCarTypeNum);
		strcpy(csEPLNum,info.csEPLNum);
		strcpy(csVCNum,info.csVCNum);
		iLevel = info.iLevel;
		strcpy(csDAENum,info.csDAENum);
		strcpy(csMMCNum,info.csMMCNum);
		strcpy(csEnglishName,info.csEnglishName);
		strcpy(csChineseName,info.csChineseName);
		strcpy(csPicNum,info.csPicNum);
		strcpy(csInstallNum,info.csInstallNum);
		iInstallMark = info.iInstallMark;
	}
}CarPartTableInfo,*PCarPartTableInfo;


typedef	struct tagCarTypePartsTableInfo
{
		char	csCarDetailTypeNum[32];
		char	csCarTypeNum[16];
		char	csDAENum[32];
		char	csMMCNum[32];

		tagCarTypePartsTableInfo()
		{
			Clear();
		}

		void Clear(){
			memset(csCarDetailTypeNum,0,sizeof(csCarDetailTypeNum));
			memset(csCarTypeNum,0,sizeof(csCarTypeNum));
			memset(csDAENum,0,sizeof(csDAENum));
			memset(csMMCNum,0,sizeof(csMMCNum));
		}
}CarTypePartsTableInfo,*PCarTypePartsTableInfo;

typedef struct tagSearchCarTypePartsInfo
{
	char	csCarDetailTypeNum[32];
	char	csCarFactory[32];
	char	csCarDetailName[32];
	char	csCarTypeNum[16];
	char	csDAENum[32];
	char	csMMCNum[32];
	char	csChineseName[64];
	int		iLevel;

	tagSearchCarTypePartsInfo()
	{
		Clear();
	}

	void Clear(){
		memset(csCarDetailTypeNum,0,sizeof(csCarDetailTypeNum));
		memset(csCarFactory,0,sizeof(csCarFactory));
		memset(csCarDetailName,0,sizeof(csCarDetailName));
		memset(csCarTypeNum,0,sizeof(csCarTypeNum));
		memset(csDAENum,0,sizeof(csDAENum));
		memset(csMMCNum,0,sizeof(csMMCNum));
		memset(csChineseName,0,sizeof(csChineseName));
		iLevel = 0;
	}
}SearchCarTypePartsInfo,*PSearchCarTypePartsInfo;

typedef	struct tagUserPwdInfo
{
	char		csUserName[16];
	char		csUserPwd[16];
	unsigned int	uKey;
}UserPwdInfo,*PUserPwdInfo;

typedef	struct	tagCarFileData
{
	char		csCarTypeNum[16];
	std::string	strFileName;
	std::string strNotes;


	tagCarFileData()
	{
		Clear();
	}

	void Clear()
	{
		memset(csCarTypeNum,0,sizeof(csCarTypeNum));
		strFileName.clear();
		strNotes.clear();
	}
}CarFileData,*PCarFileData;

//********************************************** Operate DB API	**************************************//

#ifdef __cplusplus
extern "C"
{
#endif

int REPAIRCARINFOSAVEDB_API OpenDb(const char* lpFileName);

int REPAIRCARINFOSAVEDB_API CloseDb();

int	REPAIRCARINFOSAVEDB_API InsertCarTypeInfo(const PCarTypeTableInfo	pInfo);

int	REPAIRCARINFOSAVEDB_API UpdateCarTypeInfo(const PCarTypeTableInfo	pInfo);

int REPAIRCARINFOSAVEDB_API GetCarTypeCount(const PCarTypeTableInfo pInfo,int* pTotalCount);

int REPAIRCARINFOSAVEDB_API GetCarTypeInfo(const PCarTypeTableInfo pInfo,int iPages,int iMaxCount,std::vector<CarTypeTableInfo>& carTypeInfoList,bool bOrderInc=true);

int	REPAIRCARINFOSAVEDB_API DeleteCarTypeInfo(const char* lpTypeNumer);

int	REPAIRCARINFOSAVEDB_API InsertCarPartInfo(const PCarPartTableInfo	pInfo);

int	REPAIRCARINFOSAVEDB_API UpdateCarPartInfo(const PCarPartTableInfo	pInfo);

int REPAIRCARINFOSAVEDB_API GetCarPartCount(const PCarPartTableInfo pInfo,int* pTotalCount);

int REPAIRCARINFOSAVEDB_API GetCarPartInfo(const PCarPartTableInfo pInfo,int iPages,int iMaxCount,std::vector<CarPartTableInfo>& carPartInfoList,bool bOrderInc=true);

int	REPAIRCARINFOSAVEDB_API DeleteCarPartInfo(const PCarPartTableInfo	pInfo);

int	REPAIRCARINFOSAVEDB_API InsertCarTypePartsInfo(const PCarTypePartsTableInfo pInfo,std::vector<std::string>& carTypeInfoList);

int	REPAIRCARINFOSAVEDB_API UpdateCarTypePartsInfo(const PCarTypePartsTableInfo pInfo,std::vector<std::string>& carTypeInfoList);

int REPAIRCARINFOSAVEDB_API GetCarTypePartsAllInfo(std::vector<CarTypeTableInfo>& carTypeInfoList);

int REPAIRCARINFOSAVEDB_API GetCarTypePartsSuppInfo(const PCarTypePartsTableInfo pInfo,std::vector<CarTypeTableInfo>& carTypeInfoList);

int REPAIRCARINFOSAVEDB_API GetCarTypePartsSuppInfoEx(const PCarTypePartsTableInfo pInfo,std::vector<CarTypeTableInfo>& carTypeInfoList);

int REPAIRCARINFOSAVEDB_API GetCarTypePartsCount(const PSearchCarTypePartsInfo pInfo,int* pTotalCount);

int REPAIRCARINFOSAVEDB_API GetCarTypePartsInfo(const PSearchCarTypePartsInfo pInfo,int iPages,int iMaxCount,std::vector<SearchCarTypePartsInfo>& carTypePartInfoList,bool bOrderInc=true);

int	REPAIRCARINFOSAVEDB_API DeleteCarTypePartsInfo(const PCarTypePartsTableInfo pInfo);

int REPAIRCARINFOSAVEDB_API InsertUserInfo(PUserPwdInfo pInfo);

int REPAIRCARINFOSAVEDB_API UpdateUserInfo(PUserPwdInfo pInfo);

int REPAIRCARINFOSAVEDB_API QueryUserInfo(PUserPwdInfo pInfo);

int REPAIRCARINFOSAVEDB_API DeleteUserInfo(const char* lpUserName);

int REPAIRCARINFOSAVEDB_API InsertCarFileData(const PCarFileData pInfo);

int REPAIRCARINFOSAVEDB_API UpdateCarFileData(const PCarFileData pInfo);

int REPAIRCARINFOSAVEDB_API GetCarFileDataCount(const PCarFileData pInfo,int* pTotalCount);

int REPAIRCARINFOSAVEDB_API GetCarFileData(const PCarFileData pInfo,int iPages,int iMaxCount,std::vector<CarFileData>& carFileDataList,bool bOrderInc=true);

int	REPAIRCARINFOSAVEDB_API DeleteCarFileData(const char* lpFileName);


#ifdef __cplusplus
}
#endif

#endif