#include "GameObjects\Projectile\ProjectileFactory.h"
#include "GameObjects\Projectile\GraphicBullet.h"
#include "GameObjects\Projectile\Bullet.h"

#include "DDD\InfoCollection.h"
#include "DDD\GameObjectInfo.h"

#include "DDD\Representation\DrawingRepresentation.h"
#include "DDD\Representation\SpriteRepresentation.h"

#include "DDD\Projectile\BulletUserDataInfo.h"

#include "Component\GenericGraphicsComponent.h"
#include "Component\PhysicsComponent.h"

#include "DebugBoxDraw\WorldConstants.h"

#include "DDD\FixtureShape\CircleShape.h"
#include "DDD\FixtureShape\PolygonShape.h"
#include "DDD\FixtureShape\VerticesShape.h"

#include "GameObjects\Factory\GraphicsFactory.h"
#include "GameObjects\Factory\PhysicsFactory.h"

#include <iostream>

using namespace GameComponent::Projectiles;


Projectile* ProjectileFactory::makeNew(
	ProjectileType projectileType,
	b2World& world,
	b2Vec2 initialPosition,
	b2Vec2 initialVel)
{
	if (BULLET == projectileType)
	{
		const std::string bulletInfo = "BulletInfo";
		const DDD::GameObjectInfo* info = DDD::InfoCollection::getInstance().get(bulletInfo);

		Components::GraphicsComponent* graphic = GameComponent::Factory::GraphicsFactory::makeNew(info->_graphicsInfo);
		Components::PhysicsComponent* physics = GameComponent::Factory::PhysicsFactory::makeNew(world, info->_physicsInfo, initialPosition);

		const DDD::Projectile::BulletUserDataInfo* b = static_cast<const DDD::Projectile::BulletUserDataInfo*>(info->_userDataInfo);

		return new Bullet(world, physics, graphic, b->_lifeTime, b->_bulletSpeed, initialPosition, initialVel);
	}


	std::cout << "Invalid Projectile! " << std::endl;
	return nullptr;
}