#include "GameObjects\Actions\MoveAction.h"
#include "GameObjects\Defs\PlayerDefinition.h"

using namespace GameComponent::GameActions;

MoveAction::MoveAction(GameComponent::GameObject& gameObject, MoveDirection moveDirection)
	: _moveDir(moveDirection), Action(gameObject)
{
}

MoveAction::~MoveAction()
{

}

void MoveAction::execute()
{
	b2Body* body = _target.body();

	float pVelocity = GameComponent::Definitions::PlayerDefinition::MOVE_VELOCITY;
	b2Vec2 nextVel(_moveDir.xDir * pVelocity, _moveDir.yDir * pVelocity);

	b2Vec2 velChange = nextVel - body->GetLinearVelocity();

	b2Vec2 force;

	/* 
	 * TODO: Remove 1 / 60.f. Clearly a configurable parameter. 
	 */
	force.x = body->GetMass() * velChange.x / (1 / 60.f);
	force.y = body->GetMass() * velChange.y / (1 / 60.f);

	body->ApplyForce(force, body->GetWorldCenter(), true);
}