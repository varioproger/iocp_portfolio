#pragma once
#include<vector>
#include<string>

//Strategy Interface class
class ReadBase {
public:
	virtual ~ReadBase() = default;
	virtual std::vector<char> DoRead(std::string&& path) = 0;
	virtual std::vector<std::vector<std::string>> DoRead(std::string&& path, std::string&& delims) = 0;
};