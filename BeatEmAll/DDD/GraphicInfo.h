#pragma once

#include "SFML\Graphics.hpp"
#include "DDD\RepresentationInfo.h"

namespace DDD
{
	class GraphicInfo
	{
	public:
		GraphicInfo(RepresentationInfo* repInfo, sf::Vector2f origin, bool followRotation) :
			_info(repInfo),
			_origin(origin),
			_followRotation(followRotation) {}

		const RepresentationInfo* _info;
		const sf::Vector2f _origin;
		const bool _followRotation;
	};
}