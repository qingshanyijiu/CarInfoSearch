#include "stdafx.h"
#include "UserInfoTable.h"

#include <sstream>
#include <string>
#include <iomanip>
using namespace std;


#define  CONST_ENCRY_DATA_ELN		(64)

void EncryData(const char* lpSrcData,char* lpDestData)
{
	ostringstream ostr;

	int iLen = strlen(lpSrcData),i,j,iDiv,index,ilastindex;
	char chTemp;
	unsigned short usSum=0;

	ostr<<setw(2)<<setfill('0')<<hex<<(iLen/10);
	ostr<<setw(2)<<setfill('0')<<hex<<(iLen%10);

	iDiv = (CONST_ENCRY_DATA_ELN-2)/iLen;

	for(i=0;i<iLen;++i)
	{
		chTemp = ostr.str().at(i*iDiv);
		chTemp ^= lpSrcData[i];
		usSum += chTemp;
		ostr<<setw(2)<<setfill('0')<<hex<<(int)chTemp;
		ilastindex = i*iDiv+4;

		for (j=1;j<iDiv;++j)
		{
			index = i*iDiv+j+3;
			chTemp = ostr.str().at(ilastindex);
			chTemp ^= (CONST_ENCRY_DATA_ELN-index)&0x3C;
			usSum += chTemp;
			ostr<<setw(2)<<setfill('0')<<hex<<(int)chTemp;

			++ilastindex;
		}
	}

	ilastindex = i*iDiv+4;
	for(i=iLen*iDiv+2;i<CONST_ENCRY_DATA_ELN;++i)
	{
		index = i-iDiv;
		chTemp = ostr.str().at(ilastindex);
		chTemp ^= (CONST_ENCRY_DATA_ELN-index)&0x3C;
		usSum += chTemp;
		ostr<<setw(2)<<setfill('0')<<hex<<(int)chTemp;

		++ilastindex;
	}
	strcpy(lpDestData,ostr.str().c_str());

	char csTempBufer[5]={0};
	sprintf(csTempBufer,"%02x%02x",(iLen/10)^((usSum>>8)&0xFF),(iLen%10)^(usSum&0xFF));
	memcpy(lpDestData,csTempBufer,4);
}

void DecodeData(const char* lpSrcData,char* lpDestData)
{
	char bData[10]={0};
	int bValue;
	int iLen,i,j;
	unsigned short usSum=0;

	iLen = strlen(lpSrcData);
	for (i=4;i<iLen;i+=2)
	{
		strncpy(bData,lpSrcData+i,2);
		sscanf(bData, "%02x",&bValue); 
		usSum += bValue;
	}

	strncpy(bData,lpSrcData,2);
	sscanf(bData, "%02x",&bValue);  
	bValue ^= (usSum>>8)&0xFF;
	iLen = bValue*10;

	strncpy(bData,lpSrcData+2,2);
	sscanf(bData, "%02x",&bValue);  
	bValue ^= (usSum&0xFF);
	iLen += bValue;

	char csTempBufffer[256]={0};
	sprintf(csTempBufffer,"%02x%02x%s",iLen/10,iLen%10,lpSrcData+4);

	int iDiv = (CONST_ENCRY_DATA_ELN-2)/iLen,index;
	for (i=0,j=4;i<iLen;++i,j+=iDiv*2)
	{
		index = i*iDiv;
		strncpy(bData,csTempBufffer+j,2);
		sscanf(bData, "%02x",&bValue);
		bValue ^= csTempBufffer[index];

		lpDestData[i] = bValue;
	}
	lpDestData[iLen] ='\0'; 
}



CUserInfoTable::CUserInfoTable(CDbBase* pBase)
	:CTableOperateBase(pBase)
{
}


CUserInfoTable::~CUserInfoTable(void)
{
}


int CUserInfoTable::InitTable()
{
	int iRes = SQLITE_OK;

	iRes = m_pDbBase->m_dbOp.get_table("UserInfo");
	if (SQLITE_OK != iRes)
	{
		const char* lpTableInfoSql = "CREATE TABLE UserInfo (UserName TEXT PRIMARY KEY NOT NULL,UserPwd TEXT, UserKey INT);";
		iRes = m_pDbBase->m_dbOp.execute_dml(lpTableInfoSql);

		if (SQLITE_OK == iRes)
		{
			UserPwdInfo info;
			strcpy(info.csUserName,"root");
			strcpy(info.csUserPwd,"root");
			info.uKey = 0xFF;
			InsertUserInfo(&info);

			strcpy(info.csUserName,"admin");
			strcpy(info.csUserPwd,"admin");
			info.uKey = 0x07;
			InsertUserInfo(&info);

			strcpy(info.csUserName,"user");
			strcpy(info.csUserPwd,"user");
			info.uKey = 0x05;
			InsertUserInfo(&info);
		}
	}
	/*else
	{
		UserPwdInfo info;
		strcpy(info.csUserName,"root");
		strcpy(info.csUserPwd,"root");
		info.uKey = 0xFF;
		UpdateUserInfo(&info);

		strcpy(info.csUserName,"admin");
		strcpy(info.csUserPwd,"admin");
		info.uKey = 0x07;
		UpdateUserInfo(&info);

		strcpy(info.csUserName,"user");
		strcpy(info.csUserPwd,"user");
		info.uKey = 0x05;
		UpdateUserInfo(&info);
	}*/

	return iRes;
}

int CUserInfoTable::InsertUserInfo(PUserPwdInfo pInfo)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	char csEnCode[256]={0};
	EncryData(pInfo->csUserPwd,csEnCode);

	sql<<"insert into UserInfo values ('";
	sql<<pInfo->csUserName<<"','";
	sql<<csEnCode<<"',";
	sql<<pInfo->uKey<<");";
	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}

int CUserInfoTable::UpdateUserInfo(PUserPwdInfo pInfo)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	char csEnCode[256]={0};
	EncryData(pInfo->csUserPwd,csEnCode);

	sql<<"update UserInfo set ";
	sql<<"UserPwd='"<<csEnCode<<"',";
	sql<<"UserKey="<<pInfo->uKey;
	sql<<" where UserName='"<<pInfo->csUserName<<"';";

	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}

int CUserInfoTable::QueryUserInfo(PUserPwdInfo pInfo)
{
	sqlstring sql;

	char csEnCode[256]={0};
	EncryData(pInfo->csUserPwd,csEnCode);

	sql<<"select UserKey from UserInfo";
	sql<<" where UserName='"<<pInfo->csUserName<<"' and UserPwd='"<<csEnCode<<"';";

	pInfo->uKey = GetRecordCount(sql.str().c_str());

	return SQLITE_OK;
}

int CUserInfoTable::DeleteUserInfo(const char* lpUserName)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	sql<<"delete from UserInfo where UserName='";
	sql<<lpUserName<<"';";

	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}