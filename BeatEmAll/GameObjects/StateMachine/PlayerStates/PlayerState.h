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

				virtual float getPlayerVelocity() const { return _player.getMaximumVelocity(); }
//				virtual State* handleKeyboard(const std::map<Keys::KeyboardManager::KeyAction, bool>& keys);

			protected:
				GameComponent::Player& _player;
			};
		}
	}
}