#include "Tiled\TiledLayerTile.h"


#define FLIPPED_HORIZONTALLY_FLAG	0x8;
#define FLIPPED_VERTICALLY_FLAG		0x4;
#define FLIPPED_DIAGONALLY_FLAG		0x2;

TiledLayerTile::TiledLayerTile()
{
	_gid = -1;

	_hFlipped = false;
	_vFlipped = false;
	_dFlipped = false;
}

TiledLayerTile::TiledLayerTile(unsigned int gid)
{
	init(gid);
}

void TiledLayerTile::init(unsigned int gid)
{
	_hFlipped = TiledLayerTile::isHFlipped(gid);
	_vFlipped = TiledLayerTile::isVFlipped(gid);
	_dFlipped = TiledLayerTile::isDFlipped(gid);

	/* Remove Flipped Flags from the Tiles' IDs */
	_gid = gid & (0x0FFFFFFF);
}

bool TiledLayerTile::isHFlipped(unsigned int gid)
{
	return (gid >> 28) & FLIPPED_HORIZONTALLY_FLAG;
}

bool TiledLayerTile::isVFlipped(unsigned int gid)
{
	return (gid >> 28) & FLIPPED_VERTICALLY_FLAG;
}

bool TiledLayerTile::isDFlipped(unsigned int gid)
{
	return (gid >> 28) & FLIPPED_DIAGONALLY_FLAG;
}

void TiledLayerTile::setGid(unsigned int gid)
{
	init(gid);
}