#pragma once

#include "Box2D\Box2D.h"


namespace IA 
{
	namespace Steering
	{
		class Steerable;

		class SteeringBehavior
		{
		public:
			SteeringBehavior() {}
			virtual ~SteeringBehavior() {}

			virtual b2Vec2 compute(const IA::Steering::Steerable& steerable) = 0;

			static b2Vec2 SteeringBehavior::truncate(b2Vec2 vector, float maxValue)
			{
				float num = maxValue / vector.Length();

				num = num > 1.f ? 1.f : num;

				vector.x *= num;
				vector.y *= num;

				return vector;
			}
		};
	}
}