#include <iostream>
#include <string>
#include <regex>

std::string ltrim(std::string str) {
	return std::regex_replace(str, std::regex("^\\s+"), std::string(""));
}

std::string rtrim(std::string str) {
	return std::regex_replace(str, std::regex("\\s+$"), std::string(""));
}

std::string trim(std::string str) {
	return ltrim(rtrim(str));
}