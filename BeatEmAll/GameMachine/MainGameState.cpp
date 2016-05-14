#include "GameMachine\MainGameState.h"

#include "Tiled\TiledParser\TiledMapParser.h"

#include "GameObjects\TileMap.h"
#include "GameObjects\Player.h"
#include "GameObjects\GameObject.h"

#include "Box2D\Box2D.h"

#include <iostream>

#include "DebugBoxDraw\WorldConstants.h"

using namespace GameMachine;

MainGameState::MainGameState()
{
	_running = true;
}

MainGameState::~MainGameState()
{
	delete _world;
}

bool MainGameState::init()
{
	_window.create(sf::VideoMode(1280, 640), "SFML Works! YAY!");

	TiledMapParser mapParser("assets\\tileMap_1280_640.tmx");
	TiledMap tiledMap;
	if (!mapParser.parse(tiledMap))
	{
		std::cout << "Erro ao realizar o parse do arquivo: " << mapParser.getXmlLocation() << std::endl;
		return false;
	}

	_tileMap = new TileMap;
	if (!TileMap::newTileMap(tiledMap, *_tileMap, std::string("assets\\")))
	{
		std::cout << "Erro ao criar tileMap. " << std::endl;
		return false;
	}


	b2Vec2 gravity(.0f, 9.8f);
	_world = new b2World(gravity);

	_debugDraw.setRenderWindow(_window);
	_debugDraw.SetFlags(b2Draw::e_shapeBit);
	_world->SetDebugDraw(&_debugDraw);

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position = WorldConstants::sfmlToPhysics(sf::Vector2f(250.f, 250.f));

	b2Body* body = _world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(32.f / 2 / 30, 32.f / 2 / 30);

	b2FixtureDef fix;
	fix.shape = &shape;
	fix.density = 1;

	body->CreateFixture(&fix);
}

void MainGameState::step(float delta)
{
	_player.update(delta);

	_world->Step(delta, 8, 3);
	_world->ClearForces();
}

void MainGameState::draw()
{
	_window.draw(*_tileMap);
	_window.draw(_player);

	_world->DrawDebugData();

	_window.display();
}

void MainGameState::shutdown()
{
	_running = false;
}

void MainGameState::processEvents()
{
	// Process Events
	sf::Event event;
	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_window.close();
			_running = false;
		}
	}
}