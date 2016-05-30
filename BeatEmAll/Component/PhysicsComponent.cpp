#include "PhysicsComponent.h"

#include "DebugBoxDraw\WorldConstants.h"
#include "GameObjects\GameObject.h"

using namespace Components;

void PhysicsComponent::update(GameComponent::GameObject& gameObject)
{
	/* Update position */
	sf::Vector2f bodyPos = WorldConstants::physicsToSFML(getBody()->GetPosition());
	gameObject.position(bodyPos.x, bodyPos.y);

	/* Update rotation */
	getBody()->SetTransform(getBody()->GetPosition(), gameObject.rotation());
}
