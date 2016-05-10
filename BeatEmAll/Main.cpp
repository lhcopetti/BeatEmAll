#include <iostream>

#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"
#include <Windows.h>



void createGround(b2World& world, float x, float y);
void createBox(b2World& world, int mouseX, int mouseY);

const float SCALE = 30.f;

int mainss(int oldMain)
{
	bool mouseLeftPressed = false;
	bool mouseRightPressed = false;
	sf::RenderWindow rw(sf::VideoMode(1280, 640), "SFML Works! YAY!");

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	b2Vec2 gravity(0.f, 9.8f);
	b2World myWorld(gravity);

	createGround(myWorld, 400.f, 500.f);

	sf::Texture ground;
	sf::Texture box;
	sf::Texture pokeBall;
	ground.loadFromFile("assets\\ground.png");
	box.loadFromFile("assets\\box.png");
	pokeBall.loadFromFile("assets\\pokeball.png");

	while (rw.isOpen())
	{
		sf::Event event;
		while(rw.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				rw.close();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			mouseLeftPressed = true;
		}
		else if (mouseLeftPressed)
		{
			int mouseX = sf::Mouse::getPosition(rw).x;
			int mouseY = sf::Mouse::getPosition(rw).y;
			createBox(myWorld, mouseX, mouseY);
			mouseLeftPressed = false;
		}


		myWorld.Step(1 / 60.f, 8, 3);

		rw.clear(sf::Color::White);

		for (b2Body* bodyIterator = myWorld.GetBodyList(); bodyIterator != 0; bodyIterator = bodyIterator->GetNext())
		{
			if (bodyIterator->GetType() == b2_dynamicBody)
			{
				sf::Sprite sprite;
				sprite.setTexture(pokeBall);
				sprite.setOrigin(16.f, 16.f);
				sprite.setPosition(SCALE * bodyIterator->GetPosition().x, SCALE * bodyIterator->GetPosition().y);
				sprite.setRotation(bodyIterator->GetAngle() * 180 / b2_pi);
				rw.draw(sprite);
			}
			else
			{
				sf::Sprite groundSprite;
				groundSprite.setTexture(ground);
				groundSprite.setOrigin(400.f, 8.f);
				groundSprite.setPosition(bodyIterator->GetPosition().x * SCALE, bodyIterator->GetPosition().y * SCALE);
				groundSprite.setRotation(180 / b2_pi * bodyIterator->GetAngle());
				rw.draw(groundSprite);
			}
		}

		rw.draw(shape);
		rw.display();
		Sleep(10);
	}

	return 0;
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