#include "Catch\catch.hpp"

#include "DDD\InfoBuilder.h"
#include "DDD\Projectile\BulletUserDataInfo.h"

#include "DDD\Representation\DrawingRepresentation.h"

TEST_CASE("Test the loading of a info file", "[ddd]")
{
	/* TODO FIX */
	DDD::InfoBuilder builder(nullptr);

	REQUIRE(builder.load("Tests\\DDD\\Configuration\\xml_bullet.xml"));
	REQUIRE(builder.getInfoName() == "BulletInfo");
	REQUIRE(builder.getGameInfo() != nullptr);

	DDD::GameObjectInfo* gi = builder.getGameInfo();
	
	/* Physics */
	CHECK(gi->_physicsInfo->_type == DDD::DYNAMIC);
	CHECK(gi->_physicsInfo->_isBullet);

	std::vector<DDD::FixtureInfo*> fixs = gi->_physicsInfo->_fixtures;
	CHECK(fixs.size() == 1);

	/* Fixtures */
	DDD::FixtureInfo* fix = fixs[0];
	CHECK(fix->_restitution == 0.5f);
	CHECK(fix->_density == .1f);

	//CHECK(fix->_fType == DDD::CIRCLE);
	//CHECK(fix->_radius == 6.5f);

	/* Graphic */
	CHECK(gi->_graphicInfo->_origin == sf::Vector2f(4.0f, 3.0f));
	CHECK(!gi->_graphicInfo->_followRotation);

	CHECK(gi->_graphicInfo->_info->_type == DDD::DRAWING);
	const DDD::DrawingRepresentation* drawing = static_cast<const DDD::DrawingRepresentation*>(gi->_graphicInfo->_info);

	/* Representation Info */
	CHECK(drawing->_radius == 5.2f);
	CHECK(drawing->_color == sf::Color(255, 0, 240, 255));

	/* User Data Info */
	CHECK(gi->_userDataInfo != nullptr);
	const DDD::Projectile::BulletUserDataInfo* b = static_cast<const DDD::Projectile::BulletUserDataInfo*>(gi->_userDataInfo);

	CHECK(b->_lifeTime == 15.f);
}