#pragma once
#include "DDD\FixtureShape\FixtureShape.h"

namespace DDD
{
	class PolygonShape : public FixtureShape
	{
	public:
		PolygonShape(float hx, float hy, b2Vec2 center, float angle) :
			FixtureShape(SHAPE_BOX),
			_hx(hx), _hy(hy),
			_center(center),
			_angle(angle) {}

		const float _hx, _hy;
		const b2Vec2 _center;
		const float _angle;
	};
}