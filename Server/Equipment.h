#pragma once
#include"Equip.h"
#include<vector>
#include<memory>

class Equipment // CharacterBase�� Lock�� ������ �����Ƿ� �ʿ䰡 ����.
{
public:
	Equipment();
	virtual ~Equipment();
	void EquipItem();
	void UnequipItem();
	void clear();
private:
	// ���� �� �κ� ���̿����� ����Ұ��̱� ������ ���� shared�� �� �ʿ䰡 ����
	// ���� ĭ�� �������̱� ������ vector�� ���°��̴� �����ϰ� ������.
	std::vector<std::unique_ptr<Equip>> m_litem; 
};

