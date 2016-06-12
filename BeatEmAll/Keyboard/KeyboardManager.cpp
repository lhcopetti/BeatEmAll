#include "Keyboard\KeyboardManager.h"
#include "SFML\Window\Keyboard.hpp"

using namespace Keys;

KeyboardManager::KeyboardManager()
{
	_keys[MOVE_UP] = false;
	_keys[MOVE_LEFT] = false;
	_keys[MOVE_DOWN] = false;
	_keys[MOVE_RIGHT] = false;
	_keys[SHOOT] = false;
	_keys[RUN] = false;
}

bool KeyboardManager::get(KeyAction key)
{
	return _keys[key];
}

void KeyboardManager::update()
{
	_keys[MOVE_UP] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
	_keys[MOVE_LEFT] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
	_keys[MOVE_DOWN] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
	_keys[MOVE_RIGHT] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
	_keys[SHOOT] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
	_keys[RUN] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift);
}