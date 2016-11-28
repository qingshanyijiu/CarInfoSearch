#include "stdafx.h"
#include "TableOperateBase.h"
#include "dba.h"


CTableOperateBase::CTableOperateBase(CDbBase* pBase)
	:m_pDbBase(pBase)
{

}


CTableOperateBase::~CTableOperateBase(void)
{
}


int	CTableOperateBase::GetRecordCount(const char* lpSql)
{
	sqlite3* pDb= NULL;
	sqlite3_stmt *pstmt = NULL;
	int iCount=0;

	CConvertChar convertCar;
	const char* pConverSql = convertCar.ToUTF8(lpSql);

	int ret = sqlite3_prepare(m_pDbBase->m_dbOp.GetDB(), pConverSql,convertCar.m_iLen, &pstmt, NULL);
	if( ret != SQLITE_OK )
		return iCount;

	ret = sqlite3_step(pstmt);
	if(SQLITE_ROW == ret)
	{
		iCount = sqlite3_column_int(pstmt, 0);
	}
	sqlite3_finalize(pstmt);

	return iCount;
}