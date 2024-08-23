#include "BinRead.h"
#include<fstream>
#include<algorithm>
BinRead::BinRead()
{
}

BinRead::~BinRead()
{
}
std::vector<std::vector<std::string>> BinRead::DoRead(std::string&& path, std::string&& delims)
{
	return std::vector<std::vector<std::string>>();
}
std::vector<char> BinRead::DoRead(std::string&& path)
{
	std::vector<char> Data;
	Data.clear();
	std::ifstream file(path, std::ios::binary);
	if (file.is_open())
	{
		std::vector<char> buffer(std::istreambuf_iterator<char>(file), {});
		std::copy(Data.begin(), Data.end(), std::back_inserter(buffer));
	}
	file.close();
	return Data;
}
