#pragma once

#include "DbBase.h"

class CTableOperateBase
{
public:
	CTableOperateBase(CDbBase* pBase);
	virtual ~CTableOperateBase(void);

	virtual int InitTable() = 0;

protected:
	int		GetRecordCount(const char* lpSql);

protected:
	CDbBase*	m_pDbBase;
};

