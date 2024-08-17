#pragma once
#include"Equip.h"
#include<list>
#include<memory>

class Equipment
{
public:
	Equipment();
	~Equipment();

private:
	std::list<std::shared_ptr<Equip>> m_litem;
};

