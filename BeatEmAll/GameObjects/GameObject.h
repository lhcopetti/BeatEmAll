#pragma once
#include "Updatable\Updatable.h"

#include "SFML\Graphics.hpp"

namespace GameComponent
{
	class GameObject : public Updatable, public sf::Drawable
	{
	protected:
		int _x, _y;

	public:
		GameObject();
		virtual ~GameObject();

		virtual void update(float elapsedTime) = 0;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};
}