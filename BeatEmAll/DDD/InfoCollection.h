#pragma once

#include "DDD\GameObjectInfo.h"

#include <map>
#include <string>

namespace DDD
{
	class InfoCollection
	{

	public:
		bool loadInfo(const std::string& filePath);
		const GameObjectInfo* get(const std::string& name) const;

		static InfoCollection& getInstance();

	private:
		InfoCollection();

		static InfoCollection* _instance;

		std::map<std::string, DDD::GameObjectInfo*> _map;
	};
}