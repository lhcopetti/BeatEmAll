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
	class Player : public GameObject, 
		public IA::Steering::Steerable, 
		public Keys::KeyboardListener,
		public MouseComponent::MouseListener
	{
	private:
		GameComponent::Weapons::Weapon* _weapon;

		float _health;
		const float _playerVelocity;
		const float _playerRunningVelocity;
		GameComponent::StateMachine::StateManager _stateManager;

	public:
		Player(GameObjectTypes type, b2World& world, 
			float playerVelocity, float playerRunningVelocity,
			float health,
			Components::PhysicsComponent* physicsComponent,
			Components::InputComponent* inputComponent,
			Components::GraphicsComponent* graphicsComponent);
		~Player();

		void init();

		GameComponent::Weapons::Weapon& weapon() const { return *_weapon; }

		virtual void doUpdate(float elapsedTime);

		virtual void handleKeyboard(const std::map<Keys::KeyboardManager::KeyAction, bool>& keys);
		virtual void handleMouse(const sf::Vector2i& vector, bool leftClicked, bool rightClicked);

		b2Vec2 getCurrentVelocity() const { return _physicsComponent->getBody()->GetLinearVelocity(); }

		float getMaximumVelocity() const { return _playerVelocity; }
		float getRunningMaximumVelocity() const { return _playerRunningVelocity; }


		b2Vec2 getCurrentPosition() const { return _physicsComponent->getBody()->GetPosition(); }
		float getMass() const { return _physicsComponent->getBody()->GetMass(); }

	};
}