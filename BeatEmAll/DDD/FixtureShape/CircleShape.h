#pragma once
#include "DDD\FixtureShape\FixtureShape.h"

namespace DDD
{
	class CircleShape : public FixtureShape
	{
	public:
		CircleShape(float radius, b2Vec2 position) :
			FixtureShape(SHAPE_CIRCLE),
			_radius(radius),
			_position(position) { }

		const float _radius;
		const b2Vec2 _position;
	};
}