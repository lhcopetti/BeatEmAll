#pragma once

#include "SFML\Graphics.hpp"
#include "Component\Graphic.h"

namespace Components
{
	class GraphicsComponent : public Components::Graphic
	{

	public:
		GraphicsComponent();
		virtual ~GraphicsComponent();

		void addGraphic(const std::string& graphicName, Components::Graphic* graphic);

		bool setActiveGraphic(const std::string& graphicName);

		virtual void update(GameComponent::GameObject& gameObject);
		virtual void draw(const GameComponent::GameObject& gameObject, sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		std::map<std::string, Components::Graphic*> _graphics;

		Components::Graphic* _current;
	};
}