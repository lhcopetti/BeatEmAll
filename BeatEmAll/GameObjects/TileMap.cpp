
#include "GameObjects\TileMap.h"
#include "Tiled\TiledImageTile.h"
#include "Tiled\TiledTransform.h"

TileMap::TileMap()
{

}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (size_t i = 0; i < _tiles.size(); i++)
		target.draw(*_tiles[i]);
}

bool TileMap::newTileMap(const TiledMap& tiledMap, TileMap& refMap, std::string& sourcePreffix)
{
	for (auto kv = tiledMap.getImageTiles().begin(); kv != tiledMap.getImageTiles().end(); ++kv)
	{
		// Create Textures
		std::string& source = kv->second->source();
		sf::Texture* texture = new sf::Texture;
		texture->loadFromFile(sourcePreffix + source);
		refMap._textures[kv->first] = texture;
	}

	// Create sprites and assign them to each x, y. Tile Objects

	for (int x = 0; x < tiledMap.width(); x++)
		for (int y = 0; y < tiledMap.height(); y++)
		{
			const TiledLayerTile* layer = tiledMap.getLayerTiles()[y * tiledMap.width() + x];

			const std::map<int, TiledImageTile*>& imageMap = tiledMap.getImageTiles();

			/*
			TODO: Where does this -1 come from? Probably from the firstgid defined 
				in the tileset.
			*/
			sf::Texture* texture = refMap.textures().at(layer->gid() - 1);

			sf::Sprite* sprite = new sf::Sprite(*texture);
			/* Center Point */

			/* Flip the textures */
			TiledTransform::flip(*sprite, layer->hFlipped(), layer->vFlipped());

			Tile* newTile = new Tile(texture->getSize().x, texture->getSize().y, x, y, sprite);
			refMap._tiles.push_back(newTile);
		}

	return true;
}