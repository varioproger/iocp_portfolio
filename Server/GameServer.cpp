#include"../Global/PacketDefinition.h"
#include "GameServer.h"
#include"ConnMap.h"
#include"PacketProcess.h"
#include<iostream>
GameServer::GameServer()
{
}

GameServer::~GameServer()
{
}

void GameServer::WorkerThread(LPVOID arg)
{
	PacketProcessBase* packet = (PacketProcessBase*)arg;
	int retval = 0;
	while (1)
	{
		DWORD cbTransferrd = 0;
		Conn* Conn = nullptr;
		WSAOverLapped_EX* overlapped = nullptr;

		/*
* 		Returns nonzero (TRUE) if successful or zero (FALSE) otherwise.
*
		If *lpOverlapped is NULL, the function did not dequeue a completion packet from the completion port.
		In this case, the function does not store information in the variables pointed to by the lpNumberOfBytes
		and lpCompletionKey parameters, and their values are indeterminate.

		If *lpOverlapped is not NULL and the function dequeues a completion packet for a failed I/O operation from the completion port,
		the function stores information about the failed operation in the variables pointed to by
		lpNumberOfBytes, lpCompletionKey, and lpOverlapped.
		To get extended error information, call GetLastError.
		*/
		retval = GetQueuedCompletionStatus(hCP, &cbTransferrd, reinterpret_cast<ULONG_PTR*>(&Conn), reinterpret_cast<LPOVERLAPPED*>(&overlapped), INFINITE);
		if (retval == 0 || cbTransferrd == 0)
		{
			if (retval == 0)
			{
				//receives the number of bytes that were actually transferred by a send or receive operation, or by the WSAIoctl function.This parameter must not be a NULL pointer.
				DWORD lpcbTransfer;

				// A pointer to a 32-bit variable that will receive one or more flags that supplement the completion status.
				// initiated through WSARecv or WSARecvFrom, this parameter will contain the results value for lpFlags parameter
				// WSARecv : lpFlags : https://learn.microsoft.com/ko-kr/windows/win32/api/winsock2/nf-winsock2-wsarecv
				DWORD lpdwFlags;

				// retrieves the results of an overlapped operation on the specified socket.
				WSAGetOverlappedResult(Conn->GetSocket(), &overlapped->m_overlapped, &lpcbTransfer, false, &lpdwFlags);
			}
			CloseCon(Conn);
			continue;
		}
		switch (overlapped->m_type)
		{
		case ECIoType::IO_RECV:
		{
			ECSocketResult ret = CompleteRecv(Conn, cbTransferrd);
			if (ret == ECSocketResult::FINISHED)
			{
				if (packet->ProcessPacket(Conn) == FALSE)
				{
					printf("Recv Eror\n");
					CloseCon(Conn);
					continue;
				}
			}
			else if (ret == ECSocketResult::SOC_ERROR)
			{
				printf("Recv Eror\n");
				CloseCon(Conn);
				continue;
			}
		}
		break;
		case ECIoType::IO_SEND:
		{
			ECSocketResult ret = CompleteSend(Conn, cbTransferrd);
			if (ret == ECSocketResult::FINISHED)
			{
				if (Conn->PopSend() == FALSE) // Send가 완료되면 추가로 더 Send 할게 있는지 확인한 이후에 있으면 Send 다시 진행
				{
					printf("Send Eror\n");
					CloseCon(Conn);
				}
			}
			else if (ret == ECSocketResult::SOC_ERROR)
			{
				printf("Send Eror\n");
				CloseCon(Conn);
			}
			continue;
		}
		default:
			break;
		}
		Conn->StartRecv();
	}
	return;
}

ECSocketResult GameServer::CompleteSend(LPVOID conn, int bytes)
{
	Conn* ptr = (Conn*)conn;
	std::lock_guard lock(ptr->GetSendLock());
	int add_bytes = ptr->GetSendBytes() + bytes;
	int packet_size = ptr->GetSendPacketSize();
	ptr->AddSendBytes(bytes);

	if (add_bytes == packet_size) // 패킷 전부 다 보냈다.
	{
		return ECSocketResult::FINISHED;
	}
	else if (add_bytes < packet_size)
	{
		if (ptr->SendLeft() == FALSE)
		{
			ECSocketResult::SOC_ERROR;
		}
	}
	else
	{
		ECSocketResult::SOC_ERROR;
	}
	return ECSocketResult::UNFINISHED;
}

ECSocketResult GameServer::CompleteRecv(LPVOID conn, int bytes)
{
	Conn* ptr = (Conn*)conn;
	std::lock_guard lock(ptr->GetRecvLock());
	int add_bytes = ptr->GetRecvBytes() + bytes;
	int packet_size = ptr->GetRecvPacketSize();
	ptr->AddRecvBytes(bytes);

	if (add_bytes == SizeBaseMsg)
	{
		BaseMsg* msg = (BaseMsg*)ptr->GetRecvBuf();
		ptr->SetRecvPacketSize(msg->Size);
	}
	else if (add_bytes == packet_size)
	{
		return ECSocketResult::FINISHED;
	}
	else if (add_bytes > packet_size)
	{
		ECSocketResult::SOC_ERROR;
	}
	return ECSocketResult::UNFINISHED;
}

void GameServer::CloseCon(LPVOID conn)
{
	std::cout << "유저 접속 끊김" << std::endl;
	ConnMap::getInstance()->Delete((Conn*)conn);
}
