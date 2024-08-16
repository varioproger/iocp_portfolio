#pragma once
#include"Singleton.h"
#include"CriticalSection.h"
#include"Conn.h"
#include<memory>
#include<map>
#include <optional>

class ConnMap : public Singleton<ConnMap>
{
public:
	Conn* Insert(SOCKET key);
	void Delete(Conn* key);

	// 객체 접근 .value()
	// 실제로 값을 가지고 있는지 확인 .has_value()
	std::optional<Conn*> Select(SOCKET key);

private:
	std::map<SOCKET, Conn*> m_conn;
	CriticalSection m_lock;
};

