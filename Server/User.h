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
	std::shared_ptr<Character> m_cur_character; // ���� ���� ���� ĳ����
	std::vector<std::shared_ptr<Character>> m_vcharacter; // �� ������ ĳ���Ͱ� ������ �� �� �ֱ� ������
};

