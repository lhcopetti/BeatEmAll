#include "DDD\InfoCollection.h"
#include "DDD\InfoBuilder.h"

using namespace DDD;

InfoCollection* InfoCollection::_instance = nullptr;

InfoCollection::InfoCollection()
{

}

const InfoCollection& InfoCollection::getInstance()
{
	if (nullptr == _instance)
		_instance = new InfoCollection();

	return *_instance;
}

bool InfoCollection::loadInfo(const std::string& filePath)
{
	InfoBuilder infoB;

	if (!infoB.load(filePath))
		return false;

	std::string keyInfo = infoB.getInfoName();
	GameObjectInfo* gInfo = infoB.getGameInfo();

	_map[keyInfo] = gInfo;
	return true;
}

const GameObjectInfo* InfoCollection::get(const std::string& key) const
{
	if (_map.find(key) == _map.end())
		return nullptr;
	return _map.at(key);
}