#pragma once
#include"Character.h"
#include"Singleton.h"
#include<map>
#include<mutex>
#include<memory>

class CharacterMap : public Singleton<CharacterMap>
{
public:
	~CharacterMap();
private:
	std::map<int, std::shared_ptr<Character>> m_mcharacter;
	std::mutex m_lock;
};

