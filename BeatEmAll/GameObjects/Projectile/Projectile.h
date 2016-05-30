#pragma once
#include "GameObjects\GameObject.h"

namespace GameComponent
{
	namespace Projectiles
	{

		enum ProjectileType
		{
			BULLET
		};

		class Projectile : public GameComponent::GameObject
		{
			friend class ProjectileFactory;

		public:
			virtual ~Projectile() {}
			//virtual void update(float elapsedTime) = 0;
			//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		protected:
			Projectile(GameObjectTypes type, b2World& world, Components::PhysicsComponent* physics, Components::InputComponent* inputC, Components::GraphicsComponent* graphics) : 
				GameObject(type, world, physics, inputC, graphics) {};
		};
	}
}