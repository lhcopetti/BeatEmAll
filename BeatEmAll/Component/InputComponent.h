#pragma once

namespace GameComponent
{
	class Player;
}

namespace Components
{
	class InputComponent
	{
	public:
		InputComponent() {}
		virtual ~InputComponent() {}

		virtual void update(GameComponent::Player& player) = 0;
	};
}