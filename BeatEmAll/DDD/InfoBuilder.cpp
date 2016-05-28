#include "DDD\InfoBuilder.h"

#include "DDD\Representation\DrawingRepresentation.h"
#include "DDD\Representation\SpriteRepresentation.h"

#include "DDD\Projectile\BulletUserDataInfo.h"

#include "SFML\Graphics\Color.hpp"

#include <sstream>
#include <fstream>

using namespace DDD;

InfoBuilder::InfoBuilder()
{
	_gameInfo = nullptr;
}

bool InfoBuilder::load(const std::string& filePath)
{
	_xmlRawContent = readAllText(filePath);
	_xmlDoc.parse<0>(&_xmlRawContent[0]);

	rapidxml::xml_node<>* rootNode = _xmlDoc.first_node();
	
	if (!rootNode)
		return false;

	_infoName = rootNode->name();

	rapidxml::xml_node<>* physicsNode = rootNode->first_node("physics");
	DDD::PhysicsInfo* physics =  parsePhysics(physicsNode);

	rapidxml::xml_node<>* graphicNode = physicsNode->next_sibling();
	DDD::GraphicInfo* graphic = parseGraphic(graphicNode);

	rapidxml::xml_node<>* userDataInfoNode = graphicNode->next_sibling();
	DDD::UserDataInfo* userDataInfo = parseUserDataInfo(userDataInfoNode);

	_gameInfo = new GameObjectInfo(physics, graphic, userDataInfo);

	return true;
}

DDD::PhysicsInfo* InfoBuilder::parsePhysics(rapidxml::xml_node<>* nPhysics)
{
	rapidxml::xml_node<>* bodyNode = nPhysics->first_node("body");

	std::string bodyType = bodyNode->first_node("type")->value();
	std::string bullet = bodyNode->first_node("bullet")->value();

	std::vector<DDD::FixtureInfo*> fixtures;

	rapidxml::xml_node<>* fixturesNode = nPhysics->first_node("fixtures");

	for (rapidxml::xml_node<>* fixtureNode = fixturesNode->first_node("fixture"); fixtureNode; fixtureNode = fixtureNode->next_sibling())
	{
		DDD::FixtureInfo* fix = parseFixtureInfo(fixtureNode);

		if (!fix)
			break;

		fixtures.push_back(fix);
	}

	PhysicsBodyType pBodyType = bodyType == "dynamic" ? DYNAMIC : STATIC;
	bool bIsBullet = bullet == "true" ? true : false;

	return new PhysicsInfo(pBodyType, bIsBullet, fixtures);
}

DDD::FixtureInfo* InfoBuilder::parseFixtureInfo(rapidxml::xml_node<>* node)
{
	float density = std::stof(node->first_node("density")->value());
	float restitution = std::stof(node->first_node("restitution")->value());

	rapidxml::xml_node<>* shapeNode = node->first_node("shape");

	FixtureInfo* fixtureInfo;
	std::string shapeType = shapeNode->first_attribute("type")->value();

	if (shapeType == "circle")
	{
		float radius = std::stof(shapeNode->first_node("radius")->value());
		fixtureInfo = new FixtureInfo(density, restitution, radius);
	}
	else
	{
		float hx = std::stof(shapeNode->first_node("box")->first_attribute("hx")->value());
		float hy = std::stof(shapeNode->first_node("box")->first_attribute("hy")->value());
		fixtureInfo = new FixtureInfo(density, restitution, hx, hy);
	}

	return fixtureInfo;
}

bool to_bool(char* c)
{
	return strcmp(c, "true") == 0;
}

DDD::GraphicInfo* InfoBuilder::parseGraphic(rapidxml::xml_node<>* node)
{
	rapidxml::xml_node<>* originNode = node->first_node("origin");

	float originX = std::stof(originNode->first_attribute("x")->value());
	float originY = std::stof(originNode->first_attribute("y")->value());

	bool followRotation = to_bool(originNode->next_sibling()->value());

	rapidxml::xml_node<>* repNode = node->first_node("representation");

	RepresentationInfo* repInfo;

	if (std::string(repNode->first_attribute("repType")->value()) == "drawing")
	{
		rapidxml::xml_node<>* circleNode = repNode->first_node("circle");
		float radius = std::stof(circleNode->first_attribute("radius")->value());

		float r = std::stof(circleNode->first_attribute("r")->value());
		float g = std::stof(circleNode->first_attribute("g")->value());
		float b = std::stof(circleNode->first_attribute("b")->value());
		float a = std::stof(circleNode->first_attribute("a")->value());

		sf::Color color(r, g, b, a);

		repInfo = new DDD::DrawingRepresentation(DRAWING, radius, color);
	}
	else
	{
		std::string filePath = repNode->first_node("path")->value();

		rapidxml::xml_node<>* scaleNode = repNode->first_node("scale");
		float scaleX = std::stof(scaleNode->first_attribute("factorX")->value());
		float scaleY = std::stof(scaleNode->first_attribute("factorY")->value());

		repInfo = new DDD::SpriteRepresentation(SPRITE, filePath, scaleX, scaleY);
	}

	return new DDD::GraphicInfo(repInfo, sf::Vector2f(originX, originY), followRotation);
}

DDD::UserDataInfo* InfoBuilder::parseUserDataInfo(rapidxml::xml_node<>* node)
{
	if (_infoName == "BulletInfo")
		return parseBulletInfo(node);
	else if (_infoName == "PlayerInfo")
		return parsePlayerInfo(node);
	return nullptr;
}

UserDataInfo* InfoBuilder::parseBulletInfo(rapidxml::xml_node<>* node)
{
	float bulletLifeTime = std::stof(node->first_node("lifeTime")->value());
	return new DDD::Projectile::BulletUserDataInfo(bulletLifeTime);
}

UserDataInfo* InfoBuilder::parsePlayerInfo(rapidxml::xml_node<>* node)
{
	return nullptr;
}

std::string InfoBuilder::readAllText(const std::string& filePath)
{
	std::ifstream file(filePath);
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	return buffer.str();
}