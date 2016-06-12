#pragma once

#include "Component\Graphic.h"

namespace Components
{
	class GenericGraphicsComponent : public Graphic
	{

	private:
		sf::Transformable* _transformable;
		sf::Drawable* _drawable;

		bool _followRotation;
		sf::Vector2f _origin;

		GenericGraphicsComponent();

		static void init(GenericGraphicsComponent& genericG, bool followRotation, sf::Vector2f origin);

	public:

		~GenericGraphicsComponent();
		static GenericGraphicsComponent* newDrawingGraphic(sf::Shape* shape, bool followRotation, sf::Vector2f origin);
		static GenericGraphicsComponent* newSpriteGraphic(sf::Sprite* sprite, bool followRotation, sf::Vector2f origin);

		virtual void update(GameComponent::GameObject& gameObject);
		virtual void draw(const GameComponent::GameObject& gameObject, sf::RenderTarget& target, sf::RenderStates states) const;
	};
}