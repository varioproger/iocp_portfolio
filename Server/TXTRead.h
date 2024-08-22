#pragma once
#include"ReadBase.h"

class TXTRead : public ReadBase
{
public:
	TXTRead();
	virtual~TXTRead();
	virtual std::vector<std::vector<std::string>> DoRead(std::string Path, std::string Delims) override;
};