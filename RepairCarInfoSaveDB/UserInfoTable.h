#pragma once

#include "TableOperateBase.h"
#include "SingletonInstance.h"

class CUserInfoTable
	:public	CTableOperateBase,public CSingletonInstance<CUserInfoTable>
{
public:
	CUserInfoTable(CDbBase* pBase);
	~CUserInfoTable(void);

	int InitTable();
	int InsertUserInfo(PUserPwdInfo pInfo);
	int UpdateUserInfo(PUserPwdInfo pInfo);
	int QueryUserInfo(PUserPwdInfo pInfo);
	int DeleteUserInfo(const char* lpUserName);
};

