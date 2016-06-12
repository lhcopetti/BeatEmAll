#include "GameObjects\StateMachine\StateManager.h"

#include "GameObjects\Actions\AimAction.h"
#include "GameObjects\Actions\MoveAction.h"

using namespace GameComponent::StateMachine;

StateManager::StateManager(State* initialState) :
	_currentState(initialState)
{
	if (_currentState)
		_currentState->onEnter();
}

void StateManager::update(float elapsedTime)
{
	State* newState = _currentState->update(elapsedTime);

	if (nullptr != newState)
	{
		delete _currentState;
		_currentState = newState;
	}
}

void StateManager::handleKeyboard(const std::map<Keys::KeyboardManager::KeyAction, bool>& keys)
{
	_currentState->handleKeyboard(keys);
}

void StateManager::handleMouse(const sf::Vector2i& vector, bool leftClicked, bool rightClicked)
{
	_currentState->handleMouse(vector, leftClicked, rightClicked);
}