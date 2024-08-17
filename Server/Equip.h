#pragma once
#include"ItemBase.h"


enum EquipType {
	Face,
	Hair,
	Armor,
	Helmet,
	Glove,
	Shoes,
};

class Equip : public ItemBase
{
public:
	Equip();
	~Equip();
private:
	EquipType type;
};

