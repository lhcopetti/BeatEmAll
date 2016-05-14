#include "GameMachine\MainGameState.h"

#include "Tiled\TiledParser\TiledMapParser.h"

#include "GameObjects\TileMap.h"
#include "GameObjects\Player.h"
#include "GameObjects\GameObject.h"

#include "Box2D\Box2D.h"

#include <iostream>


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

}

void MainGameState::step(float delta)
{
	_player.update(delta);
}

void MainGameState::draw()
{
	_window.draw(*_tileMap);
	_window.draw(_player);
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