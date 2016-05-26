#pragma once
#include "Box2D\Box2D.h"

namespace Collision
{
	class Collidable
	{

	public:
		virtual void beginContact(Collidable* other, b2Contact* contact) {}
		virtual void endContact(Collidable* other, b2Contact* contact) {}
		virtual uint16 getCategoryType() const = 0;
		virtual uint16 getMaskBits() const = 0;
	};
}