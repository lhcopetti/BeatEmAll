#include "DDD\GraphicsInfo.h"

using namespace DDD;

GraphicsInfo::GraphicsInfo()
{

}

const std::map<std::string, DDD::GraphicInfo*>& GraphicsInfo::getMap() const
{
	return _graphics;
}

void GraphicsInfo::addGraphic(std::string key, DDD::GraphicInfo* graphic)
{
	if (_graphics.find(key) != _graphics.end())
	{
		DDD::GraphicInfo* g = _graphics[key];
		delete g;
	}

	_graphics[key] = graphic;
}