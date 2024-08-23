#pragma once
#include"ReadBase.h"

class BinRead : public ReadBase
{
public:
	BinRead();
	virtual ~BinRead();
	virtual std::vector<std::vector<std::string>> DoRead(std::string&& path, std::string&& delims) override;
	virtual std::vector<char> DoRead(std::string&& path) override;
};

