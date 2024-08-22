#pragma once
#include"ServerGlobalDef.h"
#include<vector>
#include<string>

class MonostateTable
{
public:
	static std::vector<std::vector< STRUCT_SERVERLIST>> g_pServerList;
};
 
#define MONOSERVERLIST MonostateTable::g_pServerList


