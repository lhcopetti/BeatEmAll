#include "FileIO\FileIO.h"

#include <sstream>
#include <fstream>

using namespace FileInputOutput;

const std::string FileIO::readAllText(const std::string& filePath)
{
	std::ifstream file(filePath);
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	return buffer.str();
}