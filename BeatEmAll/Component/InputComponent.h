#pragma once

namespace GameComponent
{
	class GameObject;
}

namespace Components
{
	class InputComponent
	{
	public:
		InputComponent() {}
		virtual ~InputComponent() {}

		virtual void update(GameComponent::GameObject& player) = 0;
	};
}