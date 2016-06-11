#pragma once

#include "Component\PhysicsComponent.h"

#include "DDD\PhysicsInfo.h"

#include "Box2D\Box2D.h"

namespace GameComponent
{
	namespace Factory
	{
		class PhysicsFactory
		{
		public:
			static Components::PhysicsComponent* makeNew(b2World& world, const DDD::PhysicsInfo* physics, b2Vec2 position);
		};
	}
}