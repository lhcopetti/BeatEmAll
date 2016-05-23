#pragma once
#include "Box2D\Box2D.h"

namespace IA
{
	namespace Steering
	{
		class Steerable
		{
			virtual b2Vec2 getCurrentVelocity() const = 0;
			virtual b2Vec2 getMaximumVelocity() const = 0;
			virtual b2Vec2 getCurrentPosition() const = 0;
			virtual float getMass() const = 0;
		};
	}
}