#pragma once

#include "DDD\GameObjectInfo.h"
#include "Collision\CollisionCategory.h"

#include <map>
#include <string>

namespace DDD
{
	class InfoCollection
	{

	public:
		bool loadCategory(const std::string& filePath);
		bool loadInfo(const std::string& filePath);
		const GameObjectInfo* get(const std::string& name) const;

		static InfoCollection& getInstance();

	private:
		InfoCollection();
		static InfoCollection* _instance;

		Collision::CollisionCategory _collisionCategory;
		std::map<std::string, DDD::GameObjectInfo*> _map;
	};
}