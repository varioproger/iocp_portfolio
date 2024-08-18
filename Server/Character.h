#pragma once
#include"Inven.h"
#include"Equipment.h"
#include"SRWLock.h"

class Character
{
public:
	Character();
	~Character();
private:
	Inven m_inven; // 인벤
	Equipment m_equip; // 장비 장착
private:
	SRWLock m_lock;
};

