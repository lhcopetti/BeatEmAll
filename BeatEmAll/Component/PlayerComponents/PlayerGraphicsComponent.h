#pragma once

#include "SFML\Graphics.hpp"
#include "Component\GraphicsComponent.h"

namespace Components
{
	namespace PlayerComponents
	{
		class PlayerGraphicsComponent : public Components::GraphicsComponent
		{
		private:
			sf::Texture _texture;
			sf::Sprite _sprite;

		public:
			PlayerGraphicsComponent();
			virtual void update(GameComponent::Player& player);
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		};
	}
}