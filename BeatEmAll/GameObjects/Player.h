#pragma once
#include "Updatable\Updatable.h"

#include "GameObjects\GameObject.h"

#include "GameObjects\Actions\Action.h"
#include "GameObjects\Weapon\Weapon.h"

#include "Mouse\MouseListener.h"
#include "Keyboard\KeyboardListener.h"

#include "Component\InputComponent.h"
#include "Component\GraphicsComponent.h"

#include "Box2D\Box2D.h"

#include "IA\Steering\Steerable.h"

#define PLAYER_VELOCITY 5.f

namespace GA = GameComponent::GameActions;

namespace GameComponent
{
	class Player : public GameObject, public IA::Steering::Steerable
	{
	private:
		Components::InputComponent& _inputComponent;
		Components::GraphicsComponent& _graphicsComponent;

		std::vector<GA::Action*> _actions;
		GameComponent::Weapons::Weapon* _weapon;

	public:
		Player(b2World& world, 
			Components::InputComponent& inputComponent,
			Components::GraphicsComponent& graphicsComponent);
		~Player();

		void init();

		GameComponent::Weapons::Weapon& weapon() const { return *_weapon; }

		virtual void update(float elapsedTime);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void addAction(GameActions::Action* action);


		virtual b2Vec2 getCurrentVelocity() const { return _body->GetLinearVelocity(); }
		virtual float getMaximumVelocity() const { return 4.f; }
		virtual b2Vec2 getCurrentPosition() const { return _body->GetPosition(); }
		virtual float getMass() const { return _body->GetMass(); }

	};
}