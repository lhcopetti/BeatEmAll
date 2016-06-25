#pragma once

#include "Component\GraphicsComponent.h"
#include "Component\PhysicsComponent.h"

#include "DDD\GameObjectInfo.h"
#include "DDD\PhysicsInfo.h"
#include "DDD\GraphicInfo.h"

#include "GameObjects\Player.h"
#include "GameObjects\Enemy.h"

#include "Keyboard\KeyboardManager.h"
#include "Mouse\MouseManager.h"

namespace GameComponent
{
	namespace Factory
	{
		/* GameObjectFactory */
		class GOFactory
		{
		public:
			static GameComponent::Player* newPlayer(b2World& world, Keys::KeyboardManager& keyManager, MouseComponent::MouseManager& mouseManager, sf::Vector2f position);

			static GameComponent::Enemy* newEnemyDefault(b2World& world, sf::Vector2f position, sf::RenderWindow* window);
		};
	}
}