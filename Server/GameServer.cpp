#include "GameServer.h"
#include<GlobalDef.h>
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
		retval = GetQueuedCompletionStatus(hCP, &cbTransferrd, &ulkey, (LPOVERLAPPED*)&overlapped, INFINITE);
		if (ulkey == 1)//PostStopSignal()로 보낸값
		{
			break;
		}
		if (retval == 0 || cbTransferrd == 0)
		{
			if (retval == 0)
			{
				DWORD temp1, temp2;
				WSAGetOverlappedResult(ulkey, &overlapped->overlapped, &temp1, false, &temp2);
			}
			//Event->ConEnd((Conn*)overlapped->ptr);
			continue;
		}
		//Conn* conn = (Conn*)overlapped->ptr;
		switch (overlapped->type)
		{
		case ECIoType::IO_RECV:
			//if (conn->GetRecv().CompleteRecv(conn->GetSocket(), cbTransferrd) == ECSocketResult::FINISHED)
			//{
			//	//Event->AnalyzeProtocol(conn);
			//}
			//else
			//{
			//	continue;
			//}
			break;
		case ECIoType::IO_SEND:
			/*if (conn->GetSend().CompleteSend(conn->GetSocket(), cbTransferrd) == ECSocketResult::SOC_ERROR)
			{
				printf("Send Eror\n");
			}*/
			continue;
		default:
			break;
		}
	/*	conn->GetRecv().FirstRecv(conn->GetSocket());*/
	}
	return;
}

int GameServer::CompleteSend(LPVOID conn, int Bytes)
{
	return 0;
}

int GameServer::CompleteRecv(LPVOID conn, int Bytes)
{
	return 0;
}

void GameServer::CloseCon(LPVOID conn)
{
}
