#pragma once

#include "SFML\Graphics.hpp"

#include "GameObjects\TileMap.h"
#include "GameObjects\Player.h"

#include "Box2D\Box2D.h"

namespace GameMachine
{

	class MainGameState
	{
	private:
		bool _running;

		sf::RenderWindow _window;
		TileMap* _tileMap;

		b2World* _world;

		GameComponent::Player _player;

	public:
		MainGameState();
		~MainGameState();

		bool init();

		bool isRunning() const { return _running; };

		void processEvents();
		void step(float delta);
		void draw();

		void shutdown();

	};
}