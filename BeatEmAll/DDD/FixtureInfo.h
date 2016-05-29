#pragma once
#include "Box2D\Box2D.h"
#include "DDD\FixtureShape\FixtureShape.h"
#include <vector>

namespace DDD
{
	class FixtureInfo
	{
	public:
		static FixtureInfo* newVerticesFixture(float density, float restitution, std::vector<b2Vec2> vertices);

		FixtureInfo(float density, float restitution, float radius, b2Vec2 position);
		FixtureInfo(float density, float restitution, float hx, float hy, b2Vec2 center, float angle);

		const float _density;
		const float _restitution;

		const FixtureShape* _shape;

	private:
		FixtureInfo(float density, float restitution);
	};
}