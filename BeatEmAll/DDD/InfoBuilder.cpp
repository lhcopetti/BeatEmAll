#include "DDD\InfoBuilder.h"

#include "DDD\Representation\DrawingRepresentation.h"
#include "DDD\Representation\SpriteRepresentation.h"

#include "DDD\GameObjects\EnemyDefaultUserDataInfo.h"
#include "DDD\GameObjects\PlayerUserDataInfo.h"
#include "DDD\Projectile\BulletUserDataInfo.h"

#include "Component\GenericGraphicsComponent.h"

#include "DebugBoxDraw\WorldConstants.h"

#include "SFML\Graphics\Color.hpp"

#include "String\SplitString.h"

#include <sstream>
#include <fstream>

using namespace DDD;

float getFloat(rapidxml::xml_node<>* parent, const std::string& nodeName);
const std::vector<std::string> getCategoryAttr(rapidxml::xml_node<>* parent, const std::string& attrName);

float getPhysicsAngle(rapidxml::xml_node<>* parent, const std::string& nodeName);
b2Vec2 getCoordinate(rapidxml::xml_node<>* node, const std::string& nodeName, const std::string& xName, const std::string& yName);
b2Vec2 getCoordinate(rapidxml::xml_node<>* node, const std::string& xName, const std::string& yName);
float getPhysicsNodeValue(rapidxml::xml_node<>* parent, const std::string& nodeName);

InfoBuilder::InfoBuilder(Collision::CollisionCategory* collisionCategory) :
	_categories(collisionCategory)
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
	DDD::GraphicsInfo* graphics = parseGraphicCollection(graphicNode);

	rapidxml::xml_node<>* userDataInfoNode = graphicNode->next_sibling();
	DDD::UserDataInfo* userDataInfo = parseUserDataInfo(userDataInfoNode);

	_gameInfo = new GameObjectInfo(physics, graphics, userDataInfo);

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
	float density = getFloat(node, "density");
	float restitution = getFloat(node, "restitution");
	bool isSensor = false;

	if (nullptr != node->first_node("isSensor"))
		isSensor = true;

	rapidxml::xml_node<>* filterNode = node->first_node("filter");
	unsigned short category = _categories->getCategoryValue(getCategoryAttr(filterNode, "category"));
	unsigned short maskBits = _categories->getCategoryValue(getCategoryAttr(filterNode, "maskBits"));

	rapidxml::xml_node<>* shapeNode = node->first_node("shape");

	FixtureInfo* fixtureInfo;
	std::string shapeType = shapeNode->first_attribute("type")->value();

	if (shapeType == "circle")
	{
		float radius = getPhysicsNodeValue(shapeNode, "radius");
		b2Vec2 position = getCoordinate(shapeNode, "position", "x", "y");
		fixtureInfo = new FixtureInfo(density, restitution, category, maskBits, isSensor, radius, position);
	}
	else if (shapeType == "box")
	{
		b2Vec2 halfLength = getCoordinate(shapeNode, "size", "width", "height");
		b2Vec2 center = getCoordinate(shapeNode, "center", "x", "y");
		float angle = getPhysicsAngle(shapeNode, "angle");
		fixtureInfo = new FixtureInfo(density, restitution, category, maskBits, isSensor, halfLength.x / 2.f, halfLength.y / 2.f, center, angle);
	}
	else if (shapeType == "vertices")
	{
		std::vector<b2Vec2> vertices;

		for (rapidxml::xml_node<>* node = shapeNode->first_node("vertice"); node; node = node->next_sibling())
		{
			b2Vec2 vertice = getCoordinate(node, "x", "y");
			vertices.push_back(vertice);
		}
		fixtureInfo = FixtureInfo::newVerticesFixture(density, restitution, category, maskBits, isSensor, vertices);
	}

	return fixtureInfo;
}

bool to_bool(char* c)
{
	return strcmp(c, "true") == 0;
}

