#include "GameObjects\Projectile\ProjectileFactory.h"
#include "GameObjects\Projectile\GraphicBullet.h"
#include "GameObjects\Projectile\Bullet.h"

#include <iostream>

using namespace GameComponent::Projectiles;

Projectile* ProjectileFactory::makeNew(
	ProjectileType projectileType,
	b2World& world,
	b2Vec2 initialPosition,
	b2Vec2 initialVel)
{
	if (BULLET == projectileType)
		return new Bullet(world, new GraphicBullet, 6.f, initialPosition, initialVel);


	std::cout << "Invalid Projectile! " << std::endl;
	return nullptr;
}