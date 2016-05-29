#pragma once

namespace DDD
{
	enum FixtureInfoType
	{
		SHAPE_CIRCLE,
		SHAPE_BOX,
		SHAPE_VERTICES
	};

	class FixtureShape
	{
	public:

		FixtureShape(FixtureInfoType f) : _type(f) { }
		const FixtureInfoType _type;
	};
}