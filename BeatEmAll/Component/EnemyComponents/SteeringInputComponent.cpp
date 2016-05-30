#include "Component\EnemyComponents\SteeringInputComponent.h"

#include "Keyboard\KeyboardManager.h"
#include "Mouse\MouseManager.h"

#include "GameObjects\Player.h"
#include "SFML\Config.hpp"

#include "GameObjects\Actions\VelocityAction.h"

#include "DebugBoxDraw\WorldConstants.h"

using namespace Components::EnemyComponents;

void SteeringInputComponent::update(GameComponent::GameObject& player)
{
	sf::Vector2i vec = sf::Mouse::getPosition(*_window);
	sf::Vector2f vecF = sf::Vector2f(vec.x, vec.y);

	_manager->seek(WorldConstants::sfmlToPhysics(vecF));

	b2Vec2 steeringVel = _manager->getSteering();

	GA::VelocityAction* velocityAction = new GA::VelocityAction(steeringVel);

	GameComponent::Player& p = static_cast<GameComponent::Player&>(player);
	p.addAction(velocityAction);
	p.rotation(atan2(steeringVel.y, steeringVel.x));
}