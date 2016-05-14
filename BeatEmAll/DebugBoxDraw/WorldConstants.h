#pragma once

//#define SCALE 20.f;
#define MOVING_TOLERANCE 0.5f;

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"

class WorldConstants
{

public:
	static const float SCALE;

	static const sf::Vector2f physicsToSFML(b2Vec2 vector);
	static const b2Vec2 sfmlToPhysics(sf::Vector2f vector);
};