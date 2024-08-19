#pragma once
#include"../Global/PacketDefinition.h"
#include"Conn.h"
#include<Windows.h>
#include<mutex>

class PacketProcessBase {
public:
	PacketProcessBase()
	{

	}
	virtual ~PacketProcessBase()
	{

	}
	virtual BOOL ProcessPacket(Conn* ptr) = 0;
private:
	virtual BOOL ProcessSignal(char* packet, Conn* ptr) = 0;
};

class PacketProcess : public PacketProcessBase
{
public:
	PacketProcess();
	virtual ~PacketProcess();
	virtual BOOL ProcessPacket(Conn* ptr) override;
private:
	virtual BOOL ProcessSignal(char* packet, Conn* ptr) override;
private:
	static std::mutex m_signal_lock; // 여러 쓰레드에서 접근 하더라도 한번에 한번씩으로 제한 하기 위함
};

