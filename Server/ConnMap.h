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
	virtual ~ConnMap();
	Conn* Insert(SOCKET key);
	void Delete(Conn* key);

	// 객체 접근 .value() 
	// 실제로 값을 가지고 있는지 확인 .has_value()
	std::optional<Conn*> Select(SOCKET key);

private:
	std::map<SOCKET, Conn*> m_conn; //std::shared_ptr로 해야 관리도 편한건 사실이지만, IOCP 키값으로 줄 수가 없기 때문에 일반 포인터로 진행
	CriticalSection m_lock;
};

