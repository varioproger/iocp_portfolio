#include "TBServerList.h"
#include<iostream>
#include"MonostateTable.h"
#include"ReadManager.h"
TBServerList::TBServerList()
{
	MONOSERVERLIST.clear();
}

TBServerList::~TBServerList()
{
	MONOSERVERLIST.clear();
}

BOOL TBServerList::SetInfo()
{
	auto Data = std::move(READMANAGER->DoRead("../../serverlistL.txt", "\t", "txt"));
		
	std::vector< STRUCT_SERVERLIST> v_elem;
	v_elem.clear();

	// Struct ��ũ�� �κ��� ���������Ƿ� �׳� ����
	/*int cur_group = atoi(Data[0][0].c_str());
	int next_group = atoi(Data[0][0].c_str());
	for (int i = 0; i < Data.size(); i++)
	{

		STRUCT_SERVERLIST elem;
		next_group = atoi(Data[i][0].c_str());
		if (cur_group != next_group)
		{
			MONOSERVERLIST.emplace_back(v_elem);
			cur_group = next_group;
			v_elem.clear();
		}

		elem.InsertData(Data[i]);	
		next_group = atoi(Data[0][0].c_str());
		v_elem.emplace_back(elem);
	
	}*/
	MONOSERVERLIST.emplace_back(v_elem);
	return TRUE;
}
