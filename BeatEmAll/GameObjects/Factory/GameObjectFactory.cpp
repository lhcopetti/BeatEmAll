#include "GameObjects\Factory\GameObjectFactory.h"

#include "DDD\FixtureShape\CircleShape.h"
#include "DDD\FixtureShape\PolygonShape.h"
#include "DDD\FixtureShape\VerticesShape.h"

#include "Component\GenericGraphicsComponent.h"

#include "DDD\Representation\DrawingRepresentation.h"
#include "DDD\Representation\SpriteRepresentation.h"

#include "DDD\GameObjects\EnemyDefaultUserDataInfo.h"
#include "DDD\GameObjects\PlayerUserDataInfo.h"

#include "DebugBoxDraw\WorldConstants.h"

#include "Component\KeyboardInputComponent.h"

#include "DDD\InfoCollection.h"

#include "IA\Steering\SteeringManager.h"
#include "Component\EnemyComponents\SteeringInputComponent.h"

#include "GameObjects\Factory\GraphicsFactory.h"
#include "GameObjects\Factory\PhysicsFactory.h"


using namespace GameComponent::Factory;

GameComponent::Player* GOFactory::newPlayer(b2World& world, Keys::KeyboardManager& keyManager, MouseComponent::MouseManager& mouseManager, sf::Vector2f position)
{
	DDD::GameObjectInfo* gameInfo = DDD::InfoCollection::getInstance().get("PlayerInfo");

	Components::PhysicsComponent*  p = PhysicsFactory::makeNew(world, gameInfo->_physicsInfo, WorldConstants::sfmlToPhysics(position));
	Components::GraphicsComponent* g = GraphicsFactory::makeNew(gameInfo->_graphicsInfo);

	const DDD::GameComponent::PlayerUserDataInfo* userData = static_cast<const DDD::GameComponent::PlayerUserDataInfo*>(gameInfo->_userDataInfo);
	float health = userData->_health;
	float vel = userData->_velocity;
	float runningVel = userData->_runningVelocity;


	GameComponent::Player* player = new GameComponent::Player(GameComponent::GameObjectTypes::PLAYER, world, 
		vel, runningVel, health,
		p,
		GameObject::nullInput(),//new Components::KeyboardInputComponent(keyManager, mouseManager),
		g);
	player->init();
	return player;
}

GameComponent::Enemy* GOFactory::newEnemyDefault(b2World& world, sf::Vector2f position, sf::RenderWindow* window)
{
	DDD::GameObjectInfo* gameInfo = DDD::InfoCollection::getInstance().get("EnemyDefault");

	Components::PhysicsComponent*  p = PhysicsFactory::makeNew(world, gameInfo->_physicsInfo, WorldConstants::sfmlToPhysics(position));
	Components::GraphicsComponent* g = GraphicsFactory::makeNew(gameInfo->_graphicsInfo);

	const DDD::GameComponent::EnemyDefaultUserDataInfo* userData = static_cast<const DDD::GameComponent::EnemyDefaultUserDataInfo*>(gameInfo->_userDataInfo);
	float health = userData->_health;
	float vel = userData->_velocity;

	IA::Steering::SteeringManager* _steeringManager = new IA::Steering::SteeringManager;
	Components::InputComponent* input = new Components::EnemyComponents::SteeringInputComponent(_steeringManager, window);

	GameComponent::Enemy* enemyDefault = new GameComponent::Enemy(world, vel, health, p, GameObject::nullInput(), g);
	enemyDefault->init();
	_steeringManager->setGameObject(enemyDefault);

	return enemyDefault;
}