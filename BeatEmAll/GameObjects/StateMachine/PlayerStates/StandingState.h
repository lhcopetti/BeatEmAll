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
				virtual State* update(float elapsedTime);
			};
		}
	}
}