﻿#pragma once
#include"Equip.h"
#include<vector>
#include<memory>

class Equipment // CharacterBase가 Lock을 가지고 있으므로 필요가 없다. 
{
public:
	Equipment();
	virtual ~Equipment();
	void EquipItem();
	void UnequipItem();
	void clear();
private:
	// 장착 과 인벤 사이에서만 사용할것이기 때문에 따로 shared를 할 필요가 없음
	// 장착 칸은 고정적이기 때문에 vector를 쓰는것이더 안전하고 빠르다.
	std::vector<std::unique_ptr<Equip>> m_litem; 
};

