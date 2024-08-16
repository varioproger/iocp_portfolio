#include "pch.h"
#include "WRecv.h"

WRecv::WRecv()
{
	Clear();
}

WRecv::~WRecv()
{

}
BOOL WRecv::Recv()
{
	if (Buf == nullptr || Sock == NULL || Over.ptr == nullptr)
	{
		return FALSE;
	}
	int len = 0;
	memset(Buf, 0, strlen(Buf));

	if (RecvBytes < sizeof(int)) //맨 앞에 패킷 사이즈 만큼 못 읽었거나 int 값 한개 이거나
	{
		len = sizeof(int) - RecvBytes;
	}
	else  // 사이즈 패킷 다 읽고 그 뒤에 패킷 데이터를 읽고 있는것
	{
		len = PacketSize - RecvBytes;
	}
	return Recv(Buf + RecvBytes, len);
}


ECSocketResult WRecv::CompleteRecv(int _Bytes)
{
	RecvBytes += _Bytes;
	if (RecvBytes == sizeof(int))
	{
		memcpy(&PacketSize, Buf, sizeof(int));
	}
	if (RecvBytes == PacketSize)
	{
		RecvBytes = 0;
		PacketSize = 0;
		return ECSocketResult::FINISHED;
	}
	return ECSocketResult::UNFINISHED;
}

void WRecv::Clear()
{
	Sock = 0;
	PacketSize = 0;
	RecvBytes = 0;
	if (Buf)
	{
		delete[] Buf;
	}
	Buf = nullptr;
	memset(&Over, 0, sizeof(WSAOverLapped_EX));
}

char* WRecv::GetBuf()
{
	return Buf;
}

BOOL WRecv::SetBuf(char* _Ptr)
{
	if (Buf == nullptr)
	{
		Buf = _Ptr;
		return TRUE;
	}
	return FALSE;
}

BOOL WRecv::SetOverlapped(PVOID _Ptr)
{
	if (Over.ptr == nullptr)
	{
		Over.ptr = _Ptr;
		Over.type = ECIoType::IO_RECV;
		return TRUE;
	}
	return FALSE;
}

BOOL WRecv::SetSocket(SOCKET _Sock)
{
	if (Sock == NULL)
	{
		Sock = _Sock;
		return TRUE;
	}
	return FALSE;
}

BOOL WRecv::Recv(char* _Buf, int _Len)
{
	DWORD recvbyte;
	DWORD flag = 0;
	/*
	WSARecv시에 생성키, 전송 바이트 수, 에러 코드 , OVERLAPPED 구조체 포인터를 하나의 엔트리로 만들어 입출력 완료 큐(I/O Completion Queue)에 엔큐한다

	OVERLAPPED 구조체에 해당 정보를 담아서 엔큐 하기 때문에 그전에 객체를 미리 비워 놓는것이다.
	꼭 그래야 하는건 아니지만 더 안전하기 때문이다
	*/
	memset(&Over.overlapped, 0, sizeof(WSAOVERLAPPED));

	WBuf.buf = _Buf;
	WBuf.len = _Len;

	int retval = WSARecv(Sock, &WBuf, 1, &recvbyte, &flag, &Over.overlapped, nullptr);
	if (retval == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			Clear();
			return FALSE;
		}
	}
	return TRUE;
}