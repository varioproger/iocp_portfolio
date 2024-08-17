#include "PacketProcess.h"
#include<iostream>

PacketProcess::PacketProcess()
{
}

PacketProcess::~PacketProcess()
{
}

BOOL PacketProcess::ProcessPacket(Conn* ptr)
{
	m_process_lock.lock(); 
	// ���� �����忡�� ProcessPacket �Լ��� �����ϴ°ſ� ���� ������ �δ��� �� �Լ��� ������ ���� ��Ƶδ°� �ſ� ��ȿ�� ���̴�.
	// �׷��� lock�� lock_guard�� �����ϰ� ���� �ʴ�. 

	char* packet = ptr->GetRecvBuf(); // Recv ���۴� StartRecv�� ȣ���� �Ǿ�� ������ �Ǳ� ������ �׳� �����ص� ���� ����.
	BaseMsg* msg = (BaseMsg*)packet;
	switch (msg->Type)
	{
		case PacketType::PT_Signal:
			return ProcessSignal(packet, ptr);
		default:
			m_process_lock.unlock();
			return FALSE;
	}
}

BOOL PacketProcess::ProcessSignal(char* packet, Conn* ptr)
{
	std::lock_guard<std::mutex> lock(m_signal_lock);
	SignalMsg* msg = (SignalMsg*)packet;
	m_process_lock.unlock();

	std::cout << msg->msg << std::endl;
	return FALSE;
}
