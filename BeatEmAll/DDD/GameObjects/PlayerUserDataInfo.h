#pragma once
#include "DDD\UserDataInfo.h"

namespace DDD
{
	namespace GameComponent
	{
		class PlayerUserDataInfo : public UserDataInfo
		{
		public:
			PlayerUserDataInfo(float velocity, float runningVelocity, float health) :
				_velocity(velocity),
				_runningVelocity(runningVelocity),
				_health(health)
			{ }

			const float _velocity;
			const float _runningVelocity;
			const float _health;
		};
	}
}