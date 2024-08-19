#pragma once
#include"Singleton.h"
#include"User.h"
#include<map>
#include<mutex>
#include<memory>

// 현재 접속중인 유저 map 
class UserMap : public Singleton<UserMap>
{
public:
	virtual ~UserMap();
private:
	std::map<int, std::shared_ptr<User>> m_muser;
	std::mutex m_lock;
};

