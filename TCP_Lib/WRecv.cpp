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

	if (RecvBytes < sizeof(int)) //�� �տ� ��Ŷ ������ ��ŭ �� �о��ų� int �� �Ѱ� �̰ų�
	{
		len = sizeof(int) - RecvBytes;
	}
	else  // ������ ��Ŷ �� �а� �� �ڿ� ��Ŷ �����͸� �а� �ִ°�
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
	WSARecv�ÿ� ����Ű, ���� ����Ʈ ��, ���� �ڵ� , OVERLAPPED ����ü �����͸� �ϳ��� ��Ʈ���� ����� ����� �Ϸ� ť(I/O Completion Queue)�� ��ť�Ѵ�

	OVERLAPPED ����ü�� �ش� ������ ��Ƽ� ��ť �ϱ� ������ ������ ��ü�� �̸� ��� ���°��̴�.
	�� �׷��� �ϴ°� �ƴ����� �� �����ϱ� �����̴�
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