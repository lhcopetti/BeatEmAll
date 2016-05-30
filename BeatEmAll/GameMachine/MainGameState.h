#pragma once

#include <map>

#include "SFML\Graphics.hpp"

#include "GameObjects\TileMap.h"
#include "GameObjects\Player.h"

#include "Box2D\Box2D.h"
#include "DebugBoxDraw\SFMLDebugDraw.h"

#include "Keyboard\KeyboardManager.h"
#include "Mouse\MouseListener.h"
#include "Mouse\MouseManager.h"

#include "Component\GraphicsComponent.h"

#include "IA\Steering\SteeringManager.h"

#include "Collision\ContactListener.h"

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

		GameComponent::Player* _player;

		Keys::KeyboardManager _keyManager;
		MouseComponent::MouseManager _mouseManager;
		
		Collision::ContactListener* _contactListener;

		std::vector<GameComponent::GameObject*> _gameObjects;

		void createBoundingBox(b2World& _world, float height, float width);

		void updateGameObject(GameComponent::GameObject& gO, float delta, std::vector<GameComponent::GameObject*>& children);

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