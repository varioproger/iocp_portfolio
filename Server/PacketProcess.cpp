#include "PacketProcess.h"
#include<iostream>
#include"SRWLockGuard.h"

std::mutex PacketProcess::m_signal_lock;
std::mutex PacketProcess::m_move_lock;
std::mutex PacketProcess::m_useitem_lock; 
std::mutex PacketProcess::m_rootitem_lock; 
std::mutex PacketProcess::m_attack_lock; 

PacketProcess::PacketProcess()
{
}

PacketProcess::~PacketProcess()
{
}

BOOL PacketProcess::ProcessPacket(Conn* ptr)
{
	// 여러 스레드에서 ProcessPacket 함수를 접근하는거에 대한 제한을 두더라도 이 함수가 끝날때 까지 잡아두는건 매우 비효울 적이다. 

	char* packet = ptr->GetRecvBuf(); // Recv 버퍼는 StartRecv가 호출이 되어야 변경이 되기 때문에 그냥 접근해도 문제 없다.
	BaseMsg* msg = (BaseMsg*)packet;
	switch (msg->Type)
	{
		case PacketType::PT_Signal:
			return ProcessSignal(packet, ptr);
		case PacketType::PT_Move:
			return ProcessMove(packet, ptr);
		case PacketType::PT_UseItem:
			return ProcessUseItem(packet, ptr);
		case PacketType::PT_RootItem:
			return ProcessRootItem(packet, ptr);
		case PacketType::PT_Attack:
			return ProcessAttack(packet, ptr);
		default:
			return FALSE;
	}
}

BOOL PacketProcess::ProcessSignal(char* packet, Conn* ptr)
{
	SRWLockExGuard user_lock(&ptr->m_user->GetLock()); //한 유저가 동시에 시그널을 보낼 순 있지만 순차적으로 처리, 하지만 다른 유저가 시그널을 보낼 경우는 그냥 패스
	std::lock_guard lock(m_signal_lock); // 한번의 하나의 signal을 순차적으로 처리
	SignalMsg* msg = (SignalMsg*)packet;

	std::cout << msg->msg << std::endl;

	SignalMsg sm;
	memset(&sm, 0, sizeof(SignalMsg));
	sm.Type = PacketType::PT_Signal;
	sm.Size = sizeof(SignalMsg);
	strncpy_s(sm.msg, MaxMsgSize, "From Server", MaxMsgSize);
	ptr->AddSend((BaseMsg*)&sm);
	return TRUE;
}

BOOL PacketProcess::ProcessMove(char* packet, Conn* ptr)
{
	SRWLockExGuard user_lock(&ptr->m_user->GetLock()); // 시그널과 같은 이유
	std::scoped_lock lock(m_attack_lock, m_move_lock); // 공격을 하는 동안에는 이동 할 수 없기 때문
	return 0;
}
BOOL PacketProcess::ProcessUseItem(char* packet, Conn* ptr)
{
	SRWLockExGuard user_lock(&ptr->m_user->GetLock()); // 시그널과 같은 이유
	std::scoped_lock lock(m_attack_lock, m_useitem_lock); // 공격을 하는 동안에는 아이템 사용 할 수 없기 때문
	return 0;
}
BOOL PacketProcess::ProcessRootItem(char* packet, Conn* ptr)
{
	SRWLockExGuard user_lock(&ptr->m_user->GetLock()); // 시그널과 같은 이유
	std::scoped_lock lock(m_attack_lock, m_useitem_lock,m_rootitem_lock); // 공격을 하는 동안이나 아이템 사용중에는 아이템 루팅을 할 수 없기 때문
	return 0;
}

BOOL PacketProcess::ProcessAttack(char* packet, Conn* ptr)
{
	SRWLockExGuard user_lock(&ptr->m_user->GetLock()); // 시그널과 같은 이유
	std::unique_lock lock(m_attack_lock); // 이동, 아이템사용, 아이템 루팅에 이미 m_attack_lock을 걸기 때문에 여기는 따로 안걸어줘도 된다.
	return 0;
}
