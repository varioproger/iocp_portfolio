#pragma once
#include"ItemBase.h"

class Equip : public ItemBase
{
public:
	Equip();
	~Equip();
private:
	EquipType type;
};

