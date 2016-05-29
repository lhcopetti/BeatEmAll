#include "DDD\FixtureInfo.h"

#include "DDD\FixtureShape\CircleShape.h"
#include "DDD\FixtureShape\PolygonShape.h"

using namespace DDD;

FixtureInfo::FixtureInfo(float density, float restitution, float radius, b2Vec2 position) :
	_density(density),
	_restitution(restitution)
{
	_shape = new CircleShape(radius, position);
}


FixtureInfo::FixtureInfo(float density, float restitution, float hx, float hy, b2Vec2 center, float angle) :
	_density(density),
	_restitution(restitution)
{
	_shape = new PolygonShape(hx, hy, center, angle);
}