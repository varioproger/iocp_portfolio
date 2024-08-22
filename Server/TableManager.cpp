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
	emplace_back 함수는 전달된 인자를 완벽한 전달(perfect forwarding) 을 통해, 직접 unique_ptr<A> 의 생성자에 전달 해서,
	vector 맨 뒤에 unique_ptr<A> 객체를 생성해버리게 됩니다.
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