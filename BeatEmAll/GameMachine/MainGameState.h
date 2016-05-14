#pragma once

#include <map>

#include "SFML\Graphics.hpp"

#include "GameObjects\TileMap.h"
#include "GameObjects\Player.h"

#include "Box2D\Box2D.h"
#include "DebugBoxDraw\SFMLDebugDraw.h"
#include "Keyboard\KeyboardManager.h"

#define BOX2D_VELOCITY_ITERATIONS 8 // how strongly to correct velocity
#define BOX2D_POSITION_ITERATIONS 3 // how strongly to correct position

namespace GameMachine
{

	class MainGameState
	{
	private:
		bool _running;

		sf::RenderWindow _window;
		TileMap* _tileMap;

		b2World* _world;
		SFMLDebugDraw _debugDraw;


		GameComponent::Player _player;

		sf::Vector2i _mousePointer;
		bool _mouseLeftClicked;
		bool _mouseRightClicked;

		Keys::KeyboardManager _keyManager;

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