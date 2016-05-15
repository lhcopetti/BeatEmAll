#pragma once

#include <vector>
#include "GameObjects\GameObject.h"

namespace GameComponent
{
	class ChildBearer
	{

		virtual const std::vector<GameObject*>& getChildren() const = 0;

		virtual void clearChildren() = 0;
	};
}