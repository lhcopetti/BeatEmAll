#include "GameObjects\StateMachine\PlayerStates\WalkingState.h"
#include "GameObjects\StateMachine\PlayerStates\StandingState.h"

using namespace GameComponent::StateMachine;


void PlayerStates::WalkingState::onEnter()
{
}

State* PlayerStates::WalkingState::update(float elapsedTime)
{
	if (b2Vec2_zero == _player.body()->GetLinearVelocity())
	{
		return new GameComponent::StateMachine::PlayerStates::StandingState(_player);
	}

	return nullptr;
}