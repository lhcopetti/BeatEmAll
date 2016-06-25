#pragma once
#include "GameObjects\StateMachine\PlayerStates\PlayerState.h"

namespace GameComponent
{
	namespace StateMachine
	{
		namespace PlayerStates
		{
			class StandingState : public GameComponent::StateMachine::PlayerStates::PlayerState
			{
			public:
				StandingState(GameComponent::Player& player) : PlayerState(player) {}

				virtual State* update(float elapsedTime);
				virtual void onEnter();
			};
		}
	}
}