DDD::GraphicInfo* InfoBuilder::parseGraphic(rapidxml::xml_node<>* node, std::string& keyName)
{
	keyName = node->first_attribute("key")->value();

	rapidxml::xml_node<>* originNode = node->first_node("origin");

	float originX = std::stof(originNode->first_attribute("x")->value());
	float originY = std::stof(originNode->first_attribute("y")->value());
	sf::Vector2f origin = sf::Vector2f(originX, originY);

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

DDD::GraphicsInfo* InfoBuilder::parseGraphicCollection(rapidxml::xml_node<>* node)
{
	DDD::GraphicsInfo* _graphicsInfo = new DDD::GraphicsInfo;

	for (rapidxml::xml_node<>* graphicNode = node->first_node("graphic"); graphicNode; graphicNode = graphicNode->next_sibling())
	{
		std::string keyName;
		DDD::GraphicInfo* graphic = parseGraphic(graphicNode, keyName);
		_graphicsInfo->addGraphic(keyName, graphic);
	}

	return _graphicsInfo;
}

DDD::UserDataInfo* InfoBuilder::parseUserDataInfo(rapidxml::xml_node<>* node)
{
	if (_infoName == "BulletInfo")
		return parseBulletInfo(node);
	else if (_infoName == "PlayerInfo")
		return parsePlayerInfo(node);
	else if (_infoName == "EnemyDefault")
		return parseEnemyInfo(node);
	return nullptr;
}

UserDataInfo* InfoBuilder::parseBulletInfo(rapidxml::xml_node<>* node)
{
	float bulletLifeTime = std::stof(node->first_node("lifeTime")->value());
	float bulletSpeed = std::stof(node->first_node("bulletSpeed")->value());
	return new DDD::Projectile::BulletUserDataInfo(bulletLifeTime, bulletSpeed);
}

UserDataInfo* InfoBuilder::parsePlayerInfo(rapidxml::xml_node<>* node)
{
	float velocity = getFloat(node, "velocity");
	float runningVelocity = getFloat(node, "runningVelocity");
	float health = getFloat(node, "health");
	return new DDD::GameComponent::PlayerUserDataInfo(velocity, runningVelocity, health);
}

UserDataInfo* InfoBuilder::parseEnemyInfo(rapidxml::xml_node<>* node)
{
	float velocity = getFloat(node, "velocity");
	float health = getFloat(node, "health");
	return new DDD::GameComponent::EnemyDefaultUserDataInfo(velocity, health);
}

std::string InfoBuilder::readAllText(const std::string& filePath)
{
	std::ifstream file(filePath);
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	return buffer.str();
}

b2Vec2 getCoordinate(rapidxml::xml_node<>* node, const std::string& nodeName, const std::string& xName, const std::string& yName)
{
	rapidxml::xml_node<>* coordNode = node->first_node(nodeName.c_str());

	float xValue = std::stof(coordNode->first_attribute(xName.c_str())->value());
	float yValue = std::stof(coordNode->first_attribute(yName.c_str())->value());

	return b2Vec2(	WorldConstants::sfmlToPhysics(xValue), 
					WorldConstants::sfmlToPhysics(yValue));
}

b2Vec2 getCoordinate(rapidxml::xml_node<>* node, const std::string& xName, const std::string& yName)
{
	float xValue = std::stof(node->first_attribute(xName.c_str())->value());
	float yValue = std::stof(node->first_attribute(yName.c_str())->value());

	return b2Vec2(	WorldConstants::sfmlToPhysics(xValue), 
					WorldConstants::sfmlToPhysics(yValue));
}


float getPhysicsNodeValue(rapidxml::xml_node<>* parent, const std::string& nodeName)
{
	float value = std::stof(parent->first_node(nodeName.c_str())->value());
	return WorldConstants::sfmlToPhysics(value);
}

float getPhysicsAngle(rapidxml::xml_node<>* parent, const std::string& nodeName)
{
	return DEGTORAD * getFloat(parent, nodeName);
}

float getFloat(rapidxml::xml_node<>* parent, const std::string& nodeName)
{
	return std::stof(parent->first_node(nodeName.c_str())->value());
}

const std::vector<std::string> getCategoryAttr(rapidxml::xml_node<>* parent, const std::string& attrName)
{
	std::vector<std::string> categories;
	std::string attributeValue = parent->first_attribute(attrName.c_str())->value();
	String::split(attributeValue, '|', categories);
	return categories;
}

unsigned short InfoBuilder::getCatValue(const std::string& category)
{
	return 0x0;
}