#pragma once
#include "DDD\FixtureShape\FixtureShape.h"
#include "Box2D\Box2D.h"
#include <vector>

namespace DDD
{
	class VerticesShape : public FixtureShape
	{
	public:
		VerticesShape(std::vector<b2Vec2> vertices) :
			FixtureShape(SHAPE_VERTICES),
			_vertices(vertices) {}

		const std::vector<b2Vec2> _vertices;
	};
}