#pragma once

#include "SFML\System\Vector2.hpp"

namespace MouseComponent
{
	class MouseListener
	{
	public:
		virtual void handleMouse(const sf::Vector2i& vector, bool leftClicked, bool rightClicked) = 0;
	};
}