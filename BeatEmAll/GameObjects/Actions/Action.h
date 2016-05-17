#pragma once

#include "GameObjects\GameObject.h"

namespace GameComponent
{
	namespace GameActions
	{
		class Action
		{
		public:
			Action(GameComponent::GameObject& target) : _target(target) {}
			virtual ~Action() {};

			virtual void execute() = 0 {};

		protected:
			/* 
			 * Cannot be const because I'm calling non-const methods, such as
			 * body() : b2Body*
			 */
			GameComponent::GameObject& _target;
		};
	}
}