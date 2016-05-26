#pragma once

namespace GameComponent
{
	class GameObject;
}

namespace Components
{
	class GraphicsComponent
	{

	public:
		GraphicsComponent() {}
		virtual ~GraphicsComponent() {}

		virtual void update(GameComponent::GameObject& gameObject) = 0;
		virtual void draw(const GameComponent::GameObject& gameObject, sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};
}