#pragma once

#include <map>

#include "Keyboard\KeyboardManager.h"

namespace Keys
{
	class KeyboardListener
	{
		virtual void handleKeyboard(const std::map<Keys::KeyboardManager::KeyAction, bool> keys) = 0;
	};
}