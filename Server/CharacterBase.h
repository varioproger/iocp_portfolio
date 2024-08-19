#pragma once
#include"Inven.h"
#include"Equipment.h"
#include"SRWLock.h"

class CharacterBase
{
public:
	CharacterBase();
	virtual ~CharacterBase();
protected:
	virtual void SetBasicInfo() = 0;
protected:
	CharacterBasicInfo m_basic_info; 
	Inven m_inven; // 인벤 
	Equipment m_equip; // 장비 장착
protected:
	SRWLock m_lock;
};

