#include "GameObjects\StateMachine\StateManager.h"

#include "GameObjects\Actions\AimAction.h"
#include "GameObjects\Actions\MoveAction.h"

using namespace GameComponent::StateMachine;

StateManager::StateManager(State* initialState) :
	_currentState(initialState)
{

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
	///* We can safely assume there will no vector.x as big as MAX_INT. Cast is OK! */
	//const sf::Vector2f mousePosF = sf::Vector2f(static_cast<float>(vector.x), static_cast<float>(vector.y));

	//GA::Action* aimAction = new GA::AimAction(getCurrentPosition(), WorldConstants::sfmlToPhysics(mousePosF));
	//addAction(aimAction);

	//if (leftClicked)
	//{
	//	b2Vec2 target = WorldConstants::sfmlToPhysics(mousePosF);
	//	GA::ShootAction* shootAction = new GA::ShootAction(getCurrentPosition(), target);
	//	addAction(shootAction);
	//}
}