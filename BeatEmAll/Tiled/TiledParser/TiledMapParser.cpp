#include <fstream>
#include <sstream>
#include <iostream>

#include "Tiled\TiledParser\TiledMapParser.h"
#include "RapidXML\rapidxml.hpp"

bool TiledMapParser::parse(TiledMap& tiledMap)
{
	std::ifstream file(_xmlLocation);
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();

	std::string content(buffer.str());

	rapidxml::xml_document<> doc;
	doc.parse<0>(&content[0]);

	rapidxml::xml_node<> *pRoot = doc.first_node();

	rapidxml::xml_node<> *tileSet = pRoot->first_node("tileset");

	for (rapidxml::xml_node<> *tileSetNode = tileSet->first_node("tile"); tileSetNode; tileSetNode = tileSetNode->next_sibling())
	{
		std::string id = tileSetNode->first_attribute("id")->value();

		rapidxml::xml_node<> *tile = tileSetNode->first_node();
		std::string height = tile->first_attribute("height")->value();
		std::string width = tile->first_attribute("width")->value();
		std::string source = tile->first_attribute("source")->value();

		tiledMap.addToImageTiles(id, new TiledImageTile(std::stoi(height), std::stoi(width), source));
	}

	rapidxml::xml_node<> *layerNode = tileSet->next_sibling();

	for (rapidxml::xml_node<>* layerTile = layerNode->first_node("data")->first_node("tile"); layerTile; layerTile = layerTile->next_sibling())
	{
		std::string cgid = layerTile->first_attribute("gid")->value();
		unsigned int gid = std::stoi(cgid);
		TiledLayerTile* tile = new TiledLayerTile(gid);
		tiledMap.addToLayerTile(tile);
	}

	return true;
}