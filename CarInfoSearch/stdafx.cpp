
// stdafx.cpp : 只包括标准包含文件的源文件
// CarPartCarInfoManage.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"


#ifdef _DEBUG
#pragma comment(lib,"../bin/RepairCarInfoSaveDBD.lib")
#else
#pragma comment(lib,"../bin/RepairCarInfoSaveDB.lib")
#endif