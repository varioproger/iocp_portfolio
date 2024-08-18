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
	Inven m_inven; // �κ�
	Equipment m_equip; // ��� ����
private:
	SRWLock m_lock;
};

