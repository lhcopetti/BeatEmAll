#pragma once

#include <vector>
#include "DDD\FixtureInfo.h"

namespace DDD
{
	enum PhysicsBodyType
	{
		DYNAMIC,
		STATIC
	};

	class PhysicsInfo
	{
	public:
		PhysicsInfo(PhysicsBodyType bodyType, bool isBullet, std::vector<DDD::FixtureInfo*> fixtures) :
			_type(bodyType),
			_isBullet(isBullet),
			_fixtures(fixtures) {}

		const PhysicsBodyType _type;
		const bool _isBullet;
		const std::vector<DDD::FixtureInfo*> _fixtures;
	};
}