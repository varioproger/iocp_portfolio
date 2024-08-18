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
	std::list<std::shared_ptr<ItemBase>> m_litem; // 캐릭터와의 거래나 경매장 등 내가 아닌 타인 과 교류가 있기 때문에 shared로 한다.
};

