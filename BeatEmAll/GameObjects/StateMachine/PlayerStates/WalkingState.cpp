#include "GameObjects\StateMachine\PlayerStates\WalkingState.h"
#include "GameObjects\StateMachine\PlayerStates\StandingState.h"
#include "GameObjects\StateMachine\PlayerStates\RunningState.h"

using namespace GameComponent::StateMachine;


void PlayerStates::WalkingState::onEnter()
{
	_player.graphics()->setActiveGraphic("WALKING");
}

State* PlayerStates::WalkingState::update(float elapsedTime)
{
	if (b2Vec2_zero == _player.body()->GetLinearVelocity())
		return new GameComponent::StateMachine::PlayerStates::StandingState(_player);

	return nullptr;
}

State* PlayerStates::WalkingState::handleKeyboard(const std::map<Keys::KeyboardManager::KeyAction, bool>& keys)
{
	if (keys.at(Keys::KeyboardManager::RUN))
		return new GameComponent::StateMachine::PlayerStates::RunningState(_player);

	return nullptr;
}