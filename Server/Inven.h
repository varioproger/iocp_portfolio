#pragma once
#include"ItemBase.h"
#include<list>
#include<memory>

class Inven
{
public:
	Inven();
	virtual ~Inven();
	void Add();
	void Create();
	void Delete();
	void Use();
	void Swap();
private:
	std::list<std::unique_ptr<ItemBase>> m_litem;
};

