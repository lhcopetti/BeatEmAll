#include "Catch\catch.hpp"

#include "Collision\CollisionCategory.h"

TEST_CASE("CollisionCategory Interface", "[collision]")
{
	Collision::CollisionCategory coll;

	REQUIRE(coll.getCategories().size() == 0);
	REQUIRE(coll.load("Tests\\Collision\\mockCollisionCategory.xml"));

	CHECK(coll.getCategoryValue("CAT_BOUNDARY") == 0x0001);
	CHECK(coll.getCategoryValue("CAT_BULLET")	== 0x0008);
	CHECK(coll.getCategoryValue("CAT_PLAYER")	== 0x0002);
	CHECK(coll.getCategoryValue("CAT_ENEMY")	== 0x0004);

	{
		std::vector<std::string> vec1 = { "CAT_BOUNDARY", "CAT_ENEMY" };
		CHECK(coll.getCategoryValue(vec1) == (0x0001 | 0x0004));
	}

	{
		std::vector<std::string> vec1 = { "CAT_BOUNDARY", "CAT_ENEMY", "CAT_BULLET" };
		CHECK(coll.getCategoryValue(vec1) == (0x0001 | 0x0004 | 0x0008));
	}

	{
		std::vector<std::string> vec1 = { "CAT_ENEMY", "CAT_PLAYER" };
		CHECK(coll.getCategoryValue(vec1) == (0x0002 | 0x0004));
	}

	{
		std::vector<std::string> vec1 = { "CAT_ENEMY", "UNEXISTENT_KEY" };
		CHECK(coll.getCategoryValue(vec1) == (0x0004));
	}
}