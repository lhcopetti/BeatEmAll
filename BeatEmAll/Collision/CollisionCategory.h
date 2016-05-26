#pragma once

namespace Collision
{
	enum CollisionCategories
	{
		CAT_BOUNDARY	= 0x0001,
		CAT_PLAYER		= 0x0002,
		CAT_ENEMY		= 0x0004,
		CAT_BULLET		= 0x0008
	};
}