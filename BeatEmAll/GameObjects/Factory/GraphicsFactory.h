#pragma once

#include "Component\GraphicsComponent.h"
#include "DDD\GraphicsInfo.h"

namespace GameComponent
{
	namespace Factory
	{
		class GraphicsFactory
		{
		public:
			static Components::GraphicsComponent* makeNew(const DDD::GraphicsInfo* graphicsInfo);
		};
	}
}