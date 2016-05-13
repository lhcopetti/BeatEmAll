#pragma once
#include "SFML\Graphics.hpp"

using namespace sf;

class Tile : public sf::Drawable
{
private:

	int _width, _height;
	int _x, _y;
	sf::Sprite* _tileSprite;
	
	virtual void draw(RenderTarget& target, RenderStates states) const;

public:
	Tile(int width, int height, int x, int y, sf::Sprite* tileSprite);
	
	int x() const { return _x; };
	int y() const { return _y; };

	int width() const { return _width; };
	int height() const { return _height; };

	const sf::Sprite& sprite() const { return *_tileSprite; };
};