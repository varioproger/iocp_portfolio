#pragma once
#include"CharacterBase.h"
#include<vector>
#include<memory>
#include"SRWLock.h"
class User
{
public:
	User();
	virtual ~User();
private:
	std::vector<std::shared_ptr<CharacterBase>> m_vcharacter; // �� ������ ĳ���Ͱ� ������ �� �� �ֱ� ������
private:
	SRWLock m_lock;
};

