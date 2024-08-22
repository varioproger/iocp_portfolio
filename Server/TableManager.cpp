#include "TableManager.h"

TableManager ::TableManager()
{
	v_table.clear();
}
TableManager::~TableManager()
{
	v_table.clear();
}
void TableManager::init()
{
	/*
	emplace_back �Լ��� ���޵� ���ڸ� �Ϻ��� ����(perfect forwarding) �� ����, ���� unique_ptr<A> �� �����ڿ� ���� �ؼ�,
	vector �� �ڿ� unique_ptr<A> ��ü�� �����ع����� �˴ϴ�.
	*/
	v_table.emplace_back(std::make_unique<TBServerList>());
}
void TableManager::SetInfo()
{
	for (int i = 0; i < v_table.size(); i++)
	{
		v_table[i]->SetInfo();
	}
}