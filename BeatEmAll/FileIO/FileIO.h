#pragma once
#include <string>

namespace FileInputOutput
{
	class FileIO
	{
	public:
		static const std::string FileIO::readAllText(const std::string& filePath);
	};
}