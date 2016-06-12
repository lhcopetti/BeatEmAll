#include "GameObjects\Factory\PhysicsFactory.h"

#include "DDD\FixtureShape\CircleShape.h"
#include "DDD\FixtureShape\PolygonShape.h"
#include "DDD\FixtureShape\VerticesShape.h"

using namespace GameComponent::Factory;

Components::PhysicsComponent* PhysicsFactory::makeNew(b2World& world, const DDD::PhysicsInfo* physics, b2Vec2 position)
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
		fixture.isSensor = f->_isSensor;
		fixture.density = f->_density;
		fixture.restitution = f->_restitution;
		fixture.filter.categoryBits = f->_category;
		fixture.filter.maskBits = f->_maskBits;

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
				dddShape->_angle);
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