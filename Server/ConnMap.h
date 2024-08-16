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
	std::shared_ptr<Conn>  Insert(SOCKET key);
	void Delete(Conn* key);

	// ��ü ���� .value()
	// ������ ���� ������ �ִ��� Ȯ�� .has_value()
	std::optional<std::shared_ptr<Conn>> Select(SOCKET key);

private:
	std::map<SOCKET, std::shared_ptr<Conn>> m_conn;
	CriticalSection m_lock;
};

