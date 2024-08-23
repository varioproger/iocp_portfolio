#include "BinRead.h"
#include<fstream>
#include<algorithm>

#include<iostream>
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
		file.seekg(0, std::ios_base::end);
		auto length = file.tellg();
		file.seekg(0, std::ios_base::beg);

		std::vector<char> buffer(length);
		file.read(reinterpret_cast<char*>(buffer.data()), length);

		std::copy(buffer.begin(), buffer.end(), std::back_inserter(Data));
	}
	file.close();
	return Data;
}
