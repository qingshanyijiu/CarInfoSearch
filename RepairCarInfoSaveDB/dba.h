#ifndef __KT_CASHUNITINFO_DBA_INCLUDED_H__
#define __KT_CASHUNITINFO_DBA_INCLUDED_H__

extern "C"
{
#include "../ktdb/sqlite3.h"
#include "../ktdb/sqliteLimit.h"
};

#include <sstream>
#include <string>
using namespace std;


#ifdef _DEBUG
#pragma comment(lib, "..\\lib\\ktdbD.lib")
#else
#pragma comment(lib, "..\\lib\\ktdb.lib")
#endif

typedef std::ostringstream sqlstring;


class CConvertChar
{
public:
	CConvertChar(){
		m_pDst = NULL;
		m_iLen = 0;
	}

	~CConvertChar(){
		if (m_pDst)
		{
			delete [] m_pDst;
			m_pDst = NULL;
		}
	}

	char* ToUTF8(const char* lpSrc)
	{
		if (m_pDst)
		{
			delete [] m_pDst;
			m_pDst = NULL;
		}

		m_pDst = ConvertToUTF8(lpSrc,&m_iLen);
		return m_pDst;
	}

	char* ToGBK(const char* lpSrc)
	{
		if (m_pDst)
		{
			delete [] m_pDst;
			m_pDst = NULL;
		}
		m_pDst = ConvertToGBK(lpSrc,&m_iLen);
		return m_pDst;
	}

protected:
	static char* ConvertToUTF8(const char* lpSrc,int* pLen=NULL)
	{
		unsigned short* pusUnPath = NULL;
		int iLen = MultiByteToWideChar(CP_ACP,0,lpSrc,strlen(lpSrc)+1,NULL,0);
		pusUnPath = new unsigned short[iLen];
		MultiByteToWideChar(CP_ACP,0,lpSrc,strlen(lpSrc)+1,(LPWSTR)pusUnPath,iLen);

		int iGetLen = WideCharToMultiByte(CP_UTF8,0,(LPWSTR)pusUnPath,iLen,NULL,0,NULL,NULL);
		char* lpDst = new char[iGetLen];
		WideCharToMultiByte(CP_UTF8,0,(LPWSTR)pusUnPath,iLen,lpDst,iGetLen,NULL,NULL);
		delete [] pusUnPath;

		if (pLen)
		{
			*pLen = iGetLen;
		}

		return lpDst;
	}

	static char* ConvertToGBK(const char* lpSrc,int* pLen=NULL)
	{
		unsigned short* pusUnPath = NULL;
		int iLen = MultiByteToWideChar(CP_UTF8,0,lpSrc,strlen(lpSrc)+1,NULL,0);
		pusUnPath = new unsigned short[iLen];
		MultiByteToWideChar(CP_UTF8,0,lpSrc,strlen(lpSrc)+1,(LPWSTR)pusUnPath,iLen);

		int iGetLen = WideCharToMultiByte(CP_ACP,0,(LPWSTR)pusUnPath,iLen,NULL,0,NULL,NULL);
		char* lpDst = new char[iGetLen];
		WideCharToMultiByte(CP_ACP,0,(LPWSTR)pusUnPath,iLen,lpDst,iGetLen,NULL,NULL);

		delete [] pusUnPath;

		if (pLen)
		{
			*pLen = iGetLen;
		}

		return lpDst;
	}

private:
	char*	m_pDst;

public:
	int		m_iLen;
};

class db_operator
{
public:
	db_operator():p_db_(0)
	{
	}
	~db_operator()
	{
	}

	int open(const char * lpFilename)
	{
		CConvertChar convectChar;

		return sqlite3_open(convectChar.ToUTF8(lpFilename), &p_db_);;
	}

	int close()
	{
		int res = sqlite3_close(p_db_);
		if (SQLITE_OK==res) p_db_=0;

		return res;
	}

	int execute_dml(const char *sql)
	{
		int res = SQLITE_OK;
		do
		{
			res = sqlite3_exec(p_db_, sql, 0, 0, 0);
			
		}while((SQLITE_BUSY==res)||(SQLITE_LOCKED==res));
		
		return res;
	}

	int begin_trans()
	{
		const char * sql = "begin transaction;";

		return execute(sql, NULL, NULL, NULL);
		
	}

	int rollback_trans()
	{
		const char * sql = "rollback transaction;";

		return execute(sql, NULL, NULL, NULL);
		
	}

	int commit_trans()
	{
		const char * sql = "commit transaction;";

		return execute(sql, NULL, NULL, NULL);
		
	}

// 	int execute(const char *sql, sqlite3_callback cb, void * para, char **errmsg)
// 	{
// 		return sqlite3_exec(p_db_, sql, cb, para, errmsg);
// 	}

	int execute(const char *sql, sqlite3_callback cb, void * para, char **errmsg)
	{
		CConvertChar convectChar;
		return sqlite3_exec(p_db_, convectChar.ToUTF8(sql), cb, para, errmsg);
	}

	static int query_table_name_handle(void * para, int n_column, char ** column_value, char ** column_name)
	{
		if(strlen(column_value[0]))
			memcpy(para, column_value[0], strlen(column_value[0]));

		return SQLITE_OK;
	}

	//SQLITE_OK 为有表，其它值为无表
	int get_table(const char * name)
	{
		sqlstring sql;
		sql << "select name from sqlite_master where type='table' and name='" << name << "';";
		char result[256]={0};

		int res = sqlite3_exec(p_db_, sql.str().c_str(), db_operator::query_table_name_handle, result, NULL);
		if (SQLITE_OK==res)
		{
			if (strcmp(name, result)) res=SQLITE_NOTFOUND;
		}
	
		return res;
	}

	

	sqlite3* GetDB()
	{
		return p_db_;
	}
	
private:
	db_operator(const db_operator&);
	db_operator& operator=(const db_operator&);

	struct sqlite3 * p_db_;
};
#endif