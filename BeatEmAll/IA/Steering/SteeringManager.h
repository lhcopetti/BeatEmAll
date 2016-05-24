#pragma once

#include "GameObjects\Player.h"
#include "IA\Steering\WanderBehavior.h"

namespace IA
{
	namespace Steering
	{
		class SteeringManager
		{
		private:
			GameComponent::Player* _player;
			b2Vec2 _steering;

			b2Vec2 doSeek(b2Vec2 position);

			b2Vec2 truncate(b2Vec2 vector, float maxValue) const;

			WanderBehavior _wander;

		public:
			SteeringManager() : _wander(8.f)
			{
				_steering = b2Vec2_zero;
				_player = nullptr;
			}

			~SteeringManager();

			void seek(b2Vec2 position);

			b2Vec2 getSteering() const { return _steering; }

			void setPlayer(GameComponent::Player* player) { _player = player; }

		};
	}
}