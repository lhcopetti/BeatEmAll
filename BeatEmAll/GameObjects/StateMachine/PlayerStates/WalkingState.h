#pragma once
#include "GameObjects\StateMachine\PlayerStates\PlayerState.h"

namespace GameComponent
{
	namespace StateMachine
	{
		namespace PlayerStates
		{
			class WalkingState : public GameComponent::StateMachine::PlayerStates::PlayerState
			{
			public:
				WalkingState(GameComponent::Player& player) : PlayerState(player) { }

				virtual State* update(float elapsedTime);
				virtual void onEnter();

				State* handleKeyboard(const std::map<Keys::KeyboardManager::KeyAction, bool>& keys);
			};
		}
	}
}