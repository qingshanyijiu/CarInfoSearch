#pragma once

#include "dba.h"
#include "SingletonInstance.h"
#include <string>
#include "RepairCarInfoSaveDB.h"
#include "ASInfoInterface.h"
#include <list>
#include <vector>
typedef std::vector<pair<const std::string,std::list< std::string> > > RetDataType;

class CDbBase : public CSingletonInstance<CDbBase>
{
public:
	CDbBase(void);
	~CDbBase(void);
	
	int OpenDb(const char* lpFileName);
	int CloseDb();
	int QueryBySql(const char* strSql,RetDataType& retData );
protected:
	static void GetThisDllPath(std::string& strPath);

public:
	db_operator		m_dbOp;

protected:
	bool			m_bIsOpen;
};

