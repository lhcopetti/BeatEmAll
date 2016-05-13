#include "Catch\catch.hpp"
#include "Tiled\TiledParser\TiledMapParser.h"

#include "GameObjects\TileMap.h"

#include "SFML\Graphics.hpp"

TEST_CASE("Test the loading of Tile maps", "[tiledmap]")
{
	TiledMapParser mapParser("Tests\\TiledParser\\SmallMap\\littletestmap.tmx");

	TiledMap tiledMap;
	REQUIRE(mapParser.parse(tiledMap));
	TileMap newTileMap;
	std::string sourcePreffix = "Tests\\TiledParser\\SmallMap\\";
	REQUIRE(TileMap::newTileMap(tiledMap, newTileMap, sourcePreffix));

	const std::map<int, sf::Texture*> textures = newTileMap.textures();
	const std::vector<Tile*> tiles = newTileMap.tiles();

	REQUIRE(textures.size() == 3);

	CHECK(textures.at(0)->getSize().x == 64);
	CHECK(textures.at(0)->getSize().y == 64);

	CHECK(textures.at(1)->getSize().x == 64);
	CHECK(textures.at(1)->getSize().y == 64);

	REQUIRE(tiles.size() == 16);

	CHECK(tiles[0]->x() == 0);
	CHECK(tiles[0]->y() == 0);
	CHECK(tiles[0]->height() == 64);
	CHECK(tiles[0]->width() == 64);

	CHECK(tiles[15]->x() == 3);
	CHECK(tiles[15]->y() == 3);
	CHECK(tiles[15]->height() == 64);
	CHECK(tiles[15]->width() == 64);
}