#include "Tiled\TiledMap.h"

void TiledMap::addToImageTiles(std::string idKey, TiledImageTile* imageTiles)
{
	_imageTiles[idKey] = imageTiles;
}

void TiledMap::addToLayerTile(TiledLayerTile* layerTile)
{
	_layerTile.push_back(layerTile);
}