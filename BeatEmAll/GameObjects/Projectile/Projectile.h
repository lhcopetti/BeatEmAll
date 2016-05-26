#pragma once
#include "GameObjects\GameObject.h"

namespace GameComponent
{
	namespace Projectiles
	{
		class Projectile : public GameComponent::GameObject
		{
		public:
			Projectile(b2World& world, Components::InputComponent* inputC, Components::GraphicsComponent* graphics) : 
				GameObject(world, inputC, graphics) {};
			virtual ~Projectile() {}

			//virtual void update(float elapsedTime) = 0;
			//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		private:
		};
	}
}