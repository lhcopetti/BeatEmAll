#pragma once
#include "Component\InputComponent.h"

#include "Keyboard\KeyboardManager.h"
#include "Mouse\MouseManager.h"

#include "GameObjects\Actions\MoveAction.h"

namespace Components
{
	class RandomInputComponent : public InputComponent
	{
	private:
		GameComponent::GameActions::MoveAction::MoveDirection _lastMove;

	public:
		RandomInputComponent();
		~RandomInputComponent();

		virtual void update(GameComponent::Player& player);
	};
}