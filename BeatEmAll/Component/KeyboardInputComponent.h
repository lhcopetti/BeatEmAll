#pragma once
#include "Component\InputComponent.h"

#include "Keyboard\KeyboardManager.h"

namespace Components
{
	class KeyboardInputComponent : public InputComponent
	{
	private:
		Keys::KeyboardManager _keyboardManager;

		void KeyboardInputComponent::handleKeyboard(GameComponent::Player& player, std::map<Keys::KeyboardManager::KeyAction, bool> keys);

	public:
		KeyboardInputComponent();
		~KeyboardInputComponent();

		virtual void update(GameComponent::Player& player);


	};
}