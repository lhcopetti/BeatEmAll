#pragma once
#include "SFML\Graphics.hpp"

namespace GameComponent
{
	class GameObject;
}

namespace Components
{
	class Graphic
	{
	public:
		Graphic() {}
		virtual ~Graphic() {}

		virtual void update(GameComponent::GameObject& gameObject) = 0;
		virtual void draw(const GameComponent::GameObject& gameObject, sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};
}