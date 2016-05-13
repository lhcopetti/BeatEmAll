#pragma once

#include <map>

#include "SFML\Graphics.hpp"

#include "GameObjects\Tile.h"
#include "Tiled\TiledMap.h"

class TileMap : public sf::Drawable
{
private:

	int _width, _height;
	std::map<int, sf::Texture*> _textures;
	std::vector<Tile*> _tiles;

public:
	TileMap();

	void setWidth(int width) { _width = width; };
	void setHeight(int height) { _height = height; };

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	static bool newTileMap(const TiledMap& tiledMap, TileMap& refMap, std::string& sourcePreffix);

	const std::vector<Tile*>& tiles() const { return _tiles; };
	const std::map<int, sf::Texture*>& textures() const { return _textures; };
};
