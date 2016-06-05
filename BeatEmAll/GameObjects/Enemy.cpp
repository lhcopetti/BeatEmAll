#include "GameObjects\Enemy.h"

#include "DebugBoxDraw\WorldConstants.h"

#include "GameObjects\Actions\VelocityAction.h"

using namespace GameComponent;
namespace GA = GameActions;

Enemy::Enemy(b2World& world,
	float velocity, float health,
	Components::PhysicsComponent* physicsComponent,
	Components::InputComponent* inputComponent,
	Components::GraphicsComponent* graphicsComponent)
	:
	GameObject(GameObjectTypes::ENEMY_DEFAULT, world, physicsComponent, inputComponent, graphicsComponent),
	_velocity(velocity), _health(health)
{
	_x = 50;
	_y = 50;
	_tracking = nullptr;
}

void Enemy::init()
{
	_steeringManager.setGameObject(this);
}

Enemy::~Enemy()
{

}

void Enemy::doUpdate(float elapsedTime)
{
	if (!_tracking)
		return;

	_steeringManager.seek(WorldConstants::sfmlToPhysics(_tracking->position()));
	b2Vec2 steeringVel = _steeringManager.getSteering();

	GA::VelocityAction* velocityAction = new GA::VelocityAction(steeringVel);

	this->addAction(velocityAction);
	this->rotation(atan2(steeringVel.y, steeringVel.x));
}

void Enemy::beginContact(GameComponent::GameObject* other, b2Contact* contact)
{
	int x = 0;
	if (other && other->type() == GameObjectTypes::PLAYER)
		_tracking = other;
}

void Enemy::endContact(GameComponent::GameObject* other, b2Contact* contact) 
{
	int x = 0;
	if (other && other->type() == GameObjectTypes::PLAYER)
		_tracking = nullptr;
}