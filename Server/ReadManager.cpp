#include "ReadManager.h"

ReadManager::ReadManager() : m_read(0)
{
	m_txt = std::shared_ptr<TXTRead>();
	m_csv = std::shared_ptr<CSVRead>();
}


std::vector<std::vector<std::string>> ReadManager::DoRead(std::string&& path, std::string&& delims, std::string&& file_type)
{
	if (file_type.compare("txt") == 0)
	{
		ChangeTXT();
	}
	else if (file_type.compare("csv") == 0)
	{
		ChangeCSV();
	}
	else if (file_type.compare("bin") == 0)
	{
		ChangeBin();
	}
	return std::move(m_read->DoRead(std::move(path), std::move(delims)));

}
std::vector<char> ReadManager::DoRead(std::string&& path, std::string&& file_type)
{
	if (file_type.compare("bin") == 0)
	{
		ChangeBin();
	}
	return std::move(m_read->DoRead(std::move(path)));
}
void ReadManager::ChangeTXT()
{
	m_read = std::dynamic_pointer_cast<ReadBase>(m_txt);
}
void ReadManager::ChangeCSV()
{
	m_read = std::dynamic_pointer_cast<ReadBase>(m_csv);
}

void ReadManager::ChangeBin()
{
	m_read = std::dynamic_pointer_cast<ReadBase>(m_bin);
}
