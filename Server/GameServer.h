#pragma once
#pragma comment(lib,"TCP_Lib.lib")
#include<CompletionPort.h>

class GameServer : public CompletionPort
{
public:
	GameServer();
	virtual ~GameServer();
	virtual void WorkerThread(LPVOID arg) override;
	virtual int CompleteSend(LPVOID conn, int Bytes) override;
	virtual int CompleteRecv(LPVOID conn, int Bytes) override;
	virtual void CloseCon(LPVOID conn) override;
};
