#include "GameObjects\Projectile\ProjectileFactory.h"
#include "GameObjects\Projectile\GraphicBullet.h"
#include "GameObjects\Projectile\Bullet.h"

#include "DDD\InfoCollection.h"
#include "DDD\GameObjectInfo.h"

#include "DDD\Representation\DrawingRepresentation.h"
#include "DDD\Representation\SpriteRepresentation.h"

#include "DDD\Projectile\BulletUserDataInfo.h"

#include "Component\GenericGraphicsComponent.h"

#include <iostream>

using namespace GameComponent::Projectiles;


Components::GraphicsComponent* getGraphic(const DDD::GameObjectInfo* gameObjectInfo);

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

		Components::GraphicsComponent* graphic = getGraphic(info);
		const DDD::Projectile::BulletUserDataInfo* b = static_cast<const DDD::Projectile::BulletUserDataInfo*>(info->_userDataInfo);

		return new Bullet(world, graphic, b->_lifeTime, initialPosition, initialVel);
	}


	std::cout << "Invalid Projectile! " << std::endl;
	return nullptr;
}

Components::GraphicsComponent* getGraphic(const DDD::GameObjectInfo* gameObjectInfo)
{
	Components::GraphicsComponent* gr;
	const DDD::GraphicInfo* graphicInfo = gameObjectInfo->_graphicInfo;

	if (DDD::DRAWING == graphicInfo->_info->_type)
	{
		const DDD::DrawingRepresentation* dr = static_cast<const DDD::DrawingRepresentation*>(graphicInfo->_info);

		sf::CircleShape* circleShape = new sf::CircleShape(dr->_radius);
		circleShape->setFillColor(dr->_color);

		gr = Components::GenericGraphicsComponent::newDrawingGraphic(
			circleShape, 
			graphicInfo->_followRotation, 
			graphicInfo->_origin);
	}
	else
	{
		// TODO: what if it is not a drawing,
		// what if it is not a projectile but a player?
		return nullptr;
	}
}