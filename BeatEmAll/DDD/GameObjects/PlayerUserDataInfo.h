#pragma once
#include "DDD\UserDataInfo.h"

namespace DDD
{
	namespace GameComponent
	{
		class PlayerUserDataInfo : public UserDataInfo
		{
		public:
			PlayerUserDataInfo(float velocity, float health) :
				_velocity(velocity),
				_health(health)
			{ }

			const float _velocity;
			const float _health;
		};
	}
}