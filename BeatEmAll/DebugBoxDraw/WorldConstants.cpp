#include "DebugBoxDraw\SFMLDebugDraw.h"
#include "DebugBoxDraw\WorldConstants.h"

const float WorldConstants::SCALE = 30.f;

const sf::Vector2f WorldConstants::physicsToSFML(b2Vec2 vector)
{
	return sf::Vector2f(WorldConstants::SCALE * vector.x, WorldConstants::SCALE * vector.y);
}

const b2Vec2 WorldConstants::sfmlToPhysics(sf::Vector2f vector)
{
	return b2Vec2(vector.x / WorldConstants::SCALE, vector.y / WorldConstants::SCALE);
}

const float WorldConstants::sfmlToPhysics(float x)
{
	return x / WorldConstants::SCALE;
}