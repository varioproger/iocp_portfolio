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
	Inven m_inven; // �κ�
	Equipment m_equip; // ��� ����
private:
	SRWLock m_lock;
};

