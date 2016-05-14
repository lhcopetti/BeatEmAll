#pragma once
#include "Updatable\Updatable.h"
#include "GameObjects\GameObject.h"

namespace GameComponent
{
	class Player : public GameObject
	{
	private:
		sf::Texture _texture;
		sf::Sprite _sprite;

	public:

		Player();
		~Player();

		virtual void update(float elapsedTime);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}