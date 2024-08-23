#pragma once
#include"ReadBase.h"
class CSVRead : public ReadBase
{
public:
	CSVRead();
	virtual~CSVRead();
	virtual std::vector<std::vector<std::string>> DoRead(std::string&& path, std::string&& delims) override;
	virtual  std::vector<char> DoRead(std::string&& path) override;
};

