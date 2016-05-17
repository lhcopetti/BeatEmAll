#include "GameObjects\Actions\ShootAction.h"
#include "GameObjects\Defs\PlayerDefinition.h"

#include "GameObjects\Projectile\Bullet.h"

using namespace GameComponent::GameActions;

ShootAction::ShootAction(GameComponent::GameObject& gameObject, b2Vec2 originTarget, b2Vec2 shotTarget)
	: _originTarget(originTarget), _shotTarget(shotTarget), Action(gameObject)
{
}

ShootAction::~ShootAction()
{

}

void ShootAction::execute()
{
	using namespace GameComponent::Projectile;

	b2Body* body = _target.body();
	float radAngle = body->GetAngle();

	b2Vec2 velChange = b2Vec2(std::cos(radAngle), std::sin(radAngle));

	/* TODO: The Bullet lifetime should be parametrized. But by whom? */
	Bullet* bullet = new Bullet(*body->GetWorld(), 6.f, _originTarget, velChange);
	_target.addChild(bullet);
}