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
			SHOOT,
			RUN
		};

	private:
		std::map<KeyAction, bool> _keys;

	public:
		KeyboardManager();

		bool get(KeyAction key);
		void update();

		const std::map<KeyAction, bool>& keys() const { return _keys; };
	};
}