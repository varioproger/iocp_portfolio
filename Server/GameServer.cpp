#include "GameServer.h"
#include"ConnMap.h"
GameServer::GameServer()
{
}

GameServer::~GameServer()
{
}

void GameServer::WorkerThread(LPVOID arg)
{
	//EventManager* Event = (EventManager*)arg;
	int retval = 0;
	while (1)
	{
		DWORD cbTransferrd;
		ULONG_PTR ulkey;
		WSAOverLapped_EX* overlapped;

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
		retval = GetQueuedCompletionStatus(hCP, &cbTransferrd, &ulkey, (LPOVERLAPPED*)&overlapped, INFINITE);
		if (ulkey == 1)//PostStopSignal()로 보낸값
		{
			break;
		}
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
				WSAGetOverlappedResult(ulkey, &overlapped->overlapped, &lpcbTransfer, false, &lpdwFlags);
			}
			ConnMap::getInstance()->Delete((Conn*)overlapped->ptr);
			//Event->ConEnd((Conn*)overlapped->ptr);
			continue;
		}
		Conn* conn = (Conn*)overlapped->ptr;
		switch (overlapped->type)
		{
		case ECIoType::IO_RECV:
			if (CompleteRecv(conn, cbTransferrd) == ECSocketResult::FINISHED)
			{
				//Event->AnalyzeProtocol(conn);
			}
			else
			{
				continue;
			}		
			break;
		case ECIoType::IO_SEND:
			if (CompleteSend(conn, cbTransferrd) == ECSocketResult::SOC_ERROR)
			{
				printf("Send Eror\n");
			}
			continue;
		default:
			break;
		}
		conn->StartRecv();
	}
	return;
}

ECSocketResult GameServer::CompleteSend(LPVOID conn, int Bytes)
{
	return ECSocketResult::FINISHED;
}

ECSocketResult GameServer::CompleteRecv(LPVOID conn, int Bytes)
{
	return ECSocketResult::FINISHED;
}

void GameServer::CloseCon(LPVOID conn)
{
}
