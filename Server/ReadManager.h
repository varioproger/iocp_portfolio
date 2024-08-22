#pragma once
#include"Singleton.h"
#include"ReadBase.h"
#include"TXTRead.h"
#include"CSVRead.h"

class ReadManager : public Singleton<ReadManager>{
public:
	ReadManager();
	virtual ~ReadManager();
	std::vector<std::vector<std::string>> DoRead(std::string&& Path, std::string&& Delims, std::string&& extension);

private:
	void ChangeTXT();
	void ChangeCSV();
private:
	TXTRead* m_txt;
	CSVRead* m_csv;
	ReadBase* m_read;
};

#define READMANAGER ReadManager::getInstance()