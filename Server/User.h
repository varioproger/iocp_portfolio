﻿#pragma once
#include"CharacterBase.h"
#include<vector>
#include<memory>
#include"SRWLock.h"
class User
{
public:
	User();
	virtual ~User();
	SRWLock& GetLock();
private:
	std::vector<std::shared_ptr<CharacterBase>> m_vcharacter; // 한 계정에 캐릭터가 여러개 일 수 있기 때문에 
private:
	SRWLock m_lock;
};

