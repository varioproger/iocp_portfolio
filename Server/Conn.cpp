#include "Conn.h"
#include"ServerGlobalDef.h"
#include"SRWLockGuard.h"
#include"../Global/PacketDefinition.h"

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
}

SRWLock& Conn::GetRecvLock()
{
	return m_recv_lock;
}
SRWLock& Conn::GetSendLock()
{
	return m_send_lock;
}
std::mutex& Conn::GetActionLock()
{
	return m_action_lock;
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
	SRWLockExGuard lock(&m_recv_lock);
	int len = 0;
	if (m_recv_packet_size == m_recv_bytes)
	{
		ClearRecv();
	}
	if (m_recv_bytes < SizeBaseMsg) //맨 앞에 패킷 사이즈 만큼 못 읽었거나 int 값 한개 이거나
	{
		len = SizeBaseMsg - m_recv_bytes;
	}
	else  // 사이즈 패킷 다 읽고 그 뒤에 패킷 데이터를 읽고 있는것
	{
		len = m_recv_packet_size - m_recv_bytes;
	}
	return Recv(m_recv_overlapped.m_buf + m_recv_bytes, len);
}

BOOL Conn::StartSend(char* buf, int size)
{
	SRWLockExGuard lock(&m_send_lock);
	ClearSend();
	
	memcpy(m_send_overlapped.m_buf, buf, size);
	m_send_packet_size = size;
	return Send(m_send_overlapped.m_buf + m_send_bytes, m_send_packet_size - m_send_bytes);
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
	WSARecv시에 생성키, 전송 바이트 수, 에러 코드 , OVERLAPPED 구조체 포인터를 하나의 엔트리로 만들어 입출력 완료 큐(I/O Completion Queue)에 엔큐한다

	OVERLAPPED 구조체에 해당 정보를 담아서 엔큐 하기 때문에 그전에 객체를 미리 비워 놓는것이다.
	꼭 그래야 하는건 아니지만 더 안전하기 때문이다
	*/
	memset(&m_recv_overlapped.m_overlapped, 0, sizeof(WSAOVERLAPPED));

	m_recv_overlapped.m_wbuf.buf = buf;
	m_recv_overlapped.m_wbuf.len = len;

	int retval = WSARecv(m_sock, &m_recv_overlapped.m_wbuf, 1, &recvbyte, &flag, &m_recv_overlapped.m_overlapped, nullptr);
	if (retval == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL Conn::Send(char* buf, int len)
{
	DWORD recvbyte;
	DWORD flag = 0;
	/*
	WSARecv시에 생성키, 전송 바이트 수, 에러 코드 , OVERLAPPED 구조체 포인터를 하나의 엔트리로 만들어 입출력 완료 큐(I/O Completion Queue)에 엔큐한다

	OVERLAPPED 구조체에 해당 정보를 담아서 엔큐 하기 때문에 그전에 객체를 미리 비워 놓는것이다.
	꼭 그래야 하는건 아니지만 더 안전하기 때문이다
	*/
	memset(&m_send_overlapped.m_overlapped, 0, sizeof(WSAOVERLAPPED));

	m_send_overlapped.m_wbuf.buf = buf;
	m_send_overlapped.m_wbuf.len = len;

	int retval = WSARecv(m_sock, &m_send_overlapped.m_wbuf, 1, &recvbyte, &flag, &m_send_overlapped.m_overlapped, nullptr);
	if (retval == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
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
