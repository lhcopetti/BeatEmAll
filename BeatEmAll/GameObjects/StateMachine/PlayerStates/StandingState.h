#pragma once
#include "GameObjects\StateMachine\State.h"

namespace GameComponent
{
	namespace StateMachine
	{
		namespace PlayerStates
		{
			class StandingState : public GameComponent::StateMachine::State
			{
				virtual State* update(float elapsedTime);
			};
		}
	}
}