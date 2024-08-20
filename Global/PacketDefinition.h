#pragma once

enum PacketType {
	PT_Base,
	PT_Signal,
	PT_Move,
	PT_UseItem,
	PT_RootItem,
	PT_Attack,
	PT_None,
};
struct BaseMsg {
	unsigned short Size;
	unsigned __int64 Type;
	unsigned int Tick;
};
constexpr int SizeBaseMsg = sizeof(BaseMsg);

constexpr int MaxMsgSize =32;
struct SignalMsg : BaseMsg {
	char msg[MaxMsgSize];
};