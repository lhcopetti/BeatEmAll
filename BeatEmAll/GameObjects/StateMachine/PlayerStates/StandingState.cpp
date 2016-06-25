#include "GameObjects\StateMachine\PlayerStates\StandingState.h"
#include "GameObjects\StateMachine\PlayerStates\WalkingState.h"

using namespace GameComponent::StateMachine;

void PlayerStates::StandingState::onEnter()
{
	_player.graphics()->setActiveGraphic("STANDING");
}

State* PlayerStates::StandingState::update(float elapsedTime)
{
	if (!(b2Vec2_zero == _player.body()->GetLinearVelocity()))
		return new GameComponent::StateMachine::PlayerStates::WalkingState(_player);

	return nullptr;
}