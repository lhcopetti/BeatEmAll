#pragma once
#include "GameObjects\StateMachine\State.h"
#include "GameObjects\Player.h"

namespace GameComponent
{
	namespace StateMachine
	{
		namespace PlayerStates
		{
			class PlayerState : public GameComponent::StateMachine::State
			{

			public:
				PlayerState(GameComponent::Player& player) : _player(player) {}

				virtual void onEnter() = 0;
				virtual State* update(float elapsedTime) = 0;

			protected:
				GameComponent::Player& _player;
			};
		}
	}
}