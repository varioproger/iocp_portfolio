#pragma once
#include"Character.h"
#include<vector>
#include<memory>

class User
{
public:
	User();
	~User();
private:
	std::vector<std::shared_ptr<Character>> m_vchar; // �� ������ ĳ���Ͱ� ������ �� �� �ֱ� ������
};

