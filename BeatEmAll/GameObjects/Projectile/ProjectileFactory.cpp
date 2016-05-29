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

#include <iostream>

using namespace GameComponent::Projectiles;


Components::GraphicsComponent* getGraphic(const DDD::GameObjectInfo* gameObjectInfo);
Components::PhysicsComponent* getPhysics(b2World& world, const DDD::PhysicsInfo* physics, b2Vec2 position);

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
		Components::PhysicsComponent* physics = getPhysics(world, info->_physicsInfo, initialPosition);

		const DDD::Projectile::BulletUserDataInfo* b = static_cast<const DDD::Projectile::BulletUserDataInfo*>(info->_userDataInfo);

		return new Bullet(world, physics, graphic, b->_lifeTime, b->_bulletSpeed, initialPosition, initialVel);
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
		gr = nullptr;
	}

	return gr;
}

Components::PhysicsComponent* getPhysics(b2World& world, const DDD::PhysicsInfo* physics, b2Vec2 position)
{
	b2BodyDef bodyDef;
	bodyDef.type = physics->_type == DDD::STATIC ? b2_staticBody : b2_dynamicBody;
	bodyDef.bullet = physics->_isBullet;
	bodyDef.position = position;

	b2Body* body = world.CreateBody(&bodyDef);

	for (int i = 0; i < physics->_fixtures.size(); i++)
	{
		DDD::FixtureInfo* f = physics->_fixtures[i];
		const DDD::FixtureShape* fixtureShape = f->_shape;

		b2FixtureDef fixture;
		fixture.density = f->_density;
		fixture.restitution = f->_restitution;

		b2Shape* shape = nullptr;
		if (fixtureShape->_type == DDD::SHAPE_CIRCLE)
		{
			const DDD::CircleShape* dddShape = static_cast<const DDD::CircleShape*>(fixtureShape);
			b2CircleShape* circleShape = new b2CircleShape;
			circleShape->m_radius = dddShape->_radius;
			circleShape->m_p = dddShape->_position;
			shape = circleShape;
		}
		else if (fixtureShape->_type == DDD::SHAPE_BOX)
		{
			const DDD::PolygonShape* dddShape = static_cast<const DDD::PolygonShape*>(fixtureShape);
			b2PolygonShape* poly = new b2PolygonShape;
			poly->SetAsBox(
				dddShape->_hx, 
				dddShape->_hy,
				dddShape->_center,
				dddShape->_angle * DEGTORAD);
			shape = poly;
		}
		else if (fixtureShape->_type == DDD::SHAPE_VERTICES)
		{
			const DDD::VerticesShape* vShape = static_cast<const DDD::VerticesShape*>(fixtureShape);
			b2PolygonShape* vertices = new b2PolygonShape;
			vertices->Set(&vShape->_vertices[0], vShape->_vertices.size());
			shape = vertices;
		}

		fixture.shape = shape;
		body->CreateFixture(&fixture);
		delete shape;
	}

	return new Components::PhysicsComponent(world, body);
}