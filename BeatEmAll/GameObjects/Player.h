#pragma once
#include "Updatable\Updatable.h"

#include "GameObjects\GameObject.h"
#include "GameObjects\Actions\Action.h"

#include "Mouse\MouseListener.h"
#include "Keyboard\KeyboardListener.h"

#include "Box2D\Box2D.h"

#define PLAYER_VELOCITY 5.f

namespace GA = GameComponent::GameActions;

namespace GameComponent
{
	class Player : public GameObject, public MouseComponent::MouseListener, public Keys::KeyboardListener
	{
	private:
		sf::Texture _texture;
		sf::Sprite _sprite;

		b2Vec2 _nextPlayerVel;

		std::vector<GA::Action*> _actions;

		bool _canShoot;
		float _canShootCounter;

	public:
		Player(b2World& world);
		~Player();

		void init();

		virtual void update(float elapsedTime);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		virtual void handleMouse(const sf::Vector2i vector, bool leftClicked, bool rightClicked);

		virtual void handleKeyboard(const std::map<Keys::KeyboardManager::KeyAction, bool> keys);

		void shoot(const b2Vec2& mousePos);
	};
}