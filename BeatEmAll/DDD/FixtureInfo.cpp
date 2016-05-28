#include "DDD\FixtureInfo.h"

using namespace DDD;

FixtureInfo::FixtureInfo(float density, float restitution, float radius) :
	_fType(CIRCLE),
	_radius(radius),
	_density(density),
	_restitution(restitution),
	_hx(0.f), _hy(0.f)
{
}


FixtureInfo::FixtureInfo(float density, float restitution, float hx, float hy) :
	_fType(POLYGON),
	_hx(hx), _hy(hy),
	_density(density),
	_restitution(restitution),
	_radius(0.f)
{
}