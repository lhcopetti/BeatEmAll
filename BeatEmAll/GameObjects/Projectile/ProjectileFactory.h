#pragma once

#include "GameObjects\Projectile\Projectile.h"

namespace GameComponent
{
	namespace Projectiles
	{
		class ProjectileFactory
		{
		public:
			static Projectiles::Projectile* makeNew(
				Projectiles::ProjectileType projectileType,
				b2World& world, 
				b2Vec2 initialPosition, 
				b2Vec2 initialVel);
		};

	}
}