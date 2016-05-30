#pragma once
#include "Box2D\Box2D.h"

namespace GameComponent
{
	class GameObject;
}

namespace Collision
{
	class Collidable
	{

	public:
		virtual void beginContact(GameComponent::GameObject* other, b2Contact* contact) {}
		virtual void endContact(GameComponent::GameObject* other, b2Contact* contact) {}
	};
}