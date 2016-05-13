#pragma once

#include "Tiled\TiledImageTile.h"
#include "Tiled\TiledLayerTile.h"

#include <vector>
#include <map>

class TiledMap
{
	friend class TiledMapParser;
private:

	int _height, _width;
	std::map<int, TiledImageTile*> _imageTiles;
	std::vector<TiledLayerTile*> _layerTile;



public:
	TiledMap() {}
	~TiledMap() {}

	const std::map<int, TiledImageTile*>& getImageTiles() const { return _imageTiles; };
	const std::vector<TiledLayerTile*>& getLayerTiles() const { return _layerTile; };

	void addToImageTiles(int idKey, TiledImageTile* imageTiles);
	void addToLayerTile(TiledLayerTile* layerTile);

	int height() const { return _height; };
	int width() const { return _width; };
};