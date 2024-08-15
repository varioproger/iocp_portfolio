#include "pch.h"
#include "WSend.h"

WSend::WSend()
{
	Clear();
}

WSend::~WSend()
{
}

BOOL WSend::StartSend(char* _Buf, int _Size)
{
	if (Sock == NULL || Over.ptr == nullptr || _Buf == nullptr || _Size <= 0)
	{
		return -1;
	}
	memcpy(Buf, _Buf, _Size);
	SendSize = _Size;
	return Send(Buf + SendBytes, SendSize - SendBytes);
}

ECSocketResult WSend::CompleteSend(int _Bytes)
{
	SendBytes += _Bytes;
	if (SendSize == SendBytes) // 패킷 전부 다 보냈다.
	{
		memset(Buf, 0, SendSize);
		SendBytes = 0;
		SendSize = 0;
		return ECSocketResult::FINISHED;
	}
	else
	{
		if (Send() == FALSE)
		{
			ECSocketResult::SOC_ERROR;
		}
	}
	return ECSocketResult::UNFINISHED;
}

void WSend::Clear()
{
	Sock = 0;
	SendBytes = 0;
	SendSize = 0;
	if (Buf)
	{
		delete[] Buf;
	}
	Buf = nullptr;
	memset(&Over, 0, sizeof(WSAOverLapped_EX));

}

BOOL WSend::SetSocket(SOCKET _Sock)
{
	if (Sock == NULL)
	{
		Sock = _Sock;
		return TRUE;
	}
	return FALSE;
}

BOOL WSend::SetOverlapped(PVOID _Ptr)
{
	if (Over.ptr == nullptr)
	{
		Over.ptr = _Ptr;
		Over.type = ECIoType::IO_SEND;
		return TRUE;
	}
	return FALSE;
}

BOOL WSend::SetBuf(char* _Buf)
{
	if (Buf == nullptr)
	{
		Buf = _Buf;
		return TRUE;
	}
	return FALSE;
}

BOOL WSend::Send()
{
	return Send(Buf + SendBytes, SendSize - SendBytes);
}

BOOL WSend::Send(char* _Buf, int _Len)
{
	DWORD sendbyte;

	memset(&Over.overlapped, 0, sizeof(WSAOVERLAPPED));

	WBuf.buf = _Buf;
	WBuf.len = _Len;
	int retval = WSASend(Sock, &WBuf, 1, &sendbyte, 0, &Over.overlapped, nullptr);
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