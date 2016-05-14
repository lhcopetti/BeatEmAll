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
	//_sprite.scale(.8f, .8f);
}

Player::~Player()
{

}

void Player::update(float elapsedTime)
{
}

void Player::handleMouse(const sf::Vector2i vector, bool leftClicked, bool rightClicked)
{
	sf::Vector2f currentPos = _sprite.getPosition();
	sf::Vector2f mousePos = sf::Vector2f(vector.x, vector.y);
	sf::Vector2f toTarget = mousePos - currentPos;
	float newAngle = std::atan2(toTarget.y, toTarget.x);
	_sprite.setRotation(newAngle * RADTODEG);
}

void Player::handleKeyboard(std::map<Keys::KeyboardManager::KeyAction, bool> keys)
{
	using namespace Keys;

	if (keys[KeyboardManager::KeyAction::MOVE_DOWN])
		std::cout << "Down" << std::endl;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite);
}