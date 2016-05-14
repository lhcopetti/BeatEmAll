#pragma once
#include "Updatable\Updatable.h"
#include "GameObjects\GameObject.h"

#include "Mouse\MouseListener.h"
#include "Keyboard\KeyboardListener.h"

namespace GameComponent
{
	class Player : public GameObject, public MouseListener, public Keys::KeyboardListener
	{
	private:
		sf::Texture _texture;
		sf::Sprite _sprite;

	public:

		Player();
		~Player();

		virtual void update(float elapsedTime);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		virtual void handleMouse(const sf::Vector2i vector, bool leftClicked, bool rightClicked);
		virtual void handleKeyboard(std::map<Keys::KeyboardManager::KeyAction, bool> keys);
	};
}