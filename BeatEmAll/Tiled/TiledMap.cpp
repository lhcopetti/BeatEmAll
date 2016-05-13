#include "Tiled\TiledMap.h"

void TiledMap::addToImageTiles(int idKey, TiledImageTile* imageTiles)
{
	_imageTiles[idKey] = imageTiles;
}

void TiledMap::addToLayerTile(TiledLayerTile* layerTile)
{
	_layerTile.push_back(layerTile);
}