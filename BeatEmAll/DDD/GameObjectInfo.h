#pragma once
#include "DDD\PhysicsInfo.h"
#include "DDD\GraphicInfo.h"
#include "DDD\UserDataInfo.h"

namespace DDD
{
	class GameObjectInfo
	{
	public:
		GameObjectInfo(DDD::PhysicsInfo* p, DDD::GraphicInfo* g, DDD::UserDataInfo* u) :
			_physicsInfo(p),
			_graphicInfo(g),
			_userDataInfo(u) {}

		const DDD::PhysicsInfo* _physicsInfo;
		const DDD::GraphicInfo* _graphicInfo;
		const DDD::UserDataInfo* _userDataInfo;
	};
}