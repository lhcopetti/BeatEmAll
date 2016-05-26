#pragma once

#include "GameObjects\Projectile\Projectile.h"
#include "GameObjects\GameObject.h"

namespace GameComponent
{
	namespace Weapons
	{
		class Weapon : public GameComponent::GameObject
		{
		public:
			/* TODO: Does Data Oriented Design ring any bell? */
			Weapon(b2World& world, int cartdrigeSize, int bulletCount) : 
				GameObject(world, GameObject::nullInput(), GameObject::nullGraphics()), 
				_cartdrigeSize(cartdrigeSize), 
				_bulletCount(bulletCount) {}

			virtual void update(float elapsedTime) = 0;
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

			virtual GameComponent::Projectiles::Projectile* shoot(b2Vec2 initialPos, b2Vec2 initialVel) = 0;

			virtual bool canShoot() const = 0;

			int bulletCount() const { return _bulletCount; }
			int cartridgeSize() const { return _cartdrigeSize; }

		protected:
			int _bulletCount;
			const int _cartdrigeSize;
		};
	}
}