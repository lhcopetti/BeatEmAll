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

#include "GameObjects\StateMachine\PlayerStates\ParentPlayerState.h"
#include "GameObjects\StateMachine\PlayerStates\StandingState.h"

#include <iostream>

using namespace GameComponent;
namespace GA = GameComponent::GameActions;

Player::Player(GameObjectTypes type, b2World& world,
	float playerVelocity, float playerRunningVelocity,
	float health,
	Components::PhysicsComponent* physicsComponent,
	Components::InputComponent* inputComponent,
	Components::GraphicsComponent* graphicsComponent)
	:
	GameObject(type, world, physicsComponent, inputComponent, graphicsComponent),
	_playerVelocity(playerVelocity), _playerRunningVelocity(playerRunningVelocity),
	_health(health),
	_stateManager(new StateMachine::PlayerStates::ParentPlayerState
		(*this, new StateMachine::PlayerStates::StandingState(*this)))
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

void Player::handleKeyboard(const std::map<Keys::KeyboardManager::KeyAction, bool>& keys)
{
	_stateManager.handleKeyboard(keys);
}

void Player::handleMouse(const sf::Vector2i& vector, bool leftClicked, bool rightClicked)
{
	_stateManager.handleMouse(vector, leftClicked, rightClicked);
}