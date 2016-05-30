#pragma once
#include <string>
#include <vector>
#include <sstream>

namespace String
{
	static void split(const std::string& content, char delim, std::vector<std::string>& output)
	{
		std::stringstream ss(content);
		std::string item;
		while (std::getline(ss, item, delim))
			output.push_back(item);
	}
}