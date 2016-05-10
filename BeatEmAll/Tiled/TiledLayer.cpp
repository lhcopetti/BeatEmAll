
#include "Tiled\TiledLayer.h"


TiledLayer::TiledLayer(std::string name, int width, int height)
{
	_name = name;
	_width = width;
	_height = height;

	_tiles = new TiledLayerTile*[_height];
	for (int i = 0; i < height; i++)
		_tiles[i] = new TiledLayerTile[_width];
}

TiledLayer::~TiledLayer()
{
	for (int i = 0; i < _height; i++)
		delete[] _tiles[i];
	delete _tiles;
}