#pragma once

#include "Box2D\Box2D.h"
#include "IA\Steering\Steerable.h"
#include "IA\Steering\SteeringBehavior.h"

namespace IA
{
	namespace Steering
	{
		class WanderBehavior : public IA::Steering::SteeringBehavior
		{

		public:
			WanderBehavior(float circleRadius);
			virtual b2Vec2 compute(const IA::Steering::Steerable& steerable);

		private:
			const float _circleRadius;
			b2Vec2 _displacement;
			float _wanderAngle;
			static float _wanderAngleChange;
		};
	}
}