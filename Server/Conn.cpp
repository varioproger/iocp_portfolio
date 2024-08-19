#include "Conn.h"
#include"ServerGlobalDef.h"
#include"SRWLockGuard.h"

Conn::Conn(SOCKET sock) : m_sock(sock)
{
	m_recv_overlapped.m_type = ECIoType::IO_RECV;
	m_recv_overlapped.m_buf = new char[KB_4];
	ClearRecv();

	m_send_overlapped.m_type = ECIoType::IO_SEND;
	m_send_overlapped.m_buf = new char[KB_1];
	ClearSend();
}

Conn::~Conn()
{
	delete m_recv_overlapped.m_buf;
	m_recv_packet_size = 0;
	m_recv_bytes = 0;

	delete m_send_overlapped.m_buf;
	m_send_packet_size = 0;
	m_send_bytes = 0;
	closesocket(m_sock);
}

std::mutex& Conn::GetRecvLock()
{
	return m_recv_lock;
}
std::mutex& Conn::GetSendLock()
{
	return m_send_lock;
}
SOCKET Conn::GetSocket()
{
	return m_sock;
}

int Conn::GetRecvPacketSize()
{
	return m_recv_packet_size;
}

void Conn::SetRecvPacketSize(int size)
{
	m_recv_packet_size = size;
}

void Conn::ResetRecvPacketSize()
{
	m_recv_packet_size = 0;
}

int Conn::GetRecvBytes()
{
	return m_recv_bytes;
}

void Conn::AddRecvBytes(int bytes)
{
	m_recv_bytes += bytes;
}

void Conn::ResetRecvBytes()
{
	m_recv_bytes = 0;
}

char* Conn::GetRecvBuf()
{
	return m_recv_overlapped.m_buf;
}

void Conn::ResetRecvBuf()
{
	memset(m_recv_overlapped.m_buf, 0, KB_1);
}

int Conn::GetSendPacketSize()
{
	return m_send_packet_size;
}

void Conn::SetSendPacketSize(int size)
{
	m_send_packet_size = size;
}

void Conn::ResetSendPacketSize()
{
	m_send_packet_size = 0;
}

int Conn::GetSendBytes()
{
	return m_send_bytes;
}

void Conn::AddSendBytes(int bytes)
{
	m_send_bytes += bytes;
}

void Conn::ResetSendBytes()
{
	m_send_bytes = 0;
}

char* Conn::GetSendBuf()
{
	return m_send_overlapped.m_buf;
}

void Conn::ResetSendBuf()
{
	memset(m_send_overlapped.m_buf, 0, KB_1);
}

BOOL Conn::StartRecv()
{
	std::lock_guard<std::mutex> lock(m_recv_lock);
	int len = 0;
	if (m_recv_packet_size == m_recv_bytes)
	{
		ClearRecv();
	}
	if (m_recv_bytes < SizeBaseMsg) //�� �տ� ��Ŷ ������ ��ŭ �� �о��ų� int �� �Ѱ� �̰ų�
	{
		len = SizeBaseMsg - m_recv_bytes;
	}
	else  // ������ ��Ŷ �� �а� �� �ڿ� ��Ŷ �����͸� �а� �ִ°�
	{
		len = m_recv_packet_size - m_recv_bytes;
	}
	return Recv(m_recv_overlapped.m_buf + m_recv_bytes, len);
}


BOOL Conn::AddSend(BaseMsg* packet)
{
	std::lock_guard<std::mutex> lock(m_send_lock);
	if (m_send_queue.empty() == true)// ���� �������.
	{
		memcpy(m_send_overlapped.m_buf, (char*)packet, packet->Size);
		m_send_packet_size = packet->Size;
		return Send(m_send_overlapped.m_buf + m_send_bytes, m_send_packet_size - m_send_bytes);
	}
	else // ó���ؾ��ϴ� ��Ŷ�� ������ ����
	{
		m_send_queue.push(packet);
		return TRUE;
	}
}

BOOL Conn::PopSend()
{
	BaseMsg* msg = nullptr;
	ClearSend();
	if (m_send_queue.try_pop(msg))
	{
		std::lock_guard<std::mutex> lock(m_send_lock);
		memcpy(m_send_overlapped.m_buf, (char*)msg, msg->Size);
		m_send_packet_size = msg->Size;
		return Send(m_send_overlapped.m_buf + m_send_bytes, m_send_packet_size - m_send_bytes);
	}
	return TRUE;
}

BOOL Conn::SendLeft()
{
	return Send(m_send_overlapped.m_buf + m_send_bytes, m_send_packet_size - m_send_bytes);
}

BOOL Conn::Recv(char* buf, int len)
{
	DWORD recvbyte;
	DWORD flag = 0;
	/*
	WSARecv�ÿ� ����Ű, ���� ����Ʈ ��, ���� �ڵ� , OVERLAPPED ����ü �����͸� �ϳ��� ��Ʈ���� ����� ����� �Ϸ� ť(I/O Completion Queue)�� ��ť�Ѵ�

	OVERLAPPED ����ü�� �ش� ������ ��Ƽ� ��ť �ϱ� ������ ������ ��ü�� �̸� ��� ���°��̴�.
	�� �׷��� �ϴ°� �ƴ����� �� �����ϱ� �����̴�
	*/
	memset(&m_recv_overlapped.m_overlapped, 0, sizeof(WSAOVERLAPPED));

	m_recv_overlapped.m_wbuf.buf = buf;
	m_recv_overlapped.m_wbuf.len = len;

	int retval = WSARecv(m_sock, &m_recv_overlapped.m_wbuf, 1, &recvbyte, &flag, &m_recv_overlapped.m_overlapped, nullptr);
	if (retval == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			ClearRecv();
			return FALSE;
		}
	}
	return TRUE;
}

BOOL Conn::Send(char* buf, int len)
{
	/*
	WSASend�ÿ� ����Ű, ���� ����Ʈ ��, ���� �ڵ� , OVERLAPPED ����ü �����͸� �ϳ��� ��Ʈ���� ����� ����� �Ϸ� ť(I/O Completion Queue)�� ��ť�Ѵ�

	OVERLAPPED ����ü�� �ش� ������ ��Ƽ� ��ť �ϱ� ������ ������ ��ü�� �̸� ��� ���°��̴�.
	�� �׷��� �ϴ°� �ƴ����� �� �����ϱ� �����̴�
	*/
	DWORD sendbyte;

	memset(&m_send_overlapped.m_overlapped, 0, sizeof(WSAOVERLAPPED));

	m_send_overlapped.m_wbuf.buf = buf;
	m_send_overlapped.m_wbuf.len = len;
	int retval = WSASend(m_sock, &m_send_overlapped.m_wbuf, 1, &sendbyte, 0, &m_send_overlapped.m_overlapped, nullptr);
	if (retval == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			ClearSend();
			return FALSE;
		}
	}

	return TRUE;
}

void Conn::ClearRecv()
{
	memset(m_recv_overlapped.m_buf, 0, KB_4);
	m_recv_packet_size = 0;
	m_recv_bytes = 0;
}

void Conn::ClearSend()
{
	memset(m_send_overlapped.m_buf, 0, KB_1);
	m_send_packet_size = 0;
	m_send_bytes = 0;
}
