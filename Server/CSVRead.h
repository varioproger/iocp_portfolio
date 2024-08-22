#pragma once
#include"ReadBase.h"
class CSVRead : public ReadBase
{
public:
	CSVRead();
	virtual~CSVRead();
	virtual std::vector<std::vector<std::string>> DoRead(std::string Path, std::string Delims) override;
};

