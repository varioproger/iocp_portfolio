#pragma comment(lib,"TCP_Lib.lib")
#include"PacketProcess.h"
#include"GameServer.h"
#include"ConnMap.h"
#include<vector>
#include<iostream>
#include <stdlib.h>
#include <ws2tcpip.h>

#define REGISTER_KEY (WM_USER+1)


#define START_SERVER(class_name , name) \
		class_name name; \
		name.WStartUp()

#define SET_SERVER(name , sock_name) \
		name.CreateSocket(); \
		name.Bind(sock_name);\
		name.Listen(sock_name)

BOOL CtrlHandler(DWORD fdwCtrlType)
{
	switch (fdwCtrlType)
	{
	case CTRL_C_EVENT:
		std::cout << "CTRL_C_EVENT" << std::endl;
		break;
	case CTRL_CLOSE_EVENT:
		std::cout << "CTRL_CLOSE_EVENT" << std::endl;
		break;
	case CTRL_LOGOFF_EVENT:
		std::cout << "CTRL_LOGOFF_EVENT" << std::endl;
		break;
	case CTRL_SHUTDOWN_EVENT:
		std::cout << "CTRL_SHUTDOWN_EVENT" << std::endl;
		break;
	case CTRL_BREAK_EVENT:
		std::cout << "CTRL_BREAK_EVENT" << std::endl;
		break;
	default:
		break;
	}

	return FALSE;

}

int main()
{
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE);
	std::vector< PacketProcess> PProcess;
	PProcess.clear();
	PProcess.emplace_back();

	START_SERVER(GameServer, GS);
	SOCKET sock = SET_SERVER(GS, sock);

	size_t CPU = GS.GetThreadCount();
	GS.CreateIOPort();
	GS.BeginThread<PacketProcess>(CPU, PProcess);

	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char str[32] = { 0 };
	printf("Start Listening\n");

	while (1)
	{
		client_sock = GS.Accept(sock, clientaddr, addrlen);
		if (client_sock == INVALID_SOCKET)
		{
			inet_ntop(AF_INET, &(clientaddr.sin_addr), str, INET_ADDRSTRLEN);
			printf("\n[TCP 서버] 클라이언트 접속 에러: IP 주소=%s, 포트 번호=%d\n",	str, ntohs(clientaddr.sin_port));
			memset(str, 0, sizeof(str));
			continue;
		}
		auto client_conn = ConnMap::getInstance()->Insert(client_sock);
		// 포인터가 다른 포인터 형식으로 변환될 수 있도록 합니다. 또한 정수 계열 형식이 포인터 형식으로 변환될 수 있도록 하고 그 반대로도 변환될 수 있도록 합니다.
		// shared_ptr을 reinterpret_cast 로 캐스팅이 안됨. 그렇다고 get으로 하면 use_count가 안오름. 그럼 shared_ptr 사용하는 의미가 없어짐.
		GS.Register(client_sock, reinterpret_cast<ULONG_PTR>(client_conn));

		client_conn->StartRecv();

	}
	GS.JoinThread();
	return 0;
}