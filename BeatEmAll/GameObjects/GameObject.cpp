
#include "GameObjects\GameObject.h"
#include "DebugBoxDraw\WorldConstants.h"

using namespace GameComponent;

GameObject::GameObject(GameObjectTypes type, b2World& world, Components::PhysicsComponent* physics, Components::InputComponent* inputC, Components::GraphicsComponent* graphicsC) :
	_world(world), _type(type)
{

	_physicsComponent = physics;
	_inputComponent = inputC;
	_graphicsComponent = graphicsC;

	_alive = true;
	_rotationRad = 0.f;
	_x = _y = 0.f;

	if (_physicsComponent)
		_physicsComponent->getBody()->SetUserData(this);
}

GameObject::~GameObject()
{
	if (_inputComponent)
		delete _inputComponent;

	if (_graphicsComponent)
		delete _graphicsComponent;

	if (_physicsComponent)
		delete _physicsComponent;

	_inputComponent = nullptr;
	_graphicsComponent = nullptr;
	_physicsComponent = nullptr;
}

void GameObject::update(float elapsedTime)
{
	if (_physicsComponent)
		_physicsComponent->update(*this);

	if (_inputComponent)
		_inputComponent->update(*this);

	if (_graphicsComponent)
		_graphicsComponent->update(*this);

	doUpdate(elapsedTime);
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (_graphicsComponent)
		_graphicsComponent->draw(*this, target, states);
}

const std::vector<GameObject*>& GameObject::getChildren() const
{
	return _children;
}

void GameObject::clearChildren()
{
	/* Do not free the pointers */
	_children.clear();
}

void GameObject::addChild(GameObject* child)
{
	_children.push_back(child);
}

void GameObject::position(float x, float y)
{
	_x = x;
	_y = y;
}