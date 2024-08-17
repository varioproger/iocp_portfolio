#pragma once
#include"Character.h"
#include<vector>
#include<memory>
#include"SRWLock.h"
class User
{
public:
	User();
	~User();
private:
	std::vector<std::shared_ptr<Character>> m_vcharacter; // �� ������ ĳ���Ͱ� ������ �� �� �ֱ� ������
private:
	SRWLock m_lock;
};

