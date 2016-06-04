#include "GameObjects\Actions\VelocityAction.h"
#include "GameObjects\Defs\PlayerDefinition.h"

#include "GameObjects\GameObject.h"

using namespace GameComponent::GameActions;

VelocityAction::VelocityAction(b2Vec2 newVelocity)
	: _newVelocity(newVelocity)
{
}

VelocityAction::~VelocityAction()
{

}

void VelocityAction::execute(GameComponent::GameObject& target)
{
	b2Body* body = target.body();
	b2Vec2 velChange = _newVelocity - body->GetLinearVelocity();

	b2Vec2 force = b2Vec2_zero;

	/*
	* TODO: Remove 1 / 60.f. Clearly a configurable parameter.
	*/
	force.x = body->GetMass() * velChange.x / (1 / 60.f);
	force.y = body->GetMass() * velChange.y / (1 / 60.f);

	body->ApplyForce(force, body->GetWorldCenter(), true);
}