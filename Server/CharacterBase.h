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
	Inven m_inven; // �κ�
	Equipment m_equip; // ��� ����
protected:
	SRWLock m_lock;
};

