#pragma once
#include "DDD\UserDataInfo.h"

namespace DDD
{
	namespace GameComponent
	{
		class EnemyDefaultUserDataInfo : public UserDataInfo
		{
		public:
			EnemyDefaultUserDataInfo(float velocity, float health) :
				_velocity(velocity),
				_health(health)
			{ }

			const float _velocity;
			const float _health;
		};
	}
}