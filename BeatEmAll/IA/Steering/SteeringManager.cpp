
#include "IA\Steering\SteeringManager.h"
#include "IA\Steering\SeekBehavior.h"
#include "DebugBoxDraw\WorldConstants.h"

using namespace IA::Steering;


SteeringManager::~SteeringManager()
{

}

void SteeringManager::seek(b2Vec2 position)
{
	if (!_gameObject)
		return;

	SeekBehavior seek(position, WorldConstants::sfmlToPhysics(64));
	_steering = seek.compute(*_gameObject);

	//WanderBehavior wander(2.f);
	//_steering = _wander.compute(*_player);
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