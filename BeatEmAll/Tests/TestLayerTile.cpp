#include "Catch\catch.hpp"
#include "Tiled\TiledLayerTile.h"

TEST_CASE("Parsing from Tiled Map Editor (LayerTile)", "[layertile]")
{
	// 7 Not Flipped
	CHECK_FALSE(TiledLayerTile::isDFlipped(7));
	CHECK_FALSE(TiledLayerTile::isHFlipped(7));
	CHECK_FALSE(TiledLayerTile::isVFlipped(7));

	// 7 Flipped Vertically = 1073741831
	CHECK(TiledLayerTile::isVFlipped(1073741831));
	CHECK_FALSE(TiledLayerTile::isDFlipped(1073741831));
	CHECK_FALSE(TiledLayerTile::isHFlipped(1073741831));

	// 7 Flipped Horizontally = 2147483655
	CHECK(TiledLayerTile::isHFlipped(2147483655));
	CHECK_FALSE(TiledLayerTile::isVFlipped(2147483655));
	CHECK_FALSE(TiledLayerTile::isDFlipped(2147483655));

	// 7 Flipped Diagonally = 536870919
	CHECK(TiledLayerTile::isDFlipped(536870919));
	CHECK_FALSE(TiledLayerTile::isVFlipped(536870919));
	CHECK_FALSE(TiledLayerTile::isHFlipped(536870919));

	// 7 Flipped Hor and Ver tically = 3221225479
	CHECK(TiledLayerTile::isVFlipped(3221225479));
	CHECK(TiledLayerTile::isHFlipped(3221225479));
	CHECK_FALSE(TiledLayerTile::isDFlipped(3221225479));

	TiledLayerTile notFlipped(7);
	CHECK_FALSE((notFlipped.dFlipped() || notFlipped.vFlipped() || notFlipped.hFlipped()));

	TiledLayerTile vFlipped(1073741831);
	CHECK(vFlipped.gid() == 7);
	CHECK(vFlipped.vFlipped());

	TiledLayerTile hFlipped(2147483655);
	CHECK(hFlipped.gid() == 7);

	TiledLayerTile vhFlipped(3221225479);
	CHECK(vhFlipped.gid() == 7);
	CHECK_FALSE(vhFlipped.dFlipped());

	TiledLayerTile dFlipped(536870919);
	CHECK(dFlipped.gid() == 7);
	CHECK(dFlipped.dFlipped());

	TiledLayerTile dFlippedNoArgsConstructor;
	dFlippedNoArgsConstructor.setGid(536870919);
	CHECK(dFlipped.gid() == 7);
	CHECK(dFlipped.dFlipped());
}