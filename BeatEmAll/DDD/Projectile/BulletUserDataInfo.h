#pragma once
#include "DDD\UserDataInfo.h"

namespace DDD
{
	namespace Projectile
	{
		class BulletUserDataInfo : public UserDataInfo
		{
		public:
			BulletUserDataInfo(float lifeTime, float bulletSpeed) : 
				_lifeTime(lifeTime),
				_bulletSpeed(bulletSpeed)
			{ }

			const float _lifeTime;
			const float _bulletSpeed;
		};
	}
}