#pragma once
#include"ItemBase.h"

class Equip : public ItemBase
{
public:
	Equip();
	virtual ~Equip();
private:
	EquipType type;
};

