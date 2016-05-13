#include <iostream>

#include "Tiled\TiledParser\TiledMapParser.h"
#include "Tiled\TiledMap.h"
#include "GameObjects\TileMap.h"

#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"
#include <Windows.h>



void createGround(b2World& world, float x, float y);
void createBox(b2World& world, int mouseX, int mouseY);

const float SCALE = 30.f;

#ifndef RUN_UNIT_TEST
int main(int oldMain)
{
	bool mouseLeftPressed = false;
	bool mouseRightPressed = false;
	sf::RenderWindow rw(sf::VideoMode(1280, 640), "SFML Works! YAY!");

	TiledMapParser mapParser("assets\\tileMap_1280_640.tmx");
	TiledMap tiledMap;
	if (!mapParser.parse(tiledMap))
	{
		int xx = 0;
	}

	TileMap newTileMap;
	if (!TileMap::newTileMap(tiledMap, newTileMap, std::string("assets\\")))
	{
		int xx = 0;
	}

	
	while (rw.isOpen())
	{
		sf::Event event;
		while(rw.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				rw.close();
		}


		rw.draw(newTileMap);
		rw.display();
		Sleep(10);
	}

	return 0;
}
#endif

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