#pragma once

struct BaseMsg {
	unsigned short Size;
	unsigned __int64 Type;
	unsigned int Tick;
};
constexpr int SizeBaseMsg = sizeof(BaseMsg);