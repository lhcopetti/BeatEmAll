#pragma once

namespace DDD
{
	enum RepresentationType
	{
		DRAWING,
		SPRITE
	};

	class RepresentationInfo
	{
	public:
		RepresentationInfo(RepresentationType type) : _type(type) {}

	public:
		RepresentationType _type;
	};
}