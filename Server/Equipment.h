#pragma once
#include"Item.h"
#include<list>
#include<memory>

class Equipment
{
public:
	Equipment();
	~Equipment();

private:
	std::list<std::shared_ptr<Item>> m_litem;
};

