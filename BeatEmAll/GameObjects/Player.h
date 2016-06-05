#pragma once
#include "Updatable\Updatable.h"

#include "GameObjects\GameObject.h"

#include "GameObjects\Weapon\Weapon.h"

#include "Mouse\MouseListener.h"
#include "Keyboard\KeyboardListener.h"

#include "Component\InputComponent.h"
#include "Component\GraphicsComponent.h"

#include "Box2D\Box2D.h"

#include "IA\Steering\Steerable.h"

#include "GameObjects\StateMachine\StateManager.h"

#define PLAYER_VELOCITY 5.f

namespace GA = GameComponent::GameActions;

namespace GameComponent
{
	class Player : public GameObject, public IA::Steering::Steerable
	{
	private:
		GameComponent::Weapons::Weapon* _weapon;

		float _health;
		const float _playerVelocity;
		GameComponent::StateMachine::StateManager _stateManager;

	public:
		Player(GameObjectTypes type, b2World& world, 
			float playerVelocity, float health,
			Components::PhysicsComponent* physicsComponent,
			Components::InputComponent* inputComponent,
			Components::GraphicsComponent* graphicsComponent);
		~Player();

		void init();

		GameComponent::Weapons::Weapon& weapon() const { return *_weapon; }

		virtual void doUpdate(float elapsedTime);

		virtual b2Vec2 getCurrentVelocity() const { return _physicsComponent->getBody()->GetLinearVelocity(); }
		virtual float getMaximumVelocity() const { return _playerVelocity; }
		virtual b2Vec2 getCurrentPosition() const { return _physicsComponent->getBody()->GetPosition(); }
		virtual float getMass() const { return _physicsComponent->getBody()->GetMass(); }

	};
}