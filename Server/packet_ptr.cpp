#include<iostream>
#include"../Global/PacketDefinition.h"
#include<concurrent_queue.h>
#include<iostream>
concurrency::concurrent_queue<BaseMsg*> packet;

int main()
{
	BaseMsg* buf = nullptr;
	{
		SignalMsg sm;
		memset(&sm, 0, sizeof(SignalMsg));
		sm.Type = PacketType::PT_Signal;
		sm.Size = sizeof(SignalMsg);
		strncpy_s(sm.msg, MaxMsgSize, "abcd", 4);
		packet.push((BaseMsg*)&sm);
	}

	if (packet.try_pop(buf))
	{
		BaseMsg* msg = (BaseMsg*)buf;
		if (msg->Type == PT_Signal)
		{
			SignalMsg* signal = (SignalMsg*)msg;
			std::cout << signal->msg << std::endl;
		}
	}


	return 0;
}