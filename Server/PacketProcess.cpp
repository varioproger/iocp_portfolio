#include "PacketProcess.h"
#include<iostream>

std::mutex PacketProcess::m_signal_lock;

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
		default:
			return FALSE;
	}
}

BOOL PacketProcess::ProcessSignal(char* packet, Conn* ptr)
{
	std::lock_guard<std::mutex> lock(m_signal_lock);
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
