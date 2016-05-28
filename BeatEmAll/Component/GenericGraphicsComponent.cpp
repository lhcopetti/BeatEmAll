
#include "Component\GenericGraphicsComponent.h"
#include "GameObjects\GameObject.h"

using namespace Components;

GenericGraphicsComponent* GenericGraphicsComponent::newDrawingGraphic(sf::Shape* shape, bool followRotation, sf::Vector2f origin)
{
	GenericGraphicsComponent* genericG = new GenericGraphicsComponent;
	genericG->_drawable = shape;
	genericG->_transformable = shape;
	init(*genericG, followRotation, origin);
	return genericG;
}

GenericGraphicsComponent* GenericGraphicsComponent::newSpriteGraphic(sf::Sprite* sprite, bool followRotation, sf::Vector2f origin)
{
	GenericGraphicsComponent* genericG = new GenericGraphicsComponent;
	genericG->_drawable = sprite;
	genericG->_transformable = sprite;
	init(*genericG, followRotation, origin);
	return genericG;
}

void GenericGraphicsComponent::init(GenericGraphicsComponent& genericG, bool followRotation, sf::Vector2f origin)
{
	genericG._followRotation = followRotation;
	genericG._origin = origin;
	genericG._transformable->setOrigin(origin);
}

GenericGraphicsComponent::GenericGraphicsComponent()
{
	/* PRIVATE */
}

GenericGraphicsComponent::~GenericGraphicsComponent()
{

}

void GenericGraphicsComponent::update(GameComponent::GameObject& gameObject)
{
	_transformable->setPosition(gameObject.position());
	if (_followRotation)
		_transformable->setRotation(gameObject.rotation());
}

void GenericGraphicsComponent::draw(const GameComponent::GameObject& gameObject, sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*_drawable);
}
