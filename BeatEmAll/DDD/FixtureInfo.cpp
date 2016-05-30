#include "DDD\FixtureInfo.h"

#include "DDD\FixtureShape\CircleShape.h"
#include "DDD\FixtureShape\PolygonShape.h"
#include "DDD\FixtureShape\VerticesShape.h"

using namespace DDD;

FixtureInfo::FixtureInfo(float density, float restitution, float category, float maskBits) :
	_density(density),
	_restitution(restitution),
	_category(category),
	_maskBits(maskBits)
{

}

FixtureInfo::FixtureInfo(float density, float restitution, float category, float maskBits, float radius, b2Vec2 position) :
	_density(density),
	_restitution(restitution),
	_category(category),
	_maskBits(maskBits)
{
	_shape = new CircleShape(radius, position);
}


FixtureInfo::FixtureInfo(float density, float restitution, float category, float maskBits, float hx, float hy, b2Vec2 center, float angle) :
	_density(density),
	_restitution(restitution),
	_category(category),
	_maskBits(maskBits)
{
	_shape = new PolygonShape(hx, hy, center, angle);
}

FixtureInfo* FixtureInfo::newVerticesFixture(float density, float restitution, float category, float maskBits, std::vector<b2Vec2> vertices)
{
	FixtureInfo* fix = new FixtureInfo(density, restitution, category, maskBits);
	fix->_shape = new VerticesShape(vertices);
	return fix;
}