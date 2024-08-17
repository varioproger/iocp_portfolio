#pragma comment(lib,"TCP_Lib.lib")
#include<BaseTCP.h>
#include<stdio.h>
#include"../Global/PacketDefinition.h"
#define BUFSIZE    512

int main()
{
	BaseTCP client;

	client.WStartUp();
	SOCKET sock = client.CreateSocket();
	SOCKADDR_IN Addr;
	client.Connect(sock, Addr);

	char buf[BUFSIZE + 1];
	int len = 0;
	int retval = 0;
	SignalMsg signal;
	// 서버와 데이터 통신
	while (1) {

		memset(&signal, 0, sizeof(SignalMsg));
		// 데이터 입력
		printf("\n[보낼 데이터] ");
		if (fgets(signal.msg, MaxMsgSize, stdin) == NULL)
			break;

		// '\n' 문자 제거
		len = strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (strlen(buf) == 0)
			break;

		signal.Type = PacketType::PT_Signal;
		signal.Size = sizeof(SignalMsg);
		// 데이터 보내기
		retval = client.Send(sock, (char*)&signal, signal.Size, 0);
		if (retval == SOCKET_ERROR) {
			break;
		}
		printf("[TCP 클라이언트] %d바이트를 보냈습니다.\n", retval);

		// 데이터 받기
		retval = client.Recvn(sock, buf, retval, 0);
		if (retval == SOCKET_ERROR)
		{
			break;
		}
		else if (retval == 0)
		{
			break;
		}
		// 받은 데이터 출력
		BaseMsg* msg = (BaseMsg*)buf;
		if (msg->Type == PacketType::PT_Signal)
		{
			SignalMsg* signal = (SignalMsg*)msg;
			printf("[TCP 클라이언트] %d바이트를 받았습니다.\n", retval);
			printf("[받은 데이터] %s\n", signal->msg);
		}	
	}

	// closesocket()
	closesocket(sock);
	return 0;
}