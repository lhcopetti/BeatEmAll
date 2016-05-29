
#include "GameObjects\GameObject.h"
#include "DebugBoxDraw\WorldConstants.h"

using namespace GameComponent;

GameObject::GameObject(GameObjectTypes type, b2World& world, Components::InputComponent* inputC, Components::GraphicsComponent* graphicsC) :
	_world(world), _type(type)
{
	_physicsComponent = nullptr;
	_inputComponent = inputC;
	_graphicsComponent = graphicsC;
	_body = nullptr;

	_alive = true;
	_rotationRad = 0.f;
	_x = _y = 0.f;
}

GameObject::~GameObject()
{
	if (_inputComponent)
		delete _inputComponent;

	if (_graphicsComponent)
		delete _graphicsComponent;

	_inputComponent = nullptr;
	_graphicsComponent = nullptr;
}

void GameObject::update(float elapsedTime)
{
	sf::Vector2f bodyPos;
	if (_body == nullptr)
		bodyPos = WorldConstants::physicsToSFML(_physicsComponent->getBody()->GetPosition());
	else
		bodyPos = WorldConstants::physicsToSFML(_body->GetPosition());

	_x = bodyPos.x;
	_y = bodyPos.y;

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