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
	// ���� �����忡�� ProcessPacket �Լ��� �����ϴ°ſ� ���� ������ �δ��� �� �Լ��� ������ ���� ��Ƶδ°� �ſ� ��ȿ�� ���̴�.

	char* packet = ptr->GetRecvBuf(); // Recv ���۴� StartRecv�� ȣ���� �Ǿ�� ������ �Ǳ� ������ �׳� �����ص� ���� ����.
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
