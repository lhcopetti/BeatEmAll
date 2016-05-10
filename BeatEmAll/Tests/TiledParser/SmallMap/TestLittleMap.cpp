#include "Catch\catch.hpp"
#include "Tiled\TiledParser\TiledMapParser.h"
#include "Tiled\TiledMap.h"


TEST_CASE("Parse Little Map (.tmx)", "[tiledparser]")
{
	TiledMapParser mapParser("Tests\\TiledParser\\SmallMap\\littletestmap.tmx");

	TiledMap tiledMap;
	REQUIRE(mapParser.parse(tiledMap));

	const std::map<std::string, TiledImageTile*> imageTiles = tiledMap.getImageTiles();
	REQUIRE(imageTiles.find("0") != imageTiles.end());
	REQUIRE(imageTiles.find("1") != imageTiles.end());

	CHECK(strcmp(imageTiles.find("0")->second->source().c_str(), "assets/test_tile_001.png") == 0);
	CHECK(strcmp(imageTiles.find("1")->second->source().c_str(), "assets/test_tile_002.png") == 0);

	const std::vector<TiledLayerTile*> layerTiles = tiledMap.getLayerTiles();

	REQUIRE(layerTiles.size() == 16);
	CHECK(layerTiles[0]->gid() == 2);
	CHECK(layerTiles[1]->gid() == 1);
	CHECK(layerTiles[2]->gid() == 1);
	CHECK(layerTiles[3]->gid() == 2);
}