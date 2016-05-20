#pragma once
#include "GameObjects\Weapon\Weapon.h"

namespace GameComponent
{
	namespace Weapons
	{
		class Pistol : public Weapon
		{
		private:
			bool _canShoot;
			float _fireRate;
			float _fireRateCounter;
		public:

			/* TODO: Does Data Oriented Design ring any bell? */
			Pistol(b2World& world, int cartdrigeSize, int bulletCount);

			virtual void update(float elapsedTime);
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			virtual GameComponent::Projectiles::Projectile* shoot(b2Vec2 initialPos, b2Vec2 initialVel);

			virtual bool canShoot() const;
		};
	}
}