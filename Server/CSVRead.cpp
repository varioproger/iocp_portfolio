#include "CSVRead.h"
#include <vector>
#include <string>
#include <fstream>

CSVRead::CSVRead()
{
}

CSVRead::~CSVRead()
{
}

std::vector<std::vector<std::string>> CSVRead::DoRead(std::string Path, std::string Delims)
{
	std::vector<std::vector<std::string>> OutPut;
	std::ifstream file;
	std::string str;
	std::vector<std::string> elem;
	elem.clear();
	OutPut.clear();

	file.open(Path);
	if (file.is_open())
	{
		while (std::getline(file, str))
		{
			if (str[0] != '/' && str.length() > 0)
			{
				std::string::size_type begIdx, endIdx;
				// search beginning of the first word
				begIdx = str.find_first_not_of(Delims);
				// while beginning of a word found
				while (begIdx != std::string::npos) {
					// search end of the actual word
					endIdx = str.find_first_of(Delims, begIdx);
					if (endIdx == std::string::npos) {
						// end of word is end of line
						endIdx = str.length();
					}
					elem.push_back(str.substr(begIdx, endIdx - begIdx));
					// search beginning of the next word
					begIdx = str.find_first_not_of(Delims, endIdx);
				}
				OutPut.push_back(elem);
				elem.clear();
			}
		}
	}
	file.close();
	return OutPut;
}
