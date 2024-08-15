#pragma once
#include"Singleton.h"
#include"Conn.h"
#include<memory>
#include<map>
#include<mutex>

class ConnMap : public Singleton<ConnMap>
{
public:
	std::shared_ptr<Conn> Create(SOCKET sock);
	void Insert(SOCKET sock);
	void Delete(SOCKET sock);
	std::shared_ptr<Conn> Select();

private:
	std::map<int, std::shared_ptr<Conn>> m_conn;
	std::mutex m_lock;
};

