#include "GameMachine\MainGameState.h"

#include "Tiled\TiledParser\TiledMapParser.h"

#include "GameObjects\TileMap.h"
#include "GameObjects\Player.h"
#include "GameObjects\GameObject.h"

#include "Box2D\Box2D.h"

#include <iostream>

#include "DebugBoxDraw\WorldConstants.h"

using namespace GameMachine;

static void setEdge(b2EdgeShape& edge, int xBegin, int yBegin, int xEnd, int yEnd);

MainGameState::MainGameState()
{
	_running = true;
	_mouseLeftClicked = false;
	_mouseRightClicked = false;
	_mousePointer = sf::Vector2i(0, 0);

	_world = nullptr;
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


	b2Vec2 gravity(.0f, 0.f);
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

	bodyDef.position = WorldConstants::sfmlToPhysics(sf::Vector2f(500.f, 500.f));
	b2Body* circ = _world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = 32.f / 2 / WorldConstants::SCALE;
	fix.shape = &circle;

	circ->CreateFixture(&fix);

	_player.init(_world);

	createBoundingBox(*_world, 1279, 639);

	return true;
}

void MainGameState::createBoundingBox(b2World& _world, int width, int height)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.SetZero();

	b2Body* boundingBox = _world.CreateBody(&bodyDef);
	b2EdgeShape edge;

	b2FixtureDef fixDef;
	fixDef.density = 1;
	fixDef.shape = &edge;

	/* TOP */
	setEdge(edge, 0, 0, width, 0);
	boundingBox->CreateFixture(&fixDef);

	/* RIGHT */
	setEdge(edge, width, 0, width, height);
	boundingBox->CreateFixture(&fixDef);

	/* DOWN */
	setEdge(edge, 0, height, width, height);
	boundingBox->CreateFixture(&fixDef);

	/* LEFT */
	setEdge(edge, 0, 0, 0, height);
	boundingBox->CreateFixture(&fixDef);
}

static void setEdge(b2EdgeShape& edge, int xBegin, int yBegin, int xEnd, int yEnd)
{
	sf::Vector2f begin(xBegin, yBegin);
	sf::Vector2f end(xEnd, yEnd);

	edge.Set(WorldConstants::sfmlToPhysics(begin), WorldConstants::sfmlToPhysics(end));
}

void MainGameState::step(float delta)
{
	_player.handleMouse(_mousePointer, _mouseLeftClicked, _mouseRightClicked);
	_player.handleKeyboard(_keyManager.keys());
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

	_mouseLeftClicked = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	_mouseRightClicked = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
	_mousePointer = sf::Mouse::getPosition(_window);

	_keyManager.update();
}