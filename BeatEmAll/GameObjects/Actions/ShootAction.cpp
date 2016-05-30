#include "GameObjects\Actions\ShootAction.h"
#include "GameObjects\Defs\PlayerDefinition.h"

#include "GameObjects\Projectile\Bullet.h"

using namespace GameComponent::GameActions;

ShootAction::ShootAction(b2Vec2 originTarget, b2Vec2 shotTarget)
	: _originTarget(originTarget), _shotTarget(shotTarget)
{
}

ShootAction::~ShootAction()
{

}

void ShootAction::execute(GameComponent::GameObject& target)
{
	using namespace GameComponent::Projectiles;

	GameComponent::Player& player = static_cast<GameComponent::Player&>(target);
	GameComponent::Weapons::Weapon& weapon = player.weapon();

	b2Vec2 velChange2 = _shotTarget - _originTarget;
	velChange2.Normalize();
	velChange2 *= 2;

	GameComponent::Projectiles::Projectile* projectile = weapon.shoot(_originTarget, velChange2);

	if (nullptr != projectile)
		target.addChild(projectile);
}