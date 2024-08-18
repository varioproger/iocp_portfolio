#pragma once
#include"Inven.h"
#include"Equipment.h"
#include"SRWLock.h"

class CharacterBase
{
public:
	CharacterBase();
	virtual ~CharacterBase();
private:
	Inven m_inven; // 인벤
	Equipment m_equip; // 장비 장착
private:
	SRWLock m_lock;
};

