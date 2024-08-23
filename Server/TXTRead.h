#pragma once
#include"ReadBase.h"

class TXTRead : public ReadBase
{
public:
	TXTRead();
	virtual~TXTRead();
	virtual std::vector<std::vector<std::string>> DoRead(std::string&& path, std::string&& delims) override;
	virtual std::vector<char> DoRead(std::string&& path) override;
};