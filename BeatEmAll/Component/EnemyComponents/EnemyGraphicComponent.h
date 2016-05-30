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
			virtual void update(GameComponent::GameObject& player);
			virtual void draw(const GameComponent::GameObject& gameObject, sf::RenderTarget& target, sf::RenderStates states) const;
		};
	}
}