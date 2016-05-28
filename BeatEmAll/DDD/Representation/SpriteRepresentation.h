#pragma once

#include <string>
#include "DDD\RepresentationInfo.h"

namespace DDD
{
	class SpriteRepresentation : public RepresentationInfo
	{
	public:
		SpriteRepresentation(RepresentationType type, std::string filePath, float scaleX, float scaleY) :
			RepresentationInfo(type),
			_filePath(filePath),
			_scaleX(scaleX),
			_scaleY(scaleY) {}

		const std::string _filePath;
		const float _scaleX;
		const float _scaleY;
	};
}