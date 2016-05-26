#pragma once

#include "GameObjects\GameObject.h"
#include "GameObjects\Projectile\Projectile.h"
#include "Box2D\Box2D.h"

#include "Collision\Collidable.h"

#define BULLET_SPEED 15.f

namespace GameComponent
{
	namespace Projectiles
	{
		class Bullet :	public GameComponent::Projectiles::Projectile,
			public Collision::Collidable
		{
		private:
			const float _lifeTime;
			float _lifeTimeCounter;

			const b2Vec2 _initialPos;
			const b2Vec2 _initialVel;

			sf::CircleShape _circleSprite;

			static uint16 _categoryType;
			static uint16 _maskBits;

		public:
			Bullet(b2World& world, Components::GraphicsComponent* gComponent, float lifeTime, b2Vec2 initialPos, b2Vec2 initialVel);
			~Bullet();

			void init();

			virtual void doUpdate(float elapsedTime);

			virtual void beginContact(Collidable* other, b2Contact* contact);
			virtual uint16 getCategoryType() const;
			virtual uint16 getMaskBits() const;
		};
	}
}