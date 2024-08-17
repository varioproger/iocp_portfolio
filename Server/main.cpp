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

	START_SERVER(GameServer, gs);
	SOCKET sock = SET_SERVER(gs, sock);

	size_t cpu_count = gs.GetThreadCount();
	gs.CreateIOPort();

	std::vector<PacketProcessBase*> vppbase;
	vppbase.clear();
	for (int i = 0; i < 1; i++)
	{
		vppbase.push_back((PacketProcessBase*)new PacketProcess());
	}
	if (gs.BeginThread<PacketProcessBase*>(2, vppbase) == FALSE)
	{
		printf("Begin Thread Failed\n");
	}

	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char str[32] = { 0 };
	printf("Start Listening\n");

	while (1)
	{
		client_sock = gs.Accept(sock, clientaddr, addrlen);
		inet_ntop(AF_INET, &(clientaddr.sin_addr), str, INET_ADDRSTRLEN);
		if (client_sock == INVALID_SOCKET)
		{
			printf("\n[TCP ����] Ŭ���̾�Ʈ ���� ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",	str, ntohs(clientaddr.sin_port));
			memset(str, 0, sizeof(str));
			continue;
		}
		auto client_conn = ConnMap::getInstance()->Insert(client_sock);
		// �����Ͱ� �ٸ� ������ �������� ��ȯ�� �� �ֵ��� �մϴ�. ���� ���� �迭 ������ ������ �������� ��ȯ�� �� �ֵ��� �ϰ� �� �ݴ�ε� ��ȯ�� �� �ֵ��� �մϴ�.
		// shared_ptr�� reinterpret_cast �� ĳ������ �ȵ�. �׷��ٰ� get���� �ϸ� use_count�� �ȿ���. �׷� shared_ptr ����ϴ� �ǹ̰� ������.
		gs.Register(client_sock, reinterpret_cast<ULONG_PTR>(client_conn));

		client_conn->StartRecv();
		printf("\n[TCP ����] Ŭ���̾�Ʈ ���� ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n", str, ntohs(clientaddr.sin_port));
		memset(str, 0, sizeof(str));
	}
	gs.JoinThread();
	return 0;
}