#pragma once
#include"ItemBase.h"
#include<list>
#include<memory>

class Inven // CharacterBase가 Lock을 가지고 있으므로 필요가 없다.
{
public:
	Inven();
	virtual ~Inven();
	void Add(); // 아이템 추가
	void Create(ItemType type,int item_idx); // 아이템 생성
	void Delete(); // 아이템 삭제
	void Use(); // 아이템 사용
	void Swap(); // 인벤 위치 변경
	std::shared_ptr<ItemBase> Select();// 아이템 확인
	void clear();
private:
	std::list<std::shared_ptr<ItemBase>> m_litem; // 캐릭터와의 거래나 경매장 등 내가 아닌 타인 과 교류가 있기 때문에 shared로 한다.
};

