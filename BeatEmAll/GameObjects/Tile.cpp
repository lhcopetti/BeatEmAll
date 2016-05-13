
#include "GameObjects\Tile.h"


Tile::Tile(int width, int height, int x, int y, sf::Sprite* tileSprite)
{
	_x = x;
	_y = y;
	_tileSprite = tileSprite;

	_height = height;
	_width = width;

	_tileSprite->setPosition(_x * _width, _y * _height);
}

void Tile::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(*_tileSprite, states);
}