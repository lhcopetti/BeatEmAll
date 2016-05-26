#include "Component\PlayerComponents\PlayerGraphicsComponent.h"
#include "GameObjects\Player.h"
#include "DebugBoxDraw\WorldConstants.h"

using namespace Components::PlayerComponents;

PlayerGraphicsComponent::PlayerGraphicsComponent()
{
	_texture.loadFromFile("assets\\player1\\manBlue_silencer.png");
	_sprite.setTexture(_texture);
	_sprite.setOrigin(14, 21);
	_sprite.scale(.6f, .6f);
}

void PlayerGraphicsComponent::update(GameComponent::GameObject& player)
{
	_sprite.setPosition(player.position());
	_sprite.setRotation(player.rotation() * RADTODEG);
}

void PlayerGraphicsComponent::draw(const GameComponent::GameObject& gameObject, sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite);
}