#include "GameObjects\Player.h"
#include "DebugBoxDraw\WorldConstants.h"

#include "GameObjects\Projectile\Bullet.h"
#include "GameObjects\Weapon\Pistol.h"

#include "GameObjects\Actions\MoveAction.h"
#include "GameObjects\Actions\ShootAction.h"
#include "GameObjects\Actions\AimAction.h"

#include "Component\KeyboardInputComponent.h"

#include <iostream>

using namespace GameComponent;
namespace GA = GameComponent::GameActions;

Player::Player(b2World& world, 
	Components::InputComponent& inputComponent,
	Components::GraphicsComponent& graphicsComponent) 
	: 
	GameObject(world), 
	_inputComponent(inputComponent),
	_graphicsComponent(graphicsComponent)
{
	_x = 50;
	_y = 50;
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

	_weapon = new GameComponent::Weapons::Pistol(_world, 30, 30);
	addChild(_weapon);
}

Player::~Player()
{

}

void Player::update(float elapsedTime)
{
	sf::Vector2f bodyPos = WorldConstants::physicsToSFML(_body->GetPosition());
	_x = bodyPos.x;
	_y = bodyPos.y;

	/* Update Components */
	_inputComponent.update(*this);
	_graphicsComponent.update(*this);


	/* Isn't it just beautiful? */
	auto iter = _actions.begin();
	while (iter != _actions.end())
	{
		(*iter)->execute(*this);
		delete *iter;
		iter = _actions.erase(iter);
	}

	/*
	 * TODO: Update shared state (rotation angle) 
	 * This will soon be abstracted away by the Component Design Pattern
	 */
	_body->SetTransform(_body->GetPosition(), _rotationRad);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	_graphicsComponent.draw(target, states);
}

void Player::addAction(GameActions::Action* action)
{
	_actions.push_back(action);
}