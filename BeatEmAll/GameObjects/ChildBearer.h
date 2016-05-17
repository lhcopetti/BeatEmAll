#pragma once

#include <vector>

namespace GameComponent
{
	class GameObject;
}

namespace GameComponent
{
	class ChildBearer
	{
	public:
		virtual const std::vector<GameComponent::GameObject*>& getChildren() const = 0;
		virtual void clearChildren() = 0;
		virtual void addChild(GameObject* child) = 0;
	};
}