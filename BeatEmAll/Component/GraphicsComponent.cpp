#include "Component\GraphicsComponent.h"

using namespace Components;

GraphicsComponent::GraphicsComponent()
{
	_current = nullptr;
}

GraphicsComponent::~GraphicsComponent()
{
}

void GraphicsComponent::addGraphic(const std::string& graphicName, Components::Graphic* graphic)
{
	if (_graphics.find(graphicName) != _graphics.end())
	{
		Graphic* g = _graphics[graphicName];
		delete g;
	}

	_graphics[graphicName] = graphic;
}

bool GraphicsComponent::setActiveGraphic(const std::string& graphicName)
{
	if (_graphics.find(graphicName) == _graphics.end())
		return false;

	_current = _graphics[graphicName];
}

void GraphicsComponent::update(GameComponent::GameObject& gameObject)
{
	if (_current)
		_current->update(gameObject);
}

void GraphicsComponent::draw(const GameComponent::GameObject& gameObject, sf::RenderTarget& target, sf::RenderStates states) const
{
	if (_current)
		_current->draw(gameObject, target, states);
}