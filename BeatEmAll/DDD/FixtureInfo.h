#pragma once
#include "Box2D\Box2D.h"
#include "DDD\FixtureShape\FixtureShape.h"
#include <vector>

namespace DDD
{
	class FixtureInfo
	{
	public:
		static FixtureInfo* newVerticesFixture(float density, float restitution, float category, float maskBits, std::vector<b2Vec2> vertices);

		FixtureInfo(float density, float restitution, float category, float maskBits, float radius, b2Vec2 position);
		FixtureInfo(float density, float restitution, float category, float maskBits, float hx, float hy, b2Vec2 center, float angle);

		const float _density;
		const float _restitution;

		const FixtureShape* _shape;

		const uint16 _category;
		const uint16 _maskBits;

	private:
		FixtureInfo(float density, float restitution, float category, float maskBits);
	};
}