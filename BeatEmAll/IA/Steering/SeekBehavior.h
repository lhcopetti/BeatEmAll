#pragma once

#include "Box2D\Box2D.h"
#include "IA\Steering\Steerable.h"
#include "IA\Steering\SteeringBehavior.h"

namespace IA
{
	namespace Steering
	{
		class SeekBehavior : IA::Steering::SteeringBehavior
		{
		private:
			const b2Vec2 _target;
			float _slowingRadius;

		public:
			SeekBehavior(b2Vec2 target, float slowingRadius = 0) 
				: _target(target),
				_slowingRadius(slowingRadius)
			{}
			virtual b2Vec2 compute(const IA::Steering::Steerable& steerable);

		private:
		};
	}
}