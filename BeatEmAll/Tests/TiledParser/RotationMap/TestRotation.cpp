#include "Catch\catch.hpp"
#include "Tiled\TiledParser\TiledMapParser.h"

#include "GameObjects\TileMap.h"

#include "SFML\Graphics.hpp"

TEST_CASE("Test the rotation of tiles", "[tiledmap]")
{
	TiledMapParser mapParser("Tests\\TiledParser\\RotationMap\\rotationMap.tmx");

	TiledMap tiledMap;
	REQUIRE(mapParser.parse(tiledMap));
	TileMap newTileMap;
	std::string sourcePreffix = "Tests\\TiledParser\\RotationMap\\";
	REQUIRE(TileMap::newTileMap(tiledMap, newTileMap, sourcePreffix));

	const std::map<int, sf::Texture*> textures = newTileMap.textures();
	const std::vector<Tile*> tiles = newTileMap.tiles();

	REQUIRE(textures.size() == 1);
	REQUIRE(tiles.size() == 4);

	//REQUIRE(tiles[0]->sprite().getTransform().getMatrix);

	//sf::RenderWindow rw(sf::VideoMode(1280, 640), "SFML Works! YAY!");

	//while (rw.isOpen())
	//{
	//	sf::Event event;
	//	while (rw.pollEvent(event))
	//	{
	//		if (event.type == sf::Event::Closed)
	//			rw.close();
	//	}


	//	rw.draw(newTileMap);
	//	rw.display();
	//}
}