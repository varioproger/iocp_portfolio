#pragma once
#include<Windows.h>
#include"ReadManager.h"
#include<vector>
#include<string>

class TableBase
{
public:
	virtual ~TableBase() = default;
	virtual BOOL SetInfo() = 0;
};

