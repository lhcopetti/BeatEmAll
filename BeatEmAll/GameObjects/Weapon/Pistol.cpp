#include "GameObjects\Weapon\Pistol.h"

#include "GameObjects\Projectile\Bullet.h"
#include "GameObjects\Projectile\GraphicBullet.h"
#include "GameObjects\Projectile\ProjectileFactory.h"

using namespace GameComponent::Weapons;

#define PISTOL_FIRERATE .2f

Pistol::Pistol(b2World& world, int cartdrigeSize, int bulletCount) :
	Weapon(GameObjectTypes::WEAPON_PISTOL, world, cartdrigeSize, bulletCount)
{
	_canShoot = false;
	_fireRate = PISTOL_FIRERATE;
	_fireRateCounter = 0.f;
}

void Pistol::update(float elapsedTime)
{
	_fireRateCounter += elapsedTime;

	if (_fireRateCounter > _fireRate)
	{
		_fireRateCounter -= _fireRate;
		_canShoot = true;
	}
}

void Pistol::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	/* Do nothing for now */
}

GameComponent::Projectiles::Projectile* Pistol::shoot(b2Vec2 initialPos, b2Vec2 initialVel)
{
	using namespace GameComponent::Projectiles;

	if (!_canShoot)
		return nullptr;

	_canShoot = false;

	return ProjectileFactory::makeNew(ProjectileType::BULLET, _world, initialPos, initialVel);
}

bool Pistol::canShoot() const
{
	return _canShoot;
}