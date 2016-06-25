#pragma once

#include "Updatable\Updatable.h"

#include "GameObjects\StateMachine\State.h"

#include "Keyboard\KeyboardListener.h"
#include "Mouse\MouseListener.h"

namespace GameComponent
{
	namespace StateMachine
	{
		class StateManager : public Updatable, 
			public Keys::KeyboardListener, 
			public MouseComponent::MouseListener
		{
		public:
			StateManager(GameComponent::StateMachine::State* initialState);
			virtual void update(float elapsedTime);

			virtual void handleKeyboard(const std::map<Keys::KeyboardManager::KeyAction, bool>& keys);
			virtual void handleMouse(const sf::Vector2i& vector, bool leftClicked, bool rightClicked);

		private:
			GameComponent::StateMachine::State* _currentState;
		};
	}
}