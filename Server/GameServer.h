#pragma once
#pragma comment(lib,"TCP_Lib.lib")
#include<CompletionPort.h>

class GameServer : public CompletionPort
{
public:
	GameServer();
	virtual ~GameServer();
	virtual void WorkerThread(LPVOID arg) override;
	virtual ECSocketResult CompleteSend(LPVOID conn, int bytes) override;
	virtual ECSocketResult CompleteRecv(LPVOID conn, int bytes) override;
	virtual void CloseCon(LPVOID conn) override;
};
