#pragma once
#include "Component\InputComponent.h"

#include "Keyboard\KeyboardManager.h"
#include "Mouse\MouseManager.h"

namespace Components
{
	class KeyboardInputComponent : public InputComponent
	{
	private:
		Keys::KeyboardManager& _keyboardManager;
		MouseComponent::MouseManager& _mouseManager;

		void handleKeyboard(GameComponent::GameObject& player, const std::map<Keys::KeyboardManager::KeyAction, bool>& keys);
		void handleMouse(GameComponent::GameObject& player, MouseComponent::MouseManager& mouse);

	public:
		KeyboardInputComponent(Keys::KeyboardManager& keyboardManager,	MouseComponent::MouseManager& mouseManager);

		~KeyboardInputComponent();

		virtual void update(GameComponent::GameObject& player);
	};
}