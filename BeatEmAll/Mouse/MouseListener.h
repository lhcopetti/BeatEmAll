#pragma once

#include "SFML\System\Vector2.hpp"

class MouseListener
{
	virtual void handleMouse(const sf::Vector2i vector, bool leftClicked, bool rightClicked) = 0;
};