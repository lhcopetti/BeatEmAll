#pragma once

#include "SFML\Graphics.hpp"
#include "Component\GraphicsComponent.h"

namespace Components
{
	namespace EnemyComponents
	{
		class EnemyGraphicComponent : public Components::GraphicsComponent
		{
		private:
			sf::Texture _texture;
			sf::Sprite _sprite;

		public:
			EnemyGraphicComponent();
			virtual void update(GameComponent::Player& player);
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		};
	}
}