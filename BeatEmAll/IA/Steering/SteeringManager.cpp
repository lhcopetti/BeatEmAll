
#include "IA\Steering\SteeringManager.h"

using namespace IA::Steering;


SteeringManager::~SteeringManager()
{

}

void SteeringManager::seek(b2Vec2 position)
{
	if (!_player)
		return;

	b2Vec2 desiredVel = (position - _player->body()->GetPosition());
	desiredVel.Normalize();
	desiredVel *= 3.f /* Velocity */;

	_steering = b2Vec2_zero;
	_steering = desiredVel - _player->body()->GetLinearVelocity();
	_steering = truncate(_steering, 3.f);

	_steering = truncate(_player->body()->GetLinearVelocity() + _steering, 3.f);
}

b2Vec2 SteeringManager::doSeek(b2Vec2 position)
{
	return b2Vec2_zero;
}

b2Vec2 SteeringManager::truncate(b2Vec2 vector, float maxValue) const
{
	float num = maxValue / vector.Length();

	num = num > 1.f ? 1.f : num;

	vector.x *= num;
	vector.y *= num;

	return vector;
}