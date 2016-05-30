#include "DDD\InfoCollection.h"
#include "DDD\InfoBuilder.h"

using namespace DDD;

InfoCollection* InfoCollection::_instance = nullptr;

InfoCollection::InfoCollection()
{

}

InfoCollection& InfoCollection::getInstance()
{
	if (nullptr == _instance)
		_instance = new InfoCollection();

	return *_instance;
}

bool InfoCollection::loadInfo(const std::string& filePath)
{
	InfoBuilder infoB(&_collisionCategory);

	if (!infoB.load(filePath))
		return false;

	std::string keyInfo = infoB.getInfoName();
	GameObjectInfo* gInfo = infoB.getGameInfo();

	_map[keyInfo] = gInfo;
	return true;
}

bool InfoCollection::loadCategory(const std::string& filePath)
{
	return _collisionCategory.load(filePath);
}

const GameObjectInfo* InfoCollection::get(const std::string& key) const
{
	if (_map.find(key) == _map.end())
		return nullptr;
	return _map.at(key);
}