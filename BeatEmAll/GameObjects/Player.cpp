#include "GameObjects\Player.h"
#include "DebugBoxDraw\WorldConstants.h"

#include "GameObjects\Projectile\Bullet.h"
#include "GameObjects\Weapon\Pistol.h"

#include "GameObjects\Actions\MoveAction.h"
#include "GameObjects\Actions\ShootAction.h"
#include "GameObjects\Actions\AimAction.h"
#include "GameObjects\Actions\VelocityAction.h"

#include "Component\KeyboardInputComponent.h"

#include "Collision\CollisionCategory.h"

#include <iostream>

using namespace GameComponent;
namespace GA = GameComponent::GameActions;

Player::Player(GameObjectTypes type, b2World& world,
	float playerVelocity, float health,
	Components::PhysicsComponent* physicsComponent,
	Components::InputComponent* inputComponent,
	Components::GraphicsComponent* graphicsComponent)
	:
	GameObject(type, world, physicsComponent, inputComponent, graphicsComponent),
	_playerVelocity(playerVelocity), _health(health)
{
	_x = 50;
	_y = 50;
}

void Player::init()
{
//	/* Create fixtures */
//	b2BodyDef bodyDef;
//	bodyDef.type = b2_dynamicBody;
//	bodyDef.position = WorldConstants::sfmlToPhysics(sf::Vector2f(_x, _y));
//	bodyDef.userData = this;
//
//	_body = _world.CreateBody(&bodyDef);
//
//	b2PolygonShape polygonShape;
//	polygonShape.SetAsBox(27 / 2 / WorldConstants::SCALE, 43 / 2 / WorldConstants::SCALE);
//
//	b2FixtureDef fixture;
//	fixture.density = 1;
//	fixture.shape = &polygonShape;
//
//	if (GameObjectTypes::PLAYER == _type)
//	{
////		fixture.filter.categoryBits = Collision::CAT_PLAYER;
////		fixture.filter.maskBits = Collision::CAT_ENEMY | Collision::CAT_BOUNDARY;
//	}
//	else if (GameObjectTypes::ENEMY_DEFAULT == _type)
//	{
//		//fixture.filter.categoryBits = Collision::CAT_ENEMY;
//		//fixture.filter.maskBits =	Collision::CAT_PLAYER |
//		//							Collision::CAT_BOUNDARY |
//		//							Collision::CAT_BULLET |
//		//							Collision::CAT_ENEMY;
//	}
//	else
//	{
//		int x = 0;
//	}
//	_body->CreateFixture(&fixture);

	_weapon = new GameComponent::Weapons::Pistol(_world, 30, 30);
	addChild(_weapon);
}

Player::~Player()
{

}

void Player::doUpdate(float elapsedTime)
{


	/* Update Components */
//	_inputComponent->update(*this);
//	_graphicsComponent->update(*this);


	/* Isn't it just beautiful? */
	//auto iter = _actions.begin();
	//while (iter != _actions.end())
	//{
	//	(*iter)->execute(*this);
	//	delete *iter;
	//	iter = _actions.erase(iter);
	//}

	/*
	 * TODO: Update shared state (rotation angle)
	 * This will soon be abstracted away by the Component Design Pattern
	 */
	//_physicsComponent->getBody()->SetTransform(_physicsComponent->getBody()->GetPosition(), _rotationRad);
}

void Player::handleKeyboard(const std::map<Keys::KeyboardManager::KeyAction, bool>& keys)
{
	using namespace Keys;
	GA::MoveAction::MoveDirection moveDir;

	if (keys.at(KeyboardManager::KeyAction::MOVE_UP))
		moveDir.yDir = GA::YAxis::UP;
	if (keys.at(KeyboardManager::KeyAction::MOVE_DOWN))
		moveDir.yDir = GA::YAxis::DOWN;
	if (keys.at(KeyboardManager::KeyAction::MOVE_LEFT))
		moveDir.xDir = GA::XAxis::LEFT;
	if (keys.at(KeyboardManager::KeyAction::MOVE_RIGHT))
		moveDir.xDir = GA::XAxis::RIGHT;

	float pVelocity = getMaximumVelocity();
	b2Vec2 nextVel(moveDir.xDir * pVelocity, moveDir.yDir * pVelocity);

	GA::VelocityAction* velAction = new GA::VelocityAction(nextVel);
	addAction(velAction);
}

void Player::handleMouse(const sf::Vector2i& vector, bool leftClicked, bool rightClicked)
{
	/* We can safely assume there will no vector.x as big as MAX_INT. Cast is OK! */
	const sf::Vector2f mousePosF = sf::Vector2f(static_cast<float>(vector.x), static_cast<float>(vector.y));

	GA::Action* aimAction = new GA::AimAction(getCurrentPosition(), WorldConstants::sfmlToPhysics(mousePosF));
	addAction(aimAction);

	if (leftClicked)
	{
		b2Vec2 target = WorldConstants::sfmlToPhysics(mousePosF);
		GA::ShootAction* shootAction = new GA::ShootAction(getCurrentPosition(), target);
		addAction(shootAction);
	}
}