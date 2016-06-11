
#include "GameObjects\Projectile\Bullet.h"
#include "DebugBoxDraw\WorldConstants.h"

#include "Collision\CollisionCategory.h"

using namespace GameComponent::Projectiles;

//uint16 Bullet::_categoryType = Collision::CAT_BULLET;
//
//uint16 Bullet::_maskBits =		Collision::CAT_BOUNDARY |
//								Collision::CAT_BULLET |
//								Collision::CAT_ENEMY;

Bullet::~Bullet()
{
	if (_physicsComponent)
	{
		delete _physicsComponent;
		_physicsComponent = nullptr;
	}

	if (_graphicsComponent)
	{
		delete _graphicsComponent;
		_graphicsComponent = nullptr;
	}
}

Bullet::Bullet(b2World& world, Components::PhysicsComponent* physics, Components::GraphicsComponent* gComponent, float lifeTime, float bulletSpeed, b2Vec2 initialPos, b2Vec2 initialVel) :
	GameComponent::Projectiles::Projectile(GameObjectTypes::PROJECTILE_BULLET, world, physics, GameObject::nullInput(), gComponent),
	_lifeTime(lifeTime),
	_bulletSpeed(bulletSpeed),
	_initialPos(initialPos),
	_initialVel(initialVel)
{
	_lifeTimeCounter = 0;
}

void Bullet::init()
{
	//_physicsComponent->getBody()->SetUserData(this);
	//bulletDef.position = _initialPos;
	//bulletDef.userData = this;
	/*b2BodyDef bulletDef;
	bulletDef.type = b2_dynamicBody;
	bulletDef.bullet = true;
	bulletDef.position = _initialPos;
	bulletDef.userData = this;

	b2CircleShape circle;
	circle.m_radius = 10 / 2 / WorldConstants::SCALE;

	b2FixtureDef bulletFix;
	bulletFix.density = .1f;
	bulletFix.shape = &circle;
	bulletFix.restitution = .5f;
	bulletFix.filter.categoryBits = _categoryType;
	bulletFix.filter.maskBits = _maskBits;

	_body = _world.CreateBody(&bulletDef);
	_body->CreateFixture(&bulletFix);*/
	_graphicsComponent->setActiveGraphic("BULLET");

	float ratio = _physicsComponent->getBody()->GetMass() * _bulletSpeed;
	b2Vec2 impulse = b2Vec2(_initialVel.x * ratio, _initialVel.y * ratio);

	_physicsComponent->getBody()->ApplyLinearImpulse(impulse, _physicsComponent->getBody()->GetWorldCenter(), true);
}

void Bullet::doUpdate(float elapsedTime)
{
	_lifeTimeCounter += elapsedTime;

	if (_lifeTimeCounter > _lifeTime)
		_alive = false;
}

void Bullet::beginContact(GameComponent::GameObject* other, b2Contact* contact)
{
	if (nullptr == other)
		return;

	if (other->type() == GameObjectTypes::ENEMY_DEFAULT)
		_alive = false;
}