#include "GameObjects\Projectile\GraphicBullet.h"

#include "DebugBoxDraw\WorldConstants.h"

using namespace GameComponent::Projectiles;

void GraphicBullet::update(GameComponent::GameObject& gameObject)
{
	float circRadius = gameObject.body()->GetFixtureList()[0].GetShape()->m_radius * WorldConstants::SCALE;
	_circle.setRadius(circRadius);
	_circle.setPosition(gameObject.position());
	_circle.setOrigin(sf::Vector2f(circRadius / 2.f, circRadius / 2.f));
	_circle.setFillColor(sf::Color(0,0,0,255));
}


void GraphicBullet::draw(const GameComponent::GameObject& gameObject, sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_circle);
}