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

	// ��ü ���� .value()
	// ������ ���� ������ �ִ��� Ȯ�� .has_value()
	std::optional<Conn*> Select(SOCKET key);

private:
	std::map<SOCKET, Conn*> m_conn; //std::shared_ptr�� �ؾ� ������ ���Ѱ� ���������, IOCP Ű������ �� ���� ���� ������ �Ϲ� �����ͷ� ����
	CriticalSection m_lock;
};

