#include<iostream>
#include<vector>
#include<Windows.h>
#include"PacketProcess.h"


template<typename T>
BOOL BeginThread(int MaxThread, std::vector<T> t)
{

	for (int i = 0; i < MaxThread; i++)
	{
		t[i];
	}
	return TRUE;
}


int main()
{
	std::vector<PacketProcess> v_pp;
	v_pp.clear();
	for (int i = 0; i < 3; i++)
	{
		v_pp.emplace_back();
	}
	BeginThread<PacketProcess>(v_pp.size(), v_pp);
	return 0;
}