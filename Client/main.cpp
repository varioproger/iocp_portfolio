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
	// ������ ������ ���
	while (1) {

		memset(&signal, 0, sizeof(SignalMsg));
		// ������ �Է�
		printf("\n[���� ������] ");
		if (fgets(signal.msg, MaxMsgSize, stdin) == NULL)
			break;

		// '\n' ���� ����
		len = strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (strlen(buf) == 0)
			break;

		signal.Type = PacketType::PT_Signal;
		signal.Size = sizeof(SignalMsg);
		// ������ ������
		retval = client.Send(sock, (char*)&signal, signal.Size, 0);
		if (retval == SOCKET_ERROR) {
			break;
		}
		printf("[TCP Ŭ���̾�Ʈ] %d����Ʈ�� ���½��ϴ�.\n", retval);

		// ������ �ޱ�
		retval = client.Recvn(sock, buf, retval, 0);
		if (retval == SOCKET_ERROR)
		{
			break;
		}
		else if (retval == 0)
		{
			break;
		}
		// ���� ������ ���
		BaseMsg* msg = (BaseMsg*)buf;
		if (msg->Type == PacketType::PT_Signal)
		{
			SignalMsg* signal = (SignalMsg*)msg;
			printf("[TCP Ŭ���̾�Ʈ] %d����Ʈ�� �޾ҽ��ϴ�.\n", retval);
			printf("[���� ������] %s\n", signal->msg);
		}	
	}

	// closesocket()
	closesocket(sock);
	return 0;
}