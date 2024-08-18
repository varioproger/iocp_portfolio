#pragma once
#include"Equip.h"
#include<vector>
#include<memory>

class Equipment
{
public:
	Equipment();
	virtual ~Equipment();

private:
	// ���� �� �κ� ���̿����� ����Ұ��̱� ������ ���� shared�� �� �ʿ䰡 ����
	// ���� ĭ�� �������̱� ������ vector�� ���°��̴� �����ϰ� ������.
	std::vector<std::unique_ptr<Equip>> m_litem; 
};

