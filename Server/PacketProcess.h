#pragma once

class PacketProcess
{
public:
	PacketProcess();
	~PacketProcess();
	void ProcessSocket();
	int UnPackPacket();
};