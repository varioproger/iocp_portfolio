#pragma once
#include"TableBase.h"


class TBServerList :public TableBase
{
public:
	TBServerList();
	virtual ~TBServerList();
	virtual BOOL SetInfo() override;
};

