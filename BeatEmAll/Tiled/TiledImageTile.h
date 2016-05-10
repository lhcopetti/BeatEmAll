#pragma once

#include <string>

class TiledImageTile
{
private:
	int _height;
	int _width;
	std::string _source;

public:
	TiledImageTile(int height, int width, std::string source)
	{
		_height = height;
		_width = width;
		_source = source;
	}

	int height() const { return _height; };
	int width() const { return _width; };
	std::string source() const { return _source; };
};