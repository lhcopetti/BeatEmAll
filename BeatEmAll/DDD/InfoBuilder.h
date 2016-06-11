#pragma once

#include "DDD\GameObjectInfo.h"
#include "DDD\PhysicsInfo.h"
#include "RapidXML\rapidxml.hpp"

#include "Collision\CollisionCategory.h"

#include "Component\GraphicsComponent.h"

namespace DDD
{
	class InfoBuilder
	{
	public:
		InfoBuilder(Collision::CollisionCategory* collisionCat);
		bool load(const std::string& filePath);

		const std::string& getInfoName() { return _infoName; }
		GameObjectInfo* getGameInfo() { return _gameInfo; }

	private:
		std::string readAllText(const std::string& filePath);

		DDD::PhysicsInfo* parsePhysics(rapidxml::xml_node<>* node);
		DDD::FixtureInfo* parseFixtureInfo(rapidxml::xml_node<>* node);

		DDD::GraphicInfo* parseGraphic(rapidxml::xml_node<>* node, std::string& keyName);
		DDD::GraphicsInfo* parseGraphicCollection(rapidxml::xml_node<>* node);

		DDD::UserDataInfo* parseUserDataInfo(rapidxml::xml_node<>* node);

		UserDataInfo* parseBulletInfo(rapidxml::xml_node<>* node);
		UserDataInfo* parsePlayerInfo(rapidxml::xml_node<>* node);
		UserDataInfo* parseEnemyInfo(rapidxml::xml_node<>* node);

		unsigned short getCatValue(const std::string& category);

		rapidxml::xml_document<> _xmlDoc;
		std::string _xmlRawContent;

		std::string _infoName;
		GameObjectInfo* _gameInfo;

		Collision::CollisionCategory* _categories;
	};
}