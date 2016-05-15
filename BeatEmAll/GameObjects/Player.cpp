#include "GameObjects\Player.h"
#include "SFML\Graphics.hpp"
#include "DebugBoxDraw\WorldConstants.h"

#include <iostream>

using namespace GameComponent;

Player::Player()
{
	_x = 50;
	_y = 50;

	_texture.loadFromFile("assets\\player1\\manBlue_silencer.png");
	_sprite.setTexture(_texture);
	_sprite.setOrigin(14, 21);
	_sprite.setPosition(_x, _y);
	_sprite.scale(.8f, .8f);
}

void Player::init(b2World* world)
{
	_world = world;

	/* Create fixtures */
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = WorldConstants::sfmlToPhysics(sf::Vector2f(_x, _y));

	_body = _world->CreateBody(&bodyDef);
	
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
	b2Vec2 velChange = _nextPlayerVel - _body->GetLinearVelocity();
	b2Vec2 force;
	force.x = _body->GetMass() * velChange.x / (1 / 60.f);
	force.y = _body->GetMass() * velChange.y / (1 / 60.f);

	_body->ApplyForce(force, _body->GetWorldCenter(), true);
}

void Player::handleMouse(const sf::Vector2i vector, bool leftClicked, bool rightClicked)
{
	sf::Vector2f currentPos = _sprite.getPosition();
	sf::Vector2f mousePos = sf::Vector2f(vector.x, vector.y);
	sf::Vector2f toTarget = mousePos - currentPos;
	float newAngle = std::atan2(toTarget.y, toTarget.x);

	_body->SetTransform(_body->GetPosition(), newAngle);
	_sprite.setRotation(_body->GetAngle() * RADTODEG);
	_sprite.setPosition(WorldConstants::physicsToSFML(_body->GetPosition()));
}

void Player::handleKeyboard(std::map<Keys::KeyboardManager::KeyAction, bool> keys)
{
	using namespace Keys;

	b2Vec2 vel(0.f, 0.f);

	if (keys[KeyboardManager::KeyAction::MOVE_UP])
		vel.y -= PLAYER_VELOCITY;
	if (keys[KeyboardManager::KeyAction::MOVE_LEFT])
		vel.x -= PLAYER_VELOCITY;
	if (keys[KeyboardManager::KeyAction::MOVE_RIGHT])
		vel.x += PLAYER_VELOCITY;
	if (keys[KeyboardManager::KeyAction::MOVE_DOWN])
		vel.y += PLAYER_VELOCITY;

	_nextPlayerVel = vel;
	//if (keys[KeyboardManager::KeyAction::MOVE_DOWN])
	//	std::cout << "Down" << std::endl;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite);
}