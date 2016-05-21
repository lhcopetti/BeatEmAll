#pragma once

namespace GameComponent
{
	class Player;
}

namespace Components
{
	class GraphicsComponent
	{

	public:
		GraphicsComponent() {}
		virtual ~GraphicsComponent() {}

		virtual void update(GameComponent::Player& player) = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};
}