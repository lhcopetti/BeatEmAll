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
		class GraphicBullet : public Components::GraphicsComponent
		{

		public:
			virtual void update(GameComponent::GameObject& gameObject);
			virtual void draw(const GameComponent::GameObject& gameObject, sf::RenderTarget& target, sf::RenderStates states) const;
//			virtual void draw(GameComponent::GameObject& gameObject, sf::RenderTarget& target, sf::RenderStates states);

		private:
			sf::CircleShape _circle;
		};
	}
}