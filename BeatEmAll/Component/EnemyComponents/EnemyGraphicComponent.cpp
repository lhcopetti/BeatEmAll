#include "Component\EnemyComponents\EnemyGraphicComponent.h"
#include "GameObjects\Player.h"
#include "DebugBoxDraw\WorldConstants.h"

using namespace Components::EnemyComponents;

EnemyGraphicComponent::EnemyGraphicComponent()
{
	_texture.loadFromFile("assets\\Robot 1\\robot1_hold.png");
	_sprite.setTexture(_texture);
	_sprite.setOrigin(14, 21);
	_sprite.scale(.6f, .6f);
}

void EnemyGraphicComponent::update(GameComponent::Player& player)
{
	_sprite.setPosition(player.position());
	_sprite.setRotation(player.rotation() * RADTODEG);
}

void EnemyGraphicComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite);
}