#include "SFML\Graphics.hpp"

#include "Mouse\MouseManager.h"

using namespace MouseComponent;

MouseManager::MouseManager()
{
	_window = nullptr;
}

void MouseManager::update()
{
	_leftClicked = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	_rightClicked = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);

	if (_window)
		_mousePos = sf::Mouse::getPosition(*_window);
}