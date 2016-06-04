#pragma once

namespace GameComponent
{
	class GameObject;
}

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