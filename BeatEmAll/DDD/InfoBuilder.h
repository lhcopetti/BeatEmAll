#pragma once

#include "DDD\GameObjectInfo.h"
#include "DDD\PhysicsInfo.h"
#include "RapidXML\rapidxml.hpp"

namespace DDD
{
	class InfoBuilder
	{
	public:
		InfoBuilder();
		bool load(const std::string& filePath);

		const std::string& getInfoName() { return _infoName; }
		GameObjectInfo* getGameInfo() { return _gameInfo; }

	private:
		std::string readAllText(const std::string& filePath);

		DDD::PhysicsInfo* parsePhysics(rapidxml::xml_node<>* node);
		DDD::FixtureInfo* parseFixtureInfo(rapidxml::xml_node<>* node);
		DDD::GraphicInfo* parseGraphic(rapidxml::xml_node<>* node);
		DDD::UserDataInfo* parseUserDataInfo(rapidxml::xml_node<>* node);

		UserDataInfo* parseBulletInfo(rapidxml::xml_node<>* node);
		UserDataInfo* parsePlayerInfo(rapidxml::xml_node<>* node);

		rapidxml::xml_document<> _xmlDoc;
		std::string _xmlRawContent;

		std::string _infoName;
		GameObjectInfo* _gameInfo;
	};
}