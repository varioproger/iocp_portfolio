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
};

class PacketProcess : public PacketProcessBase
{
public:
	PacketProcess();
	virtual ~PacketProcess();
	virtual BOOL ProcessPacket(Conn* ptr) override;
private:
	BOOL ProcessSignal(char* packet, Conn* ptr);
	BOOL ProcessMove(char* packet, Conn* ptr);
	BOOL ProcessUseItem(char* packet, Conn* ptr);
	BOOL ProcessRootItem(char* packet, Conn* ptr);
	BOOL ProcessAttack(char* packet, Conn* ptr);
private:
	static std::mutex m_signal_lock; // 여러 쓰레드에서 접근 하더라도 한번에 한번씩으로 제한 하기 위함 
	static std::mutex m_rootitem_lock; // 여러 쓰레드에서 접근 하더라도 한번에 한번씩으로 제한 하기 위함 

	// PVE 나 PVP의 경우 내가 공격하는 도중 아이템이나 스킬을 사용할 경우, 이 순서가 패킷이 들어온 순서대로 순차적으로 처리해야만 한다.
	// 그래서 서로의 락과의 연결고리가 필요하다.
	static std::mutex m_move_lock; // 여러 쓰레드에서 접근 하더라도 한번에 한번씩으로 제한 하기 위함 
	static std::mutex m_useitem_lock; // 여러 쓰레드에서 접근 하더라도 한번에 한번씩으로 제한 하기 위함 
	static std::mutex m_attack_lock; // 여러 쓰레드에서 접근 하더라도 한번에 한번씩으로 제한 하기 위함 
};

