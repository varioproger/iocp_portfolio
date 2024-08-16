#include "ConnMap.h"
#include"CSLockGuard.h"

std::shared_ptr<Conn>  ConnMap::Insert(SOCKET key)
{
	CSLockGuard lock(&m_lock);
	std::shared_ptr<Conn> conn = std::make_shared<Conn>(key);
	m_conn.insert(std::make_pair(key, conn));
	return conn;
}

void ConnMap::Delete(SOCKET key)
{
	CSLockGuard lock(&m_lock);
	m_conn.erase(m_conn.find(key));
}

std::optional<std::shared_ptr<Conn>>  ConnMap::Select(SOCKET key)
{
	CSLockGuard lock(&m_lock);
	auto it = m_conn.find(key);
	if (it != m_conn.end()) {
		return it->second;
	}

	// nullopt 는 <optional> 에 정의된 객체로 비어있는 optional 을 의미한다.
	return std::nullopt;
}
