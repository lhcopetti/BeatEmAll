#pragma once
#include "Updatable\Updatable.h"
#include "GameObjects\ChildBearer.h"

#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"

#include "GameObjects\Actions\Action.h"

#include "Component\PhysicsComponent.h"
#include "Component\GraphicsComponent.h"
#include "Component\InputComponent.h"

#include "GameObjects\GameObjectTypes.h"

#include "Collision\Collidable.h"

namespace GameComponent
{
	class GameObject : public Updatable, public sf::Drawable, public GameComponent::ChildBearer, public Collision::Collidable
	{
	protected:
		
		const GameObjectTypes _type;

		b2World& _world;
//		b2Body* _body;

		bool _alive;
		float _x, _y;

		float _rotationRad;

		std::vector<GameObject*> _children;

		Components::PhysicsComponent* _physicsComponent;
		Components::InputComponent* _inputComponent;
		Components::GraphicsComponent* _graphicsComponent;

		std::vector<GameComponent::GameActions::Action*> _actions;
	public:
		GameObject(GameObjectTypes type, b2World& world, 
			Components::PhysicsComponent* physics,
			Components::InputComponent* inputC, 
			Components::GraphicsComponent* graphicsC);
		virtual ~GameObject();

		// TODO: Remove this two-step initialization
		virtual void init() {}

		void update(float elapsedTime);
		virtual void doUpdate(float elapsedTime) {}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		virtual const std::vector<GameObject*>& getChildren() const;
		virtual void clearChildren();
		virtual void addChild(GameObject* child);

		GameObjectTypes type() const { return _type; }

		bool isAlive() const { return _alive; };

		Components::GraphicsComponent* graphics() { return _graphicsComponent; }
		Components::PhysicsComponent* physics() { return _physicsComponent; }

		b2Body* body() { return _physicsComponent->getBody(); };
		float rotation() const { return _rotationRad; }
		void rotation(float r) { _rotationRad = r; }

		void addAction(GameActions::Action* action);

		float x() const { return _x; }
		float y() const { return _y; }

		void position(float x, float y);
		sf::Vector2f position() const { return sf::Vector2f(_x, _y); }

		static Components::GraphicsComponent* nullGraphics() { return nullptr; }
		static Components::InputComponent* nullInput() { return nullptr; }
		static Components::PhysicsComponent* nullPhysics() { return nullptr; }

	};
}