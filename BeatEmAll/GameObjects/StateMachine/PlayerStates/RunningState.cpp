#include "GameObjects\StateMachine\PlayerStates\RunningState.h"
#include "GameObjects\StateMachine\PlayerStates\StandingState.h"
#include "GameObjects\StateMachine\PlayerStates\WalkingState.h"

using namespace GameComponent::StateMachine;


void PlayerStates::RunningState::onEnter()
{
	_player.graphics()->setActiveGraphic("RUNNING");
}

State* PlayerStates::RunningState::update(float elapsedTime)
{
	if (b2Vec2_zero == _player.body()->GetLinearVelocity())
	{
		return new GameComponent::StateMachine::PlayerStates::StandingState(_player);
	}

	return nullptr;
}

State* PlayerStates::RunningState::handleKeyboard(const std::map<Keys::KeyboardManager::KeyAction, bool>& keys)
{
	if (!keys.at(Keys::KeyboardManager::RUN))
		return new GameComponent::StateMachine::PlayerStates::WalkingState(_player);

	return nullptr;
}