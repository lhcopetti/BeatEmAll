#include "GameObjects\StateMachine\StateManager.h"

using namespace GameComponent::StateMachine;

void StateManager::update(float elapsedTime)
{
	State* newState = _currentState->update(elapsedTime);

	if (nullptr != newState)
	{
		delete _currentState;
		_currentState = newState;
	}
}