#pragma once

#include "SFML\Graphics.hpp"
#include "Component\InputComponent.h"

#include "IA\Steering\SteeringManager.h"

namespace Components
{
	namespace EnemyComponents
	{
		class SteeringInputComponent : public Components::InputComponent
		{
		private:
			IA::Steering::SteeringManager* _manager;
			sf::RenderWindow* _window;

		public:
			SteeringInputComponent(IA::Steering::SteeringManager* manager, sf::RenderWindow* window)
				: _manager(manager), _window(window)
			{}

			virtual void update(GameComponent::GameObject& player);
		};
	}
}