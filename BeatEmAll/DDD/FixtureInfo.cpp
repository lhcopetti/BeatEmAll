#include "DDD\FixtureInfo.h"

#include "DDD\FixtureShape\CircleShape.h"
#include "DDD\FixtureShape\PolygonShape.h"
#include "DDD\FixtureShape\VerticesShape.h"

using namespace DDD;

FixtureInfo::FixtureInfo(float density, float restitution, float category, float maskBits, bool isSensor) :
	_density(density),
	_restitution(restitution),
	_category(category),
	_maskBits(maskBits),
	_isSensor(isSensor)
{

}

FixtureInfo::FixtureInfo(float density, float restitution, float category, float maskBits, bool isSensor, float radius, b2Vec2 position) :
	_density(density),
	_restitution(restitution),
	_category(category),
	_maskBits(maskBits),
	_isSensor(isSensor)
{
	_shape = new CircleShape(radius, position);
}


FixtureInfo::FixtureInfo(float density, float restitution, float category, float maskBits, bool isSensor, float hx, float hy, b2Vec2 center, float angle) :
	_density(density),
	_restitution(restitution),
	_category(category),
	_maskBits(maskBits),
	_isSensor(isSensor)
{
	_shape = new PolygonShape(hx, hy, center, angle);
}

FixtureInfo* FixtureInfo::newVerticesFixture(float density, float restitution, float category, float maskBits, bool isSensor, std::vector<b2Vec2> vertices)
{
	FixtureInfo* fix = new FixtureInfo(density, restitution, category, maskBits, isSensor);
	fix->_shape = new VerticesShape(vertices);
	return fix;
}