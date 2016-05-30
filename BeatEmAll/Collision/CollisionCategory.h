#pragma once
#include <map>
#include <vector>
#include <string>

namespace Collision
{
	/*enum CollisionCategories
	{
		CAT_BOUNDARY	= 0x0001,
		CAT_PLAYER		= 0x0002,
		CAT_ENEMY		= 0x0004,
		CAT_BULLET		= 0x0008
	};*/

	class CollisionCategory
	{
	public:
		CollisionCategory();
		bool load(const std::string& fileName);

		unsigned short getCategoryValue(const std::string& key);
		unsigned short getCategoryValue(const std::vector<std::string>& keys);

		const std::map<std::string, unsigned short>& getCategories() const { return _categories; }

	private:
		std::map<std::string, unsigned short> _categories;
	};
}