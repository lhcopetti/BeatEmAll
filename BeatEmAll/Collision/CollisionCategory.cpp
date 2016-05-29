#include "Collision\CollisionCategory.h"

#include "RapidXML\rapidxml.hpp"
#include "FileIO\FileIO.h"

using namespace Collision;

CollisionCategory::CollisionCategory()
{

}

bool CollisionCategory::load(const std::string& fileName)
{
	std::string xmlContent = FileInputOutput::FileIO::readAllText(fileName);

	rapidxml::xml_document<> xmlDocument;
	xmlDocument.parse<0>(&xmlContent[0]);

	rapidxml::xml_node<>* root = xmlDocument.first_node("CollisionCategories");

	for (rapidxml::xml_node<>* node = root->first_node("category"); node; node = node->next_sibling())
	{
		std::string categ = node->first_attribute("name")->value();
		unsigned short value = std::stoi(node->first_attribute("value")->value());
		_categories[categ] = value;
	}
	return true;
}

unsigned short CollisionCategory::getCategoryValue(const std::string& key)
{
	std::vector<std::string> vector = { key };
	return getCategoryValue(vector);
}

unsigned short CollisionCategory::getCategoryValue(const std::vector<std::string>& keys)
{
	unsigned short value = 0x0000;

	for (int i = 0; i < keys.size(); i++)
		value |= _categories[keys[i]];
	return value;
}