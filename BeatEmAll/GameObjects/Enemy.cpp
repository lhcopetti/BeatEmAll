#include "GameObjects\Enemy.h"


using namespace GameComponent;

Enemy::Enemy(b2World& world,
	Components::PhysicsComponent* physicsComponent,
	Components::InputComponent* inputComponent,
	Components::GraphicsComponent* graphicsComponent)
	:
	GameObject(GameObjectTypes::ENEMY_DEFAULT, world, physicsComponent, inputComponent, graphicsComponent)
{
	_x = 50;
	_y = 50;
}

void Enemy::init()
{

}

Enemy::~Enemy()
{

}

void Enemy::doUpdate(float elapsedTime)
{

}