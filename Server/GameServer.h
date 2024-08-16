#pragma once
#pragma comment(lib,"TCP_Lib.lib")
#include<CompletionPort.h>

class GameServer : public CompletionPort
{
public:
	GameServer();
	virtual ~GameServer();
	virtual void WorkerThread(LPVOID arg) override;
	virtual ECSocketResult CompleteSend(LPVOID conn, int Bytes) override;
	virtual ECSocketResult CompleteRecv(LPVOID conn, int Bytes) override;
	virtual void CloseCon(LPVOID conn) override;
};
