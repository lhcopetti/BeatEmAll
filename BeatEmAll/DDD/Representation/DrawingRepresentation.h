#pragma once
#include "DDD\RepresentationInfo.h"
#include "SFML\Graphics\Color.hpp"

namespace DDD
{
	class DrawingRepresentation : public RepresentationInfo
	{
	public:
		DrawingRepresentation(RepresentationType type, float radius, sf::Color color) :
			RepresentationInfo(type),
			_radius(radius),
			_color(color) {}

		const float _radius;
		const sf::Color _color;
	};
}