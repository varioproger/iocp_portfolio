#include "ConnMap.h"
#include"CSLockGuard.h"

ConnMap::~ConnMap()
{
	for (auto it = m_conn.begin(); it != m_conn.end(); it++)
	{
		delete it->second;
	}
	m_conn.clear();
}

Conn* ConnMap::Insert(SOCKET key)
{
	CSLockGuard lock(&m_lock);
	Conn* conn = new Conn(key);
	m_conn.insert(std::make_pair(key, conn));
	return conn;
}

void ConnMap::Delete(Conn* conn)
{
	CSLockGuard lock(&m_lock);
	m_conn.erase(m_conn.find(conn->GetSocket()));
}

std::optional<Conn*>  ConnMap::Select(SOCKET key)
{
	CSLockGuard lock(&m_lock);
	auto it = m_conn.find(key);
	if (it != m_conn.end()) {
		return it->second;
	}

	// nullopt �� <optional> �� ���ǵ� ��ü�� ����ִ� optional �� �ǹ��Ѵ�.
	return std::nullopt;
}
