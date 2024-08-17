#pragma once
#include"Inven.h"
#include"Equipment.h"
class Character
{
public:
	Character();
	~Character();
private:
	Inven m_inven;
	Equipment m_equip;
};

