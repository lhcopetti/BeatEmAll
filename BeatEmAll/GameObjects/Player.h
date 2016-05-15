#pragma once
#include "Updatable\Updatable.h"
#include "GameObjects\GameObject.h"

#include "Mouse\MouseListener.h"
#include "Keyboard\KeyboardListener.h"

#include "Box2D\Box2D.h"

#define PLAYER_VELOCITY 5.f

namespace GameComponent
{
	class Player : public GameObject, public MouseListener, public Keys::KeyboardListener
	{
	private:
		sf::Texture _texture;
		sf::Sprite _sprite;

		b2World* _world;
		b2Body* _body;

		b2Vec2 _nextPlayerVel;

		bool _canShoot;
		float _canShootCounter;

	public:
		Player();
		~Player();

		void init(b2World* world);

		virtual void update(float elapsedTime);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		virtual void handleMouse(const sf::Vector2i vector, bool leftClicked, bool rightClicked);

		virtual void handleKeyboard(const std::map<Keys::KeyboardManager::KeyAction, bool> keys);

		void shoot();
	};
}