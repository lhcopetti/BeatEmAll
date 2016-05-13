#include "Catch\catch.hpp"
#include "Tiled\TiledTransform.h"

TEST_CASE("Test Angle Transformation", "[tiled]")
{
	// TODO: Add diagonal flip
	bool vFlip = true;
	bool hFlip = true;

	CHECK(TiledTransform::getAngleFromFlip(!hFlip, !vFlip, false) == 0);
	CHECK(TiledTransform::getAngleFromFlip(!hFlip, vFlip, false) == 90);
	CHECK(TiledTransform::getAngleFromFlip(hFlip, !vFlip, false) == 270);
	CHECK(TiledTransform::getAngleFromFlip(hFlip, vFlip, false) == 180);
}