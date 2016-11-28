#include "stdafx.h"
#include "DbBase.h"
#include "Dbghelp.h"

#pragma comment(lib,"Dbghelp.lib")


#ifdef _DEBUG
#define DB_LIB_PATH "RepairCarInfoSaveDBD.dll"
#else
#define DB_LIB_PATH "RepairCarInfoSaveDB.dll"
#endif

CDbBase::CDbBase(void)
{
	m_bIsOpen = false;
}


CDbBase::~CDbBase(void)
{
	CloseDb();
}


int CDbBase::OpenDb(const char* lpFileName)
{
	if(m_bIsOpen)
		return OPERATE_DB_SUCCESS;

	string strPath = lpFileName;
	if (string::npos == strPath.find(':'))
	{
		GetThisDllPath(strPath);
		strPath +="SaveInfo\\";
		strPath += lpFileName;
	}
	MakeSureDirectoryPathExists(strPath.c_str());

	int iRes = m_dbOp.open(strPath.c_str());
	if (SQLITE_OK == iRes)
		m_bIsOpen = true;

	return iRes;
}

int CDbBase::CloseDb()
{
	int iRes  = SQLITE_OK;
	if (m_bIsOpen)
	{
		iRes = m_dbOp.close();
		if (SQLITE_OK == iRes)
			m_bIsOpen  = false;
	}

	return iRes;
}

int CDbBase::QueryBySql(const char* strSql,RetDataType& retData )
{
	sqlite3_stmt *pstmt = NULL;
	int ret;
	sqlite3* p_db= m_dbOp.GetDB();
	if(p_db == NULL)
		return SQLITE_ERROR;
	ret = sqlite3_prepare(p_db, strSql,strlen(strSql), &pstmt, NULL);
	if( ret != SQLITE_OK )
		return SQLITE_ERROR;
	bool bFirst =true;
	int colCount = 0;
	std::ostringstream tempStr;
	vector<int> coltypes;
	int i=0;
	while( 1 )
	{
		ret = sqlite3_step(pstmt);
		if( ret != SQLITE_ROW )
			break;
		if(bFirst)
		{
			bFirst = false;
			colCount = sqlite3_data_count(pstmt);
			std::list<std::string> dataList;
			for (i=0;i<colCount;++i)
			{
				retData.push_back(std::make_pair(sqlite3_column_name(pstmt,i),dataList));
				coltypes.push_back(sqlite3_column_type(pstmt,i));
			}
		}
		if(colCount == 0)
			return SQLITE_ERROR;
		for (i=0;i<colCount;++i)
		{
			if(coltypes[i] == SQLITE_INTEGER)
				tempStr<<sqlite3_column_int(pstmt,i);
			else if(coltypes[i] == SQLITE_FLOAT )
				tempStr<<sqlite3_column_double(pstmt,i);
			else if(coltypes[i] == SQLITE_TEXT)
				tempStr<<sqlite3_column_text(pstmt,i);
			else
				tempStr<<"";
			(retData[i].second).push_back(tempStr.str());
			tempStr.clear();
			tempStr.str("");
		}
	} 
	sqlite3_finalize(pstmt);

	return SQLITE_OK;
}

void CDbBase::GetThisDllPath(std::string& strPath)
{
	CHAR tcDllPath[MAX_PATH]={0};

	::GetModuleFileName(::GetModuleHandle(DB_LIB_PATH),tcDllPath,MAX_PATH);
	strPath = tcDllPath;

	int iPos = strPath.rfind('\\');
	if (string::npos != iPos)
		strPath = strPath.substr(0,iPos+1);
	else
		strPath.empty();
}