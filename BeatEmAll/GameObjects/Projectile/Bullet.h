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
		class Bullet :	public GameComponent::Projectiles::Projectile
		{
		private:
			const float _bulletSpeed;
			const float _lifeTime;
			float _lifeTimeCounter;

			const b2Vec2 _initialPos;
			const b2Vec2 _initialVel;

			sf::CircleShape _circleSprite;

			static uint16 _categoryType;
			static uint16 _maskBits;

		public:
			Bullet(b2World& world, Components::PhysicsComponent* physics, Components::GraphicsComponent* gComponent, float lifeTime, float bulletSpeed, b2Vec2 initialPos, b2Vec2 initialVel);
			~Bullet();

			void init();

			virtual void doUpdate(float elapsedTime);

			virtual void beginContact(GameComponent::GameObject* other, b2Contact* contact);
		};
	}
}