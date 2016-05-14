#pragma once

#include <string>

#include "Tiled\TiledMap.h"

class TiledMapParser
{
private:
	std::string _xmlLocation;

public:

	TiledMapParser(const std::string& tileMap) { _xmlLocation = tileMap; };

	bool parse(TiledMap& tiledMap);

	std::string getXmlLocation() const { return _xmlLocation; };
};