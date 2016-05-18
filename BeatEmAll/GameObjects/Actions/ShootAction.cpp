#include "GameObjects\Actions\ShootAction.h"
#include "GameObjects\Defs\PlayerDefinition.h"

#include "GameObjects\Projectile\Bullet.h"

using namespace GameComponent::GameActions;

ShootAction::ShootAction(GameComponent::Player& gameObject, b2Vec2 originTarget, b2Vec2 shotTarget)
	: _originTarget(originTarget), _shotTarget(shotTarget), Action(gameObject)
{
}

ShootAction::~ShootAction()
{

}

void ShootAction::execute()
{
	using namespace GameComponent::Projectiles;

	b2Body* body = _target.body();
	float radAngle = body->GetAngle();

	GameComponent::Player& player = static_cast<GameComponent::Player&>(_target);
	GameComponent::Weapons::Weapon& weapon = player.weapon();

	b2Vec2 velChange = b2Vec2(std::cos(radAngle), std::sin(radAngle));

	GameComponent::Projectiles::Projectile* projectile = weapon.shoot(_originTarget, velChange);

	if (nullptr != projectile)
		_target.addChild(projectile);
}