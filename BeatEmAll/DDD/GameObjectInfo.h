#pragma once
#include "DDD\PhysicsInfo.h"

#include "DDD\GraphicsInfo.h"
#include "Component\GraphicsComponent.h"

#include "DDD\UserDataInfo.h"

namespace DDD
{
	class GameObjectInfo
	{
	public:
		GameObjectInfo(DDD::PhysicsInfo* p, DDD::GraphicsInfo* g, DDD::UserDataInfo* u) :
			_physicsInfo(p),
			_graphicsInfo(g),
			_userDataInfo(u) {}

		const DDD::PhysicsInfo* _physicsInfo;
		const DDD::GraphicsInfo* _graphicsInfo;
		const DDD::UserDataInfo* _userDataInfo;
	};
}