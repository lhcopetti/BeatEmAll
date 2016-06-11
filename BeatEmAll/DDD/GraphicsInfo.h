#pragma once

#include "SFML\Graphics.hpp"
#include "DDD\GraphicInfo.h"

namespace DDD
{
	class GraphicsInfo
	{
	public:
		GraphicsInfo();
		const std::map<std::string, DDD::GraphicInfo*>& getMap() const;
		void addGraphic(std::string key, DDD::GraphicInfo* graphic);

	private:
		std::map<std::string, DDD::GraphicInfo*> _graphics;
	};
}