#pragma once

#include "Box2D\Box2D.h"

namespace Components
{
	class PhysicsComponent
	{
	public:
		PhysicsComponent(b2World& world, b2Body* body) :
			_world(world),
			_body(body) {}
		~PhysicsComponent()
		{
			_world.DestroyBody(_body);
			_body = nullptr;
		}

		b2Body* getBody() const { return _body; }
		virtual b2World& getWorld() const { return _world; }

	private:
		b2Body* _body;
		b2World& _world;
	};
}