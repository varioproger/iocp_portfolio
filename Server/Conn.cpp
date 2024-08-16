#include "Conn.h"
#include"ServerGlobalDef.h"
#include"SRWLockGuard.h"
#include"../Global/PacketDefinition.h"

Conn::Conn(SOCKET sock) : m_sock(sock)
{
	m_over.ptr = this;
	m_packet_recv_size = 0;
	m_recv_bytes = 0;
	memset(m_recv_buf,0, KB_4);

	m_packet_send_size = 0;
	m_send_bytes = 0;
	memset(m_send_buf, 0, KB_1);
}

Conn::~Conn()
{
	m_over.ptr = nullptr;
	m_packet_recv_size = 0;
	m_recv_bytes = 0;
	memset(m_recv_buf, 0, KB_4);

	m_packet_send_size = 0;
	m_send_bytes = 0;
	memset(m_send_buf, 0, KB_1);
}

SRWLock& Conn::GetLock()
{
	return m_lock;
}

SOCKET Conn::GetSocket()
{
	return m_sock;
}

BOOL Conn::StartRecv()
{
	SWRLockExGuard lock(&m_lock);
	m_over.type = ECIoType::IO_RECV;

	int len = 0;
	memset(m_recv_buf, 0, KB_4);

	if (m_recv_bytes < SizeBaseMsg) //맨 앞에 패킷 사이즈 만큼 못 읽었거나 int 값 한개 이거나
	{
		len = SizeBaseMsg - m_recv_bytes;
	}
	else  // 사이즈 패킷 다 읽고 그 뒤에 패킷 데이터를 읽고 있는것
	{
		len = m_packet_recv_size - m_recv_bytes;
	}
	return Recv(m_recv_buf + m_recv_bytes, len);
}

BOOL Conn::StartSend(char* buf, int size)
{
	m_over.type = ECIoType::IO_SEND;
	memcpy(m_send_buf, buf, size);
	m_packet_send_size = size;
	return Send(m_send_buf + m_send_bytes, m_packet_send_size - m_send_bytes);
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
	memset(&m_over.overlapped, 0, sizeof(WSAOVERLAPPED));

	m_wbuf.buf = buf;
	m_wbuf.len = len;

	int retval = WSARecv(m_sock, &m_wbuf, 1, &recvbyte, &flag, &m_over.overlapped, nullptr);
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
	memset(&m_over.overlapped, 0, sizeof(WSAOVERLAPPED));

	m_wbuf.buf = buf;
	m_wbuf.len = len;

	int retval = WSARecv(m_sock, &m_wbuf, 1, &recvbyte, &flag, &m_over.overlapped, nullptr);
	if (retval == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			return FALSE;
		}
	}
	return TRUE;
}
