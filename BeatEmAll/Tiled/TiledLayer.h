#pragma once

#include <string>

#include "Tiled\TiledLayerTile.h"

class TiledLayer
{
private:
	std::string _name;
	int _width;
	int _height;
	TiledLayerTile** _tiles;

public:
	TiledLayer(std::string name, int width, int height);
	~TiledLayer();

	TiledLayerTile** tiles() const { return _tiles; };
};