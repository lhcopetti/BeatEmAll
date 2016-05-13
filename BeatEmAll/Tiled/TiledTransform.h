#pragma once

#include "Tiled\TiledLayerTile.h"

#include "SFML\Graphics.hpp"

class TiledTransform
{
public:

	static int getAngleFromFlip(const TiledLayerTile& tiled);

	static int getAngleFromFlip(bool flipH, bool flipV, bool flipD);

	static void flip(sf::Sprite& sprite, bool flipH, bool flipV);
};