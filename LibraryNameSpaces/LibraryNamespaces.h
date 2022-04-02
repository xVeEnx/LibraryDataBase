#pragma once
#include <iostream>
namespace LibraryNamespaces {

	constexpr auto SEPARATOR = ";";
	static void error(const std::string& message) { std::cout << "ERROR! " << message; }
	static std::string getNextValue(std::string* line)
	{
		int end = line->find(SEPARATOR);
		std::string temp = line->substr(0, end);
		*line = line->substr(end + 1);
		return temp;
	}
}
