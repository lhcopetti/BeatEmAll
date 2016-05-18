#include "GameObjects\Weapon\Pistol.h"

#include "GameObjects\Projectile\Bullet.h"

using namespace GameComponent::Weapons;

void Pistol::update(float elapsedTime)
{

}

void Pistol::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	/* Do nothing for now */
}

GameComponent::Projectiles::Projectile* Pistol::shoot(b2Vec2 initialPos, b2Vec2 initialVel)
{
	using namespace GameComponent::Projectiles;

	return new Bullet(_world, 6.f, initialPos, initialVel);
}
