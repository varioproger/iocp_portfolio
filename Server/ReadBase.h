#pragma once
#include<vector>
#include<string>
//Strategy Interface class
class ReadBase {
public:
	virtual ~ReadBase() = default;
	virtual std::vector<std::vector<std::string>> DoRead(std::string Path, std::string Delims) = 0;
};