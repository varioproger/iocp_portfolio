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
	std::vector<std::shared_ptr<Character>> m_vchar; // 한 계정에 캐릭터가 여러개 일 수 있기 때문에
};

