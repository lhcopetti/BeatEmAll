#include "Tiled\TiledTransform.h"


int TiledTransform::getAngleFromFlip(const TiledLayerTile& tiled)
{
	return TiledTransform::getAngleFromFlip(tiled.hFlipped(), tiled.vFlipped(), tiled.dFlipped());
}

int TiledTransform::getAngleFromFlip(bool flipH, bool flipV, bool flipD)
{
	if (!flipH && !flipV) return 0;
	if (flipH && !flipV) return 270;
	if (!flipH && flipV)  return 90;
	return 180;
}

void TiledTransform::flip(sf::Sprite& sprite, bool flipH, bool flipV)
{
	sf::IntRect rect;
	const sf::Vector2u vec = sprite.getTexture()->getSize();

	int x = vec.x;
	int y = vec.y;
	int width = vec.x;
	int height = vec.y;

	if (flipH && flipV)
		rect = sf::IntRect(x, y, -width, -height);
	else if (flipH)
		rect = sf::IntRect(x, 0, -width, height);
	else if (flipV)
		rect = sf::IntRect(0, y, width, -height);
	else
		/* Do not rotate! */
		return;

	sprite.setTextureRect(rect);
}