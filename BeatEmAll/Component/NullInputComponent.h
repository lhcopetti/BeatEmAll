#pragma once
#include "Component\InputComponent.h"

namespace Components
{
	class NullInputComponent : public InputComponent
	{
	private:
	public:

		~NullInputComponent() {}
		virtual void update(GameComponent::Player& player)
		{ /* Empty Implementation */ }
	};
}