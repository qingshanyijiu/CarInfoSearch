#include "stdafx.h"
#include "UserInfoTable.h"


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
			m_pDbBase->m_dbOp.execute_dml("insert into UserInfo values ('root','root',7);");
			m_pDbBase->m_dbOp.execute_dml("insert into UserInfo values ('admin','admin',3);");
			m_pDbBase->m_dbOp.execute_dml("insert into UserInfo values ('user','user',1);");
		}
	}

	return iRes;
}

int CUserInfoTable::InsertUserInfo(PUserPwdInfo pInfo)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	sql<<"insert into UserInfo values ('";
	sql<<pInfo->csUserName<<"','";
	sql<<pInfo->csUserPwd<<"',";
	sql<<pInfo->uKey<<");";
	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}

int CUserInfoTable::UpdateUserInfo(PUserPwdInfo pInfo)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	sql<<"update UserInfo set ";
	sql<<"UserPwd='"<<pInfo->csUserPwd<<"',";
	sql<<"UserKey="<<pInfo->uKey;
	sql<<" where UserName='"<<pInfo->csUserName<<"';";

	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}

int CUserInfoTable::QueryUserInfo(PUserPwdInfo pInfo)
{
	sqlstring sql;

	sql<<"select UserKey from UserInfo";
	sql<<" where UserName='"<<pInfo->csUserName<<"' and UserPwd='"<<pInfo->csUserPwd<<"';";

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