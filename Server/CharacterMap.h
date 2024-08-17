#pragma once
#include"Character.h"
#include"Singleton.h"
#include<map>
#include<mutex>
#include<memory>

// 현재 접속중인 캐릭터 map
class CharacterMap : public Singleton<CharacterMap>
{
public:
	~CharacterMap();
private:
	std::map<int, std::shared_ptr<Character>> m_mcharacter;
	std::mutex m_lock;
};

