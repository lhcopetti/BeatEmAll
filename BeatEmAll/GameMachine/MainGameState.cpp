#include "GameMachine\MainGameState.h"

#include "Tiled\TiledParser\TiledMapParser.h"

#include "GameObjects\TileMap.h"
#include "GameObjects\Player.h"
#include "GameObjects\GameObject.h"

#include "Component\KeyboardInputComponent.h"

#include "Box2D\Box2D.h"

#include <iostream>

#include "DebugBoxDraw\WorldConstants.h"

using namespace GameMachine;

static void setPolygon(b2PolygonShape& poly, float sfHeight, float sfWidth, sf::Vector2f center);
static void setEdge(b2EdgeShape& edge, float xBegin, float yBegin, float xEnd, float yEnd);

MainGameState::MainGameState()
{
	_running = true;
	_mouseLeftClicked = false;
	_mouseRightClicked = false;
	_mousePointer = sf::Vector2i(0, 0);

	_world = nullptr;
	_inputComponent = nullptr;
}

MainGameState::~MainGameState()
{
	delete _inputComponent;
	_inputComponent = nullptr;
	delete _world;
	_world = nullptr;
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

	_inputComponent = new Components::KeyboardInputComponent();
	_player = new GameComponent::Player(*_world, *_inputComponent);
	_player->init();

	createBoundingBox(*_world, 1279.0, 639.0);

	_keyboardListeners.push_back(_player);
	_mouseListeners.push_back(_player);
	_gameObjects.push_back(_player);

	return true;
}

void MainGameState::createBoundingBox(b2World& _world, float width, float height)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.SetZero();

	b2Body* boundingBox = _world.CreateBody(&bodyDef);
	b2PolygonShape polyShape;

	b2FixtureDef fixDef;
	fixDef.density = 1;
	fixDef.shape = &polyShape;

	float thickness = 10.f;

	/* TOP */
	setPolygon(polyShape, thickness, width, sf::Vector2f(width / 2, thickness/ 2));
	boundingBox->CreateFixture(&fixDef);

	/* DOWN */
	setPolygon(polyShape, thickness, width, sf::Vector2f(width / 2, height - (thickness/ 2)));
	boundingBox->CreateFixture(&fixDef);

	/* RIGHT */
	setPolygon(polyShape, height, thickness, sf::Vector2f(width - (thickness / 2), height / 2));
	boundingBox->CreateFixture(&fixDef);

	/* LEFT */
	setPolygon(polyShape, height, thickness, sf::Vector2f(thickness / 2, height / 2));
	boundingBox->CreateFixture(&fixDef);
}

static void setEdge(b2EdgeShape& edge, float xBegin, float yBegin, float xEnd, float yEnd)
{
	sf::Vector2f begin(xBegin, yBegin);
	sf::Vector2f end(xEnd, yEnd);

	edge.Set(WorldConstants::sfmlToPhysics(begin), WorldConstants::sfmlToPhysics(end));
}

static void setPolygon(b2PolygonShape& poly, float sfHeight, float sfWidth, sf::Vector2f center)
{
	float b2Height = sfHeight / 2 / WorldConstants::SCALE;
	float b2Width = sfWidth / 2 / WorldConstants::SCALE;
	b2Vec2 b2Center = WorldConstants::sfmlToPhysics(center);

	poly.SetAsBox(b2Width, b2Height, b2Center, 0);
}

void MainGameState::step(float delta)
{
	const sf::Vector2i mousePointer = _mousePointer;
	bool leftMouse = _mouseLeftClicked;
	bool rightMouse = _mouseRightClicked;
	Keys::KeyboardManager &keyManager = _keyManager;

	std::for_each(
		_mouseListeners.begin(),
		_mouseListeners.end(),
		[&mousePointer, leftMouse, rightMouse](MouseComponent::MouseListener* l)
	{
		l->handleMouse(mousePointer, leftMouse, rightMouse);
	});

	std::for_each(
		_keyboardListeners.begin(),
		_keyboardListeners.end(),
		[keyManager](Keys::KeyboardListener* kL)
	{
		kL->handleKeyboard(keyManager.keys());
	});



	std::vector<GameComponent::GameObject*>::iterator gOIterator = _gameObjects.begin();
	std::vector<GameComponent::GameObject*> newChildren;

	while (gOIterator != _gameObjects.end())
	{
		GameComponent::GameObject* gO = *gOIterator;
		updateGameObject(*gO, delta, newChildren);

		if (gO->isAlive())
			++gOIterator;
		else
		{
			gOIterator = _gameObjects.erase(gOIterator);
			delete gO;
		}
	}

	for each(GameComponent::GameObject* child in newChildren)
	{
		child->init();
		_gameObjects.push_back(child);
	}

	_world->Step(delta, 8, 3);
	_world->ClearForces();
}

void MainGameState::draw()
{
	/* Capture locally for lambda */
	RenderWindow* rw = &_window;

	/* Draw the Tile Map */
	_window.draw(*_tileMap);

	std::for_each(_gameObjects.begin(), _gameObjects.end(), [rw](const GameComponent::GameObject* gO) { rw->draw(*gO); });

	//	_window.draw(_player);

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

void MainGameState::updateGameObject(GameComponent::GameObject& gO, float delta, std::vector<GameComponent::GameObject*>& newChildren)
{
	gO.update(delta);

	const std::vector<GameComponent::GameObject*>& children = gO.getChildren();

	if (children.size() > 0)
	{
		for each(GameComponent::GameObject* child in children)
			newChildren.push_back(child);

		gO.clearChildren();
	}
}