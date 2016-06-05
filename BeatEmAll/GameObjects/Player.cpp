#include "GameObjects\Player.h"
#include "DebugBoxDraw\WorldConstants.h"

#include "GameObjects\Projectile\Bullet.h"
#include "GameObjects\Weapon\Pistol.h"

#include "GameObjects\Actions\MoveAction.h"
#include "GameObjects\Actions\ShootAction.h"
#include "GameObjects\Actions\AimAction.h"

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
	_weapon = new GameComponent::Weapons::Pistol(_world, 30, 30);
	addChild(_weapon);
}

Player::~Player()
{

}

void Player::doUpdate(float elapsedTime)
{
	_stateManager.update(elapsedTime);
}