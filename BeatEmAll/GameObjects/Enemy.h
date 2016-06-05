#pragma once

#include "GameObjects\GameObject.h"

#include "IA\Steering\Steerable.h"
#include "IA\Steering\SteeringManager.h"

namespace GameComponent
{
	class Enemy : public GameComponent::GameObject, public IA::Steering::Steerable
	{

	public:
		GameComponent::GameObject* _tracking;

		IA::Steering::SteeringManager _steeringManager;

		Enemy(b2World& world,
			float velocity, float health,
			Components::PhysicsComponent* physicsComponent,
			Components::InputComponent* inputComponent,
			Components::GraphicsComponent* graphicsComponent);
		~Enemy();

		virtual void doUpdate(float elapsedTime);

		void init();

		virtual void beginContact(GameComponent::GameObject* other, b2Contact* contact);
		virtual void endContact(GameComponent::GameObject* other, b2Contact* contact);

		/* TODO: 2nd Duplication */
		virtual b2Vec2 getCurrentVelocity() const { return _physicsComponent->getBody()->GetLinearVelocity(); }
		virtual float getMaximumVelocity() const { return _velocity; }
		virtual b2Vec2 getCurrentPosition() const { return _physicsComponent->getBody()->GetPosition(); }
		virtual float getMass() const { return _physicsComponent->getBody()->GetMass(); }

	private:
		float _velocity;
		float _health;
	};
}