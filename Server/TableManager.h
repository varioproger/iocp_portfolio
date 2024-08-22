#pragma once
#include"Singleton.h"
#include"TableBase.h"
#include"TBServerList.h"
#include<memory>
#include<vector>

class TableManager : public Singleton<TableManager>
{
private:
	std::vector<std::unique_ptr<TableBase>> v_table;

public:
	TableManager();
	~TableManager();
	void init();
	void SetInfo();
};

#define TABLEMANAGER TableManager::getInstance()

