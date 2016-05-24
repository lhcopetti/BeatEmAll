#pragma once

#include "GameObjects\GameObject.h"

namespace GameComponent
{
	namespace GameActions
	{
		class Action
		{
		public:
			Action() {}
			virtual ~Action() {};

			virtual void execute(GameComponent::GameObject& target) = 0 {};
		};
	}
}