#include "GameObjects\Actions\AimAction.h"
#include "GameObjects\Defs\PlayerDefinition.h"

using namespace GameComponent::GameActions;

AimAction::AimAction(GameComponent::Player& gameObject, b2Vec2 origin, b2Vec2 aimTarget)
	: _origin(origin), _aimTarget(aimTarget), Action(gameObject)
{
}

AimAction::~AimAction()
{

}

void AimAction::execute()
{
	/* TODO: What is the best way to get from where should I aim? 
	 * Thinking about aiming with a gun, it is not the center of the body that should be
	 * aligned with the target but rather the point of the gun.
	 */
	b2Vec2 toTarget = _aimTarget - _origin;
	float angRotation = std::atan2(toTarget.y, toTarget.x);
	_target.rotation(angRotation);
}