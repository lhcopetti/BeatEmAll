#include "GameObjects\Factory\GraphicsFactory.h"

#include "DDD\Representation\DrawingRepresentation.h"
#include "DDD\Representation\SpriteRepresentation.h"

#include "Component\GenericGraphicsComponent.h"

using namespace GameComponent::Factory;


Components::GraphicsComponent* GraphicsFactory::makeNew(const DDD::GraphicsInfo* graphicsInfo)
{
	Components::GraphicsComponent* graphicsComponent = new Components::GraphicsComponent;

	for (auto it = graphicsInfo->getMap().begin(); it != graphicsInfo->getMap().end(); ++it)
	{
		std::string key = it->first;
		const DDD::GraphicInfo* graphicInfo = it->second;
		Components::Graphic* graphic = nullptr;

		if (DDD::DRAWING == graphicInfo->_info->_type)
		{
			const DDD::DrawingRepresentation* dr = static_cast<const DDD::DrawingRepresentation*>(graphicInfo->_info);

			sf::CircleShape* circleShape = new sf::CircleShape(dr->_radius);
			circleShape->setFillColor(dr->_color);

			graphic = Components::GenericGraphicsComponent::newDrawingGraphic(
				circleShape,
				graphicInfo->_followRotation,
				graphicInfo->_origin);
		}
		else
		{
			const DDD::SpriteRepresentation* sr = static_cast<const DDD::SpriteRepresentation*>(graphicInfo->_info);

			sf::Texture* texture = new sf::Texture;
			texture->loadFromFile(sr->_filePath);
			sf::Sprite* sprite = new sf::Sprite;
			sprite->setTexture(*texture);
			sprite->setScale(sf::Vector2f(sr->_scaleX, sr->_scaleY));
			// TODO: what if it is not a drawing,
			// what if it is not a projectile but a player?
			graphic = Components::GenericGraphicsComponent::newSpriteGraphic
				(sprite, graphicInfo->_followRotation, graphicInfo->_origin);
		}

		graphicsComponent->addGraphic(key, graphic);
	}
	return graphicsComponent;

}