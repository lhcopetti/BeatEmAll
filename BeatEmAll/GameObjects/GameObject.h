#pragma once
#include "Updatable\Updatable.h"
#include "GameObjects\ChildBearer.h"

#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"

namespace GameComponent
{
	class GameObject : public Updatable, public sf::Drawable, public GameComponent::ChildBearer
	{
	protected:
		
		b2World& _world;
		b2Body* _body;

		bool _alive;
		float _x, _y;

		float _rotationRad;

		std::vector<GameObject*> _children;

	public:
		GameObject(b2World& world);
		virtual ~GameObject() {}

		// TODO: Remove this two-step initialization
		virtual void init() {}

		virtual void update(float elapsedTime) = 0;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		virtual const std::vector<GameObject*>& getChildren() const;
		virtual void clearChildren();
		virtual void addChild(GameObject* child);

		bool isAlive() const { return _alive; };

		b2Body* body() { return _body; };
		float rotation() const { return _rotationRad; }
		void rotation(float r) { _rotationRad = r; }


		float x() const { return _x; }
		float y() const { return _y; }

		void position(float x, float y);
		sf::Vector2f position() const { return sf::Vector2f(_x, _y); }
	};
}