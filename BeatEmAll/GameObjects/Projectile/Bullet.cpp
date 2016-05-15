
#include "GameObjects\Projectile\Bullet.h"
#include "DebugBoxDraw\WorldConstants.h"

using namespace GameComponent::Projectile;

Bullet::~Bullet()
{
	_world.DestroyBody(_body);
	_body = nullptr;
}

Bullet::Bullet(b2World& world, float lifeTime, b2Vec2 initialPos, b2Vec2 initialVel) :
	GameComponent::GameObject(world),
	_lifeTime(lifeTime),
	_initialPos(initialPos),
	_initialVel(initialVel)
{
	_lifeTimeCounter = 0;
}

void Bullet::init()
{
	b2BodyDef bulletDef;
	bulletDef.type = b2_dynamicBody;
	bulletDef.bullet = true;
	bulletDef.position = _initialPos;

	b2CircleShape circle;
	circle.m_radius = 10 / 2 / WorldConstants::SCALE;

	b2FixtureDef bulletFix;
	bulletFix.density = .1f;
	bulletFix.shape = &circle;
	bulletFix.restitution = .5f;

	_body = _world.CreateBody(&bulletDef);
	_body->CreateFixture(&bulletFix);

	float ratio = _body->GetMass() * BULLET_SPEED;
	b2Vec2 impulse = b2Vec2(_initialVel.x * ratio, _initialVel.y * ratio);

	_body->ApplyLinearImpulse(impulse, _body->GetWorldCenter(), true);
}

void Bullet::update(float elapsedTime)
{
	_lifeTimeCounter += elapsedTime;

	if (_lifeTimeCounter > _lifeTime)
		_alive = false;
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	/* Drawing will be handled (for now) by debugDraw from Box2D */
	float circleRadius = _body->GetFixtureList()[0].GetShape()->m_radius * WorldConstants::SCALE;

	sf::CircleShape circle(circleRadius);

	sf::Vector2f pos = WorldConstants::physicsToSFML(_body->GetPosition());
	circle.setOrigin(sf::Vector2f(circleRadius / 2.f, circleRadius / 2.f));
	circle.setPosition(pos);

	int ratio = std::floor(255 * _lifeTimeCounter / _lifeTime);

	circle.setFillColor(sf::Color(255, 255 - ratio, 255 - ratio));
	
	target.draw(circle);
}
