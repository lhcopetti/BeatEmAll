#pragma once

#include "Tiled\TiledImageTile.h"
#include "Tiled\TiledLayerTile.h"

#include <vector>
#include <map>

class TiledMap
{
	friend class TiledMapParser;
private:
	std::map<std::string, TiledImageTile*> _imageTiles;
	std::vector<TiledLayerTile*> _layerTile;

	void addToImageTiles(std::string idKey, TiledImageTile* imageTiles);
	void addToLayerTile(TiledLayerTile* layerTile);

public:
	TiledMap() {}
	~TiledMap() {}

	const std::map<std::string, TiledImageTile*>& getImageTiles() const { return _imageTiles; };
	const std::vector<TiledLayerTile*>& getLayerTiles() const { return _layerTile; };
};