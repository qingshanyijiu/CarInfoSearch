#pragma once

template<typename DataType >
class	CDataObject
{
public:
	CDataObject()
	{
		m_data = NULL;
	}

	~CDataObject()
	{
		if (m_data)
			delete m_data;
	}

public:
	DataType*	m_data;
};

template<typename DataType>
class CSingletonInstance
{
protected:
	CSingletonInstance(){};
	CSingletonInstance(CSingletonInstance&);
	CSingletonInstance& operator =(CSingletonInstance&);

public:
	virtual~CSingletonInstance(){};

	template<typename OperateType>
	static DataType*& GetInstance(OperateType* pOpType)
	{
		if (NULL == s_dataInstance.m_data)
			s_dataInstance.m_data = new DataType(pOpType);

		return s_dataInstance.m_data;
	}

	static DataType*& GetInstance()
	{
		if (NULL == s_dataInstance.m_data)
			s_dataInstance.m_data = new DataType();

		return s_dataInstance.m_data;
	}

protected:
	static CDataObject<DataType> s_dataInstance;
};

 template<typename DataType>
 CDataObject<DataType>	CSingletonInstance<DataType>::s_dataInstance;