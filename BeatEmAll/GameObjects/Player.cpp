#include "GameObjects\Player.h"
#include "SFML\Graphics.hpp"
#include "DebugBoxDraw\WorldConstants.h"

#include "GameObjects\Projectile\Bullet.h"

#include "GameObjects\Actions\MoveAction.h"
#include "GameObjects\Actions\ShootAction.h"

#include <iostream>

using namespace GameComponent;
namespace GA = GameComponent::GameActions;

Player::Player(b2World& world) : GameObject(world)
{
	_x = 50;
	_y = 50;

	_texture.loadFromFile("assets\\player1\\manBlue_silencer.png");
	_sprite.setTexture(_texture);
	_sprite.setOrigin(14, 21);
	_sprite.setPosition(_x, _y);
	_sprite.scale(.8f, .8f);

	_canShoot = false;
	_canShootCounter = 0.f;
}

void Player::init()
{
	/* Create fixtures */
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = WorldConstants::sfmlToPhysics(sf::Vector2f(_x, _y));

	_body = _world.CreateBody(&bodyDef);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(27 / 2 / WorldConstants::SCALE, 43 / 2 / WorldConstants::SCALE);

	b2FixtureDef fixture;
	fixture.density = 1;
	fixture.shape = &polygonShape;

	_body->CreateFixture(&fixture);
}

Player::~Player()
{

}

void Player::update(float elapsedTime)
{
	/* Isn't it just beautiful? */
	auto iter = _actions.begin();
	while (iter != _actions.end())
	{
		(*iter)->execute();
		delete *iter;
		iter = _actions.erase(iter);
	}


	/* TODO: How should this state be handled? */
	_canShootCounter += elapsedTime;

	if (_canShootCounter > .2f)
	{
		_canShootCounter -= .2f;
		_canShoot = true;
	}
}

void Player::handleMouse(const sf::Vector2i vector, bool leftClicked, bool rightClicked)
{
	const sf::Vector2f currentPos = _sprite.getPosition();
	/* We can safely assume there will no vector.x as big as MAX_INT. Cast is OK! */
	const sf::Vector2f mousePosF = sf::Vector2f(static_cast<int>(vector.x), static_cast<int>(vector.y));
	sf::Vector2f toTarget = mousePosF - currentPos;
	float newAngle = std::atan2(toTarget.y, toTarget.x);

	_body->SetTransform(_body->GetPosition(), newAngle);
	_sprite.setRotation(_body->GetAngle() * RADTODEG);
	_sprite.setPosition(WorldConstants::physicsToSFML(_body->GetPosition()));

	if (leftClicked && _canShoot)
		shoot(WorldConstants::sfmlToPhysics(sf::Vector2f(mousePosF.x, mousePosF.y)));
}

void Player::handleKeyboard(std::map<Keys::KeyboardManager::KeyAction, bool> keys)
{
	/* TODO: The player should not take any control! */
	/* What if I wanted the player to be AI Controlled? */
	using namespace Keys;

	GA::MoveAction::MoveDirection moveDir;

	if (keys[KeyboardManager::KeyAction::MOVE_UP])
		moveDir.yDir = GA::YAxis::UP;
	if (keys[KeyboardManager::KeyAction::MOVE_DOWN])
		moveDir.yDir = GA::YAxis::DOWN;
	if (keys[KeyboardManager::KeyAction::MOVE_LEFT])
		moveDir.xDir = GA::XAxis::LEFT;
	if (keys[KeyboardManager::KeyAction::MOVE_RIGHT])
		moveDir.xDir = GA::XAxis::RIGHT;

	GA::MoveAction* moveAction = new GA::MoveAction(*this, moveDir);
	_actions.push_back(moveAction);
}

void Player::shoot(const b2Vec2& target)
{
	using namespace GameComponent::Projectile;

	/* TODO: How should this state be kept? */
	_canShoot = false;
	_canShootCounter = .0f;

	/*
	 * The Player should not be responsible for issuing Actions!
	 */
	GA::ShootAction* shootAction = new GA::ShootAction(*this, _body->GetPosition(), target);
	_actions.push_back(shootAction);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite);
}