#pragma once

#include "GameObjects\GameObject.h"
#include "Box2D\Box2D.h"

#define BULLET_SPEED 15.f

namespace GameComponent
{
	namespace Projectile
	{
		class Bullet : public GameComponent::GameObject
		{
		private:
			const float _lifeTime;
			float _lifeTimeCounter;

			const b2Vec2 _initialPos;
			const b2Vec2 _initialVel;

			sf::CircleShape _circleSprite;

		public:
			Bullet(b2World& world, float lifeTime, b2Vec2 initialPos, b2Vec2 initialVel);

			void init();

			~Bullet();
			virtual void update(float elapsedTime);
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		};
	}
}