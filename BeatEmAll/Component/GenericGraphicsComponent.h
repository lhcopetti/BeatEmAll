#pragma once

#include "Component\GraphicsComponent.h"

namespace Components
{
	class GenericGraphicsComponent : public GraphicsComponent
	{
		//enum RepresentationType
		//{
		//	DRAWING, /* SHAPE  */
		//	SPRITE   /* SPRITE */
		//};

	private:
		sf::Transformable* _transformable;
		sf::Drawable* _drawable;

//		sf::Shape* _shape;
//		sf::Sprite* _sprite;
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