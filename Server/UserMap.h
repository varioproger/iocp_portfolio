#pragma once
#include"Singleton.h"
#include"User.h"
#include<map>
#include<mutex>
#include<memory>

class UserMap : public Singleton<UserMap>
{
public:
	~UserMap();
private:
	std::map<int, std::shared_ptr<User>> m_muser;
	std::mutex m_lock;
};

