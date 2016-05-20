#pragma once

#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\RenderWindow.hpp"

namespace MouseComponent
{
	class MouseManager
	{

	private: 

		/* TODO: Abstract out both these classes*/
		sf::RenderWindow* _window;
		sf::Vector2i _mousePos;

		bool _leftClicked;
		bool _rightClicked;

	public:
		MouseManager();

		void window(sf::RenderWindow* window) { _window = window; }
		bool left() const { return _leftClicked; }
		bool right() const { return _rightClicked; }
		const sf::Vector2i& mousePos() const { return _mousePos; }

		void update();
	};

}