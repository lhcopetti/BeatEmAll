#pragma once
#include "GameObjects\StateMachine\PlayerStates\PlayerState.h"

namespace GameComponent
{
	namespace StateMachine
	{
		namespace PlayerStates
		{
			class RunningState : public GameComponent::StateMachine::PlayerStates::PlayerState
			{
			public:
				RunningState(GameComponent::Player& player) : PlayerState(player) { }

				virtual State* update(float elapsedTime);
				virtual void onEnter();

//				virtual void handleKeyboard(const std::map<Keys::KeyboardManager::KeyAction, bool>& keys);
			};
		}
	}
}