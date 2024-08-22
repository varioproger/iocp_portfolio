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
protected:
	SRWLock m_lock;
};

