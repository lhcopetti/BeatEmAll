#pragma once
#include "GameObjects\StateMachine\State.h"

namespace GameComponent
{
	namespace StateMachine
	{
		namespace PlayerStates
		{
			class PlayerState : public GameComponent::StateMachine::State
			{

			public:
				virtual State* update(float elapsedTime) = 0;
			};
		}
	}
}