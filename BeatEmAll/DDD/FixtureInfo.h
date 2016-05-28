#pragma once

namespace DDD
{
	enum FixtureInfoType
	{
		 CIRCLE,
		 POLYGON
	};

	class FixtureInfo
	{

	public:
		FixtureInfo(float density, float restitution, float radius);
		FixtureInfo(float density, float restitution, float hx, float hy);

		const FixtureInfoType _fType;
		const float _density;
		const float _restitution;

		const float _radius;

		const float _hx, _hy;
	};
}