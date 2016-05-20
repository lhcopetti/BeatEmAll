#pragma once
#include "Updatable\Updatable.h"

#include "GameObjects\GameObject.h"

#include "GameObjects\Actions\Action.h"
#include "GameObjects\Weapon\Weapon.h"

#include "Mouse\MouseListener.h"
#include "Keyboard\KeyboardListener.h"

#include "Component\InputComponent.h"

#include "Box2D\Box2D.h"

#define PLAYER_VELOCITY 5.f

namespace GA = GameComponent::GameActions;

namespace GameComponent
{
	class Player : public GameObject
	{
	private:
		sf::Texture _texture;
		sf::Sprite _sprite;

		Components::InputComponent& _inputComponent;

		b2Vec2 _nextPlayerVel;

		std::vector<GA::Action*> _actions;

		GameComponent::Weapons::Weapon* _weapon;

		bool _canShoot;
		float _canShootCounter;

	public:
		Player(b2World& world, Components::InputComponent& inputComponent);
		~Player();

		void init();

		GameComponent::Weapons::Weapon& weapon() const { return *_weapon; }

		virtual void update(float elapsedTime);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void addAction(GameActions::Action* action);
	};
}