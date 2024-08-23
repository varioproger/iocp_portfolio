#pragma once
#include"Singleton.h"
#include"ReadBase.h"
#include"TXTRead.h"
#include"CSVRead.h"
#include"BinRead.h"
#include<memory>
class ReadManager : public Singleton<ReadManager> {
public:
	ReadManager();
	virtual ~ReadManager() = default;
	std::vector<std::vector<std::string>> DoRead(std::string&& path, std::string&& delims, std::string&& file_type);
	std::vector<char> DoRead(std::string&& path, std::string&& file_type);
private:
	void ChangeTXT();
	void ChangeCSV();
	void ChangeBin();
private:
	std::shared_ptr <TXTRead> m_txt;
	std::shared_ptr <CSVRead> m_csv;
	std::shared_ptr <BinRead> m_bin;
	std::shared_ptr <ReadBase> m_read;
};

#define READMANAGER ReadManager::getInstance()