#include "GameObjects\Player.h"

using namespace GameComponent;

Player::Player()
{
	_x = 50;
	_y = 50;

	_texture.loadFromFile("assets\\pokeball.png");
	_sprite.setTexture(_texture);
	_sprite.setPosition(_x, _y);
}

Player::~Player()
{

}

void Player::update(float elapsedTime)
{
	static float acc = 0;

	acc += elapsedTime;

	if (acc > 1.f)
	{
		acc -= 1.f;
		_sprite.rotate(45);
	}

	//counter = ++counter % 60;
	/*
	static int counter = 0;

	counter = ++counter % 60;

	if (counter == 0)
		_sprite.rotate(30);
		*/
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite);
}