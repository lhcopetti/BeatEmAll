#pragma once

#include "GameObjects\GameObject.h"
#include "GameObjects\Projectile\Projectile.h"
#include "Box2D\Box2D.h"

#define BULLET_SPEED 15.f

namespace GameComponent
{
	namespace Projectiles
	{
		class Bullet : public GameComponent::Projectiles::Projectile
		{
		private:
			const float _lifeTime;
			float _lifeTimeCounter;

			const b2Vec2 _initialPos;
			const b2Vec2 _initialVel;

			sf::CircleShape _circleSprite;

		public:
			Bullet(b2World& world, float lifeTime, b2Vec2 initialPos, b2Vec2 initialVel);
			~Bullet();

			void init();

			virtual void update(float elapsedTime);
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		};
	}
}