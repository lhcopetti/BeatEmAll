#pragma once
#include "Keyboard\KeyboardListener.h"
#include "Mouse\MouseListener.h"

namespace GameComponent
{
	namespace StateMachine 
	{
		class State //:
//			public Keys::KeyboardListener,
//			public MouseComponent::MouseListener
		{
		public:
			virtual void onEnter() = 0;
			virtual State* update(float elapsedTime) = 0;

			virtual State* handleKeyboard(const std::map<Keys::KeyboardManager::KeyAction, bool>& keys) { return nullptr; }
			virtual State* handleMouse(const sf::Vector2i& vector, bool leftClicked, bool rightClicked) { return nullptr; }
		};
	}
}