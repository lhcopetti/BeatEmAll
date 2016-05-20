
#include "GameObjects\GameObject.h"

using namespace GameComponent;

GameObject::GameObject(b2World& world) :
	_world(world)
{
	_alive = true;
	_body = nullptr;
	_rotationRad = 0.f;
	_x = _y = 0.f;
}

const std::vector<GameObject*>& GameObject::getChildren() const
{
	return _children;
}

void GameObject::clearChildren()
{
	/* Do not free the pointers */
	_children.clear();
}

void GameObject::addChild(GameObject* child)
{
	_children.push_back(child);
}

void GameObject::position(float x, float y)
{
	_x = x;
	_y = y;
}