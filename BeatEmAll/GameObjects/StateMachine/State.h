#pragma once
#include "Keyboard\KeyboardListener.h"
#include "Mouse\MouseListener.h"

namespace GameComponent
{
	namespace StateMachine 
	{
		class State :
			public Keys::KeyboardListener,
			public MouseComponent::MouseListener
		{
		public:
			virtual void onEnter() = 0;
			virtual State* update(float elapsedTime) = 0;

			virtual void handleKeyboard(const std::map<Keys::KeyboardManager::KeyAction, bool>& keys) {}
			virtual void handleMouse(const sf::Vector2i& vector, bool leftClicked, bool rightClicked) {}
		};
	}
}