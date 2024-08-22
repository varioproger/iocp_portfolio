#include "ReadManager.h"

ReadManager::ReadManager() : m_read(0)
{
	m_txt = new TXTRead();
	m_csv = new CSVRead();
}
ReadManager::~ReadManager()
{ 
	if (m_txt)
	{
		delete m_txt;
	}
	if (m_csv)
	{
		delete m_csv;
	}
}


std::vector<std::vector<std::string>> ReadManager::DoRead(std::string&& Path, std::string&& Delims, std::string&& extension)
{
	if (extension.compare("txt") == 0 )
	{
		ChangeTXT();
	}
	else if (extension.compare("csv") == 0)
	{
		ChangeCSV();
	}
	return std::move(m_read->DoRead(Path, Delims));
}
void ReadManager::ChangeTXT()
{
	m_read = (ReadBase*)m_txt;
}
void ReadManager::ChangeCSV()
{
	m_read = (ReadBase*)m_csv;
}
