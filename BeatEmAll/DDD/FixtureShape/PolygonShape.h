#pragma once
#include "DDD\FixtureShape\FixtureShape.h"

#include "SFML\System\Vector2.hpp"

namespace DDD
{
	class PolygonShape : public FixtureShape
	{
	public:
		PolygonShape(float hx, float hy, b2Vec2 center, float angle) :
			FixtureShape(SHAPE_POLYGON),
			_hx(hx), _hy(hy),
			_center(center),
			_angle(angle) {}

		const float _hx, _hy;
		const b2Vec2 _center;
		const float _angle;
	};
}