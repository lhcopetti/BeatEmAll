#pragma once

#include "Component\GraphicsComponent.h"
#include "Component\PhysicsComponent.h"

#include "DDD\GameObjectInfo.h"
#include "DDD\PhysicsInfo.h"
#include "DDD\GraphicInfo.h"

#include "GameObjects\Player.h"

#include "Keyboard\KeyboardManager.h"
#include "Mouse\MouseManager.h"

namespace GameComponent
{
	namespace Factory
	{
		/* GameObjectFactory */
		class GOFactory
		{
			static Components::GraphicsComponent* getGraphic(const DDD::GameObjectInfo* gameObjectInfo);
			static Components::PhysicsComponent* getPhysics(b2World& world, const DDD::PhysicsInfo* physics, b2Vec2 position);

		public:
			static GameComponent::Player* newPlayer(b2World& world, Keys::KeyboardManager& keyManager, MouseComponent::MouseManager& mouseManager, sf::Vector2f position);
		};
	}
}