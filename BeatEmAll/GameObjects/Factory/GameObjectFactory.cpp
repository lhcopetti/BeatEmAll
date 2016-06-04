#include "GameObjects\Factory\GameObjectFactory.h"

#include "DDD\FixtureShape\CircleShape.h"
#include "DDD\FixtureShape\PolygonShape.h"
#include "DDD\FixtureShape\VerticesShape.h"

#include "Component\GenericGraphicsComponent.h"

#include "DDD\Representation\DrawingRepresentation.h"
#include "DDD\Representation\SpriteRepresentation.h"

#include "DebugBoxDraw\WorldConstants.h"

#include "Component\KeyboardInputComponent.h"

#include "DDD\InfoCollection.h"

#include "IA\Steering\SteeringManager.h"
#include "Component\EnemyComponents\SteeringInputComponent.h"

using namespace GameComponent::Factory;

GameComponent::Player* GOFactory::newPlayer(b2World& world, Keys::KeyboardManager& keyManager, MouseComponent::MouseManager& mouseManager, sf::Vector2f position)
{
	const DDD::GameObjectInfo* gameInfo = DDD::InfoCollection::getInstance().get("PlayerInfo");

	Components::PhysicsComponent*  p = GOFactory::getPhysics(world, gameInfo->_physicsInfo, WorldConstants::sfmlToPhysics(position));
	Components::GraphicsComponent* g = GOFactory::getGraphic(gameInfo);

	GameComponent::Player* player = new GameComponent::Player(GameComponent::GameObjectTypes::PLAYER, world,
		p,
		new Components::KeyboardInputComponent(keyManager, mouseManager),
		g);
	player->init();
	return player;
}

GameComponent::Enemy* GOFactory::newEnemyDefault(b2World& world, sf::Vector2f position, sf::RenderWindow* window)
{
	const DDD::GameObjectInfo* gameInfo = DDD::InfoCollection::getInstance().get("EnemyDefault");

	Components::PhysicsComponent*  p = GOFactory::getPhysics(world, gameInfo->_physicsInfo, WorldConstants::sfmlToPhysics(position));
	Components::GraphicsComponent* g = GOFactory::getGraphic(gameInfo);

	IA::Steering::SteeringManager* _steeringManager = new IA::Steering::SteeringManager;
	Components::InputComponent* input = new Components::EnemyComponents::SteeringInputComponent(_steeringManager, window);

	GameComponent::Enemy* enemyDefault = new GameComponent::Enemy(world, p, input, g);
	enemyDefault->init();
	_steeringManager->setPlayer(enemyDefault);

	return enemyDefault;
}

Components::GraphicsComponent* GOFactory::getGraphic(const DDD::GameObjectInfo* gameObjectInfo)
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
		const DDD::SpriteRepresentation* sr = static_cast<const DDD::SpriteRepresentation*>(graphicInfo->_info);

		sf::Texture* texture = new sf::Texture;
		texture->loadFromFile(sr->_filePath);
		sf::Sprite* sprite = new sf::Sprite;
		sprite->setTexture(*texture);
		sprite->setScale(sf::Vector2f(sr->_scaleX, sr->_scaleY));
		// TODO: what if it is not a drawing,
		// what if it is not a projectile but a player?
		gr = Components::GenericGraphicsComponent::newSpriteGraphic
			(sprite, graphicInfo->_followRotation, graphicInfo->_origin);
	}

	return gr;
}

Components::PhysicsComponent* GOFactory::getPhysics(b2World& world, const DDD::PhysicsInfo* physics, b2Vec2 position)
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