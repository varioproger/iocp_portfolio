#pragma once
#include"Item.h"
#include<list>
#include<memory>

class Inven
{
public:
	Inven();
	~Inven();
	void Add();
	void Create();
	void Delete();
	void Use();
	void Swap();
private:
	std::list<std::shared_ptr<Item>> m_litem;
};

