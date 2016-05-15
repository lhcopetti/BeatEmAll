#pragma once

#include <map>

namespace Keys
{
	class KeyboardManager
	{
	public:
		enum KeyAction
		{
			MOVE_UP = 0,
			MOVE_LEFT,
			MOVE_DOWN,
			MOVE_RIGHT,
			SHOOT
		};

	private:
		std::map<KeyAction, bool> _keys;

	public:
		bool get(KeyAction key);
		void update();

		KeyboardManager();

		std::map<KeyAction, bool> keys() const { return _keys; };
	};
}