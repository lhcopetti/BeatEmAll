#pragma once
#include "DDD\UserDataInfo.h"

namespace DDD
{
	namespace Projectile
	{
		class BulletUserDataInfo : public UserDataInfo
		{
		public:
			BulletUserDataInfo(float lifeTime) : _lifeTime(lifeTime) { }

			const float _lifeTime;
		};
	}
}