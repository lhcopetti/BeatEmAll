#include <iostream>

#include "Tiled\TiledParser\TiledMapParser.h"
#include "Tiled\TiledMap.h"
#include "GameObjects\TileMap.h"

#include "GameObjects\Player.h"

#include "GameMachine\MainGameState.h"

#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"
#include <Windows.h>



void createGround(b2World& world, float x, float y);
void createBox(b2World& world, int mouseX, int mouseY);

const float SCALE = 30.f;

#ifdef MAIN
int main(int oldMain)
{
	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);

	GameMachine::MainGameState mainGameState;

	mainGameState.init();

	while (mainGameState.isRunning())
	{
		mainGameState.processEvents();

		while (accumulator > ups)
		{
			accumulator -= ups;
			mainGameState.step(ups.asSeconds());
		}

		mainGameState.draw();

		accumulator += clock.restart();
	}

	mainGameState.shutdown();

	return 0;
}
#endif

void startGame()
{

}

void createGround(b2World& world, float X, float Y)
{
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(X / SCALE, Y / SCALE);
	bodyDef.type = b2_staticBody;
	b2Body* body = world.CreateBody(&bodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((800.f / 2) / SCALE, (16.f / 2) / SCALE); // Creates a box shape. Divide your desired width and height by 2.
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;  // Sets the density of the body
	FixtureDef.shape = &Shape; // Sets the shape
	body->CreateFixture(&FixtureDef); // Apply the fixture definition


	Shape.SetAsBox((16.f / 2) / SCALE, (600.f / 2) / SCALE, b2Vec2(-400 / SCALE,-300 /SCALE), 0); // Creates a box shape. Divide your desired width and height by 2.
	body->CreateFixture(&FixtureDef);

	Shape.SetAsBox((16.f / 2) / SCALE, (600.f / 2) / SCALE, b2Vec2(380 / SCALE, -300 / SCALE), 0); // Creates a box shape. Divide your desired width and height by 2.
	body->CreateFixture(&FixtureDef);
}

void createBox(b2World& world, int mouseX, int mouseY)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(mouseX / SCALE, mouseY / SCALE);
	BodyDef.type = b2_dynamicBody;
	b2Body* Body = world.CreateBody(&BodyDef);

	b2CircleShape Shape;
	Shape.m_radius = 32.f / 2 / SCALE;
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
}