
#include "GameObjects\GameObject.h"

using namespace GameComponent;

GameObject::GameObject(b2World& world) :
	_world(world)
{
	_alive = true;
	_body = nullptr;
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